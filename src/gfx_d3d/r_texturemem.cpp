#include "r_local.h"

#include <initguid.h>
#include <ddraw.h>

unsigned int R_VideoMemoryForDevice(_GUID *lpGUID)
{
  DDSCAPS2 caps;
  HRESULT hr;
  IDirectDraw7 *dd;
  long unsigned int total;
  long unsigned int free;

  hr = DirectDrawCreateEx(lpGUID, (void **)&dd, IID_IDirectDraw7, 0);

  if ( hr < 0 )
  {
    return 0;
  }
  caps.dwCaps2 = 0;
  caps.dwCaps3 = 0;
  caps.dwCaps4 = 0;
  caps.dwCaps = 0x10000000;
  hr = dd->GetAvailableVidMem (&caps, &total, &free);
  dd->Release( );
  if ( hr >= 0 )
  {
    return total;
  }
  return 0;
}

unsigned int R_DrasticVideoMemoryForDevice(_GUID *lpGUID, const char *lpDriverDescription)
{
  DDSCAPS2 caps;
  HRESULT hr;
  IDirectDraw7 *dd;
  long unsigned int total;
  HWND hwndDummy;
  long unsigned int free;

  hr = DirectDrawCreateEx(lpGUID, (void **)&dd, IID_IDirectDraw7, 0);
  if ( hr < 0 )
  {
    return 0;
  }
  hwndDummy = CreateWindowExA(0, "static", "dummy", 0, 0, 0, 1, 1, 0, 0, GetModuleHandleA(0), 0);
  if ( hwndDummy )
  {
    hr = dd->SetCooperativeLevel(hwndDummy, DDSCL_FULLSCREEN | DDSCL_FULLSCREEN);
    if ( hr >= 0 )
    {
      caps.dwCaps2 = 0;
      caps.dwCaps3 = 0;
      caps.dwCaps4 = 0;
      caps.dwCaps = 0x4000;
      hr = dd->GetAvailableVidMem (&caps, &total, &free);
      DestroyWindow(hwndDummy);
      dd->Release();
      if ( hr >= 0 )
      {
        return total;
      }
      return 0;
    }
    DestroyWindow(hwndDummy);
    dd->Release();
    return 0;
  }
  dd->Release();
  return 0;
}



int __stdcall R_DDEnumCallback(_GUID *lpGUID, char *lpDriverDescription, char *lpDriverName, void *lpContext, HMONITOR hm)
{
  unsigned int total;

  if ( hm )
  {
    return 1;
  }
  total = R_VideoMemoryForDevice(lpGUID);
  if ( *(DWORD *)lpContext < total )
  {
    *(DWORD *)lpContext = total;
  }
  return 1;
}

int __stdcall R_DDEnumDrasticCallback(_GUID *lpGUID, char *lpDriverDescription, char *lpDriverName, void *lpContext, HMONITOR hm)
{
  unsigned int total;

  total = R_DrasticVideoMemoryForDevice(lpGUID, lpDriverDescription);
  if ( *(DWORD *)lpContext < total )
  {
    *(DWORD *)lpContext = total;
  }
  return 1;
}


unsigned int R_VideoMemory()
{
  unsigned int total;
  unsigned int size;

  total = R_VideoMemoryForDevice(0);
  if ( total )
  {
    Com_Printf(CON_CHANNEL_GFX, "Video memory for device: %i MB.\n", total / (1024 * 1024));
  }
  else
  {
    DirectDrawEnumerateEx(R_DDEnumCallback, &total, 0);
    if ( total )
    {
      Com_Printf(CON_CHANNEL_GFX, "Enumerated video memory for device: %i MB.\n", total / (1024 * 1024));
    }
    else
    {
      total = R_DrasticVideoMemoryForDevice(0, "NULL device");
      if ( total )
      {
        Com_Printf(CON_CHANNEL_GFX, "Drastic video memory for device: %i MB.\n", total / (1024 * 1024));
      }
      else
      {
        DirectDrawEnumerateEx(R_DDEnumDrasticCallback, &total, 0);
        if ( !total )
        {
          Com_Printf(CON_CHANNEL_GFX, "Failed to get video memory size.\n");
          return 0;
        }
        Com_Printf(CON_CHANNEL_GFX, "Enumerated drastic video memory for device: %i MB.\n", total / (1024 * 1024));
      }
    }
  }
  total = ((total - 1) / (1024 * 1024)) + 1;
  for ( size = 1; size < total; size *= 2 );
  if ( size - total > 0x20 )
  {
    size >>= 1;
  }
  Com_Printf(CON_CHANNEL_GFX, "Rounded video memory size: %i MB.\n", size);
  return size;
}



int R_AvailableTextureMemory()
{
  unsigned int texMemInMegs;
  unsigned int vidMemInMegs;

  assert(r_dx.device);

  vidMemInMegs = R_VideoMemory();
  texMemInMegs = r_dx.device->GetAvailableTextureMem() / (1024 * 1024);
  if ( vidMemInMegs )
  {
    Com_Printf(CON_CHANNEL_GFX, "DirectX reports %i MB of video memory and %i MB of available texture memory.\n", vidMemInMegs, texMemInMegs);
    if ( vidMemInMegs >= texMemInMegs )
    {
      return texMemInMegs;
    }
    Com_Printf(CON_CHANNEL_GFX, "Using video memory size to cap used texture memory at %i MB.\n", vidMemInMegs - 16);
    return vidMemInMegs - 16;

  }
  Com_Printf(CON_CHANNEL_GFX, "DirectX reports %i MB of available texture memory, but wouldn't tell available video memory.\n", texMemInMegs);
  return texMemInMegs;
}