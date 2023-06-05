#include "qcommon.h"
#include "sys_thread.h"
#include <gfx_d3d/r_shared.h>
#include <client/client_shared.h>
#include <script/scr_shared.h>
#include <script/cscr_stringlist.h>
#include <script/cscr_animtree.h>
#include <server/server_shared.h>
#include "com_dobj_shared.h"
#include <xanim/dobj_shared.h>
#include <xanim/xanim_shared.h>
#include "com_world.h"
#include "sys_shared.h"
#include "cm_public.h"
#include <database/db_shared.h>
#include <ctype.h>
#include <sound/snd_shared.h>
#include "physicalmemory.h"
#include <client/cl_storage.h>
#include "com_playerprofile.h"
#include <sound/snd_shared.h>
#include <client/screen_placement.h>
#include "netchan.h"
#include "stringed_public.h"
#include <ui/ui_public.h>
#include <ragdoll/ragdoll_shared.h>
#include <client/cl_console.h>
#include "ctrycatch.h"

extern char com_errorMessage[0x1000];
dvar_s* com_recommendedSet;
dvar_s* com_nextmap;
extern dvar_s* com_introPlayed;
extern dvar_s* com_animCheck;
extern dvar_s* com_maxfps;
extern dvar_s* com_timescale;
extern dvar_s* dev_timescale;
extern dvar_s* com_fixedtime;
extern dvar_s* com_statmon;

extern qboolean com_fullyInitialized;
float com_codeTimeScale;
float com_timescaleValue;
unsigned int com_frameNumber;
static int com_lastFrameIndex;
static int com_lastFrameTime;
extern int errorcode;


void Com_ErrorCleanup( );
qboolean Com_AddStartupCommands( void );
void Com_ParseCommandLine( char *commandLine );
void Com_CheckSetRecommended(int localclientnum);
void Com_WriteConfig_f();
void Com_WriteDefaults_f();
void Com_StartHunkUsers();
void Com_EventLoop();
void Com_SetDedicatedMode();
void Com_Statmon();
void Com_WriteConfiguration(int localClientNum);




const char * Com_GetBuildDisplayName()
{
	return "Call of Duty 4 v1.7";
}

bool Com_IsFullyInitialized()
{
	return com_fullyInitialized;
}

/*
==================
Com_RandomBytes

fills string array with len radom bytes, peferably from the OS randomizer
==================
*/
void Com_RandomBytes( byte *string, int len )
{
	int i;

	if( Sys_RandomBytes( string, len ) )
  {
		return;
  }
	Com_Printf(CON_CHANNEL_SYSTEM, "Com_RandomBytes: using weak randomization\n" );
	for( i = 0; i < len; i++ )
  {
		string[i] = (unsigned char)( rand() % 255 );
  }
}

/*
=============
Com_Error_f

Just throw a fatal error to
test error shutdown procedures
=============
*/
static void Com_Error_f (void) {
	if ( Cmd_Argc() > 1 ) {
		Com_Error( ERR_DROP, "Testing drop error" );
	} else {
		Com_Error( ERR_FATAL, "Testing fatal error" );
	}
}


/*
=============
Com_Freeze_f

Just freeze in place for a given number of seconds to test
error recovery
=============
*/
static void Com_Freeze_f (void) {
	float	s;
	int		start, now;

	if ( Cmd_Argc() != 2 ) {
		Com_Printf(CON_CHANNEL_SYSTEM, "freeze <seconds>\n" );
		return;
	}
	s = atof( Cmd_Argv(1) );

	start = Sys_Milliseconds();

	while ( 1 ) {
		now = Sys_Milliseconds();
		if ( ( now - start ) * 0.001 > s ) {
			break;
		}
	}
}

/*
=================
Com_Crash_f

A way to force a bus error for development reasons
=================
*/
static void Com_Crash_f( void ) {
	* ( int * ) 0 = 0x12345678;
}

void Com_Assert_f()
{
  assertx(NULL, "Testing assertion");
}

void Com_SetErrorEntered()
{

	com_errorEntered = qtrue;

}

void Com_AdjustMaxFPS(int *maxFPS)
{
  int maxUserCmdsPerSecond;

  if ( com_timescaleValue < 1.0 )
  {
    maxUserCmdsPerSecond = (int)(320.0 * com_timescaleValue);
    if ( maxUserCmdsPerSecond < 1 )
    {
      maxUserCmdsPerSecond = 1;
    }
    if ( !*maxFPS || *maxFPS > maxUserCmdsPerSecond )
    {
      *maxFPS = maxUserCmdsPerSecond;
    }
  }
}

void Com_SyncThreads()
{
  R_SyncRenderThread();
  if ( com_sv_running )
  {
    if ( com_sv_running->current.enabled )
    {
      SV_WaitServer();
      SV_AllowPackets(0);
    }
  }
  R_WaitWorkerCmds();
}

fileHandle_t logfile;

bool Com_LogFileOpen()
{
	return logfile != 0;
}

void Com_CloseLogfiles()
{
  if ( logfile )
  {
    FS_FCloseLogFile(logfile);
    logfile = 0;
  }
}

void Com_ClearTempMemory()
{
  Hunk_ClearTempMemory();
  Hunk_ClearTempMemoryHigh();
}

void Com_SetScriptSettings()
{
  Scr_Settings(com_developer->current.integer || com_logfile->current.integer, com_developer_script->current.enabled, com_developer->current.integer);
}

void Com_Close()
{
    Com_ShutdownDObj();
    DObjShutdown();
    XAnimShutdown();
    //R_FreeWaterSimulationBuffers();
    Com_ShutdownWorld();
    CM_Shutdown();
    //UI_ScreenshotShutdown();
    //Live_FileShare_CacheShutdown();
    SND_ShutdownChannels();
    Hunk_Clear();
    if ( useFastFile->current.enabled )
    {
        DB_ShutdownXAssets();
    }
    Scr_Shutdown( );
    //Scr_Shutdown(SCRIPTINSTANCE_CLIENT);
    //NET_ShutdownDebug();
    //Hunk_UserShutdown();
    Hunk_ShutdownDebugMemory();
}

void Com_Quit_f()
{
    Com_Printf(CON_CHANNEL_DONT_FILTER, "quitting...\n");
/*	
    while ( r_glob.remoteScreenUpdateNesting )
	{
		R_EndRemoteScreenUpdate();
	}
*/  
	Com_SyncThreads();
  //scrVarPub.evaluate = 0;
  Sys_EnterCriticalSection( CRITSECT_COM_ERROR );
	GScr_Shutdown();

	if ( !com_errorEntered )
  {
    Com_ClearTempMemory();
		Sys_DestroySplashWindow();
    CL_Shutdown(0);
//		CL_ShutdownSteamApi();
//		CL_DiscordShutdown();
    SV_Shutdown("EXE_SERVERQUIT");
    CL_ShutdownRef(); //Also destroy window

    Com_Close();
    Com_CloseLogfiles();
    FS_Shutdown(1);
		FS_ShutdownIwdPureCheckReferences();
		FS_ShutdownServerIwdNames( );
		FS_ShutdownServerReferencedIwds( );
		FS_ShutdownServerReferencedFFs( );
  }
	Key_Shutdown();
  RefreshQuitOnErrorCondition();
  Dvar_Shutdown();
	Cmd_Shutdown();
	Con_Shutdown();
  //Sys_ShutdownEvents();
	SL_Shutdown();
	Con_ShutdownChannels();
	Sys_Quit();
}



void Com_Init(char *commandLine)
{
  TRY(Exception_type::SystemException)
  {
    Com_Printf(CON_CHANNEL_SYSTEM,"%s %s %s build %i %s\n", GAME_STRING,Q3_VERSION,PLATFORM_STRING, Sys_GetBuild(), __DATE__);
    Com_ParseCommandLine(commandLine);
    SL_Init();
    Swap_Init();
    Cbuf_Init();
    Cmd_Init();
    Com_StartupVariable(0);
    Com_InitDvars();
    com_nextmap = Dvar_RegisterString("nextmap", "", 0, "Next map to play"); //shall be placed in Com_InitDvars()
    CCS_InitConstantConfigStrings();
    int initStartTime = 0;
    if ( useFastFile->current.enabled )
    {
      PMem_Init();
      DB_SetInitializing(1u);
      Com_Printf(CON_CHANNEL_CONSOLEONLY, "begin $init\n");
      initStartTime = Sys_Milliseconds();
      PMem_BeginAlloc("$init", 1u);
      DB_InitThread();
    }
    CL_InitKeyCommands();
    FS_InitFilesystem();
    Con_InitChannels();
    LiveStorage_Init();
    Com_InitPlayerProfiles(0);
    Cbuf_Execute(0, CL_ControllerIndexFromClientNum(0));
    if ( (dvar_modifiedFlags & 0x20) != 0 )
    {
      Com_InitDvars();
    }

    com_recommendedSet = Dvar_RegisterBool("com_recommendedSet", 0, 1u, "Use recommended settings");
    Com_CheckSetRecommended(0);
    Com_StartupVariable(0);
    if ( !useFastFile->current.enabled )
    {
      SEH_UpdateLanguageInfo();
    }
    if ( com_dedicated->current.integer )
    {
      CL_InitDedicated();
    }
    Com_InitHunkMemory();
    Hunk_InitDebugMemory();
    dvar_modifiedFlags &= ~1u;
    com_codeTimeScale = 1.0;
    if ( com_developer->current.integer )
    {
      Cmd_AddCommand("error", Com_Error_f);
      Cmd_AddCommand("crash", Com_Crash_f);
      Cmd_AddCommand("freeze", Com_Freeze_f);
      Cmd_AddCommand("assert", Com_Assert_f);
    }
    Cmd_AddCommand("quit", Com_Quit_f);
    Cmd_AddCommand("writeconfig", Com_WriteConfig_f);
    Cmd_AddCommand("writedefaults", Com_WriteDefaults_f);

    dvar_s* version = Dvar_RegisterString("version", "", 0x40u, "Game version");
    Dvar_SetString(version, va("%s %s build %s %s", GAME_STRING, Q3_VERSION, Sys_GetBuild(), PLATFORM_STRING));
    Dvar_RegisterString("shortversion", Q3_VERSION, 0x44u, "Short game version");
    Sys_Init();
    
    unsigned short qport;
    Com_RandomBytes( (byte*)&qport, sizeof(short) );
    Netchan_Init( qport );

    Scr_InitVariables();
    Scr_Init();
    Com_SetScriptSettings();
    XAnimInit();
    DObjInit();
    SV_Init();
    NET_Init();
    Dvar_ClearModified(com_dedicated);

    if ( !com_dedicated->current.integer )
    {
      ScrPlace_Init();
      CL_InitOnceForAllClients();
      CL_Init(0);
      com_frameTime = Sys_Milliseconds();
      Com_StartupVariable(0);
      SND_InitDriver();
      R_InitOnce();
      CL_InitRenderer();
      Com_InitDebugSystems();
      cls.soundStarted = qtrue;
      SND_Init();
      if ( !com_introPlayed->current.enabled )
      {
        Cbuf_AddText(0, "cinematic IW_logo\n");
        Dvar_SetString(com_nextmap, "cinematic atvi; set nextmap \"cinematic Aspyr; set nextmap cinematic cod_intro\"");
        Dvar_SetBool(com_introPlayed, 1);
      }
    }else{
      com_frameTime = Sys_Milliseconds();
      Com_StartupVariable(0);
    }
    if ( useFastFile->current.enabled )
    {
      PMem_EndAlloc("$init", 1u);
      DB_SetInitializing(0);
      Com_Printf(CON_CHANNEL_SYSTEM, "end $init %d ms\n", Sys_Milliseconds() - initStartTime);
    }
    com_fullyInitialized = qtrue;
    Com_Printf(CON_CHANNEL_SYSTEM, "--- Common Initialization Complete ---\n");
  }
  CATCH
  {
    Sys_Error("Error during initialization:\n%s\n", com_errorMessage);
  }
  ENDTRY

  TRY( Exception_type::SystemException )
  {
    Com_AddStartupCommands();
  }
  CATCH
  {
    if ( com_errorEntered )
    {
      Com_ErrorCleanup( );
    }
  }
  ENDTRY


  if ( !com_sv_running->current.enabled && com_dedicated->current.integer == 0)
  {
    TRY( Exception_type::SystemException )
    {
      if ( !cls.rendererStarted )
      {
        CL_InitRenderer();
      }
      CL_StartHunkUsers();
    }
    CATCH
    {
      Sys_Error("Error during initialization:\n%s\n", com_errorMessage);
    }
    ENDTRY
  }
}

int Com_ModifyMsec(int msec)
{
  int originalMsec;
  bool useTimescale;

  originalMsec = msec;
  if ( com_fixedtime->current.integer )
  {
    msec = com_fixedtime->current.integer;
    useTimescale = 1;
  }
  else if ( com_timescale->current.value == 1.0 && com_codeTimeScale == 1.0 && dev_timescale->current.value == 1.0 )
  {
    useTimescale = 0;
  }
  else
  {
    msec = (int)((float)msec * com_timescale->current.value * com_codeTimeScale * dev_timescale->current.value);
    useTimescale = 1;
  }
  if ( msec < 1 )
  {
    msec = 1;
  }
  if ( msec > 500 && msec < 500000 )
  {
    Com_PrintWarning(CON_CHANNEL_SYSTEM, "Hitch warning: %i msec frame time\n", msec);
  }
  if ( msec > 5000 )
  {
    msec = 5000;
  }
  if ( useTimescale && originalMsec )
  {
    com_timescaleValue = (float)msec / (float)originalMsec;
  }
  else
  {
    com_timescaleValue = 1.0;
  }
  return msec;
}



void Com_Frame()
{
  TRY(Exception_type::SystemException)
  {
    int msec;
    int maxFPS;

    DB_Update();
    //Start of official try block function
    assert(Cmd_AssertNestingIsReset());

    PIXBeginNamedEvent(-1, "Com_Frame");
    Com_WriteConfiguration(0);
    SetAnimCheck(com_animCheck->current.enabled);
    maxFPS = com_maxfps->current.integer;
    Com_AdjustMaxFPS(&maxFPS);
    Win_UpdateThreadLock();
    ++com_lastFrameIndex;
    for ( int i = 0; i < 50; ++i )
    {
      Com_EventLoop();
      com_frameTime = Sys_Milliseconds();
      if ( com_frameTime - com_lastFrameTime < 0 )
      {
        com_lastFrameTime = com_frameTime;
      }
      msec = com_frameTime - com_lastFrameTime;
      if ( msec >= 1 )
      {
        break;
      }
      NET_Sleep(1);
    }
    com_lastFrameTime = com_frameTime;
  /*
    for ( int localControllerIndex = 0; localControllerIndex < 1; ++localControllerIndex )
    {
      TaskManager2_ProcessTasks(localControllerIndex);
    }
  */
    Cbuf_Execute(0, CL_ControllerIndexFromClientNum(0));
    /*
    ProcessStringEdCmds();
    ProcessGDTCmds();
    if ( Demo_IsPlaying() && msec > maxDemoMsec )
    {
      msec = maxDemoMsec;
    }
    cls.inputRealMsec = msec;
    Demo_Frame(msec);
    */
    msec = Com_ModifyMsec(msec);
    //LiveSteam_Frame();
    PIXBeginNamedEvent(-1, "SV frame");
    SV_Frame(msec);
    
    Com_SetDedicatedMode( );

    if ( com_dedicated->current.integer == 0)
    {
      R_SetEndTime( com_lastFrameTime );
      PIXBeginNamedEvent(-1, "pre frame");
      CL_RunOncePerClientFrame( 0, msec );

      Com_EventLoop( );
      Cbuf_Execute(0, CL_ControllerIndexFromClientNum(0));
      PIXBeginNamedEvent(-1, "CL_Frame");
      CL_Frame(0, msec);

      /* reset cvar_modifiedFlags */
      dvar_modifiedFlags &= ~CVAR_USERINFO;

      if ( !UI_IsFullscreen(0) && !CL_GetLocalClientUIGlobals(0)->state )
      {
        UI_SetActiveMenu(0, UI_GetMenuScreen());
      }

      SCR_UpdateScreen( );

      Ragdoll_Update( msec );
      SCR_UpdateRumble();
      Com_Statmon( );

      R_WaitEndTime( );
    }
    /*
    if ( GetCurrentThreadId() == g_DXDeviceThread.owner && !g_DXDeviceThread.aquired )
    {
      D3DPERF_EndEvent();
    }
    */
    //Monkey_Frame();
    //Phys_RunToTime(svsHeader.time);
    /*
    if ( GetCurrentThreadId() == g_DXDeviceThread.owner && !g_DXDeviceThread.aquired )
    {
      D3DPERF_EndEvent();
    }
    */
    //End of official try block function

    ++com_frameNumber;
  }
  CATCH
  {
    Sys_EnterCriticalSection(CRITSECT_COM_ERROR);
    Com_ErrorCleanup();
    Sys_LeaveCriticalSection(CRITSECT_COM_ERROR);
    if ( !com_dedicated->current.integer )
    {
      CL_InitRenderer();
      Com_StartHunkUsers();
    }
  }
  ENDTRY
}

int Com_GpuStringCompare(const char *wild, const char *s)
{
  int lCharWild;
  int lCharRef;
  char charWild;
  char charRef;

  do
  {
    charWild = *wild++;
    if ( charWild == '*' )
    {
      if ( !*wild )
      {
        return 0;
      }
      if ( *s && !Com_GpuStringCompare(wild - 1, s + 1) )
      {
        return 0;
      }
    }
    else if ( charWild == 32 )
    {
      if ( *s && !isdigit(*s) && !Com_GpuStringCompare(wild - 1, s + 1) )
      {
        return 0;
      }
    }
    else
    {
      charRef = *s++;
      if ( charWild != charRef && charWild != '?' )
      {
        lCharWild = tolower(charWild);
        lCharRef = tolower(charRef);
        if ( lCharWild != lCharRef )
        {
          return 2 * (lCharWild - lCharRef >= 0) - 1;
        }
      }
    }
  }
  while ( charWild );
  return 0;
}



void Com_SetConfigureDvars(int dvarCount, const char (*dvarNames)[32], const char (*dvarValues)[32])
{
  dvar_s *dvar;
  int dvarIndex;

  for ( dvarIndex = 0; dvarIndex < dvarCount; ++dvarIndex )
  {
    Dvar_SetFromStringByNameFromSource(dvarNames[dvarIndex], dvarValues[dvarIndex], DVAR_SOURCE_EXTERNAL, 0);
    dvar = Dvar_FindVar(&(*dvarNames)[32 * dvarIndex]);
    Dvar_AddFlags(dvar, 1);
  }
}


void Com_GetConfigureDvarValues(int dvarCount, const char **text, char (*dvarValues)[32])
{
  int dvarIndex;
  parseInfo_t *token;

  for ( dvarIndex = 0; dvarIndex < dvarCount; ++dvarIndex )
  {
    token = Com_ParseOnLine(text);
    if ( !*text )
    {
      Com_Error(ERR_FATAL, "\x15""configure_mp.csv: unexpected end-of-file\n");
    }
    if ( !token->token[0] )
    {
      Com_Error(ERR_FATAL, "\x15""configure_mp.csv: missing entry in dvar value column %i\n", dvarIndex);
    }
    if ( strlen(token->token) > 31 )
    {
      Com_Error(ERR_FATAL, "\x15""configure_mp.csv: entry \'%s\' in dvar value column %i is longer than %\n", token->token, dvarIndex, 31);
    }
    if ( dvarValues )
    {
      Q_strncpyz(dvarValues[dvarIndex], token->token, 32);
    }
  }
  token = Com_ParseOnLine(text);
  if ( token->token[0] )
  {
    Com_Error(ERR_FATAL, "\x15""configure_mp.csv: extra dvar value column(s): value = %s\n", token->token);
  }
}


int Com_GetConfigureDvarNames(const char **text, char (*dvarNames)[32])
{
  int dvarCount;
  parseInfo_t *token;

  for ( dvarCount = 0; ; ++dvarCount )
  {
    token = Com_ParseOnLine(text);
    if ( !*text )
    {
      Com_Error(ERR_FATAL, "\x15""configure_mp.csv: unexpected end-of-file\n");
    }
    if ( !token->token[0] )
    {
      break;
    }
    if ( strlen(token->token) > 31 )
    {
      Com_Error(ERR_FATAL, "\x15""configure_mp.csv: dvar name \"%s\" longer than %i\n", token, 31);
    }
    if ( dvarCount >= 64 )
    {
      Com_Error(ERR_FATAL, "\x15""configure_mp.csv: more than %i dvars\n", 64);
    }
    Q_strncpyz(dvarNames[dvarCount], token->token, 32);
  }
  return dvarCount;
}


int Com_ConfigureChecksum(const char *csv, int filesize)
{
  int checksum;
  int i;

  checksum = 0;
  for ( i = 0; i < filesize; ++i )
  {
    checksum = csv[i] + 31337 * checksum;
  }
  return (checksum & 0xFFFFFFF) + 1;
}

bool Com_DoesGpuStringMatch(const char *find, const char *ref)
{
  int wildcardLen;
  char wildcardTemplate[1024];
  int findLen;

  wildcardTemplate[0] = '*';
  wildcardLen = 1;
  for ( findLen = 0; find[findLen]; ++findLen )
  {
    if ( !isspace(find[findLen]) )
    {
      wildcardTemplate[wildcardLen] = find[findLen];
      if ( ++wildcardLen == sizeof(wildcardTemplate) -1 )
      {
        Com_Error(ERR_FATAL, "\x15""configure_mp.csv: \"find\" string is too long\n");
      }
      continue;
    }
	assert(wildcardLen >= 1);

    if ( wildcardTemplate[wildcardLen -1] != ' ' )
    {
      wildcardTemplate[wildcardLen] = ' ';
      if ( ++wildcardLen == sizeof(wildcardTemplate) -1 )
      {
        Com_Error(ERR_FATAL, "\x15""configure_mp.csv: \"find\" string is too long\n");
      }
    }
  }
  if ( wildcardTemplate[wildcardLen -1] != '*' )
  {
    wildcardTemplate[wildcardLen++] = '*';
  }
  wildcardTemplate[wildcardLen] = 0;
  return Com_GpuStringCompare(wildcardTemplate, ref) == 0;
}


bool Com_SetRecommendedGpu(SysInfo *info, const char **text)
{
	char dvarValues[64][32];
	char dvarNames[64][32];
	int dvarCount;
	bool success;
	char *s0;

	s0 = (char *)Com_Parse(text);
	if ( Q_stricmp(s0, "gpu") )
	{
		Com_UngetToken();
		return false;
	}

    dvarCount = Com_GetConfigureDvarNames(text, dvarNames);
    success = 0;
    while ( 1 )
    {
      s0 = (char *)Com_Parse(text);
      if ( !*text )
      {
        break;
      }
      if ( *s0 && *s0 != '#' )
      {
        if ( success || !Com_DoesGpuStringMatch(s0, info->gpuDescription) )
        {
          Com_GetConfigureDvarValues(dvarCount, text, 0);
        }
        else
        {
          Com_Printf(CON_CHANNEL_SYSTEM, "configure_mp.csv: using GPU configuration \"%s\"\n", s0);
          Com_GetConfigureDvarValues(dvarCount, text, dvarValues);
          Com_SetConfigureDvars(dvarCount, dvarNames, dvarValues);
          success = 1;
        }
      }
      else
      {
        Com_SkipRestOfLine(text);
      }
    }
  return success;
}


bool Com_SetRecommendedCpu(int localClientNum, SysInfo *info, const char **text)
{
  char dvarValues[64][32];
  char dvarNames[64][32];
  int dvarCount;
  SysInfo cpPInfo;
  bool success;
  bool j;
  SysInfo parseInfo;
  char *s0;

  dvarCount = 0;
  cpPInfo.cpuGHz = -1.0;
  cpPInfo.sysMB = 0;
  success = 0;
  while ( 1 )
  {
    s0 = (char *)Com_Parse(text);
    if ( !text )
    {
      break;
    }
    if ( *s0 && *s0 != '#' )
    {
      if ( !Q_stricmp(s0, "gpu") )
      {
        Com_UngetToken();
        break;
      }
      if ( dvarCount )
      {
        parseInfo.cpuGHz = atof(s0);
        if ( parseInfo.cpuGHz < 0.0 )
        {
          Com_Error(ERR_FATAL, "\x15""configure_mp.csv: cpu ghz %g not allowed to be less than 0\n", parseInfo.cpuGHz);
        }
        s0 = (char *)Com_ParseOnLine(text);
        parseInfo.sysMB = atoi(s0);
        if ( parseInfo.sysMB < 128 )
        {
          Com_Error(ERR_FATAL, "\x15""configure_mp.csv: sys mb %i not allowed to be less than 128\n", parseInfo.sysMB);
        }
        j = false;
        if ( info->configureGHz >= parseInfo.cpuGHz && info->sysMB >= parseInfo.sysMB && (parseInfo.cpuGHz > cpPInfo.cpuGHz || (cpPInfo.cpuGHz == parseInfo.cpuGHz && cpPInfo.sysMB < parseInfo.sysMB)) )
        {
          j = true;
          memcpy(&cpPInfo, &parseInfo, sizeof(cpPInfo));
          success = 1;
        }
		char (*dvarValuesPtr)[32] = dvarValues;
		if(j == false)
		{
			dvarValuesPtr = NULL;
		}
        Com_GetConfigureDvarValues(dvarCount, text, dvarValuesPtr);
      }
      else
      {
        if ( Q_stricmp(s0, "cpu ghz") )
        {
          Com_Error(ERR_FATAL, "\x15""configure_mp.csv: \"cpu ghz\" should be the first column\n");
        }
        s0 = (char *)Com_ParseOnLine(text);
        if ( Q_stricmp(s0, "sys mb") )
        {
          Com_Error(ERR_FATAL, "\x15""configure_mp.csv: \"sys mb\" should be the second column\n");
        }
        dvarCount = Com_GetConfigureDvarNames(text, dvarNames);
      }
    }
    else
    {
      Com_SkipRestOfLine(text);
    }
  }
  if ( !success )
  {
    return false;
  }
  Com_Printf(CON_CHANNEL_SYSTEM, "configure_mp.csv: using CPU configuration %.0f GHz %i MB\n", cpPInfo.cpuGHz, cpPInfo.sysMB);
  Cbuf_AddText(localClientNum, "exec configure_mp.cfg");
  Cbuf_Execute(localClientNum, 0);
  Com_SetConfigureDvars(dvarCount, dvarNames, dvarValues);
  return true;
}



void Com_SetRecommended(int localClientNum, int restart)
{
  int filesize;
  SysInfo info;
  int checksum;
  char *csv;
  const char *text;

  Com_Printf(CON_CHANNEL_SYSTEM, "========= autoconfigure =========\n");
  Sys_GetInfo(&info);
  info.configureGHz = info.configureGHz * 1.02;
  if ( info.sysMB >= 128 )
  {
    info.sysMB += 8;
  }
  else
  {
    info.sysMB = 128;
  }
  filesize = FS_ReadFile("configure_mp.csv", (void **)&csv);
  if ( filesize < 0 )
  {
    Com_Error(ERR_FATAL, "EXE_ERR_NOT_FOUND\x15""configure_mp.csv");
  }
  text = csv;
  Com_BeginParseSession("configure_mp.csv");
  Com_SetCSV(1);
  if ( !Com_SetRecommendedCpu(localClientNum, &info, &text) )
  {
    Sys_GetInfo(&info);
    Com_Error(ERR_FATAL, "\x15""configure_mp.csv: \x14""EXE_ERR_COULDNT_CONFIGURE\x15 %.0f GHz %i MB\n", info.configureGHz, info.sysMB);
  }
  if ( !Com_SetRecommendedGpu(&info, &text) )
  {
    Com_Error(ERR_FATAL, "\x15""configure_mp.csv: \x14""EXE_ERR_COULDNT_CONFIGURE\x15 \"%s\"\n", info.gpuDescription);
  }
  Com_EndParseSession();
  checksum = Com_ConfigureChecksum(csv, filesize);
  FS_FreeFile(csv);
  Sys_ArchiveInfo(checksum);
  if ( restart )
  {
    if ( Dvar_AnyLatchedValues() )
    {
      Cbuf_AddText(localClientNum, "vid_restart\n");
    }
  }
}



void Sys_FastFileBlockedCallback()
{
	R_CheckLostDevice();
}



/*
========================================================================

Command line parsing

========================================================================
*/
#define		MAX_CONSOLE_LINES	32
int com_numConsoleLines;
char *com_consoleLines[MAX_CONSOLE_LINES];

/*
=================
Com_AddStartupCommands

Adds command line parameters as script statements
Commands are seperated by + signs

Returns qtrue if any late commands were added, which
will keep the demoloop from immediately starting
=================
*/
qboolean Com_AddStartupCommands( void ) {
	int		i;
	qboolean	added;
	char		buf[1024];
	added = qfalse;
	// quote every token, so args with semicolons can work
	for (i=0 ; i < com_numConsoleLines ; i++) {
    assert(com_consoleLines[i]);
		if ( !com_consoleLines[i] || !com_consoleLines[i][0] ) {
			continue;
		}

		// set commands already added with Com_StartupVariable
		if ( !Q_stricmpn( com_consoleLines[i], "set", 3 )) {
			continue;
		}

		added = qtrue;
		Com_sprintf(buf,sizeof(buf),"%s\n", com_consoleLines[i]);
    Cbuf_ExecuteBuffer(0, CL_ControllerIndexFromClientNum(0), buf);
    
	}

	return added;
}

/*
==================
Com_ParseCommandLine

Break it up into multiple console lines
==================
*/
void Com_ParseCommandLine( char *commandLine ) {

  com_consoleLines[0] = commandLine;
  com_numConsoleLines = 1;
	char* line;
	int numQuotes, i;

  while ( *commandLine ) {
  
  // look for a + seperating character
    // if commandLine came from a file, we might have real line seperators
    if ( (*commandLine == '+') || *commandLine == '\n'  || *commandLine == '\r' ) {
      if ( com_numConsoleLines == MAX_CONSOLE_LINES ) {
        return;
      }
      if(*(commandLine +1) != '\n')
      {
        com_consoleLines[com_numConsoleLines] = commandLine + 1;
        com_numConsoleLines = (com_numConsoleLines)+1;
      }
          *commandLine = 0;
    }
    commandLine++;
  }
	
	for (i = 0; i < com_numConsoleLines; i++)
	{
		line = com_consoleLines[i];
		/* Remove trailling spaces and / or bad quotes */
		while ( (*line == ' ' || *line == '\"') && *line != '\0') {
			line++;
		}
		
		memmove(com_consoleLines[i], line, strlen(line) +1);

		numQuotes = 0;

		/* Now verify quotes */
		while (*line)
		{

			while (*line != '\"' && *line != '\0')
			{
				line ++;
			}
			if(*line == '\"' && *(line -1) != ' ')
				break;
			
			if(*line == '\"')
				numQuotes++;

			if(*line != '\0')
			{
				line ++;
			}

			while (*line != '\"' && *line != '\0')
			{
				line ++;
			}
			if(*line == '\"' && *(line +1) != ' ' && *(line +1) != '\0'  )
				break;
			
			if(*line == '\"')
				numQuotes++;

			if(*line != '\0')
			{
				line ++;
			}
		}
		
		/* if we have bad quotes or an odd number of quotes we replace them all with ' ' */
		if(*line != '\0' || numQuotes & 1)
		{
			line = com_consoleLines[i];
			while (*line != '\0')
			{
				if(*line == '\"')
				{
					*line = ' ';
					
				}
				line++;
			}
		}
		
	}
}

/*
===============
Com_StartupVariable

Searches for command line parameters that are set commands.
If match is not NULL, only that cvar will be looked for.
That is necessary because cddir and basedir need to be set
before the filesystem is started, but all other sets should
be after execing the config and default.
===============
*/
void Com_StartupVariable( const char *match ) {
	int		i;
	for (i=0 ; i < com_numConsoleLines ; i++) {
		Cmd_TokenizeString( com_consoleLines[i] );

		if(!match || !strcmp(Cmd_Argv(1), match))
		{
			if ( !strcmp( Cmd_Argv(0), "set" )){
				Dvar_Set_f();
				Cmd_EndTokenizedString();
				continue;
			}else if( !strcmp( Cmd_Argv(0), "seta" ) ) {
				Dvar_SetA_f();
			}
		}
		Cmd_EndTokenizedString();
	}
}

static bool com_safemode;

void Com_ForceSafeMode(void)
{
  com_safemode = 1;
}

/*
===================
Com_SafeMode

Check for "safe" on the command line, which will
skip loading of wolfconfig.cfg
===================
*/
bool Com_SafeMode( void ) {

  for ( int i = 0 ; i < com_numConsoleLines ; i++ ) {
		Cmd_TokenizeString( com_consoleLines[i] );
		if ( !Q_stricmp( Cmd_Argv( 0 ), "safe" ) || !Q_stricmp( Cmd_Argv( 0 ), "dvar_restart" ) ) {
			com_consoleLines[i][0] = 0;
			Cmd_EndTokenizedString( );
			return true;
		}
		Cmd_EndTokenizedString( );
	}
	return com_safemode;
}

void Com_WriteConfiguration(int localClientNum)
{
  char configFile[MAX_OSPATH];

  if ( !Com_IsFullyInitialized() || !(dvar_modifiedFlags & CVAR_ARCHIVE) )
  {
	  return;
  }

  dvar_modifiedFlags &= ~CVAR_ARCHIVE;
  if(!Com_HasPlayerProfile())
  {
    return;
  }
  Com_BuildPlayerProfilePath(configFile, sizeof(configFile), "config_mp.cfg", NULL);
  Com_WriteConfigToFile(localClientNum, configFile);
}


void Com_WriteConfig_f()
{
  char filename[MAX_OSPATH];

  if ( Cmd_Argc() == 2 )
  {
    Q_strncpyz(filename, Cmd_Argv(1), sizeof(filename));
    Com_DefaultExtension(filename, sizeof(filename), ".cfg");
    Com_Printf(CON_CHANNEL_DONT_FILTER, "Writing %s.\n", filename);
    Com_WriteConfigToFile(0, filename);
  }
  else
  {
    Com_Printf(CON_CHANNEL_DONT_FILTER, "Usage: writeconfig <filename>\n");
  }
}

void Com_SetDedicatedMode()
{
	static const char* g_dedicatedEnumNames[] = { "listen server", "dedicated LAN server", "dedicated internet server", NULL };

	if ( com_dedicated->flags & CVAR_ROM || com_dedicated->latched.integer == com_dedicated->current.integer)
	{
		return;
	}

  com_dedicated = Dvar_RegisterEnum("dedicated", g_dedicatedEnumNames, 0, CVAR_LATCH, "True if this is a dedicated server");

  if ( com_dedicated->current.integer )
  {
    Dvar_RegisterEnum("dedicated", g_dedicatedEnumNames, 0, CVAR_ROM, "True if this is a dedicated server");
  }
  Dvar_ClearModified( com_dedicated );
  CL_Shutdown(0);
	//CL_ShutdownSteamApi();
	//CL_DiscordShutdown();
  CL_ShutdownRef();
  CL_InitDedicated();
  SV_AddDedicatedCommands();
}

void Com_Statmon()
{
  int timePrevFrame;
  static int timeClientFrame;

  if ( com_statmon->current.enabled )
  {
    if ( com_fileAccessed )
    {
      StatMon_Warning(1, 3000, "code_warning_file");
      com_fileAccessed = 0;
    }
    timePrevFrame = timeClientFrame;
    timeClientFrame = Sys_Milliseconds();
    if ( com_statmon->current.enabled )
    {
      if ( timeClientFrame - timePrevFrame > 33 )
      {
        if ( timePrevFrame )
        {
          StatMon_Warning(0, 3000, "code_warning_fps");
        }
      }
      /*
      if ( sv.serverFrameTimeMax > 50 )
      {
        StatMon_Warning(6, 3000, "code_warning_serverfps");
      }
      */
    }
  }
}

void Com_AssetLoadUI()
{
  XZoneInfo zone;

  zone.name = "ui_mp";
  zone.allocFlags = 2;
  zone.freeFlags = 2;
  DB_LoadXAssets(&zone, 1u, 0);
  UI_SetMap("", "");
  CL_StartHunkUsers();
}

void Com_StartHunkUsers()
{
  TRY(Exception_type::SystemException)
  {
    Com_AssetLoadUI();
    UI_SetActiveMenu(0, UI_GetMenuScreen());
    IN_Frame();
    Com_EventLoop();
  }
  CATCH
  {
    Sys_Error("Error during initialization:\n%s\n", com_errorMessage);
  }
  ENDTRY
}

void Com_PrintStackTrace()
{
  char g_stackTrace[32768];

  Assert_DoStackTrace(g_stackTrace, 1, 2, nullptr);
  Com_Printf(CON_CHANNEL_SYSTEM, "STACKBEGIN -------------------------------------------------------------------\n");
  Com_Printf(CON_CHANNEL_SYSTEM, g_stackTrace);
  Com_Printf(CON_CHANNEL_SYSTEM, "STACKEND ---------------------------------------------------------------------\n");
}



void Com_Error(errorParm_t code, const char *fmt, ...)
{
  va_list va;
/*
  if ( (code == ERR_DROP || code == ERR_SCRIPT_DROP) && G_ExitAfterToolComplete() )
  {
    va_start(va, fmt);
    _vsnprintf(com_errorMessage, sizeof(com_errorMessage), fmt, va);
    va_end(va);
    com_errorMessage[sizeof(com_errorMessage) -1] = 0;
    
    printf(com_errorMessage);
    Com_Printf(CON_CHANNEL_SYSTEM, com_errorMessage);
    Com_PrintStackTrace();
    return;
  }
*/
  Sys_EnterCriticalSection(CRITSECT_COM_ERROR);
  if ( code != ERR_DISCONNECT )
  {
    //Monkey_GrabComPrints(1);
  }
  Assert_ResetAddressInfo();
  if ( code <= ERR_DROP )
  {
    Com_PrintStackTrace();
  }
  /*
  if ( !Demo_IsIdle() && code != ERR_SCRIPT )
  {
    Demo_End(1);
  }
  */
  if ( com_errorEntered )
  {
    Sys_Error("recursive error after: %s", com_errorMessage);
  }
  com_errorEntered = qtrue;

  va_start(va, fmt);
  _vsnprintf(com_errorMessage, sizeof(com_errorMessage), fmt, va);
  va_end(va);
  com_errorMessage[sizeof(com_errorMessage) -1] = 0;
/*
  if ( code != ERR_DISCONNECT && Monkey_IsRunning() )
  {
    Com_Printf(CON_CHANNEL_SYSTEM, com_errorMessage);
    Monkey_Error(0);
    exit(-1);
  }
*/  
  if ( code == ERR_SCRIPT )
  {
    StatMon_Warning(10, 3000, "code_warning_scripterrors");
  }

  if ( code == ERR_SCRIPT || code == ERR_LOCALIZATION )
  {
    if ( !com_fixedConsolePosition )
    {
      com_fixedConsolePosition = qtrue;
      CL_ConsoleFixPosition();
    }
    if ( cls.uiStarted )
    {
      Com_SetErrorMessage(com_errorMessage);
      //_InterlockedExchange(&cls.scriptError, 1);
      if(Sys_IsMainThread())
      {
        UI_SetActiveMenu(0, UIMENU_MAIN);
      }
    }else{
      code = ERR_DROP;
      errorcode = code;
      Sys_LeaveCriticalSection(CRITSECT_COM_ERROR);
      THROW(Exception_type::SystemException);
    }
    com_errorEntered = qfalse;
    Sys_LeaveCriticalSection(CRITSECT_COM_ERROR);
    return;
  }

  if ( code == ERR_SCRIPT_DROP || code == ERR_MAPLOADERRORSUMMARY)
  {
    com_fixedConsolePosition = qtrue;
    CL_ConsoleFixPosition();
    code = ERR_DROP;
  }
  else
  { //default
    com_fixedConsolePosition = qfalse;
  }
  if(code == ERR_MAPLOADERRORSUMMARY)
  {
    if ( cls.uiStarted && Sys_IsMainThread() )
    {
      //UI_SetActiveMenu(0, UIMENU_NONE);
      Com_SetErrorMessage(com_errorMessage);
      UI_SetActiveMenu(0, UIMENU_PREGAME);
      com_errorEntered = qfalse;
      Sys_LeaveCriticalSection(CRITSECT_COM_ERROR);
      return;
    }else{
      if(com_dedicated->current.integer)
      {
        Sys_Print("\n==========================\n");
        Sys_Print(com_errorMessage);
        Sys_Print("\n==========================\n");
        com_errorEntered = qfalse;
        Sys_LeaveCriticalSection(CRITSECT_COM_ERROR);
        return;
      }
    }
  }
  errorcode = code;
  Sys_LeaveCriticalSection(CRITSECT_COM_ERROR);
  //Com_Printf(CON_CHANNEL_SYSTEM, "\n====================================================\n");
  //Com_Printf(CON_CHANNEL_SYSTEM, "Com_ERROR: %s", com_errorMessage);
  //Com_Printf(CON_CHANNEL_SYSTEM, "\n====================================================\n\n");
  //R_ReleaseDXDeviceOwnership();
  /*
  if ( G_ExitOnComError(code) )
  {
    printf("Fatal Error: %s\n", com_errorMessage);
    Sys_NormalExit();
    v2 = __iob_func();
    fflush(v2 + 1);
    ExitProcess(-1);
  }*/
  //TaskManager2_ComErrorCleanup();
  //GlassCl_WaitUpdate();
  THROW(Exception_type::SystemException);
}

