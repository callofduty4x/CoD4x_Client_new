#include <q_shared.h>
#include "scr_local.h"
#include "scr_shared.h"
#include "cscr_stringlist.h"
#include "cscr_variable.h"
#include "cscr_vm.h"
#include "cscr_animtree.h"
#include "cscr_debugger.h"
#include "cscr_main.h"
#include "cscr_compiler.h"
#include "cscr_memorytree.h"
#include <common/qcommon.h>
#include <common/sys_shared.h>
#include <game/server_game_shared.h>
#include <setjmp.h>


int g_script_error_level;
jmp_buf g_script_error[33];
char error_message[1024];
cvar_t* logScriptTimes;
cvar_t* scrVmEnableScripts;
int gScrExecuteTime;
function_stack_t gFs;
scrVmPub_t gScrVmPub;
unsigned int VM_Execute();
int gThreadCount;

#define MAX_VM_STACK_DEPTH 32

bool Scr_IgnoreInfiniteLoopError()
{
  return false;
}

VariableValue GetEntityFieldValue(unsigned int classnum, int entnum, int offset)
{
  VariableValue result;

  assert ( !gScrVmPub.inparamcount );
  assert(!gScrVmPub.outparamcount);

  gScrVmPub.top = gScrVmGlob.eval_stack - 1;
  gScrVmGlob.eval_stack[0].type = 0;
  Scr_GetObjectField(classnum, entnum, offset);

  assert(!gScrVmPub.inparamcount || gScrVmPub.inparamcount == 1);
  assert(!gScrVmPub.outparamcount);
  assert(gScrVmPub.top - gScrVmPub.inparamcount == gScrVmGlob.eval_stack - 1);

  gScrVmPub.inparamcount = 0;

  result.u.intValue = gScrVmGlob.eval_stack[0].u.intValue;
  result.type = gScrVmGlob.eval_stack[0].type;

  return result;
}

const char * Scr_GetString(unsigned int index)
{
  unsigned int constString;

  constString = Scr_GetConstString(index);
  return SL_ConvertToString(constString);
}


void Scr_UpdateDebugger()
{
    
}


void Scr_ErrorInternal( )
{   
  assert(gScrVarPub.error_message != NULL);

  if ( !gScrVarPub.evaluate && !gScrCompilePub.script_loading )
  {
    if ( gScrVmPub.function_count || gScrVmPub.debugCode )
    {
        Com_Printf(CON_CHANNEL_LOGFILEONLY, "throwing script exception: %s\n", gScrVarPub.error_message);
        Scr_ErrorJumpOut();
    }
    Sys_Error("%s", gScrVarPub.error_message);
  }
  if ( gScrVmPub.terminal_error )
  {
    Sys_Error("%s", gScrVarPub.error_message);
  }
}

void Scr_SetErrorMessage(const char *error)
{
  if ( !gScrVarPub.error_message )
  {
    Q_strncpyz(error_message, error, sizeof(error_message));
    gScrVarPub.error_message = error_message;
  }
}

void Scr_Error(const char *error, bool force_terminal)
{
  Scr_SetErrorMessage(error);
  gScrVmPub.terminal_error = false;
  Scr_ErrorInternal( );
}

void Scr_Error(const char *error)
{
  Scr_Error(error, false);
}

void Scr_Errorf(const char *fmt, ...)
{
  char buf[MAX_STRING_CHARS];

  va_list argptr;
  va_start(argptr,fmt);
  Q_vsnprintf(buf, sizeof(buf), fmt, argptr);
  va_end (argptr);

  Scr_Error(buf);
}

void Scr_TerminalError(const char *error)
{

  Scr_DumpScriptThreads( );
  Scr_DumpScriptVariablesDefault( );
  gScrVmPub.terminal_error = true;
  Scr_SetErrorMessage(error);

  Scr_ErrorInternal( );
}


void Scr_ClearOutParams()
{
  while ( gScrVmPub.outparamcount )
  {
    RemoveRefToValue(gScrVmPub.top->type, gScrVmPub.top->u);
    --gScrVmPub.top;
    --gScrVmPub.outparamcount;
  }
}

void IncInParam()
{

  assert(((gScrVmPub.top >= gScrVmGlob.eval_stack - 1) && (gScrVmPub.top <= gScrVmGlob.eval_stack)) || ((gScrVmPub.top >= gScrVmPub.stack) && (gScrVmPub.top <= gScrVmPub.maxstack)));

  Scr_ClearOutParams( );

  if ( gScrVmPub.top == gScrVmPub.maxstack )
  {
    Sys_Error("Internal script stack overflow");
  }
  ++gScrVmPub.top;
  ++gScrVmPub.inparamcount;
  assert(((gScrVmPub.top >= gScrVmGlob.eval_stack) && (gScrVmPub.top <= gScrVmGlob.eval_stack + 1)) || ((gScrVmPub.top >= gScrVmPub.stack) && (gScrVmPub.top <= gScrVmPub.maxstack)));

}


void Scr_AddString(const char *value)
{
  assert(value != NULL);

  IncInParam( );
  gScrVmPub.top->type = VAR_STRING;
  gScrVmPub.top->u.stringValue = SL_GetString(value, 0);
}

void Scr_AddInt(int value)
{
  IncInParam( );
  gScrVmPub.top->type = VAR_INTEGER;
  gScrVmPub.top->u.intValue = value;
}

void Scr_AddBool(bool value)
{
  IncInParam( );
  gScrVmPub.top->type = VAR_INTEGER;
  gScrVmPub.top->u.intValue = value;
}

void Scr_AddFloat(float value)
{
  IncInParam();
  gScrVmPub.top->type = VAR_FLOAT;
  gScrVmPub.top->u.floatValue = value;
}

void Scr_AddAnim(struct scr_anim_s value)
{
  IncInParam();
  gScrVmPub.top->type = VAR_ANIMATION;
  gScrVmPub.top->u.codePosValue = value.linkPointer;
}

void Scr_AddUndefined( )
{
  IncInParam();
  gScrVmPub.top->type = VAR_UNDEFINED;
}

void Scr_AddObject(unsigned int id)
{
  assert(id != 0);
  assert(Scr_GetObjectType( id ) != VAR_THREAD);
  assert(Scr_GetObjectType( id ) != VAR_NOTIFY_THREAD);
  assert(Scr_GetObjectType( id ) != VAR_TIME_THREAD);
  assert(Scr_GetObjectType( id ) != VAR_CHILD_THREAD);
  assert(Scr_GetObjectType( id ) != VAR_DEAD_THREAD);

  IncInParam();
  gScrVmPub.top->type = VAR_POINTER;
  gScrVmPub.top->u.intValue = id;
  AddRefToObject(id);
}

void Scr_AddEntityNum(int entnum, unsigned int classnum)
{
  unsigned int entId;
  const char *varUsagePos;

  varUsagePos = gScrVarPub.varUsagePos;
  if ( !gScrVarPub.varUsagePos )
  {
    gScrVarPub.varUsagePos = "<script entity variable>";
  }
  entId = Scr_GetEntityId(entnum, classnum);
  Scr_AddObject(entId);
  gScrVarPub.varUsagePos = varUsagePos;
}

void Scr_AddStruct( )
{
  unsigned int id;

  id = AllocObject();
  Scr_AddObject(id );
  RemoveRefToObject(id);
}

void Scr_AddIString(const char *value)
{
  assert(value != NULL);

  IncInParam( );
  gScrVmPub.top->type = VAR_ISTRING;
  gScrVmPub.top->u.stringValue = SL_GetString(value, 0);
}

void Scr_AddConstString(unsigned int value)
{
  assert(value != 0);

  IncInParam( );
  gScrVmPub.top->type = VAR_STRING;
  gScrVmPub.top->u.stringValue = value;
  SL_AddRefToString(value);
}

void Scr_AddVector(const float *value)
{
  IncInParam();
  gScrVmPub.top->type = VAR_VECTOR;
  gScrVmPub.top->u.vectorValue = Scr_AllocVector(value);
}

void Scr_MakeArray( )
{
  IncInParam( );
  gScrVmPub.top->type = VAR_POINTER;
  gScrVmPub.top->u.intValue = Scr_AllocArray( );
}

void Scr_AddArray( )
{
  unsigned int arraySize;
  unsigned int id;
  const char *varUsagePos;

  varUsagePos = gScrVarPub.varUsagePos;
  if ( !gScrVarPub.varUsagePos )
  {
    gScrVarPub.varUsagePos = "<script array variable>";
  }

  assert(gScrVmPub.inparamcount);

  --gScrVmPub.top;
  --gScrVmPub.inparamcount;

  assert(gScrVmPub.top->type == VAR_POINTER);

  arraySize = GetArraySize( gScrVmPub.top->u.stringValue);
  id = GetNewArrayVariable( gScrVmPub.top->u.stringValue, arraySize);
  SetNewVariableValue( id, gScrVmPub.top + 1);
  gScrVarPub.varUsagePos = varUsagePos;
}

void Scr_AddArrayStringIndexed(unsigned int stringValue)
{
  unsigned int id;

  assert(gScrVmPub.inparamcount != 0);

  --gScrVmPub.top;
  --gScrVmPub.inparamcount;
  assert(gScrVmPub.top->type == VAR_POINTER);

  id = GetNewVariable( gScrVmPub.top->u.stringValue, stringValue);
  SetNewVariableValue( id, gScrVmPub.top + 1);
}


unsigned int Scr_GetConstStringIncludeNull(unsigned int index)
{
  if ( index >= gScrVmPub.outparamcount || gScrVmPub.top[-index].type )
  {
    return Scr_GetConstString(index);
  }
  return 0;
}

//Use with Scr_Exce(Ent)Thread
int Scr_GetFunc(unsigned int paramnum)
{
    VariableValue *var;

    if (paramnum >= gScrVmPub.outparamcount)
    {
        Scr_Error(va("parameter %d does not exist", paramnum + 1));
        return -1;
    }

    var = &gScrVmPub.top[-paramnum];
    if (var->type == VAR_FUNCTION)
    {
        int vmRomAddress = var->u.codePosValue - gScrVarPub.programBuffer;
        return vmRomAddress;
    }
    gScrVarPub.error_index = paramnum + 1;
    Scr_Error(va("type %s is not an function", var_typename[var->type]));
    return -1;
}


int Scr_GetInt(unsigned int paramnum)
{
    VariableValue *var;

    if (paramnum >= gScrVmPub.outparamcount)
    {
        Scr_Error(va("parameter %d does not exist", paramnum + 1));
        return 0;
    }

    var = &gScrVmPub.top[-paramnum];
    if (var->type == 6)
    {
        return var->u.intValue;
    }
    gScrVarPub.error_index = paramnum + 1;
    Scr_Error(va("type %s is not an int", var_typename[var->type]));
    return 0;
}

unsigned int Scr_GetObject(unsigned int paramnum)
{
    VariableValue *var;

    if (paramnum >= gScrVmPub.outparamcount)
    {
        Scr_Error(va("parameter %d does not exist", paramnum + 1));
        return 0;
    }

    var = &gScrVmPub.top[-paramnum];
    if (var->type == 1)
    {
        return var->u.pointerValue;
    }
    gScrVarPub.error_index = paramnum + 1;
    Scr_Error(va("type %s is not an object", var_typename[var->type]));
    return 0;
}


void Scr_NotifyInternal(int varNum, int constString, int numArgs)
{
    VariableValue *curArg;
    int z;
    int ctype;

    Scr_ClearOutParams();
    curArg = gScrVmPub.top - numArgs;
    z = gScrVmPub.inparamcount - numArgs;
    if (varNum)
    {
        ctype = curArg->type;
        curArg->type = 8;
        gScrVmPub.inparamcount = 0;
        VM_Notify(varNum, constString, gScrVmPub.top);
        curArg->type = ctype;
    }
    while (gScrVmPub.top != curArg)
    {
        RemoveRefToValue(gScrVmPub.top->type, gScrVmPub.top->u);
        --gScrVmPub.top;
    }
    gScrVmPub.inparamcount = z;
}

void Scr_NotifyLevel(int constString, unsigned int numArgs)
{
    Scr_NotifyInternal(gScrVarPub.levelId, constString, numArgs);
}

void Scr_NotifyNum(int entityNum, unsigned int entType, unsigned int constString, unsigned int numArgs)
{
    int entVarNum;

    entVarNum = FindEntityId(entityNum, entType);

    Scr_NotifyInternal(entVarNum, constString, numArgs);
}

void Scr_Notify(gentity_s *ent, unsigned short constString, unsigned int numArgs)
{
    Scr_NotifyNum(ent->s.number, 0, constString, numArgs);
}






void VM_SetTime( )
{
  unsigned int id;

  assert(!(gScrVarPub.time & ~VAR_NAME_LOW_MASK));

  if ( gScrVarPub.timeArrayId )
  {
    id = FindVariable(gScrVarPub.timeArrayId, gScrVarPub.time);
    if ( id )
    {

      assert(logScriptTimes);
      if ( logScriptTimes->current.enabled )
      {
        Com_Printf(CON_CHANNEL_PARSERSCRIPT, "SET TIME: %d\n", Sys_Milliseconds());
      }

      VM_Resume(FindObject(id));
      SafeRemoveVariable(gScrVarPub.timeArrayId, gScrVarPub.time);
    }
  }
}

void Scr_RunCurrentThreads( )
{
  int pre_time;

  if ( scrVmEnableScripts->current.enabled )
  {
    pre_time = Sys_MillisecondsRaw();
    assert(!gScrVmPub.function_count);
    assert(!gScrVarPub.error_message);
    assert(!gScrVarPub.error_index);
    assert(!gScrVmPub.outparamcount);
    assert(!gScrVmPub.inparamcount);
    assert(gScrVmPub.top == gScrVmPub.stack);

    VM_SetTime();
    gScrExecuteTime += Sys_MillisecondsRaw() - pre_time;
  }
}



void Scr_IncTime( )
{
  Scr_RunCurrentThreads();
  Scr_FreeEntityList();

  assert(!(gScrVarPub.time & ~VAR_NAME_LOW_MASK));

  ++gScrVarPub.time;
  gScrVarPub.time &= VAR_NAME_LOW_MASK;
//  gScrVmPub.showError = gScrVmPub.abort_on_error != 0;

}

void Scr_DecTime()
{

  assert(!(gScrVarPub.time & ~VAR_NAME_LOW_MASK));

  --gScrVarPub.time;
  gScrVarPub.time &= VAR_NAME_LOW_MASK;
}


void Scr_ErrorJumpOut()
{
    assert ( (unsigned int)g_script_error_level < ARRAY_COUNT( g_script_error ));
    longjmp(g_script_error[g_script_error_level], -1);
}


jmp_buf* VM_GetJmpBuf()
{
    return &g_script_error[g_script_error_level];
}


void Scr_ClearErrorMessage( )
{
  gScrVarPub.error_message = 0;
  gScrVmGlob.dialog_error_message = 0;
  gScrVarPub.error_index = 0;
}

bool Scr_ScriptRuntimecheckInfiniteLoop()
{
    int now = Sys_Milliseconds();

    if (now - gScrVmGlob.starttime > 2500)
    {
        return true;
    }
    return false;
}



#pragma msg "VM_CalcWaitTime ignores framerate"

int VM_CalcWaitTime(VariableValue *waitval)
{
    int waitTime;
    if ( waitval->type == VAR_FLOAT )
    {
        if ( waitval->u.floatValue < 0.0 )
        {
            Scr_Error("negative wait is not allowed");
            return 1;
        }
        //waitTime = f2rint(level.framerate * waitval->u.floatValue);
        waitTime = f2rint(20 * waitval->u.floatValue);
        
        if ( !waitTime && waitval->u.floatValue != 0.0 )
        {
          waitTime = 1;
        }
    }
    else if ( waitval->type == VAR_INTEGER )
    {
        if ( waitval->u.intValue < 0.0 )
        {
            Scr_Error("negative wait is not allowed");
            return 1;
        }
//        waitTime = waitval->u.intValue * level.framerate;
        waitTime = waitval->u.intValue * 20;
    }
    else
    {
        gScrVarPub.error_index = 2;
        Scr_Error(va("type %s is not a float", var_typename[waitval->type]));
        waitTime = 1;
    }
    return waitTime;
}


void Scr_VM_Init( )
{
  gScrVarPub.varUsagePos = "<script init variable>";
  gScrVmPub.maxstack = &gScrVmPub.stack[ARRAY_COUNT(gScrVmPub.stack) -1];
  gScrVmPub.top = gScrVmPub.stack;
  gScrVmPub.function_count = 0;
  gScrVmPub.function_frame = gScrVmPub.function_frame_start;
  gScrVmPub.localVars = gScrVmGlob.localVarsStack -1;
  gScrVarPub.evaluate = 0;
  gScrVmPub.debugCode = 0;
  Scr_ClearErrorMessage( );
  gScrVmPub.terminal_error = 0;
  gScrVmPub.outparamcount = 0;
  gScrVmPub.inparamcount = 0;
  gScrVarPub.tempVariable = AllocValue( );
  gScrVarPub.timeArrayId = 0;
  gScrVarPub.pauseArrayId = 0;
  gScrVarPub.levelId = 0;
  gScrVarPub.gameId = 0;
  gScrVarPub.animId = 0;
  gScrVarPub.freeEntList = 0;
  gScrVmPub.stack[0].type = VAR_CODEPOS;
  gScrVmGlob.loading = 0;
  /*
  gScrVmGlob.recordPlace = 0;
  gScrVmGlob.lastFileName = 0;
  gScrVmGlob.lastLine = 0;
  gScrVarPub.ext_threadcount = 0;
  */
  gScrVarPub.numScriptThreads = 0;
  gScrVarPub.varUsagePos = 0;

  logScriptTimes = Dvar_RegisterBool("logScriptTimes", false, 0, "Log times for every print called from script");
  scrVmEnableScripts = Dvar_RegisterBool("scrVmEnableScripts", true, 0, "Enables script execution");

  scrShowVarUsage = Dvar_RegisterBool("scrShowVarUsage", 0, 0, "Displays var useage at compile time.");
  scrShowStrUsage = Dvar_RegisterBool("scrShowStrUsage", 0, 0, "Displays script string usage at compile time.");


/*
  sv_clientside = _Dvar_RegisterBool("sv_clientside", 0, 0, "Used to toggle systems in script on and off on the server.");
*/
//  Cmd_AddCommandInternal("scrProfileInfo", BG_EvalVehicleName, &VM_DumpScriptProfileInfo_VAR);
}

void Scr_InitSystem(int sys)
{
  assert(sys == SCR_SYS_GAME);
  assert(!gScrVarPub.timeArrayId);
 // assert(!gScrVarPub.ext_threadcount);
  assert(!gScrVarPub.varUsagePos);
  
  gScrVarPub.varUsagePos = "<script init variable>";
  gScrVarPub.timeArrayId = AllocObject();

  if ( gScrVarDebugPub )
  {
    ++gScrVarDebugPub->extRefCount[gScrVarPub.timeArrayId];
  }

  assert(!gScrVarPub.pauseArrayId);

  gScrVarPub.pauseArrayId = Scr_AllocArray();

  if ( gScrVarDebugPub )
  {
    ++gScrVarDebugPub->extRefCount[gScrVarPub.pauseArrayId];
  }

  assert(!gScrVarPub.levelId);
  gScrVarPub.levelId = AllocObject();

  if ( gScrVarDebugPub )
  {
    ++gScrVarDebugPub->extRefCount[gScrVarPub.levelId];
  }
  assert(!gScrVarPub.animId);

  gScrVarPub.animId = AllocObject();

  if ( gScrVarDebugPub )
  {
    ++gScrVarDebugPub->extRefCount[gScrVarPub.animId];
  }
  assert(!gScrVarPub.freeEntList);

  gScrVarPub.time = 0;
  g_script_error_level = -1;

  //if ( inst == SCRIPTINSTANCE_SERVER )
  {
    Scr_InitDebuggerSystem();
  }
  gScrVarPub.varUsagePos = 0;

}



void Scr_Init( )
{
  assert(!gScrVarPub.bInited);

  Scr_InitClassMap();
  Scr_VM_Init();

  gScrCompilePub.script_loading = 0;
  gScrAnimPub.animtree_loading = 0;
  gScrCompilePub.scriptsPos = 0;
//  gScrCompilePub.scriptsCount = 0;
  gScrCompilePub.loadedscripts = 0;
  gScrAnimPub.animtrees = 0;
  gScrCompilePub.builtinMeth = 0;
  gScrCompilePub.builtinFunc = 0;
  gScrVarPub.bInited = 1;
}

unsigned int VM_Execute(unsigned int localId, const char *pos, unsigned int paramcount)
{
  function_stack_t fs_backup;
  VariableValue *startTop;
  int type;
  int thread_count_backup;

  assert(paramcount <= gScrVmPub.inparamcount);

  Scr_ClearOutParams( );
  startTop = &gScrVmPub.top[-paramcount];
  paramcount = gScrVmPub.inparamcount - paramcount;
  if ( gScrVmPub.function_count >= 30 )
  {
    Scr_KillThread(localId);
    gScrVmPub.inparamcount = paramcount + 1;
    assert(!gScrVmPub.outparamcount);
    while ( paramcount )
    {
      RemoveRefToValue(gScrVmPub.top->type, gScrVmPub.top->u);
      --gScrVmPub.top;
      --paramcount;
    }
    ++gScrVmPub.top;
		gScrVmPub.top->type = VAR_UNDEFINED;
    RuntimeError(pos, 0, "script stack overflow (too many embedded function calls)", 0);
    return localId;
  }
  else
  {
    fs_backup = gFs;
    thread_count_backup = gThreadCount;
    gFs.localId = localId;
    gFs.startTop = startTop;
    
    
    if ( gScrVmPub.function_count )
    {
      ++gScrVmPub.function_count;
      ++gScrVmPub.function_frame;
      gScrVmPub.function_frame->fs.localId = 0;
    }
    gScrVmPub.function_frame->fs.pos = pos;
    ++gScrVmPub.function_count;
    ++gScrVmPub.function_frame;
    gScrVmPub.function_frame->fs.localId = localId;
    type = startTop->type;
    startTop->type = VAR_PRECODEPOS;
    gScrVmPub.inparamcount = 0;

    gFs.top = gScrVmPub.top;
    gFs.pos = pos;
    gFs.localVarCount = 0;
    gThreadCount = 0;
    
    localId = VM_Execute();
    gFs = fs_backup;
    gThreadCount = thread_count_backup;
    
    startTop->type = type;
    gScrVmPub.top = startTop + 1;
    gScrVmPub.inparamcount = paramcount + 1;
    assert(!gScrVmPub.outparamcount);
    ClearVariableValue(gScrVarPub.tempVariable);
    if ( gScrVmPub.function_count )
    {
      --gScrVmPub.function_count;
      --gScrVmPub.function_frame;
    }
    return localId;
  }
}


int Scr_AddLocalVars(unsigned int localId)
{
  int localVarCount;
  unsigned int fieldIndex;

  localVarCount = 0;
  for ( fieldIndex = FindLastSibling(localId); fieldIndex; fieldIndex = FindPrevSibling(fieldIndex) )
  {
    *++gScrVmPub.localVars = Scr_GetVarId(fieldIndex);
    ++localVarCount;
  }
  return localVarCount;
}


void VM_UnarchiveStack(unsigned int startLocalId, VariableStackBuffer *stackValue)
{
  VariableValue *top;
  char *buf;
  unsigned int localId;
  int function_count;
  int size;

  assert(!gScrVmPub.function_count);
  assert(stackValue->pos);
  assert(gFs.startTop == &gScrVmPub.stack[0]);

  _mm_prefetch(stackValue->pos, 1);

  gScrVmPub.function_frame->fs.pos = stackValue->pos;
  ++gScrVmPub.function_count;
  ++gScrVmPub.function_frame;
  size = stackValue->size;
  buf = stackValue->buf;
  top = gScrVmPub.stack;
  while ( size )
  {
    --size;
    top[1].type = *(unsigned char*)buf;
    ++top;
    ++buf;
    if ( top->type == VAR_CODEPOS )
    {
      assert(gScrVmPub.function_count < MAX_VM_STACK_DEPTH);

      gScrVmPub.function_frame->fs.pos = *(const char **)buf;
      ++gScrVmPub.function_count;
      ++gScrVmPub.function_frame;
    }
    else
    {
      top->u.stackValue = *(VariableStackBuffer **)buf;
    }
    buf += 4;
  }
  gFs.pos = stackValue->pos;
  gFs.top = top;
  localId = stackValue->localId;
  gFs.localId = localId;
  Scr_ClearWaitTime(startLocalId);

  assert(gScrVmPub.function_count < MAX_VM_STACK_DEPTH);

  function_count = gScrVmPub.function_count;
  while ( 1 )
  {
    gScrVmPub.function_frame_start[function_count].fs.localId = localId;
    --function_count;
    if ( !function_count )
    {
      break;
    }
    localId = GetParentLocalId(localId);
  }
  while ( ++function_count != gScrVmPub.function_count )
  {
    gScrVmPub.function_frame_start[function_count].fs.localVarCount = Scr_AddLocalVars(gScrVmPub.function_frame_start[function_count].fs.localId);
  }
  gFs.localVarCount = Scr_AddLocalVars(gFs.localId);

  if ( stackValue->time != (gScrVarPub.time & 0xFF) )
  {
    Scr_ResetTimeout( );
  }
  --gScrVarPub.numScriptThreads;
  MT_Free(stackValue, stackValue->bufLen);

  assert(gScrVmPub.stack[0].type == VAR_CODEPOS);

}


void VM_Resume(unsigned int timeId)
{
  VariableStackBuffer *stackValue;
  unsigned int stackId;
  unsigned int startLocalId;
  unsigned int localId;

  PIXBeginNamedEvent(-1, "VM_Resume");
  assert(gScrVmPub.top == gScrVmPub.stack);
  Scr_ResetAbortDebugger( );
  Scr_ResetTimeout( );

  assert(timeId);

  AddRefToObject(timeId);
  gFs.startTop = gScrVmPub.stack;
  gThreadCount = 0;
  while ( 1 )
  {
    assert( gScrVarPub.error_message == nullptr);
    assert(!gScrVarPub.error_index);
    assert(!gScrVmPub.outparamcount);
    assert(!gScrVmPub.inparamcount);
    assert(!gScrVmPub.function_count);
    assert(gScrVmPub.localVars == gScrVmGlob.localVarsStack - 1);
    assert(gFs.startTop == &gScrVmPub.stack[0]);
    assert(!gThreadCount);

    stackId = FindFirstSibling(timeId);
    if ( !stackId )
    {
      break;
    }
    startLocalId = GetVariableKeyObject(stackId);
    assert(startLocalId);
    assert(GetValueType( stackId ) == VAR_STACK);

    stackValue = GetVariableValueAddress(stackId)->u.stackValue;
    RemoveObjectVariable(timeId, startLocalId);
    VM_UnarchiveStack(startLocalId, stackValue);
    localId = VM_Execute();
    RemoveRefToObject(localId);
    RemoveRefToValue(gScrVmPub.stack[1].type, gScrVmPub.stack[1].u);
  }
  RemoveRefToObject(timeId);
  ClearVariableValue(gScrVarPub.tempVariable);
  gScrVmPub.top = gScrVmPub.stack;
  /*
  if ( GetCurrentThreadId() == g_DXDeviceThread.owner && !g_DXDeviceThread.aquired )
  {
    D3DPERF_EndEvent();
  }*/
}

unsigned int GetDummyObject( )
{
  ClearVariableValue(gScrVarPub.tempVariable);
  return GetObject(gScrVarPub.tempVariable);
}

unsigned int GetDummyFieldValue( )
{
  ClearVariableValue(gScrVarPub.tempVariable);
  return gScrVarPub.tempVariable;
}

const char * Scr_ReadCodePos(const char **pos)
{
  const char* value = *(reinterpret_cast<const char**>(const_cast<char *>(*pos)));
  *pos += sizeof(const char*);
  return value;
}

unsigned int Scr_ReadUnsigned(const char **pos)
{
  unsigned int value = *(reinterpret_cast<const unsigned int*>(*pos));
  *pos += sizeof(unsigned int);
  return value;
}

unsigned short Scr_ReadUnsignedShort(const char **pos)
{
  unsigned short value = *(reinterpret_cast<const unsigned short*>(*pos));
  *pos += sizeof(unsigned short);
  return value;
}

const unsigned int* Scr_ReadIntArray(const char **pos, int count)
{
  const unsigned int *val;

  val = reinterpret_cast<const unsigned int *>(*pos);
  *pos += sizeof(unsigned int) * count;
  return val;
}


void VM_PrintJumpHistory( )
{
  const char *pos;
  int index;

  Com_Printf(CON_CHANNEL_PARSERSCRIPT, "********************************\n");
  Com_Printf(CON_CHANNEL_PARSERSCRIPT, "Recent loop history (from most recent) :\n");
  index = gScrVmDebugPub.jumpbackHistoryIndex;
  do
  {
    if ( !index )
    {
      index = 128;
    }
    pos = gScrVmDebugPub.jumpbackHistory[--index];
    if ( !pos )
    {
      break;
    }
    Scr_PrintPrevCodePos(CON_CHANNEL_PARSERSCRIPT, pos, 0);
  }
  while ( index != gScrVmDebugPub.jumpbackHistoryIndex );
  Com_Printf(CON_CHANNEL_PARSERSCRIPT, "********************************\n");
}


VariableStackBuffer* VM_ArchiveStack(function_stack_t *stack)
{
  VariableStackBuffer *stackValue;
  VariableValue *top;
  char *buf;
  unsigned int localId;
  int size;
  int bufLen;

  top = stack->top;
  size = top - stack->startTop;
  assert(size == (unsigned short)size);

  bufLen = 5 * size + (sizeof(VariableStackBuffer) -1);

  assert(bufLen == (unsigned short)bufLen);

  stackValue = reinterpret_cast<VariableStackBuffer *>(MT_Alloc(bufLen, 1));
  ++gScrVarPub.numScriptThreads;
  localId = stack->localId;
  stackValue->localId = localId;
  stackValue->size = size;
  stackValue->bufLen = bufLen;
  stackValue->pos = stack->pos;
  stackValue->time = gScrVarPub.time;
  gScrVmPub.localVars -= stack->localVarCount;
  buf = &stackValue->buf[5 * size];
  while ( size )
  {
    buf -= 4;
    if ( top->type == VAR_CODEPOS )
    {
      --gScrVmPub.function_count;
      --gScrVmPub.function_frame;
      *reinterpret_cast<unsigned int32_t*>(buf) = reinterpret_cast<unsigned int32_t>(gScrVmPub.function_frame->fs.pos);
      gScrVmPub.localVars -= gScrVmPub.function_frame->fs.localVarCount;
      localId = GetParentLocalId(localId);
    }
    else
    {
      *reinterpret_cast<unsigned int32_t*>(buf) = top->u.pointerValue;
    }
    --buf;
    assert(top->type >= 0 && top->type < (1 << 8));
    *buf = top->type;
    --top;
    --size;
  }
  --gScrVmPub.function_count;
  --gScrVmPub.function_frame;
  AddRefToObject(localId);
  stack->localId = localId;
  return stackValue;
}

unsigned int Scr_GetLocalVar(const char *pos)
{
  return gScrVmPub.localVars[-(*reinterpret_cast<const unsigned int8_t*>(pos))];
}


unsigned int VM_Execute( )
{
  unsigned int stackOff; // eax
  unsigned int ObjectVariable; // eax
  unsigned int EntityId; // eax
  unsigned __int16 UnsignedShort; // ax
  function_frame_t *function_frame; // [esp+18h] [ebp-324h]
  unsigned int outParCntBackup; // [esp+2ACh] [ebp-90h]
  unsigned int outparamcount; // [esp+2B0h] [ebp-8Ch]
  scr_entref_t entref; // [esp+2B4h] [ebp-88h]
  unsigned int classnum; // [esp+2BCh] [ebp-80h]
  VariableValue stackValue; // [esp+2C0h] [ebp-7Ch] BYREF
  unsigned int builtinIndex; // [esp+2C8h] [ebp-74h]
  unsigned int stringValue; // [esp+2CCh] [ebp-70h]
  const char *currentCodePos; // [esp+2D0h] [ebp-6Ch]
  const char *tempCodePos; // [esp+2D4h] [ebp-68h]
  unsigned int stackId; // [esp+2D8h] [ebp-64h]
  unsigned int fieldValueId; // [esp+2DCh] [ebp-60h]
  int waitTime; // [esp+2E0h] [ebp-5Ch]
  int jumpOffset; // [esp+2E4h] [ebp-58h]
  function_stack_t localFs; // [esp+2E8h] [ebp-54h] BYREF
  unsigned int objectId; // [esp+2FCh] [ebp-40h]
  unsigned int caseValue; // [esp+300h] [ebp-3Ch]
  unsigned int fieldName; // [esp+304h] [ebp-38h]
  unsigned int threadId; // [esp+308h] [ebp-34h]
  unsigned int currentCaseValue; // [esp+30Ch] [ebp-30h]
  unsigned int parentLocalId; // [esp+310h] [ebp-2Ch]
  unsigned int paramcount; // [esp+314h] [ebp-28h]
  int type; // [esp+318h] [ebp-24h]
  int entnum; // [esp+31Ch] [ebp-20h]
  unsigned int fieldValueIndex; // [esp+320h] [ebp-1Ch]
  const char *debugpos; // [esp+324h] [ebp-18h]
  unsigned int selfId; // [esp+328h] [ebp-14h]
  VariableValue tempValue; // [esp+32Ch] [ebp-10h] BYREF
  unsigned int id; // [esp+334h] [ebp-8h]
  uint8_t removeCount; // [esp+33Bh] [ebp-1h]
  static int gOpcode;
  static int gCaseCount;

  ++g_script_error_level;
  localFs = gFs;
  while ( 1 )
  {
    assertlimit(g_script_error_level, ARRAY_COUNT( g_script_error ));
    if ( !_setjmp3(g_script_error[g_script_error_level], 0) )
    {
      break;
    }
error_1:
    //Monkey_GrabComPrints(1);
    Com_Printf(CON_CHANNEL_LOGFILEONLY, "caught script exception\n");
    switch ( gOpcode )
    {
      case OP_EvalLocalArrayRefCached0:
      case OP_EvalLocalArrayRefCached:
      case OP_EvalArrayRef:
      case OP_ClearArray:
      case OP_EvalLocalVariableRef:
        assert(gScrVarPub.error_index >= -1);
        if ( gScrVarPub.error_index < 0 )
        {
          gScrVarPub.error_index = 1;
        }
        break;
      case OP_EvalSelfFieldVariable:
      case OP_EvalFieldVariable:
      case OP_ClearFieldVariable:
      case OP_SetVariableField:
      case OP_SetSelfFieldVariableField:
      case OP_inc:
      case OP_dec:
        gScrVarPub.error_index = 0;
        break;
      case OP_CallBuiltin0:
      case OP_CallBuiltin1:
      case OP_CallBuiltin2:
      case OP_CallBuiltin3:
      case OP_CallBuiltin4:
      case OP_CallBuiltin5:
      case OP_CallBuiltin:
        assert(gScrVarPub.error_index >= 0);
        if ( gScrVarPub.error_index > 0 )
        {
          gScrVarPub.error_index = gScrVmPub.outparamcount + 1 - gScrVarPub.error_index;
        }
        break;
      case OP_CallBuiltinMethod0:
      case OP_CallBuiltinMethod1:
      case OP_CallBuiltinMethod2:
      case OP_CallBuiltinMethod3:
      case OP_CallBuiltinMethod4:
      case OP_CallBuiltinMethod5:
      case OP_CallBuiltinMethod:
        assert(gScrVarPub.error_index >= -1);
        if ( gScrVarPub.error_index <= 0 )
        {
          if ( gScrVarPub.error_index < 0 )
          {
            gScrVarPub.error_index = 1;
          }
        }
        else
        {
          gScrVarPub.error_index = gScrVmPub.outparamcount + 2 - gScrVarPub.error_index;
        }
        break;
      default:
        break;
    }
    RuntimeError(localFs.pos, gScrVarPub.error_index, gScrVarPub.error_message, gScrVmGlob.dialog_error_message);
    Scr_ClearErrorMessage( );
    switch ( gOpcode )
    {
      case OP_EvalLocalArrayCached:
      case OP_EvalArray:
        RemoveRefToValue(localFs.top);
        --localFs.top;
        RemoveRefToValue(localFs.top);
        localFs.top->type = 0;
        break;
      case OP_EvalLocalArrayRefCached0:
      case OP_EvalLocalArrayRefCached:
      case OP_EvalArrayRef:
      case OP_EvalLocalVariableRef:
        fieldValueIndex = 0;
        fieldValueId = GetDummyFieldValue( );
        goto $LN25_31;
      case OP_ClearArray:
      case OP_wait:
        goto $LN25_31;
      case OP_GetSelfObject:
        goto $LN38_13;
      case OP_EvalSelfFieldVariable:
      case OP_EvalFieldVariable:
        localFs.top->type = 0;
        break;
      case OP_EvalSelfFieldVariableRef:
      case OP_EvalFieldVariableRef:
        fieldValueIndex = 0;
        fieldValueId = GetDummyFieldValue( );
        break;
      case OP_ClearFieldVariable:
        if ( gScrVmPub.outparamcount )
        {
          assert(gScrVmPub.outparamcount == 1);
          assert(gScrVmPub.top->type == VAR_UNDEFINED);
          gScrVmPub.outparamcount = 0;
        }
        break;
      case OP_checkclearparams:
        assertx(localFs.top->type != VAR_CODEPOS, "(localFs.top - gScrVmPub.stack) = %i", localFs.top - gScrVmPub.stack);
        while ( localFs.top->type != VAR_PRECODEPOS )
        {
          RemoveRefToValue(localFs.top);
          localFs.top--;
          assertx(localFs.top->type != VAR_CODEPOS, "(localFs.top - gScrVmPub.stack) = %i", localFs.top - gScrVmPub.stack);
        }
        localFs.top->type = VAR_CODEPOS;
        break;
      case OP_SetVariableField:
        if ( gScrVmPub.outparamcount )
        {
          assert(gScrVmPub.outparamcount == 1);
          assert(gScrVmPub.top == localFs.top);
          RemoveRefToValue(localFs.top);
          gScrVmPub.outparamcount = 0;
        }
        goto error_dec_top;
      case OP_SetSelfFieldVariableField:
        RemoveRefToValue(localFs.top);
        gScrVmPub.outparamcount = 0;
        goto error_dec_top;
      case OP_CallBuiltin0:
      case OP_CallBuiltin1:
      case OP_CallBuiltin2:
      case OP_CallBuiltin3:
      case OP_CallBuiltin4:
      case OP_CallBuiltin5:
      case OP_CallBuiltin:
      case OP_CallBuiltinMethod0:
      case OP_CallBuiltinMethod1:
      case OP_CallBuiltinMethod2:
      case OP_CallBuiltinMethod3:
      case OP_CallBuiltinMethod4:
      case OP_CallBuiltinMethod5:
      case OP_CallBuiltinMethod:
        Scr_ClearOutParams( );
        localFs.top = gScrVmPub.top + 1;
        localFs.top->type = VAR_UNDEFINED;
        break;
      case OP_ScriptFunctionCall2:
      case OP_ScriptFunctionCall:
      case OP_ScriptMethodCall:
        Scr_ReadCodePos(&localFs.pos);
      case OP_ScriptFunctionCallPointer:
      case OP_ScriptMethodCallPointer:
        assert(localFs.top->type != VAR_CODEPOS);
        while ( localFs.top->type != VAR_PRECODEPOS )
        {
          RemoveRefToValue(localFs.top);
          localFs.top--;
          assert(localFs.top->type != VAR_CODEPOS);
        }
        localFs.top->type = VAR_UNDEFINED;
        break;
      case OP_ScriptThreadCall:
      case OP_ScriptMethodThreadCall:
        Scr_ReadCodePos(&localFs.pos);
        goto $LN14_59;
      case OP_ScriptThreadCallPointer:
      case OP_ScriptMethodThreadCallPointer:
$LN14_59:
        for ( paramcount = Scr_ReadUnsigned(&localFs.pos); paramcount; --paramcount )
        {
          RemoveRefToValue(localFs.top);
          localFs.top--;
        }
        ++localFs.top;
        localFs.top[0].type = VAR_UNDEFINED;
        break;
      case OP_CastFieldObject:
        objectId = GetDummyObject( );
        goto error_dec_top;
      case OP_EvalLocalVariableObjectCached:
        ++localFs.pos;
$LN38_13:
        objectId = GetDummyObject( );
        break;
      case OP_JumpOnFalse:
      case OP_JumpOnTrue:
      case OP_JumpOnFalseExpr:
      case OP_JumpOnTrueExpr:
        Scr_ReadUnsignedShort(&localFs.pos);
        goto error_dec_top;
      case OP_jumpback:
        jumpOffset = Scr_ReadUnsignedShort(&localFs.pos);
        localFs.pos -= jumpOffset;
        break;
      case OP_bit_or:
      case OP_bit_ex_or:
      case OP_bit_and:
      case OP_equality:
      case OP_inequality:
      case OP_less:
      case OP_greater:
      case OP_less_equal:
      case OP_greater_equal:
      case OP_shift_left:
      case OP_shift_right:
      case OP_plus:
      case OP_minus:
      case OP_multiply:
      case OP_divide:
      case OP_mod:
        goto error_dec_top;
      case OP_waittillmatch:
        ++localFs.pos;
        goto $LN26_29;
      case OP_waittill:
      case OP_endon:
$LN26_29:
        RemoveRefToValue(localFs.top);
        localFs.top--;
        goto $LN25_31;
      case OP_notify:
        assert(localFs.top->type != VAR_CODEPOS);
        while ( localFs.top->type != VAR_PRECODEPOS )
        {
          RemoveRefToValue(localFs.top);
          localFs.top--;
          assert(localFs.top->type != VAR_CODEPOS);
        }
        goto $LN25_31;
      case OP_switch:
        if ( gCaseCount )
        {
          do
          {
            currentCaseValue = Scr_ReadUnsigned(&localFs.pos);
            currentCodePos = Scr_ReadCodePos(&localFs.pos);
            --gCaseCount;
          }
          while ( gCaseCount );
          if ( !currentCaseValue )
          {
            localFs.pos = currentCodePos;
            assert(localFs.pos);
          }
        }
$LN25_31:
        RemoveRefToValue(localFs.top);
error_dec_top:
        --localFs.top;
        break;
      default:
        break;
    }
    assert(!gScrVmPub.inparamcount);
    assert(!gScrVmPub.outparamcount);

//    Monkey_Error(0);
    if ( gScrVmPub.showError && !gScrVmPub.debugCode && !Scr_IgnoreErrors( ) )
    {
      gScrVmPub.showError = 0;
      Scr_HitBreakpoint(localFs.top, localFs.pos, localFs.localId, 0);
    }
  }
  while ( 1 )
  {
    assertx(!gScrVarPub.error_message, "(gScrVarPub.error_message) = %s", gScrVarPub.error_message);
    assert(!gScrVarPub.error_index);
    assert(!gScrVmPub.inparamcount);
    assert(!gScrVmPub.outparamcount);

    gOpcode = static_cast<unsigned char>(*localFs.pos);
    localFs.pos++;
interrupt_return:
    gScrVarPub.varUsagePos = localFs.pos;
    switch ( gOpcode )
    {
      case OP_End:
        parentLocalId = GetSafeParentLocalId(localFs.localId);
        Scr_KillThread(localFs.localId);
        gScrVmPub.localVars -= localFs.localVarCount;
        assertx(localFs.top->type != VAR_PRECODEPOS, "(localFs.top - gScrVmPub.stack) = %i", localFs.top - gScrVmPub.stack);

        while ( localFs.top->type != VAR_CODEPOS )
        {
          RemoveRefToValue(localFs.top);
          --localFs.top;
          assertx(localFs.top->type != VAR_PRECODEPOS, "(localFs.top - gScrVmPub.stack) = %i", localFs.top - gScrVmPub.stack);
        }

        --gScrVmPub.function_count;
        --gScrVmPub.function_frame;
        if ( !parentLocalId )
        {
          assertx(localFs.top == localFs.startTop, "(localFs.top - localFs.startTop) = %i", localFs.top - localFs.startTop);

thread_end:
          localFs.startTop[1].type = VAR_UNDEFINED;
          goto thread_return;
        }
        assertx(localFs.top->type == VAR_CODEPOS, "(localFs.top - gScrVmPub.stack) = %i", localFs.top - gScrVmPub.stack);

        localFs.top->type = VAR_UNDEFINED;
        goto end;
      case OP_Return:
        parentLocalId = GetSafeParentLocalId(localFs.localId);
        Scr_KillThread(localFs.localId);
        gScrVmPub.localVars -= localFs.localVarCount;
        tempValue.type = localFs.top->type;
        tempValue.u.intValue = localFs.top->u.intValue;
        --localFs.top;
        assertx(localFs.top->type != VAR_PRECODEPOS, "(localFs.top - gScrVmPub.stack) = %i", localFs.top - gScrVmPub.stack);

        while ( localFs.top->type != VAR_CODEPOS )
        {
          RemoveRefToValue(localFs.top->type, localFs.top->u);
          --localFs.top;
          assertx(localFs.top->type != VAR_PRECODEPOS, "(localFs.top - gScrVmPub.stack) = %i", localFs.top - gScrVmPub.stack);
        }
        --gScrVmPub.function_count;
        --gScrVmPub.function_frame;
        if ( parentLocalId )
        {
          assertx(localFs.top->type == VAR_CODEPOS, "(localFs.top - gScrVmPub.stack) = %i", localFs.top - gScrVmPub.stack);

          *localFs.top = tempValue;
end:
          assert(localFs.top != localFs.startTop);

          RemoveRefToObject(localFs.localId);
          localFs.pos = gScrVmPub.function_frame->fs.pos;
          assert(localFs.pos);

          localFs.localVarCount = gScrVmPub.function_frame->fs.localVarCount;
          localFs.localId = parentLocalId;
          continue;
        }
        assertint(localFs.top == localFs.startTop, localFs.top - localFs.startTop);
        localFs.top[1] = tempValue;
thread_return:
        if ( gThreadCount )
        {
          --gThreadCount;
          RemoveRefToObject(localFs.localId);
          localFs = gScrVmPub.function_frame->fs;
          localFs.top->type = gScrVmPub.function_frame->topType;
          ++localFs.top;
          continue;
        }
        assertint(g_script_error_level >= 0, g_script_error_level);

        --g_script_error_level;
        gFs = localFs;
        return localFs.localId;
      case OP_GetUndefined:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;
        localFs.top[0].type = VAR_UNDEFINED;
        continue;
      case OP_GetZero:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_INTEGER;
        localFs.top[0].u.intValue = 0;
        continue;
      case OP_GetByte:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;
        
        localFs.top[0].type = VAR_INTEGER;
        localFs.top[0].u.intValue = *reinterpret_cast<const unsigned char*>(localFs.pos);
        ++localFs.pos;
        continue;
      case OP_GetNegByte:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_INTEGER;
        localFs.top[0].u.intValue = -(*reinterpret_cast<const unsigned char*>(localFs.pos));
        ++localFs.pos;
        continue;
      case OP_GetUnsignedShort:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_INTEGER;
        localFs.top[0].u.intValue = *reinterpret_cast<const unsigned short*>(localFs.pos);
        localFs.pos += sizeof(unsigned short);
        continue;
      case OP_GetNegUnsignedShort:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_INTEGER;
        localFs.top[0].u.intValue = -(*reinterpret_cast<const unsigned short*>(localFs.pos));
        localFs.pos += sizeof(unsigned short);
        continue;
      case OP_GetInteger:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_INTEGER;
        localFs.top[0].u.intValue = *reinterpret_cast<const int32_t*>(localFs.pos);
        localFs.pos += sizeof(int32_t);
        continue;
      case OP_GetFloat:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_FLOAT;
        localFs.top[0].u.floatValue = *reinterpret_cast<const float*>(localFs.pos);
        localFs.pos += sizeof(float);
        continue;
      case OP_GetString:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_STRING;
        localFs.top[0].u.stringValue = *reinterpret_cast<const unsigned short*>(localFs.pos);
        localFs.pos += sizeof(unsigned short);
        SL_AddRefToString(localFs.top[0].u.stringValue);
        continue;
      case OP_GetIString:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_ISTRING;
        localFs.top[0].u.stringValue = *reinterpret_cast<const unsigned short*>(localFs.pos);
        localFs.pos += sizeof(unsigned short);
        SL_AddRefToString(localFs.top[0].u.stringValue);
        continue;
      case OP_GetVector:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_VECTOR;
        localFs.top[0].u.vectorValue = reinterpret_cast<const float*>(localFs.pos);
        localFs.pos += sizeof(vec3_t);
        continue;
      case OP_GetLevelObject:
        objectId = gScrVarPub.levelId;
        continue;
      case OP_GetAnimObject:
        objectId = gScrVarPub.animId;
        continue;
      case OP_GetSelf:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_BEGIN_REF;
        localFs.top[0].u.pointerValue = Scr_GetSelf(localFs.localId);
        AddRefToObject(localFs.top[0].u.pointerValue);
        continue;
      case OP_GetLevel:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_BEGIN_REF;
        localFs.top[0].u.pointerValue = gScrVarPub.levelId;
        AddRefToObject(gScrVarPub.levelId);
        continue;
      case OP_GetGame:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0] = Scr_EvalVariable(gScrVarPub.gameId);
        continue;
      case OP_GetAnim:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;
        
        localFs.top[0].type = VAR_BEGIN_REF;
        localFs.top[0].u.pointerValue = gScrVarPub.animId;
        AddRefToObject(gScrVarPub.animId);
        continue;
      case OP_GetAnimation:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_ANIMATION;
        localFs.top[0].u.pointerValue = *reinterpret_cast<const unsigned int32_t*>(localFs.pos);
        localFs.pos += sizeof(unsigned int32_t);
        continue;
      case OP_GetGameRef:
        fieldValueIndex = 0;
        fieldValueId = gScrVarPub.gameId;
        continue;
      case OP_GetFunction:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0].type = VAR_FUNCTION;
        localFs.top[0].u.pointerValue = *reinterpret_cast<const unsigned int32_t*>(localFs.pos);
        localFs.pos += sizeof(unsigned int32_t);
        continue;



      case OP_CreateLocalVariable:
        ++gScrVmPub.localVars;
        ++localFs.localVarCount;
        *gScrVmPub.localVars = GetNewVariable(localFs.localId, *reinterpret_cast<const unsigned short*>(localFs.pos));
        localFs.pos += sizeof(unsigned short);
        continue;
      case OP_RemoveLocalVariables:
        removeCount = *localFs.pos++;
        gScrVmPub.localVars -= removeCount;
        localFs.localVarCount -= removeCount;
        while ( removeCount )
        {
          RemoveNextVariable(localFs.localId);
          --removeCount;
        }
        continue;
      case OP_EvalLocalVariableCached0:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0] = Scr_EvalVariable(gScrVmPub.localVars[0]);
        continue;
      case OP_EvalLocalVariableCached1:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0] = Scr_EvalVariable(gScrVmPub.localVars[-1]);
        continue;
      case OP_EvalLocalVariableCached2:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0] = Scr_EvalVariable(gScrVmPub.localVars[-2]);
        continue;
      case OP_EvalLocalVariableCached3:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0] = Scr_EvalVariable(gScrVmPub.localVars[-3]);
        continue;
      case OP_EvalLocalVariableCached4:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0] = Scr_EvalVariable(gScrVmPub.localVars[-4]);
        continue;
      case OP_EvalLocalVariableCached5:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0] = Scr_EvalVariable(gScrVmPub.localVars[-5]);
        continue;
      case OP_EvalLocalVariableCached:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;

        localFs.top[0] = Scr_EvalVariable(gScrVmPub.localVars[-(*reinterpret_cast<const unsigned int8_t*>(localFs.pos))]);
        ++localFs.pos;
        continue;
      case OP_EvalLocalArrayCached:
        assertint(localFs.top >= gScrVmPub.stack, localFs.top - gScrVmPub.stack);
        assertint(localFs.top+1 <= gScrVmPub.maxstack, localFs.top+1 - gScrVmPub.stack);
        ++localFs.top;
        
        localFs.top[0] = Scr_EvalVariable(gScrVmPub.localVars[-(*reinterpret_cast<const unsigned int8_t*>(localFs.pos))]);
        ++localFs.pos;
      case OP_EvalArray:
        Scr_EvalArray(localFs.top, localFs.top - 1);
        goto loop_dec_top;
      case OP_EvalLocalArrayRefCached0:
        fieldValueId = gScrVmPub.localVars[0];
        goto EvalArrayRef;
      case OP_EvalLocalArrayRefCached:
        fieldValueId = gScrVmPub.localVars[-(*reinterpret_cast<const unsigned int8_t*>(localFs.pos))];
        ++localFs.pos;
        goto EvalArrayRef;
      case OP_EvalArrayRef:
EvalArrayRef:
        objectId = Scr_EvalArrayRef(fieldValueId);
        
        if ( localFs.top->type == VAR_INTEGER )
        {
          if ( !IsValidArrayIndex(localFs.top->u.intValue) )
          {
            gFs = localFs;
            Scr_Errorf("array index %d out of range", localFs.top->u.intValue);
          }
          fieldValueIndex = GetArrayVariableIndex(objectId, localFs.top->u.intValue);
        }
        else if ( localFs.top->type == VAR_STRING )
        {
          fieldValueIndex = GetVariableIndexInternal(objectId, localFs.top->u.stringValue);
          SL_RemoveRefToString(localFs.top->u.stringValue);
        }
        else
        {
          gFs = localFs;
          Scr_Errorf("%s is not an array index", var_typename[localFs.top->type]);
        }
        fieldValueId = Scr_GetVarId(fieldValueIndex);
        assert(fieldValueId);
        goto loop_dec_top;
      case OP_ClearArray:
        ClearArray(fieldValueId, localFs.top);
        goto loop_dec_top;
      case OP_EmptyArray:
        ++localFs.top;

        localFs.top[0].type = VAR_BEGIN_REF;
        localFs.top[0].u.pointerValue = Scr_AllocArray( );
        continue;
      case OP_GetSelfObject:
        objectId = Scr_GetSelf(localFs.localId);
        if ( IsFieldObject(objectId) )
        {
          continue;
        }
        type = Scr_GetObjectType(objectId);
        goto not_an_object_error;
      case OP_EvalLevelFieldVariable:
        objectId = gScrVarPub.levelId;
        goto EvalFieldVariable;
      case OP_EvalAnimFieldVariable:
        objectId = gScrVarPub.animId;
EvalFieldVariable:
        assert(localFs.top >= gScrVmPub.stack);
        assert(localFs.top+1 <= gScrVmPub.maxstack);
        ++localFs.top;

        localFs.top[0] = Scr_EvalVariable(FindVariable(objectId, *reinterpret_cast<const unsigned short*>(localFs.pos)));
        localFs.pos += sizeof(unsigned short);
        continue;
      case OP_EvalSelfFieldVariable:
        objectId = Scr_GetSelf(localFs.localId);
        if ( !IsFieldObject(objectId) )
        {
          assert(localFs.top >= gScrVmPub.stack);
          assert(localFs.top+1 <= gScrVmPub.maxstack);

          ++localFs.top;
          localFs.pos += sizeof(unsigned short);
          type = Scr_GetObjectType(objectId);
          goto not_an_object_error;
        }
      case OP_EvalFieldVariable:
        assert(localFs.top >= gScrVmPub.stack);
        assert(localFs.top+1 <= gScrVmPub.maxstack);
        ++localFs.top;    
        
        localFs.top[0] = Scr_FindVariableField(objectId, *reinterpret_cast<const unsigned short*>(localFs.pos));
        localFs.pos += sizeof(unsigned short);
        continue;
      case OP_EvalLevelFieldVariableRef:
        objectId = gScrVarPub.levelId;
        goto EvalFieldVariableRef;
      case OP_EvalAnimFieldVariableRef:
        objectId = gScrVarPub.animId;
        goto EvalFieldVariableRef;
      case OP_EvalSelfFieldVariableRef:
        objectId = Scr_GetSelf(localFs.localId);
        goto EvalFieldVariableRef;
      case OP_EvalFieldVariableRef:
EvalFieldVariableRef:
        fieldValueIndex = Scr_GetVariableFieldIndex(objectId, *reinterpret_cast<const unsigned short*>(localFs.pos));
        localFs.pos += sizeof(unsigned short);
        fieldValueId = Scr_GetVarId(fieldValueIndex);
        continue;
      case OP_ClearFieldVariable:
        ClearVariableField(objectId, *reinterpret_cast<const unsigned short*>(localFs.pos), localFs.top);
        localFs.pos += sizeof(unsigned short);
        continue;
      case OP_SafeCreateVariableFieldCached:
        ++gScrVmPub.localVars;
        ++localFs.localVarCount;
        gScrVmPub.localVars[0] = GetNewVariable(localFs.localId, *reinterpret_cast<const unsigned short*>(localFs.pos));
        localFs.pos += sizeof(unsigned short);
      case OP_SafeSetVariableFieldCached0:
        assertint(localFs.top->type != VAR_CODEPOS, localFs.top - gScrVmPub.stack);
        if ( localFs.top->type != VAR_PRECODEPOS )
        {
          goto LABEL_298;
        }
        continue;
      case OP_SafeSetVariableFieldCached:
        assertint(localFs.top->type != VAR_CODEPOS, localFs.top - gScrVmPub.stack);
        if ( localFs.top->type != VAR_PRECODEPOS )
        {
          goto LABEL_304;
        }
        ++localFs.pos;
        continue;
      case OP_SafeSetWaittillVariableFieldCached:
        assertint(localFs.top->type != VAR_PRECODEPOS, localFs.top - gScrVmPub.stack);

        if ( localFs.top->type != VAR_CODEPOS )
        {
          goto LABEL_304;
        }
        ClearVariableValue(gScrVmPub.localVars[-(*reinterpret_cast<const unsigned int8_t*>(localFs.pos))]);
        localFs.pos++;
        continue;
      case OP_clearparams:
        assertint(localFs.top->type != VAR_PRECODEPOS, localFs.top - gScrVmPub.stack);

        while ( localFs.top->type != VAR_CODEPOS )
        {
          RemoveRefToValue(localFs.top);
          --localFs.top;
          assertint(localFs.top->type != VAR_PRECODEPOS, localFs.top - gScrVmPub.stack);
        }
        continue;
      case OP_checkclearparams:
        assertint(localFs.top->type != VAR_CODEPOS, localFs.top - gScrVmPub.stack);

        if ( localFs.top->type == VAR_PRECODEPOS )
        {
          /*
          //Variable count is unknown
          if ( gScrVarPub.numScriptValues > 0x3F37E || gScrVarPub.numScriptObjects > 0x737E )
          {
            gFs = localFs;
            if ( gScrVmPub.showError )
            {
              Scr_DumpScriptThreads( );
              Scr_DumpScriptVariablesDefault( );
              Scr_Error("exceeded maximum number of script variables", false);
            }
            Sys_Error("exceeded maximum number of script variables");
          }
          */
          localFs.top->type = VAR_CODEPOS;
          continue;
        }
        else
        {
          gFs = localFs;
          Scr_Error("function called with too many parameters", false);
        }
      case OP_EvalLocalVariableRefCached0:
        fieldValueIndex = 0;
        fieldValueId = gScrVmPub.localVars[0];     
        continue;
      case OP_EvalLocalVariableRefCached:
        fieldValueIndex = 0;
        fieldValueId = gScrVmPub.localVars[-(*reinterpret_cast<const unsigned int8_t*>(localFs.pos))];
        localFs.pos++;
        continue;
      case OP_SetLevelFieldVariableField:
        SetVariableValue(GetVariable(gScrVarPub.levelId, *reinterpret_cast<const unsigned short*>(localFs.pos)), localFs.top);
        localFs.pos += sizeof(unsigned short);
        goto loop_dec_top;
      case OP_SetAnimFieldVariableField:
        SetVariableValue(GetVariable(gScrVarPub.animId, *reinterpret_cast<const unsigned short*>(localFs.pos)), localFs.top);
        localFs.pos += sizeof(unsigned short);
        goto loop_dec_top;
      case OP_SetSelfFieldVariableField:
        fieldName = *reinterpret_cast<const unsigned short*>(localFs.pos);
        objectId = Scr_GetSelf(localFs.localId);
        fieldValueIndex = Scr_GetVariableFieldIndex(objectId, fieldName);
        localFs.pos += sizeof(unsigned short);
        fieldValueId = Scr_GetVarId(fieldValueIndex);
      case OP_SetVariableField:
        if ( fieldValueIndex )
        {
          assert(fieldValueId);
          if ( localFs.top->type )
          {
            SetVariableValue(fieldValueId, localFs.top);
          }
          else
          {
            RemoveVariableValue(objectId, fieldValueIndex);
          }
        }
        else
        {
          SetVariableFieldValue(fieldValueId, localFs.top);
        }
        goto loop_dec_top;
      case OP_SetLocalVariableFieldCached0:
LABEL_298:
        SetVariableValue(gScrVmPub.localVars[0], localFs.top);
        goto loop_dec_top;
      case OP_SetLocalVariableFieldCached:
LABEL_304:
        SetVariableValue(gScrVmPub.localVars[-(*reinterpret_cast<const unsigned int8_t*>(localFs.pos))], localFs.top);
        localFs.pos++;
        goto loop_dec_top;
      case OP_CallBuiltin0:
      case OP_CallBuiltin1:
      case OP_CallBuiltin2:
      case OP_CallBuiltin3:
      case OP_CallBuiltin4:
      case OP_CallBuiltin5:
        assert(!gScrVmPub.outparamcount);
        gScrVmPub.outparamcount = gOpcode - OP_CallBuiltin0;
        goto CallBuiltin;
      case OP_CallBuiltin:
        assert(!gScrVmPub.outparamcount);
        gScrVmPub.outparamcount = *reinterpret_cast<const unsigned int8_t*>(localFs.pos);
        localFs.pos++;
CallBuiltin:
        assert(!gScrVmPub.inparamcount);
        debugpos = localFs.pos;
        builtinIndex = *reinterpret_cast<const unsigned short*>(localFs.pos);
        localFs.pos += sizeof(unsigned short);
        gScrVmPub.function_frame->fs.pos = localFs.pos;
        if ( gScrVmDebugPub.func_table[builtinIndex].breakpointCount )
        {
          outparamcount = gScrVmPub.outparamcount;
          Scr_HitBuiltinBreakpoint(localFs.top, debugpos, localFs.localId, gOpcode, builtinIndex, outparamcount);
          gScrVmPub.outparamcount = outparamcount;
        }
        gScrVmPub.top = localFs.top;
        reinterpret_cast<void (*)(void)>(gScrCompilePub.func_table[builtinIndex])();
        goto post_builtin;
      case OP_CallBuiltinMethod0:
      case OP_CallBuiltinMethod1:
      case OP_CallBuiltinMethod2:
      case OP_CallBuiltinMethod3:
      case OP_CallBuiltinMethod4:
      case OP_CallBuiltinMethod5:
        assert(!gScrVmPub.outparamcount);
        gScrVmPub.outparamcount = gOpcode - OP_CallBuiltinMethod0;
        goto CallBuiltinMethod;
      case OP_CallBuiltinMethod:
        assert(!gScrVmPub.outparamcount);
        gScrVmPub.outparamcount = *reinterpret_cast<const unsigned int8_t*>(localFs.pos);
        localFs.pos++;
CallBuiltinMethod:
        assert(!gScrVmPub.inparamcount);
        debugpos = localFs.pos;
        gScrVmPub.top = localFs.top - 1;
        builtinIndex = *reinterpret_cast<const unsigned short*>(localFs.pos);
        localFs.pos += sizeof(unsigned short);
        if ( localFs.top->type != VAR_POINTER )
        {
          goto LABEL_395;
        }
        objectId = localFs.top->u.stringValue;
        if ( Scr_GetObjectType(objectId) != VAR_ENTITY )
        {
          type = Scr_GetObjectType(objectId);
          RemoveRefToObject(objectId);
          gScrVarPub.error_index = -1;
          gFs = localFs;
          Scr_Errorf("%s is not an entity", var_typename[type]);
LABEL_395:
          type = localFs.top->type;
          RemoveRefToValue(localFs.top->type, localFs.top->u);
          gScrVarPub.error_index = -1;
          gFs = localFs;
          Scr_Errorf("%s is not an entity", var_typename[type]);

$LN221_0:
          assert(Scr_IsInOpcodeMemory( localFs.pos ));
          if ( localFs.top->type == VAR_FLOAT )
          {
            if ( localFs.top->u.floatValue < 0.0 )
            {
              goto negWait;
            }
            //waitTime = (int)((float)((float)(inst != SCRIPTINSTANCE_SERVER ? 60 : 20) * localFs.top->u.floatValue) + 9.313225746154785e-10);
            waitTime = 20 * localFs.top->u.floatValue;
            if ( !waitTime )
            {
              waitTime = localFs.top->u.floatValue != 0.0;
            }
          }
          else if ( localFs.top->type == VAR_INTEGER )
          {
            //waitTime = localFs.top->u.intValue * (inst != SCRIPTINSTANCE_SERVER ? 60 : 20);
            waitTime = localFs.top->u.intValue * 20;
          }
          else
          {
            gScrVarPub.error_index = 2;
            gFs = localFs;
            Scr_Errorf("type %s is not a float", var_typename[localFs.top->type]);
          }
          if ( (unsigned int)waitTime < 0xFFFFFF )
          {
            if ( waitTime )
            {
              Scr_ResetTimeout( );
            }
            waitTime = (waitTime + gScrVarPub.time) & 0xFFFFFF;
            --localFs.top;
            stackValue.type = VAR_STACK;
            stackValue.u.stackValue = VM_ArchiveStack(&localFs);
            id = GetArray(GetVariable(gScrVarPub.timeArrayId, waitTime));
            stackId = GetNewObjectVariable(id, localFs.localId);
            SetNewVariableValue(stackId, &stackValue);
            Scr_SetThreadWaitTime(localFs.localId, waitTime);
            goto thread_end;
          }
          gScrVarPub.error_index = 2;
          if ( waitTime >= 0 )
          {
            gFs = localFs;
            Scr_Error("wait is too long", false);
          }
negWait:
          gFs = localFs;
          Scr_Error("negative wait is not allowed", false);
$LN209:
          assert(Scr_IsInOpcodeMemory( localFs.pos ));
          assert(!(gScrVarPub.time & ~VAR_NAME_LOW_MASK));

          stackValue.type = VAR_STACK;
          stackValue.u.stackValue = VM_ArchiveStack(&localFs);
          id = GetArray(GetVariable(gScrVarPub.timeArrayId, gScrVarPub.time));
          stackId = GetNewObjectVariableReverse(id, localFs.localId);
          SetNewVariableValue(stackId, &stackValue);
          Scr_SetThreadWaitTime(localFs.localId, gScrVarPub.time);
          goto thread_end;
        }
        entref = Scr_GetEntityIdRef(objectId);
        RemoveRefToObject(objectId);
        gScrVmPub.function_frame->fs.pos = localFs.pos;
        if ( gScrVmGlob.recordPlace )
        {
          Scr_GetFileAndLine(localFs.pos, const_cast<char**>(&gScrVmGlob.lastFileName), &gScrVmGlob.lastLine);
        }
        if ( gScrVmDebugPub.func_table[builtinIndex].breakpointCount )
        {
          assert(gScrVmPub.top == localFs.top - 1);
          outParCntBackup = gScrVmPub.outparamcount;
          Scr_HitBuiltinBreakpoint(localFs.top, debugpos, localFs.localId, gOpcode, builtinIndex, outParCntBackup + 1);
          gScrVmPub.outparamcount = outParCntBackup;
          gScrVmPub.top = localFs.top - 1;
        }
        gFs = localFs;   
        reinterpret_cast<void (*)(scr_entref_t)>(gScrCompilePub.func_table[builtinIndex])(entref);
post_builtin:
        localFs.top = gScrVmPub.top;
        localFs.pos = gScrVmPub.function_frame->fs.pos;
        if ( gScrVmPub.outparamcount )
        {
          paramcount = gScrVmPub.outparamcount;
          gScrVmPub.outparamcount = 0;
          gScrVmPub.top -= paramcount;
          do
          {
            RemoveRefToValue(localFs.top->type, localFs.top->u);
            --localFs.top;
            --paramcount;
          }
          while ( paramcount );
        }
        if ( gScrVmPub.inparamcount )
        {
          assert(gScrVmPub.inparamcount == 1);
          gScrVmPub.inparamcount = 0;
          assert(localFs.top == gScrVmPub.top);
        }
        else
        {
          assert(localFs.top == gScrVmPub.top);
          ++localFs.top;
          localFs.top[0].type = VAR_UNDEFINED;
        }
        continue;
      case OP_wait:
        goto $LN221_0;
      case OP_waittillFrameEnd:
        goto $LN209;
      case OP_PreScriptCall:
        assert(localFs.top >= gScrVmPub.stack);
        assert(localFs.top+1 <= gScrVmPub.maxstack);
        ++localFs.top;
        
        localFs.top[0].type = VAR_PRECODEPOS;
        continue;
      case OP_ScriptFunctionCall2:
        assert(localFs.top >= gScrVmPub.stack);
        assert(localFs.top+1 <= gScrVmPub.maxstack);
        ++localFs.top;

        localFs.top[0].type = VAR_PRECODEPOS;
      case OP_ScriptFunctionCall:
        if ( gScrVmPub.function_count < 31 )
        {
          selfId = Scr_GetSelf(localFs.localId);
          AddRefToObject(selfId);
          localFs.localId = AllocChildThread(selfId, localFs.localId);
          gScrVmPub.function_frame->fs.pos = localFs.pos;
          function_frame = gScrVmPub.function_frame;
          localFs.pos = *reinterpret_cast<const char **>(const_cast<char *>(function_frame->fs.pos));
          function_frame->fs.pos += sizeof(char *);
          goto function_call;
        }
        gFs = localFs;
        Scr_Error("script stack overflow (too many embedded function calls)", false);
$LN202_0:
        if ( localFs.top->type != VAR_FUNCTION )
        {
          goto LABEL_442;
        }
        if ( gScrVmPub.function_count < 31 )
        {
          selfId = Scr_GetSelf(localFs.localId);
          AddRefToObject(selfId);
          localFs.localId = AllocChildThread(selfId, localFs.localId);
          gScrVmPub.function_frame->fs.pos = localFs.pos;
          localFs.pos = localFs.top->u.codePosValue;
          --localFs.top;
          goto function_call;
        }
        gScrVarPub.error_index = 1;
        gFs = localFs;
        Scr_Error("script stack overflow (too many embedded function calls)", 0);
LABEL_442:
        gFs = localFs;
        Scr_Errorf("%s is not a function pointer", var_typename[localFs.top->type]);
$LN198:
        if ( localFs.top->type != VAR_BEGIN_REF )
        {
          goto not_an_object1;
        }
        if ( gScrVmPub.function_count < 31 )
        {
          localFs.localId = AllocChildThread(localFs.top->u.stringValue, localFs.localId);
          --localFs.top;
          gScrVmPub.function_frame->fs.pos = localFs.pos;
          localFs.pos = Scr_ReadCodePos(&gScrVmPub.function_frame->fs.pos);
          goto function_call;
        }
        gFs = localFs;
        Scr_Error("script stack overflow (too many embedded function calls)", false);
not_an_object1:
        type = localFs.top->type;
        goto not_an_object_error1;
      case OP_ScriptFunctionCallPointer:
        goto $LN202_0;
      case OP_ScriptMethodCall:
        goto $LN198;
      case OP_ScriptMethodCallPointer:
        if ( localFs.top->type == VAR_FUNCTION )
        {
          tempCodePos = localFs.top->u.codePosValue;
          --localFs.top;
          if ( localFs.top->type != VAR_BEGIN_REF )
          {
            goto not_an_object2;
          }
          if ( gScrVmPub.function_count < 31 )
          {
            localFs.localId = AllocChildThread(localFs.top->u.stringValue, localFs.localId);
            --localFs.top;
            gScrVmPub.function_frame->fs.pos = localFs.pos;
            localFs.pos = tempCodePos;
            goto function_call;
          }
          gScrVarPub.error_index = 1;
          gFs = localFs;
          Scr_Error("script stack overflow (too many embedded function calls)", false);
        }
        else
        {
          RemoveRefToValue(localFs.top--);
          gFs = localFs;
          Scr_Errorf("%s is not a function pointer", var_typename[localFs.top[1].type]);
$LN187:
          if ( gScrVmPub.function_count < 31 )
          {
            selfId = Scr_GetSelf(localFs.localId);
            AddRefToObject(selfId);
            localFs.localId = AllocThread(selfId);
            gScrVmPub.function_frame->fs.pos = localFs.pos;
            gScrVmPub.function_frame->fs.startTop = localFs.startTop;
            localFs.pos = Scr_ReadCodePos(&gScrVmPub.function_frame->fs.pos);
            stackOff = Scr_ReadUnsigned(&gScrVmPub.function_frame->fs.pos);
            localFs.startTop = &localFs.top[-stackOff];
            goto thread_call;
          }
          gScrVarPub.error_index = 1;
          gFs = localFs;
          Scr_Error("script stack overflow (too many embedded function calls)", false);
$LN184_0:
          if ( localFs.top->type == VAR_FUNCTION )
          {
            if ( gScrVmPub.function_count < 31 )
            {
              tempCodePos = localFs.top->u.codePosValue;
              --localFs.top;
              selfId = Scr_GetSelf(localFs.localId);
              AddRefToObject(selfId);
              localFs.localId = AllocThread(selfId);
              gScrVmPub.function_frame->fs.pos = localFs.pos;
              gScrVmPub.function_frame->fs.startTop = localFs.startTop;
              localFs.pos = tempCodePos;
              stackOff = Scr_ReadUnsigned(&gScrVmPub.function_frame->fs.pos);
              localFs.startTop = &localFs.top[-stackOff];
              goto thread_call;
            }
            gScrVarPub.error_index = 1;
            gFs = localFs;
            Scr_Error("script stack overflow (too many embedded function calls)", false);
          }
          gFs = localFs;
          Scr_Errorf("%s is not a function pointer", var_typename[localFs.top->type]);
$LN180_0:
          if ( localFs.top->type == VAR_BEGIN_REF )
          {
            if ( gScrVmPub.function_count < 31 )
            {
              localFs.localId = AllocThread(localFs.top->u.stringValue);
              --localFs.top;
              gScrVmPub.function_frame->fs.pos = localFs.pos;
              gScrVmPub.function_frame->fs.startTop = localFs.startTop;
              localFs.pos = Scr_ReadCodePos(&gScrVmPub.function_frame->fs.pos);
              stackOff = Scr_ReadUnsigned(&gScrVmPub.function_frame->fs.pos);
              localFs.startTop = &localFs.top[-stackOff];
              goto thread_call;
            }
            gScrVarPub.error_index = 1;
            gFs = localFs;
            Scr_Error("script stack overflow (too many embedded function calls)", false);
          }
        }
        goto not_an_object2;
      case OP_ScriptThreadCall:
        goto $LN187;
      case OP_ScriptThreadCallPointer:
        goto $LN184_0;
      case OP_ScriptMethodThreadCall:
        goto $LN180_0;
      case OP_ScriptMethodThreadCallPointer:
        if ( localFs.top->type != VAR_FUNCTION )
        {
          RemoveRefToValue(localFs.top--);
          gFs = localFs;
          Scr_Errorf("%s is not a function pointer", var_typename[localFs.top[1].type]);
$LN169:
          RemoveRefToValue(localFs.top);
          goto loop_dec_top;
        }
        tempCodePos = localFs.top->u.codePosValue;
        --localFs.top;
        if ( localFs.top->type != VAR_BEGIN_REF )
        {
          goto not_an_object2;
        }
        if ( gScrVmPub.function_count >= 31 )
        {
          gScrVarPub.error_index = 1;
          gFs = localFs;
          Scr_Error("script stack overflow (too many embedded function calls)", false);
not_an_object2:
          type = localFs.top->type;
          goto not_an_object_error2;
        }
        localFs.localId = AllocThread(localFs.top->u.stringValue);
        --localFs.top;
        gScrVmPub.function_frame->fs.pos = localFs.pos;
        gScrVmPub.function_frame->fs.startTop = localFs.startTop;
        localFs.pos = tempCodePos;
        stackOff = Scr_ReadUnsigned(&gScrVmPub.function_frame->fs.pos);
        localFs.startTop = &localFs.top[-stackOff];
thread_call:
        gScrVmPub.function_frame->fs.top = localFs.startTop;
        gScrVmPub.function_frame->topType = localFs.startTop->type;
        localFs.startTop->type = VAR_PRECODEPOS;
        ++gThreadCount;
function_call:
        gScrVmPub.function_frame->fs.localVarCount = localFs.localVarCount;
        localFs.localVarCount = 0;
        ++gScrVmPub.function_count;
        ++gScrVmPub.function_frame;
        gScrVmPub.function_frame->fs.localId = localFs.localId;
        assert(localFs.pos);
        continue;
      case OP_DecTop:
        goto $LN169;
      case OP_CastFieldObject:
        objectId = Scr_EvalFieldObject(gScrVarPub.tempVariable, localFs.top);
        goto loop_dec_top;
      case OP_EvalLocalVariableObjectCached:
        objectId = Scr_EvalVariableObject(Scr_GetLocalVar(localFs.pos));
        ++localFs.pos;
        continue;
      case OP_CastBool:
        Scr_CastBool(localFs.top);
        continue;
      case OP_BoolNot:
        Scr_EvalBoolNot(localFs.top);
        continue;
      case OP_BoolComplement:
        Scr_EvalBoolComplement(localFs.top);
        continue;
      case OP_JumpOnFalse:
        Scr_CastBool(localFs.top);
        assert(localFs.top->type == VAR_INTEGER);
        jumpOffset = Scr_ReadUnsignedShort(&localFs.pos);
        if ( !localFs.top->u.intValue )
        {
          localFs.pos += jumpOffset;
        }
        goto loop_dec_top;
      case OP_JumpOnTrue:
        Scr_CastBool(localFs.top);
        assert(localFs.top->type == VAR_INTEGER);
        jumpOffset = Scr_ReadUnsignedShort(&localFs.pos);
        if ( localFs.top->u.intValue )
        {
          localFs.pos += jumpOffset;
        }
        goto loop_dec_top;
      case OP_JumpOnFalseExpr:
        Scr_CastBool(localFs.top);
        assert(localFs.top->type == VAR_INTEGER);
        jumpOffset = Scr_ReadUnsignedShort(&localFs.pos);
        if ( localFs.top->u.intValue )
        {
          goto loop_dec_top;
        }
        localFs.pos += jumpOffset;
        continue;
      case OP_JumpOnTrueExpr:
        Scr_CastBool(localFs.top);
        assert(localFs.top->type == VAR_INTEGER);
        jumpOffset = Scr_ReadUnsignedShort(&localFs.pos);
        if ( !localFs.top->u.intValue )
        {
          goto loop_dec_top;
        }
        localFs.pos += jumpOffset;
        continue;
      case OP_jump:
        jumpOffset = Scr_ReadUnsigned(&localFs.pos);
        localFs.pos += jumpOffset;
        continue;
      case OP_jumpback:
        /*
        //Variable count is unknown
        if ( gScrVarPub.numScriptValues > 0x3F37E || gScrVarPub.numScriptObjects > 0x737E )
        {
          if ( gScrVmPub.showError )
          {
            Scr_DumpScriptThreads(inst);
            Scr_DumpScriptVariablesDefault(inst);
            gFs = localFs;
            Scr_Error(inst, "exceeded maximum number of script variables", 0);
          }
          Sys_Error("exceeded maximum number of script variables");
        }
        */

        if ( (int)(Sys_Milliseconds() - gScrVmGlob.starttime) >= 2500 )
        {
          assert(logScriptTimes);
          if ( logScriptTimes->current.enabled )
          {
            Com_Printf(CON_CHANNEL_PARSERSCRIPT, "EXCEED TIME: %d\n", Sys_Milliseconds());
          }
          if ( !gScrVmGlob.loading )
          {
            if ( Scr_IgnoreInfiniteLoopError() )
            {
              goto ignore_error;
            }
            VM_PrintJumpHistory( );
            if ( gScrVmPub.showError )
            {
              assert(!gScrVmPub.debugCode);
              Scr_DumpScriptThreads( );
              Scr_DumpScriptVariablesDefault( );
              gFs = localFs;
              Scr_Error("potential infinite loop in script", false);
            }
            if ( !gScrVmPub.abort_on_error )
            {
              /*
              if ( inst == SCRIPTINSTANCE_CLIENT )
              {
                Com_PrintError(CON_CHANNEL_PARSERSCRIPT, "%s script runtime error: potential infinite loop in script - killing thread.\n", "client");
              }
              else*/
              {
                Com_PrintError(CON_CHANNEL_PARSERSCRIPT, "%s script runtime error: potential infinite loop in script - killing thread.\n", "server");
              }
              Scr_PrintPrevCodePos(CON_CHANNEL_PARSERSCRIPT, localFs.pos, 0);
              Scr_ResetTimeout( );
              while ( 1 )
              {
                parentLocalId = GetSafeParentLocalId(localFs.localId);
                Scr_KillThread(localFs.localId);
                gScrVmPub.localVars -= localFs.localVarCount;
                assertint(localFs.top->type != VAR_PRECODEPOS, localFs.top - gScrVmPub.stack);
  
                while ( localFs.top->type != VAR_CODEPOS )
                {
                  RemoveRefToValue(localFs.top);
                  localFs.top--;
                  assertint(localFs.top->type != VAR_PRECODEPOS, localFs.top - gScrVmPub.stack);

                }
                --gScrVmPub.function_count;
                --gScrVmPub.function_frame;
                if ( !parentLocalId )
                {
                  break;
                }
                assert(localFs.top != localFs.startTop);

                RemoveRefToObject(localFs.localId);
                assertint(localFs.top->type == VAR_CODEPOS, localFs.top - gScrVmPub.stack);

                localFs.pos = gScrVmPub.function_frame->fs.pos;
                assert(localFs.pos);

                localFs.localVarCount = gScrVmPub.function_frame->fs.localVarCount;
                localFs.localId = parentLocalId;
                --localFs.top;
              }
              assertint(localFs.top == localFs.startTop, localFs.top - localFs.startTop);
              goto thread_end;
            }
            Scr_Error("potential infinite loop in script", false);
$LN142:
            assert(localFs.top >= gScrVmPub.stack);
            assert(localFs.top+1 <= gScrVmPub.maxstack);

            localFs.top[1] = Scr_EvalVariableField(fieldValueId);
            if ( localFs.top[1].type == VAR_INTEGER )
            {
              ++localFs.top[1].u.intValue;
              assert(localFs.pos[0] == OP_SetVariableField);
            }
            else
            {
              ++localFs.top;
              gFs = localFs;
              Scr_Errorf("++ must be applied to an int (applied to %s)", var_typename[localFs.top->type]);
$LN140_0:
              assert(localFs.top >= gScrVmPub.stack);
              assert(localFs.top+1 <= gScrVmPub.maxstack);

              localFs.top[1] = Scr_EvalVariableField(fieldValueId);
              if ( localFs.top[1].type != VAR_INTEGER )
              {
                ++localFs.top;
                gFs = localFs;
                Scr_Errorf("-- must be applied to an int (applied to %s)", var_typename[localFs.top->type]);
$LN138:
                Scr_EvalOr(localFs.top - 1, localFs.top);
                goto loop_dec_top;
              }
              --localFs.top[1].u.intValue;
              assert(localFs.pos[0] == OP_SetVariableField);
            }
            ++localFs.pos;
            SetVariableFieldValue(fieldValueId, ++localFs.top);
loop_dec_top:
            --localFs.top;
            continue;
          }
          if ( gScrVmPub.abort_on_error )
          {
            gScrVmPub.showError = true;
          }
ignore_error:
          Com_PrintWarning(CON_CHANNEL_PARSERSCRIPT, "script runtime warning: potential infinite loop in script.\n");
          Scr_PrintPrevCodePos(CON_CHANNEL_PARSERSCRIPT, localFs.pos, 0);
          jumpOffset = Scr_ReadUnsignedShort(&localFs.pos);
          localFs.pos -= jumpOffset;
          Scr_ResetTimeout( );
        }
        else
        {
          gScrVmDebugPub.jumpbackHistory[gScrVmDebugPub.jumpbackHistoryIndex] = localFs.pos;
          gScrVmDebugPub.jumpbackHistoryIndex = (gScrVmDebugPub.jumpbackHistoryIndex + 1) % 0x80u;
          jumpOffset = Scr_ReadUnsignedShort(&localFs.pos);
          localFs.pos -= jumpOffset;
        }
        continue;
      case OP_inc:
        goto $LN142;
      case OP_dec:
        goto $LN140_0;
      case OP_bit_or:
        goto $LN138;
      case OP_bit_ex_or:
        Scr_EvalExOr(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_bit_and:
        Scr_EvalAnd(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_equality:
        Scr_EvalEquality(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_inequality:
        Scr_EvalInequality(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_less:
        Scr_EvalLess(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_greater:
        Scr_EvalGreater(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_less_equal:
        Scr_EvalLessEqual(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_greater_equal:
        Scr_EvalGreaterEqual(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_shift_left:
        Scr_EvalShiftLeft(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_shift_right:
        Scr_EvalShiftRight(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_plus:
        Scr_EvalPlus(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_minus:
        Scr_EvalMinus(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_multiply:
        Scr_EvalMultiply(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_divide:
        Scr_EvalDivide(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_mod:
        Scr_EvalMod(localFs.top - 1, localFs.top);
        goto loop_dec_top;
      case OP_size:
        Scr_EvalSizeValue(localFs.top);
        continue;
      case OP_waittillmatch:
      case OP_waittill:
        assert(Scr_IsInOpcodeMemory( localFs.pos ));

        if ( localFs.top->type != VAR_BEGIN_REF )
        {
          goto not_an_object2;
        }
        if ( !IsFieldObject(localFs.top->u.pointerValue) )
        {
          goto not_an_object2a;
        }
        tempValue.u.intValue = localFs.top->u.intValue;
        --localFs.top;
        if ( localFs.top->type != VAR_STRING )
        {
          ++localFs.top;
          gScrVarPub.error_index = 3;
          gFs = localFs;
          Scr_Error("first parameter of waittill must evaluate to a string", false);
not_an_object2a:
          type = Scr_GetObjectType(localFs.top->u.stringValue);
not_an_object_error2:
          gScrVarPub.error_index = 2;
not_an_object_error:
          gFs = localFs;
          Scr_Errorf("%s is not an object", var_typename[type]);
          goto error_1;
        }
        stringValue = localFs.top->u.stringValue;
        --localFs.top;
        assert(Scr_GetObjectType( tempValue.u.pointerValue ) != VAR_THREAD);
        assert(Scr_GetObjectType( tempValue.u.pointerValue ) != VAR_NOTIFY_THREAD);
        assert(Scr_GetObjectType( tempValue.u.pointerValue ) != VAR_TIME_THREAD);
        assert(Scr_GetObjectType( tempValue.u.pointerValue ) != VAR_CHILD_THREAD);
        assert(Scr_GetObjectType( tempValue.u.pointerValue ) != VAR_DEAD_THREAD);

        stackValue.type = VAR_STACK;
        stackValue.u.stackValue = VM_ArchiveStack(&localFs);
        id = GetArray(GetVariable(GetArray(GetVariable(tempValue.u.stringValue, 0x18000u)), stringValue));
        stackId = GetNewObjectVariable(id, localFs.localId);
        SetNewVariableValue(stackId, &stackValue);
        tempValue.type = VAR_POINTER;
        ObjectVariable = GetObjectVariable(gScrVarPub.pauseArrayId, Scr_GetSelf(localFs.localId));
        id = GetNewObjectVariable(GetArray(ObjectVariable), localFs.localId);
        SetNewVariableValue(id, &tempValue);
        Scr_SetThreadNotifyName(localFs.localId, stringValue);
        goto thread_end;

      case OP_notify:
        if ( localFs.top->type != VAR_POINTER )
        {
          goto not_an_object2;
        }
        id = localFs.top->u.stringValue;
        if ( !IsFieldObject(id) )
        {
          goto not_an_object2a;
        }
        --localFs.top;
        if ( localFs.top->type != VAR_STRING )
        {
          ++localFs.top;
          gScrVarPub.error_index = 1;
          gFs = localFs;
          Scr_Error("first parameter of notify must evaluate to a string", false);
          goto not_an_object2a;
        }
        stringValue = localFs.top->u.stringValue;
        --localFs.top;
        if ( gScrVmDebugPub.checkBreakon )
        {
          Scr_CheckBreakonNotify(id, stringValue, localFs.top, localFs.pos, localFs.localId);
        }
        gScrVmPub.function_frame->fs.pos = localFs.pos;
        VM_Notify(id, stringValue, localFs.top);
        localFs.pos = gScrVmPub.function_frame->fs.pos;
        RemoveRefToObject(id);
        SL_RemoveRefToString(stringValue);
        assertint(localFs.top->type != VAR_CODEPOS, localFs.top - gScrVmPub.stack);

        while ( localFs.top->type != VAR_PRECODEPOS )
        {
          RemoveRefToValue(localFs.top);
          localFs.top--;
          assertint(localFs.top->type != VAR_CODEPOS, localFs.top - gScrVmPub.stack);
        }
        goto loop_dec_top;
      case OP_endon:
        if ( localFs.top->type != VAR_POINTER )
        {
          goto not_an_object1;
        }
        if ( !IsFieldObject(localFs.top->u.pointerValue) )
        {
          goto LABEL_633;
        }
        if ( localFs.top[-1].type == VAR_STRING )
        {
          stringValue = localFs.top[-1].u.stringValue;
          AddRefToObject(localFs.localId);
          threadId = AllocThread(localFs.localId);
          assert(Scr_GetObjectType( localFs.top->u.pointerValue ) != VAR_THREAD);
          assert(Scr_GetObjectType( localFs.top->u.pointerValue ) != VAR_NOTIFY_THREAD);
          assert(Scr_GetObjectType( localFs.top->u.pointerValue ) != VAR_TIME_THREAD);
          assert(Scr_GetObjectType( localFs.top->u.pointerValue ) != VAR_CHILD_THREAD);
          assert(Scr_GetObjectType( localFs.top->u.pointerValue ) != VAR_DEAD_THREAD);

          GetObjectVariable(GetArray(GetVariable(GetArray(GetVariable(localFs.top->u.stringValue, 0x18000u)), stringValue)), threadId);
          RemoveRefToObject(threadId);
          tempValue.type = VAR_POINTER;
          tempValue.u.pointerValue = localFs.top->u.pointerValue;
          SetNewVariableValue(GetNewObjectVariable(GetArray(GetObjectVariable(gScrVarPub.pauseArrayId, localFs.localId)), threadId), &tempValue);
          Scr_SetThreadNotifyName(threadId, stringValue);
          localFs.top -= 2;
          continue;
        }
        gFs = localFs;
        Scr_Error("first parameter of endon must evaluate to a string", false);
LABEL_633:
        type = Scr_GetObjectType(localFs.top->u.pointerValue);
not_an_object_error1:
        gScrVarPub.error_index = 1;
        goto not_an_object_error;
      case OP_voidCodepos:
        assert(localFs.top >= gScrVmPub.stack);
        assert(localFs.top+1 <= gScrVmPub.maxstack);
        ++localFs.top;
        localFs.top[0].type = VAR_PRECODEPOS;
        continue;
      case OP_switch:
        jumpOffset = Scr_ReadUnsigned(&localFs.pos);
        localFs.pos += jumpOffset;
        gCaseCount = Scr_ReadUnsignedShort(&localFs.pos);
        if ( localFs.top->type == VAR_STRING )
        {
          goto LABEL_647;
        }
        if ( localFs.top->type == VAR_INTEGER )
        {
          if ( IsValidArrayIndex(localFs.top->u.pointerValue) )
          {
            caseValue = GetInternalVariableIndex(localFs.top->u.pointerValue);
          }
          else
          {
            gFs = localFs;
            Scr_Errorf("switch index %d out of range", localFs.top->u.intValue);
LABEL_647:
            caseValue = localFs.top->u.stringValue;
            SL_RemoveRefToString(localFs.top->u.stringValue);
          }
        }
        else
        {
          gFs = localFs;
          Scr_Errorf("cannot switch on %s", var_typename[localFs.top->type]);
        }
        if ( !gCaseCount )
        {
          goto loop_dec_top;
        }
        assert(caseValue);
        do
        {
          currentCaseValue = Scr_ReadUnsigned(&localFs.pos);
          currentCodePos = Scr_ReadCodePos(&localFs.pos);
          if ( currentCaseValue == caseValue )
          {
            localFs.pos = currentCodePos;
            assert(localFs.pos);
            goto loop_dec_top;
          }
          --gCaseCount;
        }
        while ( gCaseCount );
        if ( !currentCaseValue )
        {
          localFs.pos = currentCodePos;
          assert(localFs.pos);
        }
        goto loop_dec_top;
      case OP_endswitch:
        gCaseCount = Scr_ReadUnsignedShort(&localFs.pos);
        Scr_ReadIntArray(&localFs.pos, 2 * gCaseCount);
        continue;
      case OP_vector:
        localFs.top -= 2;
        Scr_CastVector(localFs.top);
        continue;
      case OP_NOP:
        continue;
      case OP_abort:
        assertint(g_script_error_level >= 0, g_script_error_level);
        --g_script_error_level;
        gFs = localFs;
        return 0;
      case OP_object:
        assert(localFs.top >= gScrVmPub.stack);
        assert(localFs.top <= gScrVmPub.maxstack);
        classnum = Scr_ReadUnsigned(&localFs.pos);
        entnum = Scr_ReadUnsigned(&localFs.pos);
        EntityId = FindEntityId(entnum, classnum);
        localFs.top[1].u.intValue = EntityId;
        if ( localFs.top[1].u.intValue )
        {
          ++localFs.top;
        }
        else
        {
          ++localFs.top;
          localFs.top[0].type = VAR_UNDEFINED;
          gFs = localFs;
          Scr_Error("unknown object", false);
        }
        goto object;
      case OP_thread_object:
        assert(localFs.top >= gScrVmPub.stack);
        assert(localFs.top+1 <= gScrVmPub.maxstack);

        UnsignedShort = Scr_ReadUnsignedShort(&localFs.pos);
        ++localFs.top;
        localFs.top[0].u.intValue = UnsignedShort;
object:
        localFs.top->type = VAR_POINTER;
        AddRefToObject(localFs.top->u.pointerValue);
        continue;
      case OP_EvalLocalVariable:
        assert(localFs.top >= gScrVmPub.stack);
        assert(localFs.top+1 <= gScrVmPub.maxstack);
        ++localFs.top;
        localFs.top[0] = Scr_EvalVariable(FindVariable(localFs.localId, Scr_ReadUnsignedShort(&localFs.pos)));
        continue;
      case OP_EvalLocalVariableRef:
        fieldValueIndex = 0;
        fieldValueId = FindVariable(localFs.localId, Scr_ReadUnsignedShort(&localFs.pos));
        if ( fieldValueId )
        {
          continue;
        }
        gFs = localFs;
        Scr_Error("cannot create a new local variable in the debugger", false);
      case OP_prof_begin:
        ++localFs.pos;
        continue;
      case OP_prof_end:
        ++localFs.pos;
        continue;
      case OP_breakpoint:
        if ( !gScrVarPub.developer )
        {
          continue;
        }
        gOpcode = Scr_HitBreakpoint(localFs.top, localFs.pos, localFs.localId, 0);
        goto interrupt_return;
      case OP_assignmentBreakpoint:
        gOpcode = Scr_HitAssignmentBreakpoint(localFs.top, localFs.pos, localFs.localId, 0);
        goto interrupt_return;
      case OP_manualAndAssignmentBreakpoint:
        gOpcode = Scr_HitAssignmentBreakpoint(localFs.top, localFs.pos, localFs.localId, 1);
        goto interrupt_return;
      default:
        gScrVmPub.terminal_error = 1;
        RuntimeError(localFs.pos, 0, va("CODE ERROR: unknown opcode %d", gOpcode), NULL);
        continue;
    }
  }
}