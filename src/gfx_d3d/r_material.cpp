#include "r_local.h"
#include "rb_backend.h"
#include <D3DX9Shader.h>
#include <stdint.h>
#include <string>
#include "../common/sys_thread.h"
#include "../common/qcommon.h"
#include "../database/db_shared.h"


#if 0
void Load_CreateMaterialPixelShader(GfxPixelShaderLoadDef *loadDef, MaterialPixelShader *mtlShader)
{
  HRESULT hr; // [esp+0h] [ebp-8h]
  int semaphore; // [esp+4h] [ebp-4h]

  assert(loadDef == &mtlShader->prog.loadDef);

  if ( r_loadForRenderer && r_loadForRenderer->current.enabled )
  {
    ProfLoad_Begin("Create pixel shader");
    if ( Sys_IsRenderThread() )
    {
      semaphore = R_AcquireDXDeviceOwnership(0);
      hr = dx.device->vfptr->CreatePixelShader(dx.device, loadDef->program, (IDirect3DPixelShader9 **)&mtlShader->prog);
      if ( hr < 0 )
      {
        g_hr = hr;
        mem = dx.device->vfptr->GetAvailableTextureMem(dx.device);
      }
      if ( semaphore )
      {
        R_ReleaseDXDeviceOwnership();
      }
    }
    else
    {
      RB_Resource_CreatePixelShader(loadDef->program, &mtlShader->prog.ps);
      RB_Resource_Flush();
    }
    DB_LoadedExternalData(10000);
    ProfLoad_End();
  }
  else
  {
    mtlShader->prog.ps = 0;
  }
}
#endif



void __cdecl Load_CreateMaterialPixelShader(GfxPixelShaderLoadDef *loadDef, MaterialPixelShader *mtlShader)
{


  if ( r_loadForRenderer->current.enabled && loadDef->rendertype == r_rendererInUse->current.integer )
  {

#ifndef _WIN32

    LPD3DXBUFFER shaderbuf;
    LPD3DXBUFFER errorMsgs;
    LPD3DXCONSTANTTABLE constantTable;

    std::string shadername(mtlShader->name);
    std::size_t findpos = shadername.find(".hlsl", 0, 5);

    if ( findpos != std::string::npos )
    {
        const std::string transshadername = shadername.substr(0, findpos) + ".ps";
 
        D3DXCompileShader(transshadername.c_str(), 0, 0, 0, 0, 0, 0, &shaderbuf, &errorMsgs, &constantTable);
        if ( shaderbuf )
        {
            r_dx.device->CreatePixelShader((const DWORD*)shaderbuf->GetBufferPointer(), &mtlShader->prog.ps);
        }

    }
#else
    D3DCALLNOERROR(r_dx.device->CreatePixelShader((const DWORD*)loadDef->program, &mtlShader->prog.ps));
#endif
  }
  else
  {
    mtlShader->prog.ps = 0;
  }
}



void __cdecl Load_CreateMaterialVertexShader(GfxVertexShaderLoadDef *loadDef, MaterialVertexShader *mtlShader)
{

  if ( r_loadForRenderer->current.enabled && loadDef->rendertype == r_rendererInUse->current.integer )
  {
#ifndef _WIN32
    LPD3DXBUFFER shaderbuf;
    LPD3DXBUFFER errorMsgs;
    LPD3DXCONSTANTTABLE constantTable;

    std::string shadername(mtlShader->name);
    std::size_t findpos = shadername.find(".hlsl", 0, 5);

    if ( findpos != std::string::npos )
    {
        const std::string transshadername = shadername.substr(0, findpos) + ".vs";
 
        D3DXCompileShader(transshadername.c_str(), 0, 0, 0, 0, 0, 0, &shaderbuf, &errorMsgs, &constantTable);
        if ( shaderbuf )
        {
            r_dx.device->CreateVertexShader((const DWORD*)shaderbuf->GetBufferPointer(), &mtlShader->prog.vs);
        }
    }
#else
    D3DCALLNOERROR(r_dx.device->CreateVertexShader((const DWORD*)loadDef->program, &mtlShader->prog.vs));
#endif
  }
  else
  {
    mtlShader->prog.vs = 0;
  }
}

/*
char *__ZZ29Material_TechniqueTypeForNamePKcE5C_439[] =
{
  "\"depth prepass\"",
  "\"build floatz\"",
  "\"build shadowmap depth\"",
  "\"build shadowmap color\"",
  "\"unlit\"",
  "\"emissive\"",
  "\"emissive shadow\"",
  "\"lit\"",
  "\"lit sun\"",
  "\"lit sun shadow\"",
  "\"lit spot\"",
  "\"lit spot shadow\"",
  "\"lit omni\"",
  "\"lit omni shadow\"",
  "\"lit instanced\"",
  "\"lit instanced sun\"",
  "\"lit instanced sun shadow\"",
  "\"lit instanced spot\"",
  "\"lit instanced spot shadow\"",
  "\"lit instanced omni\"",
  "\"lit instanced omni shadow\"",
  "\"light spot\"",
  "\"light omni\"",
  "\"light spot shadow\"",
  "\"fakelight normal\"",
  "\"fakelight view\"",
  "\"sunlight preview\"",
  "\"case texture\"",
  "\"solid wireframe\"",
  "\"shaded wireframe\"",
  "\"shadowcookie caster\"",
  "\"shadowcookie receiver\"",
  "\"debug bumpmap\"",
  "\"debug bumpmap instanced\""
};
*/

void Material_ReleasePassResources(MaterialPass *pass)
{
  unsigned int declIndex;

  if ( !r_loadForRenderer || !r_loadForRenderer->current.enabled )
  {
    return;
  }

  assert(pass->pixelShader);
  assert(pass->vertexShader);
  assert(pass->vertexDecl);

  if ( Sys_IsRenderThread() )
  {
    if ( pass->pixelShader->prog.ps )
    {
      D3DRELEASEBUFFER(pass->pixelShader->prog.ps);
    }
    if ( pass->vertexShader->prog.vs )
    {
      D3DRELEASEBUFFER(pass->vertexShader->prog.vs);
    }

    if ( pass->vertexDecl->isLoaded )
    {
      pass->vertexDecl->isLoaded = 0;
      for ( declIndex = 0; declIndex < ARRAY_COUNT(pass->vertexDecl->routing.decl); ++declIndex )
      {
        if ( pass->vertexDecl->routing.decl[declIndex] )
        {
          D3DRELEASEBUFFER(pass->vertexDecl->routing.decl[declIndex]);
        }
      }
    }
  }
  else
  {
    if ( pass->pixelShader->prog.ps )
    {
      RB_Resource_Release(pass->pixelShader->prog.ps);
      pass->pixelShader->prog.ps = 0;
    }
    if ( pass->vertexShader->prog.vs )
    {
      RB_Resource_Release(pass->vertexShader->prog.vs);
      pass->vertexShader->prog.vs = 0;
    }
    if ( pass->vertexDecl->isLoaded )
    {
      pass->vertexDecl->isLoaded = 0;
      for ( declIndex = 0; declIndex < ARRAY_COUNT(pass->vertexDecl->routing.decl); ++declIndex )
      {
        if ( pass->vertexDecl->routing.decl[declIndex] )
        {
          RB_Resource_Release(pass->vertexDecl->routing.decl[declIndex]);
          pass->vertexDecl->routing.decl[declIndex] = 0;
        }
      }
    }
  }

}


void Material_ReleaseTechniqueSetResources(MaterialTechniqueSet *techniqueSet)
{
  MaterialTechnique *technique;
  unsigned int techType;
  int passIndex;

  for ( techType = 0; techType < ARRAY_COUNT(techniqueSet->techniques); ++techType )
  {
    technique = techniqueSet->techniques[techType];
    if ( technique )
    {
      for ( passIndex = 0; passIndex < technique->passCount; ++passIndex )
      {
        Material_ReleasePassResources(&technique->passArray[passIndex]);
      }
    }
  }
}

void Material_ReleaseTechniqueSet(XAssetHeader header, void* arg)
{
  Material_ReleaseTechniqueSetResources(header.techniqueSet);
}

void Material_FreeTechniqueSet(XAssetHeader header, void* arg)
{
  Material_ReleaseTechniqueSetResources(header.techniqueSet);
}

#define STREAM_SRC_COUNT 9

struct stream_source_info_t
{
  uint8_t Stream;
  uint8_t Offset;
  uint8_t Type;
};

struct stream_dest_info_t
{
  uint8_t Usage;
  uint8_t UsageIndex;
};


extern stream_source_info_t s_streamSourceInfo[16][STREAM_SRC_COUNT];
extern stream_dest_info_t s_streamDestInfo[72];

IDirect3DVertexDeclaration9* Material_BuildVertexDecl(MaterialStreamRouting *routingData, int streamCount, stream_source_info_t *sourceTable)
{
  int elemIndexInsert;
  stream_source_info_t *sourceInfo;
  D3DVERTEXELEMENT9 declEnd;
  D3DVERTEXELEMENT9 elemTable[256];
  D3DVertexDeclaration *decl;
  stream_dest_info_t *destInfo;
  int elemIndex;

  decl = 0;
  declEnd.Stream = 255;
  declEnd.Offset = 0;
  declEnd.Type = 17;
  declEnd.Method = 0;
  declEnd.Usage = 0;
  declEnd.UsageIndex = 0;
  elemIndex = 0;
  while ( streamCount )
  {
    assert(routingData->source < STREAM_SRC_COUNT);

    sourceInfo = &sourceTable[routingData->source];
    if ( sourceInfo->Stream == 255 )
    {
      return 0;
    }
    destInfo = &s_streamDestInfo[routingData->dest];
    for ( elemIndexInsert = elemIndex; elemIndexInsert > 0 && elemTable[elemIndexInsert -1].Stream > (signed int)sourceInfo->Stream; --elemIndexInsert )
    {
      elemTable[elemIndexInsert] = elemTable[elemIndexInsert -1];
    }
    elemTable[elemIndexInsert].Stream = sourceInfo->Stream;
    elemTable[elemIndexInsert].Offset = sourceInfo->Offset;
    elemTable[elemIndexInsert].Type = sourceInfo->Type;
    elemTable[elemIndexInsert].Method = 0;
    elemTable[elemIndexInsert].Usage = destInfo->Usage;
    elemTable[elemIndexInsert].UsageIndex = destInfo->UsageIndex;
    ++elemIndex;
    ++routingData;
    --streamCount;
  }
  elemTable[elemIndex] = declEnd;
  if ( r_dx.device )
  {
    if ( Sys_IsRenderThread() )
    {
      D3DCALL(r_dx.device->CreateVertexDeclaration( elemTable, &decl ));
    }
    else
    {
      RB_Resource_CreateVertexDeclaration(elemTable, &decl);
      RB_Resource_Flush();
    }
    assert(decl);
  }
  return decl;
}


void Load_BuildVertexDecl(MaterialVertexDeclaration **mtlVertDecl)
{
  MaterialStreamRouting data[16];
  int vertDeclType;

  memcpy(data, (*mtlVertDecl)->routing.data, sizeof(data));
  for ( vertDeclType = 0; vertDeclType < VERTDECL_COUNT; ++vertDeclType )
  {
    if ( r_loadForRenderer && r_loadForRenderer->current.enabled )
    {
      (*mtlVertDecl)->routing.decl[vertDeclType] = Material_BuildVertexDecl(data, (*mtlVertDecl)->streamCount, s_streamSourceInfo[vertDeclType]);
    }
    else
    {
      (*mtlVertDecl)->routing.decl[vertDeclType] = 0;
    }
  }
  (*mtlVertDecl)->isLoaded = true;
}

void Material_ReloadPass(struct MaterialPass *pass)
{
  if ( !pass->pixelShader->prog.ps )
  {
    Load_CreateMaterialPixelShader(&pass->pixelShader->prog.loadDef, pass->pixelShader);
  }
  if ( !pass->vertexShader->prog.vs )
  {
    Load_CreateMaterialVertexShader(&pass->vertexShader->prog.loadDef, pass->vertexShader);
  }
  if ( !pass->vertexDecl->isLoaded ){
    Load_BuildVertexDecl(&pass->vertexDecl);
  }
}

void Material_ReloadPassArray(MaterialTechniqueSet *techniqueSet)
{
  MaterialTechnique *technique;
  unsigned int techType;
  int passIndex;

  for ( techType = 0; techType < ARRAY_COUNT(techniqueSet->techniques); ++techType )
  {
    technique = techniqueSet->techniques[techType];
    if ( technique )
    {
      for ( passIndex = 0; passIndex < technique->passCount; ++passIndex )
      {
        Material_ReloadPass(&technique->passArray[passIndex]);
      }
    }
  }
}

void Material_ReloadTechniqueSet(XAssetHeader header, void* arg)
{
  Material_ReloadPassArray(header.techniqueSet);
}

enum MaterialShaderType
{
  MTL_VERTEX_SHADER = 0x0,
  MTL_PIXEL_SHADER = 0x1
};

REGPARM(3) ID3DXBuffer *Material_CompileShader(char const*, MaterialShaderType, char const*, char const*)
{
  Com_Error(ERR_FATAL, "Needs implementation for Material_CompileShader\n");
  return NULL;
}

struct materialGlobals_s
{
  int techniqueSetCount;
  MaterialTechniqueSet *techniqueSetHashTable[1024];
};

extern materialGlobals_s materialGlobals;

struct BuiltInMaterialTable
{
  const char *name;
  Material **material;
};

BuiltInMaterialTable s_builtInMaterials[] =
{
  { "$default", &rgp.defaultMaterial },
  { "white", &rgp.whiteMaterial },
  { "$additive", &rgp.additiveMaterial },
  { "$glare_blind", &rgp.glareBlindMaterial },
  { "$point", &rgp.pointMaterial },
  { "$line", &rgp.lineMaterial },
  { "$line_nodepth", &rgp.lineMaterialNoDepth },
  { "clear_alpha_stencil", &rgp.clearAlphaStencilMaterial },
  { "depthprepass", &rgp.depthPrepassMaterial },
  { "shadowclear", &rgp.shadowClearMaterial },
  { "shadowcookieoverlay", &rgp.shadowCookieOverlayMaterial },
  { "shadowcookieblur", &rgp.shadowCookieBlurMaterial },
  { "shadowcaster", &rgp.shadowCasterMaterial },
  { "shadowoverlay", &rgp.shadowOverlayMaterial },
  { "stencilshadow", &rgp.stencilShadowMaterial },
  { "stencildisplay", &rgp.stencilDisplayMaterial },
  { "floatz_display", &rgp.floatZDisplayMaterial },
  { "shellshock", &rgp.shellShockBlurredMaterial },
  { "shellshock_flashed", &rgp.shellShockFlashedMaterial },
  { "color_channel_mixer", &rgp.colorChannelMixerMaterial },
  { "frame_color_debug", &rgp.frameColorDebugMaterial },
  { "frame_alpha_debug", &rgp.frameAlphaDebugMaterial },
  { "feedbackblend", &rgp.feedbackBlendMaterial },
  { "feedbackfilmblend", &rgp.feedbackFilmBlendMaterial },
  { "feedbackreplace", &rgp.feedbackReplaceMaterial },
  { "cinematic", &rgp.cinematicMaterial },
  { "dof_downsample", &rgp.dofDownsampleMaterial },
  { "dof_near_coc", &rgp.dofNearCocMaterial },
  { "small_blur", &rgp.smallBlurMaterial },
  { "postfx_dof", &rgp.postFxDofMaterial },
  { "postfx_dof_color", &rgp.postFxDofColorMaterial },
  { "postfx_color", &rgp.postFxColorMaterial },
  { "postfx", &rgp.postFxMaterial },
  { "glow_consistent_setup", &rgp.glowConsistentSetupMaterial },
  { "glow_apply_bloom", &rgp.glowApplyBloomMaterial },

  { "filter_symmetric_1", &rgp.symmetricFilterMaterial[0] },
  { "filter_symmetric_2", &rgp.symmetricFilterMaterial[1] },
  { "filter_symmetric_3", &rgp.symmetricFilterMaterial[2] },
  { "filter_symmetric_4", &rgp.symmetricFilterMaterial[3] },
  { "filter_symmetric_5", &rgp.symmetricFilterMaterial[4] },
  { "filter_symmetric_6", &rgp.symmetricFilterMaterial[5] },
  { "filter_symmetric_7", &rgp.symmetricFilterMaterial[6] },
  { "filter_symmetric_8", &rgp.symmetricFilterMaterial[7] },

  { "pixel_cost_add_depth_always", &rgp.pixelCostAddDepthAlwaysMaterial },
  { "pixel_cost_add_depth_disable", &rgp.pixelCostAddDepthDisableMaterial },
  { "pixel_cost_add_depth_equal", &rgp.pixelCostAddDepthEqualMaterial },
  { "pixel_cost_add_depth_less", &rgp.pixelCostAddDepthLessMaterial },
  { "pixel_cost_add_depthwrite", &rgp.pixelCostAddDepthWriteMaterial },
  { "pixel_cost_add_nodepthwrite", &rgp.pixelCostAddNoDepthWriteMaterial },
  { "pixel_cost_color_code", &rgp.pixelCostColorCodeMaterial }

};

void Material_LoadBuiltIn(BuiltInMaterialTable *mtlTable, int mtlTableCount)
{
    int builtInMtlIndex;

    for ( builtInMtlIndex = 0; builtInMtlIndex < mtlTableCount; ++builtInMtlIndex )
    {
      assert(!*mtlTable[builtInMtlIndex].material);

      *mtlTable[builtInMtlIndex].material = Material_Register(mtlTable[builtInMtlIndex].name, 0);
      if ( !*mtlTable[builtInMtlIndex].material )
      {
          Com_Error(ERR_FATAL, "Could not find build-in material '%s'", mtlTable[builtInMtlIndex].name);
      }
      //rgp.dummyMaterial = 0;
    }
}

void Material_Init()
{
    if ( !useFastFile->current.enabled )
    {
        memset((char *)&materialGlobals, 0, sizeof(materialGlobals));
        Material_PreLoadAllShaderText();
    }
    Material_LoadBuiltIn(s_builtInMaterials, ARRAY_COUNT(s_builtInMaterials));
    //Material_Register("statmon_warning_tris", 1);
}
