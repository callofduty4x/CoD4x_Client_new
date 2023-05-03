#include "r_local.h"
#include "../common/sys_thread.h"

//Probably needed to support ShaderModel2 translated from ShaderModel3 material-techset names

struct __align(4) GfxMtlOverrrideGlob
{
  bool a;
  bool dirty;
  int mask;
  int value;
};


#pragma pack(push, 4)
struct GfxMtlFeatureMap
{
  const char *name;
  unsigned int mask;
  unsigned int value;
  bool8 valueRequired;
};
#pragma pack(pop)

GfxMtlFeatureMap s_materialFeatures[] =
{
  { "s0", 4u, 0u, false },
  { "s1", 4u, 0u, false },
  { "s2", 4u, 0u, false },
  { "s3", 4u, 0u, false },
  { "s4", 4u, 0u, false },
  { "d0", 8u, 0u, false },
  { "d1", 8u, 0u, false },
  { "d2", 8u, 0u, false },
  { "d3", 8u, 0u, false },
  { "d4", 8u, 0u, false },
  { "n0", 16u, 0u, false },
  { "n1", 16u, 0u, false },
  { "n2", 16u, 0u, false },
  { "n3", 16u, 0u, false },
  { "n4", 16u, 0u, false },
  { "zfeather", 1u, 0u, false },
  { "outdoor", 2u, 0u, false },
  { "sm", 384u, 128u, true },
  { "hsm", 384u, 256u, true },
  { "twk", 32u, 0u, false }
};



GfxMtlOverrrideGlob mtlOverrideGlob;

int Material_ExtendTechsetname(char *remapName, int remapOffset, const char *extendtok, int extendtoklen, bool hasunderscore)
{
  if ( hasunderscore )
  {
    remapName[remapOffset++] = '_';
  }
  if ( (unsigned int)(remapOffset + extendtoklen) >= 64 )
  {
    Com_Error(ERR_FATAL, "Can't extend techset name '%s' with '%s'; would exceed %i chars", remapName, extendtok, 63);
  }
  memcpy(&remapName[remapOffset], (void *)extendtok, extendtoklen + 1);
  return remapOffset + extendtoklen;
}


int Material_NextTechniqueSetNameToken(const char **parse, char *token)
{
    int toklen;

    toklen = 0;
    while ( **parse )
    {
        token[toklen] = **parse;
        if ( **parse == '_' )
        {
            ++*parse;
            break;
        }
        if ( toklen && isdigit(token[toklen - 1]) && !isdigit(token[toklen]) ){
            break;
        }
        ++*parse;
        ++toklen;
    }

    token[toklen] = 0;
    return toklen;
}





GfxMtlFeatureMap *Material_GetFeatureForToken(const char *a1, GfxMtlFeatureMap *featureMap, unsigned int featureCount)
{
  unsigned int i;

  for(i = 0; i < featureCount; ++i)
  {
    if(strcmp(a1, featureMap[i].name))
    {
        return &featureMap[i];
    }
  }
  return 0;
}


void Material_RemapTechniqueSetName(const char *techSetName, char *remapName, unsigned int remapMask, unsigned int remapValue, GfxMtlFeatureMap *featureMap, unsigned int featureCount)
{
    GfxMtlFeatureMap *featureTok;
    signed int prefixlen;
    bool hasunderscore;
    int toklen;
    const char *parse;
    char token[64];

    prefixlen = 0;
    remapName[0] = 0;
    parse = techSetName;
    if ( r_rendererInUse->current.integer == 0 )
    {
        strcat(remapName, "sm2/");
        prefixlen = 4;
    }

    if ( !strncmp(techSetName, "sm2/", 4u) )
    {
        parse += 4;
    }


    hasunderscore = prefixlen && parse[-1] == '_';
    toklen = Material_NextTechniqueSetNameToken(&parse, token);


    while ( toklen )
    {

        featureTok = Material_GetFeatureForToken(token, featureMap, featureCount);
        if ( featureTok && (featureTok->mask & remapMask) )
        {
            if ( featureTok->value && remapValue & featureTok->mask )
            {
                unsigned int i;
                for (i = 0 ; (featureMap[i].mask != featureTok->mask || featureMap[i].value != (remapValue & featureTok->mask)) && i < featureCount; ++i );

                prefixlen = Material_ExtendTechsetname(remapName, prefixlen, featureMap[i].name, strlen(featureMap[i].name), hasunderscore);
            }
        }
        else
        {
            prefixlen = Material_ExtendTechsetname(remapName, prefixlen, token, toklen, hasunderscore);
        }

        hasunderscore = prefixlen && parse[-1] == '_';
        toklen = Material_NextTechniqueSetNameToken(&parse, token);
    }
}


void Material_RegisterOverriddenTechniqueSets_r(const char *remapName, int prefixlen, const char *techSetName, unsigned int remapMask, unsigned int remapValue)
{
  int toklen;
  GfxMtlFeatureMap *featureTok;
  bool hasunderscore;
  char token[64];
  char cpRemapName[256];
  char cp2RemapName[256];


  const char *parse = techSetName;

  hasunderscore = prefixlen && parse[-1] == '_';
  toklen = Material_NextTechniqueSetNameToken(&techSetName, token);

  strcpy(cpRemapName, remapName);

  while ( toklen )
  {
    featureTok = Material_GetFeatureForToken(token, s_materialFeatures, ARRAY_COUNT(s_materialFeatures));
    if ( featureTok )
    {
      remapMask &= ~featureTok->mask;
      if ( featureTok->value == 0 )
      {
        if ( featureTok->mask & remapMask )
        {
          Material_RegisterOverriddenTechniqueSets_r(cpRemapName, prefixlen, techSetName, ~featureTok->mask & remapMask, remapValue);
          remapValue = featureTok->mask | remapValue;
        }
        if ( featureTok->mask & remapValue )
        {
          prefixlen = Material_ExtendTechsetname(cpRemapName, prefixlen, token, toklen, hasunderscore);
        }
      }
      else
      {
        unsigned int i;
        for(i = 0; i < ARRAY_COUNT(s_materialFeatures); ++i)
        {
            GfxMtlFeatureMap *fm = &s_materialFeatures[i];
            if ( fm->mask == featureTok->mask )
            {
                if ( featureTok->mask & remapMask )
                {
                    strcpy(cp2RemapName, cpRemapName);
                    
                    int newlen = Material_ExtendTechsetname(cp2RemapName, prefixlen, fm->name, strlen(fm->name), hasunderscore);
                    Material_RegisterOverriddenTechniqueSets_r(cp2RemapName, newlen, techSetName, remapMask, remapValue | fm->value);
                }
                else if ( fm->value == (remapValue & fm->mask) )
                {
                    toklen = strlen(fm->name);
                    prefixlen = Material_ExtendTechsetname(cpRemapName, prefixlen, fm->name, toklen, hasunderscore);
                    break;
                }
            }
        }
        if(i == ARRAY_COUNT(s_materialFeatures))
        {
            if ( (featureTok->mask & remapMask) && featureTok->valueRequired )
            {
                return;
            }
        }
      }
    }
    else
    {
      prefixlen = Material_ExtendTechsetname(cpRemapName, prefixlen, token, toklen, hasunderscore);
    }

    hasunderscore = prefixlen && parse[-1] == '_';
    toklen = Material_NextTechniqueSetNameToken(&techSetName, token);
  }
  Material_RegisterTechniqueSet(cpRemapName);
}


void Material_SetRemapFlags(int *flags, int *remapValue)
{
  *flags = 0;
  *remapValue = 0;
  if ( !r_detail->current.enabled )
    *flags = 8;
  if ( !r_specular->current.enabled )
    *flags |= 4u;
  if ( !r_normal->current.enabled )
    *flags |= 0x10u;
  if ( !r_zFeather->current.enabled )
    *flags |= 1u;
  if ( !r_outdoor->current.enabled )
    *flags |= 2u;

  *flags |= 0x180u;

  *remapValue = gfxMetrics.hasHardwareShadowmap != false ? 256 : 128;
  if ( r_envMapOverride->current.enabled )
  {
    *flags |= 0x20;
  }
}

bool Material_WouldTechniqueSetBeOverridden(const MaterialTechniqueSet *techset)
{
  int flags;
  int remapValue;
  char remapName[256];

  Material_SetRemapFlags(&flags, &remapValue);
  Material_RemapTechniqueSetName(techset->name, remapName, flags, remapValue, s_materialFeatures, ARRAY_COUNT(s_materialFeatures));
  
  return strcmp(techset->name, remapName) != 0;
}

void Material_RemapTechniqueSet(MaterialTechniqueSet *techniqueSet)
{
  char remapName[256];

  Material_RemapTechniqueSetName(techniqueSet->name, remapName, mtlOverrideGlob.mask, mtlOverrideGlob.value, s_materialFeatures, ARRAY_COUNT(s_materialFeatures));
  if ( !strcmp(techniqueSet->name, remapName))
  {
    techniqueSet->remappedTechniqueSet = techniqueSet;
  }else{
    techniqueSet->remappedTechniqueSet = Material_FindTechniqueSet(remapName, MtlTECHNOTFOUND_NONE);
    if(techniqueSet->remappedTechniqueSet == NULL)
    {
        techniqueSet->remappedTechniqueSet = techniqueSet;
    }
  }
}

void Material_RegisterOverriddenTechniqueSets(const char *a1)
{
  char techsetstring[264];

  if ( !mtlOverrideGlob.a )
  {
    mtlOverrideGlob.a = 1;
    techsetstring[0] = 0;
    Material_RegisterOverriddenTechniqueSets_r(techsetstring, 0, a1, 0xFFFFFFFF, 0);
    mtlOverrideGlob.a = 0;
  }
}

void Material_OverrideTechniqueSets(void)
{
  int mask, remapValue;

  if(Sys_IsRenderThread())
  {
//      return;
  }

  Material_SetRemapFlags(&mask, &remapValue);



  if ( mtlOverrideGlob.dirty || mtlOverrideGlob.mask != mask || remapValue != mtlOverrideGlob.value )
  {
    mtlOverrideGlob.dirty = false;
    mtlOverrideGlob.mask = mask;
    mtlOverrideGlob.value = remapValue;
    rgp.needSortMaterials = true;
    R_SyncRenderThread();
    Material_ForEachTechniqueSet(Material_RemapTechniqueSet);
  }
}

void Material_OriginalRemapTechniqueSet(MaterialTechniqueSet *techset)
{
    char sm2name[64];

    if ( r_rendererInUse->current.integer || !strncmp(techset->name, "sm2/", 4u) )
    {
        techset->remappedTechniqueSet = techset;
        return;
    }
    snprintf(sm2name, sizeof(sm2name), "sm2/%s", techset->name);
    techset->remappedTechniqueSet = Material_FindTechniqueSet(sm2name, MtlTECHNOTFOUND_ONE);
}

void Material_DirtyTechniqueSetOverrides(void)
{
  mtlOverrideGlob.dirty = true;
}

