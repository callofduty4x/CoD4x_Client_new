#include "../q_shared.h"


enum ThreadContextIndex
{
  THREAD_CONTEXT_MAIN,
  THREAD_CONTEXT_DATABASE,
  THREAD_CONTEXT_RENDERER,
  NUMTHREADS
};

typedef unsigned int threadid_t;


void** Sys_GetThreadLocalStorage();
void Sys_SetThreadLocalStorage(void**);

enum CriticalSection
{
  CRITSECT_CONSOLE = 0,
  CRITSECT_DEBUG_SOCKET = 1,
  CRITSECT_COM_ERROR = 2,
  CRITSECT_STATMON = 3,
  CRITSECT_SCRIPT_STRING = 4,
  CRITSECT_MEMORY_TREE = 5,
  CRITSECT_RD_BUFFER = 6,
  CRITSECT_SYS_EVENT_QUEUE = 7,
  CRITSECT_GPU_FENCE = 8,
  CRITSECT_FATAL_ERROR = 9,
  CRITSECT_DBHASH = 10,
  CRITSECT_PHYSICS = 11,
  CRITSECT_CVAR = 12,
  CRITSECT_AUDIO_PHYSICS = 13,
  CRITSECT_CINEMATIC = 14,
  CRITSECT_CINEMATIC_TARGET_CHANGE = 15,
  CRITSECT_CBUF = 16,
  CRITSECT_LOGFILE = 17,
  CRITSECT_LOGFILETHREAD = 18,
  CRITSECT_PLUGIN = 19,
  CRITSECT_HTTPS = 20,
  CRITSECT_RESOLVE = 21,
  CRITSECT_FILESYSTEM = 22,
  CRITSECT_DL_MAP = 23,
  CRITSECT_PHYSICAL_MEMORY = 24,
  CRITSECT_WATCHDOG = 25,
  CRITSECT_MISSING_ASSET = 26,
  CRITSECT_COUNT = 27
};

struct FastCriticalSection
{
  volatile int readCount;
  volatile int writeCount;
};


void Sys_EnterCriticalSection(CriticalSection section);
void Sys_LeaveCriticalSection(CriticalSection section);
void Sys_EnterCriticalSectionInternal(CriticalSection section);
void Sys_LeaveCriticalSectionInternal(CriticalSection section);
void Sys_SuspendOtherThreads();
bool Sys_IsMainThread();
bool Sys_WaitForSingleObjectTimeout(void **event, unsigned int msec);

void Com_InitThreadData(int threadContext);

bool Sys_IsRenderThread();
void Sys_SyncDatabase();
void Sys_ClearRGRegisteredEvent();

void* Sys_CreateEvent(bool bManualReset, bool bInitialState, const char *name);
bool Sys_WaitForSingleObjectTimeout(void **event, unsigned int msec);
void Sys_WaitForSingleObject(void **event);
void Sys_SetEvent(void **event);
void Sys_ResetEvent(void **event);
bool Sys_SpawnRenderThread(void ( *function)(unsigned int));
void Sys_LockWrite(FastCriticalSection *critSect);
void Sys_UnlockWrite(FastCriticalSection *critSect);
void Sys_SetResourcesQueuedEvent();
void Sys_ClearResourcesFlushedEvent();
void Sys_WaitResourcesFlushedEvent();
void Sys_ClearResourcesQueuedEvent();
void Sys_SetResourcesFlushedEvent();

void Sys_SetThreadName(threadid_t tid, const char* szThreadName);
void* Sys_CreateThreadWithHandle(void* (*ThreadMain)(void*), threadid_t *tid, void* arg);
bool Sys_SetThreadForProcessor(void* handle, unsigned int cpu);
threadid_t Sys_GetCurrentThreadId( void );
void Sys_InitThreadAffinity();
void* Sys_GetThreadHandleForId(threadid_t tid);
bool Sys_ThreadisSame(threadid_t threadid);
unsigned int Sys_GetCpuCount();
void Sys_SetThreadPriorityBelowNormal(void* handle);
void Sys_SetThreadPriorityNormal(void* handle);
void Sys_SuspendThread(void* handle);
void Sys_WaitDatabaseThread();
void Sys_WaitStartDatabase();

