#include "r_local.h"
#include "rb_backend.h"
#include "r_material.h"

void R_HW_SetVertexShader(D3DDevice *device, const MaterialVertexShader *mtlShader)
{
  assert(device);
  
  D3DCALL(device->SetVertexShader( mtlShader ? mtlShader->prog.vs : NULL ));
}

void R_HW_SetPixelShader(D3DDevice *device, const MaterialPixelShader *mtlShader)
{
  assert(device);

  D3DCALL(device->SetPixelShader( mtlShader ? mtlShader->prog.ps : NULL ));

}

void RB_ClearVertexShader()
{
  if ( gfxCmdBufState.vertexShader )
  {
    R_HW_SetVertexShader(gfxCmdBufState.prim.device, NULL);
  }
  gfxCmdBufState.vertexShader = NULL;
}

void R_SetVertexDecl(GfxCmdBufPrimState *primState, MaterialVertexDeclaration *vertexDecl)
{
  D3DVertexDeclaration *decl;
  D3DDevice *device;

  if ( vertexDecl )
  {
    decl = vertexDecl->routing.decl[primState->vertDeclType];
  }
  else
  {
    decl = NULL;
  }
  if ( primState->vertexDecl != decl )
  {
    device = primState->device;
    assert(device);
    if ( decl )
    {
      D3DCALL(device->SetVertexDeclaration( decl ));
    }
    primState->vertexDecl = decl;
  }
}

void RB_ClearVertexDecl()
{
  if ( gfxCmdBufState.prim.vertexDecl )
  {
    R_SetVertexDecl(&gfxCmdBufState.prim, 0);
  }
  if ( gfxCmdBufState.prim.vertexDecl )
  {
      assert(gfxCmdBufState.prim.vertexDecl == NULL);
  }
}


void R_CheckVertexDataOverflow(int dataSize)
{
  assert(gfxBuf.dynamicVertexBuffer);
  assertx(dataSize > 0 && dataSize <= gfxBuf.dynamicVertexBuffer->total, "(dataSize) = %i", dataSize);

  if ( dataSize + gfxBuf.dynamicVertexBuffer->used > gfxBuf.dynamicVertexBuffer->total )
  {
    gfxBuf.dynamicVertexBuffer->used = 0;
  }
}

void R_DrawTessTechnique(GfxCmdBufContext context, GfxDrawPrimArgs *args) //Seems to be used 2D Drawing, not so much (or not at all) for 3D
{
  MaterialTechnique *technique;
  D3DVertexBuffer *vb;
  int vertexOffset;
  bool isPixelCostEnabled;
  unsigned int passIndex;

  assert(r_dx.d3d9 && r_dx.device);
  assert(context.state->material);

  technique = context.state->technique;

  assert(technique);

//  R_BeginPixMaterial(context.state);

  _RB_LogPrintf("\n---------- R_DrawTechnique( %s ) ----------\n", technique->name);

  isPixelCostEnabled = pixelCostMode != GFX_PIXEL_COST_MODE_OFF;
  if ( isPixelCostEnabled )
  {
    R_PixelCost_BeginSurface(context);
  }

  assert(context.state->prim.vertDeclType == VERTDECL_GENERIC);

  R_CheckVertexDataOverflow(32 * tess.vertexCount);

  vertexOffset = R_SetVertexData(context.state, &tess, tess.vertexCount, 32);
  for ( passIndex = 0; passIndex < technique->passCount; ++passIndex )
  {
    R_SetupPass(context, passIndex);
    R_UpdateVertexDecl(context.state);
    R_SetupPassCriticalPixelShaderArgs(context);
    vb = gfxBuf.dynamicVertexBuffer->buffer;

    assert(vb);

    R_SetStreamSource(&context.state->prim, vb, vertexOffset, 32);
    R_SetupPassPerObjectArgs(context);
    R_SetupPassPerPrimArgs(context);
    R_DrawIndexedPrimitive(&context.state->prim, args);
  }
  if ( isPixelCostEnabled )
  {
    R_PixelCost_EndSurface(context);
  }

  _RB_LogPrintf("\n");

//  R_EndPixMaterial(context.state);
}


void RB_DrawTessSurface()
{
//  GfxViewport scissor;
  GfxViewport viewport;
  GfxDrawPrimArgs args;

  assert(tess.indexCount);

  if ( gfxCmdBufSourceState.viewportIsDirty )
  {
    R_GetViewport(&gfxCmdBufSourceState, &viewport);
    R_SetViewport(&gfxCmdBufState, &viewport);
    R_UpdateViewport(&gfxCmdBufSourceState, &viewport);
/*    
    if ( R_GetScissor(&gfxCmdBufSourceState, &scissor) )
    {
      R_SetScissor(&gfxCmdBufState, &scissor);
    }
    else
    {
      R_ClearScissor(&gfxCmdBufState);
    }
*/  
  }
  args.vertexCount = tess.vertexCount;
  args.triCount = tess.indexCount / 3;

  assert(gfxCmdBufState.prim.vertDeclType == VERTDECL_GENERIC);

  args.baseIndex = R_SetIndexData(&gfxCmdBufState.prim, tess.indices, args.triCount);
  R_DrawTessTechnique(gfxCmdBufContext, &args);
  tess.indexCount = 0;
  tess.vertexCount = 0;
}

