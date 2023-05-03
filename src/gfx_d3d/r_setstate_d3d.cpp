#include <intrin.h>
#include "r_local.h"
#include "../common/sys_thread.h"

void R_FinishGpuFence()
{
  HRESULT hr;

  while ( r_dx.flushGpuFenceIssued )
  {
    hr = D3DCALLNOLOCKNOERROR( r_dx.flushGpuFence->GetData(0, 0, 1u));
    if ( hr != 1 )
    {
      r_dx.flushGpuFenceIssued = 0;
    }
  }
}

bool RB_IsGpuFenceFinished()
{
  HRESULT hr;

  if ( !r_dx.flushGpuFenceIssued )
  {
    return true;
  }
  hr = r_dx.flushGpuFence->GetData(0, 0, 1u);
  if ( hr == 1 )
  {
    return false;
  }
  r_dx.flushGpuFenceIssued = 0;
  return true;
}


void R_AcquireGpuFenceLock()
{
  return Sys_EnterCriticalSection(CRITSECT_GPU_FENCE);
}

void R_ReleaseGpuFenceLock()
{
  return Sys_LeaveCriticalSection(CRITSECT_GPU_FENCE);
}



void R_InsertGpuFence()
{
  D3DCALLNOLOCKNOERROR(r_dx.flushGpuFence->Issue( 1 ));
  r_dx.flushGpuFenceIssued = true;
}


void sub_615230()
{
  int old;
  int elapsed;

  if(RB_IsGpuFenceFinished() == true)
  {
    if ( r_dx.gpuSyncDelay > 20000 )
    {
      r_dx.gpuSyncDelay = 127 * ((r_dx.gpuSyncDelay - 20000) / 128);
    }else{
      r_dx.gpuSyncDelay = 0;
    }
    return;
  }

  old = (signed int)__rdtsc();

  while ( !RB_IsGpuFenceFinished() )
  {
    if ( (signed int) __rdtsc() - old < 0 )
    {
      r_dx.flushGpuFenceIssued = 0;
      break;
    }
  }
  elapsed = __rdtsc() - old;
  if ( elapsed >= 0 )
  {
    r_dx.gpuSyncDelay += elapsed / 16;
  }
}



void R_HW_DisableScissor(D3DDevice *device)
{
    D3DCALL(device->SetRenderState( D3DRS_SCISSORTESTENABLE, 0 ));
}


void R_HW_EnableScissor(D3DDevice *device, unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
  RECT scissor;

  scissor.left = x;
  scissor.top = y;
  scissor.right = w + x;
  scissor.bottom = h + y;


  D3DCALL(device->SetRenderState(D3DRS_SCISSORTESTENABLE, 1));
  D3DCALL(device->SetScissorRect( &scissor ));

}
