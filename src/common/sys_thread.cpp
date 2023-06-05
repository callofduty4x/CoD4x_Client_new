#include "../q_shared.h"
#include "qcommon.h"
#include "sys_thread.h"

#define MAX_KEYS 3


#define MAX_VASTRINGS 2

struct va_info_t
{
  char va_string[MAX_VASTRINGS][1024];
  int index;
};

struct TraceCheckCount
{
  int global;
  int *partitions;
};

typedef struct TraceThreadInfo
{
  struct TraceCheckCount checkcount;
  struct cbrush_t *box_brush;
  struct cmodel_t *box_model;
}TraceThreadInfo;

enum ThreadOwner
{
  THREAD_OWNER_NONE = 0x0,
  THREAD_OWNER_DATABASE = 0x1,
  THREAD_OWNER_CINEMATICS = 0x2,
  THREAD_OWNER_SHUTDOWN = 0x3
};


void* sys_valuestoreage[NUMTHREADS][MAX_KEYS];

void* Sys_GetValue(int key)
{
    void **s;

    if(key < 1 || key > MAX_KEYS)
	Com_Error(ERR_FATAL, "Sys_GetValue: Invalid value");



    s = Sys_GetThreadLocalStorage();
    if(!s)
    {
        return NULL;
    }
    return s[key -1];
}

void Sys_SetValue(int key, void* value)
{
    void **s;

    if(key < 1 || key > MAX_KEYS)
	Com_Error(ERR_FATAL, "Sys_GetValue: Invalid value");

    s = Sys_GetThreadLocalStorage();
    if(!s)
    {
        return;
    }
    s[key -1] = value;
}

//Thread local buffers
extern struct va_info_t va_info[NUMTHREADS];
extern TraceThreadInfo g_traceThreadInfo[NUMTHREADS];

void Com_InitThreadData(int threadContext)
{
  Sys_SetThreadLocalStorage(sys_valuestoreage[threadContext]);

  Sys_SetValue(1, &va_info[threadContext]);
  Sys_SetValue(3, &g_traceThreadInfo[threadContext]);
/*
  if ( threadContext == 1 )
  {
    Sys_SetValue(4, &args);
  }
  else
  {
    Sys_SetValue(4, &g_cmd_args);
  }
*/
}


void Sys_EnterCriticalSection(CriticalSection section)
{
#ifdef THREAD_DEBUG

	if( section != CRITSECT_COM_ERROR)
		threadDebugPrint("Sys_EnterCriticalSection for Thread: %d Section: %d Depth: %d\n", Sys_GetCurrentThreadId(), section, mutex_depth[section]);
	mutex_depth[section] ++;
#endif
/*	if(Com_InError() && section != CRITSECT_COM_ERROR && Sys_IsMainThread() == qtrue)
	{
		Com_Error(0, "Error Cleanup");
	}
*/
	Sys_EnterCriticalSectionInternal(section);

#ifdef THREAD_DEBUG
	if( section != CRITSECT_COM_ERROR)
		threadDebugPrint("Section %d Locked for: %d\n", section, Sys_GetCurrentThreadId());
#endif

}

void Sys_LeaveCriticalSection(CriticalSection section)
{
#ifdef THREAD_DEBUG
	mutex_depth[section] --;
	if( section != CRITSECT_COM_ERROR)
		threadDebugPrint("Sys_LeaveCriticalSection for Thread: %d Section: %d\n", Sys_GetCurrentThreadId(), section);
#endif
	Sys_LeaveCriticalSectionInternal(section);
}
//Renderer events
void *rgRegisteredEvent;
void *resourcesQueuedEvent;
void *resourcesFlushedEvent;

//Database events
void *wakeDatabaseEvent;
void *databaseCompletedEvent;
void *databaseCompletedEvent2;
void *resumedDatabaseEvent;

//Threads common
void (*threadFunc[NUMTHREADS])(unsigned int p);
threadid_t threadId[NUMTHREADS];
void* threadHandle[NUMTHREADS];
const char* s_threadNames[] = { "Mainthread", "Database", "Renderer" };
enum ThreadOwner g_ThreadOwners[NUMTHREADS];



void Sys_ClearRGRegisteredEvent()
{
  Sys_ResetEvent(&rgRegisteredEvent);
}

void Sys_WaitRGRegisteredEvent()
{
  Sys_WaitForSingleObject(&rgRegisteredEvent);
}

void Sys_SetRGRegisteredEvent()
{
  Sys_SetEvent(&rgRegisteredEvent);
}

int Sys_QueryRGRegisteredEvent()
{
  return Sys_WaitForSingleObjectTimeout(&rgRegisteredEvent, 0);
}


bool Sys_SpawnRenderThread(void (*function)(unsigned int))
{
  rgRegisteredEvent = Sys_CreateEvent(1, 0, "rgRegisteredEvent");
  resourcesFlushedEvent = Sys_CreateEvent(1, 0, "resourcesFlushedEvent");
  resourcesQueuedEvent = Sys_CreateEvent(1, 0, "resourcesQueuedEvent");
  return true;
}

void Sys_SetResourcesQueuedEvent()
{
  Sys_SetEvent(&resourcesQueuedEvent);
}

void Sys_ClearResourcesFlushedEvent()
{
  Sys_ResetEvent(&resourcesFlushedEvent);
}

void Sys_WaitResourcesFlushedEvent()
{
  Sys_WaitForSingleObject(&resourcesFlushedEvent);
}

void Sys_ClearResourcesQueuedEvent()
{
  Sys_ResetEvent(&resourcesQueuedEvent);
}

void Sys_SetResourcesFlushedEvent()
{
  Sys_SetEvent(&resourcesFlushedEvent);
}

void* Sys_ThreadMain(void *parameter)
{
  unsigned int p = (unsigned int)parameter;
  assert(p < NUMTHREADS);
  assert(threadFunc[p] != NULL);

  Sys_SetThreadName(-1, s_threadNames[p]);
  Com_InitThreadData(p);
  threadFunc[p](p);
  return NULL;
}


qboolean Sys_SpawnDatabaseThread(void (*db_proc)(unsigned int p))
{
  wakeDatabaseEvent = Sys_CreateEvent(0, 0, "wakeDatabaseEvent");
  databaseCompletedEvent = Sys_CreateEvent(1, 1, "databaseCompletedEvent");
  databaseCompletedEvent2 = Sys_CreateEvent(1, 1, "databaseCompletedEvent2");
  resumedDatabaseEvent = Sys_CreateEvent(1, 1, "resumedDatabaseEvent");
  threadFunc[THREAD_CONTEXT_DATABASE] = db_proc;
  threadId[THREAD_CONTEXT_DATABASE] = 0;
  threadHandle[THREAD_CONTEXT_DATABASE] = Sys_CreateThreadWithHandle(Sys_ThreadMain, &threadId[THREAD_CONTEXT_DATABASE], (void*)THREAD_CONTEXT_DATABASE);

  if ( threadHandle[THREAD_CONTEXT_DATABASE] )
  {
    if ( Sys_GetCpuCount() == 1 )
    {
      Sys_SetThreadForProcessor(threadHandle[THREAD_CONTEXT_DATABASE], 0);
    }
    else if ( Sys_GetCpuCount() == 2 )
    {
      Sys_SetThreadForProcessor(threadHandle[THREAD_CONTEXT_DATABASE], 1u);
    }
    else
    {
      Sys_SetThreadForProcessor(threadHandle[THREAD_CONTEXT_DATABASE], 2u);
    }
    //ResumeThread(threadHandle[THREAD_CONTEXT_DATABASE]);
    return qtrue;
  }

  return qfalse;
}


void Sys_InitMainThread()
{
    threadid_t localthreadid = Sys_GetCurrentThreadId();

    void* localtheadhandle = Sys_GetThreadHandleForId(localthreadid);

    Sys_InitThreadAffinity();

    if(Sys_SetThreadForProcessor(localtheadhandle, 0) == false)
    {
      Sys_Error("Sys_SetThreadForProcessor failed\n");
    }

    threadId[THREAD_CONTEXT_MAIN] = localthreadid;
    threadHandle[THREAD_CONTEXT_MAIN] = localtheadhandle;

    Sys_SetThreadName(-1, s_threadNames[THREAD_CONTEXT_MAIN]);

    Com_InitThreadData(THREAD_CONTEXT_MAIN);
}


bool Sys_IsMainThread( void )
{
	return Sys_ThreadisSame(threadId[THREAD_CONTEXT_MAIN]);
}

bool Sys_IsDatabaseThread( void )
{
	return Sys_ThreadisSame(threadId[THREAD_CONTEXT_DATABASE]);
}

bool Sys_IsRenderThread( void )
{
#pragma msg "Warning, wrong status over render tread returned"
  return true;
	return Sys_ThreadisSame(threadId[THREAD_CONTEXT_RENDERER]);
}

void Sys_ResumeDatabaseThread(enum ThreadOwner to)
{
  g_ThreadOwners[THREAD_CONTEXT_DATABASE] = THREAD_OWNER_NONE;
  Sys_SetEvent(&resumedDatabaseEvent);
}

void Sys_SuspendDatabaseThread(enum ThreadOwner owner)
{
  g_ThreadOwners[THREAD_CONTEXT_DATABASE] = owner;
  Sys_ResetEvent(&resumedDatabaseEvent);
}

bool Sys_HaveSuspendedDatabaseThread(enum ThreadOwner to)
{
  return g_ThreadOwners[THREAD_CONTEXT_DATABASE] == to;
}

void Sys_WaitDatabaseThread()
{
  Sys_WaitForSingleObject(&resumedDatabaseEvent);
}

void Sys_DatabaseCompleted()
{
/*
  g_databaseStopServer = 1;
  if ( serverCompletedEvent )
  {
      Sys_WaitForSingleObject(&serverCompletedEvent);
  }
*/
  Sys_SetEvent(&databaseCompletedEvent);
}

void Sys_DatabaseCompleted2()
{
  //g_databaseStopServer = 0;
  Sys_SetEvent(&databaseCompletedEvent2);
}


bool Sys_IsDatabaseReady2()
{
  bool signaled = Sys_WaitForSingleObjectTimeout(&databaseCompletedEvent2, 0) == 1;
  return signaled;
}

bool Sys_IsDatabaseReady()
{
  return Sys_WaitForSingleObjectTimeout(&databaseCompletedEvent, 0) == 1;
}

void Sys_SyncDatabase()
{
/*
    int semaphore;

    semaphore = R_ReleaseDXDeviceOwnership();
*/
    while ( !Sys_WaitForSingleObjectTimeout(&databaseCompletedEvent, 1u) )
    {
/*
        R_Cinematic_ForceRelinquishIO();
        if ( Sys_IsRenderThread() )
        {
            RB_Resource_Update(5);
        }
        SocketRouter_EmergencyFrame();
*/
    }
/*
    if ( semaphore )
    {
        R_AcquireDXDeviceOwnership(0);
    }
*/
}

void Sys_WakeDatabase()
{
    Sys_ResetEvent(&databaseCompletedEvent);
}

void Sys_WakeDatabase2()
{
    Sys_ResetEvent(&databaseCompletedEvent2);
}

void Sys_WaitStartDatabase()
{
    Sys_WaitForSingleObject(&wakeDatabaseEvent);
}

void Sys_NotifyDatabase()
{
    Sys_SetEvent(&wakeDatabaseEvent);
}



void Sys_BeginLoadThreadPriorities()
{
  Sys_SetThreadPriorityBelowNormal(threadHandle[THREAD_CONTEXT_MAIN]);
}

void Sys_EndLoadThreadPriorities()
{
  Sys_SetThreadPriorityNormal(threadHandle[THREAD_CONTEXT_MAIN]);
}


void Sys_SuspendOtherThreads()
{
    unsigned int threadIndex;
    threadid_t currentThreadId;

    currentThreadId = Sys_GetCurrentThreadId();
    for ( threadIndex = 0; threadIndex < ARRAY_COUNT(threadHandle); ++threadIndex )
    {
      if ( threadHandle[threadIndex] && threadId[threadIndex] && threadId[threadIndex] != currentThreadId)
      {
        Sys_SuspendThread(threadHandle[threadIndex]);
      }
    }
}