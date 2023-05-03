#include <windows.h>
#include <tlhelp32.h>
#include <direct.h>
#include "../q_shared.h"
#include "../common/sys_thread.h"
#include "../common/qcommon.h"
#include "win_local.h"
#include "win_input.h"
#include "win_shared.h"
#include "resource.h"



SysInfo sys_info;
WinVars_t g_wv;

qboolean IsJumpInstruction(void* adr)
{
	byte* inst = (byte*)adr;
	if(inst[0] == 0xe9)
	{
		return qtrue;
	}
	return qfalse;
}

qboolean Sys_RemoveHookFromProc(void* topatchproc, byte* replacebytes, int replacebyteslen)
{
	DWORD oldprotect, dummyoldp;

	/* Detect if a hook was really installed */
	if(IsJumpInstruction(topatchproc) == qfalse)
	{
		//No hook found
		return qtrue;
	}

	if(VirtualProtect(topatchproc, replacebyteslen, PAGE_EXECUTE_READWRITE, &oldprotect) == 0)
	{

		return qfalse;
	}
	memcpy(topatchproc, replacebytes, replacebyteslen);

	VirtualProtect(topatchproc, replacebyteslen, oldprotect, &dummyoldp);

	return qtrue;

}

qboolean IsHotpatchEntrypoint(void* adr)
{
	byte* inst = (byte*)adr;

	if(inst[2] != 0x55){
		return qfalse;
	}
	if(inst[3] != 0x8b || inst[4] != 0xec)
	{
		return qfalse;
	}
	return qtrue;

}

qboolean Sys_RemoveHooksFromModule(const char* libraryname, const char* cleanprocname, const char **tocleanprocs, int numprocs)
{
	void* topatchproc;
	void* cleancmpproc;
	int i;

	HMODULE hModule = GetModuleHandleA(libraryname);
	byte buffer[5];

	if(hModule == NULL)
	{
		return qfalse;
	}

	cleancmpproc = (void*)GetProcAddress(hModule, cleanprocname);
	if(cleancmpproc == NULL)
	{
		return qfalse;
	}

	/* Dirty Hook is detected! Removing it... */
	if(IsHotpatchEntrypoint(cleancmpproc) == qfalse)
	{
		return qfalse;
	}

	memcpy(buffer, cleancmpproc, sizeof(buffer));

	for(i = 0; i < numprocs; ++i)
	{
		/* Get the proc addresses of "Direct3DCreate9" for fixing and "DebugSetLevel" to get bytes to copy from */
		topatchproc = (void*)GetProcAddress(hModule, tocleanprocs[i]);
		if(topatchproc == NULL){
			continue;
		}

		if(Sys_RemoveHookFromProc(topatchproc, buffer, sizeof(buffer)) == qfalse)
		{
			return qfalse;
		}
	}
	return qtrue;
}

void CleanKernel32Funcs()
{
	const char *kernelbaseprocs[] = {"GetModuleHandleW", "GetModuleHandleA", "GetModuleHandleExW", "GetModuleHandleExA"};

	Sys_RemoveHooksFromModule("KernelBase.dll", "Sleep", kernelbaseprocs, 4);
	Sys_RemoveHooksFromModule("kernel32.dll", "Sleep", kernelbaseprocs, 4);
}



qboolean Sys_AlreadyRunning(qboolean destroy)
{
	/*
	char varname[1024];
	static HANDLE hMutexOneInstance;
	qboolean alreadyRunning;

	uint32_t crc = crc32_16bytes(Sys_ExeFile(), strlen(Sys_ExeFile()), 0);

	Com_sprintf(varname, sizeof(varname), "Global\\%X-6-BZ34-1337-7331-IW3", crc);

	if(destroy)
	{
		if(hMutexOneInstance == NULL)
		{
			return 1;
		}
		hMutexOneInstance = NULL;
		CloseHandle(hMutexOneInstance);
		return 1;
	}

	hMutexOneInstance = CreateMutexA( NULL, TRUE, varname);
	alreadyRunning = (GetLastError() == ERROR_ALREADY_EXISTS);

	if (hMutexOneInstance != NULL)
    {
        ReleaseMutex(hMutexOneInstance);
    }
	return alreadyRunning;
	*/
	return qfalse;
}

void __noreturn Sys_NoFreeFilesError()
{
#ifdef MONKEY
  if ( Monkey_IsRunning() )
  {
    Monkey_Error("Sys_NoFreeFilesError");
    exit(-1);
  }
#endif
  Sys_EnterCriticalSection(CRITSECT_FATAL_ERROR);
  MessageBoxA(GetActiveWindow(), Win_LocalizeRef("WIN_DISK_FULL_BODY"), Win_LocalizeRef("WIN_DISK_FULL_TITLE"), 0x10u);
  exit(-1);
}

int Sys_IsGameProcess(int id)
{
  tagMODULEENTRY32 me;
  int isGame;
  char *i;
  char *moduleName;
  char modulePath[260];
  void *snapshot;
  void *process;

  process = OpenProcess(0x1F0FFFu, 0, id);
  if ( !process )
  {
    return 0;
  }
  CloseHandle(process);
  snapshot = CreateToolhelp32Snapshot(8u, id);
  if ( snapshot == (void *)-1 )
  {
    return 0;
  }
  isGame = 0;
  me.dwSize = sizeof(me);
  if ( Module32First(snapshot, &me) )
  {
    GetModuleFileNameA(0, modulePath, sizeof(modulePath));
    modulePath[sizeof(modulePath) -1] = 0;
    moduleName = modulePath;
    for ( i = modulePath; *i; ++i )
    {
      if ( *i == '\\' || *i == ':' )
      {
        moduleName = i + 1;
      }
    }
	while(1)
	{
		if(Q_stricmp(me.szModule, moduleName) == 0)
		{
		    isGame = 1;
			break;
		}
		if ( !Module32Next(snapshot, &me) )
		{
			break;
		}
	}
  }
  CloseHandle(snapshot);
  return isGame;
}

static char sys_processSemaphoreFile[260];

int Sys_GetSemaphoreFileName()
{
  char *i;
  char *moduleName;
  char modulePath[260];

  GetModuleFileNameA(0, modulePath, sizeof(modulePath));
  modulePath[sizeof(modulePath) -1] = 0;
  moduleName = modulePath;
  for ( i = modulePath; *i; ++i )
  {
    if ( *i != '\\' && *i != ':' )
    {
      if ( *i == '.' )
      {
        *i = 0;
      }
    }
    else
    {
      moduleName = i + 1;
    }
  }
  return sprintf(sys_processSemaphoreFile, "__%s", moduleName);
}

void Sys_NormalExit()
{
  DeleteFileA(sys_processSemaphoreFile);
}

int Sys_CheckCrashOrRerun()
{
  DWORD procID;
  int answer;
  DWORD byteCount;
  void *file;
  unsigned int id;

  if ( !sys_processSemaphoreFile[0] )
  {
    return 1;
  }
  procID = GetCurrentProcessId();
  file = CreateFileA(sys_processSemaphoreFile, 0x80000000, 0, 0, 3u, 2u, 0);
  if ( file != (void *)-1 )
  {
    if ( ReadFile(file, &id, sizeof(id), &byteCount, 0) && byteCount == sizeof(id) )
    {
      CloseHandle(file);
      if ( procID != id && Sys_IsGameProcess(id) )
      {
        return 0;
      }
      answer = MessageBoxA(GetActiveWindow(), Win_LocalizeRef("WIN_IMPROPER_QUIT_BODY"), Win_LocalizeRef("WIN_IMPROPER_QUIT_TITLE"), 0x33u);
      if ( answer == 6 )
      {
        Com_ForceSafeMode();
      }
      else if ( answer != 7 && answer == 2 )
      {
        return 0;
      }
    }
    else
    {
      CloseHandle(file);
    }
  }
  file = CreateFileA(sys_processSemaphoreFile, 0x40000000u, 0, 0, 2u, 2u, 0);
  if ( file == (void *)-1 )
  {
    Sys_NoFreeFilesError();
  }
  if ( !WriteFile(file, &procID, sizeof(procID), &byteCount, 0) || byteCount != sizeof(procID) )
  {
    CloseHandle(file);
    Sys_NoFreeFilesError();
  }
  CloseHandle(file);
  return 1;
}


void Sys_CreateErrorBox(const char* text)
{
  MessageBoxA(GetActiveWindow(), text, "Error", 0x10u);
}

void Sys_Error(const char *fmt, ...)
{
	struct tagMSG Msg;
	char		errormsg[0x1000];
	va_list		argptr;

    Sys_EnterCriticalSection( CRITSECT_COM_ERROR );

	Com_SetErrorEntered();

	Sys_SuspendOtherThreads();

	//R_DestroyGameWindows();

	va_start (argptr,fmt);
	Q_vsnprintf (errormsg, sizeof(errormsg), fmt, argptr);
	va_end (argptr);

	FixWindowsDesktop();

	if ( com_dedicated->current.integer && Sys_IsMainThread() )
	{
		Sys_ShowConsole(1, qfalse);
		Sys_Print("\n\n");
		Sys_Print(errormsg);
		Sys_Print("\n");
		Sys_CreateErrorBox(errormsg);
		while ( GetMessageA(&Msg, 0, 0, 0) )
		{
		  TranslateMessage(&Msg);
		  DispatchMessageA(&Msg);
		}
	}else{
		Sys_CreateErrorBox(errormsg);
	}
	Sys_AlreadyRunning(qtrue);
	ExitProcess(0);

//	doexit( 0, 0, 0 );
}

void Sys_Print(const char *msg)
{

//  OutputDebugStringA(msg);

  Conbuf_AppendTextInMainThread(msg);
}



struct sysEvent_t{
	int evTime;
	sysEventType_t evType;
	int evValue, evValue2;
	int evPtrLength;                // bytes of data pointed to by evPtr, for journaling
	void            *evPtr;         // this must be manually freed if not NULL
};

#define MAX_QUED_EVENTS  256
#define MAX_TIMED_EVENTS  1024
#define MASK_QUED_EVENTS ( MAX_QUED_EVENTS - 1 )
#define MASK_TIMED_EVENTS ( MAX_TIMED_EVENTS - 1 )

sysEvent_t eventQue[MAX_QUED_EVENTS];
int eventHead, eventTail;

/*
================
Com_QueueEvent

A time of 0 will get the current time
Ptr should either be null, or point to a block of data that can
be freed by the game later.
================
*/
void Sys_QueEvent( int time, sysEventType_t type, int value, int value2, int ptrLength, void *ptr )
{
	sysEvent_t  *ev;
	
	Sys_EnterCriticalSection(CRITSECT_SYS_EVENT_QUEUE);
	
	ev = &eventQue[ eventHead & MASK_QUED_EVENTS ];

	if ( eventHead - eventTail >= MAX_QUED_EVENTS )
	{
		Com_PrintWarning(CON_CHANNEL_SYSTEM,"Sys_QueEvent: overflow\n");
		// we are discarding an event, but don't leak memory
		if ( ev->evPtr )
		{
			Z_Free( ev->evPtr );
		}
		eventTail++;
	}

	eventHead++;

	if ( time == 0 )
	{
		time = Sys_Milliseconds();
	}

	ev->evTime = time;
	ev->evType = type;
	ev->evValue = value;
	ev->evValue2 = value2;
	ev->evPtrLength = ptrLength;
	ev->evPtr = ptr;
	Sys_LeaveCriticalSection(CRITSECT_SYS_EVENT_QUEUE);
}


void Sys_ShutdownEvents(  )
{
	sysEvent_t  *ev;
	
	Sys_EnterCriticalSection(CRITSECT_SYS_EVENT_QUEUE);

	while ( eventHead > eventTail )
	{
		ev = &eventQue[ eventTail & MASK_QUED_EVENTS ];

		if ( ev->evPtr )
		{
			Z_Free( ev->evPtr );
		}
		eventTail++;
	}

	Sys_LeaveCriticalSection(CRITSECT_SYS_EVENT_QUEUE);
}


void Sys_Quit()
{
    timeEndPeriod(1u);
    IN_Shutdown();

	//Sys_NormalExit();
	Win_ShutdownLocalization( );
	/* Function does not release all elements properly in some cases */
    //Dvar_Shutdown(); //sub_56B7D0();

	Sys_ShutdownEvents();
	Sys_DestroyConsole();

	Sys_AlreadyRunning(qtrue);
//  Sys_RestartProcessOnExit( );
//	Sys_RunInstallerOnDemand();
	assert(Sys_IsMainThread());
	ExitProcess(0);

}


void* win32QuitEvent;

BOOL Sys_QueryWin32QuitEvent()
{
  return Sys_WaitForSingleObjectTimeout(&win32QuitEvent, 0);
}

sysEvent_t Win_GetEvent()
{
	sysEvent_t ev;
	tagMSG msg;
	char *s;

	Sys_EnterCriticalSection(CRITSECT_SYS_EVENT_QUEUE);
	
	// return if we have data
	if ( eventHead > eventTail ) {
		eventTail++;
		ev = eventQue[ ( eventTail - 1 ) & MASK_QUED_EVENTS ];
	    Sys_LeaveCriticalSection(CRITSECT_SYS_EVENT_QUEUE);
		return ev;
	}	

	if ( Sys_QueryWin32QuitEvent() )
	{
		Com_Quit_f();
	}
	while ( PeekMessageA(&msg, 0, 0, 0, 0) )
	{
		if ( !GetMessageA(&msg, 0, 0, 0) )
		{
			Com_Quit_f();
		}
		g_wv.sysMsgTime = msg.time;
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	// check for console commands
	s = Sys_ConsoleInput();
	if ( s )
	{
		char	*b;
		int		len;	
		
		len = strlen(s) + 1;
		b = (char *)Com_AllocEvent(len);
		strcpy(b, s);
		Sys_QueEvent(0, SE_CONSOLE, 0, 0, len, b);
	}

	// return if we have data
	if ( eventHead > eventTail ) {
		eventTail++;
		ev = eventQue[ ( eventTail - 1 ) & MASK_QUED_EVENTS ];
	    Sys_LeaveCriticalSection(CRITSECT_SYS_EVENT_QUEUE);
		return ev;
	}	
	
	memset( &ev, 0, sizeof( ev ) );
	ev.evTime = Sys_Milliseconds();
	Sys_LeaveCriticalSection(CRITSECT_SYS_EVENT_QUEUE);
	return ev;


}


sysEvent_t Sys_GetEvent( )
{
  sysEvent_t ev;

  ev = Win_GetEvent( );
  return ev;
}

void Sys_LoadingKeepAlive()
{
  sysEvent_t ev;
#ifdef MONKEY
  Monkey_KeepAlive();
#endif
  do
  {
    ev = Win_GetEvent( );
  }
  while ( ev.evType != SE_NONE);
}


unsigned int sys_timeBase;
bool sys_timeInitialized;
/*
================
Sys_Milliseconds
================
*/

unsigned int Sys_Milliseconds(void){
	unsigned int sys_curtime;

	if( !sys_timeInitialized){
		sys_timeBase = timeGetTime();
		sys_timeInitialized = true;
	}
	sys_curtime = timeGetTime() - sys_timeBase;
	return sys_curtime;
}

unsigned int Sys_MillisecondsRaw()
{
	return timeGetTime();
}


void __noreturn Sys_OutOfMemErrorInternal(const char *filename, int line)
{
#ifdef MONKEY
  if ( Monkey_IsRunning() )
  {
    Monkey_Error(va("Sys_OutOfMemErrorInternal(%s, %d)", filename, line));
    exit(-1);
  }
#endif
  Sys_EnterCriticalSection(CRITSECT_FATAL_ERROR);
  Com_Printf(CON_CHANNEL_SYSTEM, "Out of memory: filename '%s', line %d\n", filename, line);
  MessageBoxA(GetActiveWindow(), Win_LocalizeRef("WIN_OUT_OF_MEM_BODY"), Win_LocalizeRef("WIN_OUT_OF_MEM_TITLE"), 0x10u);
  exit(-1);
}

char cl_cdkey[33] = { "                                " };
char cl_cdkeychecksum[5] = { "    " };

void Com_ReadCDKey()
{
	HKEY hKey;
	DWORD cbData;
	DWORD Type;
	char querydata[21];
	bool opened;
	LSTATUS errval;

	opened = (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Activision\\Call of Duty 4", 0, KEY_READ, &hKey) == ERROR_SUCCESS);
	if(opened == false)
	{
		errval = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Activision\\Call of Duty 4", 0, KEY_READ, &hKey);
		opened = (errval == ERROR_SUCCESS);
		if(opened == false)
		{
			Com_PrintError(CON_CHANNEL_SYSTEM, "Reg open key error %x\nCould not read a cdkey\n", (int)errval);
		}
	}


	if (opened == true )
	{
		Type = 1;
		cbData = 21;
		if ( RegQueryValueExA(hKey, "codkey", 0, &Type, (LPBYTE)querydata, &cbData) == 0 && cbData == 21)
		{
			Q_strncpyz(cl_cdkey, querydata, 16 +1);
			Q_strncpyz(cl_cdkeychecksum, querydata + 16, 4 +1);

			if(CL_CDKeyValidate(cl_cdkey, cl_cdkeychecksum))
			{
				RegCloseKey(hKey);
				return;
			}
		}
		RegCloseKey(hKey);
	}

	memset(cl_cdkey, ' ', 16);
	cl_cdkey[16] = '\0';
	memset(cl_cdkeychecksum, ' ', 4);
	cl_cdkeychecksum[4] = '\0';
}

void Com_WriteCDKey()
{
  HKEY hKey;
  char cdkey_full[33];

  if ( CL_CDKeyValidate(cl_cdkey, cl_cdkeychecksum) )
  {
    if ( !RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Activision\\Call of Duty 4", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_WOW64_64KEY, NULL, &hKey, NULL) )
    {
      strcpy(cdkey_full, cl_cdkey);
	  strcpy(cdkey_full + 16, cl_cdkeychecksum);
      if(RegSetValueExA(hKey, "codkey", 0, REG_SZ, (BYTE*)cdkey_full, 21u) != ERROR_SUCCESS)
	  {
		Com_PrintError(CON_CHANNEL_ERROR, "Error setting cdkey in registry!\n");
	  }
      RegCloseKey(hKey);
    }
  }
  else
  {
    strcpy(cl_cdkey, "                ");
  }
}



char * Sys_GetClipboardData()
{
  SIZE_T clipboardsz;
  HANDLE hClipboardData;
  char *data;
  char *cliptext;

  data = 0;
  if ( OpenClipboard(0) )
  {
    hClipboardData = GetClipboardData(1u);
    if ( hClipboardData )
    {
      cliptext = (char *)GlobalLock(hClipboardData);
      if ( cliptext )
      {
        clipboardsz = GlobalSize(hClipboardData);
        data = (char *)Z_Malloc(clipboardsz + 1, TAG_CLIPBOARD, qfalse);
        Q_strncpyz(data, cliptext, clipboardsz);
        GlobalUnlock(hClipboardData);
        strtok(data, "\n\r\b");
      }
    }
    CloseClipboard();
  }
  return data;
}

void Sys_FreeClipboardData(char *ptr)
{
  Z_Free(ptr);
}

void Sys_ShowEarlyErrorDialog(const char* functionName)
{
	char errMessageBuf[1024];
	char displayMessageBuf[1024];
	DWORD lastError = GetLastError();

	if(lastError != 0)
	{
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, lastError, MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT), errMessageBuf, sizeof(errMessageBuf) -1, NULL);
	}else{
		Q_strncpyz(errMessageBuf, "Unknown Error", sizeof(errMessageBuf));
	}

	Com_sprintf(displayMessageBuf, sizeof(displayMessageBuf), "Error in function: %s\nThe error is: %s", functionName, errMessageBuf);

	MessageBoxA(NULL, displayMessageBuf, "System Error", MB_OK | MB_ICONERROR);
}


int Sys_RemoveDirTree(const char *dir)
{
  HANDLE dhandle;
  bool hassep;
  struct _WIN32_FIND_DATAA FindFileData;
  char FileName[256];
  char lastchar;

  lastchar = dir[strlen(dir) - 1];
  if ( lastchar == '\\' || lastchar == '/' )
  {
    hassep = 1;
    Com_sprintf(FileName, sizeof(FileName), "%s*", dir);
  }
  else
  {
    hassep = 0;
	Com_sprintf(FileName, sizeof(FileName), "%s\\*", dir);
  }
  dhandle = FindFirstFileA(FileName, &FindFileData);
  if ( dhandle == (HANDLE)-1 )
  {
    return _rmdir(dir) != -1;
  }

  do
  {

    if ( FindFileData.cFileName[0] != '.' || (FindFileData.cFileName[1] && (FindFileData.cFileName[1] != '.' || FindFileData.cFileName[2])) )
    {
	    if(hassep)
		{
		  Com_sprintf(FileName, sizeof(FileName), "%s%s", dir, FindFileData.cFileName);
        }else{
		  Com_sprintf(FileName, sizeof(FileName), "%s\\%s", dir, FindFileData.cFileName);
		}

        if ( FindFileData.dwFileAttributes & 0x10 ? Sys_RemoveDirTree(FileName) == 0 : remove(FileName) == -1 )
		{
			FindClose(dhandle);
			return 0;
		}
    }
  }
  while ( FindNextFileA(dhandle, &FindFileData) != 0 );
  FindClose(dhandle);
  return _rmdir(dir) != -1;
}


const char* Sys_DefaultInstallPath()
{
  HMODULE hModule;
  DWORD len;
  static char exePath[256];

  if ( !exePath[0] )
  {
    hModule = GetModuleHandleA(0);
    if(hModule == NULL)
	{
		Com_Error(ERR_FATAL, "Sys_DefaultInstallPath: Got no HMODULE");
		return exePath;
	}
	len = GetModuleFileNameA(hModule, exePath, sizeof(exePath));
    if ( len == sizeof(exePath) )
    {
      len = sizeof(exePath) -1;
    }
    else if ( len == 0 )
    {
		Com_Error(ERR_FATAL, "Sys_DefaultInstallPath: Got no ModuleFileName");
		return exePath;
    }

    do
    {
      if ( exePath[len] == '\\' )
        break;
      if ( exePath[len] == '/' )
        break;
      if ( exePath[len] == ':' )
        break;

      --len;
    }
    while ( len );
    exePath[len] = 0;

  }
  return exePath;
}


void Sys_OpenURL(const char *url, int doexit)
{
  HWND wnd;

  if ( !ShellExecuteA(0, "open", url, 0, 0, 9) )
  {
    Com_Error(ERR_DROP, "EXE_ERR_COULDNT_OPEN_URL\x15%s", url);
  }
  wnd = GetForegroundWindow();
  if ( wnd )
  {
    ShowWindow(wnd, 3);
  }
  if ( doexit )
  {
    Cbuf_AddText(0, "quit\n");
  }
}

static char sys_exitCmdLine[1024];

void Sys_QuitAndStartProcess(const char *exeName)
{
  Q_strncpyz(sys_exitCmdLine, exeName, sizeof(sys_exitCmdLine));
  Cbuf_AddText(0, "quit\n");
}

void Sys_SpawnQuitProcess()
{
  char msgBuf[1024];
  unsigned int error;
  bool success;
  PROCESS_INFORMATION processInformation;
  STARTUPINFOA startupInfo;

  if ( sys_exitCmdLine[0] )
  {
    success = 1;
    /*
	if ( !LiveSteam_LaunchOtherApp(sys_exitCmdLine) )
    {
      success = 0;
    }*/
    memset(&startupInfo, 0, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    if ( !CreateProcessA(0, sys_exitCmdLine, 0, 0, 0, 0, 0, 0, &startupInfo, &processInformation) )
    {
      success = 0;
	}
    if ( !success )
    {
      error = GetLastError();
      FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 0, error, 0x400u, msgBuf, sizeof(msgBuf), 0);
      Com_Error(ERR_FATAL, "\x15%s '%s'\n%s(0x%08x)\n", Win_LocalizeRef("WIN_COULDNT_START_PROCESS"), sys_exitCmdLine, msgBuf, error);
    }
  }
}


void Sys_In_Restart_f()
{
  IN_Shutdown();
  IN_Init();
}

void Sys_Net_Restart_f()
{
  NET_Restart();
}

void DB_PrintEntries_f();
void DebugFileApi();


void Sys_Init()
{

  static cmd_function_s Sys_In_Restart_f_VAR;
  static cmd_function_s Sys_Net_Restart_f_VAR;
  static cmd_function_s DB_PrintEntries_f_VAR;


  OSVERSIONINFOA osversion;

  timeBeginPeriod(1u);
  Cmd_AddCommandInternal("in_restart", Sys_In_Restart_f, &Sys_In_Restart_f_VAR);
  Cmd_AddCommandInternal("net_restart", Sys_Net_Restart_f, &Sys_Net_Restart_f_VAR);
  Cmd_AddCommandInternal("db_print", DB_PrintEntries_f, &DB_PrintEntries_f_VAR); //Remove me after debug

  /*
  Cmd_AddCommandInternal("movie_start", Sys_Mjpeg, &Sys_Mjpeg_VAR);
  Cmd_AddCommandInternal("movie_stop", Sys_MjpegClose, &Sys_MjpegClose_VAR);
  Cmd_AddCommandInternal("net_listen", Sys_Listen_f, &Sys_Listen_f_VAR);
  Cmd_AddCommandInternal("net_connect", Sys_Connect_f, &Sys_Connect_f_VAR);
  */
  osversion.dwOSVersionInfoSize = sizeof(osversion);
  if ( !GetVersionExA(&osversion) )
  {
    Sys_Error("Couldn't get OS info");
  }
  const char* buildname = Com_GetBuildDisplayName();
  if ( osversion.dwMajorVersion < 4 )
  {
    Sys_Error("%s requires Windows version 4 or greater", buildname);
  }
  if ( !osversion.dwPlatformId )
  {
    Sys_Error("%s doesn't run on Win32s", buildname);
  }
  Com_Printf(CON_CHANNEL_SYSTEM, "CPU vendor is \"%s\"\n", sys_info.cpuVendor);
  Com_Printf(CON_CHANNEL_SYSTEM, "CPU name is \"%s\"\n", sys_info.cpuName);
  if ( sys_info.logicalCpuCount == 1 )
  {
    Com_Printf(CON_CHANNEL_SYSTEM, "%i logical CPUs reported\n", sys_info.logicalCpuCount);
  }
  else
  {
    Com_Printf(CON_CHANNEL_SYSTEM, "%i logical CPUs reported\n", sys_info.logicalCpuCount);
  }
  Com_Printf(CON_CHANNEL_SYSTEM, "%i physical CPUs detected\n", sys_info.physicalCpuCount);
  Com_Printf(CON_CHANNEL_SYSTEM, "Measured CPU speed is %.2lf GHz\n", sys_info.cpuGHz);
  Com_Printf(CON_CHANNEL_SYSTEM, "Total CPU performance is estimated as %.2lf GHz\n", sys_info.configureGHz);
  Com_Printf(CON_CHANNEL_SYSTEM, "System memory is %i MB (capped at 1 GB)\n", sys_info.sysMB);
  Com_Printf(CON_CHANNEL_SYSTEM, "Video card is \"%s\"\n", sys_info.gpuDescription);
  if ( sys_info.SSE )
  {
    Com_Printf(CON_CHANNEL_SYSTEM, "Streaming SIMD Extensions (SSE) are supported\n");
  }
  else
  {
    Com_Printf(CON_CHANNEL_SYSTEM, "Streaming SIMD Extensions (SSE) are not supported\n");
  }
  Com_Printf(CON_CHANNEL_SYSTEM, "\n");
  IN_Init();
}


void __noreturn Sys_DirectXFatalError()
{
#ifdef MONKEY
  if ( Monkey_IsRunning() )
  {
    Monkey_Error("Sys_DirectXFatalError");
    exit(-1);
  }
#endif
  Sys_EnterCriticalSection(CRITSECT_FATAL_ERROR);
  MessageBoxA(GetActiveWindow(), Win_LocalizeRef("WIN_DIRECTX_INIT_BODY"), Win_LocalizeRef("WIN_DIRECTX_INIT_TITLE"), 0x10u);
  ShellExecuteA(0, "open", "Docs\\TechHelp\\Tech Help\\Information\\DirectX.htm", 0, 0, 3);
  exit(-1);
}


static char exeFilename[ MAX_STRING_CHARS ] = { 0 };


/*
=================
Sys_SetExeFile
=================
*/
void Sys_SetExeFile(const char *filepath)
{
	Q_strncpyz(exeFilename, filepath, sizeof(exeFilename));
}

/*
=================
Sys_ExeFile
=================
*/
const char* Sys_ExeFile( void )
{
	return exeFilename;
}


char sys_cwd[1024];

void Sys_Cwd(char* path, int len)
{
	Q_strncpyz(path, sys_cwd, len);
}

const char* Sys_Cwd( )
{
	return sys_cwd;
}


void Sys_SetupCwd(  )
{
	char* cut;

	Q_strncpyz(sys_cwd, Sys_ExeFile(), sizeof(sys_cwd));
	cut = strrchr(sys_cwd, PATH_SEP);
	if(cut != NULL)
	{
		*cut = '\0';
		SetCurrentDirectory(sys_cwd);
	}
}


void Win_RegisterClass(){

	WNDCLASSEXA wc;

	memset(&wc, 0, sizeof( wc ));
	wc.cbSize = sizeof( wc );
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.hInstance = g_wv.hInstance;
	wc.hIcon = LoadIconA(g_wv.hInstance, (LPCSTR)IDI_ICON1);
	wc.hCursor = LoadCursorA(NULL, (LPCSTR)0x7F00);
	wc.hbrBackground = CreateSolidBrush(0);
	wc.lpszClassName = "CoD4";
	if ( !RegisterClassExA(&wc) )
	{
		Com_Error(ERR_FATAL, "EXE_ERR_COULDNT_REGISTER_WINDOW");
	}
}



void D3DXCompileShaderInit()
{

}


int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	char cwd[256];
	char lpFilename[MAX_STRING_CHARS];
	int copylen;
	char cmdline[4096];
/*
	char tchr;
	bool pbrequested;
	int choice;
*/
	copylen = GetModuleFileNameA(hInstance, lpFilename, sizeof(lpFilename));
	if(copylen >= (signed int)(sizeof(lpFilename) -1))
	{
		Sys_SetExeFile( "" );
	}else{
		Sys_SetExeFile( lpFilename );
	}

	Sys_SetupCwd( );
	SetDllDirectoryA("");

	Sys_InitializeCriticalSections();

	Sys_InitMainThread();

	Win_InitLocalization();

	//Com_sprintf(UPDATE_VERSION, sizeof(UPDATE_VERSION), "%s%c", UPDATE_VERSION_NUM, tchr);
#if 0
	if(!strstr(lpCmdLine, "allowdupe") && !strstr(lpCmdLine, "dedicated") && !strstr(lpCmdLine, "installupdatefiles") && !strstr(lpCmdLine, "ui_playerProfileAlreadyChosen"))
	{
		//GetApplicationLockFileName();

		while(Sys_AlreadyRunning(qfalse))
		{
			choice = MessageBoxTimeoutA(NULL, "An copy of CoD4 is already running", "CoD4 is already running",
										MB_ABORTRETRYIGNORE | MB_DEFBUTTON1 | MB_SETFOREGROUND | MB_ICONERROR,
										0, 60000);
			if(choice == IDRETRY)
			{
				Sys_AlreadyRunning(qtrue);
				continue;
			}
			if(choice == IDIGNORE)
			{
				break;
			}
			Sys_AlreadyRunning(qtrue);
			return -1;
		}

		if(strstr(lpCmdLine, "+save")){
			if(!Sys_CheckCrashOrRerun()){
				*((DWORD*)(0xcc147d4)) = 0;
				*((DWORD*)(0xcc147d8)) = 0;
				Sys_AlreadyRunning(qtrue);
				return(0);
			}
		}
	}
#endif

	Com_InitParse();
	Dvar_Init();


	InitTiming();

	Sys_FindInfo();
	g_wv.hInstance = hInstance;

	//Clean the commandline from the executable path so no weird error show up
	const char* c = lpCmdLine;
	cmdline[0] = '\0';
	while(*c == ' ' && *c != '\0')
	{
		++c;
	}
	if(*c == '\"')
	{
		++c;
		while(*c != '\"' && *c != '\0')
		{
			++c;
		}
		if(*c != '\0')
		{
			++c;
			if(*c == ' ')
			{
				++c;
			}
		}
		Q_strncpyz( cmdline, c, sizeof(cmdline));
	}else{
		Q_strncpyz( cmdline, lpCmdLine, sizeof(cmdline));
	}

	if(strstr(lpCmdLine, "+nosplash") == NULL)
	{
		Sys_CreateSplashWindow();

	}


	Win_RegisterClass();

	D3DXCompileShaderInit();


//	if(strstr(lpCmdLine, "+sysconsole") != NULL)
//	{
		Sys_CreateConsole( qtrue );
//	}else{
//		Sys_CreateConsole( qfalse );
//	}

	SetErrorMode(1);

	Sys_Milliseconds();

	Com_Init( cmdline );


	if(!com_dedicated || !com_dedicated->current.integer)
		Cbuf_AddText(0, "readStats\n");


	Sys_Cwd( cwd, sizeof(cwd));

	Com_Printf(CON_CHANNEL_SYSTEM, "Working directory: %s\n", cwd);

#if 0
	if((!com_dedicated || !com_dedicated->current.integer))
	{
		pbrequested = Dvar_GetBool("cl_punkbuster");
		PBCL_GlobalConstructor();
		if(!PbClientInitialize(g_wv.hInstance)){
			if(pbrequested)
			{
				Com_SetErrorMessage("MPUI_NOPUNKBUSTER");
			}
		}
	}

	pbrequested = Cvar_GetBool("sv_punkbuster");
	PBSV_GlobalConstructor();
	if(!PbServerInitialize()){
		if(pbrequested)
		{
			Com_PrintError(CON_CHANNEL_SYSTEM, "Unable to initialize PunkBuster. PunkBuster is disabled\n");
			Com_SetErrorMessage("MPUI_NOPUNKBUSTER");
		}
	}
#endif
	SetFocus(g_wv.hWnd);

	CleanKernel32Funcs();

//	FS_ValidateIwdFiles();


	while(qtrue)
	{
		if((com_dedicated && com_dedicated->current.integer) || g_wv.isMinimized){
			Sys_Sleep(5);
		}

		Com_Frame();
#if 0		
		PbServerProcessEvents(0);

		if(!com_dedicated || !com_dedicated->current.integer)
		{
			PbClientProcessEvents();
		}
#endif
	}
	return 0;
}

