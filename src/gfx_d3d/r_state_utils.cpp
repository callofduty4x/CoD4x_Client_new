#include "r_local.h"
#include "rb_backend.h"

extern unsigned int s_decodeSamplerFilterState[24];
extern const float g_identityMatrix44[4][4];

void R_SetDefaultAlphaTestFunction(GfxCmdBufState *state)
{

  IDirect3DDevice9 *device;

  device = state->prim.device;
  assert(device);

  D3DCALL(device->SetRenderState( D3DRS_ALPHAREF, 0 ));

  state->alphaRef = 0;
}


void R_SetDefaultStateBits(unsigned int *stateBits)
{
  stateBits[0] = 0;
  stateBits[1] = 0;
  stateBits[0] |= 0x800u;
  stateBits[0] |= 0x18000000u;
  stateBits[0] |= 0x4000u;
  stateBits[1] |= 2u;
}


unsigned int R_DecodeSamplerState(char samplerState)
{
  unsigned int tableIndex;

  tableIndex = samplerState & 0x1F;

  assert(tableIndex < ARRAY_COUNT(s_decodeSamplerFilterState));

  return s_decodeSamplerFilterState[tableIndex] | 0x1500000 | ((samplerState & 0x20) << 16) | ((samplerState & 0x40) << 17) | ((uint8_t)(samplerState & 0x80) << 18);
}


void R_HW_ForceSamplerState(D3DDevice *device, unsigned int samplerIndex, unsigned int samplerState)
{
    unsigned int minFilter = (samplerState & 0xF00) >> 8;
    unsigned int magFilter = (samplerState & 0xF000) >> 12;
    signed int anisotropy = (unsigned)(samplerState & 0xFF);
    unsigned int mipFilter = (samplerState & 0xF0000) >> 16;

    D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_MINFILTER, minFilter ));
    D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_MAGFILTER, magFilter ));

    if ( anisotropy > 1 )
    {
        D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_MAXANISOTROPY, anisotropy ));
    }

    D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_MIPFILTER, mipFilter ));

    D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_MIPMAPLODBIAS, r_dx.mipBias));


    unsigned int address = (samplerState & 0x300000) >> 20;

    D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_ADDRESSU, address ));
    
    
    address = (samplerState & 0xC00000) >> 22;
    
    D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_ADDRESSV, address ));

    address = (samplerState & 0x3000000) >> 24;

    D3DCALL(device->SetSamplerState( samplerIndex, D3DSAMP_ADDRESSW, address ));

}



void R_InitCmdBufState(GfxCmdBufState *state)
{
    D3DDevice *device;
    unsigned int samplerIndex;
    unsigned int forceSamplerState;

    assert(state);

    device = state->prim.device;
    memset(state, 0, sizeof(*state));
    state->prim.device = device;
    state->depthRangeType = GFX_DEPTH_RANGE_FULL;
    state->depthRangeNear = 0.0;
    state->depthRangeFar = 1.0;
    state->renderTargetId = R_RENDERTARGET_SAVED_SCREEN;
    R_SetDefaultStateBits(state->activeStateBits);
    R_SetDefaultStateBits(state->refStateBits);
    R_SetCompleteState(device, state->activeStateBits);
    R_SetDefaultAlphaTestFunction(state);
    forceSamplerState = R_DecodeSamplerState(1);
    for ( samplerIndex = 0; samplerIndex < ARRAY_COUNT(state->samplerState); ++samplerIndex )
    {
        R_HW_ForceSamplerState(state->prim.device, samplerIndex, forceSamplerState);
        state->refSamplerState[samplerIndex] = 1;
        state->samplerState[samplerIndex] = forceSamplerState;
    }
    state->prim.vertexDecl = (IDirect3DVertexDeclaration9 *)-1;
    state->pixelShader = (MaterialPixelShader *)-1;
    /*
    state->stateOverride = 0;
    state->prim.viewStats = state->prim.frameStats.viewStats;
    */
}

void R_WorldMatrixChanged(GfxCmdBufSourceState *source)
{
    ++source->matrixVersions[0];
    ++source->matrixVersions[3];
    ++source->matrixVersions[5];
    ++source->matrixVersions[7];
    source->constVersions[CONST_SRC_FIRST_CODE_MATRIX] = source->matrixVersions[0];
}

GfxMatrix * R_GetActiveWorldMatrix(GfxCmdBufSourceState *source)
{
    R_WorldMatrixChanged(source);
    return source->matrices.matrix;
}

void R_MatrixIdentity44(float (*out)[4])
{
  assert(out);
  memcpy(out, g_identityMatrix44, sizeof(g_identityMatrix44));
}

void R_CmdBufSet3D(GfxCmdBufSourceState *source)
{
    GfxMatrix *worldMatrix; 

    ++source->matrixVersions[1];
    ++source->matrixVersions[2];
    ++source->matrixVersions[4];
    worldMatrix = R_GetActiveWorldMatrix(source);
    R_MatrixIdentity44(worldMatrix->m);

    VectorSubtract(worldMatrix->m[3], source->eyeOffset, worldMatrix->m[3]);
}

void R_Set3D(GfxCmdBufSourceState *source)
{

  assert(source->viewParms3D);
  if(source->viewMode == VIEW_MODE_3D)
  {
    return;
  }

  PIXBeginNamedEvent(-1, "R_Set3D");
  source->viewMode = VIEW_MODE_3D;
  memcpy(&source->viewParms, source->viewParms3D, sizeof(source->viewParms));
  if ( source->viewParms.origin[3] == 0.0 )
  {
    VectorClear(source->eyeOffset);
  }
  else
  {
    VectorCopy(source->viewParms.origin, source->eyeOffset);
  }
  source->eyeOffset[3] = 1.0;
  R_CmdBufSet3D(source);
  
  /*
  UpdateVPosToWorld(source);
  if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
  {
      D3DPERF_EndEvent();
  }
  */
}