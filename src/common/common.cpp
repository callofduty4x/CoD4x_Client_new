#include "qcommon.h"
#include "sys_thread.h"
#include <gfx_d3d/r_shared.h>
#include <client/client_shared.h>
#include <script/scr_shared.h>
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


const char * Com_GetBuildDisplayName()
{
	return "Call of Duty 4 v1.7";
}


void Com_SetErrorEntered()
{

	com_errorEntered = qtrue;

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


