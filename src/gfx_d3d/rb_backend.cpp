#include "rb_backend.h"
#include "r_local.h"
#include "r_image.h"
#include "../common/sys_shared.h"
#include "gfx_world.h"

void RB_InitBackendGlobalStructs()
{
  memset(&backEnd, 0, sizeof(backEnd));

  RB_InitSceneViewport();
  RB_InitCodeImages();
}

void RB_InitSceneViewport()
{
  gfxCmdBufSourceState.sceneViewport.x = 0;
  gfxCmdBufSourceState.sceneViewport.y = 0;
  gfxCmdBufSourceState.sceneViewport.width = vidConfig.displayWidth;
  gfxCmdBufSourceState.sceneViewport.height = vidConfig.displayHeight;
}

D3DQuery *RB_HW_AllocOcclusionQuery()
{
  HRESULT hr;
  D3DQuery *query;

  R_AssertDXDeviceOwnership();
  hr = D3DCALLNOLOCKNOERROR(r_dx.device->CreateQuery(D3DQUERYTYPE_OCCLUSION, &query));
  if ( hr >= 0 )
  {
    return query;
  }
  Com_Printf(CON_CHANNEL_GFX, "Occlusion query creation failed: %s (0x%08x)\n", R_ErrorDescription(hr), (unsigned int)hr);
  return NULL;
}

void R_HW_InsertFence(D3DQuery **fence)
{
  R_AssertDXDeviceOwnership();

  *fence = r_dx.fencePool[r_dx.nextFence];
  r_dx.nextFence = (r_dx.nextFence + 1) % ARRAY_COUNT(r_dx.fencePool);

  D3DSEMSTART;
  
  D3DCALL((*fence)->Issue( (1 << 0) ));

  D3DSEMEND;
}


void RB_StretchRaw(int x, int y, int w, int h, int cols, int rows, const unsigned char *data, int client, int dirty)
{
  D3DLOCKED_RECT lockedRect;
  IDirect3DSurface9 *rawSurf;
  unsigned char *dest;
  tagRECT dstRect;
  int colIndex;
  int newline;
  int rowIndex;

  D3DCALL(r_dx.device->CreateOffscreenPlainSurface( cols, rows, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &rawSurf, 0 ));
  D3DCALL(rawSurf->LockRect( &lockedRect, 0, 0x00002000L ));

  dest = (unsigned char *)lockedRect.pBits;
  newline = lockedRect.Pitch - 4 * cols;
  for ( rowIndex = 0; rowIndex < rows; ++rowIndex )
  {
    for ( colIndex = 0; colIndex < cols; ++colIndex )
    {
      Byte4CopyRgbaToVertexColor(data, dest);
      data += 4;
      dest += 4;
    }
    dest += newline;
  }
  D3DCALLNOLOCKNOERROR(rawSurf->UnlockRect( ));
  dstRect.left = x;
  dstRect.top = y;
  dstRect.right = w + x;
  dstRect.bottom = h + y;
  
  D3DCALL(r_dx.device->StretchRect( rawSurf, 0, gfxRenderTargets[R_RENDERTARGET_FRAME_BUFFER].surface.color, &dstRect, D3DTEXF_LINEAR ));

  rawSurf->Release( );
}


void R_Resolve(GfxCmdBufContext context, GfxImage *image)
{
  D3DSurface *imageSurface;

  assert(image);
  assert(image->width == gfxRenderTargets[context.state->renderTargetId].width);
  assert(image->height == gfxRenderTargets[context.state->renderTargetId].height);
  assert(image != gfxRenderTargets[context.state->renderTargetId].image);

  imageSurface = Image_GetSurface(image);

  assert(imageSurface);
/*
  a = r_reflectionProbeGenerate->current.enabled;

  if ( context.state->renderTargetId == 3 && a )
  {
    w = gfxRenderTargets[3].width;
    h = gfxRenderTargets[3].height;
    surf = gfxRenderTargets[2].surface.color;
    surfd = gfxRenderTargets[16].surface.color;
    surfx = gfxRenderTargets[17].surface.color;
    surfxd = gfxRenderTargets[18].surface.color;
    context.state->prim.device->vfptr[4].QueryInterface(
      (IDirect3DQuery9 *)context.state->prim.device,
      (const IID *const )gfxRenderTargets[2].surface.color,
      (void **)gfxRenderTargets[16].surface.color);
    Sleep(0x64u);
    ((void (__stdcall *)(IDirect3DSurface9 *, _D3DLOCKED_RECT *, _DWORD, _DWORD))surfd->vfptr[1].GetDataSize)(surfd, &rs, 0, 0);
    bitss = (unsigned __int16 *)rs.pBits;
    ((void (__stdcall *)(IDirect3DSurface9 *, _D3DLOCKED_RECT *, _DWORD, _DWORD))surfx->vfptr[1].GetDataSize)(surfx, &rd, 0, 0);
    bitsd = (char *)rd.pBits;
    if ( !bitss || !rd.pBits )
    {
      ((void (__stdcall *)(IDirect3DSurface9 *))surfx->vfptr[1].Issue)(surfx);
      ((void (__stdcall *)(IDirect3DSurface9 *))surfd->vfptr[1].Issue)(surfd);
      return;
    }
    for ( y = 0; y < h; ++y )
    {
      for ( x = 0; x < w; ++x )
      {
        r = bitss[2];
        g = bitss[1];
        b = *bitss;
        v18 = bitss[3];
        bitss += 4;
        LODWORD(rf) = ((r & 0x3FF) << 13) | (((r & 0x7C00) + 114688) << 13) | ((unsigned __int16)(r & 0x8000) << 16);
        LODWORD(gf) = ((g & 0x3FF) << 13) | (((g & 0x7C00) + 114688) << 13) | ((unsigned __int16)(g & 0x8000) << 16);
        LODWORD(bf) = ((b & 0x3FF) << 13) | (((b & 0x7C00) + 114688) << 13) | ((unsigned __int16)(b & 0x8000) << 16);
        if ( rf > 1.0 )
        {
          rf = FLOAT_1_0;
        }
        if ( gf > 1.0 )
        {
          gf = FLOAT_1_0;
        }
        if ( bf > 1.0 )
        {
          bf = FLOAT_1_0;
        }
        *bitsd = (signed int)(float)(rf * 255.0);
        bitsd[1] = (signed int)(float)(gf * 255.0);
        bitsd[2] = (signed int)(float)(bf * 255.0);
        bitsd[3] = v18;
        bitsd += 4;
      }
      bitss -= 4 * w;
      bitss += rs.Pitch / 2;
      bitsd = &bitsd[rd.Pitch + -4 * w];
    }
    ((void (__stdcall *)(IDirect3DSurface9 *))surfx->vfptr[1].Issue)(surfx);
    ((void (__stdcall *)(IDirect3DSurface9 *))surfd->vfptr[1].Issue)(surfd);
    ((void (__stdcall *)(IDirect3DDevice9 *, IDirect3DSurface9 *, _DWORD, IDirect3DSurface9 *, _DWORD))context.state->prim.device->vfptr[3].Issue)(context.state->prim.device, surfx, 0, surfxd, 0);
    R_AssertDXDeviceOwnership();
    if ( r_logFile )
    {
      if ( r_logFile->current.integer )
      {
        RB_LogPrint("context.state->prim.device->StretchRect( gfxRenderTargets[R_RENDERTARGET_SCENE].surface.color, 0, imageSurface, 0, D3DTEXF_LINEAR)\n");
      }
    }
    semaphore = R_AcquireDXDeviceOwnership(0);
    hr = ((int (__stdcall *)(IDirect3DDevice9 *, IDirect3DSurface9 *, _DWORD, IDirect3DSurface9 *, _DWORD, signed int))context.state->prim.device->vfptr[4].Release)(
           context.state->prim.device,
           gfxRenderTargets[3].surface.color,
           0,
           imageSurface,
           0,
           2);
    if ( semaphore )
    {
      R_ReleaseDXDeviceOwnership();
    }
    if ( hr < 0 )
    {
      ++g_disableRendering;
      v8 = R_ErrorDescription(hr);
      Com_Error(
        0,
        "C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\rb_backend.cpp (%i) context.state->prim.device->StretchRect( gfxRenderTargets[R_RENDERTARGET_SCENE].surface.color, 0, imageSurface, 0, D3DTEXF_LINEAR) failed: %s\n",
        1348,
        v8);
    }
  }
  else
  {
*/
  D3DCALL(context.state->prim.device->StretchRect( gfxRenderTargets[context.state->renderTargetId].surface.color, 0, imageSurface, 0, D3DTEXF_NONE));
//  }
  
  D3DCALL(imageSurface->Release());

}

struct GfxRenderCommandExecState
{
  const void *cmd;
};


/**************************************************************************
GfxCmdSaveScreen
***************************************************************************/

struct GfxCmdSaveScreen
{
  GfxCmdHeader header;
  int screenTimerId;
};


void RB_SaveScreenCmd(GfxRenderCommandExecState *execState)
{
  GfxCmdSaveScreen *cmd;

  cmd = (GfxCmdSaveScreen *)execState->cmd;
  
  if ( tess.indexCount ){
    RB_EndTessSurface();
  }

  R_Resolve(gfxCmdBufContext, gfxRenderTargets[0].image);
  rgp.savedScreenTimes[cmd->screenTimerId] = gfxCmdBufSourceState.sceneDef.time;

	execState->cmd = (char *)execState->cmd + cmd->header.byteCount;
}



/**************************************************************************
GfxCmdStretchRaw
***************************************************************************/
struct GfxCmdStretchRaw
{
  GfxCmdHeader header;
  int x;
  int y;
  int w;
  int h;
  int cols;
  int rows;
  const char *data;
  int client;
  int dirty;
};

void RB_StretchRawCmd(GfxRenderCommandExecState *execState)
{
  GfxCmdStretchRaw *cmd = (GfxCmdStretchRaw*)execState->cmd;

  RB_StretchRaw(cmd->x, cmd->y, cmd->w, cmd->h, cmd->cols, cmd->rows, (const unsigned char*)cmd->data, cmd->client, cmd->dirty);

	execState->cmd = (char *)execState->cmd + cmd->header.byteCount;
}


void RB_SwapBuffers()
{
  HRESULT hr;


  assert(r_dx.targetWindowIndex >= 0 && r_dx.targetWindowIndex < r_dx.windowCount);
/*
  if ( rg.renderHiResShot || r_dx.resizeWindow )
  {
    hr = 0;
  }
  else
  {*/
    hr = r_dx.windows[r_dx.targetWindowIndex].swapChain->Present(0, 0, 0, 0, 0);
/*
  }

  mjpeg_draw(r_dx.device, 0);
  
  if ( r_dx.resizeWindow )
  {
    R_ResizeWindow();
    hr = -2005530520;
  }
  if ( hr == -2005530520 )
  {
    Sys_ClearD3DDeviceOKEvent();
    if ( !r_glob.isRenderingRemoteUpdate )
    {
      while ( Sys_QueryRenderEvent() )
      {
        semaphore = R_ReleaseDXDeviceOwnership();
        NET_Sleep(1);
        if ( semaphore )
        {
          R_AcquireDXDeviceOwnership(0);
        }
      }
    }
  }

  desiredShow = (g_showCursor != 0) - 1;
  for ( actualShow = ShowCursor(g_showCursor); actualShow != desiredShow; actualShow = ShowCursor(actualShow < desiredShow) )
  {
    ;
  }
  while ( PeekMessageA(&msg, 0, 0, 0, 0) )
  {
    if ( !GetMessageA(&msg, 0, 0, 0) )
    {
      Sys_SetWin32QuitEvent();
    }
    dword_9B73494 = msg.time;
    TranslateMessage(&msg);
    DispatchMessageA(&msg);
  }
  if ( hr == D3DERR_DEVICELOST )
  {
    while ( hr )
    {
      hr = r_dx.device->TestCooperativeLevel( );
      if ( r_dx.resizeWindow )
      {
        hr = D3DERR_DEVICENOTRESET;
        r_dx.resizeWindow = 0;
      }
      if ( hr == D3DERR_DEVICELOST )
      {
        if ( !assets_released )
        {
          R_ReleaseLostDeviceAssets2();
          R_ReleaseForShutdownOrReset();
          assets_released = 1;
        }
        NET_Sleep(5);
      }
      else if ( hr == D3DERR_DEVICENOTRESET )
      {
        if ( !assets_released )
        {
          R_ReleaseLostDeviceAssets2();
          R_ReleaseForShutdownOrReset();
          assets_released = 1;
        }
        if ( R_RecoverLostDevice() )
        {
          assets_released = 0;
        }
      }
      else if ( hr )
      {
        Com_Error(ERR_FATAL, "Direct3DDevice9::Present failed: %s (%d)\n", R_ErrorDescription(hr), hr);
      }
      while ( PeekMessageA(&msg, 0, 0, 0, 0) )
      {
        if ( !GetMessageA(&msg, 0, 0, 0) )
        {
          Sys_SetWin32QuitEvent();
        }
        dword_9B73494 = msg.time;
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
      }
    }
    Sys_SetD3DDeviceOKEvent();
  }
  else if ( hr )
  {
    R_ReleaseDXDeviceOwnership();
    if ( r_glob.isRenderingRemoteUpdate )
    {
      Sys_LeaveCriticalSection(CRITSECT_DBHASH);
    }
    Com_Error(ERR_FATAL, "Direct3DDevice9::Present failed: %s (%d)\n", R_ErrorDescription(hr), hr);
  }
*/
  if(hr < 0 && hr != D3DERR_DEVICELOST)
  {
    Com_Error(ERR_FATAL, "Direct3DDevice9::Present failed: %s (%d)\n", R_ErrorDescription(hr), hr);
  }

  //R_HW_InsertFence(&r_dx.swapFence[r_glob.backEndFrameCount % r_dx.gpuCount]);

  R_HW_InsertFence(&r_dx.swapFence);

  gfxBuf.dynamicIndexBuffer->used = 0;
}


void RB_UpdateBackEndDvarOptions()
{
  if ( !r_dx.device->TestCooperativeLevel( ) )
  {
    if ( R_CheckDvarModified(r_texFilterAnisoMax) || R_CheckDvarModified(r_texFilterDisable) || R_CheckDvarModified(r_texFilterAnisoMin) ||
      R_CheckDvarModified(r_texFilterMipMode) || R_CheckDvarModified(r_texFilterMipBias))
    {
      R_SetTexFilter();
    }

    if ( R_CheckDvarModified(r_showPixelCost) && !r_showPixelCost->current.integer )
    {
      R_PixelCost_PrintColorCodeKey();
    }
    if ( R_CheckDvarModified(r_aaAlpha) )
    {
#pragma msg "Remove the if condition maybe (CoD4)"
      if ( gfxMetrics.hasTransparencyMsaa )
      {
        R_SetAlphaAntiAliasingState(gfxCmdBufState.prim.device, gfxCmdBufState.activeStateBits[0]);
      }
    }
  }
}





void RB_EndFrame(unsigned int drawType)
{
  if ( !(drawType & 2) )
  {
    return;
  }

  _RB_LogPrintf("***************** RB_SwapBuffers *****************\n\n\n");

  RB_SwapBuffers();
  RB_UpdateLogging();

  assert(r_gamma);
  assert(r_ignoreHwGamma);

  if ( r_gamma->modified || r_ignoreHwGamma->modified )
  {
    Dvar_ClearModified(r_gamma);
    Dvar_ClearModified(r_ignoreHwGamma);
    if ( !r_ignoreHwGamma->current.enabled )
    {
      R_SetColorMappings();
    }
  }
  
}


void RB_PatchStaticModelCache()
{
  static_model_leaf_t *cachedSurf;
  unsigned int vertCount;
  void *bufferData;
  D3DVertexBuffer *handle;
  unsigned int firstPatchVert;
  unsigned int patchIter;

  if ( backEndData->smcPatchCount )
  {
    handle = gfxBuf.smodelCacheVb;
    firstPatchVert = 0;
    for ( patchIter = 0; patchIter < backEndData->smcPatchCount; ++patchIter )
    {
      cachedSurf = R_GetCachedSModelSurf(backEndData->smcPatchList[patchIter]);
      vertCount = XModelGetStaticModelCacheVertCount(rgp.world->dpvs.smodelDrawInsts[cachedSurf->cachedSurf.smodelIndex].model, cachedSurf->cachedSurf.lodIndex);
      bufferData = R_LockVertexBuffer(handle, 32 * cachedSurf->cachedSurf.baseVertIndex, 32 * vertCount, 4096);
      memcpy(bufferData, &backEndData->smcPatchVerts[firstPatchVert], sizeof(backEndData->smcPatchVerts[0]) * vertCount);
      R_UnlockVertexBuffer(handle);
      firstPatchVert += vertCount;
    }
  }
}


void RB_BeginFrame(const void *data)
{

  backEndData = (GfxBackEndData *)data;
  if ( backEndData->drawType & 1 )
  {
/*
  int rt;
    if ( !rg.renderHiResShot )
    {
      ++r_glob.backEndFrameCount;
    }
    for ( rt = 0; rt < ARRAY_COUNT(gfxRenderTargets); ++rt )
    {
      gfxRenderTargets[rt].cleared = 0;
    }

    R_Cinematic_UpdateFrame(0);
*/
    RB_UpdateBackEndDvarOptions();
    
    RB_PatchStaticModelCache();
    
    RB_PatchModelLighting(backEndData->modelLightingPatchList, backEndData->modelLightingPatchCount);

    assert(r_dx.device);
    assert(!r_dx.inScene);

    r_dx.inScene = true;

    D3DCALL(r_dx.device->BeginScene());

    //R_InitCmdBufSamplerState(&gfxCmdBufState);
    RB_UploadShaderStep();
    R_Cinematic_UpdateFrame(0);
    tess.indexCount = 0;
    tess.vertexCount = 0;
  }
}



void RB_SetGammaRamp(const GfxGammaRamp *gammaTable)
{
  unsigned int colorIndex;
  D3DGAMMARAMP d3dGammaRamp;

  assert(gammaTable != NULL);
  assert(vidConfig.deviceSupportsGamma == true);
  assert(r_dx.device != NULL);

  for ( colorIndex = 0; colorIndex < ARRAY_COUNT(gammaTable->entries); ++colorIndex )
  {
    d3dGammaRamp.red[colorIndex] = gammaTable->entries[colorIndex];
    d3dGammaRamp.green[colorIndex] = gammaTable->entries[colorIndex];
    d3dGammaRamp.blue[colorIndex] = gammaTable->entries[colorIndex];
  }
  D3DCALLNOLOCKNOERRORNORETVAL(r_dx.device->SetGammaRamp(r_dx.targetWindowIndex, 0, &d3dGammaRamp));
}


void R_InitLocalCmdBufState(GfxCmdBufState *state)
{
  if(&gfxCmdBufState != state)
  {
    memcpy(state, &gfxCmdBufState, sizeof(*state));
  }
  memset((char *)state->vertexShaderConstState, 0, sizeof(state->vertexShaderConstState));
  memset((char *)state->pixelShaderConstState, 0, sizeof(state->pixelShaderConstState));
}


void RB_CallExecuteRenderCommands()
{
  PIXBeginNamedEvent(-1, "RB_CallExecuteRenderCommands");

  assert(backEndData);
#ifdef BLACKOPS
  if ( !(backEndData->drawType & 0x12) )
#else
  if ( !(backEndData->drawType & 2) )
#endif
  {
    return;
  }
  assert(!tess.indexCount);

  if ( backEndData->viewInfoCount )
  {
    RB_Draw3DCommon();
  }

  assert(!tess.indexCount);

//  RB_UI3D_RenderToTexture(backEndData->cmds, &backEndData->rbUI3D, &gfxCmdBufInput);

  R_InitCmdBufSourceState(&gfxCmdBufSourceState, &gfxCmdBufInput, 0);
  gfxCmdBufSourceState.input.data = (GfxBackEndData *)backEndData;
  R_InitLocalCmdBufState(&gfxCmdBufState);
  R_SetRenderTargetSize(&gfxCmdBufSourceState, R_RENDERTARGET_FRAME_BUFFER);
  R_SetRenderTarget(gfxCmdBufContext, R_RENDERTARGET_FRAME_BUFFER);
  RB_InitSceneViewport();


/*
  v0 = gfxCmdBufSourceState.input.consts[170];
  gfxCmdBufSourceState.input.consts[170][0] = 0.0;
  v0[1] = 0.0;
  v0[2] = 0.0;
  v0[3] = 0.0;
  R_DirtyCodeConstant(&gfxCmdBufSourceState, 0xAAu);
  v1 = gfxCmdBufSourceState.input.consts[171];
  gfxCmdBufSourceState.input.consts[171][0] = 0.0;
  v1[1] = 0.0;
  v1[2] = 0.0;
  v1[3] = 0.0;
  R_DirtyCodeConstant(&gfxCmdBufSourceState, 0xABu);
  if ( rgp.heatMapImage )
  {
    R_SetCodeImageTexture(&gfxCmdBufSourceState, 0x2Au, rgp.heatMapImage);
  }
  else
  {
    R_SetCodeImageTexture(&gfxCmdBufSourceState, 0x2Au, rgp.whiteImage);
  }
  RB_SetUI3DSamplerAndConstants(&gfxCmdBufSourceState, &backEndData->rbUI3D);
  
  */

  if ( backEndData->cmds )
  {
    PIXBeginNamedEvent(-1, "backEndData->cmds");
    RB_ExecuteRenderCommandsLoop(backEndData->cmds);
/*    
    if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
    {
      D3DPERF_EndEvent();
    }
*/
  }

/* 
  if ( r_drawPrimHistogram->current.enabled )
  {
    RB_DrawPrimHistogramOverlay();
  }
*/

  if ( tess.indexCount )
  {
    RB_EndTessSurface();
  }

  //memcpy(gfxCmdBufState, gfxCmdBufState, sizeof(gfxCmdBufState));
  
  if ( gfxCmdBufState.prim.indexBuffer )
  {
    R_ChangeIndices(&gfxCmdBufState.prim, NULL);
  }


  R_ClearAllStreamSources(&gfxCmdBufState.prim);

  assert(!tess.indexCount);
  assert(r_dx.device);
  assert(r_dx.inScene);

  D3DCALL(r_dx.device->EndScene());

  r_dx.inScene = false;
  
  if ( !r_glob.isRenderingRemoteUpdate )
  {
    if ( r_dx.gpuSync )
    {

      R_AcquireGpuFenceLock();
      sub_615230();
      if ( r_dx.gpuSync == 2 ){
        r_dx.gpuSyncDelay = (uint64_t)(30.0 / msecPerRawTimerTick);
      }
      R_InsertGpuFence();
      R_ReleaseGpuFenceLock();
    }
    else
    {
      r_dx.gpuSyncDelay = 0;
    }
  }
/*
  backEndData = 0;
  
  if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
  {
    D3DPERF_EndEvent();
  }
*/
}


void RB_ResetStatTracking(int viewIndex)
{

}

void R_TessEnd(GfxCmdBufContext context, GfxCmdBufContext prepassContext)
{
    GfxDepthRangeType depthRangeType;
    GfxCmdBufSourceState* commonSource;

    commonSource = context.source;

    assert(prepassContext.state == NULL || commonSource == prepassContext.source);

    commonSource->objectPlacement = 0;
    R_ChangeDepthHackNearClip(commonSource, 0);
    if(commonSource->cameraView == 0)
    {
      depthRangeType = GFX_DEPTH_RANGE_FULL;
    }else{
      depthRangeType = GFX_DEPTH_RANGE_SCENE;
    }
    if ( depthRangeType != context.state->depthRangeType )
    {
        R_ChangeDepthRange(context.state, depthRangeType);
    }
    if ( prepassContext.state )
    {
        if(prepassContext.source->cameraView == 0)
        {
          depthRangeType = GFX_DEPTH_RANGE_FULL;
        }else{
          depthRangeType = GFX_DEPTH_RANGE_SCENE;
        }
        if ( depthRangeType != prepassContext.state->depthRangeType )
        {
            R_ChangeDepthRange(prepassContext.state, depthRangeType);
        }
    }
}

unsigned int R_RenderDrawSurfListMaterial(GfxDrawSurfListArgs *listArgs, GfxCmdBufContext prepassContext)
{
    unsigned int firstDrawSurfIndex;
    unsigned int passIndex;
    GfxCmdBufContext passPrepassContext;

    GfxDrawSurf drawSurf;
    unsigned int subListCount;
    uint16_t passCount;
    GfxDrawSurf *drawSurfList;
    bool isPixelCostEnabled;
    unsigned int drawSurfCount;

    firstDrawSurfIndex = listArgs->firstDrawSurfIndex;
    drawSurfCount = listArgs->info->drawSurfCount - listArgs->firstDrawSurfIndex;
    drawSurfList = &listArgs->info->drawSurfs[firstDrawSurfIndex];
    assert(*((unsigned int*)drawSurfList) != 0xb0b0b0b0);

    drawSurf = *drawSurfList;
/*
    v4 = RB_ShaderConstantSetFromDrawSurf(listArgs->context.source->input.data, &drawSurf);
    ScopedShaderConstantSetUndo::ScopedShaderConstantSetUndo(&shaderConstantUndo, listArgs->context.source, v4);
*/
    if ( !R_SetTechnique(listArgs->context, &prepassContext, listArgs->info, drawSurf) )
    {
      return R_SkipDrawSurfListMaterial(drawSurfList, drawSurfCount);
      //ScopedShaderConstantSetUndo::~ScopedShaderConstantSetUndo(&shaderConstantUndo);
    }
    /*
    R_SetPixPrimarySortKey(listArgs->context.state, (drawSurf.packed >> 58) & 0x3F);
    R_BeginPixMaterial(listArgs->context.state);
    if ( prepassContext.state )
    {
        R_SetPixPrimarySortKey(prepassContext.state, (drawSurf.packed >> 58) & 0x3F);
        R_BeginPixMaterial(prepassContext.state);
    }
    */
    isPixelCostEnabled = pixelCostMode != 0;
    if ( isPixelCostEnabled )
    {
        R_PixelCost_BeginSurface(listArgs->context);
    }
    assert(!prepassContext.state || (prepassContext.state->technique->passCount == 1));

    passPrepassContext.source = prepassContext.source;
    subListCount = 0;
    passCount = listArgs->context.state->technique->passCount;
    for ( passIndex = 0; passIndex < passCount; ++passIndex )
    {
        //R_UpdateMaterialTime(listArgs->context.source, 0.0, 0.0, 0.0, 0.0);
        R_UpdateMaterialTime(listArgs->context.source, 0.0);
        R_SetupPass(listArgs->context, passIndex);
        if ( passIndex || !prepassContext.state )
        {
            passPrepassContext.state = NULL;
        }
        else
        {
            R_SetupPass(prepassContext, 0);
            passPrepassContext.state = prepassContext.state;
        }
        assert(drawSurf.fields.surfType < ARRAY_COUNT( rb_tessTable ));
        subListCount = rb_tessTable[drawSurf.fields.surfType](listArgs, passPrepassContext);
    }
    if ( isPixelCostEnabled )
    {
        R_PixelCost_EndSurface(listArgs->context);
    }
    /*
    R_EndPixMaterial(listArgs->context.state);
    if ( prepassContext.state )
    {
        R_EndPixMaterial(prepassContext.state);
    }
    ScopedShaderConstantSetUndo::~ScopedShaderConstantSetUndo(&shaderConstantUndo);
    */
    return subListCount;
}

void R_DrawSurfs(GfxCmdBufContext context, GfxCmdBufState *prepassState, const GfxDrawSurfListInfo *info)
{
    GfxViewport viewport;
    GfxCmdBufContext prepassContext;
    GfxDrawSurfListArgs listArgs;
    unsigned int drawMatCount;
    unsigned int processedDrawSurfCount;
    unsigned int drawSurfCount;

    assert(context.source->cameraView == info->cameraView);

    context.state->origMaterial = 0;
    R_SetDrawSurfsShadowableLight(context.source, info);
    R_Set3D(context.source);
    prepassContext.source = prepassState != 0 ? context.source : 0;
    prepassContext.state = prepassState;
    if ( context.source->viewportIsDirty )
    {
        R_GetViewport(context.source, &viewport);
        R_SetViewport(context.state, &viewport);
        if ( prepassState )
        {
            R_SetViewport(prepassContext.state, &viewport);
        }
        R_UpdateViewport(context.source, &viewport);
    }
    assert(r_dx.d3d9 && r_dx.device);

    if ( context.state->prim.device != r_dx.device )
    {
        PIXBeginNamedEvent(-1, "draw surf");
    }
    /*
    R_BeginPixMaterials(context.state);
    if ( prepassContext.state )
    {
        R_BeginPixMaterials(prepassContext.state);
    }*/

    drawSurfCount = info->drawSurfCount;
 
    listArgs.context = context;
    listArgs.firstDrawSurfIndex = 0;
    listArgs.info = info;
    drawMatCount = 0;

    while ( listArgs.firstDrawSurfIndex != drawSurfCount )
    {
        processedDrawSurfCount = R_RenderDrawSurfListMaterial(&listArgs, prepassContext);
        listArgs.firstDrawSurfIndex += processedDrawSurfCount;
        ++drawMatCount;
    }


    /*
    context.state->prim.viewStats->drawSurfCount += drawSurfCount;
    context.state->prim.viewStats->drawMatCount += drawMatCount;
    R_EndPixMaterials(context.state);
    if ( prepassContext.state )
    {
        R_EndPixMaterials(prepassContext.state);
    }
    if ( context.state->prim.device != r_dx.device && GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
    {
        D3DPERF_EndEvent();
    }
    */
    R_TessEnd(context, prepassContext);
    context.state->origMaterial = 0;
}

