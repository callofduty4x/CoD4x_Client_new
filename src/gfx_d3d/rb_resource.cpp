#include "r_local.h"
#include "r_image.h"
#include "../common/sys_thread.h"


#define R_MAX_RESOURCE_ACTIONS 0x4000


FastCriticalSection resourceLock;
r_resource_action resourceActions[4096];
volatile int numResourceActions;

void RB_Resource_Lock()
{
  Sys_LockWrite(&resourceLock);
}

void RB_Resource_Unlock()
{
  Sys_UnlockWrite(&resourceLock);
}

r_resource_action* RB_Resource_AllocEntry()
{
    Com_Error(ERR_FATAL, "Resource actions are not supported at this time");
    assert(numResourceActions < R_MAX_RESOURCE_ACTIONS);

    Sys_SetResourcesQueuedEvent();
    
    return &resourceActions[numResourceActions++];
}

void RB_Resource_Release(IUnknown *resource)
{
  r_resource_action *action;
  int semaphore;

  semaphore = R_ReleaseDXDeviceOwnership();
  RB_Resource_Lock();
  action = RB_Resource_AllocEntry();

  assert(action);

  action->action = 2;
  action->resource = resource;
  RB_Resource_Unlock();
  if ( semaphore )
  {
    R_AcquireDXDeviceOwnership(0);
  }
}

void RB_Resource_Flush()
{
  int semaphore;

  assert(!Sys_IsRenderThread());

  semaphore = R_ReleaseDXDeviceOwnership();
  
  RB_Resource_Lock();
  if ( numResourceActions )
  {
    Sys_ClearResourcesFlushedEvent();
    RB_Resource_Unlock();
    Sys_WaitResourcesFlushedEvent();
  }
  else
  {
    RB_Resource_Unlock();
  }

  if ( semaphore )
  {
    R_AcquireDXDeviceOwnership(0);
  }
}

void RB_Resource_CreateVertexDeclaration(D3DVERTEXELEMENT9 *elements, D3DVertexDeclaration **declaration)
{
  r_resource_action *action;
  int semaphore;

  semaphore = R_ReleaseDXDeviceOwnership();
  RB_Resource_Lock();
  action = RB_Resource_AllocEntry();

  assert(action);

  action->action = 7;
  action->resource = declaration;
  action->data = elements;
  RB_Resource_Unlock();
  if ( semaphore )
  {
    R_AcquireDXDeviceOwnership(0);
  }
}

//Unusued from here atm.

void RB_Resource_CreateTexture(GfxImage *image, void *imageBuffer, int mipCount, int flags, D3DFORMAT imageFormat)
{
  r_resource_action *action;
  int semaphore;

  semaphore = R_ReleaseDXDeviceOwnership();
  RB_Resource_Lock();
  action = RB_Resource_AllocEntry();
  assert(action);

  action->action = 1;
  action->resource = image;
  action->data = imageBuffer;
  action->p1 = mipCount;
  action->p2 = imageFormat;
  action->p3 = flags;
  RB_Resource_Unlock();
  if ( semaphore )
  {
    R_AcquireDXDeviceOwnership(0);
  }
}

void RB_Resource_ReloadTexture(GfxImage *image, void *data)
{
  r_resource_action *action;
  int semaphore;

  semaphore = R_ReleaseDXDeviceOwnership();
  RB_Resource_Lock();
  action = RB_Resource_AllocEntry();

  assert(action);

  action->action = 4;
  action->resource = image;
  action->data = data;
  RB_Resource_Unlock();
  if ( semaphore )
  {
    R_AcquireDXDeviceOwnership(0);
  }
}


void RB_Resource_Callback(void (__cdecl *callback)())
{
  r_resource_action *action;
  int semaphore;

  semaphore = R_ReleaseDXDeviceOwnership();
  RB_Resource_Lock();
  action = RB_Resource_AllocEntry();
  assert(action);

  action->action = 5;
  action->resource = (void*)callback;
  RB_Resource_Unlock();
  if ( semaphore )
  {
    R_AcquireDXDeviceOwnership(0);
  }
}

void RB_Resource_CallbackParam(void (__cdecl *callback)(void *), void *data)
{
  r_resource_action *action;
  int semaphore;

  semaphore = R_ReleaseDXDeviceOwnership();
  RB_Resource_Lock();
  action = RB_Resource_AllocEntry();\

  assert(action);

  action->action = 6;
  action->resource = (void*)callback;
  action->data = data;
  RB_Resource_Unlock();
  if ( semaphore )
  {
    R_AcquireDXDeviceOwnership(0);
  }
}

void RB_Resource_CreateVertexShader(unsigned int *function, D3DVertexShader **shader)
{
  r_resource_action *action;
  int semaphore;

  semaphore = R_ReleaseDXDeviceOwnership();
  RB_Resource_Lock();
  action = RB_Resource_AllocEntry();

  assert(action);

  action->action = 8;
  action->resource = shader;
  action->data = function;
  RB_Resource_Unlock();
  if ( semaphore )
  {
    R_AcquireDXDeviceOwnership(0);
  }
}

void RB_Resource_CreatePixelShader(unsigned int *function, D3DPixelShader **shader)
{
  r_resource_action *action;
  int semaphore;

  semaphore = R_ReleaseDXDeviceOwnership();
  RB_Resource_Lock();
  action = RB_Resource_AllocEntry();

  assert(action);

  action->action = 9;
  action->resource = shader;
  action->data = function;
  RB_Resource_Unlock();
  if ( semaphore )
  {
    R_AcquireDXDeviceOwnership(0);
  }
}

void RB_Resource_LoadVertexBuffer(D3DVertexBuffer **vb, void *bufferData, int sizeInBytes)
{
  r_resource_action *action;
  int semaphore;

  semaphore = R_ReleaseDXDeviceOwnership();
  RB_Resource_Lock();
  action = RB_Resource_AllocEntry();

  assert(action);

  action->action = 10;
  action->resource = vb;
  action->data = bufferData;
  action->p1 = sizeInBytes;
  RB_Resource_Unlock();
  if ( semaphore )
  {
    R_AcquireDXDeviceOwnership(0);
  }
}

void RB_Resource_Update_Internal()
{
  signed int mipWidth;
  signed int mipHeight;
  signed int mipDepth;
  D3DCUBEMAP_FACES face;
  void *indexBuffer;
  int rawIndexBytes;
  signed int indexBytes;
  D3DIndexBuffer **ib;
  void *src;
  GfxImage *v10; // [esp+6Ch] [ebp-54h]
  GfxImageFileHeader *v11; // [esp+74h] [ebp-4Ch]
  GfxImage *image;
  int mipCount;
  unsigned char *data;
  int faceCount;
  int faceIndex;
  D3DFORMAT imageFormat;
  int mipLevel;
  int flags;
  r_resource_action *action;
  int resourceIndex;

  PIXBeginNamedEvent(0, "RB_Resource_Update");
  RB_Resource_Lock();
  for ( resourceIndex = 0; resourceIndex < numResourceActions; ++resourceIndex )
  {
    action = &resourceActions[resourceIndex];

    switch ( action->action )
    {
/*
      case 1:
        image = (GfxImage *)action->resource;
        data = (unsigned char *)action->data;
        mipCount = action->p1;
        imageFormat = (D3DFORMAT)action->p2;
        flags = action->p3;
        if ( image->mapType == MAPTYPE_2D )
        {
          Image_Create2DTexture_PC(image, image->width, image->height, mipCount, flags, imageFormat);
          faceCount = 1;
        }
        else if ( image->mapType == MAPTYPE_3D )
        {
          Image_Create3DTexture_PC(image, image->width, image->height, image->depth, mipCount, flags, imageFormat);
          faceCount = 1;
        }
        else
        {
            assert(image->mapType == MAPTYPE_CUBE);

          Image_CreateCubeTexture_PC(image, image->width, mipCount, imageFormat);
          faceCount = 6;
        }
        if ( data )
        {
            for ( faceIndex = 0; faceIndex < faceCount; ++faceIndex )
            {
                if ( faceCount != 1 )
                {
                    face = Image_CubemapFace(faceIndex);
                }else{
                    face = D3DCUBEMAP_FACE_POSITIVE_X;
                }
                for ( mipLevel = 0; mipLevel < mipCount; ++mipLevel )
                {
                    Image_UploadData(image, imageFormat, face, mipLevel, data);
                    if ( (signed int)(image->width >> mipLevel) > 1 )
                    {
                        mipWidth = (unsigned int)image->width >> mipLevel;
                    }
                    else
                    {
                        mipWidth = 1;
                    }
                    if ( (signed int)(image->height >> mipLevel) > 1 )
                    {
                        mipHeight = (unsigned int)image->height >> mipLevel;
                    }
                    else
                    {
                        mipHeight = 1;
                    }
                    if ( (signed int)(image->depth >> mipLevel) > 1 )
                    {
                        mipDepth = (unsigned int)image->depth >> mipLevel;
                    }
                    else
                    {
                        mipDepth = 1;
                    }
                    data += Image_GetCardMemoryAmountForMipLevel(imageFormat, mipWidth, mipHeight, mipDepth);
                }
            }
            D3DCALLNOLOCKNOERRORNORETVAL(image->texture.cubemap->PreLoad( ));
            Z_VirtualFree(action->data, 20);
        }
        continue;
*/
      case 2:
        ((IUnknown*)(action->resource))->Release( );
        continue;
/*
      case 3:
        Image_LoadFromData((GfxImage *)action->resource, (GfxImageFileHeader *)action->data, (unsigned char *)action->data + 48, 2u);
        Z_VirtualFree(action->data, 20);
        continue;

      case 4:
        v10 = (GfxImage *)action->resource;
        v11 = (GfxImageFileHeader *)action->data;
        Image_Release((GfxImage *)action->resource);

        assert(!image->texture.basemap);

        Image_LoadFromData((GfxImage *)action->resource, v11, v11[1].tag, 2u);
        Z_VirtualFree(action->data, 20);
        continue;
      case 5:
        ((void (*)(void))action->resource)();
        continue;
      case 6:
        ((void (__cdecl *)(void *))action->resource)(action->data);
        continue;
      case 7:
        ((void (__stdcall *)(IDirect3DDevice9 *, void *, void *))r_dx.device->vfptr[5].AddRef)(r_dx.device, action->data, action->resource);
        continue;
      case 8:
        ((void (__stdcall *)(IDirect3DDevice9 *, void *, void *))r_dx.device->vfptr[5].FreePrivateData)(r_dx.device, action->data, action->resource);
        continue;
      case 9:
        ((void (__stdcall *)(IDirect3DDevice9 *, void *, void *))r_dx.device->vfptr[6].SetPrivateData)(r_dx.device, action->data, action->resource);
        continue;
      case 0xA:
        Load_VertexBuffer((IDirect3DVertexBuffer9 **)action->resource, action->data, action->p1);
        continue;
      case 0xB:
        ib = (IDirect3DIndexBuffer9 **)action->resource;
        src = action->data;
        rawIndexBytes = action->p1;
        indexBytes = (rawIndexBytes + 31) & 0xFFFFFFE0;
        if ( indexBytes > 0x200000 && !(unsigned __int8)Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\rb_resource.cpp", 422, 0, "%s", "indexBytes <= MATERIAL_MAX_INDEX_BUFFER_SIZE") )
        {
          __debugbreak();
        }
        indexBuffer = R_AllocStaticIndexBuffer(ib, indexBytes);
        if ( !indexBuffer )
        {
          return;
        }
        Com_Memcpy(indexBuffer, src, rawIndexBytes);
        memset((char *)indexBuffer + rawIndexBytes, 0, indexBytes - rawIndexBytes);
        R_FinishStaticIndexBuffer(*ib);
        break;
*/
      default:
        Com_Error(ERR_FATAL, "Unsupported resource action %d\n",  action->action);
        continue;
    }
  }
  Sys_ClearResourcesQueuedEvent();
  Sys_SetResourcesFlushedEvent();
  numResourceActions = 0;
  RB_Resource_Unlock();
/*
  if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
  {
    D3DPERF_EndEvent();
  }
*/
}

/*
void RB_Resource_Update(int msec)
{
  LARGE_INTEGER v1; // [esp+20h] [ebp-20h]
  LARGE_INTEGER PerformanceCount; // [esp+28h] [ebp-18h]
  unsigned __int64 endtime; // [esp+30h] [ebp-10h]
  unsigned __int64 curtime; // [esp+38h] [ebp-8h]

  if ( Sys_IsDatabaseReady() )
  {
    RB_Resource_Update_Internal();
  }
  else
  {
    QueryPerformanceCounter(&PerformanceCount);
    curtime = PerformanceCount.QuadPart;
    endtime = PerformanceCount.QuadPart + (unsigned __int64)((double)msec / msecPerRawTimerTick);
    do
    {
      Sys_WaitResourcesQueuedEvent((signed __int64)((double)(endtime - curtime) * msecPerRawTimerTick));
      RB_Resource_Update_Internal();
      QueryPerformanceCounter(&v1);
      curtime = v1.QuadPart;
    }
    while ( v1.QuadPart < endtime );
  }
}*/