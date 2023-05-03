#include "r_local.h"
#include "rb_backend.h"
#include "../common/qcommon.h"
#include "../common/com_vector.h"
#include "r_utils.h"
#include "gfx_world.h"

struct GfxPointLitSurfsInfo
{
  const GfxViewInfo *viewInfo;
  GfxMeshData *clearQuadMesh;
  const GfxDrawSurfListInfo *drawSurfInfo;
  unsigned int x;
  unsigned int y;
  unsigned int w;
  unsigned int h;
};



void R_DrawFullbrightEmissiveCallback(const void* userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxViewInfo *viewInfo = (GfxViewInfo *)userData;
  R_SetRenderTarget(context, R_RENDERTARGET_SCENE);
  
  R_HW_EnableScissor(context.state->prim.device, viewInfo->scissorViewport.x, viewInfo->scissorViewport.y, viewInfo->scissorViewport.width, viewInfo->scissorViewport.height);
  
  R_DrawSurfs(context, 0, &viewInfo->emissiveInfo);

  R_HW_DisableScissor(context.state->prim.device);
}

void R_DrawEmissiveCallback(const void* userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxViewInfo *viewInfo = (GfxViewInfo *)userData;

  R_SetRenderTarget(context, R_RENDERTARGET_SCENE);

  R_Set3D(context.source);

  R_HW_EnableScissor(context.state->prim.device, viewInfo->scissorViewport.x, viewInfo->scissorViewport.y, viewInfo->scissorViewport.width, viewInfo->scissorViewport.height);

  PIXBeginNamedEvent(-1, "emissive");
  R_DrawSurfs(context, 0, &viewInfo->emissiveInfo);

  R_HW_DisableScissor(context.state->prim.device);
}

void R_DrawEmissive(const GfxViewInfo *viewInfo, GfxCmdBuf *cmdBuf)
{
    GfxCmdBufSourceState sourceState;

    R_InitCmdBufSourceState(&sourceState, &viewInfo->input, 1);
    R_SetRenderTargetSize(&sourceState, R_RENDERTARGET_SCENE);
    R_SetViewportStruct(&sourceState, &viewInfo->sceneViewport);
    //R_SetADSZScaleConstants(viewInfo->localClientNum, &sourceState);
    R_DrawCall(R_DrawEmissiveCallback, viewInfo, &sourceState, viewInfo, &viewInfo->emissiveInfo, &viewInfo->viewParms, cmdBuf, 0);
}

void R_DrawPointLitSurfsCallback(const void* userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxPointLitSurfsInfo *surfInfo = (GfxPointLitSurfsInfo*)userData;
  R_SetRenderTarget(context, R_RENDERTARGET_SCENE);
  R_Set2D(context.source);
  R_DrawQuadMesh(context, rgp.clearAlphaStencilMaterial, surfInfo->clearQuadMesh);
  R_Set3D(context.source);
/*
  if ( !(surfInfo->viewInfo->sceneComposition.renderingMode & 7) )
  {
    R_HW_EnableScissor(context.state->prim.device, surfInfo->x, surfInfo->y, surfInfo->w, surfInfo->h);
  }
  R_DrawSurfs(context, 0, surfInfo->drawSurfInfo);
  if ( !(surfInfo->viewInfo->sceneComposition.renderingMode & 7) )
  {
    R_HW_DisableScissor(context.state->prim.device);
  }
*/
  R_HW_EnableScissor(context.state->prim.device, surfInfo->x, surfInfo->y, surfInfo->w, surfInfo->h);
  R_DrawSurfs(context, 0, surfInfo->drawSurfInfo);
  R_HW_DisableScissor(context.state->prim.device);
}


void R_DrawDebugShaderLitCallback(const void* userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxViewInfo *viewInfo = (GfxViewInfo *)userData;

  R_SetRenderTarget(context, R_RENDERTARGET_SCENE);
  R_HW_EnableScissor(context.state->prim.device, viewInfo->scissorViewport.x, viewInfo->scissorViewport.y, viewInfo->scissorViewport.width, viewInfo->scissorViewport.height);
  R_DrawSurfs(context, 0, &viewInfo->litInfo);
  R_HW_DisableScissor(context.state->prim.device);
}

void R_DrawDebugShaderDecalCallback(const void* userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxViewInfo *viewInfo = (GfxViewInfo *)userData;

  R_SetRenderTarget(context, R_RENDERTARGET_SCENE);
  R_DrawSurfs(context, 0, &viewInfo->decalInfo);
}

void R_DrawDebugShaderEmissiveCallback(const void* userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxViewInfo *viewInfo = (GfxViewInfo *)userData;

  R_SetRenderTarget(context, R_RENDERTARGET_SCENE);

  R_HW_EnableScissor(context.state->prim.device, viewInfo->scissorViewport.x, viewInfo->scissorViewport.y, viewInfo->scissorViewport.width, viewInfo->scissorViewport.height);
  R_DrawSurfs(context, 0, &viewInfo->emissiveInfo);
  R_HW_DisableScissor(context.state->prim.device);
}


void R_DrawFullbrightLitCallback(const void* userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxViewInfo *viewInfo = (GfxViewInfo *)userData;

  R_SetRenderTarget(context, R_RENDERTARGET_SCENE);
/*
  if ( !(viewInfo->sceneComposition.renderingMode & 7) )
  {
    R_HW_EnableScissor(context.state->prim.device, viewInfo->scissorViewport.x, viewInfo->scissorViewport.y, viewInfo->scissorViewport.width, viewInfo->scissorViewport.height);
  }
  R_DrawSurfs(context, 0, viewInfo->drawList);
  if ( !(viewInfo->sceneComposition.renderingMode & 7) )
  {
    R_HW_DisableScissor(context.state->prim.device);
  }
  */
  R_HW_EnableScissor(context.state->prim.device, viewInfo->scissorViewport.x, viewInfo->scissorViewport.y, viewInfo->scissorViewport.width, viewInfo->scissorViewport.height);
  
  R_DrawSurfs(context, 0, &viewInfo->litInfo);

  R_HW_DisableScissor(context.state->prim.device);
}


void R_DrawFullbrightDecalCallback(const void* userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxViewInfo *viewInfo = (GfxViewInfo *)userData;

  R_SetRenderTarget(context, R_RENDERTARGET_SCENE);
/*
  if ( !(viewInfo->sceneComposition.renderingMode & 7) )
  {
    R_HW_EnableScissor(context.state->prim.device, viewInfo->scissorViewport.x, viewInfo->scissorViewport.y, viewInfo->scissorViewport.width, viewInfo->scissorViewport.height);
  }
  R_DrawSurfs(context, 0, &viewInfo->drawList[3]);
  if ( !(viewInfo->sceneComposition.renderingMode & 7) )
  {
    R_HW_DisableScissor(context.state->prim.device);
  }
*/

  R_HW_EnableScissor(context.state->prim.device, viewInfo->scissorViewport.x, viewInfo->scissorViewport.y, viewInfo->scissorViewport.width, viewInfo->scissorViewport.height);
  
  R_DrawSurfs(context, 0, &viewInfo->decalInfo);

  R_HW_DisableScissor(context.state->prim.device);
}

void RB_EndSceneRendering(GfxCmdBufContext context, const GfxCmdBufInput *input, const GfxViewInfo *viewInfo)
{
  PIXBeginNamedEvent(-1, "RB_EndSceneRendering()");

  R_HW_InsertFence(&backEndData->endFence);
  
  R_InitCmdBufSourceState(context.source, input, 0);
  R_InitLocalCmdBufState(context.state);

  R_SetRenderTargetSize(&gfxCmdBufSourceState, R_RENDERTARGET_SCENE);
  R_BeginView(&gfxCmdBufSourceState, &viewInfo->sceneDef, &viewInfo->viewParms);
  R_SetViewportStruct(&gfxCmdBufSourceState, &viewInfo->sceneViewport);
  R_SetRenderTarget(gfxCmdBufContext, R_RENDERTARGET_SCENE);

  if ( com_developer->current.integer )
  {
    R_Set3D(&gfxCmdBufSourceState);

    assert(gfxCmdBufSourceState.viewMode == VIEW_MODE_3D);

    RB_DrawDebug(&gfxCmdBufSourceState.viewParms);
    RB_ShowCollision(&gfxCmdBufSourceState.viewParms);
  }

  memcpy(&gfxCmdBufState, context.state, sizeof(gfxCmdBufState));
/*
  if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
  {
    D3DPERF_EndEvent();
  }
*/
}

void R_DrawPointLitSurfs(GfxCmdBufSourceState *source, const GfxViewInfo *viewInfo, GfxCmdBuf *cmdBuf)
{
  vec3_t edgePoint;
  const PointLightPartition *pointLightPartitions;
  GfxPointLitSurfsInfo info;
  int pointLightCount;
  vec3_t perp;
  vec4_t dist;
  float halfWidth;
  float width;
  float height;
  const GfxLight *light;
  float sign;
  const PointLightPartition *pointLightPartition;
  vec3_t offset;
  vec3_t edgeGoalPoint;
  float tangentDist;
  vec3_t edgeDir;
  float planeDist;
  int partitionIndex;
  const GfxViewParms *viewParms;
  float tangentDistSq;
  GfxColor color;
  float x;
  float y;
  unsigned int axis;
  float offsetDistSq;
  unsigned int planeIndex;
  float halfHeight;
  vec3_t perpDir;
  float perpDist;
  float w;

  assert(viewInfo);

  pointLightCount = viewInfo->pointLightCount;
  if ( pointLightCount == 0)
  {
    return;
  }
  pointLightPartitions = viewInfo->pointLightPartitions;
  R_ConvertColorToBytes(colorWhite, color.array);

  /*
  GfxDrawPrimArgs args;
  GfxBackEndData *data;

  data = source->input.data;
  args.baseIndex = 0;
  args.vertexCount = 4;
  args.triCount = 2;
  */

  viewParms = &viewInfo->viewParms;
  info.viewInfo = viewInfo;
  for ( partitionIndex = 0; partitionIndex < pointLightCount; ++partitionIndex )
  {
    pointLightPartition = &pointLightPartitions[partitionIndex];
    light = &pointLightPartition->light;
    
    info.drawSurfInfo = &pointLightPartition->info;
    info.clearQuadMesh = (GfxMeshData*)(&viewInfo->pointLightMeshData[partitionIndex]); //ugly
    
    dist[0] = 1.0;
    dist[1] = -1.0;
    dist[2] = 1.0;
    dist[3] = -1.0;

    VectorSubtract(pointLightPartition->light.origin, viewParms->origin, offset);
    offsetDistSq = VectorLengthSquared(offset);

    tangentDistSq = offsetDistSq - Square(pointLightPartition->light.radius);
    if ( tangentDistSq > 1.0 )
    {
      tangentDist = sqrt(tangentDistSq);
      perpDist = offsetDistSq / tangentDist;
      sign = 1.0;
      planeIndex = 0;
      while ( planeIndex < 4 )
      {
        axis = planeIndex >> 1;
        VectorScale(viewParms->axis[2 - axis], sign, perp);
        Vec3Cross(perp, offset, perpDir);
        Vec3Normalize(perpDir);
        VectorMA(viewParms->origin, -perpDist, perpDir, edgeGoalPoint);
        VectorSubtract(edgeGoalPoint, light->origin, edgeDir);
        Vec3Normalize(edgeDir);
        VectorMA(light->origin, light->radius, edgeDir, edgePoint);

        if ( DotProduct(viewInfo->frustumPlanes[planeIndex], edgePoint) + viewInfo->frustumPlanes[planeIndex][3] > 0.0 )
        {
            w = edgePoint[0] * viewParms->viewProjectionMatrix.m[0][3] + edgePoint[1] * viewParms->viewProjectionMatrix.m[1][3] + edgePoint[2] * viewParms->viewProjectionMatrix.m[2][3] + viewParms->viewProjectionMatrix.m[3][3];
            if ( w > 0.0 )
            {
                planeDist = edgePoint[0] * viewParms->viewProjectionMatrix.m[0][axis] + edgePoint[1] * viewParms->viewProjectionMatrix.m[1][axis] + edgePoint[2] * viewParms->viewProjectionMatrix.m[2][axis] + viewParms->viewProjectionMatrix.m[3][axis];
                dist[planeIndex] = _clip2domain(planeDist / w, -1.0, +1.0);
            }
        }
        ++planeIndex;
        sign = -sign;
      }
    }
    halfWidth = viewInfo->sceneViewport.width / 2;
    halfHeight = viewInfo->sceneViewport.height / 2;
    x = (1.0 + dist[1]) * halfWidth;
    y = (1.0 - dist[2]) * halfHeight;
    width = (dist[0] - dist[1]) * halfWidth;
    height = (dist[2] - dist[3]) * halfHeight;
    info.x = (signed int)floor(x);
    info.y = (signed int)floor(y);
    info.w = (signed int)ceil((1.0 + dist[0]) * halfWidth) - info.x;
    info.h = (signed int)ceil((1.0 - dist[3]) * halfHeight) - info.y;
    info.x += viewInfo->sceneViewport.x;
    info.y += viewInfo->sceneViewport.y;
    R_SetQuadMeshData(info.clearQuadMesh, x, y, width, height, 0.0, 0.0, 1.0, 1.0, 0xFFFFFFFF);
    R_DrawCall(R_DrawPointLitSurfsCallback, &info, source, viewInfo, &pointLightPartition->info, &viewInfo->viewParms, cmdBuf, 0);
  }
}


void R_ResolveDistortion(const GfxViewInfo *viewInfo)
{
    PIXBeginNamedEvent(-1, "Resolve Distortion");

    R_SetRenderTargetSize(&gfxCmdBufSourceState, R_RENDERTARGET_SCENE);
    R_SetRenderTarget(gfxCmdBufContext, R_RENDERTARGET_SCENE);
    R_Resolve(gfxCmdBufContext, gfxRenderTargets[R_RENDERTARGET_RESOLVED_POST_SUN].image);
    
    /*
    if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
    {
        D3DPERF_EndEvent();
    }*/
}


void R_DrawLights(const GfxViewInfo *viewInfo, GfxCmdBuf *cmdBuf)
{

  GfxCmdBufSourceState sourceState;

  R_InitCmdBufSourceState(&sourceState, &viewInfo->input, 1);
  R_SetRenderTargetSize(&sourceState, R_RENDERTARGET_SCENE);
  R_SetViewportStruct(&sourceState, &viewInfo->sceneViewport);
  R_DrawPointLitSurfs(&sourceState, viewInfo, cmdBuf);
}


void R_DrawFullbrightOrDebugShader(DrawCallCallback callback, const GfxViewInfo *viewInfo, const GfxDrawSurfListInfo *info, GfxCmdBuf *cmdBuf)
{
  GfxCmdBufSourceState sourceState;

  R_InitCmdBufSourceState(&sourceState, &viewInfo->input, 1);
  R_SetRenderTargetSize(&sourceState, R_RENDERTARGET_SCENE);
  R_SetViewportStruct(&sourceState, &viewInfo->sceneViewport);
  R_DrawCall(callback, viewInfo, &sourceState, viewInfo, info, &viewInfo->viewParms, cmdBuf, 0);
}

void R_DrawFullbright(const GfxViewInfo *viewInfo, GfxCmdBufInput *input, GfxCmdBuf *cmdBuf)
{
  PIXBeginNamedEvent(-1, "R_DrawFullbrightOrDebugShader - Lit");
  R_DrawFullbrightOrDebugShader(R_DrawFullbrightLitCallback, viewInfo, &viewInfo->litInfo, cmdBuf);
  /*
  if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
  {
      D3DPERF_EndEvent();
  }*/
  PIXBeginNamedEvent(-1, "R_DrawFullbrightOrDebugShader - Decal");
  R_DrawFullbrightOrDebugShader(R_DrawFullbrightDecalCallback, viewInfo, &viewInfo->decalInfo, cmdBuf);
  /*if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
  {
      D3DPERF_EndEvent();
  }*/
  PIXBeginNamedEvent(-1, "R_DrawFullbrightOrDebugShader - Emissive");
  R_DrawFullbrightOrDebugShader(R_DrawFullbrightEmissiveCallback, viewInfo, &viewInfo->emissiveInfo, cmdBuf);
  /*if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
  {
      D3DPERF_EndEvent();
  }*/
}

void R_DrawDebugShader(const GfxViewInfo *viewInfo, GfxCmdBuf *cmdBuf)
{
    R_DrawFullbrightOrDebugShader(R_DrawDebugShaderLitCallback, viewInfo, &viewInfo->litInfo, cmdBuf);
    R_DrawFullbrightOrDebugShader(R_DrawDebugShaderDecalCallback, viewInfo, &viewInfo->decalInfo, cmdBuf);
    R_DrawFullbrightOrDebugShader(R_DrawDebugShaderEmissiveCallback, viewInfo, &viewInfo->emissiveInfo, cmdBuf);
}

void R_ClearForFrameBuffer(D3DDevice *device, GfxViewport *viewport)
{
    float clearColor[4];

    R_GetClearColor(clearColor);
    R_ClearScreen(device, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL | D3DCLEAR_TARGET, clearColor, 1.0, 0, viewport);
}

void R_SetAndClearSceneTarget(const GfxViewport *viewport, const GfxViewInfo *viewInfo)
{
    R_InitLocalCmdBufState(&gfxCmdBufState);
    PIXBeginNamedEvent(-1, "Clear Render Target");
    R_SetRenderTargetSize(&gfxCmdBufSourceState, R_RENDERTARGET_SCENE);
    R_SetRenderTarget(gfxCmdBufContext, R_RENDERTARGET_SCENE);
    R_ClearForFrameBuffer(gfxCmdBufState.prim.device, NULL);
/*
    if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
    {
        D3DPERF_EndEvent();
    }
*/
  //memcpy(gfxCmdBufState.refSamplerState, gfxCmdBufState.refSamplerState, 0x13D0u);
}


void RB_FullbrightDrawCommands(const GfxViewInfo *viewInfo)
{
    struct GfxBackEndData *data;
    GfxCmdBuf cmdBuf;

    PIXBeginNamedEvent(-1, "RB_FullbrightDrawCommands");
    data = backEndData;
    R_SetAndClearSceneTarget(0, viewInfo);
    R_InitContext(data, &cmdBuf);
    R_DrawFullbright(viewInfo, &gfxCmdBufContext.source->input, &cmdBuf);
    R_InitCmdBufSourceState(gfxCmdBufContext.source, &viewInfo->input, 0);
    R_InitLocalCmdBufState(gfxCmdBufContext.state);
    R_SetRenderTargetSize(gfxCmdBufContext.source, R_RENDERTARGET_SCENE);
    R_SetRenderTarget(gfxCmdBufContext, R_RENDERTARGET_SCENE);
    R_BeginView(gfxCmdBufContext.source, &viewInfo->sceneDef, &viewInfo->viewParms);
    R_SetViewportStruct(gfxCmdBufContext.source, &viewInfo->sceneViewport);
    RB_DrawSun(viewInfo->localClientNum);
    //memcpy(gfxCmdBufState.refSamplerState, gfxCmdBufContext.state->refSamplerState, 0x13D0u);
    RB_EndSceneRendering(gfxCmdBufContext, &viewInfo->input, viewInfo);
/*
    if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
    {
        D3DPERF_EndEvent();
    }
*/
}


void RB_DebugShaderDrawCommands(const GfxViewInfo *viewInfo)
{
    struct GfxBackEndData *data;
    GfxCmdBuf cmdBuf;

    data = backEndData;
    R_SetAndClearSceneTarget(0, viewInfo);
    R_InitContext(data, &cmdBuf);
    R_DrawDebugShader(viewInfo, &cmdBuf);
    RB_EndSceneRendering(gfxCmdBufContext, &viewInfo->input, viewInfo);
}

void RB_StandardDrawCommands(const GfxViewInfo *viewInfo)
{
    GfxRenderTargetId setupRenderTargetId;
    GfxBackEndData *data;
    GfxCmdBuf cmdBuf;
    bool needsDepthPrepass;
    ShadowType dynamicShadowType;
    float clearColor[4];
    unsigned char whichToClearForScene;
    unsigned char whichToClearForSetup;

    PIXBeginNamedEvent(-1, "RB_StandardDrawCommands");
    data = backEndData;

    dynamicShadowType = viewInfo->dynamicShadowType;

    if ( dynamicShadowType == SHADOW_MAP )
    {
        if ( Com_BitCheckAssert(data->shadowableLightHasShadowMap, rgp.world->sunPrimaryLightIndex, 32) )
        {
            RB_SunShadowMaps(data, viewInfo);
        }
        RB_SpotShadowMaps(data, viewInfo);
    }

    needsDepthPrepass = r_depthPrepass->current.enabled;
    whichToClearForSetup = D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
    whichToClearForScene = D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL | D3DCLEAR_TARGET;

    R_InitContext(data, &cmdBuf);

    if(viewInfo->needsFloatZ)
    {
      setupRenderTargetId = R_RENDERTARGET_FLOAT_Z;
    }else{
      whichToClearForSetup |= D3DCLEAR_TARGET;
      if ( dynamicShadowType == SHADOW_COOKIE )
      {
        setupRenderTargetId = R_RENDERTARGET_DYNAMICSHADOWS;
      }else{
        setupRenderTargetId = R_RENDERTARGET_SCENE;
      }
    }

    if(setupRenderTargetId == R_RENDERTARGET_FLOAT_Z || setupRenderTargetId == R_RENDERTARGET_DYNAMICSHADOWS)
    {
      R_InitLocalCmdBufState(&gfxCmdBufState);
      R_SetRenderTargetSize(&gfxCmdBufSourceState, setupRenderTargetId);
      R_SetRenderTarget(gfxCmdBufContext, setupRenderTargetId);
      R_ClearScreen(gfxCmdBufState.prim.device, whichToClearForSetup, colorWhite, 1.0, 0, 0);
//      memcpy(gfxCmdBufState, gfxCmdBufState, sizeof(gfxCmdBufState));
      R_InitContext(data, &cmdBuf);
/*
      Mac os cod4 has here several functions iw3mp doesn't have...
*/
      R_DepthPrepass(setupRenderTargetId, viewInfo, &cmdBuf);
      if ( dynamicShadowType == SHADOW_COOKIE )
      {
        RB_DrawShadowCookies(viewInfo);
      }
      if ( !r_dx.multiSampleType )
      {
        whichToClearForScene = D3DCLEAR_TARGET;
        needsDepthPrepass = false;
      }
    }

    R_InitLocalCmdBufState(&gfxCmdBufState);
    R_SetRenderTargetSize(&gfxCmdBufSourceState, R_RENDERTARGET_SCENE);
    R_SetRenderTarget(gfxCmdBufContext, R_RENDERTARGET_SCENE);

    if ( R_GetClearColor(clearColor) || whichToClearForScene & 0xFE )
    {
        R_ClearScreen(gfxCmdBufState.prim.device, 7, clearColor, 1.0, 0, 0);
    }
    //memcpy(&gfxCmdBufState, &gfxCmdBufState, 2576);
    if ( needsDepthPrepass )
    {
      R_InitContext(data, &cmdBuf);
      R_DepthPrepass(R_RENDERTARGET_SCENE, viewInfo, &cmdBuf);
    }

    R_InitContext(data, &cmdBuf);
    R_DrawLit(viewInfo, &cmdBuf, 0);

    R_InitContext(data, &cmdBuf);
    R_DrawDecal(viewInfo, &cmdBuf, 0);    

    PIXBeginNamedEvent(-1, "Resolve FloatZ");
    PIXBeginNamedEvent(-1, "Sun");

    R_InitCmdBufSourceState(&gfxCmdBufSourceState, &viewInfo->input, 0);
    R_InitLocalCmdBufState(&gfxCmdBufState);

    R_SetRenderTargetSize(&gfxCmdBufSourceState, R_RENDERTARGET_SCENE);
    R_SetRenderTarget(gfxCmdBufContext, R_RENDERTARGET_SCENE);
    
    R_BeginView(&gfxCmdBufSourceState, &viewInfo->sceneDef, &viewInfo->viewParms);
    R_SetViewportStruct(&gfxCmdBufSourceState, &viewInfo->sceneViewport);
    RB_DrawSun(viewInfo->localClientNum);

    R_InitContext(data, &cmdBuf);
    PIXBeginNamedEvent(-1, "Dynamic Lights");

    R_DrawLights(viewInfo, &cmdBuf);

    if(rg.distortion){
      R_ResolveDistortion(viewInfo);
    }

    PIXBeginNamedEvent(-1, "Emissive");
    R_DrawEmissive(viewInfo, &cmdBuf);

    RB_EndSceneRendering(gfxCmdBufContext, &viewInfo->input, viewInfo);

}

void RB_Draw3DInternal(const GfxViewInfo *viewInfo)
{
  assert(rgp.world);

  switch(gfxDrawMethod.drawScene)
  {
    case GFX_DRAW_SCENE_NONE:
      R_InitLocalCmdBufState(&gfxCmdBufState);
      R_SetRenderTargetSize(&gfxCmdBufSourceState, R_RENDERTARGET_FRAME_BUFFER);
      R_SetRenderTarget(gfxCmdBufContext, R_RENDERTARGET_FRAME_BUFFER);
      break;
    
    case GFX_DRAW_SCENE_FULLBRIGHT:
      RB_FullbrightDrawCommands(viewInfo);
      break;
    
    case GFX_DRAW_SCENE_DEBUGSHADER:
      RB_DebugShaderDrawCommands(viewInfo);
      break;

    case GFX_DRAW_SCENE_STANDARD:
      RB_StandardDrawCommands(viewInfo);
      break;

    default:
      assertx(false, "Bad case RB_Draw3DInternal");
      break;
  }
}


void RB_Draw3D()
{
/*
  char *Name;
  int v;
  int endView;
*/
  GfxBackEndData *data;
  const GfxViewInfo *viewInfo;

  data = backEndData;
  if ( backEndData->viewInfoCount )
  {
      //R_WindStartBackend();
      viewInfo = &data->viewInfo[data->viewInfoIndex];
/*
      if ( viewInfo->isMissileCamera )
      {
          endView = data->viewInfoIndex - 1;
          for ( v = data->viewInfoIndex; v >= endView; --v )
          {
              if ( v >= data->viewInfoCount && !(unsigned __int8)Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\rb_backend.cpp", 6072, 0, "v doesn't index data->viewInfoCount\n\t%i not in [0, %i)", v, data->viewInfoCount) )
              {
                  __debugbreak();
              }
              v0 = &data->viewInfo[v];
              Name = va("RB_Draw3D c=%d v=%d/%d", v0->localClientNum, v, data->viewInfoCount);
              PIXBeginNamedEvent(-1, Name);
              RB_ResetStatTracking(v);
              RB_Draw3DInternal(v0);
              if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
              {
                  D3DPERF_EndEvent();
              }
          }
      }
      else
      {
        */
        PIXBeginNamedEvent(-1, "RB_Draw3D c=%d v=%d/%d", viewInfo->localClientNum, data->viewInfoIndex, data->viewInfoCount);
        //RB_ResetStatTracking(data->viewInfoIndex);
        RB_Draw3DInternal(viewInfo);
/*
        if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
        {
            D3DPERF_EndEvent();
        }

      }
*/
  }
}