#include "r_local.h"
#include "rb_backend.h"

void R_DrawLitCallback(const void *userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxViewInfo *data = (GfxViewInfo*)userData;

  R_SetRenderTarget(context, R_RENDERTARGET_SCENE);
  if ( prepassContext.state )
  {
    R_SetRenderTarget(prepassContext, R_RENDERTARGET_SCENE);
  }

  R_HW_EnableScissor(context.state->prim.device, data->scissorViewport.x, data->scissorViewport.y, data->scissorViewport.width, data->scissorViewport.height);
  R_DrawSurfs(context, prepassContext.state, &data->litInfo);
  R_HW_DisableScissor(context.state->prim.device);
}


void R_DrawDecalCallback(const void *userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxViewInfo *data = (GfxViewInfo*)userData;

  R_SetRenderTarget(context, R_RENDERTARGET_SCENE);
  if ( prepassContext.state )
  {
    R_SetRenderTarget(prepassContext, R_RENDERTARGET_SCENE);
  }

  R_HW_EnableScissor(context.state->prim.device, data->scissorViewport.x, data->scissorViewport.y, data->scissorViewport.width, data->scissorViewport.height);
  R_DrawSurfs(context, prepassContext.state, &data->decalInfo);
  R_HW_DisableScissor(context.state->prim.device);
}

void R_DrawDecal(const GfxViewInfo *viewInfo, GfxCmdBuf *cmdBuf, GfxCmdBuf *prepassCmdBuf)
{
    GfxCmdBufSourceState sourceState;

    PIXBeginNamedEvent(-1, "R_DrawDecal");
    R_InitCmdBufSourceState(&sourceState, &viewInfo->input, 1);
    R_SetRenderTargetSize(&sourceState, R_RENDERTARGET_SCENE);
    R_SetViewportStruct(&sourceState, &viewInfo->sceneViewport);

    R_DrawCall(R_DrawDecalCallback, viewInfo, &sourceState, viewInfo, &viewInfo->decalInfo, &viewInfo->viewParms, cmdBuf, prepassCmdBuf);
/*
    if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
    {
        D3DPERF_EndEvent();
    }
*/
}


void R_DrawLit(const GfxViewInfo *viewInfo, GfxCmdBuf *cmdBuf, GfxCmdBuf *prepassCmdBuf)
{
    GfxCmdBufSourceState sourceState;

    R_InitCmdBufSourceState(&sourceState, &viewInfo->input, 1);
    R_SetRenderTargetSize(&sourceState, R_RENDERTARGET_SCENE);
    R_SetViewportStruct(&sourceState, &viewInfo->sceneViewport);
    //R_SetDrawLitConstants((int)&v9, &sourceState, viewInfo, &viewInfo->cullViewInfo.viewParms);

    R_DrawCall(R_DrawLitCallback, viewInfo, &sourceState, viewInfo, &viewInfo->litInfo, &viewInfo->viewParms, cmdBuf, prepassCmdBuf);
}


