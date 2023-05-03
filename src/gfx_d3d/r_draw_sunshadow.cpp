#include "r_local.h"
#include "r_state.h"
#include "rb_backend.h"


void R_DrawSunShadowMapCallback(const void *userData, GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
  GfxSunShadowPartition *partition = (GfxSunShadowPartition*)userData;

  R_SetRenderTarget(context, R_RENDERTARGET_SHADOWMAP_SUN);
  if ( !partition->partitionIndex )
  {
    R_ClearScreen(context.state->prim.device, 3, shadowmapClearColor, 1.0, 0, 0);
  }
  R_HW_EnableScissor(context.state->prim.device, 
                partition->viewport.x, partition->viewport.y + partition->partitionIndex * (R_Is1900Card() ? 512 : 1024),
                partition->viewport.width, partition->viewport.height);
  R_DrawSurfs(context, 0, &partition->info);
  R_HW_DisableScissor(context.state->prim.device);
}



