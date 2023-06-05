#ifndef __WIN_SHARED_H__
#define __WIN_SHARED_H__

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winnt.h>



struct __align(8) SysInfo
{
  double cpuGHz;
  double configureGHz;
  int logicalCpuCount;
  int physicalCpuCount;
  int sysMB;
  char gpuDescription[512];
  bool SSE;
  char cpuVendor[13];
  char cpuName[49];
};

extern SysInfo sys_info;

void 		    Sys_DestroySplashWindow();
void 		    Sys_DestroyConsole( void ) ;
void	      Sys_ShowConsole( int level, qboolean quitOnClose );
void        Sys_Print( const char *msg );
void        Sys_GetInfo(SysInfo *info);
void        Sys_ArchiveInfo(int checksum);
unsigned int Sys_Milliseconds( void );
bool        Sys_RandomBytes( byte *string, int len );
void        Sys_Init();
void        Win_UpdateThreadLock();
const char* Sys_DefaultInstallPath();







#endif