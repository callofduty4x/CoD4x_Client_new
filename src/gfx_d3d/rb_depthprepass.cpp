#include "r_local.h"
#include "rb_backend.h"
#include "r_state.h"


void R_DepthPrepassCallback(const void *userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
    GfxDrawSurfListInfo info;
    MaterialTechniqueType baseTechType;
    GfxViewInfo *viewInfo;

/*
    v3 = 3;
    for ( i = info.group; --v3 >= 0; ++i )
    {
        i->QueuedBatchCount = 0;
        i->ExecutingBatchCount = 0;
    }
*/
    viewInfo = (GfxViewInfo *)userData;

//    if ( !(userData->sceneComposition.renderingMode & 7) )
    {
        R_HW_EnableScissor(context.state->prim.device, viewInfo->scissorViewport.x, viewInfo->scissorViewport.y, viewInfo->scissorViewport.width, viewInfo->scissorViewport.height);
    }

    if ( viewInfo->needsFloatZ )
    {
        R_SetRenderTarget(context, R_RENDERTARGET_FLOAT_Z);
        
        baseTechType = TECHNIQUE_BUILD_FLOAT_Z;
        R_DrawQuadMesh(context, rgp.shadowClearMaterial, &viewInfo->fullSceneViewMesh->meshData);

        R_SetCodeConstantFromVec4(context.source, CONST_SRC_CODE_DEPTH_FROM_CLIP, (const float[]){0.0, 0.0, 0.0, 1.0});
    }
    else
    {
        
        R_SetRenderTarget(context, R_RENDERTARGET_DYNAMICSHADOWS);
        baseTechType = TECHNIQUE_DEPTH_PREPASS;
    }

//    R_SetWindShaderConstants(context.source);
    
    memcpy(&info, &viewInfo->litInfo, sizeof(info));
    info.baseTechType = baseTechType;

    PIXBeginNamedEvent(-1, "zprepass litInfo");
    R_DrawSurfs(context, 0, &info);

/*
    if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
    {
        D3DPERF_EndEvent();
    }
*/

    memcpy(&info, &viewInfo->decalInfo, sizeof(info));
    info.baseTechType = baseTechType;

    PIXBeginNamedEvent(-1, "zprepass decalInfo");
    R_DrawSurfs(context, 0, &info);

/*
    if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
    {
        D3DPERF_EndEvent();
    }
*/
//    if ( !(viewInfo->sceneComposition.renderingMode & 7) )

    {
        R_HW_DisableScissor(context.state->prim.device);
    }
}


void R_DepthPrepass(GfxRenderTargetId renderTargetId, const GfxViewInfo *viewInfo, GfxCmdBuf *cmdBuf)
{
    GfxCmdBufSourceState state;

#pragma msg "Check CoD4"

    if ( !r_reflectionProbeGenerate->current.enabled )
    {

        R_InitCmdBufSourceState(&state, &viewInfo->input, 1);
        R_SetRenderTargetSize(&state, renderTargetId);

        R_SetViewportStruct(&state, &viewInfo->sceneViewport);
        // R_SetADSZScaleConstants(viewInfo->localClientNum, &state);
        R_DrawCall(R_DepthPrepassCallback, viewInfo, &state, viewInfo, 0, &viewInfo->viewParms, cmdBuf, 0);
    }
}