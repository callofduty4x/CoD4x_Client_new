#include <d3d9.h>
#include "r_local.h"

enum DxCapsResponse
{
  DX_CAPS_RESPONSE_QUIT = 0x0,
  DX_CAPS_RESPONSE_WARN = 0x1,
  DX_CAPS_RESPONSE_INFO = 0x2,
  DX_CAPS_RESPONSE_FORBID_SM3 = 0x3,
};

struct DxCapsCheckBits
{
  int offset;
  unsigned int setBits;
  unsigned int clearBits;
  DxCapsResponse response;
  const char *msg;
};

struct DxCapsCheckInteger
{
  int offset;
  unsigned int min;
  unsigned int max;
  DxCapsResponse response;
  const char *msg;
};


DxCapsCheckBits s_capsCheckBits[33] =
{
  { 12, 0u, 536870912u, DX_CAPS_RESPONSE_QUIT, "doesn't support dynamic textures" },
  { 12, 0u, 131072u, DX_CAPS_RESPONSE_WARN, "doesn't support fullscreen gamma" },
  { 16, 0u, 32u, DX_CAPS_RESPONSE_QUIT, "doesn't support alpha blending" },
  { 16, 0u, 256u, DX_CAPS_RESPONSE_WARN, "doesn't accelerate dynamic textures" },
  { 20, 0u, 2147483648u, DX_CAPS_RESPONSE_WARN, "doesn't support immediate frame buffer swapping" },
  { 20, 0u, 1u, DX_CAPS_RESPONSE_WARN, "doesn't support vertical sync" },
  {
    28,
    0u,
    32768u,
    DX_CAPS_RESPONSE_QUIT,
    "is not at least DirectX 7 compliant"
  },
  {
    28,
    0u,
    66560u,
    DX_CAPS_RESPONSE_WARN,
    "doesn't accelerate transform and lighting"
  },
  { 28, 0u, 524288u, DX_CAPS_RESPONSE_WARN, "doesn't accelerate rasterization" },
  { 32, 0u, 2u, DX_CAPS_RESPONSE_QUIT, "can't disable depth buffer writes" },
  {
    32,
    0u,
    128u,
    DX_CAPS_RESPONSE_QUIT,
    "can't disable individual color channel writes"
  },
  {
    32,
    0u,
    2048u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support frame buffer blending ops beside add"
  },
  {
    32,
    0u,
    131072u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support separate alpha blend, glow will be disabled"
  },
  {
    32,
    0u,
    112u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support all face culling modes"
  },
  {
    36,
    0u,
    33554432u,
    DX_CAPS_RESPONSE_INFO,
    "doesn't support high-quality polygon offset"
  },
  {
    40,
    0u,
    141u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support the required depth comparison modes"
  },
  {
    44,
    0u,
    1023u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support the required frame buffer source blend modes"
  },
  {
    48,
    0u,
    1023u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support the required frame buffer destination blend modes"
  },
  {
    52,
    0u,
    210u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support the required alpha comparison modes"
  },
  { 60, 0u, 4u, DX_CAPS_RESPONSE_QUIT, "doesn't support alpha in textures" },
  { 60, 0u, 2048u, DX_CAPS_RESPONSE_QUIT, "doesn't support cubemap textures" },
  {
    60,
    0u,
    16384u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support mipmapped textures"
  },
  {
    60,
    2u,
    256u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support restricted use of non-power-of-2 textures"
  },
  {
    60,
    0u,
    1u,
    DX_CAPS_RESPONSE_WARN,
    "doesn't support perspective correct texturing"
  },
  { 60, 32u, 0u, DX_CAPS_RESPONSE_QUIT, "doesn't support non-square textures" },
  {
    64,
    0u,
    50529024u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support the required texture filtering modes"
  },
  {
    68,
    0u,
    50332416u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support the required cubemap texture filtering modes"
  },
  { 76, 0u, 4u, DX_CAPS_RESPONSE_QUIT, "doesn't support texture clamping" },
  { 76, 0u, 1u, DX_CAPS_RESPONSE_QUIT, "doesn't support texture wrapping" },
  {
    136,
    0u,
    511u,
    DX_CAPS_RESPONSE_INFO,
    "doesn't support the required stencil operations"
  },
  {
    212,
    0u,
    1u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support vertex stream offsets"
  },
  {
    244,
    0u,
    512u,
    DX_CAPS_RESPONSE_WARN,
    "doesn't support linear filtering when copying and shrinking the frame buffer"
  },
  { 236, 0u, 1u, DX_CAPS_RESPONSE_QUIT, "doesn't support UBYTE4N vertex data" }
};


DxCapsCheckInteger s_capsCheckInt[10] =
{
  {
    88,
    2048u,
    4294967295u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support large enough 2D textures"
  },
  {
    92,
    2048u,
    4294967295u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support large enough 2D textures"
  },
  {
    96,
    256u,
    4294967295u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support large enough 3D textures"
  },
  {
    148,
    8u,
    4294967295u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support enough texture coordinates for the DirectX 9 code path"
  },
  {
    152,
    8u,
    4294967295u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support enough textures for the DirectX 9 code path"
  },
  { 188, 1u, 4294967295u, DX_CAPS_RESPONSE_QUIT, "is not a DirectX 9 driver" },
  {
    196,
    4294836736u,
    4294901759u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support vertex shader 2.0 or better"
  },
  {
    204,
    4294902272u,
    4294967295u,
    DX_CAPS_RESPONSE_QUIT,
    "doesn't support pixel shader 2.0 or better"
  },
  {
    196,
    4294836992u,
    4294901759u,
    DX_CAPS_RESPONSE_FORBID_SM3,
    "doesn't support vertex shader 3.0 or better"
  },
  {
    204,
    4294902528u,
    4294967295u,
    DX_CAPS_RESPONSE_FORBID_SM3,
    "doesn't support pixel shader 3.0 or better"
  }
};


void R_RespondToMissingCaps(DxCapsResponse response, const char *msg)
{
  if ( response == DX_CAPS_RESPONSE_WARN )
  {
    Com_PrintWarning(CON_CHANNEL_GFX, "Video card or driver %s.\n", msg);
  }
  else
  {
    Com_Printf(CON_CHANNEL_GFX, "Video card or driver %s.\n", msg);
  }
  
  switch ( response )
  {
    case DX_CAPS_RESPONSE_QUIT:
      Com_Error(ERR_FATAL, "Video card or driver %s.\n", msg);
      break;
    case DX_CAPS_RESPONSE_WARN:
    case DX_CAPS_RESPONSE_INFO:
      return;
    case DX_CAPS_RESPONSE_FORBID_SM3:
      Com_Printf(CON_CHANNEL_GFX, "Shader model 3.0 not available.\n");
      Dvar_SetInt(r_rendererInUse, 0);  //shader model 2
      break;
    default:
      assertx(1, "unhandled response %i", response);
      break;
  }
}

void R_CheckDxCaps(const D3DCAPS9 *caps)
{
  unsigned int integer;
  unsigned int checkIndex;
  unsigned int bits;



  for ( checkIndex = 0; checkIndex < ARRAY_COUNT(s_capsCheckBits); ++checkIndex )
  {
    bits = *(unsigned int*)((char *)caps + s_capsCheckBits[checkIndex].offset);
    if ( (!s_capsCheckBits[checkIndex].clearBits || s_capsCheckBits[checkIndex].clearBits & ~bits) && (!s_capsCheckBits[checkIndex].setBits || s_capsCheckBits[checkIndex].setBits & bits) )
    {
      R_RespondToMissingCaps(s_capsCheckBits[checkIndex].response, s_capsCheckBits[checkIndex].msg);
    }
  }
  for ( checkIndex = 0; checkIndex < ARRAY_COUNT(s_capsCheckInt); ++checkIndex )
  {
    integer = *(unsigned int*)((char *)caps + s_capsCheckInt[checkIndex].offset);
    if ( integer < s_capsCheckInt[checkIndex].min || integer > s_capsCheckInt[checkIndex].max )
    {
      R_RespondToMissingCaps(s_capsCheckInt[checkIndex].response, s_capsCheckInt[checkIndex].msg);
    }
  }
}

