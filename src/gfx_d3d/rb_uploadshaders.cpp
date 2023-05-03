#include "r_material.h"
#include "r_local.h"
#include "rb_backend.h"

void R_HW_DrawTriangleList(const void* zerodata, int zerostride)
{
    r_dx.device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, zerodata, zerostride);
}

void R_HW_SetVertexDeclaration(D3DDevice* device, D3DVertexDeclaration *decl)
{
    device->SetVertexDeclaration(decl);
}

static void R_MaterialUpdatePrimitivesInternal(D3DVertexDeclaration *vertdecl, GfxCmdBufPrimState* primstate, const void* zerodata, int zerostride)
{
    if (primstate->vertexDecl != vertdecl)
    {
        R_HW_SetVertexDeclaration(primstate->device, vertdecl);
        primstate->vertexDecl = vertdecl;
    }
    R_HW_DrawTriangleList(zerodata, zerostride);
}


static bool R_MaterialUpdatePrimitives(MaterialVertexStreamRouting* routing, MaterialVertexDeclType _decltype, const void* zerodata, int zerostride)
{
    if ( routing->decl[_decltype] )
    {
      gfxCmdBufContext.state->prim.vertDeclType = _decltype;
      R_MaterialUpdatePrimitivesInternal(routing->decl[_decltype], &gfxCmdBufContext.state->prim, zerodata, zerostride);
      return true;
    }
    return false;
}


void sub_619950(MaterialShaderArgument *arg)
{
  struct GfxImage *image;

  if ( arg->type == 2 )
  {
    R_SetSampler(gfxCmdBufContext, arg->dest, 10, rgp.blackImage);
    return;
  }
  if ( arg->type == 4 )
  {
    if ( arg->u.codeSampler == 3 )
    {
      image = rgp.black3dImage;
    }else if ( arg->u.codeSampler == 26 ){
      image = rgp.blackCubeImage;
    }else{
      image = rgp.blackImage;
    }
    R_SetSampler(gfxCmdBufContext, arg->dest, 10, image);
  }
}

#define STRIDESZ 48

int sub_6199C0(MaterialPass *passArray, MaterialVertexDeclType _decltype)
{
    int setlist = 0;
    int zerostride = STRIDESZ;
    char zerodata[3* STRIDESZ];

    MaterialVertexDeclaration *vertexDecl = passArray->vertexDecl;

    R_SetVertexShader(gfxCmdBufContext.state, passArray->vertexShader);
    R_SetPixelShader(gfxCmdBufContext.state, passArray->pixelShader);

    int count = passArray->perPrimArgCount + passArray->perObjArgCount + passArray->stableArgCount;
    for(int i = 0; i < count; ++i)
    {
        sub_619950(&passArray->args[i]);
    }
    memset(zerodata, 0, 3* zerostride);

    if(_decltype)
    {
        if ( vertexDecl->routing.decl[_decltype] )
        {
            D3DVertexDeclaration* d3dvertexdeclaration = NULL;
            gfxCmdBufContext.state->prim.vertDeclType = _decltype;
            if ( vertexDecl )
            {
                d3dvertexdeclaration = vertexDecl->routing.decl[_decltype];
            }
            R_MaterialUpdatePrimitivesInternal(d3dvertexdeclaration, &gfxCmdBufContext.state->prim, zerodata, zerostride);   
            setlist = 1;
        }
        gfxCmdBufContext.state->prim.vertDeclType = VERTDECL_GENERIC;
        return setlist;
    }
    setlist += (int)R_MaterialUpdatePrimitives(&vertexDecl->routing, VERTDECL_GENERIC, zerodata, zerostride);
    setlist += (int)R_MaterialUpdatePrimitives(&vertexDecl->routing, VERTDECL_PACKED, zerodata, zerostride);
    setlist += (int)R_MaterialUpdatePrimitives(&vertexDecl->routing, VERTDECL_WORLD, zerodata, zerostride);
    setlist += (int)R_MaterialUpdatePrimitives(&vertexDecl->routing, VERTDECL_STATICMODELCACHE, zerodata, zerostride);
    
    gfxCmdBufContext.state->prim.vertDeclType = VERTDECL_GENERIC;
    return setlist;
}


int sub_619C60(MaterialTechnique *technique, int a2)
{
  int count = 0;
  MaterialVertexDeclType vertexdeclType;

  if ( !strncmp(technique->name, "lm_", 3u) )
  {
    vertexdeclType = VERTDECL_WORLD;
  }
  else if ( !strncmp(technique->name, "lp_", 3u) || !strncmp(technique->name, "lprobe_", 7u) || !strncmp(technique->name, "effect_", 7u) )
  {
    vertexdeclType = VERTDECL_PACKED;
    if ( (unsigned int)(a2 - 14) <= 6 )
      vertexdeclType = VERTDECL_STATICMODELCACHE;
  }
  else
  {
    vertexdeclType = VERTDECL_GENERIC;
  }
  for(int i = 0; i < technique->passCount; ++i)
  {
    count += sub_6199C0(&technique->passArray[i], vertexdeclType);
  }
  return count;
}


#pragma pack(push, 1)
struct __align(4) MaterialUploadGlob
{
  MaterialTechniqueSet *techset[1024];
  int currentTechType;
  int uploadedcount;
  int uploadcount;
};
#pragma pack(pop)

MaterialUploadGlob mtlUploadGlob;


void Material_ClearShaderUploadList()
{
  mtlUploadGlob.uploadedcount = 0;
  mtlUploadGlob.uploadcount = 0;
  mtlUploadGlob.currentTechType = 0;
}
/*
void RB_UploadShaderStep()
{
  unsigned int k;
  MaterialTechniqueSet *techSet;
  MaterialTechnique *technique;

  if ( *(int*)((char*)backEndData + 0x11E6C4) && gfxDrawMethod.drawScene == 3 )
  {
    Material_ClearShaderUploadList();
    return;
  }
  for ( k = 0; mtlUploadGlob.uploadedcount != mtlUploadGlob.uploadcount && k < 1; ++mtlUploadGlob.uploadedcount )
  {
    techSet = mtlUploadGlob.techset[mtlUploadGlob.uploadedcount & 0x3FF];
    
    if(mtlUploadGlob.currentTechType == 0 && !techSet->unused[0] && !Material_WouldTechniqueSetBeOverwridden(&techSet->name))
    {
      techSet->unused[0] = 1;
    }else if(mtlUploadGlob.currentTechType == 0){
      continue;
    }
    while ( 1 )
    {
        technique = techSet->techniques[mtlUploadGlob.currentTechType];
        if ( technique )
        {
          if ( !(technique->flags & 0x8000) )
          {
            technique->flags |= 0x8000u;
            if ( technique->passCount && technique->passArray[0].pixelShader->prog.loadDef.rendertype == r_rendererInUse->current.integer )
            {
              k += sub_619C60(technique, mtlUploadGlob.currentTechType);
            }
          }
        }
        ++mtlUploadGlob.currentTechType;
        if ( mtlUploadGlob.currentTechType == 30 )
          break;
        if ( k >= 1 )
          return;
    }
    mtlUploadGlob.currentTechType = 0;
  }
}*/


void RB_UploadShaderStep() {
    MaterialTechniqueSet *techSet;
    MaterialTechnique *technique;


    if (backEndData->viewInfoCount && gfxDrawMethod.drawScene == 3) {
        mtlUploadGlob.uploadedcount = 0;
        mtlUploadGlob.uploadcount = 0;
        mtlUploadGlob.currentTechType = 0;
        return;
    }

    for (; mtlUploadGlob.uploadedcount != mtlUploadGlob.uploadcount; ++mtlUploadGlob.uploadedcount) {
        techSet = mtlUploadGlob.techset[mtlUploadGlob.uploadedcount & 0x3FF];

        if (techSet->uploaded || Material_WouldTechniqueSetBeOverridden(techSet)) {
            continue;
        }

        techSet->uploaded = true;
        for (; mtlUploadGlob.currentTechType < 30; ++mtlUploadGlob.currentTechType) {
            technique = techSet->techniques[mtlUploadGlob.currentTechType];
            if (technique) {
                if (!(technique->flags & 0x8000)) {
                    technique->flags |= 0x8000u;
                    if (technique->passCount && technique->passArray[0].pixelShader->prog.loadDef.rendertype == r_rendererInUse->current.integer) {
                        if (sub_619C60(technique, mtlUploadGlob.currentTechType)) {
                            return;
                        }
                    }
                }
            }
        }
        mtlUploadGlob.currentTechType = 0;
    }
}

void Material_UploadShaders(MaterialTechniqueSet *techset)
{
  if ( r_preloadShaders->current.enabled )
  {
    techset->uploaded = false;
    mtlUploadGlob.techset[mtlUploadGlob.uploadcount & 0x3FF] = techset;
    ++mtlUploadGlob.uploadcount;
  }
}