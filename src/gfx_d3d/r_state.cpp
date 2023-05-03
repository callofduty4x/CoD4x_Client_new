#include "r_local.h"
#include "rb_backend.h"
#include "r_image.h"
#include "r_state.h"
#include "gfx_world.h"

void R_DrawIndexedPrimitive(GfxCmdBufPrimState *state, const GfxDrawPrimArgs *args)
{
  signed int triCount = args->triCount;
  D3DDevice *device = state->device;
/*
  triCount = args->triCount;
  if ( triCount >= r_drawPrimFloor->current.integer && (!r_drawPrimCap->current.integer || triCount <= r_drawPrimCap->current.integer) )
  {
    if ( r_skipDrawTris->current.enabled )
    {
      triCount = 1;
    }
    RB_TrackDrawPrimCall(state, triCount);
*/
    assert(device);
    _RB_LogPrintf("device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, %d, %d, %d)\n", args->vertexCount, args->baseIndex, triCount);
    D3DCALLNOLOG(device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, args->vertexCount, args->baseIndex, triCount));
//}

}


GfxImage *R_OverrideGrayscaleImage(const dvar_s *dvar)
{

  if ( dvar->current.integer == R_COLOR_OVERRIDE_WHITE )
  {
    return rgp.whiteImage;
  }
  if ( dvar->current.integer == R_COLOR_OVERRIDE_BLACK)
  {
    return rgp.blackImage;
  }
  if ( dvar->current.integer == R_COLOR_OVERRIDE_GRAY)
  {
    return rgp.grayImage;
  }  
  assertx(false, "Bad case: %d\n", dvar->current.integer);
  return NULL;
}

void R_DepthHackNearClipChanged(GfxCmdBufSourceState *source)
{
  ++source->matrixVersions[2];
  ++source->matrixVersions[4];
  ++source->matrixVersions[5];
  source->input.consts[54][3] = -source->input.consts[54][3];
  ++source->constVersions[54];
}


void R_ChangeDepthHackNearClip(GfxCmdBufSourceState *source, unsigned int depthHackFlags)
{
  assert(source);
  
  if ( depthHackFlags != source->depthHackFlags )
  {
    R_DepthHackNearClipChanged(source);
    source->depthHackFlags = depthHackFlags;
  }
}

void R_SetInitialContextState(IDirect3DDevice9 *device)
{
  D3DCALL(device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, 1));
  D3DCALL(device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, 1));
  D3DCALL(device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE));
}


void R_ChangeStreamSource(GfxCmdBufPrimState *state, int streamIndex, D3DVertexBuffer *vb, unsigned int vertexOffset, unsigned int vertexStride)
{
  D3DDevice *device;

  device = state->device;
  assert(device);
  assert(state->streams[streamIndex].vb != vb || state->streams[streamIndex].offset != vertexOffset || state->streams[streamIndex].stride != vertexStride);

  state->streams[streamIndex].vb = vb;
  state->streams[streamIndex].offset = vertexOffset;
  state->streams[streamIndex].stride = vertexStride;
  
  D3DCALL(device->SetStreamSource(streamIndex, vb, vertexOffset, vertexStride));
}

void R_ChangeIndices(GfxCmdBufPrimState *state, D3DIndexBuffer *ib)
{
  D3DDevice *device;

  assert(ib != state->indexBuffer);

  state->indexBuffer = ib;
  device = state->device;
  assert(device);

  D3DCALL(device->SetIndices( ib ));

}

void R_HW_DisableSampler(D3DDevice *device, unsigned int samplerIndex)
{
  D3DCALL(device->SetTexture( samplerIndex, 0 ));
}

void R_DisableSampler(GfxCmdBufState *state, unsigned int samplerIndex)
{
  state->samplerTexture[samplerIndex] = 0;
  R_HW_DisableSampler(state->prim.device, samplerIndex);
}

void R_UnbindImage(GfxCmdBufState *state, GfxImage *image)
{
  unsigned int samplerIndex;
  unsigned int maxTextureMaps;

  maxTextureMaps = vidConfig.maxTextureMaps;
  for ( samplerIndex = 0; samplerIndex < maxTextureMaps; ++samplerIndex )
  {
    if ( (GfxImage *)state->samplerTexture[samplerIndex] == image )
    {
      R_DisableSampler(state, samplerIndex);
    }
  }
}

#ifdef BLACKOPS   
void R_UpdateStatsTarget(GfxCmdBufContext context)
{
  context.state->prim.viewStats = context.state->prim.frameStats.viewStats;
}
#endif

#define GFXS0_ATEST_DISABLE 0x800
#define GFXS0_CULL_MASK 0xC000
#define GFXS0_CULL_SHIFT 14
#define GFXS0_CULL_NONE 0x4000
#define GFXS0_CULL_FRONT 0xC000
#define GFXS0_CULL_BACK 0x8000
#define GFXS0_POLYMODE_LINE 0x80000000
#define GFXS0_BLENDOP_RGB_SHIFT 8
#define GFXS_BLENDOP_MASK 0x7
#define GFXS_BLENDOP_DISABLED 0x7
#define GFXS0_BLENDOP_ALPHA_MASK 0x7000000
#define GFXS0_SRCBLEND_RGB_SHIFT 0
#define GFXS_BLEND_MASK 0xF
#define GFXS0_DSTBLEND_RGB_SHIFT 4
#define GFXS0_BLENDOP_ALPHA_SHIFT 24
#define GFXS0_SRCBLEND_ALPHA_SHIFT 16
#define GFXS0_DSTBLEND_ALPHA_SHIFT 20
#define GFXS1_DEPTHWRITE 1
#define GFXS1_DEPTHTEST_DISABLE 2
#define GFXS1_DEPTHTEST_SHIFT 2
#define GFXS1_DEPTHTEST_MASK 0xC
#define GFXS1_POLYGON_OFFSET_SHADOWMAP 48
#define GFXS0_ATEST_MASK 0x3000
#define GFXS0_ATEST_GE_128 0x3000
#define GFXS1_STENCIL_BACK_ENABLE 0x80
#define GFXS1_STENCIL_FRONT_ENABLE 0x40


float shadowmapClearColor[4] = {  1.0,  1.0,  1.0,  1.0 };
const unsigned int s_cullTable[] = { 0u, 1u, 3u, 2u };
const unsigned int s_blendTable[] = { 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u };
const unsigned int s_blendOpTable[] = { 0u, 1u, 2u, 3u, 4u, 5u };
const unsigned int s_depthTestTable[] = { 8u, 2u, 3u, 4u };
const unsigned int s_stencilOpTable[] = { 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u };
const unsigned int s_stencilFuncTable[] = { 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u };




void R_HW_SetColorMask(D3DDevice *device, unsigned int stateBits0)
{
  int mask = 0;
  if(stateBits0 & 0x8000000)
  {
    mask |= 7;
  }
  if(stateBits0 & 0x10000000)
  {
    mask |= 8;
  }

  D3DCALL(device->SetRenderState( D3DRS_COLORWRITEENABLE, mask ));

}


void R_HW_SetAlphaTestEnable(D3DDevice *device, unsigned int stateBits0)
{
  D3DCALL(device->SetRenderState( D3DRS_ALPHATESTENABLE, (stateBits0 & GFXS0_ATEST_DISABLE) ? 0 : 1 ));
}

void R_HW_SetCullFace(D3DDevice *device, unsigned int stateBits0)
{
  assert((stateBits0 & GFXS0_CULL_MASK) == GFXS0_CULL_NONE || (stateBits0 & GFXS0_CULL_MASK) == GFXS0_CULL_FRONT || (stateBits0 & GFXS0_CULL_MASK) == GFXS0_CULL_BACK);
  D3DCALL(device->SetRenderState( D3DRS_CULLMODE, s_cullTable[(stateBits0 & GFXS0_CULL_MASK) >> GFXS0_CULL_SHIFT] ));

}



void R_HW_SetPolygonMode(D3DDevice *device, unsigned int stateBits0)
{
  D3DCALL(device->SetRenderState( D3DRS_FILLMODE, (stateBits0 & GFXS0_POLYMODE_LINE) ? D3DFILL_WIREFRAME : D3DFILL_SOLID ));
}


void R_HW_SetBlend(D3DDevice *device, bool blendWasEnabled, unsigned int changedBits, unsigned int stateBits0)
{

  if ( !blendWasEnabled )
  {
    D3DCALL(device->SetRenderState( D3DRS_ALPHABLENDENABLE, 1 ));
  }
  if ( (changedBits >> GFXS0_BLENDOP_RGB_SHIFT) & GFXS_BLENDOP_MASK )
  {
    D3DCALL(device->SetRenderState( D3DRS_BLENDOP, s_blendOpTable[(stateBits0 >> GFXS0_BLENDOP_RGB_SHIFT) & GFXS_BLENDOP_MASK] ));
  }
  if ( (changedBits >> GFXS0_SRCBLEND_RGB_SHIFT) & GFXS_BLEND_MASK )
  {
    D3DCALL(device->SetRenderState( D3DRS_SRCBLEND, s_blendTable[(stateBits0 >> GFXS0_SRCBLEND_RGB_SHIFT) & GFXS_BLEND_MASK] ));
  }
  if ( (changedBits >> GFXS0_DSTBLEND_RGB_SHIFT) & GFXS_BLEND_MASK )
  {
    D3DCALL(device->SetRenderState( D3DRS_DESTBLEND, s_blendTable[(stateBits0 >> GFXS0_DSTBLEND_RGB_SHIFT) & GFXS_BLEND_MASK] ));
  }
  if ( (changedBits >> GFXS0_BLENDOP_ALPHA_SHIFT) & GFXS_BLENDOP_MASK )
  {
    D3DCALL(device->SetRenderState( D3DRS_BLENDOPALPHA, s_blendOpTable[(stateBits0 >> GFXS0_BLENDOP_ALPHA_SHIFT) & GFXS_BLENDOP_MASK] ));
  }
  if ( (changedBits >> GFXS0_SRCBLEND_ALPHA_SHIFT) & GFXS_BLEND_MASK )
  {
    D3DCALL(device->SetRenderState( D3DRS_SRCBLENDALPHA, s_blendTable[(stateBits0 >> GFXS0_SRCBLEND_ALPHA_SHIFT) & GFXS_BLEND_MASK] ));
  }

  if ( (changedBits >> GFXS0_DSTBLEND_ALPHA_SHIFT) & GFXS_BLEND_MASK )
  {
    D3DCALL(device->SetRenderState( D3DRS_DESTBLENDALPHA, s_blendTable[(stateBits0 >> GFXS0_DSTBLEND_ALPHA_SHIFT) & GFXS_BLEND_MASK] ));
  }
}

void R_HW_DisableBlend(D3DDevice *device)
{
  D3DCALL(device->SetRenderState( D3DRS_ALPHABLENDENABLE, 0 ));
}

void R_HW_SetDepthWriteEnable(D3DDevice *device, unsigned int stateBits1)
{
  D3DCALL(device->SetRenderState(D3DRS_ZWRITEENABLE, (stateBits1 & GFXS1_DEPTHWRITE) ? 1 : 0));
}

void R_HW_SetDepthTestEnable(D3DDevice *device, unsigned int stateBits1)
{
  D3DCALL(device->SetRenderState(D3DRS_ZENABLE, (stateBits1 & GFXS1_DEPTHTEST_DISABLE) ? D3DZB_FALSE : D3DZB_TRUE));
}

void R_HW_SetDepthTestFunction(D3DDevice *device, unsigned int stateBits1)
{
  D3DCALL(device->SetRenderState( D3DRS_ZFUNC, s_depthTestTable[(stateBits1 & GFXS1_DEPTHTEST_MASK) >> GFXS1_DEPTHTEST_SHIFT] ));
}

void R_HW_SetPolygonOffset(D3DDevice *device, float scale, float bias)
{
  if ( gfxMetrics.slopeScaleDepthBias )
  {
    D3DCALL(device->SetRenderState( D3DRS_SLOPESCALEDEPTHBIAS, FloatAsInt( &scale ) ));
  }
  else
  {
    bias = bias * 2.0;
  }
  D3DCALL(device->SetRenderState( D3DRS_DEPTHBIAS, FloatAsInt( &bias ) ));
}

void R_HW_EnableStencil(D3DDevice *device)
{
  D3DCALL(device->SetRenderState( D3DRS_STENCILENABLE, 1 ));
}

void R_HW_DisableStencil(D3DDevice *device)
{
  D3DCALL(device->SetRenderState( D3DRS_STENCILENABLE, 0 ));
}

void R_HW_SetFrontStencilOp(D3DDevice *device, unsigned int stencilOpPass, unsigned int stencilOpFail, unsigned int stencilOpZFail)
{
  D3DCALL(device->SetRenderState( D3DRS_STENCILPASS, s_stencilOpTable[stencilOpPass] ));
  D3DCALL(device->SetRenderState( D3DRS_STENCILFAIL, s_stencilOpTable[stencilOpFail] ));
  D3DCALL(device->SetRenderState( D3DRS_STENCILZFAIL, s_stencilOpTable[stencilOpZFail] ));
}

void R_HW_SetBackStencilOp(D3DDevice *device, unsigned int stencilOpPass, unsigned int stencilOpFail, unsigned int stencilOpZFail)
{
  D3DCALL(device->SetRenderState( D3DRS_CCW_STENCILPASS, s_stencilOpTable[stencilOpPass] ));
  D3DCALL(device->SetRenderState( D3DRS_CCW_STENCILFAIL, s_stencilOpTable[stencilOpFail] ));
  D3DCALL(device->SetRenderState( D3DRS_CCW_STENCILZFAIL, s_stencilOpTable[stencilOpZFail] ));
}

void R_HW_SetFrontStencilFunc(D3DDevice *device, unsigned int stencilFunc)
{
  D3DCALL(device->SetRenderState( D3DRS_STENCILFUNC, s_stencilFuncTable[stencilFunc] ));
}

void R_HW_SetBackStencilFunc(D3DDevice *device, unsigned int stencilFunc)
{
  D3DCALL(device->SetRenderState( D3DRS_CCW_STENCILFUNC, s_stencilFuncTable[stencilFunc] ));
}

void R_HW_SetViewport(D3DDevice *device, const GfxViewport *viewport, float nearValue, float farValue)
{
  D3DVIEWPORT9 d3dViewport;

  d3dViewport.X = viewport->x;
  d3dViewport.Y = viewport->y;
  d3dViewport.Width = viewport->width;
  d3dViewport.Height = viewport->height;
  d3dViewport.MinZ = nearValue;
  d3dViewport.MaxZ = farValue;

  assert(d3dViewport.MinZ < d3dViewport.MaxZ);

  D3DCALL(device->SetViewport( &d3dViewport ));
}

void R_HW_SetSamplerTexture(D3DDevice *device, unsigned int samplerIndex, const GfxTexture *texture)
{
  D3DCALL(device->SetTexture( samplerIndex, texture->basemap ));
}



unsigned int R_HW_SetSamplerState(D3DDevice *device, unsigned int samplerIndex, unsigned int samplerState, unsigned int oldSamplerState)
{
    unsigned int finalSamplerState;
    unsigned int diffSamplerState;

    finalSamplerState = samplerState;
    diffSamplerState = oldSamplerState ^ samplerState;

    assert(diffSamplerState);

    if ( diffSamplerState & 0xF00 )
    {
      unsigned int minFilter = (samplerState & 0xF00) >> 8;
      D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_MINFILTER, minFilter ));
    }
    if ( diffSamplerState & 0xF000 )
    {
      unsigned int magFilter = (samplerState & 0xF000) >> 12;
      D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_MAGFILTER, magFilter ));
    }
    if ( diffSamplerState & 0xFF )
    {
      unsigned int anisotropy = samplerState & 0xFF;
      if ( anisotropy <= 1 )
      {
        finalSamplerState = (oldSamplerState & 0xFF) | (samplerState & 0xFFFFFF00);
      }
      else
      {
        D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_MAXANISOTROPY, anisotropy ));
      }
    }
    if ( diffSamplerState & 0xF0000 )
    {
      unsigned int mipFilter = (samplerState & 0xF0000) >> 16;
      D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_MIPFILTER, mipFilter ));
    }
    if ( diffSamplerState & 0x3F00000 )
    {
        if ( diffSamplerState & 0x300000 )
        {
          unsigned int address = (samplerState & 0x300000) >> 20;
          D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_ADDRESSU, address ));
        }

        if ( diffSamplerState & 0xC00000 )
        {
          unsigned int address = (samplerState & 0xC00000) >> 22;
          D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_ADDRESSV, address ));
        }
        if ( diffSamplerState & 0x3000000 )
        {
          unsigned int address = (samplerState & 0x3000000) >> 24;
          D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_ADDRESSW, address ));
        }
    }
    return finalSamplerState;
}




void R_SetAlphaAntiAliasingState(IDirect3DDevice9 *device, int stateBits0)
{
  DWORD aaAlphaFormat;

  if ( (stateBits0 >> GFXS0_SRCBLEND_ALPHA_SHIFT) & GFXS_BLEND_MASK )
  {
    aaAlphaFormat = 0;
  }
  else if ( r_aaAlpha->current.integer == 2 )
  {
    aaAlphaFormat = (D3DFORMAT)MAKEFOURCC('S', 'S', 'A', 'A');
  }
  else
  {
    aaAlphaFormat = (D3DFORMAT)MAKEFOURCC('A', 'T', 'O', 'C');
  }
  D3DCALL(device->SetRenderState( D3DRS_ADAPTIVETESS_Y, aaAlphaFormat ));
}


void R_SetAlphaTestFunction(GfxCmdBufState *state, unsigned int stateBits0)
{
  uint8_t ref;
  D3DDevice *device;
  unsigned int function;

  if ( (stateBits0 & GFXS0_ATEST_MASK) == 0x1000 )
  {
    function = 5;
    ref = 0;
  }
  else if ( (stateBits0 & GFXS0_ATEST_MASK) == 0x2000 )
  {
#ifdef BLACKOPS    
    function = 7;
    ref = 255;
#else
    function = 2;
    ref = 128;
#endif
  }
  else
  {
    assert((stateBits0 & GFXS0_ATEST_MASK) == GFXS0_ATEST_GE_128);
    function = 7;
    ref = 128;
  }
  device = state->prim.device;

  assert(device);

  D3DCALL(device->SetRenderState( D3DRS_ALPHAFUNC, function ));

  if ( state->alphaRef != ref )
  {
    D3DCALL(device->SetRenderState( D3DRS_ALPHAREF, ref ));
    state->alphaRef = ref;
  }
}


void R_ForceSetPolygonOffset(D3DDevice *device, unsigned int stateBits1)
{
  unsigned int offset;
  float bias;
  float scale;

  offset = stateBits1 & 0x30;
  if ( offset == GFXS1_POLYGON_OFFSET_SHADOWMAP )
  {
    bias = sm_polygonOffsetBias->current.value * 0.000015258789;
    scale = sm_polygonOffsetScale->current.value;
  }
  else
  {
    assert(offset != GFXS1_POLYGON_OFFSET_SHADOWMAP);

    offset >>= 4;
    bias = (double)offset * r_polygonOffsetBias->current.value * 0.000015258789;
    scale = (double)offset * r_polygonOffsetScale->current.value;
  }
  R_HW_SetPolygonOffset(device, scale, bias);
}


void R_ForceSetBlendState(D3DDevice *device, unsigned int stateBits0)
{
  if ( (stateBits0 >> GFXS0_SRCBLEND_ALPHA_SHIFT) & GFXS_BLENDOP_MASK )
  {
    R_HW_SetBlend(device, 0, 0xFFFFFFFF, stateBits0);
  }
  else
  {
    R_HW_DisableBlend(device);
  }
}


void R_ForceSetStencilState(D3DDevice *device, unsigned int stateBits1)
{
  if ( stateBits1 & 0x40 )
  {
    R_HW_EnableStencil(device);
  }
  else
  {
    R_HW_DisableStencil(device);
#pragma msg "Enable me maybe, cod4 has this enabled"    
    //return;
  }
  if ( !(stateBits1 & 0x80) )
  {
    stateBits1 = (stateBits1 & 0xFFFFF) | ((stateBits1 & 0xFFF00) << 12);
  }
  R_HW_SetFrontStencilOp(device, (stateBits1 >> 8) & 7, (stateBits1 >> 11) & 7, (stateBits1 >> 14) & 7);
  R_HW_SetBackStencilOp(device, (stateBits1 >> 20) & 7, (stateBits1 >> 23) & 7, (stateBits1 >> 26) & 7);
  R_HW_SetFrontStencilFunc(device, (stateBits1 >> 17) & 7);
  R_HW_SetBackStencilFunc(device, stateBits1 >> 29);
}

void R_SetCompleteState(D3DDevice *device, const unsigned int *stateBits)
{
  assert(device);

  R_HW_SetColorMask(device, *stateBits);
  R_HW_SetAlphaTestEnable(device, *stateBits);

  assert(stateBits[0] & GFXS0_ATEST_DISABLE);

  R_HW_SetCullFace(device, stateBits[0]);
  R_HW_SetPolygonMode(device, stateBits[0]);
  R_ForceSetBlendState(device, stateBits[0]);
  R_HW_SetDepthWriteEnable(device, stateBits[1]);
  R_HW_SetDepthTestEnable(device, stateBits[1]);
  R_HW_SetDepthTestFunction(device, stateBits[1]);
  R_ForceSetPolygonOffset(device, stateBits[1]);
  R_ForceSetStencilState(device, stateBits[1]);

}


void R_ChangeState_0(GfxCmdBufState *state, unsigned int stateBits0)
{
  bool blendOpRgbWasEnabled;
  unsigned int changedBits;
  D3DDevice *device;

  changedBits = state->activeStateBits[0] ^ stateBits0;
  if ( changedBits || (state->refStateBits[0] ^ stateBits0) & 0x7000700 )
  {
    if ( r_logFile->current.integer )
    {
      RB_LogPrintState_0(stateBits0, changedBits);
    }

    assert(r_dx.d3d9 && r_dx.device);
    
    device = state->prim.device;

    assert(device);

    if ( changedBits & 0x18000000 )
    {
      R_HW_SetColorMask(device, stateBits0);
    }
/*    
    if ( !(state->stateOverride & 0x40000000) )
    {
*/
      if ( changedBits & GFXS0_ATEST_DISABLE )
      {
        R_HW_SetAlphaTestEnable(state->prim.device, stateBits0);
      }
      if ( stateBits0 & GFXS0_ATEST_DISABLE )
      {
        assert((stateBits0 & GFXS0_ATEST_MASK) == 0);

        stateBits0 |= state->activeStateBits[0] & GFXS0_ATEST_MASK;
        changedBits &= ~GFXS0_ATEST_MASK;

        assert((stateBits0 ^ state->activeStateBits[0]) == (unsigned)changedBits);
      }
      if ( changedBits & GFXS0_ATEST_MASK )
      {
        R_SetAlphaTestFunction(state, stateBits0);
      }
/*
    }
*/
    if ( changedBits & GFXS0_CULL_MASK )
    {
      R_HW_SetCullFace(device, stateBits0);
    }
    if ( changedBits & GFXS0_POLYMODE_LINE )
    {
      R_HW_SetPolygonMode(device, stateBits0);
    }


    blendOpRgbWasEnabled = ((state->refStateBits[0] >> GFXS0_BLENDOP_RGB_SHIFT) & GFXS_BLENDOP_MASK) != 0;
    if ( (stateBits0 >> GFXS0_BLENDOP_RGB_SHIFT) & GFXS_BLENDOP_MASK )
    {
      if ( !((stateBits0 >> GFXS0_BLENDOP_ALPHA_SHIFT) & GFXS_BLENDOP_MASK) )
      {

        stateBits0 = (stateBits0 & ~(0x7FF << GFXS0_SRCBLEND_ALPHA_SHIFT)) | ((stateBits0 & 0x7FF) << GFXS0_SRCBLEND_ALPHA_SHIFT);
        changedBits = (changedBits & ~(0x7FF << GFXS0_SRCBLEND_ALPHA_SHIFT)) | ((state->activeStateBits[0] ^ stateBits0) & (0x7FF << GFXS0_SRCBLEND_ALPHA_SHIFT));

        assert((stateBits0 ^ state->activeStateBits[0]) == changedBits);

      }
      R_HW_SetBlend(device, blendOpRgbWasEnabled, changedBits, stateBits0);
    }
    else
    {
      assert(!(stateBits0 & GFXS0_BLENDOP_ALPHA_MASK) ); //originally (stateBits0 & GFXS0_BLENDOP_ALPHA_MASK) == (GFXS_BLENDOP_DISABLED << GFXS0_BLENDOP_ALPHA_SHIFT) //constants seem to be incorrect to evaluate to the original expression

      stateBits0 = (stateBits0 & ~0x7FF07FFu) | (state->activeStateBits[0] & 0x7FF07FF);

      changedBits &= ~0x7FF07FFu;

      assert((stateBits0 ^ state->activeStateBits[0]) == changedBits);

      if ( blendOpRgbWasEnabled )
      {
        R_HW_DisableBlend(device);
      }
    }
    if ( gfxMetrics.hasTransparencyMsaa )
    {
      if ( r_aaAlpha->current.integer )
      {
        if ( changedBits & (GFXS_BLEND_MASK << GFXS0_BLENDOP_RGB_SHIFT))
        {
          R_SetAlphaAntiAliasingState(device, stateBits0);
        }
      }
    }
    state->activeStateBits[0] = stateBits0;
  }
}





void R_ChangeState_1(GfxCmdBufState *state, unsigned int stateBits1)
{
  unsigned int changedBits;
  D3DDevice *device;

  changedBits = state->activeStateBits[1] ^ stateBits1;
  if ( changedBits )
  {
    assert((!(stateBits1 & GFXS1_STENCIL_BACK_ENABLE)) | (stateBits1 & GFXS1_STENCIL_FRONT_ENABLE));

    if ( r_logFile->current.integer )
    {
      RB_LogPrintState_1(stateBits1, changedBits);
    }

    assert(r_dx.d3d9 && r_dx.device);

    device = state->prim.device;

    assert(device);
/*
    if ( state->stateOverride >= 0 )
    {
*/
      if ( changedBits & GFXS1_DEPTHWRITE )
      {
        R_HW_SetDepthWriteEnable(device, stateBits1);
      }
      if ( changedBits & GFXS1_DEPTHTEST_DISABLE )
      {
        R_HW_SetDepthTestEnable(device, stateBits1);
      }
      if ( stateBits1 & GFXS1_DEPTHTEST_DISABLE )
      {
        assert((stateBits1 & GFXS1_DEPTHTEST_MASK) == 0);

        stateBits1 |= state->activeStateBits[1] & GFXS1_DEPTHTEST_MASK;
        changedBits &= ~GFXS1_DEPTHTEST_MASK;

        assert((stateBits1 ^ state->activeStateBits[1]) == changedBits);
      }
      if ( changedBits & GFXS1_DEPTHTEST_MASK )
      {
        R_HW_SetDepthTestFunction(device, stateBits1);
      }
/*
    }
    
*/  
    if ( changedBits & GFXS1_POLYGON_OFFSET_SHADOWMAP )
    {
      R_ForceSetPolygonOffset(device, stateBits1);
    }
    if ( stateBits1 & GFXS1_STENCIL_FRONT_ENABLE )
    {
      if ( changedBits & GFXS1_STENCIL_FRONT_ENABLE )
      {
        R_HW_EnableStencil(device);
      }
    }
    else
    {
      if ( changedBits & GFXS1_STENCIL_FRONT_ENABLE )
      {
        R_HW_DisableStencil(device);
      }
      stateBits1 = (stateBits1 & 0x7F) | (state->activeStateBits[1] & 0xFFFFFF80);
      changedBits &= 0x7Fu;
    }
    if ( !(stateBits1 & GFXS1_STENCIL_BACK_ENABLE) )
    {
      stateBits1 = (stateBits1 & 0xFFFFF) | ((stateBits1 & 0xFFF00) << 12);
      changedBits = state->activeStateBits[1] ^ stateBits1;
    }
    if ( changedBits & 0x1FF00 )
    {
      R_HW_SetFrontStencilOp(device, (stateBits1 >> GFXS0_BLENDOP_RGB_SHIFT) & GFXS_BLENDOP_MASK, (stateBits1 >> 11) & GFXS_BLENDOP_MASK, (stateBits1 >> GFXS0_CULL_SHIFT) & GFXS_BLENDOP_MASK);
    }
    if ( (0x3800000 | 0x700000 | 0x1C000000) & changedBits )
    {
      R_HW_SetBackStencilOp(device, (stateBits1 >> GFXS0_DSTBLEND_ALPHA_SHIFT) & GFXS_BLENDOP_MASK, (stateBits1 >> 23) & GFXS_BLENDOP_MASK, (stateBits1 >> 26) & GFXS_BLENDOP_MASK);
    }
    if ( changedBits & 0xE0000 )
    {
      R_HW_SetFrontStencilFunc(device, (stateBits1 >> 17) & GFXS_BLENDOP_MASK);
    }
    if ( changedBits & 0xE0000000 )
    {
      R_HW_SetBackStencilFunc(device, stateBits1 >> 29);
    }
    state->activeStateBits[1] = stateBits1;
  }
}



void R_SetViewport(GfxCmdBufState *state, const GfxViewport *viewport)
{
  _RB_LogPrintf("Viewport at (%i, %i) with size %i x %i\n", viewport->x, viewport->y, viewport->width, viewport->height);
  assert(viewport->x >= 0);
  assert(viewport->y >= 0);
  assert(viewport->width > 0);
  assert(viewport->height > 0);

  if ( viewport->x != state->viewport.x || viewport->y != state->viewport.y || viewport->width != state->viewport.width || viewport->height != state->viewport.height )
  {
    state->viewport = *viewport;
    R_HW_SetViewport(state->prim.device, viewport, state->depthRangeNear, state->depthRangeFar);
  }
}


void R_SetMeshStream(GfxCmdBufState *state, GfxMeshData *mesh)
{
  R_SetStreamSource(&state->prim, mesh->vb.buffer, 0, mesh->vertSize);
}


void R_ChangeDepthRange(GfxCmdBufState *state, GfxDepthRangeType depthRangeType)
{
  D3DDevice *device;

  assert(state->depthRangeType != depthRangeType);

  state->depthRangeType = depthRangeType;
  if ( depthRangeType )
  {
    state->depthRangeNear = 0.0;
    state->depthRangeFar = 0.015625;
  }
  else
  {
    state->depthRangeNear = 0.015625;
    state->depthRangeFar = 1.0;
  }

  device = state->prim.device;
  assert(device);

  R_HW_SetViewport(device, &state->viewport, state->depthRangeNear, state->depthRangeFar);
}


void R_ClearAllStreamSources(GfxCmdBufPrimState *state)
{
  if ( state->streams[0].vb || state->streams[0].offset || state->streams[0].stride )
  {
    R_ChangeStreamSource(state, 0, 0, 0, 0);
  }
  if ( state->streams[1].vb || state->streams[1].offset || state->streams[1].stride )
  {
    R_ChangeStreamSource(state, 1, 0, 0, 0);
  }
#ifdef BLACKOPS
  if ( state->streams[2].vb || state->streams[2].offset || state->streams[2].stride )
  {
    R_ChangeStreamSource(state, 2, 0, 0, 0);
  }
#endif
}


void R_ChangeObjectPlacementRemote(GfxCmdBufSourceState *source, GfxScaledPlacement *remotePlacement)
{
  R_ChangeObjectPlacement(source, remotePlacement);
}

void R_ClearScreenInternal(D3DDevice *device, unsigned char whichToClear, const float *color, float depth, unsigned char stencil, const GfxViewport *viewport)
{
  D3DRECT rect;
  GfxColor nativeColor;

  assert(device);

  _RB_LogPrintf("---------- R_ClearScreenInternal\n");
  _RB_LogPrintf("---------- (%c) color %g %g %g %g\n", (whichToClear & 1) != 0 ? '*' : ' ', color[0], color[1], color[2], color[3]);
  _RB_LogPrintf("---------- (%c) depth %g\n", (whichToClear & 2) != 0 ? '*' : ' ', depth);
  _RB_LogPrintf("---------- (%c) stencil %i\n", (whichToClear & 4) != 0 ? '*' : ' ', (uint8_t)stencil);

  assert(whichToClear);
  assert(color);
  assert(depth >= 0.0 || depth <= 1.0);

  Byte4PackPixelColor(color, nativeColor.array);
  if ( viewport )
  {
    rect.x1 = viewport->x;
    rect.x2 = viewport->width + rect.x1;
    rect.y1 = viewport->y;
    rect.y2 = viewport->height + rect.y1;

    D3DCALL(device->Clear( 1, &rect, whichToClear, nativeColor.packed, depth, stencil ));
  }
  else
  {
    D3DCALL(device->Clear( 0, 0, whichToClear, nativeColor.packed, depth, stencil ));
  }
}



void R_SetSampler(GfxCmdBufContext context, unsigned int samplerIndex, unsigned char samplerState, const GfxImage *image)
{
    unsigned int decodedSamplerState;
    assert(image);

    if ( context.state->samplerTexture[samplerIndex] != &image->texture )
    {
        context.state->samplerTexture[samplerIndex] = &image->texture;
        _RB_LogPrintf("---------- texture %i: %s\n", samplerIndex, image->name);
        R_HW_SetSamplerTexture(context.state->prim.device, samplerIndex, &image->texture);
    }
    assert((samplerState & (SAMPLER_FILTER_MASK | SAMPLER_MIPMAP_MASK)) != 0);

    if ( context.state->refSamplerState[samplerIndex] != samplerState )
    {
        context.state->refSamplerState[samplerIndex] = samplerState;
        decodedSamplerState = R_DecodeSamplerState(samplerState);
        if ( context.state->samplerState[samplerIndex] != decodedSamplerState )
        {
            context.state->samplerState[samplerIndex] = R_HW_SetSamplerState(context.state->prim.device, samplerIndex, decodedSamplerState, context.state->samplerState[samplerIndex]);
        }
    }
}


void R_UpdateViewport(GfxCmdBufSourceState *source, GfxViewport *viewport)
{
  float invWidth;
  float invHeight;
  float lookupScale[2];
  float lookupOffset[2];

  assert(source);
  assert(source->viewMode != VIEW_MODE_NONE);
  assert(source->renderTargetWidth > 0 && source->renderTargetHeight > 0);

  source->viewportIsDirty = false;

  invWidth = 1.0 / (float)source->renderTargetWidth;
  invHeight = 1.0 / (float)source->renderTargetHeight;
  lookupScale[0] = 0.5 * ((float)viewport->width * invWidth);
  lookupScale[1] = 0.5 * ((float)viewport->height * invHeight);
  lookupOffset[0] = (0.5 * invWidth) + (lookupScale[0] + ((float)viewport->x * invWidth));
  lookupOffset[1] = (0.5 * invHeight) + (lookupScale[1] + ((float)viewport->y * invHeight));

  vec4_t codeconst = {(float)source->renderTargetWidth, (float)source->renderTargetHeight, invWidth, invHeight};
  R_SetCodeConstantFromVec4(source, CONST_SRC_CODE_RENDER_TARGET_SIZE, codeconst);

  vec4_t codeconst2 = {lookupScale[0], -lookupScale[1], 0.0, 1.0};
  R_SetCodeConstantFromVec4(source, CONST_SRC_CODE_CLIP_SPACE_LOOKUP_SCALE, codeconst2);

  vec4_t codeconst3 = {lookupOffset[0], lookupOffset[1], 0.0, 0.0};
  R_SetCodeConstantFromVec4(source, CONST_SRC_CODE_CLIP_SPACE_LOOKUP_OFFSET, codeconst3);
}

void R_SetLightmap(GfxCmdBufContext context, unsigned int lmapIndex)
{
    MaterialPass *pass;
    GfxImage *overrideImage;
    assert(rgp.world);

    pass = context.state->pass;
    if ( lmapIndex == 31 )
    {
      return;
    }
    else
    {
        if ( r_lightMap->current.integer == 1 )
        {
            if ( pass->customSamplerFlags & 2 )
            {
                if ( context.source->input.data->prim.hasSunDirChanged )
                {
                    R_SetSampler(context, 2u, 98, rgp.whiteImage);
                }
                else
                {
                    R_SetSampler(context, 2u, 98, rgp.world->lightmaps[lmapIndex].primary);
                }
            }
            if ( pass->customSamplerFlags & 4 )
            {
                R_SetSampler(context, 3u, 98, rgp.world->lightmaps[lmapIndex].secondary);
            }
            /*
            if ( pass->customSamplerFlags & 8 )
            {
                R_SetSampler(context, 14u, 98, rgp.world->lightmaps[lmapIndex].secondaryB);
            }
            */
        }
        else
        {
            if(r_lightMap->current.integer == 2)
            {
              overrideImage = rgp.whiteImage;
            }else if(r_lightMap->current.integer == 0){
              overrideImage = rgp.blackImage;
            }else{
              overrideImage = rgp.grayImage;
            }
            if ( pass->customSamplerFlags & 2 )
            {
                R_SetSampler(context, 2u, 98, overrideImage);
            }
            if ( pass->customSamplerFlags & 4 )
            {
                R_SetSampler(context, 3u, 98, overrideImage);
            }
            /*
            if ( pass->customSamplerFlags & 8 )
            {
                R_SetSampler(context, 4u, 98, rgp.g16r16Image);
            }
            */
        }
    }
}

#define REFLECTION_PROBE_INVALID 255

void R_SetReflectionProbe(GfxCmdBufContext context, unsigned int reflectionProbeIndex)
{
  assert(rgp.world);
  assert(reflectionProbeIndex != REFLECTION_PROBE_INVALID);
  assert(reflectionProbeIndex < rgp.world->reflectionProbeCount);
  assert(rgp.world->reflectionProbes[reflectionProbeIndex].reflectionImage);

  if ( context.state->pass->customSamplerFlags & 1 )
  {
    R_SetSampler(context, 1u, 114, rgp.world->reflectionProbes[reflectionProbeIndex].reflectionImage);
  }
}


GfxImage * R_GetTextureFromCode(GfxCmdBufSourceState *source, unsigned int codeTexture, char *samplerState)
{
    assert(codeTexture < TEXTURE_SRC_CODE_COUNT);
    assert(source);

    *samplerState = source->input.codeImageSamplerStates[codeTexture];

    assert(*samplerState & SAMPLER_FILTER_MASK);

    return source->input.codeImages[codeTexture];
}

#if 0
float *R_GetCodeMatrix(GfxCmdBufSourceState *source, unsigned int sourceIndex, unsigned int firstRow)
{
    float *result; // eax
    unsigned int baseIndex; // [esp+10Ch] [ebp-18h]
    int transposeIndex; // [esp+110h] [ebp-14h]
    unsigned int matrixIndex; // [esp+118h] [ebp-Ch]
    int inverseIndex; // [esp+11Ch] [ebp-8h]
    unsigned int matrixVersion; // [esp+120h] [ebp-4h]


    assert(source->matrixVersions[(((sourceIndex) - CONST_SRC_FIRST_CODE_MATRIX) >> 2)]);

    assert(firstRow <= 3);

    matrixVersion = source->matrixVersions[(sourceIndex - CONST_SRC_FIRST_CODE_MATRIX) >> 2];
    matrixIndex = sourceIndex - CONST_SRC_FIRST_CODE_MATRIX;
    if ( source->constVersions[sourceIndex] == matrixVersion )
    {
        return (float *)((char *)source + 64 * matrixIndex + 16 * firstRow);
    }
    baseIndex = matrixIndex & 0xFFFFFFFC;
    if ( source->constVersions[(matrixIndex & 0xFFFFFFFC) + CONST_SRC_FIRST_CODE_MATRIX] != matrixVersion )
    {
        R_DeriveCodeMatrix(source, &source->matrices, baseIndex);
        if ( matrixIndex == baseIndex )
        {
            return (float *)((char *)source + 64 * matrixIndex + 16 * firstRow);
        }
        assert(source->constVersions[sourceIndex] != matrixVersion);
    }
    source->constVersions[sourceIndex] = matrixVersion;
    transposeIndex = matrixIndex ^ 2;
    if ( source->constVersions[(matrixIndex ^ 2) + CONST_SRC_FIRST_CODE_MATRIX] == matrixVersion )
    {
        MatrixTranspose44((const float *)&source->matrices.matrix[transposeIndex], (float *)&source->matrices.matrix[matrixIndex]);
        result = source->matrices.matrix[matrixIndex].m[firstRow];
    }
    else
    {
        inverseIndex = matrixIndex ^ 1;
        if ( source->constVersions[(matrixIndex ^ 1) + CONST_SRC_FIRST_CODE_MATRIX] == matrixVersion )
        {
            MatrixInverse44((const float *)&source->matrices.matrix[inverseIndex], (float *)&source->matrices.matrix[matrixIndex]);
            result = source->matrices.matrix[matrixIndex].m[firstRow];
        }
        else
        {
            assert(matrixIndex == (baseIndex | CONST_SRC_MATRIX_INVERSE_BIT | CONST_SRC_MATRIX_TRANSPOSE_BIT));
            assert(transposeIndex == (baseIndex | CONST_SRC_MATRIX_INVERSE_BIT));
            assert(inverseIndex == (baseIndex | CONST_SRC_MATRIX_TRANSPOSE_BIT));

            MatrixTranspose44((const float *)&source->matrices.matrix[baseIndex], (float *)&source->matrices.matrix[inverseIndex]);
            source->constVersions[inverseIndex + 197] = matrixVersion;
            MatrixInverse44((const float *)&source->matrices.matrix[inverseIndex], (float *)&source->matrices.matrix[matrixIndex]);
            result = source->matrices.matrix[matrixIndex].m[firstRow];
        }
    }
    return result;
}
#endif


void R_SetSamplerState(GfxCmdBufState *state, unsigned int samplerIndex, uint8_t samplerState)
{
  unsigned int decodedSamplerState;

  state->samplerTexture[samplerIndex] = 0;
  assert((samplerState & (SAMPLER_FILTER_MASK | SAMPLER_MIPMAP_MASK)) != 0);

  if ( state->refSamplerState[samplerIndex] != samplerState )
  {
    state->refSamplerState[samplerIndex] = samplerState;
    decodedSamplerState = R_DecodeSamplerState(samplerState);
    if ( state->samplerState[samplerIndex] != decodedSamplerState )
    {
      state->samplerState[samplerIndex] = R_HW_SetSamplerState(state->prim.device, samplerIndex, decodedSamplerState, state->samplerState[samplerIndex]);
    }
  }
}

void R_DrawCall(DrawCallCallback callback, const void *userData, GfxCmdBufSourceState *source, const GfxViewInfo *viewInfo, const GfxDrawSurfListInfo *info, const GfxViewParms *viewParms, GfxCmdBuf *cmdBufEA, GfxCmdBuf *prepassCmdBufEA)
{
  GfxCmdBufState cmdBuf;
  GfxCmdBufState prepassCmdBuf;
  GfxCmdBufContext context;
  GfxCmdBufContext prepassContext;

  context.source = source;
  context.state = &cmdBuf;

  R_BeginView(source, &viewInfo->sceneDef, viewParms);
  R_InitLocalCmdBufState(&cmdBuf);

  if ( prepassCmdBufEA )
  {
    prepassContext.source = source;
    prepassContext.state = &prepassCmdBuf;
    R_InitLocalCmdBufState(&prepassCmdBuf);

    callback(userData, context, prepassContext);
    memcpy(&gfxCmdBufState, &prepassCmdBuf, sizeof(gfxCmdBufState));
  }
  else
  {
    prepassContext.source = NULL;
    prepassContext.state = NULL;
    callback(userData, context, prepassContext);
  }
  memcpy(&gfxCmdBufState, &cmdBuf, sizeof(gfxCmdBufState));
}


void R_GetViewport(GfxCmdBufSourceState *source, GfxViewport *outViewport)
{
  assert(source);

  if ( source->viewportBehavior == GFX_USE_VIEWPORT_FULL )
  {
    assert(source->renderTargetWidth > 0);
    assert(source->renderTargetHeight > 0);

    outViewport->x = 0;
    outViewport->y = 0;
    outViewport->width = source->renderTargetWidth;
    outViewport->height = source->renderTargetHeight;
  }
  else
  {
    assert(source->sceneViewport.width > 0);
    assert(source->sceneViewport.height > 0);

    outViewport->x = source->sceneViewport.x;
    outViewport->y = source->sceneViewport.y;
    outViewport->width = source->sceneViewport.width;
    outViewport->height = source->sceneViewport.height;
    assert(outViewport->width > 0);
    assert(outViewport->height > 0);
  }
  if ( source->viewMode != VIEW_MODE_2D && r_scaleViewport->current.value != 1.0 )
  {
    outViewport->x += (signed int)((float)outViewport->width * (1.0 - r_scaleViewport->current.value) * 0.5);
    outViewport->y += (signed int)((float)outViewport->height * (1.0 - r_scaleViewport->current.value) * 0.5);
    if ( (signed int)((float)outViewport->width * r_scaleViewport->current.value) > 1 )
    {
        outViewport->width = (signed int)((float)outViewport->width * r_scaleViewport->current.value);
    }
    else
    {
        outViewport->width = 1;
    }
    if ( (signed int)((float)outViewport->height * r_scaleViewport->current.value) > 1 )
    {
        outViewport->height = (signed int)((float)outViewport->height * r_scaleViewport->current.value);
    }
    else
    {
        outViewport->height = 1;
    }
  }
}


//OpenGL wrapper needs it
int R_GetOptimizeVBTransfersValue()
{
  return 0;
}

void R_SetOptimizeVBTransfersValue(int setval)
{

}



