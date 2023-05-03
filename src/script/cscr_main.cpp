#include <q_shared.h>
#include <common/qcommon_mem.h>
#include "cscr_vm.h"
#include "cscr_main.h"
#include "cscr_stringlist.h"
#include "cscr_variable.h"
#include "cscr_animtree.h"
#include "cscr_parser.h"
#include "cscr_parsertree.h"
#include "cscr_compiler.h"
#include "cscr_debugger.h"


cvar_t* scrShowVarUsage;
cvar_t* scrShowStrUsage;

int refCountHigh;
int includeLevelDeep;
int loadFileId;

void Scr_EndLoadAnimTrees( );

bool Scr_IsInOpcodeMemory(const char *pos)
{
    assert(gScrVarPub.programBuffer);
    assert(pos);

  if(pos - gScrVarPub.programBuffer < (signed)gScrCompilePub.programLen)
  {
      return true;
  }
  return false;
}

int Scr_GetFunctionHandle(const char *filename, const char *name)
{
  unsigned int name2;
  VariableValue pos;
  unsigned int str;
  int codepos;
  unsigned int posId;
  unsigned int filePosId;
  unsigned int id;

  assert(gScrCompilePub.scriptsPos);
  assert(strlen( filename ) < MAX_QPATH);

  name2 = Scr_CreateCanonicalFilename(filename);
  filePosId = FindVariable(gScrCompilePub.scriptsPos, name2);
  SL_RemoveRefToString(name2);
  if ( !filePosId )
  {
    return 0;
  }
  id = FindObject(filePosId);

  assert(id != 0);

  str = SL_FindLowercaseString(name);
  if ( !str )
  {
    return 0;
  }
  posId = FindVariable(id, str);
  if ( !posId )
  {
    return 0;
  }
//CoD4...
  if(GetValueType(posId) != VAR_POINTER)
  {
      return 0;
  }
  posId = FindVariable(FindObject(posId), 1);

//End cod4 stuff

  pos = Scr_EvalVariable(posId);
  assert(pos.type == VAR_CODEPOS || pos.type == VAR_DEVELOPER_CODEPOS);

  if ( !Scr_IsInOpcodeMemory(pos.u.codePosValue) )
  {
    return 0;
  }
  codepos = pos.u.codePosValue - gScrVarPub.programBuffer;
  assert ( pos.u.codePosValue > gScrVarPub.programBuffer);
  return codepos;
}


void Scr_EndLoadScripts( )
{

  if ( scrShowVarUsage->current.enabled )
  {
    Com_Printf(CON_CHANNEL_SCRIPT, "---\nHigh ref count : %i\nDeepest include level %i\n", refCountHigh, includeLevelDeep);
  }

//  Scr_EndLoadEvaluate( );
  SL_ShutdownSystem(2u);
#ifdef BLACKOPS
  if ( com_sv_running->boolean )
  {
    Scr_InitDebugger( );
  }
#endif
  gScrCompilePub.script_loading = 0;

  assert(gScrCompilePub.loadedscripts);
  ClearObject(gScrCompilePub.loadedscripts);

  if ( gScrVarDebugPub )
  {
    --gScrVarDebugPub->extRefCount[gScrCompilePub.loadedscripts];
  }

  RemoveRefToObject(gScrCompilePub.loadedscripts);
  gScrCompilePub.loadedscripts = 0;

  assert(gScrCompilePub.scriptsPos);
  ClearObject(gScrCompilePub.scriptsPos);


  if ( gScrVarDebugPub )
  {
    --gScrVarDebugPub->extRefCount[gScrCompilePub.scriptsPos];
  }

  RemoveRefToObject(gScrCompilePub.scriptsPos);
  gScrCompilePub.scriptsPos = 0;
/*
  assert(gScrCompilePub.scriptsCount);
  ClearObject(gScrCompilePub.scriptsCount);

  if ( gScrVarDebugPub )
  {
    --gScrVarDebugPub->extRefCount[gScrCompilePub.scriptsCount];
  }

  RemoveRefToObject(gScrCompilePub.scriptsCount);
  gScrCompilePub.scriptsCount = 0;
*/
  assert(gScrCompilePub.builtinFunc);
  ClearObject(gScrCompilePub.builtinFunc);

  if ( gScrVarDebugPub )
  {
    --gScrVarDebugPub->extRefCount[gScrCompilePub.builtinFunc];
  }

  RemoveRefToObject(gScrCompilePub.builtinFunc);
  gScrCompilePub.builtinFunc = 0;

  assert(gScrCompilePub.builtinMeth);
  ClearObject(gScrCompilePub.builtinMeth);

  if ( gScrVarDebugPub )
  {
    --gScrVarDebugPub->extRefCount[gScrCompilePub.builtinMeth];
  }

  RemoveRefToObject(gScrCompilePub.builtinMeth);
  gScrCompilePub.builtinMeth = 0;
}


void Scr_FreeScripts(unsigned char sys)
{
  assert(sys == SCR_SYS_GAME);
//  Hunk_CheckTempMemoryClear();
  if ( gScrCompilePub.script_loading )
  {
    gScrCompilePub.script_loading = 0;
    Scr_EndLoadScripts();
  }
  if ( gScrAnimPub.animtree_loading )
  {
    gScrAnimPub.animtree_loading = 0;
    Scr_EndLoadAnimTrees();
  }
/*
  Scr_ShutdownDebugger();
  Scr_ShutdownDebuggerMain();
  Scr_ShutdownEvaluate();
*/
  SL_ShutdownSystem(1u);
  Scr_ShutdownOpcodeLookup( );
  if ( gScrVarPub.programHunkUser )
  {
    Hunk_UserDestroy(gScrVarPub.programHunkUser);
    gScrVarPub.programHunkUser = 0;
  }
  gScrVarPub.programBuffer = 0;
  gScrCompilePub.programLen = 0;
  gScrVarPub.endScriptBuffer = 0;
  gScrVarPub.checksum = 0;
  gScrAnimPub.xanim_num[0] = 0;
  gScrAnimPub.xanim_num[1] = 0;
}



unsigned int Scr_LoadScriptInternal(const char *filename, PrecacheEntry *entries, int entriesCount)
{
  unsigned int scriptPosVar;
  char extFilename[64];
//  unsigned int fileCountId;
  unsigned int filePosPtr;
  char *sourceBuffer;
  const char *oldFilename;
  unsigned int name;
  unsigned int oldAnimTreeNames;
  const char *oldSourceBuf;
  unsigned int scriptId;
  unsigned int filePosId;
  int oldStrCount;
  const char *formatExtString;
  sval_u parseData;

  static int scrShowStrUsageStringCount;
  static int oldNum;
  oldStrCount = 0;

  assert(gScrCompilePub.script_loading);
  assert(strlen( filename ) < MAX_QPATH);

  Hunk_CheckTempMemoryHighClear();
  
  name = Scr_CreateCanonicalFilename(filename);
  if ( FindVariable(gScrCompilePub.loadedscripts, name) )
  {
    SL_RemoveRefToString(name);
    filePosPtr = FindVariable(gScrCompilePub.scriptsPos, name);
    if ( filePosPtr )
    {
      return FindObject(filePosPtr);
    }
    return 0;
  }

  scriptId = GetNewVariable(gScrCompilePub.loadedscripts, name);
  SL_RemoveRefToString(name);
  formatExtString = "%s.gsc";
  
/*
  if ( inst == SCRIPTINSTANCE_CLIENT && (!I_strncmp(filename, "clientscripts", 13) || !I_strncmp(filename, "character/clientscripts", 23)) )
  {
    formatExtString = "%s.csc";
  }
*/
  Com_sprintf(extFilename, sizeof(extFilename), formatExtString, SL_ConvertToString(name));
  oldSourceBuf = gScrParserPub.sourceBuf;
  if ( scrShowStrUsage->current.enabled )
  {
    oldStrCount = gScrStringGlob.stringsUsed[++gScrStringGlob.indentLevel];
  }
  //ProfLoad_Begin("Scr_AddSourceBuffer");
  sourceBuffer = Scr_AddSourceBuffer(SL_ConvertToString(name), extFilename, (const char*)TempMalloc(0), 1);
  //ProfLoad_End();
  if ( !sourceBuffer )
  {
    return 0;
  }
  loadFileId = loadFileId + 1;
  if(loadFileId > includeLevelDeep )
  {
    includeLevelDeep = loadFileId;
  }
  if ( scrShowVarUsage->current.enabled )
  {
    Com_Printf(CON_CHANNEL_SCRIPT, "Entering file %s (%i)\n", filename, loadFileId);
  }
  oldAnimTreeNames = gScrAnimPub.animTreeNames;
  gScrAnimPub.animTreeNames = 0;
  gScrCompilePub.far_function_count = 0;
  Scr_InitAllocNode( );
  oldFilename = gScrParserPub.scriptfilename;
  gScrParserPub.scriptfilename = extFilename;
  gScrCompilePub.in_ptr = "+";
  gScrCompilePub.parseBuf = sourceBuffer;
  ScriptParse(&parseData, 0);
  scriptPosVar = GetVariable(gScrCompilePub.scriptsPos, name);
  filePosId = GetObject(scriptPosVar);
  //fileCountId = GetObject(GetVariable(gScrCompilePub.scriptsCount, name));
  //ProfLoad_Begin("ScriptCompile");
  ScriptCompile(parseData, filePosId, /*fileCountId,*/ scriptId, entries, entriesCount);
  //ProfLoad_End();
  if ( scrShowStrUsage->current.enabled )
  {
    Com_Printf(CON_CHANNEL_DONT_FILTER, "---Script File (%i) : %s -> %i\n", gScrStringGlob.indentLevel, filename,
      gScrStringGlob.stringsUsed[gScrStringGlob.indentLevel] - oldStrCount);
    scrShowStrUsageStringCount += gScrStringGlob.stringsUsed[gScrStringGlob.indentLevel--] - oldStrCount;
    if ( !gScrStringGlob.indentLevel )
    {
      Com_Printf(CON_CHANNEL_DONT_FILTER, "******Current compilation string total: %i\n", scrShowStrUsageStringCount);
    }
  }

  if ( gScrVarPub.numScriptValues > refCountHigh )
  {
    refCountHigh = gScrVarPub.numScriptValues;
  }
  if ( scrShowVarUsage->current.enabled )
  {
    Com_Printf(CON_CHANNEL_SCRIPT, "---\nScript File (%i) : %s\nCur var useage %i\nChange %i\n---\n", loadFileId,
      filename, gScrVarPub.numScriptValues, gScrVarPub.numScriptValues - oldNum);
  }
  oldNum = gScrVarPub.numScriptValues;
  gScrParserPub.scriptfilename = oldFilename;
  gScrParserPub.sourceBuf = oldSourceBuf;
  gScrAnimPub.animTreeNames = oldAnimTreeNames;
  Hunk_CheckTempMemoryHighClear();
  if ( scrShowVarUsage->current.enabled )
  {
    Com_Printf(CON_CHANNEL_ANIM, "Leaving file %s (%i)\n", filename, loadFileId);
  }
  --loadFileId;
  return filePosId;

}

unsigned int Scr_LoadScript(const char *filename)
{
  PrecacheEntry entries;

  return Scr_LoadScriptInternal(filename, &entries, 0);
}

void SL_BeginLoadScripts( )
{
  memset((char *)gScrCompilePub.canonicalStrings, 0, sizeof(gScrCompilePub.canonicalStrings));
  gScrVarPub.canonicalStrCount = 0;
}

void Scr_BeginLoadScripts(int user)
{
  //gScrVarPub.varUsagePos = "<script compile variable>";
  loadFileId = 0;
  refCountHigh = 0;
  assert(!gScrCompilePub.script_loading);

  gScrCompilePub.script_loading = 1;
  Scr_InitOpcodeLookup( );
  Scr_InitDebuggerMain( );

  assert(!gScrCompilePub.loadedscripts);

  gScrCompilePub.loadedscripts = Scr_AllocArray( );
  if ( gScrVarDebugPub )
  {
    ++gScrVarDebugPub->extRefCount[gScrCompilePub.loadedscripts];
  }
  gScrVmPub.showError = gScrVarPub.developer;
  assert(!gScrCompilePub.scriptsPos);

  gScrCompilePub.scriptsPos = Scr_AllocArray( );
  if ( gScrVarDebugPub )
  {
    ++gScrVarDebugPub->extRefCount[gScrCompilePub.scriptsPos];
  }
/*
  assert(!gScrCompilePub.scriptsCount);

  gScrCompilePub.scriptsCount = Scr_AllocArray( );
  if ( gScrVarDebugPub )
  {
    ++gScrVarDebugPub->extRefCount[gScrCompilePub.scriptsCount];
  }
*/
  assert(!gScrCompilePub.builtinFunc);

  gScrCompilePub.builtinFunc = Scr_AllocArray( );
  if ( gScrVarDebugPub )
  {
    ++gScrVarDebugPub->extRefCount[gScrCompilePub.builtinFunc];
  }
  assert(!gScrCompilePub.builtinMeth);

  gScrCompilePub.builtinMeth = Scr_AllocArray( );
  if ( gScrVarDebugPub )
  {
    ++gScrVarDebugPub->extRefCount[gScrCompilePub.builtinMeth];
  }
  //gScrVarPub.programHunkUser = Hunk_UserCreate(0x100000, HU_SCHEME_DEFAULT, 4u, 0, "Scr_BeginLoadScripts", 7);
  gScrVarPub.programHunkUser = Hunk_UserCreate(0x100000, "Scr_BeginLoadScripts", 1, 0, 7);

  TempMemoryReset(gScrVarPub.programHunkUser);
  gScrVarPub.programBuffer = (const char*)TempMalloc(0);

  assert(!((int)gScrVarPub.programBuffer & 31));

  gScrCompilePub.programLen = 0;
  gScrVarPub.endScriptBuffer = 0;
  SL_BeginLoadScripts( );
  //Scr_InitEvaluate( );
  gScrVarPub.fieldBuffer = 0;
  gScrCompilePub.value_count = 0;
  Scr_ClearErrorMessage( );
  gScrCompilePub.func_table_size = 0;
  gScrAnimPub.animTreeNames = 0;
  Scr_SetLoadedImpureScript(0);
  Scr_BeginLoadAnimTrees(user);
}
