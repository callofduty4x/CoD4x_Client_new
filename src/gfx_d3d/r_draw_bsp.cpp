#include "r_local.h"
#include "gfx_world.h"
#include "r_draw_cmdbuf.h"
#include "rb_backend.h"
#include "r_image.h"

int g_layerDataStride[] = { 0, 0, 0, 8, 12, 16, 20, 24, 24, 28, 32, 32, 36, 40, 0, 0 };



void R_SetStreamsForBspSurface(GfxCmdBufPrimState *state, const srfTriangles_t *tris)
{
  int layerDataStride;
  GfxWorld *world = rgp.world;


  layerDataStride = g_layerDataStride[state->vertDeclType];
  if ( layerDataStride )
  {
    R_SetDoubleStreamSource(state, world->vd.worldVb, 44 * tris->firstVertex, 44, world->vld.layerVb, tris->vertexLayerData, layerDataStride);
    return;
  }
  R_SetStreamSource(state, world->vd.worldVb, 44 * tris->firstVertex, 44);
}

bool R_ReadBspPreTessDrawSurfs(GfxReadCmdBuf *cmdBuf, GfxBspPreTessDrawSurf **list, unsigned int *count, unsigned int *baseIndex)
{
    *count = R_ReadPrimDrawSurfInt(cmdBuf);
    if ( !*count )
    {
        return false;
    }
    *baseIndex = R_ReadPrimDrawSurfInt(cmdBuf);
    *list = (GfxBspPreTessDrawSurf *)R_ReadPrimDrawSurfData(cmdBuf, *count);
    return true;
}

bool R_ReadBspDrawSurfs(GfxReadCmdBuf *primDrawSurfPos, const uint16_t **list, unsigned int *count)
{
  *count = R_ReadPrimDrawSurfInt(primDrawSurfPos);
  if ( !*count )
  {
    return false;
  }
  *list = (const uint16_t*)R_ReadPrimDrawSurfData(primDrawSurfPos, (*count +1) / 2);
  return 1;
}

void R_DrawPreTessTris(GfxCmdBufPrimState *state, srfTriangles_t *tris, unsigned int baseIndex, unsigned int triCount)
{
    GfxDrawPrimArgs args;

    R_SetStreamsForBspSurface(state, tris);
    args.vertexCount = tris->vertexCount;
    args.triCount = triCount;
    args.baseIndex = baseIndex;
    R_DrawIndexedPrimitive(state, &args);
    
    /*
    state->frameStats.geoIndexCount += 3 * triCount;
    assert(state->primStats);
    state->primStats->dynamicIndexCount += 3 * triCount;
    */
}


void R_DrawBspDrawSurfsLitPreTess(const unsigned int *primDrawSurfPos, GfxCmdBufContext context)
{
    unsigned int baseIndex;
    unsigned int surfIndex;
    GfxReadCmdBuf cmdBuf;
    srfTriangles_t *tris;
    GfxBspPreTessDrawSurf *list;
    unsigned int reflectionProbeIndex;
    GfxSurface *bspSurf;
    unsigned int index;
    unsigned int lightmapIndex;
    unsigned int count;

    if ( sc_enable->current.enabled )
    {
      context.source->input.codeImages[(unsigned int)CODEIMAGES::shadowCookieSampler] = gfxRenderTargets[R_RENDERTARGET_DYNAMICSHADOWS].image;
    }
    else
    {
      context.source->input.codeImages[(unsigned int)CODEIMAGES::shadowCookieSampler] = rgp.whiteImage;
    }

    cmdBuf.primDrawSurfPos = primDrawSurfPos;
    while ( R_ReadBspPreTessDrawSurfs(&cmdBuf, &list, &count, &baseIndex) )
    {
        reflectionProbeIndex = 255;
        lightmapIndex = 31;
        for ( index = 0; index < count; ++index )
        {
            surfIndex = list[index].baseSurfIndex;
            assert(surfIndex < rgp.world->surfaceCount);

            bspSurf = &rgp.world->dpvs.surfaces[surfIndex];
            tris = &bspSurf->tris;
            
            if ( reflectionProbeIndex != bspSurf->reflectionProbeIndex || lightmapIndex != bspSurf->lightmapIndex )
            {
                reflectionProbeIndex = bspSurf->reflectionProbeIndex;
                lightmapIndex = bspSurf->lightmapIndex;
                R_SetReflectionProbe(context, reflectionProbeIndex);
                R_SetLightmap(context, lightmapIndex);
                R_SetupPassPerObjectArgs(context);
                R_SetupPassPerPrimArgs(context);
            }
            
            R_DrawPreTessTris(&context.state->prim, tris, baseIndex, list[index].totalTriCount);
            baseIndex += 3 * list[index].totalTriCount;
        }
    }
}


void R_DrawBspDrawSurfsPreTess(const unsigned int *primDrawSurfPos, GfxCmdBufContext context)
{
    unsigned int baseIndex;
    unsigned int surfIndex;
    GfxReadCmdBuf cmdBuf;
    srfTriangles_t *tris;
    srfTriangles_t *prevTris;
    GfxBspPreTessDrawSurf *list;
    unsigned int triCount;
    GfxSurface *bspSurf;
    unsigned int index;
    unsigned int count;
    int baseVertex;

    R_SetupPassPerObjectArgs(context);
    R_SetupPassPerPrimArgs(context);
    cmdBuf.primDrawSurfPos = primDrawSurfPos;
    while ( R_ReadBspPreTessDrawSurfs(&cmdBuf, &list, &count, &baseIndex) )
    {
        prevTris = 0;
        triCount = 0;
        baseVertex = -1;
        for ( index = 0; index < count; ++index )
        {
            surfIndex = list[index].baseSurfIndex;
            assert(surfIndex < rgp.world->surfaceCount);

            bspSurf = &rgp.world->dpvs.surfaces[surfIndex];
            tris = &bspSurf->tris;
            if ( baseVertex != (signed)bspSurf->tris.firstVertex )
            {
                if ( triCount )
                {
                    R_DrawPreTessTris(&context.state->prim, prevTris, baseIndex, triCount);
                    baseIndex += 3 * triCount;
                    triCount = 0;
                }
                prevTris = tris;
                baseVertex = tris->firstVertex;
            }
            triCount += list[index].totalTriCount;
        }
        R_DrawPreTessTris(&context.state->prim, prevTris, baseIndex, triCount);
    }
}


void R_DrawBspTris(GfxCmdBufPrimState *state, srfTriangles_t *tris, unsigned int triCount)
{
  GfxDrawPrimArgs args;

  args.vertexCount = tris->vertexCount;
  args.triCount = triCount;
  args.baseIndex = R_SetIndexData(state, &rgp.world->indices[tris->baseIndex], triCount);
  R_DrawIndexedPrimitive(state, &args);
  /*
  if ( state->primStats )
  {
    if ( !state->primStats && !(unsigned __int8)Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_draw_bsp.cpp", 367, 0, "%s", "state->primStats") )
    {
      __debugbreak();
    }
    state->frameStats.geoIndexCount += 3 * triCount;
    state->primStats->dynamicIndexCount += 3 * triCount;
  }
  */
}



struct GfxTrianglesDrawStream
{
  unsigned int reflectionProbeCount;
  unsigned int lightmapCount;
  const GfxTexture *reflectionProbeTextures;
  const GfxTexture *lightmapPrimaryTextures;
  const GfxTexture *lightmapSecondaryTextures;
  const GfxTexture *whiteTexture;
  const unsigned int *primDrawSurfPos;
  const GfxTexture *reflectionProbeTexture;
  const GfxTexture *lightmapPrimaryTexture;
  const GfxTexture *lightmapSecondaryTexture;
  unsigned int customSamplerFlags;
  int hasSunDirChanged;
};



void R_DrawTrianglesLit(GfxTrianglesDrawStream *drawStream, GfxCmdBufPrimState *primState, GfxCmdBufPrimState *prepassPrimState)
{
  GfxSurface *bspSurf;
  int baseIndex;
  unsigned int surfIndex;
  srfTriangles_t *prevTris;
  unsigned int lightmapSecondaryFlag;
  unsigned int reflectionProbeFlag;
  const GfxTexture *lightmapPrimaryTexture;
  const uint16_t *list;
  int triCount;
  unsigned int reflectionProbeIndex;
  const GfxTexture *reflectionProbeTexture;
  const GfxTexture *newLightmapPrimaryTexture;
  const GfxTexture *reflectionProbeTextures;
  unsigned int index;
  unsigned int lightmapIndex;
  const GfxTexture *lightmapSecondaryTexture;
  const GfxTexture *newLightmapSecondaryTexture;
  D3DDevice *device;
  unsigned int lightmapPrimaryFlag;
  GfxImage *overrideImage;
  unsigned int count;
  int baseVertex;
  const GfxTexture *newReflectionProbeTexture;
  int hasSunDirChanged;
  bool override;
//  unsigned int lightmapSecondaryFlagB;
//  GfxTexture *newLightmapSecondaryTextureB;
//  GfxTexture *lightmapSecondaryTextureB;
//  GfxTexture *conflictTex;



  reflectionProbeIndex = 255;
  lightmapIndex = 31;
  prevTris = 0;
  triCount = 0;
  baseVertex = -1;
  baseIndex = 0;
  reflectionProbeTexture = drawStream->reflectionProbeTexture;
  lightmapPrimaryTexture = drawStream->lightmapPrimaryTexture;
  lightmapSecondaryTexture = drawStream->lightmapSecondaryTexture;
  //lightmapSecondaryTextureB = drawStream->lightmapSecondaryTextureB;
  reflectionProbeFlag = drawStream->customSamplerFlags & 1;
  lightmapPrimaryFlag = drawStream->customSamplerFlags & 2;
  lightmapSecondaryFlag = drawStream->customSamplerFlags & 4;
  //lightmapSecondaryFlagB = drawStream->customSamplerFlags & 8;
  reflectionProbeTextures = rgp.world->reflectionProbeTextures;
  hasSunDirChanged = drawStream->hasSunDirChanged;
  overrideImage = 0;
  override = r_lightMap->current.integer != 1;
  if ( override )
  {
    overrideImage = R_OverrideGrayscaleImage(r_lightMap);
  }
/*
  conflictTex = NULL;
  if ( r_lightConflicts->current.enabled )
  {
    if ( rg.frontEndFrameCount & 4 )
    {
      conflictTex = &rgp.blackImage->texture;
    }
    else
    {
      conflictTex = &rgp.whiteImage->texture;
    }
  }
*/
  device = primState->device;
  while ( R_ReadBspDrawSurfs((GfxReadCmdBuf*)&drawStream->primDrawSurfPos, &list, &count) )
  {
    for ( index = 0; index < count; ++index )
    {
      surfIndex = list[index];
      assert(surfIndex < rgp.world->surfaceCount);

      bspSurf = &rgp.world->dpvs.surfaces[surfIndex];

//      __buildin_prefetch(&rgp.world->dpvs.surfaces[list[index + 1]].lightmapIndex);

      
      if ( /*r_lightConflicts->current.enabled || */ reflectionProbeIndex != bspSurf->reflectionProbeIndex || lightmapIndex != bspSurf->lightmapIndex )
      {
        if ( prevTris )
        {
          R_DrawBspTris(primState, prevTris, triCount);
        }
        prevTris = &bspSurf->tris;
        triCount = 0;
        baseIndex = bspSurf->tris.baseIndex;
        if ( baseVertex != (signed)bspSurf->tris.firstVertex )
        {
          baseVertex = bspSurf->tris.firstVertex;
          R_SetStreamsForBspSurface(primState, &bspSurf->tris);
        }
        
        reflectionProbeIndex = bspSurf->reflectionProbeIndex;
        lightmapIndex = bspSurf->lightmapIndex;
        
        if ( reflectionProbeFlag )
        {
          assert(reflectionProbeIndex < rgp.world->reflectionProbeCount);

          newReflectionProbeTexture = &reflectionProbeTextures[reflectionProbeIndex];
          if ( reflectionProbeTexture != newReflectionProbeTexture )
          {
            reflectionProbeTexture = newReflectionProbeTexture;
            R_HW_SetSamplerTexture(device, 1, newReflectionProbeTexture);
          }
        }

        if ( lightmapIndex == 31 )
        {
          assert(!lightmapPrimaryFlag);
          assert(!lightmapSecondaryFlag);
        }
        else
        {
          assert ( lightmapIndex < rgp.world->lightmapCount );
          if ( lightmapPrimaryFlag )
          {
            if ( overrideImage )
            {
              newLightmapPrimaryTexture = &overrideImage->texture;
            }
            else
            {
              if ( hasSunDirChanged )
              {
                newLightmapPrimaryTexture = drawStream->whiteTexture;
              }
              else
              {
                //newLightmapPrimaryTexture = &g_worldDraw->lightmapPrimaryTextures[lightmapIndex];
                newLightmapPrimaryTexture = &drawStream->lightmapPrimaryTextures[lightmapIndex];
              }
            }
            /*
            if ( conflictTex )
            {
              if ( bspSurf->flags & 2 )
              {
                newLightmapPrimaryTexture = conflictTex;
              }
            }
            */
            if ( lightmapPrimaryTexture != newLightmapPrimaryTexture )
            {
              lightmapPrimaryTexture = newLightmapPrimaryTexture;
              R_HW_SetSamplerTexture(device, 2, newLightmapPrimaryTexture);
            }
          }
          if ( lightmapSecondaryFlag )
          {
            if ( overrideImage )
            {
              //R_OverrideGrayscaleImage(r_lightMap);
              newLightmapSecondaryTexture = &overrideImage->texture;
              //overrideImage = rgp.g16r16Image;
              //newLightmapSecondaryTextureB = &rgp.g16r16Image->texture;
            }
            else
            {
              newLightmapSecondaryTexture = &drawStream->lightmapSecondaryTextures[lightmapIndex];
              //newLightmapSecondaryTexture = &g_worldDraw->lightmapSecondaryTextures[lightmapIndex];
              //newLightmapSecondaryTextureB = &g_worldDraw->lightmapSecondaryTexturesB[lightmapIndex];
            }
            /*
            if ( conflictTex )
            {
              if ( bspSurf->flags & 2 )
              {
                newLightmapSecondaryTexture = conflictTex;
                newLightmapSecondaryTextureB = conflictTex;
              }
            }
            */
            if ( lightmapSecondaryTexture != newLightmapSecondaryTexture )
            {
              lightmapSecondaryTexture = newLightmapSecondaryTexture;
              R_HW_SetSamplerTexture(device, 3, newLightmapSecondaryTexture);
            }
            /*
            if ( lightmapSecondaryTextureB != newLightmapSecondaryTextureB )
            {
              lightmapSecondaryTextureB = newLightmapSecondaryTextureB;
              R_HW_SetSamplerTexture(device, 0xEu, newLightmapSecondaryTextureB);
            }
            */
          }
        }
      }
      else if ( baseVertex != (signed)bspSurf->tris.firstVertex || baseIndex + 3 * triCount != bspSurf->tris.baseIndex )
      {
        if ( prevTris )
        {
          R_DrawBspTris(primState, prevTris, triCount);
        }
        prevTris = &bspSurf->tris;
        triCount = 0;
        baseIndex = bspSurf->tris.baseIndex;
        if ( baseVertex != (signed)bspSurf->tris.firstVertex )
        {
          baseVertex = bspSurf->tris.firstVertex;
          R_SetStreamsForBspSurface(primState, &bspSurf->tris);
        }
      }
      triCount += bspSurf->tris.triCount;
      assert(!prepassPrimState);
    }
  }
  if ( prevTris )
  {
    R_DrawBspTris(primState, prevTris, triCount);
  }
  drawStream->reflectionProbeTexture = reflectionProbeTexture;
  drawStream->lightmapPrimaryTexture = lightmapPrimaryTexture;
  drawStream->lightmapSecondaryTexture = lightmapSecondaryTexture;
  //drawStream->lightmapSecondaryTextureB = lightmapSecondaryTextureB;
}


void R_DrawBspDrawSurfsLit(const unsigned int *primDrawSurfPos, GfxCmdBufContext context, GfxCmdBufContext prepassContext, GfxDrawSurfListInfo const* list)
{
  MaterialPass *pass;
  GfxTrianglesDrawStream drawStream;

  pass = context.state->pass;
  uint8_t customSamplerFlags = pass->customSamplerFlags;
  if ( customSamplerFlags & 1 )
  {
    R_SetSamplerState(context.state, 1, 114);
  }
  if ( customSamplerFlags & 2 )
  {
    R_SetSamplerState(context.state, 2, 98);
  }
  if ( customSamplerFlags & 4 )
  {
    R_SetSamplerState(context.state, 3, 98);
  }

  drawStream.reflectionProbeTexture = context.state->samplerTexture[1];
  drawStream.lightmapPrimaryTexture = context.state->samplerTexture[2];
  drawStream.lightmapSecondaryTexture = context.state->samplerTexture[3];
  drawStream.reflectionProbeCount = rgp.world->reflectionProbeCount;
  drawStream.lightmapCount = rgp.world->lightmapCount;
  drawStream.reflectionProbeTextures = rgp.world->reflectionProbeTextures;
  drawStream.lightmapPrimaryTextures = rgp.world->lightmapPrimaryTextures;
  drawStream.lightmapSecondaryTextures = rgp.world->lightmapSecondaryTextures;
  drawStream.whiteTexture = &rgp.whiteImage->texture;
  drawStream.primDrawSurfPos = primDrawSurfPos;
  drawStream.customSamplerFlags = customSamplerFlags;
  drawStream.hasSunDirChanged = context.source->input.data->prim.hasSunDirChanged;

  if ( prepassContext.state )
  {
    R_DrawTrianglesLit(&drawStream, &context.state->prim, &prepassContext.state->prim);
  }
  else
  {
    R_DrawTrianglesLit(&drawStream, &context.state->prim, 0);
  }

  context.state->samplerTexture[1] = drawStream.reflectionProbeTexture;
  context.state->samplerTexture[2] = drawStream.lightmapPrimaryTexture;
  context.state->samplerTexture[3] = drawStream.lightmapSecondaryTexture;
}


