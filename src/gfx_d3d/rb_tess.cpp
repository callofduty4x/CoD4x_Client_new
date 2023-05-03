#include "r_local.h"
#include "rb_backend.h"
#include "r_model.h"
#include "r_state.h"
#include "../database/db_shared.h"


#define PARTICLE_CLOUD_QUADS 1024

void RB_CreateParticleCloud2dAxis(GfxParticleCloud *cloud, const float *viewUp, float (*viewAxis)[2])
{
  float viewRight[2];
  float scale;
  float viewAxisLength;

  assert(cloud);

  if ( viewUp[0] >= EQUAL_EPSILON || viewUp[1] >= EQUAL_EPSILON )
  {
    viewRight[0] = viewUp[1];
    viewRight[1] = -1.0 * viewUp[0];
    (*viewAxis)[0] = viewRight[0];
    (*viewAxis)[1] = viewRight[1];
    (*viewAxis)[2] = viewUp[0];
    (*viewAxis)[3] = viewUp[1];

    viewAxisLength = vec2_length((const float *)viewAxis);
    
    assert(viewAxisLength > 0);
    assert(fabs( viewAxisLength - vec2_length( viewAxis[1] ) ) < EQUAL_EPSILON);

    scale = cloud->radius[0] / viewAxisLength;
    (*viewAxis)[0] *= scale;
    (*viewAxis)[1] *= scale;
    if ( cloud->radius[0] > viewAxisLength )
    {
      (*viewAxis)[2] *= scale;
      (*viewAxis)[3] *= scale;
    }
  }
  else
  {
    (*viewAxis)[0] = cloud->radius[0];
    (*viewAxis)[1] = 0.0;
    (*viewAxis)[2] = 0.0;
    (*viewAxis)[3] = cloud->radius[1];
  }
}

void RB_Vec3DirWorldToView(GfxCmdBufSourceState *source, const float *worldDir, float *viewDir)
{
  float viewAxis[3][3];

  assert(source->viewMode == VIEW_MODE_3D);

  viewAxis[0][0] = source->viewParms.viewMatrix.m[0][1];
  viewAxis[0][1] = source->viewParms.viewMatrix.m[0][2];
  viewAxis[1][0] = source->viewParms.viewMatrix.m[1][1];
  viewAxis[1][1] = source->viewParms.viewMatrix.m[1][2];
  viewAxis[2][0] = source->viewParms.viewMatrix.m[2][1];
  viewAxis[2][1] = source->viewParms.viewMatrix.m[2][2];

  Vec3RotateTranspose(worldDir, viewAxis, viewDir);
}



void R_SetVertexDeclTypeNormal(GfxCmdBufState *state, MaterialVertexDeclType vertDeclType)
{
  state->prim.vertDeclType = vertDeclType;
  R_UpdateVertexDecl(state);
}


unsigned int R_TessStaticModelRigidDrawSurfList(const GfxDrawSurfListArgs *listArgs, GfxCmdBufContext prepassContext)
{
  GfxDrawSurf *localDrawSurf;
  GfxDepthRangeType depthRangeType;
  GfxCmdBufContext context;
  const GfxDrawSurfListInfo *info;
  GfxCmdBufSourceState *commonSource;
  char baseTechType;
  const unsigned int *primDrawSurfPos;

  context = listArgs->context;
  commonSource = listArgs->context.source;

  assert(prepassContext.state == NULL || commonSource == prepassContext.source);

  info = listArgs->info;
  if ( r_logFile->current.integer )
  {
    RB_LogPrintf("--- R_TessStaticModelRigidDrawSurfList( %s ) ---\n", context.state->material->info.name);
  }
  baseTechType = info->baseTechType;

  R_SetupPassCriticalPixelShaderArgs(context);
/*
  R_SetGameTime(context.source, context.source->sceneDef.floatTime);
  R_SetupPassVertexShaderArgs(context);
  
  if ( prepassContext.state )
  {
    R_SetupPassVertexShaderArgs(prepassContext);
  }
*/
  commonSource->objectPlacement = &s_manualObjectPlacement;
  R_ChangeDepthHackNearClip(commonSource, 0);

  R_SetVertexDeclTypeNormal(context.state, VERTDECL_PACKED);

  if(commonSource->cameraView == 0)
  {
      depthRangeType = GFX_DEPTH_RANGE_FULL;
  }else{
      depthRangeType = GFX_DEPTH_RANGE_SCENE;
  }

  if ( depthRangeType != context.state->depthRangeType )
  {
    R_ChangeDepthRange(context.state, depthRangeType);
  }

  if ( prepassContext.state )
  {
    R_SetupPassCriticalPixelShaderArgs(prepassContext);
    R_SetVertexDeclTypeNormal(prepassContext.state, VERTDECL_PACKED);
    if ( depthRangeType != prepassContext.state->depthRangeType )
    {
      R_ChangeDepthRange(prepassContext.state, depthRangeType);
    }
  }

  localDrawSurf = &info->drawSurfs[listArgs->firstDrawSurfIndex];
  primDrawSurfPos = &commonSource->input.data->primDrawSurfsBuf[localDrawSurf->fields.objectId];

//  RB_TrackImmediatePrims(&context.state->prim, GFX_PRIM_STATS_SMODELRIGID);
  
//  assert(context.state->prim.primStats);

//if ( baseTechType == 10 )
  if ( baseTechType == 7 )
  {
    if ( prepassContext.state )
    {
      R_SetupPassPerObjectArgs(prepassContext);
    }
    R_SetupPassPerObjectArgs(context);
    R_DrawStaticModelSurfLit(primDrawSurfPos, context, prepassContext, info);
  }
  else
  {
    assert(prepassContext.state == NULL);

    R_SetupPassPerObjectArgs(context);
    R_DrawStaticModelSurf(primDrawSurfPos, context, info);
  }
  //RB_EndTrackImmediatePrims(&context.state->prim);
  return 1;
}

void R_DrawXModelSkinnedUncached(GfxCmdBufContext context, XSurface *xsurf, GfxPackedVertex *skinnedVert)
{
  D3DVertexBuffer *vb;
  int vertexOffset;
  GfxDrawPrimArgs args;

  _RB_LogPrintf("--- R_DrawXModelSkinnedUncached( %s ) ---\n", context.state->material->info.name);

  assert(xsurf);
  assert(skinnedVert);

  args.triCount = XSurfaceGetNumTris(xsurf);
  args.vertexCount = XSurfaceGetNumVerts(xsurf);
#ifdef BLACKOPS
  //context.state->prim.frameStats.geoIndexCount += 3 * args.triCount;
#endif  
  args.baseIndex = R_SetIndexData(&context.state->prim, xsurf->triIndices, args.triCount);
  R_CheckVertexDataOverflow(32 * args.vertexCount);
  vertexOffset = R_SetVertexData(context.state, skinnedVert, args.vertexCount, 32);
  vb = gfxBuf.dynamicVertexBuffer->buffer;
  assert(vb);
  R_SetStreamSource(&context.state->prim, vb, vertexOffset, 32);
  R_DrawIndexedPrimitive(&context.state->prim, &args);

#ifdef BLACKOPS
  assert(context.state->prim.primStats);
  context.state->prim.primStats->staticIndexCount += 3 * args.triCount;
  context.state->prim.primStats->staticVertexCount += args.vertexCount;
  if ( r_showTess->current.integer )
  {
    GfxCmdBufSourceState* v4 = R_GetActiveWorldMatrix(context.source);
    RB_ShowTess(context, v4->matrices.matrix[0].m[3], "XMSkinUn$", &colorWhite);
  }
#endif
}

void R_DrawXModelSkinnedCached(GfxCmdBufContext context, const GfxModelSkinnedSurface *modelSurf)
{
  GfxBackEndData *data;
  XSurface *xsurf;
  D3DIndexBuffer *ib;
  GfxDrawPrimArgs args;

  _RB_LogPrintf("--- R_DrawXModelSkinnedCached( %s ) ---\n", context.state->material->info.name);

  assert(modelSurf);

  xsurf = modelSurf->xsurf;

  assert(xsurf);
  assert(xsurf->vertCount);
  assert(modelSurf->skinnedCachedOffset >= 0);

//args.baseIndex = 0;
  args.vertexCount = xsurf->vertCount;
  args.triCount = xsurf->triCount;

  DB_GetIndexBufferAndBase(xsurf->XZoneHandle, xsurf->triIndices, &ib, &args.baseIndex);

//context.state->prim.frameStats.geoIndexCount += 3 * args.triCount;
//ib = xsurf->indexBuffer;

  assert(ib);

  data = context.source->input.data;
  if ( context.state->prim.indexBuffer != ib )
  {
    R_ChangeIndices(&context.state->prim, ib);
  }
  R_SetStreamSource(&context.state->prim, data->skinnedCacheVb->buffer, modelSurf->skinnedCachedOffset, 32);

  if ( data->skinnedCacheVb->total >= data->skinnedCacheVb->used )
  {
    R_OpenGL_SetBufferHint(data->skinnedCacheVb->used);
  }
  else
  {
    R_OpenGL_SetBufferHint(data->skinnedCacheVb->total);
  }

  R_DrawIndexedPrimitive(&context.state->prim, &args);

  R_OpenGL_ClearBufferHints();

#ifdef BLACKOPS
  if ( context.state->prim.primStats )
  {
    assert(context.state->prim.primStats);
    context.state->prim.primStats->staticIndexCount += 3 * args.triCount;
    context.state->prim.primStats->staticVertexCount += args.vertexCount;
  }
  if ( r_showTess->current.integer )
  {
    GfxCmdBufSourceState *v3 = R_GetActiveWorldMatrix(context.source);
    RB_ShowTess(context, v3->matrices.matrix[0].m[3], "XMSkin$", &colorWhite);
  }
#endif
}


void RB_CheckTessOverflow(int vertexCount, int indexCount)
{
  assert(vertexCount <= 5450);
  assert(indexCount <= 1024 * 1024);

  if ( vertexCount + tess.vertexCount > 5450 || indexCount + tess.indexCount > 1024 * 1024)
  {
    RB_TessOverflow();
  }
}

void R_SetObjectIdentityPlacement(GfxCmdBufSourceState *source)
{
  if ( source->objectPlacement != &rg.remotePlacement )
  {
    source->objectPlacement = &rg.remotePlacement;
    R_ChangeObjectPlacementRemote(source, &rg.remotePlacement);
  }
}


void R_SetVertexDeclTypeWorld(GfxCmdBufState *state)
{
  if ( state->technique->flags & 8 )
  {
    R_SetVertexDeclTypeNormal(state, (MaterialVertexDeclType)((uint8_t)state->material->techniqueSet->worldVertFormat + VERTDECL_WORLD));
  }
  else
  {
    R_SetVertexDeclTypeNormal(state, VERTDECL_WORLD);
  }
}

unsigned int R_TessTrianglesPreTessList(const GfxDrawSurfListArgs *listArgs, GfxCmdBufContext prepassContext)
{
  D3DIndexBuffer *ib;
  GfxDepthRangeType depthRangeType;
  GfxCmdBufContext context;
  const GfxDrawSurfListInfo *info;
  GfxBackEndData *data;
  GfxCmdBufSourceState *commonSource;
  char baseTechType;
  const unsigned int *primDrawSurfPos;

  context = listArgs->context;
  commonSource = listArgs->context.source;


  assert(prepassContext.state == NULL);

  info = listArgs->info;
//  R_SetTerrainScorchTextures(listArgs->context.source, listArgs->context.state->material);
  R_SetupPassCriticalPixelShaderArgs(context); 
  baseTechType = info->baseTechType;
  R_SetObjectIdentityPlacement(commonSource);
  R_ChangeDepthHackNearClip(commonSource, 0);
  R_SetVertexDeclTypeWorld(context.state);

  if(commonSource->cameraView != 0)
  {
    depthRangeType = GFX_DEPTH_RANGE_SCENE;
  }else{
    depthRangeType = GFX_DEPTH_RANGE_FULL;
  }

  if ( depthRangeType != context.state->depthRangeType )
  {
    R_ChangeDepthRange(context.state, depthRangeType);
  }
  data = commonSource->input.data;
  ib = data->preTessIb;
  if ( context.state->prim.indexBuffer != ib )
  {
    R_ChangeIndices(&context.state->prim, ib);
  }
  uint16_t objectId = info->drawSurfs[listArgs->firstDrawSurfIndex].fields.objectId;
  primDrawSurfPos = &data->primDrawSurfsBuf[objectId];

//  R_TrackPrims(&context.state->prim, 0);
  if ( baseTechType == TECHNIQUE_LIT )
  {
    R_DrawBspDrawSurfsLitPreTess(primDrawSurfPos, context);
  }
  else
  {
    R_DrawBspDrawSurfsPreTess(primDrawSurfPos, context);
  }
//  context.state->prim.primStats = 0;
  return 1;
}


void R_SetParticleCloudConstants(GfxCmdBufSourceState *source, GfxParticleCloud *cloud)
{
  float scaledWorldUp[3];
  float viewUp[3];
  float viewAxis[2][2];
  float particleCloudMatrix[4];
  float particleColor[4];
  float worldUp[3];

  assert(cloud);

  if ( cloud->radius[0] == cloud->radius[1] || VecNCompareCustomEpsilon(cloud->placement.base.origin, cloud->endpos, 0.001, 3) )
  {
    viewAxis[0][0] = cloud->radius[0];
    viewAxis[0][1] = 0.0;
    viewAxis[1][0] = 0.0;
    viewAxis[1][1] = cloud->radius[1];
  }
  else
  {
    VectorSubtract(cloud->endpos, cloud->placement.base.origin, worldUp);
    Vec3Normalize(worldUp);
    VectorScale(worldUp, cloud->radius[1], scaledWorldUp);
    RB_Vec3DirWorldToView(source, scaledWorldUp, viewUp);
    RB_CreateParticleCloud2dAxis(cloud, viewUp, viewAxis);
  }
  particleCloudMatrix[0] = viewAxis[0][0];
  particleCloudMatrix[1] = viewAxis[0][1];
  particleCloudMatrix[2] = viewAxis[1][0];
  particleCloudMatrix[3] = viewAxis[1][1];

  R_SetCodeConstantFromVec4(source, CONST_SRC_CODE_PARTICLE_CLOUD_MATRIX, particleCloudMatrix);
  Byte4UnpackVertexColor((unsigned const char *)&cloud->color, particleColor);
  R_SetCodeConstantFromVec4(source, CONST_SRC_CODE_PARTICLE_CLOUD_COLOR, particleColor);
}


unsigned int R_TessParticleCloudList(const GfxDrawSurfListArgs *listArgs, GfxCmdBufContext prepassContext)
{
  GfxDepthRangeType depthRangeType;
  GfxParticleCloud *cloud;
  GfxCmdBufContext context;
  const GfxDrawSurfListInfo *info;
  GfxDrawSurf drawSurf;
  GfxBackEndData *data;
  GfxCmdBufSourceState *commonSource;
//  unsigned int offset;
  GfxDrawPrimArgs args;
//  unsigned int count;

  context = listArgs->context;
  commonSource = listArgs->context.source;

  assert(prepassContext.state == NULL || commonSource == prepassContext.source);
  
  info = listArgs->info;

  _RB_LogPrintf("--- RB_TessParticleCloud( %s ) ---\n", context.state->material->info.name);

  drawSurf = info->drawSurfs[listArgs->firstDrawSurfIndex];
  data = commonSource->input.data;
  assert ( drawSurf.fields.objectId < data->cloudCount);

  cloud = &data->clouds[drawSurf.fields.objectId];
  R_SetParticleCloudConstants(commonSource, cloud);
  R_SetupPassCriticalPixelShaderArgs(context);
  R_ChangeDepthHackNearClip(commonSource, 0);
  R_SetVertexDeclTypeNormal(context.state, VERTDECL_PARTICLECLOUD);

  if(commonSource->cameraView != 0)
  {
    depthRangeType = GFX_DEPTH_RANGE_SCENE;
  }else{
    depthRangeType = GFX_DEPTH_RANGE_FULL;
  }

  if ( depthRangeType != context.state->depthRangeType )
  {
    R_ChangeDepthRange(context.state, depthRangeType);
  }
/*
  offset = data->clouds[drawSurf.fields.objectId].offset;
  count = data->clouds[drawSurf.fields.objectId].count;

  assert(count && ((offset+count) <= PARTICLE_CLOUD_QUADS));

  if ( data->clouds[drawSurf.fields.objectId].gaussian )
  {
    offset += 1024;
  }
*/
  if ( context.state->prim.indexBuffer != gfxBuf.particleCloudIndexBuffer )
  {
    R_ChangeIndices(&context.state->prim, gfxBuf.particleCloudIndexBuffer);
  }
  R_SetStreamSource(&context.state->prim, gfxBuf.particleCloudVertexBuffer, 0, 20u);
  if ( commonSource->objectPlacement != &cloud->placement )
  {
    commonSource->objectPlacement = &cloud->placement;
    R_ChangeObjectPlacementRemote(commonSource, &cloud->placement);
  }
  R_SetupPassPerObjectArgs(context);
  R_SetupPassPerPrimArgs(context);
/*
  args.baseIndex = 6 * offset;
  args.vertexCount = 4 * count;
  if ( data->clouds[drawSurf.fields.objectId].gaussian )
  {
    args.vertexCount += 4096;
  }
  else
  {
    args.vertexCount = 4096;
  }
  args.triCount = 2 * count;

  context.state->prim.frameStats.fxIndexCount += 6 * count;
  RB_TrackImmediatePrims(&context.state->prim, GFX_PRIM_STATS_FX);
*/
  args.baseIndex = 0;
  args.triCount = 2048;
  args.vertexCount = 2 * args.triCount;
  R_DrawIndexedPrimitive(&context.state->prim, &args);
/*
  context.state->prim.primStats->staticVertexCount += args.vertexCount;
  context.state->prim.primStats->staticIndexCount += 3 * args.triCount;
  RB_EndTrackImmediatePrims(&context.state->prim);
*/
  return 1;
}