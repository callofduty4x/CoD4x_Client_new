#include "dxerr/dxerr.h"
#include "r_local.h"
#include "rb_backend.h"
#include "r_image.h"
#include "r_model.h"
#include "../common/sys_shared.h"
#include "../common/qcommon.h"
#include "../common/sys_thread.h"
#include "../database/db_shared.h"
#include <stdarg.h>


GfxGlobals r_glob;

void DB_LoadXZoneFromGfxConfig()
{
  XZoneInfo zoneinfo[7];

  int index = 0;

  zoneinfo[index].name = gfxCfg.codeFastFileName;
  zoneinfo[index].allocFlags = 2;
  zoneinfo[index].freeFlags = 0;
  ++index;
 

  if ( gfxCfg.localizedCodeFastFileName )
  {
    zoneinfo[index].name = gfxCfg.localizedCodeFastFileName;
    zoneinfo[index].allocFlags = 0;
    zoneinfo[index].freeFlags = 0;
    ++index;
  }

  if ( gfxCfg.modFastFileName )
  {
    zoneinfo[index].name = gfxCfg.modFastFileName;
    zoneinfo[index].allocFlags = 16;
    zoneinfo[index].freeFlags = 0;
    ++index;

    DB_LoadXAssets(zoneinfo, index, 0);
    DB_SyncXAssets();
    index = 0;
  }
#if 0
  else{

    zoneinfo[index].name = "cod4x_patchv2";
    zoneinfo[index].allocFlags = 16;
    zoneinfo[index].freeFlags = 0;
    ++index;
  }
#endif
  if ( gfxCfg.uiFastFileName )
  {
    zoneinfo[index].name = gfxCfg.uiFastFileName;
    zoneinfo[index].allocFlags = 8;
    zoneinfo[index].freeFlags = 0;
    ++index;
  }

  zoneinfo[index].name = gfxCfg.commonFastFileName;
  zoneinfo[index].allocFlags = 4;
  zoneinfo[index].freeFlags = 0;
  ++index;
/*
  zoneinfo[index].name = "cod4x_ambfix";
  zoneinfo[index].allocFlags = 4;
  zoneinfo[index].freeFlags = 0;
  ++index;
*/
  if ( gfxCfg.localizedCommonFastFileName )
  {
    zoneinfo[index].name = gfxCfg.localizedCommonFastFileName;
    zoneinfo[index].allocFlags = 1;
    zoneinfo[index].freeFlags = 0;
    ++index;
  }

  DB_LoadXAssets(zoneinfo, index, 0);
}

void R_UpdateGpuSyncType()
{
  if ( r_multiGpu->current.enabled )
  {
    r_dx.gpuSync = 0;
  }
  else
  {
    r_dx.gpuSync = r_gpuSync->current.integer;
  }
}

void R_StoreWindowSettings(GfxWindowParms *wndParms)
{
  double rationselector; 
  int monitorHeight;
  int monitorWidth;


  assert(r_aspectRatio);

  vidConfig.sceneWidth = wndParms->sceneWidth;
  vidConfig.sceneHeight = wndParms->sceneHeight;
  vidConfig.displayWidth = wndParms->displayWidth;
  vidConfig.displayHeight = wndParms->displayHeight;
  vidConfig.displayFrequency = wndParms->hz;
  vidConfig.isFullscreen = wndParms->fullscreen;
  switch ( r_aspectRatio->current.integer )
  {
    case 0:
      if ( vidConfig.isFullscreen && r_dx.adapterNativeIsValid )
      {
        monitorWidth = r_dx.adapterNativeWidth;
        monitorHeight = r_dx.adapterNativeHeight;
      }
      else
      {
        monitorWidth = vidConfig.displayWidth;
        monitorHeight = vidConfig.displayHeight;
      }
      rationselector = ((float)monitorHeight * 16.0) / (float)monitorWidth;
      if ( (signed int)rationselector == 10 )
      {
        vidConfig.aspectRatioWindow = 1.6;
      }
      else if ( (signed int)rationselector >= 10 )
      {
        vidConfig.aspectRatioWindow = 1.3333334;
      }
      else if((signed int)rationselector < 7)
      {
        vidConfig.aspectRatioWindow = 2.3333333;
      }
      else
      {
        vidConfig.aspectRatioWindow = 1.7777778;
      }
      break;
    default: //error case
    case 1:
      vidConfig.aspectRatioWindow = 1.3333334;
      break;
    case 2:
      vidConfig.aspectRatioWindow = 1.6;
      break;
    case 3:
      vidConfig.aspectRatioWindow = 1.7777778;
      break;
    case 4:
      vidConfig.aspectRatioWindow = 2.3333333;
      break;
  }
  assert ( com_wideScreen );

  if ( vidConfig.aspectRatioWindow > 1.3333334 )
  {
    Dvar_SetBool(com_wideScreen, 1);
  }
  else
  {
    Dvar_SetBool(com_wideScreen, 0);
  }
  vidConfig.aspectRatioScenePixel = (double)vidConfig.sceneHeight * vidConfig.aspectRatioWindow / (double)vidConfig.sceneWidth;
  if ( vidConfig.isFullscreen )
  {
    vidConfig.aspectRatioDisplayPixel = ((float)r_dx.adapterFullscreenHeight * (float)vidConfig.aspectRatioWindow) / (float)r_dx.adapterFullscreenWidth;
    if(vidConfig.aspectRatioWindow > 2.0 && vidConfig.aspectRatioDisplayPixel > 1.0)
    {
      vidConfig.aspectRatioDisplayPixel = 1.0;
    }
  }
  else
  {
    vidConfig.aspectRatioDisplayPixel = 1.0;
  }
  /*
  vidConfig.isToolMode = 0;
  v3 = r_reflectionProbeGenerate && r_reflectionProbeGenerate->current.enabled;
  vidConfig.isToolMode = v3;
  */
}

bool R_GetMonitorDimensionsEx(int *width, int *height, int *x, int *y)
{
#ifdef _WIN32
  bool valid;
  tagMONITORINFO mi;
  HMONITOR adapterMonitor;

  *x = 0;
  *y = 0;

  adapterMonitor = r_dx.d3d9->GetAdapterMonitor(r_dx.adapterIndex);
  mi.cbSize = 40;
  if ( GetMonitorInfoA(adapterMonitor, &mi) )
  {
    *x = mi.rcMonitor.left;
	  *y = mi.rcMonitor.top;
    *width = mi.rcMonitor.right - mi.rcMonitor.left;
    *height = mi.rcMonitor.bottom - mi.rcMonitor.top;
    valid = 1;
  }
  else
  {
    *width = GetSystemMetrics(0);
    *height = GetSystemMetrics(1);
    valid = *width > 0 && *height > 0;
  }
  return valid;
#else
#error "fill with code"
#endif
}

bool R_GetMonitorDimensions(int *width, int *height)
{
  int x, y;
  return R_GetMonitorDimensionsEx(width, height, &x, &y);
}



qboolean R_CreateWindow(struct GfxWindowParms *windowInfo)
{
  int wsExStyle;
  int wsStyle;
  HWND hwnd;
  struct tagRECT Rect;

  assert(windowInfo);
  assert(windowInfo->hwnd == NULL);

  if ( windowInfo->fullscreen )
  {
    Com_Printf(CON_CHANNEL_GFX, "Attempting %i x %i fullscreen with 32 bpp at %i hz\n", windowInfo->displayWidth, windowInfo->displayHeight, windowInfo->hz);
    wsExStyle = WS_EX_TOPMOST;
    wsStyle = WS_POPUP;


  }else{
	  if(windowInfo->displayWidth == windowInfo->monitorWidth && windowInfo->displayHeight == windowInfo->monitorHeight)
	  {
		wsExStyle = 0;
		wsStyle = WS_POPUP;

		windowInfo->x = windowInfo->monitorX;
		windowInfo->y = windowInfo->monitorY;
		Com_Printf(CON_CHANNEL_GFX, "Attempting %i x %i window without border at (%i, %i)\n", windowInfo->displayWidth, windowInfo->displayHeight, windowInfo->x, windowInfo->y);

	  }
	  else
	  {
		Com_Printf(CON_CHANNEL_GFX, "Attempting %i x %i window at (%i, %i)\n", windowInfo->displayWidth, windowInfo->displayHeight, windowInfo->x, windowInfo->y);
		wsExStyle = 0;
		wsStyle = WS_GROUP | WS_CAPTION | WS_SYSMENU;

	  }
  }
  Rect.left = 0;
  Rect.right = windowInfo->displayWidth;
  Rect.top = 0;
  Rect.bottom = windowInfo->displayHeight;
  AdjustWindowRectEx(&Rect, wsStyle, 0, wsExStyle);

  hwnd = CreateWindowExA(wsExStyle, WINDOW_CLASS_NAME, Com_GetBuildDisplayName(), wsStyle, windowInfo->x, windowInfo->y,
						Rect.right - Rect.left, Rect.bottom - Rect.top, 0, 0, GetModuleHandleA(0) /*g_wv.hInstance*/, 0);

  windowInfo->hwnd = hwnd;
  if ( hwnd )
  {
    Com_Printf(CON_CHANNEL_GFX, "Game window successfully created.\n");
    return qtrue;
  }
  Com_Printf(CON_CHANNEL_GFX, "Couldn't create a window.\n");

#pragma msg "Need to retry here later with lower resolution"
  R_FatalInitError("Couldn't create a window. Couldn't initialize renderer");
  //
  return qfalse;
}

qboolean R_Is1900Card()
{
    return qfalse;
}

qboolean R_HWSupportsShadows()
{
    return qtrue;
}


bool UseBufferHints;
unsigned int BufferFlushSize;

void R_OpenGL_SetBufferHint(unsigned int hint)
{
    UseBufferHints = true;
    BufferFlushSize = hint;

}

void R_OpenGL_ClearBufferHints( )
{
    UseBufferHints = false;

}

void R_OpenGL_GetBufferHint(unsigned int *hint)
{
  if ( UseBufferHints )
  {
    *hint = BufferFlushSize;
  }
  else
  {
    *hint = -1;
  }
}
void R_GetFBOSupportInfo(unsigned char *a1, unsigned char *a2)
{
    *a1 = 0;
    *a2 = 1;
}
//_Z13R_GetDeviceIDv
unsigned int R_GetDeviceID()
{
    return 0;
}
//_Z13R_GetVendorIDv
unsigned int R_GetVendorID()
{
    return 0;
}
//_Z18R_GetIsAntialiasedv
unsigned int R_GetIsAntialiased()
{
    return 1;
}

struct GfxCmdBufSourceState;

void R_DeriveOpenGLMatrices(GfxCmdBufSourceState *a1)
{
    
}

const char * R_ErrorDescription(HRESULT hr)
{
  return DXGetErrorStringA(hr);
}

void __noreturn R_FatalInitError(const char *msgfmt, ...)
{
  char msgbuf[4096];

  va_list ap;
  va_start(ap, msgfmt);
  vsnprintf(msgbuf, sizeof(msgbuf), msgfmt, ap);
  va_end(ap);

  Com_Printf(CON_CHANNEL_GFX, "********** DirectX returned an unrecoverable error code during initialization  **********\n");
  Com_Printf(CON_CHANNEL_GFX, "********** Initialization also happens while playing if DirectX loses a device **********\n");
  Com_Printf(CON_CHANNEL_GFX, "********** Consult the readme for how to continue from this problem            **********\n");
  Com_Printf(CON_CHANNEL_GFX, "\n%s\n", msgbuf);
  Sys_DirectXFatalError();
}

bool R_CheckTransparencyMsaa(unsigned int adapterIndex)
{
  if ( r_aaSamples->current.integer == 1 )
  {
    return false;
  }
  if(r_dx.d3d9->CheckDeviceFormat(adapterIndex, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, 0, D3DRTYPE_SURFACE, (D3DFORMAT)MAKEFOURCC('S', 'S', 'A', 'A')) == D3D_OK)
  {
    return true;
  }
  return false;

}

void R_GetDirect3DCaps(unsigned int adapterIndex, _D3DCAPS9 *caps)
{
  HRESULT hr;
  int attempt;

  assert(r_dx.d3d9);

  for (attempt = 0; attempt < 20; ++attempt  )
  {
    hr = D3DCALLNOLOCKNOERROR(r_dx.d3d9->GetDeviceCaps(adapterIndex, D3DDEVTYPE_HAL, caps));
    if ( hr >= 0 )
    {
      return;
    }
    Sys_Sleep(100);
  }
  R_FatalInitError("GetDeviceCaps failed: %s", R_ErrorDescription(hr));
}

void R_PickRenderer(D3DCAPS9 *caps)
{
  const char *savailpath;

  Com_Printf(CON_CHANNEL_GFX, "Pixel shader version is %i.%i\n", ((int)caps->PixelShaderVersion & 0xFF00) >> 8, (int)caps->PixelShaderVersion & 0xFF);
  Com_Printf(CON_CHANNEL_GFX, "Vertex shader version is %i.%i\n", ((int)caps->VertexShaderVersion & 0xFF00) >> 8, (int)caps->VertexShaderVersion & 0xFF);
  
  Dvar_SetInt(r_rendererInUse, 1); //shader model 3

  R_CheckDxCaps(caps);

  switch(r_rendererInUse->current.integer)
  {
    default:
      Com_Error(ERR_FATAL, "No valid rendering code path detected.\n");
      return;
    case 1:
      savailpath = "Shader model 3.0";
      break;
    case 0:
      savailpath = "Shader model 2.0";
      break;
  }
  Com_Printf(CON_CHANNEL_GFX, "Using %s code path because it is the best available path on this hardware.\n", savailpath);

}


void R_SetShadowmapFormats_DX(unsigned int adapterIndex)
{
  D3DFORMAT colorFormat;
  unsigned int formatIndex;
  D3DFORMAT depthFormat;
  D3DFORMAT formats[3][2];

  formats[0][0] = D3DFMT_D24S8;
  formats[0][1] = D3DFMT_R5G6B5;
  formats[1][0] = D3DFMT_D24S8;
  formats[1][1] = D3DFMT_X8R8G8B8;
  formats[2][0] = D3DFMT_D24S8;
  formats[2][1] = D3DFMT_A8R8G8B8;

  for ( formatIndex = 0; formatIndex < 3; ++formatIndex )
  {
    depthFormat = formats[formatIndex][0];
    colorFormat = formats[formatIndex][1];
    if ( r_dx.d3d9->CheckDepthStencilMatch(adapterIndex, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, colorFormat, depthFormat) != D3D_OK
      && r_dx.d3d9->CheckDeviceFormat(adapterIndex, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, 2, D3DRTYPE_TEXTURE, depthFormat) != D3D_OK)
    {
      gfxMetrics.shadowmapFormatPrimary = depthFormat;
      gfxMetrics.shadowmapFormatSecondary = colorFormat;
      gfxMetrics.shadowmapBuildTechType = TECHNIQUE_BUILD_SHADOWMAP_DEPTH;
      gfxMetrics.hasHardwareShadowmap = 1;
      gfxMetrics.shadowmapSamplerState = 98;
      Dvar_SetBoolByName("ui_showShadowOptions", qtrue);
      return;
    }
  }
  gfxMetrics.shadowmapFormatPrimary = D3DFMT_R32F;
  gfxMetrics.shadowmapFormatSecondary = D3DFMT_D24X8;
  gfxMetrics.shadowmapBuildTechType = TECHNIQUE_BUILD_SHADOWMAP_COLOR;
  gfxMetrics.hasHardwareShadowmap = 0;
  gfxMetrics.shadowmapSamplerState = 97;
  Dvar_SetBool(sm_enable, 0);
  Dvar_SetBoolByName("ui_showShadowOptions", qfalse);
}


void R_StoreDirect3DCaps(unsigned int adapterIndex)
{
  D3DCAPS9 caps;

  R_GetDirect3DCaps(adapterIndex, &caps);
  R_PickRenderer(&caps);
  if ( (signed int)caps.MaxTextureHeight < (signed int)caps.MaxTextureWidth )
  {
    vidConfig.maxTextureSize = caps.MaxTextureHeight;
  }
  else
  {
    vidConfig.maxTextureSize = caps.MaxTextureWidth;
  }
  vidConfig.maxTextureMaps = caps.MaxSimultaneousTextures; //16 BLACKOPS
  if(caps.Caps2 & 0x20000)
  {
    vidConfig.deviceSupportsGamma = true;
  }else{
    vidConfig.deviceSupportsGamma = false;
  }

  if ( (signed int)caps.MaxUserClipPlanes < 6 )
  {
    gfxMetrics.maxClipPlanes = caps.MaxUserClipPlanes;
  }
  else
  {
    gfxMetrics.maxClipPlanes = 6;
  }
  gfxMetrics.hasAnisotropicMinFilter = (caps.TextureFilterCaps & 0x400) != 0;
  gfxMetrics.hasAnisotropicMagFilter = (caps.TextureFilterCaps & 0x4000000) != 0;
  gfxMetrics.maxAnisotropy = caps.MaxAnisotropy;
  gfxMetrics.slopeScaleDepthBias = (caps.RasterCaps & 0x2000000) != 0;
  gfxMetrics.canMipCubemaps = (caps.TextureCaps & 0x10000) != 0;
  gfxMetrics.hasTransparencyMsaa = R_CheckTransparencyMsaa(adapterIndex);
  R_SetShadowmapFormats_DX(adapterIndex);
}


void R_SetupAntiAliasing(const GfxWindowParms *wndParms)
{
  unsigned int multiSampleCount;
  DWORD qualityLevels;

  assert(wndParms);
  assertx(wndParms->aaSamples >= 1 && wndParms->aaSamples <= 16, "%i not in [%i, %i]", wndParms->aaSamples, 1, 16);

  if ( r_reflectionProbeGenerate->current.enabled )
  {
    multiSampleCount = 1;
  }
  else
  {
    multiSampleCount = wndParms->aaSamples;
  }
  while ( (signed int)multiSampleCount > 1 )
  {
    r_dx.multiSampleType = (D3DMULTISAMPLE_TYPE)multiSampleCount;
    if ( D3DCALLNOLOCKNOERROR(r_dx.d3d9->CheckDeviceMultiSampleType(0, D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, wndParms->fullscreen == 0, (D3DMULTISAMPLE_TYPE)multiSampleCount, &qualityLevels)) >= 0 )
    {
      Com_Printf(CON_CHANNEL_GFX, "Using %ix anti-aliasing\n", multiSampleCount);
      r_dx.multiSampleQuality = 0;
      return;
    }
    --multiSampleCount;
  }
  r_dx.multiSampleType = D3DMULTISAMPLE_NONE;
  r_dx.multiSampleQuality = 0;
}

void R_SetD3DPresentParameters(D3DPRESENT_PARAMETERS *d3dpp, const GfxWindowParms *wndParms)
{
  assert(d3dpp);
  assert(wndParms);

  R_SetupAntiAliasing(wndParms);

  memset(d3dpp, 0, sizeof(*d3dpp));

  d3dpp->BackBufferHeight = wndParms->displayHeight;
  d3dpp->BackBufferWidth = wndParms->displayWidth;
  d3dpp->BackBufferFormat = D3DFMT_A8R8G8B8;
  d3dpp->BackBufferCount = 1;
  d3dpp->MultiSampleType = r_dx.multiSampleType;
  d3dpp->MultiSampleQuality = r_dx.multiSampleQuality;
  d3dpp->SwapEffect = D3DSWAPEFFECT_DISCARD;
  d3dpp->EnableAutoDepthStencil = 0;
  d3dpp->AutoDepthStencilFormat = r_dx.depthStencilFormat;
  d3dpp->PresentationInterval = r_vsync->current.enabled != 0 ? 1 : 0x80000000;

  assert(wndParms->hwnd);

  d3dpp->hDeviceWindow = wndParms->hwnd;
  d3dpp->Flags = 0;

  if ( wndParms->fullscreen )
  {
    d3dpp->Windowed = 0;
    d3dpp->FullScreen_RefreshRateInHz = wndParms->hz;
  }
  else
  {
    d3dpp->Windowed = 1;
    d3dpp->FullScreen_RefreshRateInHz = 0;
  }
}

void R_InitGlobalStructs()
{
  memset(&rg, 0, sizeof(rg));
  memset(&rgp, 0, sizeof(rgp));
  RB_InitBackendGlobalStructs();
  
  rg.remotePlacement.base.quat[0] = 0.0;
  rg.remotePlacement.base.quat[1] = 0.0;
  rg.remotePlacement.base.quat[2] = 0.0;
  rg.remotePlacement.base.quat[3] = 1.0;
  rg.remotePlacement.base.origin[0] = 0.0;
  rg.remotePlacement.base.origin[1] = 0.0;
  rg.remotePlacement.base.origin[2] = 0.0;
  rg.remotePlacement.scale = 1.0;
  
  MatrixIdentity44(rg.identityViewParms.viewMatrix.m);
  MatrixIdentity44(rg.identityViewParms.projectionMatrix.m);
  MatrixIdentity44(rg.identityViewParms.viewProjectionMatrix.m);
  MatrixIdentity44(rg.identityViewParms.inverseViewProjectionMatrix.m);
}

void R_Register()
{
  R_RegisterDvars();
  R_RegisterCmds();
}

typedef struct
{
	DWORD monitorNumber;
	HMONITOR monitorHandle;
}monitorEnumParam_t;

BOOL CALLBACK R_MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, monitorEnumParam_t *monitorParam)
{
  BOOL result;

  if ( monitorParam->monitorNumber == 1 )
  {
    monitorParam->monitorHandle = hMonitor;
    result = 0;
  }
  else
  {
    result = 1;
  }
  monitorParam->monitorNumber--;
  return result;
}

HMONITOR R_ChooseMonitor()
{
  bool fullscreen;
  HMONITOR hMonitor;
  POINT point;
  monitorEnumParam_t monitorParam;
  fullscreen = Dvar_GetBool("r_fullscreen");

  if (fullscreen)
  {
    monitorParam.monitorNumber = Dvar_GetInt("r_monitor");
    monitorParam.monitorHandle = 0;
    EnumDisplayMonitors(0, 0, (MONITORENUMPROC)R_MonitorEnumProc, (LPARAM)&monitorParam);
    hMonitor = monitorParam.monitorHandle;
  }

  if (!fullscreen  || hMonitor == 0)
  {
    point.x = Dvar_GetInt("vid_xpos");
    point.y = Dvar_GetInt("vid_ypos");
    hMonitor = MonitorFromPoint(point, 1u);
  }
  return hMonitor;
}


unsigned int R_ChooseAdapter()
{
  HMONITOR desiredMonitor;
  unsigned int adapterMon;
  unsigned int adapterCount;
  unsigned int i;

  desiredMonitor = R_ChooseMonitor();
  adapterMon = 0;
  adapterCount = r_dx.d3d9->GetAdapterCount( );

  for(i = 0; i < adapterCount; ++i)
  {
    if ( desiredMonitor )
    {
      HMONITOR hmoncur = r_dx.d3d9->GetAdapterMonitor(i);
      if(hmoncur == desiredMonitor)
      {
          adapterMon = i;
      }
    }
  }
  return adapterMon;
}

int R_SortAdapterModes(const void* cmp1, const void* cmp2)
{
  const D3DDISPLAYMODE *d3dmode1 = (const D3DDISPLAYMODE *)cmp1;
  const D3DDISPLAYMODE *d3dmode2 = (const D3DDISPLAYMODE *)cmp2;

  if ( d3dmode1->Width == d3dmode2->Width )
  {
	if ( d3dmode1->Height == d3dmode2->Height )
	{
      return d3dmode1->RefreshRate - d3dmode2->RefreshRate;
	}
    return d3dmode1->Height - d3dmode2->Height;
  }
  return d3dmode1->Width - d3dmode2->Width;
}

int R_SortAdapterRefreshRates(const void* cmp1, const void* cmp2)
{
	const int* r1 = (const int*)cmp1;
	const int* r2 = (const int*)cmp2;
	return *r1 - *r2;
}

typedef struct{
	unsigned int width;
	unsigned int height;
}resolutionPair_t;

void R_EnumDisplayModes(UINT adapterIndex)
{
	int numRefreshRates;
	int i, k;
	int modeCnt;
	char* stringBuf;
	resolutionPair_t sortedResolutions[256];
	unsigned int sortedRefreshRates[256];
	int refreshRateDefault;

	modeCnt = r_dx.d3d9->GetAdapterModeCount(adapterIndex, D3DFMT_X8R8G8B8);

	for(i = 0, r_dx.displayModeCount = 0; i < modeCnt && r_dx.displayModeCount < MAX_ADAPTERMODES; ++i)
	{
      if ( r_dx.d3d9->EnumAdapterModes(adapterIndex, D3DFMT_X8R8G8B8,	i, &r_dx.displayModes[r_dx.displayModeCount]) >= 0 )
      {
        if ( !r_dx.displayModes[r_dx.displayModeCount].RefreshRate )
        {
          r_dx.displayModes[r_dx.displayModeCount].RefreshRate = 60;
        }
        ++r_dx.displayModeCount;
      }
	}
	qsort(r_dx.displayModes, r_dx.displayModeCount, 0x10u, R_SortAdapterModes);

  modeCnt = 0;
	numRefreshRates = 0;
	for(i = 0; i < r_dx.displayModeCount; ++i)
	{
		if(r_dx.displayModes[i].Width < 640 || r_dx.displayModes[i].Height < 480){
			continue;
		}


		if ( (modeCnt <= 0 || sortedResolutions[modeCnt].width != r_dx.displayModes[i].Width || sortedResolutions[modeCnt].height != r_dx.displayModes[i].Height)  )
		{
			sortedResolutions[modeCnt +1].width = r_dx.displayModes[i].Width;
			sortedResolutions[modeCnt +1].height = r_dx.displayModes[i].Height;
			++modeCnt;
		}

		for(k = 0; k < numRefreshRates && sortedRefreshRates[k +1] != r_dx.displayModes[i].RefreshRate; ++k );

		if(k < numRefreshRates)
		{
			continue;
		}

		sortedRefreshRates[numRefreshRates +1] = r_dx.displayModes[i].RefreshRate;
		++numRefreshRates;
	}

	if ( modeCnt == 0 )
	{
		R_FatalInitError("No valid resolutions of %i x %i or above found", 640, 480);
	}

	stringBuf = r_dx.modeStringList;
	for(i = 0; i < modeCnt; ++i)
	{
		r_dx.resolutionStrings[i] = stringBuf;
		stringBuf += sprintf(stringBuf, "%ix%i", sortedResolutions[i + 1].width, sortedResolutions[i + 1].height) + 1;
	}
	r_dx.resolutionStrings[i] = NULL;

	r_mode = Dvar_RegisterEnum("r_mode", r_dx.resolutionStrings, 0, 0x21, "Direct X resolution mode");

	qsort(&sortedRefreshRates[1], numRefreshRates, sizeof(sortedRefreshRates[1]), R_SortAdapterRefreshRates);

    refreshRateDefault = 0;

	for(i = 0; i < numRefreshRates ; ++i)
	{
		r_dx.refreshRateStrings[i] = stringBuf;
		stringBuf += sprintf(stringBuf, "%i Hz", sortedRefreshRates[i + 1]) + 1;

		//Set highest refresh rate but max 60Hz as default
		if ( sortedRefreshRates[i + 1] <= 60 )
		{
			refreshRateDefault = i;
		}

	}

	r_dx.refreshRateStrings[i] = NULL;

	r_displayRefresh = Dvar_RegisterEnum("r_displayRefresh", r_dx.refreshRateStrings, refreshRateDefault, 0x221, "Refresh rate");

}


void R_PreCreateWindow()
{
  if(!r_dx.d3d9)
  {
    Com_Printf(CON_CHANNEL_GFX, "Getting Direct3D 9 interface...\n");

    //Sys_CleanUpNvd3d9Wrap();
    r_dx.d3d9 = Direct3DCreate9(0x20u);
  }


  if ( r_dx.d3d9 )
  {
    r_dx.adapterIndex = R_ChooseAdapter();
    R_StoreDirect3DCaps(r_dx.adapterIndex);
	  R_EnumDisplayModes(r_dx.adapterIndex);
  }
  else
  {
    Com_Printf(CON_CHANNEL_GFX, "Direct3D 9 failed to initialize\n");
  }
}

int R_ClosestRefreshRateForMode(unsigned int width, unsigned int height, unsigned int refreshRate)
{
  int top;
  int bot;
  int comparison;
  int mid;

  bot = 0;
  top = r_dx.displayModeCount - 1;
  while ( bot <= top )
  {
    mid = (bot + top) / 2;
    comparison = r_dx.displayModes[mid].Width - width;
    if ( r_dx.displayModes[mid].Width == width )
    {
      comparison = r_dx.displayModes[mid].Height - height;
      if ( r_dx.displayModes[mid].Height == height )
      {
        comparison = r_dx.displayModes[mid].RefreshRate - refreshRate;
        if ( r_dx.displayModes[mid].RefreshRate == refreshRate )
        {
          return refreshRate;
        }
      }
    }
    if ( comparison >= 0 )
    {
      top = mid - 1;
    }
    else
    {
      bot = mid + 1;
    }
  }
  assert(top >= 0);
  assert(top == bot - 1);

  if ( r_dx.displayModes[top].Width == width && r_dx.displayModes[top].Height == height )
  {
    return r_dx.displayModes[top].RefreshRate;
  }
  assertx(r_dx.displayModes[bot].Width == width && r_dx.displayModes[bot].Height == height, "%i = (%i %i), %i = (%i %i), want (%i %i)",
           top, r_dx.displayModes[top].Width, r_dx.displayModes[bot].Height, bot, r_dx.displayModes[bot].Width, r_dx.displayModes[bot].Height, width, height);

  return r_dx.displayModes[bot].RefreshRate;
}


bool R_SetCustomResolution(GfxWindowParms *wndParms)
{
  int monitorHeight;
  int monitorWidth;

  if ( sscanf(r_customMode->current.string, "%ix%i", &wndParms->displayWidth, &wndParms->displayHeight) != 2 )
  {
    return false;
  }
  if ( R_GetMonitorDimensions(&monitorWidth, &monitorHeight) && (wndParms->displayWidth > monitorWidth || wndParms->displayHeight > monitorHeight) )
  {
    return false;
  }
  return true;
}


void R_SetWndParms(GfxWindowParms *wndParms)
{
  const char *resolutionString;
  int refreshRate;
  const char *refreshRateString;

  wndParms->fullscreen = Dvar_GetBool("r_fullscreen");
  if ( wndParms->fullscreen || !R_SetCustomResolution(wndParms) )
  {
    resolutionString = Dvar_EnumToString(r_mode);
    sscanf(resolutionString, "%ix%i", &wndParms->displayWidth, &wndParms->displayHeight);
  }
  if ( !wndParms->fullscreen )
  {
    if ( !r_dx.adapterNativeIsValid )
    {
      r_dx.adapterNativeIsValid = R_GetMonitorDimensions(&r_dx.adapterNativeWidth, &r_dx.adapterNativeHeight);
    }
    if ( wndParms->displayWidth > r_dx.adapterNativeWidth || wndParms->displayHeight > r_dx.adapterNativeHeight )
    {
      wndParms->displayWidth = r_dx.adapterNativeWidth;
      wndParms->displayHeight = r_dx.adapterNativeHeight;
    }
  }
  wndParms->sceneWidth = wndParms->displayWidth;
  wndParms->sceneHeight = wndParms->displayHeight;
  if ( wndParms->fullscreen )
  {
    refreshRateString = Dvar_EnumToString(r_displayRefresh);
    sscanf(refreshRateString, "%i Hz", &refreshRate);
    wndParms->hz = R_ClosestRefreshRateForMode(wndParms->displayWidth, wndParms->displayHeight, refreshRate);
  }
  else
  {
    wndParms->hz = 60;
  }
  wndParms->x = Dvar_GetInt("vid_xpos");
  wndParms->y = Dvar_GetInt("vid_ypos");
  wndParms->hwnd = 0;
  wndParms->aaSamples = r_aaSamples->current.integer;
}

D3DDEVTYPE R_GetDeviceType()
{
  D3DADAPTER_IDENTIFIER9 id; 
  unsigned int Adapter;

  r_dx.adapterIndex = 0;

  for ( Adapter = 0; ; ++Adapter )
  {
    if ( Adapter >= r_dx.d3d9->GetAdapterCount( ) )
    {
      break;
    }
    if ( r_dx.d3d9->GetAdapterIdentifier( Adapter, 0, &id) >= 0 && strstr(id.Description, "PerfHUD") )
    {
      r_dx.adapterIndex = Adapter;
      return D3DDEVTYPE_REF;
    }
  }
  return D3DDEVTYPE_HAL;
}

HRESULT R_CreateDeviceInternal(HWND hwnd, unsigned int behavior, D3DPRESENT_PARAMETERS *d3dpp)
{
  D3DDEVTYPE devtype;
  HRESULT getModeSuccessCode;
  D3DDISPLAYMODE getModeResult;
  HRESULT hr;
  int attempt, attemptrecover;
#ifdef BLACKOPS
  NvAPI_Status status;
#endif
  Com_Printf(CON_CHANNEL_GFX, "Creating Direct3D device...\n");
  attempt = attemptrecover = 0;
  do
  {
    r_dx.adapterNativeIsValid = R_GetMonitorDimensions(&r_dx.adapterNativeWidth, &r_dx.adapterNativeHeight);
    d3dpp->hDeviceWindow = hwnd;
    devtype = R_GetDeviceType();
    hr = D3DCALLNOLOCKNOERROR( r_dx.d3d9->CreateDevice(r_dx.adapterIndex, devtype, hwnd, behavior, d3dpp, &r_dx.device));
    if ( hr >= 0 )
    {
#ifdef BLACKOPS
      r_dx.nvStereoActivated = 0;
      r_dx.nvStereoHandle = 0;
      status = NvAPI_Stereo_CreateHandleFromIUnknown(r_dx.device, &r_dx.nvStereoHandle);
      if ( status == NVAPI_OK )
      {
        NvAPI_Stereo_IsActivated(r_dx.nvStereoHandle, &res);
        r_dx.nvStereoActivated = res != 0;
      }
#endif
      getModeSuccessCode = r_dx.d3d9->GetAdapterDisplayMode(r_dx.adapterIndex, &getModeResult);
      if ( getModeSuccessCode < 0 )
      {
        r_dx.adapterFullscreenWidth = d3dpp->BackBufferWidth;
        r_dx.adapterFullscreenHeight = d3dpp->BackBufferHeight;
      }
      else
      {
        r_dx.adapterFullscreenWidth = getModeResult.Width;
        r_dx.adapterFullscreenHeight = getModeResult.Height;
      }
      return hr;
    }
    Sys_Sleep(200);
    if ( hr != D3DERR_DEVICELOST )
    {
      ++attempt;
    }
    ++attemptrecover;
  }
  while ( attempt < 20 && attemptrecover < 80);
  if ( !r_dx.adapterIndex )
  {
    return hr;
  }
  r_dx.adapterIndex = 0;
  return R_CreateDeviceInternal(hwnd, behavior, d3dpp);
}


bool R_CreateDevice(GfxWindowParms *wndParms)
{
  D3DPRESENT_PARAMETERS d3dpp;
  HWND hwnd;
  HRESULT hr;
  unsigned int behavior;

  hwnd = 0;
  assert(wndParms);
  assert(r_dx.windowCount == 0);
  assert(wndParms->hwnd);

  hwnd = wndParms->hwnd;
  assert(r_dx.device == NULL);

  r_dx.depthStencilFormat = R_GetDepthStencilFormat(D3DFMT_A8R8G8B8);
  R_SetD3DPresentParameters(&d3dpp, wndParms);
#ifdef BLACKOPS  
  behavior = 64;
  if ( r_multithreaded_device->current.enabled )
  {
    behavior |= 4u;
  }
#else
  behavior = 70;
#endif
  hr = R_CreateDeviceInternal(hwnd, behavior, &d3dpp);
  r_glob.haveThreadOwnership = 1;
  if ( hr >= 0 )
  {
    r_dx.deviceLost = false;
    assert(r_dx.device);
    return true;
  }
  Com_Printf(CON_CHANNEL_GFX, "Couldn't create a Direct3D device: %s\n", R_ErrorDescription(hr));
  return false;
}

void R_FinishAttachingToWindow(GfxWindowParms *wndParms)
{
//(dx.windowCount >= 0 && dx.windowCount < (( 1/(((((0) ? (0x7fffffff) : (-0x7fffffff)) * (((0)&~1) == 0)))/(0x7fffffff)) == 1) ? 5 : 1))
  assert(r_dx.windowCount >= 0 && r_dx.windowCount < 1);
  assert(r_dx.windows[r_dx.windowCount].swapChain);

  r_dx.windows[r_dx.windowCount].hwnd = wndParms->hwnd;
  r_dx.windows[r_dx.windowCount].width = wndParms->displayWidth;
  r_dx.windows[r_dx.windowCount].height = wndParms->displayHeight;
  
  ++r_dx.windowCount;
}

void DB_LoadGraphicsAssetsForPC()
{
  DB_LoadXZoneFromGfxConfig();
}

bool R_CreateForInitOrReset()
{
  HRESULT hr;
  unsigned int fenceIter;

  Com_Printf(CON_CHANNEL_GFX, "Initializing render targets...\n");
  R_InitRenderTargets();
//  RB_StreamInit();
//  R_StreamInit();
  if ( !g_allocateMinimalResources )
  {
    R_InitRenderBuffers();
    R_InitModelLightingImage();
    Com_Printf(CON_CHANNEL_GFX, "Initializing static model cache...\n");
    R_InitStaticModelCache();
  }
  Com_Printf(CON_CHANNEL_GFX, "Initializing dynamic buffers...\n");
  R_CreateDynamicBuffers();
  if ( !g_allocateMinimalResources )
  {
    Com_Printf(CON_CHANNEL_GFX, "Initializing particle cloud buffer...\n");
    R_CreateParticleCloudBuffer();
  }
  Com_Printf(CON_CHANNEL_GFX, "Creating Direct3D queries...\n");
  
  r_dx.nextFence = 0;
  r_dx.flushGpuFenceIssued = 0;

  D3DSEMSTART;

  hr = D3DCALLNOLOCKNOERROR(r_dx.device->CreateQuery(D3DQUERYTYPE_EVENT, &r_dx.flushGpuFence));
  if ( hr < 0 )
  {
    Com_Printf(CON_CHANNEL_GFX, "Event query creation failed: %s (0x%08x)\n", R_ErrorDescription(hr), (unsigned int)hr);
    return false;
  }

  for ( fenceIter = 0; fenceIter < ARRAY_COUNT(r_dx.fencePool); ++fenceIter )
  {
    hr = D3DCALLNOLOCKNOERROR(r_dx.device->CreateQuery(D3DQUERYTYPE_EVENT, &r_dx.fencePool[fenceIter]));
    if ( hr < 0 )
    {
      Com_Printf(CON_CHANNEL_GFX, "Event query creation failed: %s (0x%08x)\n", R_ErrorDescription(hr), (unsigned int)hr);
      return false;
    }
  }

  D3DSEMEND;

  if ( !g_allocateMinimalResources )
  {
    RB_AllocSunSpriteQueries();
//    RB_AllocCoronaSpriteQueries();
//    RB_AllocSuperFlareQueries();

    gfxAssets.pixelCountQuery = RB_HW_AllocOcclusionQuery();
  }
  return true;
}

void R_InitGamma()
{
  Dvar_SetModified(r_gamma);
}

bool R_InitHardware(GfxWindowParms *wndParms)
{
  bool failed;

  if ( !R_CreateDevice(wndParms) )
  {
    return false;
  }
  if ( useFastFile->current.enabled )
  {
    DB_LoadGraphicsAssetsForPC();
  }
  R_UpdateGpuSyncType();
  R_StoreWindowSettings(wndParms);
  RB_InitSceneViewport();
  
  D3DSEMSTART;
  failed = R_CreateForInitOrReset() == 0;
  D3DSEMEND;

  if ( failed )
  {
    return false;
  }
  R_Cinematic_Init();
  Com_Printf(CON_CHANNEL_GFX, "Setting initial state...\n");

  D3DSEMGUARDEDCALL(RB_SetInitialState());

  R_InitGamma();
  R_InitScene();

  D3DSEMGUARDEDCALL(R_InitSystems());
  RB_PixelCost_Init();
  R_FinishAttachingToWindow(wndParms);
  return true;
}




bool R_CreateGameWindow(struct GfxWindowParms *wndParms)
{
  if ( !R_CreateWindow(wndParms) )
  {
    return false;
  }

  if(wndParms->fullscreen)
  {
    Sys_DestroyConsole(); //no more vid_restart bugs. Shitty fix but shall work
  }

  if ( !R_InitHardware(wndParms) )
  {
    if(wndParms->hwnd)
    {
      DestroyWindow(wndParms->hwnd);
      wndParms->hwnd = NULL;
    }
    return false;
  }
  r_dx.targetWindowIndex = 0;
  ShowWindow(wndParms->hwnd, SW_SHOW);
  Sys_DestroySplashWindow();
  return true;
}




bool R_ReduceWindowSettings()
{
  cvar_t *var;
  int value;

  var = r_aaSamples;
  value = r_aaSamples->current.integer;
  if ( r_aaSamples->current.integer > 1 ||
		((var = r_displayRefresh, value = r_displayRefresh->current.integer, value > 0) && vidConfig.displayFrequency > 60) ||
		((var = r_mode, value = r_mode->current.integer, value > 0) && (vidConfig.displayWidth > 640 || vidConfig.displayHeight > 480)) )
  {
    Dvar_SetInt(var, value - 1);
    return true;
  }
  return false;

}


void R_InitGraphicsApi()
{

//	Com_DPrintf(CON_CHANNEL_GFX, "R_InitGraphicsApi():\n");
	struct GfxWindowParms wind;

  assert((r_dx.device != NULL) == (r_dx.d3d9 != NULL));

	if(!com_dedicated || !com_dedicated->current.integer )
	{
		Dvar_SetBool(r_loadForRenderer, qtrue);
	}

	if ( r_dx.device )
	{
		//Com_Printf(CON_CHANNEL_GFX, "Direct3D reported %d megabytes of available texture memory.", r_dx.device->lpVtbl->GetAvailableTextureMem(r_dx.device));
		R_InitSystems();
		return;
	}

	R_PreCreateWindow();

	//Com_Printf(CON_CHANNEL_GFX, "Direct3D reported %d megabytes of available texture memory.", r_dx.device->lpVtbl->GetAvailableTextureMem(r_dx.device));

	//DB_InitXAssetMem();
	while ( 1 )
	{
    R_SetWndParms(&wind);

    if ( R_CreateGameWindow(&wind) )
    {
      break;
    }

	  if ( !R_ReduceWindowSettings() )
	  {
        R_FatalInitError("Couldn't initialize renderer");
	  }
  }

}

void R_Init()
{
  Com_Printf(CON_CHANNEL_GFX, "----- R_Init -----\n");
#ifdef BLACKOPS
  r_glob.remoteScreenLastSceneResolveTarget = 0;
#endif
  Swap_Init();
  R_Register();
  R_InitGlobalStructs();
  R_InitDrawMethod();
  R_InitGraphicsApi();
  RB_RegisterBackendAssets();
  R_InitWater();
  
  if ( !r_dx.deviceLost )
  {
    D3DSEMSTART;
    HRESULT hr = D3DCALLNOLOCKNOERROR(r_dx.device->TestCooperativeLevel( ));
    if ( hr != (D3DERR_DEVICELOST) && hr != (D3DERR_DEVICENOTRESET) )
    {
      r_dx.sunSpriteSamples = RB_CalcSunSpriteSamples();
      if ( !r_dx.sunSpriteSamples )
      {
        Com_Printf(CON_CHANNEL_GFX, "Sun sprite occlusion query calibration failed; reverting to low-quality sun visibility test");
        RB_FreeSunSpriteQueries();
      }
    }
    D3DSEMEND;
  }
}

void R_BeginRegistration(vidConfig_t *vidConfigOut)
{
  Sys_SpawnRenderThread(NULL); //Doing nothing except registering events

  R_Init();
  *vidConfigOut = vidConfig;
  r_glob.startedRenderThread = true;
}


void R_ReleaseForShutdownOrReset()
{
  unsigned int fenceIter;
  int windowIndex;

  D3DSEMSTART;
  for ( windowIndex = 0; windowIndex < r_dx.windowCount; ++windowIndex )
  {
    D3DRELEASEBUFFER(r_dx.windows[windowIndex].swapChain);
  }
  R_ShutdownRenderTargets();
  R_ShutdownModelLightingImage();
  R_ShutdownStaticModelCache();
  R_DestroyDynamicBuffers();
  R_DestroyParticleCloudBuffer();
  if ( !g_allocateMinimalResources )
  {
    R_ShutdownRenderBuffers();
  }
  
  assert(!gfxBuf.smodelCacheVb);

  if ( r_dx.flushGpuFence )
  {
    D3DRELEASEBUFFER(r_dx.flushGpuFence);
  }
  for ( fenceIter = 0; fenceIter < 8; ++fenceIter )
  {
    if ( r_dx.fencePool[fenceIter] )
    {
      D3DRELEASEBUFFER(r_dx.fencePool[fenceIter]);
    }
  }
/*  
  for ( gpuIdx = 0; gpuIdx < 4; ++gpuIdx )
  {
    if ( r_dx.swapFence[gpuIdx] )
    {
      r_dx.swapFence[gpuIdx] = 0;
    }
  }
  RB_FreeSuperFlareQueries();
*/
  RB_FreeSunSpriteQueries();
/*  RB_FreeCoronaSpriteQueries();
  for ( i = 0; i < 4; ++i )
  {
    if ( gfxAssets[i] )
    {
      D3DRELEASEBUFFER(gfxAssets.pixelCountQuery[gpuIdx]);
    }
  }
*/
  if ( gfxAssets.pixelCountQuery )
  {
    D3DRELEASEBUFFER(gfxAssets.pixelCountQuery);
  }
  D3DSEMEND;
}

void R_ShutdownStreams()
{
  if ( r_dx.device && !r_dx.deviceLost)
  {
    R_ClearAllStreamSources(&gfxCmdBufState.prim);
  }
}

void R_UnloadGraphicsAssets()
{
  DB_ShutdownXAssets();
}

void R_ShutdownDirect3DInternal()
{
//  R_FreeWaterSimulationBuffers();
  if ( useFastFile->current.enabled )
  {
    R_UnloadGraphicsAssets();
  }
  R_Cinematic_Shutdown();
  R_ReleaseForShutdownOrReset();
  for(;r_dx.windowCount > 0; --r_dx.windowCount)
  {
    int index = r_dx.windowCount -1;
    assert(r_dx.windows[index].hwnd);

    if ( IsWindow(r_dx.windows[index].hwnd) )
    {
      DestroyWindow(r_dx.windows[index].hwnd);
    }
    r_dx.windows[index].hwnd = 0;
  }
  R_AssertDXDeviceOwnership();
  if ( r_dx.device )
  {
/*    
    NvAPI_Stereo_DestroyHandle(r_dx.nvStereoHandle);
    r_dx.nvStereoHandle = 0;
*/
    D3DCALLNOLOCKNOERROR(r_dx.device->Release( ));
    r_dx.device = NULL;
  }
  if ( r_dx.d3d9 )
  {
    D3DCALLNOLOCKNOERROR(r_dx.d3d9->Release( ));
    r_dx.d3d9 = NULL;
  }
}

void R_ShutdownDirect3D()
{
  R_ShutdownDirect3DInternal();
}


void R_ShutdownInternal(bool g_destroy_window)
{

  if ( rg.registered )
  {
    R_SyncRenderThread();
    
    D3DSEMSTART;
    
    rg.registered = false;

    Sys_ClearRGRegisteredEvent();

    r_glob.startedRenderThread = false;
/*
    R_StreamSyncThenFlush(0);
    R_StreamShutdown();
*/
    R_ShutdownStreams();
/*
    R_ShutdownMaterialUsage();
*/
    R_ShutdownDebug();
    R_SaveLightVisHistory();
    R_ShutdownLightDefs();
    R_ShutdownWorld();
/*
    R_ShutdownModels();
*/    
    if ( !useFastFile->current.enabled )
    {
      R_ShutdownLoadWater();
      R_ShutdownFonts();
      Material_Shutdown();
      R_ShutdownImages();
    }
/*
    R_VertexStream2_Shutdown();
    R_FoliageShutdown();
    R_ClearSkyboxModel();
*/
    R_ResetModelLighting();

    rgp.world = 0;
    
    R_UnlockSkinnedCache();
    R_FlushStaticModelCache();
    if ( g_destroy_window )
    {
   
      R_ShutdownDirect3D();
      R_ShutdownRenderCommands();
    }
    
    D3DSEMEND;

    R_UnregisterCmds();
  }
}

void R_Shutdown(bool g_destroy_window)
{
  R_ShutdownInternal(g_destroy_window);
}


bool R_ResetDevice()
{
  D3DPRESENT_PARAMETERS d3dpp;
  HRESULT hr;
  GfxWindowParms wndParms;
  tagRECT rc;

  wndParms.hwnd = r_dx.windows[0].hwnd;
  wndParms.x = 0;
  wndParms.y = 0;
  wndParms.displayWidth = r_dx.windows[0].width;
  wndParms.displayHeight = r_dx.windows[0].height;
  wndParms.sceneWidth = r_dx.windows[0].width;
  wndParms.sceneHeight = r_dx.windows[0].height;
  wndParms.hz = vidConfig.displayFrequency;
  wndParms.fullscreen = vidConfig.isFullscreen != 0;
  wndParms.aaSamples = r_aaSamples->current.integer;

  R_SetD3DPresentParameters(&d3dpp, &wndParms);
  if ( d3dpp.Windowed )
  {
    Com_Printf(CON_CHANNEL_GFX, "Resetting %i x %i window.\n", d3dpp.BackBufferWidth, d3dpp.BackBufferHeight);
  }
  else
  {
    Com_Printf(CON_CHANNEL_GFX, "Resetting %i x %i fullscreen.\n", d3dpp.BackBufferWidth, d3dpp.BackBufferHeight);
  }
  R_ReleaseForShutdownOrReset();

  hr = D3DCALLNOLOCKNOERROR(r_dx.device->Reset(&d3dpp));
  if ( hr != D3D_OK)
  {
    R_FatalInitError("Couldn't reset a lost Direct3D device - IDirect3DDevice9::Reset returned 0x%08x", hr);
    return false;
  }
  r_dx.deviceLost = false;
  if ( wndParms.fullscreen )
  {
    SetWindowPos(wndParms.hwnd, (HWND)-1, 0, 0, 0, 0, 3u);
  }
  else
  {
    rc.left = 0;
    rc.right = wndParms.displayWidth;
    rc.top = 0;
    rc.bottom = wndParms.displayHeight;
    AdjustWindowRectEx(&rc, 0xC80000u, 0, 0);
    SetWindowPos(wndParms.hwnd, (HWND)-2, wndParms.x, wndParms.y, rc.right - rc.left, rc.bottom - rc.top, 0x62u);
  }
  
  if ( !R_CreateForInitOrReset() )
  {
    R_FatalInitError("Couldn't reinitialize after a lost Direct3D device");
  }
  
  R_InitCmdBufSourceState(&gfxCmdBufSourceState, &gfxCmdBufInput, 0);
  R_InitCmdBufState(&gfxCmdBufState);
  RB_InitSceneViewport();
  R_SetRenderTargetSize(&gfxCmdBufSourceState, R_RENDERTARGET_FRAME_BUFFER);
  R_SetRenderTarget(gfxCmdBufContext, R_RENDERTARGET_FRAME_BUFFER);
  return true;
}


bool R_RecoverLostDevice()
{
  assert(r_dx.device);
  if ( r_dx.device->TestCooperativeLevel( ) == D3DERR_DEVICELOST )
  {
    return false;
  }

  Com_Printf(CON_CHANNEL_GFX, "Recovering lost device...\n");
  
  int remoteScreenUpdateNesting = R_PopRemoteScreenUpdate();
  R_SyncRenderThread();  

  Com_Printf(CON_CHANNEL_GFX, "R_Cinematic_BeginLostDevice()...\n");
  R_Cinematic_BeginLostDevice();

  Com_Printf(CON_CHANNEL_GFX, "DB_BeginRecoverLostDevice()...\n");
  DB_BeginRecoverLostDevice();

  Com_Printf(CON_CHANNEL_GFX, "R_ResetModelLighting()...\n");
  R_ResetModelLighting();
  
  Com_Printf(CON_CHANNEL_GFX, "R_ReleaseLostImages()...\n");
  R_ReleaseLostImages();

  Com_Printf(CON_CHANNEL_GFX, "Material_ReleaseAll()...\n");
  Material_ReleaseAll();

  Com_Printf(CON_CHANNEL_GFX, "R_ReleaseWorld()...\n");
  R_ReleaseWorld();

  Com_Printf(CON_CHANNEL_GFX, "R_ResetDevice()...\n");
  if ( !R_ResetDevice() )
  {
    return false;
  }

  Com_Printf(CON_CHANNEL_GFX, "R_ReloadWorld()...\n");
  R_ReloadWorld();
  Com_Printf(CON_CHANNEL_GFX, "Material_ReloadAll()...\n");
  Material_ReloadAll();
  Com_Printf(CON_CHANNEL_GFX, "R_ReloadLostImages()...\n");
  R_ReloadLostImages();

  r_dx.sunSpriteSamples = RB_CalcSunSpriteSamples();

  Com_Printf(CON_CHANNEL_GFX, "DB_EndRecoverLostDevice()...\n");
  DB_EndRecoverLostDevice();
  Com_Printf(CON_CHANNEL_GFX, "R_Cinematic_EndLostDevice()...\n");
  R_Cinematic_EndLostDevice();

#pragma msg "Check R_AbortRenderCommands"

  Com_Printf(CON_CHANNEL_GFX, "R_AbortRenderCommands()...\n");
  R_AbortRenderCommands();
  Com_Printf(CON_CHANNEL_GFX, "R_PushRemoteScreenUpdate()...\n");
  R_PushRemoteScreenUpdate(remoteScreenUpdateNesting);
  Com_Printf(CON_CHANNEL_GFX, "Finished recovering lost device.\n");
  return 1;
}


bool R_CheckLostDevice()
{
  HRESULT hr;

  if ( r_dx.device )
  {
    if ( !r_dx.deviceLost )
    {
      hr = r_dx.device->TestCooperativeLevel( );
      if ( hr != D3DERR_DEVICENOTRESET && hr != D3DERR_DEVICELOST )
      {
        return true;
      }
      R_SyncRenderThread();
      r_dx.deviceLost = true;
    }
    if ( Sys_IsMainThread() )
    {
      R_RecoverLostDevice();
    }
  }
  return 0;
}


void R_ComErrorCleanup()
{
  assert(Sys_IsMainThread());

  R_AbortRenderCommands();
  R_SyncRenderThread();
  if ( r_dx.inScene )
  {
    D3DCALL(r_dx.device->EndScene());

    r_dx.inScene = false;
  }
}