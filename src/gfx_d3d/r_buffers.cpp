#include "r_local.h"
#include "rb_resource.h"
#include "../common/sys_thread.h"



void R_FinishStaticVertexBuffer(D3DVertexBuffer *vb)
{
    D3DSEMSTART;

    D3DCALL(vb->Unlock());

    D3DSEMEND;
}


void R_FinishStaticIndexBuffer(D3DIndexBuffer *ib)
{
  D3DSEMSTART;

  D3DCALL(ib->Unlock());
  
  D3DSEMEND;
}


void * R_AllocStaticVertexBuffer(D3DVertexBuffer **vb, int sizeInBytes, const char* debugname)
{

  HRESULT hr;
  void *vertexBufferData;

  assert(vb);
  assert(sizeInBytes > 0);

  if ( !r_loadForRenderer->current.enabled )
  {
    return nullptr;
  }

  D3DSEMSTART;
  
  hr = D3DCALLINIT(r_dx.device->CreateVertexBuffer(sizeInBytes, 8, 0, D3DPOOL_DEFAULT, vb, 0));
  if ( hr < 0 )
  {
    R_FatalInitError("DirectX didn't create a %i-byte vertex buffer: %s\n", sizeInBytes, R_ErrorDescription(hr));
  }

  hr = D3DCALLINIT((*vb)->Lock(0, 0, &vertexBufferData, 0));
  if ( hr < 0 )
  {
    R_FatalInitError("DirectX didn't lock a vertex buffer: %s\n", R_ErrorDescription(hr));
  }
  D3DSEMEND;
  return vertexBufferData;
}


void * R_AllocStaticIndexBuffer(IDirect3DIndexBuffer9 **ib, int sizeInBytes, const char* debugname)
{
  HRESULT hr;
  void *indexBufferData;

  assert(ib);
  assert(sizeInBytes > 0);

  if ( !r_loadForRenderer->current.enabled )
  {
    return nullptr;
  }

  D3DSEMSTART;
  hr = D3DCALLINIT(r_dx.device->CreateIndexBuffer(sizeInBytes, 8, D3DFMT_INDEX16, D3DPOOL_DEFAULT, ib, 0));
  D3DSEMEND;

  if ( hr < 0 )
  {
    return NULL;
  }
  if ( D3DCALLINIT((*ib)->Lock(0, 0, &indexBufferData, 0)) >= 0 )
  {
    return indexBufferData;
  }
  D3DCALLINIT((*ib)->Release( ));
  return NULL;
}


void Load_VertexBuffer(D3DVertexBuffer **vb, void *bufferData, int sizeInBytes)
{
    void *allocvb;
    
    if ( !r_loadForRenderer->current.enabled || !bufferData )
    {
        *vb = 0;
        return;
    }  

    if ( Sys_IsRenderThread() )
    {
        allocvb = R_AllocStaticVertexBuffer(vb, sizeInBytes, "Load_VertexBuffer");
        memcpy(allocvb, bufferData, sizeInBytes);
        R_FinishStaticVertexBuffer(*vb);
    }
    else
    {
        RB_Resource_LoadVertexBuffer(vb, bufferData, sizeInBytes);
        RB_Resource_Flush();
    }

}

void * R_LockIndexBuffer(D3DIndexBuffer *handle, int offset, int bytes, int lockFlags)
{
  HRESULT hr;
  void *bufferData;

  assert(handle);

  D3DSEMSTART;

  hr = D3DCALLNAKED(handle->Lock(offset, bytes, &bufferData, lockFlags));
  if ( hr < 0 )
  {
    R_FatalLockError(hr);
  }

  D3DSEMEND;

  return bufferData;
}

void * R_LockVertexBuffer(D3DVertexBuffer *handle, int offset, int bytes, int lockFlags)
{
  HRESULT hr;
  void *bufferData;
  
  assert(handle);

  D3DSEMSTART;
  
  hr = D3DCALLNAKED(handle->Lock(offset, bytes, &bufferData, lockFlags));
  if ( hr < 0 )
  {
    R_FatalLockError(hr);
  }

  D3DSEMEND;

  return bufferData;
}


void R_UnlockVertexBuffer(D3DVertexBuffer *handle)
{
  D3DCALLNOERROR(handle->Unlock());
}


void R_UnlockIndexBuffer(D3DIndexBuffer *handle)
{
  D3DCALLNOERROR(handle->Unlock());
}


void R_FreeStaticIndexBuffer(D3DIndexBuffer *ib)
{
  D3DRELEASEBUFFER(ib);
}


void R_FreeStaticVertexBuffer(D3DVertexBuffer *vb)
{
  D3DRELEASEBUFFER(vb);
}


void * R_AllocDynamicVertexBuffer(D3DVertexBuffer **vb, int sizeInBytes, const char* debugname)
{
  HRESULT hr;

  assert(vb);
  assert(sizeInBytes > 0);

  if ( !r_loadForRenderer->current.enabled )
  {
    return NULL;
  }

  D3DSEMSTART;
  hr = D3DCALLINIT(r_dx.device->CreateVertexBuffer(sizeInBytes, R_GetOptimizeVBTransfersValue() == 0 ? 0x208 : 0x400208, 0, D3DPOOL_DEFAULT, vb, 0));
  if ( hr < 0 )
  {
    R_FatalInitError("DirectX didn't create a %i-byte dynamic vertex buffer: %s\n", sizeInBytes, R_ErrorDescription(hr));
  }
  D3DSEMEND;

  return NULL;
}


void R_InitDynamicVertexBufferState(GfxVertexBufferState *vb, int bytes)
{
  char *verts;

  assert(vb);

  vb->used = 0;
  vb->total = bytes;
  verts = (char *)R_AllocDynamicVertexBuffer(&vb->buffer, bytes, __PRETTY_FUNCTION__);
  
  assert(verts == NULL);
  
  vb->verts = verts;
}

void * R_AllocDynamicIndexBuffer(IDirect3DIndexBuffer9 **ib, int sizeInBytes)
{
  HRESULT hr;

  if ( !r_loadForRenderer->current.enabled )
  {
    return NULL;
  }

  D3DSEMSTART;
  
  hr = D3DCALLINIT(r_dx.device->CreateIndexBuffer(sizeInBytes, 520, D3DFMT_INDEX16, D3DPOOL_DEFAULT, ib, 0));
  if ( hr < 0 )
  {
    R_FatalInitError("Couldn't create a %i-byte dynamic index buffer: %s", sizeInBytes, R_ErrorDescription(hr));
  }

  D3DSEMEND;
  return NULL;
}


void R_InitDynamicIndexBufferState(GfxIndexBufferState *ib, int indexCount, bool writeOnly, unsigned int location)
{
  assert(ib);

  ib->used = 0;
  ib->total = indexCount;
  void* indices = R_AllocDynamicIndexBuffer(&ib->buffer, 2 * indexCount);
  assert(indices == NULL);
}


void R_DestroyParticleCloudBuffer()
{
  if ( gfxBuf.particleCloudVertexBuffer )
  {
    R_FreeStaticVertexBuffer(gfxBuf.particleCloudVertexBuffer);
    gfxBuf.particleCloudVertexBuffer = 0;
  }
  if ( gfxBuf.particleCloudIndexBuffer )
  {
    R_FreeStaticIndexBuffer(gfxBuf.particleCloudIndexBuffer);
    gfxBuf.particleCloudIndexBuffer = 0;
  }
}


void R_CreateDynamicBuffers()
{
  int bufferIter;

  for ( bufferIter = 0; bufferIter != ARRAY_COUNT(gfxBuf.dynamicVertexBufferPool); ++bufferIter )
  {
    R_InitDynamicVertexBufferState(&gfxBuf.dynamicVertexBufferPool[bufferIter], 0x100000);
  }
  gfxBuf.dynamicVertexBuffer = gfxBuf.dynamicVertexBufferPool;

  for ( bufferIter = 0; bufferIter != ARRAY_COUNT(gfxBuf.skinnedCacheVbPool); ++bufferIter )
  {
    R_InitDynamicVertexBufferState(&gfxBuf.skinnedCacheVbPool[bufferIter], 0x480000);
    //gfxBuf.skinnedCacheVbPool[bufferIter].verts = (char *)Z_VirtualAlloc(gfxBuf.skinnedCacheVbPool[bufferIter].total, "skinnedCacheVbPool", 19);
    gfxBuf.skinnedCacheVbPool[bufferIter].verts = NULL;
  }

  R_InitTempSkinBuf();

//  R_InitWaterSimulationVertexBuffers(1u);
  
  for ( bufferIter = 0; bufferIter != ARRAY_COUNT(gfxBuf.dynamicIndexBufferPool); ++bufferIter )
  {
    R_InitDynamicIndexBufferState(&gfxBuf.dynamicIndexBufferPool[bufferIter], 0x100000, 0, 1u);
  }
  gfxBuf.dynamicIndexBuffer = gfxBuf.dynamicIndexBufferPool;

  for ( bufferIter = 0; bufferIter != ARRAY_COUNT(gfxBuf.preTessIndexBufferPool); ++bufferIter )
  {
    R_InitDynamicIndexBufferState(&gfxBuf.preTessIndexBufferPool[bufferIter], 0x100000, 0, 1u);
    //gfxBuf.preTessIndexBufferPool[bufferIter].indices = (uint16_t *)Z_VirtualAlloc(0x200000, "preTessIndexBuffer", 19);
    gfxBuf.preTessIndexBufferPool[bufferIter].indices = NULL;
  }
  gfxBuf.preTessIndexBuffer = gfxBuf.preTessIndexBufferPool;
  gfxBuf.preTessBufferFrame = 0;
}


void R_DestroyDynamicBuffers()
{
  int bufferIter;

  for ( bufferIter = 0; bufferIter != ARRAY_COUNT(gfxBuf.preTessIndexBufferPool); ++bufferIter )
  {
    if ( gfxBuf.preTessIndexBufferPool[bufferIter].buffer )
    {
      D3DRELEASEBUFFER(gfxBuf.preTessIndexBufferPool[bufferIter].buffer);
    }
//    Z_VirtualFree(gfxBuf.preTessIndexBufferPool[bufferIter].indices, 19);
    //gfxBuf.preTessIndexBufferPool[bufferIter].indices = 0;
  }

  for ( bufferIter = 0; bufferIter != ARRAY_COUNT(gfxBuf.dynamicIndexBufferPool); ++bufferIter )
  {
    if ( gfxBuf.dynamicIndexBufferPool[bufferIter].buffer )
    {
      D3DRELEASEBUFFER(gfxBuf.dynamicIndexBufferPool[bufferIter].buffer);
    }
  }

//  R_FreeWaterSimulationVertexBuffers();
  
  for ( bufferIter = 0; bufferIter != ARRAY_COUNT(gfxBuf.skinnedCacheVbPool); ++bufferIter )
  {
    if ( gfxBuf.skinnedCacheVbPool[bufferIter].buffer )
    {
      D3DRELEASEBUFFER(gfxBuf.skinnedCacheVbPool[bufferIter].buffer);
    }
    //Z_VirtualFree(gfxBuf.skinnedCacheVbPool[bufferIter].verts, 19);
    //gfxBuf.skinnedCacheVbPool[bufferIter].verts = 0;
  }
  for ( bufferIter = 0; bufferIter != ARRAY_COUNT(gfxBuf.dynamicVertexBufferPool); ++bufferIter )
  {
    if ( gfxBuf.dynamicVertexBufferPool[bufferIter].buffer )
    {
      D3DRELEASEBUFFER(gfxBuf.dynamicVertexBufferPool[bufferIter].buffer);
    }
  }
  R_ShutdownTempSkinBuf();
}


#pragma msg "g_OptimizeVBTransfers: R_InitRenderBuffers, R_InitStaticModelCache"