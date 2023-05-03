#include <windows.h>
#include "../q_shared.h"
#include "win_local.h"
#include "../common/sys_thread.h"


threadid_t mainthread;
DWORD tlsKey;
int s_cpuCount;

#ifdef __WIN32
extern HANDLE threadHandle[NUMTHREADS];
#else
extern threadid_t threadHandle[NUMTHREADS];
#endif

threadid_t Sys_GetCurrentThreadId( void )
{
		return GetCurrentThreadId();
}


void Sys_Sleep(int msec)
{
  Sleep(msec);
}


void Sys_InitThreadContext()
{
	tlsKey = TlsAlloc();
  mainthread = Sys_GetCurrentThreadId( );
}

void Sys_SetThreadLocalStorage(void** localvar)
{
    if(TlsSetValue(tlsKey, localvar) == FALSE)
	{
		Sys_ShowEarlyErrorDialog("Sys_SetThreadLocalStorage");
		ExitProcess(-1);
	}
}

void** Sys_GetThreadLocalStorage()
{
    return (void**)TlsGetValue(tlsKey);
}

RTL_CRITICAL_SECTION s_criticalSection[CRITSECT_COUNT];

void Sys_EnterCriticalSectionInternal(CriticalSection section)
{
	EnterCriticalSection(&s_criticalSection[section]);
}

void Sys_LeaveCriticalSectionInternal(CriticalSection section)
{
	LeaveCriticalSection(&s_criticalSection[section]);
}


void Sys_InitializeCriticalSections( void )
{
	int i;

	for (i = 0; i < CRITSECT_COUNT; i++) {
		InitializeCriticalSection( &s_criticalSection[i] );

	}

}


unsigned int s_affinityMaskForProcess;
unsigned int s_affinityMaskForCpu[8];


unsigned int Sys_GetProcessAffinityMask()
{
  long unsigned int systemAffinityMask;
  long unsigned int processAffinityMask = 0;

  HANDLE h = GetCurrentProcess();

  GetProcessAffinityMask(h, &processAffinityMask, &systemAffinityMask);
  return processAffinityMask;
}


void Sys_InitThreadAffinity()
{
  unsigned int cpuCount;
  unsigned int threadAffinityMask;
  unsigned int affinityMaskBits[32];
  unsigned int processAffinityMask;

  processAffinityMask = Sys_GetProcessAffinityMask();

  s_affinityMaskForProcess = processAffinityMask;
  cpuCount = 0;
  for ( threadAffinityMask = 1; processAffinityMask & -threadAffinityMask; threadAffinityMask *= 2 )
  {
    if ( processAffinityMask & threadAffinityMask )
    {
      affinityMaskBits[cpuCount++] = threadAffinityMask;
      if ( cpuCount == 32 )
      {
        break;
      }
    }
  }
  if ( cpuCount && cpuCount != 1 )
  {
    s_cpuCount = cpuCount;
    s_affinityMaskForCpu[0] = affinityMaskBits[0];
    s_affinityMaskForCpu[1] = affinityMaskBits[cpuCount -1];
    if ( cpuCount != 2 )
    {
      if ( cpuCount == 3 )
      {
        s_affinityMaskForCpu[2] = affinityMaskBits[1];
      }
      else if ( cpuCount == 4 )
      {
        s_affinityMaskForCpu[2] = affinityMaskBits[1];
        s_affinityMaskForCpu[3] = affinityMaskBits[2];
      }
      else
      {
        s_affinityMaskForCpu[0] = -1;
        s_affinityMaskForCpu[1] = -1;
        s_affinityMaskForCpu[2] = -1;
        s_affinityMaskForCpu[3] = -1;
        s_affinityMaskForCpu[4] = -1;
        s_affinityMaskForCpu[5] = -1;
        s_affinityMaskForCpu[6] = -1;
        s_affinityMaskForCpu[7] = -1;
        if ( s_cpuCount >= 8 )
        {
          s_cpuCount = 8;
        }
      }
    }
  }
  else
  {
    s_cpuCount = 1;
    s_affinityMaskForCpu[0] = -1;
  }
}

cvar_t* sys_lockThreads;
static LONG volatile s_winThreadLock;

void Win_LockThreadAffinity()
{
  if ( s_cpuCount != 1 && InterlockedIncrement(&s_winThreadLock) == 1 )
  {
    assert(s_cpuCount >= 2);

    if ( threadHandle[0] )
    {
      SetThreadAffinityMask(threadHandle[0], s_affinityMaskForCpu[0]);
    }
    if ( threadHandle[1] )
    {
      SetThreadAffinityMask(threadHandle[1], s_affinityMaskForCpu[1]);
    }
#if 0    
    if ( s_cpuCount < 3 )
    {
      if ( threadHandle[13] )
      {
        SetThreadAffinityMask(threadHandle[13], s_affinityMaskForCpu[1]);
      }
    }
    else if ( threadHandle[13] )
    {
      SetThreadAffinityMask(threadHandle[13], s_affinityMaskForCpu[2]);
    }
    if ( s_cpuCount >= 3 )
    {
      if ( threadHandle[2] )
      {
        SetThreadAffinityMask(threadHandle[2], s_affinityMaskForCpu[2]);
      }
    }
    if ( s_cpuCount >= 4 )
    {
      if ( threadHandle[3] )
      {
        SetThreadAffinityMask(threadHandle[3], s_affinityMaskForCpu[3]);
      }
    }
#endif
  }
}


void Win_UnlockThreadAffinity()
{
  if ( s_cpuCount != 1 && !InterlockedDecrement(&s_winThreadLock) )
  {
    assert(s_cpuCount >= 2);

    if ( threadHandle[0] )
    {
      SetThreadAffinityMask(threadHandle[0], s_affinityMaskForProcess);
    }
    if ( threadHandle[1] )
    {
      SetThreadAffinityMask(threadHandle[1], s_affinityMaskForProcess);
    }
#if 0
    if ( threadHandle[13] )
    {
      SetThreadAffinityMask(threadHandle[13], s_affinityMaskForProcess);
    }
    if ( threadHandle[2] )
    {
      SetThreadAffinityMask(threadHandle[2], s_affinityMaskForProcess);
    }
    if ( threadHandle[3] )
    {
      SetThreadAffinityMask(threadHandle[3], s_affinityMaskForProcess);
    }
#endif
  }
}


void Win_UpdateThreadLock()
{
  if ( sys_lockThreads->modified )
  {
    Dvar_ClearModified(sys_lockThreads);
    if ( sys_lockThreads->current.enabled )
    {
      Win_LockThreadAffinity();
    }
    else
    {
      Win_UnlockThreadAffinity();
    }
  }
}

void* Sys_CreateEvent(bool bManualReset, bool bInitialState, const char *name)
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = false;
	
	return CreateEventA(&sa, bManualReset, bInitialState, NULL); //Name must be NULL or it will interact with other processes
}


bool Sys_WaitForSingleObjectTimeout(void **event, unsigned int msec)
{
  assert(msec != INFINITE);

  return WaitForSingleObject(*event, msec) == 0;
}

void Sys_WaitForSingleObject(void **event)
{
  unsigned int result;

  result = WaitForSingleObject(*event, INFINITE);
  
  assert((result == ((((DWORD )0x00000000L) ) + 0 )));

}

void Sys_SetEvent(void **event)
{
  SetEvent(*event);
}

void Sys_ResetEvent(void **event)
{
  ResetEvent(*event);
}


void Sys_LockWrite(FastCriticalSection *critSect)
{
  while ( 1 )
  {
    if ( !critSect->readCount )
    {
      if ( InterlockedIncrement((volatile long int*)&critSect->writeCount) == 1 && !critSect->readCount )
      {
        break;
      }
      InterlockedExchangeAdd((volatile long int*)&critSect->writeCount, -1u);
    }
    Sys_Sleep(0);
  }
}

void Sys_UnlockWrite(FastCriticalSection *critSect)
{
  assert(critSect->writeCount > 0);

  InterlockedExchangeAdd((volatile long int*)&critSect->writeCount, -1);
}

#define MS_VC_EXCEPTION 0x406D1388

LONG WINAPI Sys_SetThreadName_ExceptionHandler(EXCEPTION_POINTERS *ExceptionInfo)
{
  if(ExceptionInfo->ExceptionRecord->ExceptionCode == MS_VC_EXCEPTION)
  {
    return EXCEPTION_CONTINUE_EXECUTION;
  }  
  return EXCEPTION_CONTINUE_SEARCH;
}


void Sys_SetThreadName(threadid_t tid, const char* szThreadName)
{
  #pragma pack(push,8)
  typedef struct tagTHREADNAME_INFO
  {
    DWORD dwType; // Must be 0x1000.
    LPCSTR szName; // Pointer to name (in user addr space).
    DWORD dwThreadID; // Thread ID (-1=caller thread).
    DWORD dwFlags; // Reserved for future use, must be zero.
  } THREADNAME_INFO;
  #pragma pack(pop)

  THREADNAME_INFO info;
  PVOID hException = AddVectoredExceptionHandler(0xFFFFFFFF, Sys_SetThreadName_ExceptionHandler);

  if(hException == NULL)
  {
    return;
  }

  info.dwType = 4096;
  info.szName = szThreadName;
  info.dwThreadID = tid;
  info.dwFlags = 0;
  RaiseException(0x406D1388u, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
  
  RemoveVectoredExceptionHandler(hException);
}

void* Sys_CreateThreadWithHandle(void* (*ThreadMain)(void*), threadid_t *tid, void* arg)
{
	char errMessageBuf[512];
	DWORD lastError;


	HANDLE thid = CreateThread(	NULL, // LPSECURITY_ATTRIBUTES lpsa,
								0, // DWORD cbStack,
								(LPTHREAD_START_ROUTINE)ThreadMain, // LPTHREAD_START_ROUTINE lpStartAddr,
								arg, // LPVOID lpvThreadParm,
								0, // DWORD fdwCreate,
								(DWORD*)tid );

	if(thid == NULL)
	{
		lastError = GetLastError();

		if(lastError != 0)
		{
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, lastError, MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT), (LPSTR)errMessageBuf, sizeof(errMessageBuf) -1, NULL);
			Com_PrintError(CON_CHANNEL_SYSTEM,"Failed to start thread with error: %s\n", errMessageBuf);

		}else{
			Com_PrintError(CON_CHANNEL_SYSTEM,"Failed to start thread!\n");
		}
		return NULL;
	}
	return thid;
}


bool Sys_SetThreadForProcessor(void* handle, unsigned int cpu)
{
  if(SetThreadIdealProcessor(handle, cpu) == (DWORD)-1)
  {
    return false;
  }
  return true;
}

void* Sys_GetThreadHandleForId(threadid_t tid)
{
  HANDLE localtheadhandle;
  HANDLE process = GetCurrentProcess();
  HANDLE pseudoHandle = GetCurrentThread();
  DuplicateHandle(process, pseudoHandle, process, &localtheadhandle, 0, 0, 2u);
  return localtheadhandle;
}


bool Sys_ThreadisSame(threadid_t threadid)
{
	threadid_t thread = GetCurrentThreadId();

	return threadid == thread;

}

unsigned int Sys_GetCpuCount()
{
  return s_cpuCount;
}

void Sys_SetThreadPriorityBelowNormal(void* handle)
{
  SetThreadPriority(handle, THREAD_PRIORITY_BELOW_NORMAL);
}

void Sys_SetThreadPriorityNormal(void* handle)
{
  SetThreadPriority(handle, THREAD_PRIORITY_NORMAL);
}

void Sys_SuspendThread(void* handle)
{
  SuspendThread(handle);
}
