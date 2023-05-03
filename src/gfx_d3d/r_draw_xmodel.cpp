#include "r_local.h"
#include "r_model.h"
#include "../database/db_shared.h"


void R_DrawXModelRigidModelSurf(GfxCmdBufContext context, XSurface *surface)
{
  GfxDrawPrimArgs args;
  D3DIndexBuffer *ib;
  int offset;
  D3DVertexBuffer *vb;

  args.vertexCount = surface->vertCount;
  args.triCount = surface->triCount;
  DB_GetIndexBufferAndBase(surface->XZoneHandle, surface->triIndices, &ib, &args.baseIndex);
  if ( ib != context.state->prim.indexBuffer )
  {
    R_ChangeIndices(&context.state->prim, ib);
  }
  DB_GetVertexBufferAndOffset(surface->XZoneHandle, surface->verts0, &vb, &offset);
  R_SetStreamSource(&context.state->prim, vb, offset, 32);
  R_SetupPassPerPrimArgs(context);
  R_DrawIndexedPrimitive(&context.state->prim, &args);
}