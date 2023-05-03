#include <stdint.h>
#include <intrin.h>
#include <windows.h>
#include <d3d9.h>
#include "../q_shared.h"
#include "../common/sys_thread.h"
#include "../common/qcommon.h"
#include "win_local.h"

double msecPerRawTimerTick;

void Sys_GetPhysicalCpuCount(SysInfo *sysInfo)
{
    int i;
    HMODULE kernmod = GetModuleHandleA("kernel32");
    if(kernmod == NULL)
    {
      return;
    }
    BOOL __stdcall (*PGetLogicalProcessorInformationEx)(LOGICAL_PROCESSOR_RELATIONSHIP RelationshipType, PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Buffer, PDWORD ReturnedLength);

    PGetLogicalProcessorInformationEx = (BOOL __stdcall (*)(LOGICAL_PROCESSOR_RELATIONSHIP, PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, PDWORD))GetProcAddress(kernmod, "GetLogicalProcessorInformationEx");
    if(PGetLogicalProcessorInformationEx == NULL)
    {
      return;
    }

    SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX info[1024];
    DWORD infosize = sizeof(info);

    const BOOL result_second = PGetLogicalProcessorInformationEx(LOGICAL_PROCESSOR_RELATIONSHIP::RelationProcessorCore, info, &infosize);
    if(result_second == FALSE)
    {
      if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
      {
        return;
      }
      return;
    }

    size_t nb_physical_cores = 0;
    size_t offset = 0;

    for(i = 0; offset < infosize; ++i ) {
        const PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX current_info = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)((char*)info + offset);
        offset += current_info->Size;
        ++nb_physical_cores;
    }
    sysInfo->physicalCpuCount = nb_physical_cores;
}

/*
double SecondsPerTick()
{
  _LARGE_INTEGER qpcFrequency;

  Sleep(0);
  QueryPerformanceFrequency(&qpcFrequency);
  return 1.0 / (double)qpcFrequency.QuadPart;
}
*/

double SecondsPerTick()
{
  uint64_t oldTickCounter;
  int64_t elapsedticks;
  LARGE_INTEGER oldPerformanceCount;
  LARGE_INTEGER newPerformanceCount;
  LARGE_INTEGER qpcFrequency;

  //Win_SetThreadLock(2u);
  Sys_Sleep(0);
  QueryPerformanceFrequency(&qpcFrequency);
  QueryPerformanceCounter(&oldPerformanceCount);
  oldTickCounter = __rdtsc();
  QueryPerformanceCounter(&oldPerformanceCount);
  Sys_Sleep(250u);
  elapsedticks = __rdtsc() - oldTickCounter;;
  QueryPerformanceCounter(&newPerformanceCount);
  return (double)(newPerformanceCount.QuadPart - oldPerformanceCount.QuadPart) / ((double)elapsedticks * (double)qpcFrequency.QuadPart);
  //Win_SetThreadLock(0);
}

void InitTiming()
{
  msecPerRawTimerTick = SecondsPerTick() * 1000.0;
}

double Sys_BenchmarkGHz()
{
  uint64_t usedticks;
  int priority;
  volatile uint64_t minTime;
  unsigned int attempt;
  HANDLE thread;

  thread = GetCurrentThread();
  priority = GetThreadPriority(thread);
  SetThreadPriority(thread, 15);
  minTime = -1;
  for ( attempt = 0; attempt < 1000; ++attempt )
  {
    Sys_Sleep(0);
    usedticks = X86_Benchmark();
    if ( minTime > usedticks )
    {
      minTime = usedticks;
    }
  }
  SetThreadPriority(thread, priority);
  return 0.1010328 / ((double)minTime * msecPerRawTimerTick);
}




void Sys_SetAutoConfigureGHz(SysInfo *sysInfo)
{
  double multiCpuFactor;

  Sys_GetPhysicalCpuCount(sysInfo);
  
  assert(sysInfo->physicalCpuCount >= 1);

  if ( sysInfo->physicalCpuCount == 1 )
  {
    multiCpuFactor = 1.0;
  }
  else if ( sysInfo->physicalCpuCount == 2 )
  {
    multiCpuFactor = 1.75;
  }
  else
  {
    multiCpuFactor = 2.0;
  }
  sysInfo->configureGHz = Sys_BenchmarkGHz() * multiCpuFactor;
}

#define bit_SSE		(1 << 25)

bool Sys_SupportsSSE()
{
  int info[4];
  __cpuidex(info, 1, 0);

  if ( info[3] & bit_SSE)
  {
    return true;
  }
  return false;
}

unsigned int Sys_AddApicIdIfUnique(unsigned int apicId, unsigned int *existingApicId, unsigned int existingCount)
{
  unsigned int existingIter;

  for ( existingIter = 0; existingIter < existingCount; ++existingIter )
  {
    assert ( existingIter < 128);
    if ( existingApicId[existingIter] == apicId )
    {
      return existingCount;
    }
  }
  existingApicId[existingCount] = apicId;
  return existingCount + 1;
}

void Sys_DetectCpuVendorAndName(char *vendor, char *name)
{
  unsigned int i, j;
  int info[4];

  __cpuidex(info, 0, 0);

  ((int*)vendor)[0] = info[1];
  ((int*)vendor)[1] = info[3];
  ((int*)vendor)[2] = info[2];
  ((int*)vendor)[3] = 0;

  // Get processor brand string
  // This seems to be working for both Intel & AMD vendors
  for(i=0x80000002, j = 0; i<0x80000005; ++i, j += 16) {
    __cpuidex(info, i, 0);
	  memcpy(name + j, (char*)info, 16);
  }
  name[48] = 0;
}



void Sys_NormalExit();

int Sys_SystemMemoryMB()
{
  int sysMB;
  HINSTANCE__ *hm;
  _MEMORYSTATUS status;
  BOOL (__stdcall *MemStatEx)(_MEMORYSTATUSEX *);
  _MEMORYSTATUSEX statusEx;

  hm = GetModuleHandleA("kernel32.dll");
  if ( hm && (MemStatEx = (BOOL (__stdcall *)(_MEMORYSTATUSEX *))GetProcAddress(hm, "GlobalMemoryStatusEx")) != 0 )
  {
    statusEx.dwLength = 64;
    MemStatEx(&statusEx);
    if ( statusEx.ullAvailVirtual < 0x8000000 )
    {
      if ( MessageBoxA(GetActiveWindow(), Win_LocalizeRef("WIN_LOW_MEMORY_BODY"), Win_LocalizeRef("WIN_LOW_MEMORY_TITLE"), 0x34u) != 6 )
      {
        Sys_NormalExit();
        exit(0);
      }
    }
    sysMB = (signed int)((double)statusEx.ullTotalPhys * 0.00000095367432 + 0.4999999990686774);
    if ( (double)statusEx.ullTotalPhys > (double)sysMB * 1048576.0 || sysMB > 1024 )
    {
      sysMB = 1024;
    }
    return sysMB;
  }

  status.dwLength = 32;
  GlobalMemoryStatus(&status);
  if ( status.dwAvailVirtual < 0x8000000 )
  {
    if ( MessageBoxA(GetActiveWindow(), Win_LocalizeRef("WIN_LOW_MEMORY_BODY"), Win_LocalizeRef("WIN_LOW_MEMORY_TITLE"), 0x34u) != 6 )
    {
      Sys_NormalExit();
      exit(0);
    }
  }
  sysMB = (signed int)((double)status.dwTotalPhys * 0.00000095367432 + 0.4999999990686774);
  if ( (double)status.dwTotalPhys > (double)sysMB * 1048576.0 || sysMB > 1024 )
  {
    sysMB = 1024;
  }
  return sysMB;
}


void Sys_DetectVideoCard(int descLimit, char *description)
{
  IDirect3D9 *d3d9;
  _D3DADAPTER_IDENTIFIER9 id;

  assert(descLimit == sizeof( id.Description ));

  strcpy(description, "Unknown video card");

  d3d9 = Direct3DCreate9(0x20u);
  if ( d3d9 )
  {
    if(d3d9->GetAdapterIdentifier(0, 0, &id) >= 0)
    {
      strncpy(description, id.Description, descLimit);
    }
    d3d9->Release( );
  }
}

void  Sys_FindInfo()
{
  sys_info.logicalCpuCount = Sys_GetCpuCount();
  sys_info.cpuGHz = 1.0 / (((double)1) * msecPerRawTimerTick * 1000000.0);
  sys_info.sysMB = Sys_SystemMemoryMB( );
  Sys_DetectVideoCard(512, sys_info.gpuDescription);
  sys_info.SSE = Sys_SupportsSSE();
  Sys_DetectCpuVendorAndName(sys_info.cpuVendor, sys_info.cpuName);
  Sys_SetAutoConfigureGHz(&sys_info);
}


int Sys_GetMemorySizeInMB()
{
  return sys_info.sysMB;
}

dvar_s* sys_configureGHz;
dvar_s* sys_sysMB;
dvar_s* sys_gpu;
dvar_s* sys_configSum;
dvar_s* sys_SSE;

void Sys_RegisterInfoDvars()
{
  float value;

  sys_configureGHz = Dvar_RegisterFloat("sys_configureGHz", 0.0, -3.4028235e38, 3.4028235e38, 0x11u, "Normalized total CPU power, based on cpu type, count, and speed; used in autoconfigure");
  sys_sysMB = Dvar_RegisterInt("sys_sysMB", 0, 2147483648, 0x7FFFFFFF, 0x11u, "Physical memory in the system");
  sys_gpu = Dvar_RegisterString("sys_gpu", "", 0x11u, "GPU description");
  sys_configSum = Dvar_RegisterInt("sys_configSum", 0, 2147483648, 0x7FFFFFFF, 0x11u, "Configuration checksum");
  sys_SSE = Dvar_RegisterBool("sys_SSE", sys_info.SSE, 0x40u, "Operating system allows Streaming SIMD Extensions");
  value = sys_info.cpuGHz;
  Dvar_RegisterFloat("sys_cpuGHz", value, -3.4028235e38, 3.4028235e38, 0x40u, "Measured CPU speed");
  Dvar_RegisterString("sys_cpuName", sys_info.cpuName, 0x40u, "CPU name description");
}

void Sys_ArchiveInfo(int checksum)
{
  Sys_RegisterInfoDvars();
  Dvar_SetFloat(sys_configureGHz, sys_info.configureGHz);
  Dvar_SetInt(sys_sysMB, sys_info.sysMB);
  Dvar_SetString(sys_gpu, sys_info.gpuDescription);
  Dvar_SetInt(sys_configSum, checksum);
}

bool Sys_ShouldUpdateForInfoChange()
{
  Sys_ArchiveInfo(0);
  /*
  if ( G_OnlyConnectingPaths() )
  {
    return false;
  }
  */
  return MessageBoxA(GetActiveWindow(), Win_LocalizeRef("WIN_COMPUTER_CHANGE_BODY"), Win_LocalizeRef("WIN_COMPUTER_CHANGE_TITLE"), 0x44u) == 6;
}


void Sys_GetInfo(SysInfo *info)
{
  memcpy(info, &sys_info, sizeof(SysInfo));
}

bool Sys_HasInfoChanged()
{
  Sys_RegisterInfoDvars();
  if ( sys_configureGHz->current.value > sys_info.configureGHz * 1.100000023841858 || sys_info.configureGHz * 0.8999999761581421 > sys_configureGHz->current.value )
  {
    return Sys_ShouldUpdateForInfoChange();
  }
  if ( sys_sysMB->current.integer > sys_info.sysMB + 32 || sys_sysMB->current.integer < sys_info.sysMB - 32 )
  {
    return Sys_ShouldUpdateForInfoChange();
  }
  if ( !strcmp(sys_gpu->current.string, sys_info.gpuDescription) )
  {
    return 0;
  }
  return Sys_ShouldUpdateForInfoChange();
}

bool Sys_ShouldUpdateForConfigChange()
{
  return MessageBoxA(GetActiveWindow(), Win_LocalizeRef("WIN_CONFIGURE_UPDATED_BODY"), Win_LocalizeRef("WIN_CONFIGURE_UPDATED_TITLE"), 0x44u) == 6;
}

bool Sys_HasConfigureChecksumChanged(int checksum)
{
  bool changed;

  Sys_RegisterInfoDvars();
  /*
  if ( G_OnlyConnectingPaths() )
  {
    return 0;
  }*/
  changed = 0;
  if ( sys_configSum->current.integer )
  {
    if ( sys_configSum->current.integer != checksum )
    {
      changed = Sys_ShouldUpdateForConfigChange();
    }
  }
  if ( !sys_configSum->current.integer || sys_configSum->current.integer != checksum )
  {
    Dvar_SetInt(sys_configSum, checksum);
  }
  return changed;
}