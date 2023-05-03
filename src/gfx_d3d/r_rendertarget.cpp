#include "r_local.h"
#include "rb_backend.h"
#include "r_image.h"
#include "../common/sys_thread.h"

const char *s_renderTargetNames[] =
{
  "R_RENDERTARGET_SAVED_SCREEN",
  "R_RENDERTARGET_FRAME_BUFFER",
  "R_RENDERTARGET_SCENE",
  "R_RENDERTARGET_RESOLVED_POST_SUN",
  "R_RENDERTARGET_RESOLVED_SCENE",
  "R_RENDERTARGET_FLOAT_Z",
  "R_RENDERTARGET_DYNAMICSHADOWS",
  "R_RENDERTARGET_PINGPONG_0",
  "R_RENDERTARGET_PINGPONG_1",
  "R_RENDERTARGET_SHADOWCOOKIE",
  "R_RENDERTARGET_SHADOWCOOKIE_BLUR",
  "R_RENDERTARGET_POST_EFFECT_0",
  "R_RENDERTARGET_POST_EFFECT_1",
  "R_RENDERTARGET_SHADOWMAP_SUN",
  "R_RENDERTARGET_SHADOWMAP_SPOT"
};

struct GfxRenderTarget gfxRenderTargets[R_RENDERTARGET_COUNT];


bool R_IsDepthStencilFormatOk(D3DFORMAT renderTargetFormat, D3DFORMAT depthStencilFormat)
{
  if ( D3DCALLNAKED(r_dx.d3d9->CheckDeviceFormat(r_dx.adapterIndex, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, 2u, D3DRTYPE_SURFACE, depthStencilFormat)) < 0 )
  {
    return 0;
  }
  if ( D3DCALLNAKED( r_dx.d3d9->CheckDepthStencilMatch(r_dx.adapterIndex, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, renderTargetFormat, depthStencilFormat)) >= 0 )
  {
    return 1;
  }
  return 0;
}

D3DFORMAT R_GetDepthStencilFormat(D3DFORMAT renderTargetFormat)
{
  if ( R_IsDepthStencilFormatOk(renderTargetFormat, D3DFMT_D24FS8) )
  {
    return D3DFMT_D24FS8;
  }
  return D3DFMT_D24S8;

}

void R_AssignImageToRenderTargetColor(GfxRenderTarget *renderTarget, GfxImage *image)
{
  renderTarget->surface.color = Image_GetSurface(image);
}

void R_AssignImageToRenderTargetDepthStencil(GfxRenderTarget *renderTarget, GfxImage *image)
{
  renderTarget->surface.depthStencil = Image_GetSurface(image);
}

void R_GetFrameBufferDepthStencilRes(int *depthStencilWidth, int *depthStencilHeight)
{
  *depthStencilWidth = vidConfig.displayWidth;
  *depthStencilHeight = vidConfig.displayHeight;
}

D3DSurface * R_AssignSingleSampleDepthStencilSurface(FullscreenType screenType)
{
  int depthStencilWidth;
  int depthStencilHeight;

  if ( !r_dx.singleSampleDepthStencilSurface && r_dx.multiSampleType == D3DMULTISAMPLE_NONE )
  {
    r_dx.singleSampleDepthStencilSurface = gfxRenderTargets[2].surface.depthStencil;
  }

  if ( r_dx.singleSampleDepthStencilSurface )
  {
    D3DCALLNOLOCKNOERROR(r_dx.singleSampleDepthStencilSurface->AddRef( ));
    return r_dx.singleSampleDepthStencilSurface;
  }

  R_GetFrameBufferDepthStencilRes(&depthStencilWidth, &depthStencilHeight);

  D3DCALL(r_dx.device->CreateDepthStencilSurface( depthStencilWidth, depthStencilHeight, r_dx.depthStencilFormat, D3DMULTISAMPLE_NONE, 0, 0, &r_dx.singleSampleDepthStencilSurface, 0 ));

  assert(r_dx.singleSampleDepthStencilSurface);

  return r_dx.singleSampleDepthStencilSurface;
}

extern const char* s_renderTargetNames[];

const char * R_RenderTargetName(GfxRenderTargetId renderTargetId)
{
  return s_renderTargetNames[(uint8_t)renderTargetId];
}



void R_InitFrameBufferRenderTarget_Win32(GfxRenderTarget *renderTarget)
{
  int depthStencilWidth;
  int depthStencilHeight;

  assert(renderTarget);

  renderTarget->width = vidConfig.displayWidth;
  renderTarget->height = vidConfig.displayHeight;

  D3DCALL(r_dx.device->GetSwapChain( 0, &r_dx.windows[0].swapChain ));
  D3DCALL(r_dx.device->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &renderTarget->surface.color ));

  assert(renderTarget->surface.color);

  if ( g_allocateMinimalResources )
  {
    renderTarget->surface.depthStencil = 0;
  }
  else
  {
    R_GetFrameBufferDepthStencilRes(&depthStencilWidth, &depthStencilHeight);
    D3DCALL(r_dx.device->CreateDepthStencilSurface( depthStencilWidth, depthStencilHeight, r_dx.depthStencilFormat, r_dx.multiSampleType, r_dx.multiSampleQuality, 0, &renderTarget->surface.depthStencil, 0 ));
  }
}

const char* R_DescribeFormat(D3DFORMAT format)
{
  switch ( format )
  {
    case D3DFMT_A8R8G8B8:
    case D3DFMT_A8B8G8R8:
      return "24-bit color with 8-bit alpha";
    case D3DFMT_R5G6B5:
      return "16-bit color";
    case D3DFMT_A1R5G5B5:
      return "15-bit color with 1-bit alpha";
    case D3DFMT_D16_LOCKABLE:
    case D3DFMT_D16:
      return "16-bit depth without stencil";
    case D3DFMT_D15S1:
      return "15-bit depth with 1-bit stencil";
    case D3DFMT_D24S8:
      return "24-bit depth with 8-bit stencil";
    case D3DFMT_D24X8:
      return "24-bit depth without stencil";
    default:
      break;
  }
  return va("unknown format 0x%08x", format);
}

void R_GetFullScreenRes(FullscreenType screenType, int *fullscreenWidth, int *fullscreenHeight)
{
  assert(screenType == FULLSCREEN_DISPLAY || screenType == FULLSCREEN_MIXED || screenType == FULLSCREEN_SCENE);

  if ( screenType )
  {
    *fullscreenWidth = vidConfig.sceneWidth;
  }
  else
  {
    *fullscreenWidth = vidConfig.displayWidth;
  }
  if ( screenType == FULLSCREEN_SCENE )
  {
    *fullscreenHeight = vidConfig.sceneHeight;
  }
  else
  {
    *fullscreenHeight = vidConfig.displayHeight;
  }
}

void AssertUninitializedRenderTarget(GfxRenderTarget *renderTarget)
{
  assert(renderTarget);
  assert(renderTarget->image == NULL);
  assert(renderTarget->surface.color == NULL);
  assert(renderTarget->surface.depthStencil == NULL);
  assert(renderTarget->width == 0);
  assert(renderTarget->height == 0);
}

void R_InitRenderTargetImage(int imageProgType, uint16_t width, uint16_t height, D3DFORMAT format, RenderTargetUsage usage, GfxRenderTarget *renderTarget, unsigned int allocFlags)
{
  unsigned int renderTargetId;

#ifndef NDEBUG
  AssertUninitializedRenderTarget(renderTarget);
#endif

  assert((signed int)width > 0);
  assert((signed int)height > 0);

  renderTargetId = renderTarget - gfxRenderTargets;

  assertx(renderTargetId < ARRAY_COUNT(gfxRenderTargets), "renderTargetId doesn't index R_RENDERTARGET_COUNT. %i not in [0, %i)", renderTargetId, R_RENDERTARGET_COUNT);

  renderTarget->image = Image_AllocProg(imageProgType, 6, 0);
  assert(renderTarget->image);

  Image_SetupRenderTarget(renderTarget->image, width, height, format, s_renderTargetNames[renderTargetId], allocFlags);
  if ( usage )
  {
    R_AssignImageToRenderTargetColor(renderTarget, renderTarget->image);
  }
  else
  {
    R_AssignImageToRenderTargetDepthStencil(renderTarget, renderTarget->image);
  }
  renderTarget->width = width;
  renderTarget->height = height;
}


void R_InitFullscreenRenderTargetImage(int imageProgType, FullscreenType screenType, int picmip, _D3DFORMAT format, RenderTargetUsage usage, GfxRenderTarget *renderTarget)
{
  unsigned int w;
  unsigned int y;
  int fullscreenWidth;
  int fullscreenHeight;

  fullscreenWidth = 0;
  fullscreenHeight = 0;
  R_GetFullScreenRes(screenType, &fullscreenWidth, &fullscreenHeight);
  if ( fullscreenWidth >> picmip > 1 )
  {
    w = fullscreenWidth >> picmip;
  }
  else
  {
    w = 1;
  }
  if ( fullscreenHeight >> picmip > 1 )
  {
    y = fullscreenHeight >> picmip;
  }
  else
  {
    y = 1;
  }
  R_InitRenderTargetImage(imageProgType, w, y, format, usage, renderTarget, 2u);
  assertx(usage != 2, "RENDERTARGET_USAGE_RENDER_SHARE_SCENE only implemented for XBOX");

  if ( usage == 1 )
  {
    renderTarget->surface.depthStencil = R_AssignSingleSampleDepthStencilSurface(screenType);
  }
  Image_TrackFullscreenTexture(renderTarget->image, fullscreenWidth, fullscreenHeight, picmip, format);
}


void R_ShareRenderTarget(uint8_t idFrom, uint8_t idTo)
{
  struct GfxRenderTarget *from;
  struct GfxRenderTarget *to;

  AssertUninitializedRenderTarget(&gfxRenderTargets[idTo]);
  from = &gfxRenderTargets[idFrom];
  to = &gfxRenderTargets[idTo];
  to->image = from->image;
  to->surface.color = from->surface.color;
  to->surface.depthStencil = from->surface.depthStencil;
  to->width = from->width;
  to->height = from->height;
#ifdef BLACKOPS
  to->cleared = from->cleared;
#endif
  if ( gfxRenderTargets[idTo].surface.color )
  {
    D3DCALLNOLOCKNOERROR(gfxRenderTargets[idTo].surface.color->AddRef( ));
  }
  if ( gfxRenderTargets[idTo].surface.depthStencil )
  {
    D3DCALLNOLOCKNOERROR(gfxRenderTargets[idTo].surface.depthStencil->AddRef( ));
  }
}



D3DFORMAT R_InitFrameBufferRenderTarget()
{
  D3DSURFACE_DESC surfaceDesc;
/*
  if ( r_reflectionProbeGenerate->current.enabled )
  {
    R_InitFrameBufferRenderTarget_Win32(&gfxRenderTargets[18]);
    Com_Printf(CON_CHANNEL_GFX, "Requested frame buffer to be %s\n", R_DescribeFormat(D3DFMT_A8R8G8B8));
    gfxRenderTargets[18].surface.color->GetDesc(&surfaceDesc);
    
    assert(surfaceDesc.Format != D3DFMT_UNKNOWN);
    
    Com_Printf(CON_CHANNEL_GFX, "DirectX returned a frame buffer that is %s\n", R_DescribeFormat(surfaceDesc.Format));
    if ( !g_allocateMinimalResources )
    {
      R_InitFullscreenRenderTargetImage(9, FULLSCREEN_SCENE, 0, D3DFMT_A16B16G16R16F, RENDERTARGET_USAGE_RENDER, &gfxRenderTargets[6]);
    }
  }
  else
*/
  {
    R_InitFrameBufferRenderTarget_Win32(&gfxRenderTargets[R_RENDERTARGET_FRAME_BUFFER]);
    R_ShareRenderTarget(R_RENDERTARGET_FRAME_BUFFER, R_RENDERTARGET_SCENE);
    Com_Printf(CON_CHANNEL_GFX, "Requested frame buffer to be %s\n", R_DescribeFormat(D3DFMT_A8R8G8B8));
    D3DCALLNOLOCKNOERROR(gfxRenderTargets[R_RENDERTARGET_FRAME_BUFFER].surface.color->GetDesc(&surfaceDesc));
    
    assert(surfaceDesc.Format != D3DFMT_UNKNOWN);

    Com_Printf(CON_CHANNEL_GFX, "DirectX returned a frame buffer that is %s\n", R_DescribeFormat(surfaceDesc.Format));
    if ( !g_allocateMinimalResources )
    {
      R_InitFullscreenRenderTargetImage(9, FULLSCREEN_SCENE, 0, surfaceDesc.Format, RENDERTARGET_USAGE_RENDER, &gfxRenderTargets[R_RENDERTARGET_RESOLVED_SCENE]);
    }
  }
  return surfaceDesc.Format;
}


void R_AssignShadowCookieDepthStencilSurface(GfxRenderTargetSurface *surface)
{
  D3DFORMAT format;

  D3DSurface *depthStencil = gfxRenderTargets[R_RENDERTARGET_SHADOWCOOKIE].surface.depthStencil;
  if ( depthStencil )
  {
    surface->depthStencil = depthStencil;
    D3DCALLNOERROR(depthStencil->AddRef( ));
    return;
  }

  format = R_GetDepthStencilFormat(D3DFMT_A8R8G8B8);

  D3DCALL(r_dx.device->CreateDepthStencilSurface(128, 128, format, D3DMULTISAMPLE_NONE, 0, 0, &surface->depthStencil, 0));
}


void R_InitAndTrackRenderTargetImage(int imageProgType, uint16_t width, uint16_t height, D3DFORMAT format, RenderTargetUsage usage, GfxRenderTarget *renderTarget)
{
  R_InitRenderTargetImage(imageProgType, width, height, format, usage, renderTarget, 2u);
  Image_TrackTexture(renderTarget->image, 3, format, width, height, 1);
}

void R_InitShadowmapRenderTarget(int imageProgType, uint16_t tileRes, uint16_t tileRowCount, GfxRenderTarget *renderTarget, ShadowmapRTTiling tilingMethond)
{
  uint16_t tileGridSize;
  BOOL usage;
  uint16_t totalHeight;
  uint16_t totalWidth;

  AssertUninitializedRenderTarget(renderTarget);
  if ( tilingMethond )
  {
    tileGridSize = tileRowCount / 2;
    totalWidth = tileGridSize * tileRes;
    totalHeight = tileGridSize * tileRes;
  }
  else
  {
    totalWidth = tileRes;
    totalHeight = tileRowCount * tileRes;
  }
  assert(((totalWidth) & ((totalWidth) - 1)) == 0);
  assert(((totalHeight) & ((totalHeight) - 1)) == 0);

  usage = gfxMetrics.shadowmapBuildTechType != 2;
  R_InitAndTrackRenderTargetImage(imageProgType, totalWidth, totalHeight, gfxMetrics.shadowmapFormatPrimary, (RenderTargetUsage)usage, renderTarget);
  if ( usage )
  {
    D3DCALL(r_dx.device->CreateDepthStencilSurface( totalWidth, totalHeight, gfxMetrics.shadowmapFormatSecondary, D3DMULTISAMPLE_NONE, 0, 0, &renderTarget->surface.depthStencil, 0 ));
  }
  else
  {
    D3DCALL(r_dx.device->CreateRenderTarget( totalWidth, totalHeight, gfxMetrics.shadowmapFormatSecondary, D3DMULTISAMPLE_NONE, 0, 0, &renderTarget->surface.color, 0 ));
  }
}



void R_InitShadowCookieRenderTarget(int imageProgType, GfxRenderTarget *renderTarget)
{
  R_InitRenderTargetImage(imageProgType, 128u, 128u, D3DFMT_A8R8G8B8, RENDERTARGET_USAGE_RENDER, renderTarget, 0);
  Image_TrackTexture(renderTarget->image, 3, D3DFMT_A8R8G8B8, 128, 128, 1);
  R_AssignShadowCookieDepthStencilSurface(&renderTarget->surface);
}


void R_InitRenderTargets_PC()
{
  D3DFORMAT backBufferFormat;

  backBufferFormat = R_InitFrameBufferRenderTarget();

  if ( g_allocateMinimalResources )
  {
    return;
  }
  if ( r_floatz->current.enabled )
  {
    R_InitFullscreenRenderTargetImage(4, FULLSCREEN_SCENE, 0, D3DFMT_R32F, RENDERTARGET_USAGE_RENDER, &gfxRenderTargets[R_RENDERTARGET_FLOAT_Z]);
  }

  R_ShareRenderTarget(R_RENDERTARGET_RESOLVED_SCENE, R_RENDERTARGET_DYNAMICSHADOWS);
  R_ShareRenderTarget(R_RENDERTARGET_RESOLVED_SCENE, R_RENDERTARGET_RESOLVED_POST_SUN);

  R_InitFullscreenRenderTargetImage(10, FULLSCREEN_DISPLAY, 0, backBufferFormat, RENDERTARGET_USAGE_TEXTURE, &gfxRenderTargets[R_RENDERTARGET_SAVED_SCREEN]);

  R_InitShadowmapRenderTarget(2, R_Is1900Card() < 1u ? 1024 : 512, 2, &gfxRenderTargets[R_RENDERTARGET_SHADOWMAP_SUN], SHADOWMAP_RT_TILE_VERTICAL);
  R_InitShadowmapRenderTarget(3, R_Is1900Card() < 1u ? 512 :  256, 4, &gfxRenderTargets[R_RENDERTARGET_SHADOWMAP_SPOT], SHADOWMAP_RT_TILE_VERTICAL);

  R_InitShadowCookieRenderTarget(0, &gfxRenderTargets[R_RENDERTARGET_SHADOWCOOKIE]);
  R_InitShadowCookieRenderTarget(1, &gfxRenderTargets[R_RENDERTARGET_SHADOWCOOKIE_BLUR]);

  R_InitFullscreenRenderTargetImage(5, FULLSCREEN_SCENE, 2, backBufferFormat, RENDERTARGET_USAGE_RENDER, &gfxRenderTargets[R_RENDERTARGET_POST_EFFECT_0]);
  R_InitFullscreenRenderTargetImage(6, FULLSCREEN_SCENE, 2, backBufferFormat, RENDERTARGET_USAGE_RENDER, &gfxRenderTargets[R_RENDERTARGET_POST_EFFECT_1]);
  R_InitFullscreenRenderTargetImage(7, FULLSCREEN_SCENE, 2, backBufferFormat, RENDERTARGET_USAGE_RENDER, &gfxRenderTargets[R_RENDERTARGET_PINGPONG_0]);
  R_InitFullscreenRenderTargetImage(8, FULLSCREEN_SCENE, 2, backBufferFormat, RENDERTARGET_USAGE_RENDER, &gfxRenderTargets[R_RENDERTARGET_PINGPONG_1]);
}



void R_ShutDownSingleRenderTarget(GfxRenderTarget *rt)
{
  if ( Sys_IsRenderThread() )
  {
    if ( rt->surface.color )
    {
      rt->surface.color->Release( );
    }
    if ( rt->surface.depthStencil )
    {
      rt->surface.depthStencil->Release( );
    }
  }
  else
  {
    if ( rt->surface.color )
    {
      RB_Resource_Release(rt->surface.color);
    }
    if ( rt->surface.depthStencil )
    {
      RB_Resource_Release(rt->surface.depthStencil);
    }
  }
  if ( rt->image )
  {
    Image_Release(rt->image);
  }
  rt->image = NULL;
  rt->surface.color = NULL;
  rt->surface.depthStencil = NULL;
  rt->width = 0;
  rt->height = 0;
}

void R_ShutdownRenderTargets()
{
  unsigned int renderTargetId;

  for ( renderTargetId = 0; renderTargetId < ARRAY_COUNT(gfxRenderTargets); ++renderTargetId )
  {
    R_ShutDownSingleRenderTarget(&gfxRenderTargets[renderTargetId]);
  }
  r_dx.singleSampleDepthStencilSurface = NULL;
}


void R_InitRenderTargets()
{
  R_InitRenderTargets_PC();
}


void R_HW_SetRenderTarget(GfxCmdBufState *state, unsigned int newTargetId)
{
  IDirect3DDevice9 *device;

  //R_PixStartNamedRenderTarget(newTargetId);

  device = state->prim.device;
  assert(device);

  if ( gfxRenderTargets[(uint8_t)state->renderTargetId].surface.color != gfxRenderTargets[(uint8_t)newTargetId].surface.color )
  {
    D3DCALL(device->SetRenderTarget( 0, gfxRenderTargets[newTargetId].surface.color ));

    state->viewport.x = 0;
    state->viewport.y = 0;
    state->viewport.width = gfxRenderTargets[(uint8_t)newTargetId].width;
    state->viewport.height = gfxRenderTargets[(uint8_t)newTargetId].height;
    state->depthRangeType = GFX_DEPTH_RANGE_FULL;
    state->depthRangeNear = 0.0;
    state->depthRangeFar = 1.0;
  }
  if ( gfxRenderTargets[(uint8_t)state->renderTargetId].surface.depthStencil != gfxRenderTargets[(uint8_t)newTargetId].surface.depthStencil )
  {
      D3DCALL(device->SetDepthStencilSurface( gfxRenderTargets[newTargetId].surface.depthStencil ));
  }
}


void R_SetRenderTarget(GfxCmdBufContext context, GfxRenderTargetId newTargetId)
{
  if ( pixelCostMode > GFX_PIXEL_COST_MODE_MEASURE_MSEC )
  {
    newTargetId = RB_PixelCost_OverrideRenderTarget(newTargetId);
  }
  if ( newTargetId != context.state->renderTargetId )
  {
    _RB_LogPrintf("\n========== R_SetRenderTarget( %s ) ==========\n\n", R_RenderTargetName(newTargetId));
#ifdef BLACKOPS    
    R_UpdateStatsTarget(context, (uint8_t)newTargetId);
#endif
    if ( gfxRenderTargets[(uint8_t)newTargetId].image )
    {
      R_UnbindImage(context.state, gfxRenderTargets[(unsigned __int8)newTargetId].image);
    }

    assert(context.source->renderTargetHeight == (int)gfxRenderTargets[newTargetId].height);
    assert((context.source->renderTargetWidth > 0));
    assert(context.source->renderTargetHeight > 0);

    R_HW_SetRenderTarget(context.state, newTargetId);

    context.state->renderTargetId = newTargetId;
    context.source->viewMode = VIEW_MODE_NONE;
    context.source->viewportIsDirty = true;
  }
}
