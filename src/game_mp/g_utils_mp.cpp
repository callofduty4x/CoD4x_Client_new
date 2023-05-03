#include <game/server_game_shared.h>
#include <common/com_dobj_shared.h>
#include <xanim/dobj_shared.h>
#include <server/server_shared.h>
#include "game_mp_shared.h"

XModel *cached_models[MAX_MODELS];



void G_SafeDObjFree(gentity_s *ent)
{
  Com_SafeServerDObjFree(ent->s.number);
}

XModel * G_GetModel(int index)
{
    assert(index > 0);
    assert(index < MAX_MODELS);
    return cached_models[index];
}

void G_UpdateTagInfo(gentity_s *ent, int bParentHasDObj)
{
  tagInfo_s *tagInfo;

  tagInfo = ent->tagInfo;
  assert(tagInfo);

  if ( tagInfo->name )
  {
    if ( !bParentHasDObj )
    {
      G_EntUnlink(ent);
      return;
    }
    tagInfo->index = SV_DObjGetBoneIndex(tagInfo->parent, tagInfo->name);
    //G_UpdateClientLinkInfo(ent);
    if(tagInfo->index < 0)
    {
      G_EntUnlink(ent);
    }
  }
  else if ( tagInfo->index != -1 )
  {
    tagInfo->index = -1;
    //G_UpdateClientLinkInfo(ent);
  }
}


void G_UpdateTagInfoOfChildren(gentity_s *parent, int bHasDObj)
{
  gentity_s *next;
  gentity_s *ent;

  for ( ent = parent->tagChildren; ent; ent = next )
  {
    next = ent->tagInfo->next;
    G_UpdateTagInfo(ent, bHasDObj);
  }
}

void G_UpdateTags(gentity_s *ent, int bHasDObj)
{
/*
  if ( ent->vehicle )
  {
    Vehicle_InitBoneTags(ent->vehicle);
  }
  */
  G_UpdateTagInfoOfChildren(ent, bHasDObj);
}

void G_DObjUpdate(gentity_s *ent)
{
    DObj_s *dobj;
    //XAnimTree_s *tree;
    XModel *model;
    int numModels;
    int i;
    int modelIndex;
    DObjModel_s dobjModels[32];

    if ( ent->client )
    {
        return;
    }
    G_SafeDObjFree(ent);
    modelIndex = ent->model;
    if ( ent->model )
    {
      //tree = G_GetEntAnimTree(ent);
      model = G_GetModel(modelIndex);
      assert(model);
      dobjModels[0].model = model;
      dobjModels[0].boneName = 0;
      dobjModels[0].ignoreCollision = 0;
      numModels = 1;
      if ( ent->s.eType == ET_GENERAL|| ent->s.eType == ET_SCRIPTMOVER || ent->s.eType == ET_PLANE || ent->s.eType == ET_MG42 )
      {
        AssignToSmallerType(ent->s.index.brushModel, modelIndex);
      }
      else if ( ent->s.eType == ET_VEHICLE || ent->s.eType == ET_HELICOPTER )
      {
        ent->s.un2.vehicleXModel = modelIndex;
      }
      //G_UpdateScriptMoverAttachedModels(ent);
      //G_UpdateVehicleAttachedModels(ent);
      for ( i = 0; i < 19; ++i )
      {
        modelIndex = ent->attachModelNames[i];
        if ( !ent->attachModelNames[i] )
        {
          break;
        }
        assert(numModels < DOBJ_MAX_SUBMODELS);
        dobjModels[numModels].model = G_GetModel(modelIndex);

        assert(dobjModels[numModels].model);
        assert(ent->attachTagNames[i]);

        dobjModels[numModels].boneName = ent->attachTagNames[i];
        dobjModels[numModels++].ignoreCollision = (ent->attachIgnoreCollision & (1 << i)) != 0;
      }

      //numModels = DestructibleUpdate(ent, dobjModels, numModels);
      dobj = Com_ServerDObjCreate(dobjModels, numModels, /*tree*/ NULL, ent->s.number);
      DObjSetHidePartBits(dobj, ent->s.partBits);
      /*
      if ( ent->scr_vehicle )
      {
        G_UpdateVehicleTags(ent);
      }
      */
      G_UpdateTags(ent, 1);
    }
    else
    {
      G_UpdateTags(ent, 0);
    }
}