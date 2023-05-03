#include "cscr_compiler.h"
#include "cscr_stringlist.h"
#include "cscr_animtree.h"
#include "cscr_parsertree.h"
#include "cscr_main.h"
#include "cscr_debugger.h"
#include "cscr_vm.h"
#include <common/qcommon_mem.h>


scrCompileGlob_t gScrCompileGlob;
scrCompilePub_t gScrCompilePub;

#define SCR_DEV_NO 0

#if 0

void Scr_CompileRemoveRefToString(unsigned int stringValue)
{
    assert(stringValue);
  if ( !gScrCompileGlob.bConstRefCount && gScrCompilePub.developer_statement != 3 )
  {
    SL_RemoveRefToString(stringValue);
  }
}


void AddFilePrecache(unsigned int filename, unsigned int sourcePos, bool include, unsigned int *filePosId, unsigned int *fileCountId)
{
    unsigned int Variable;

    assert(gScrCompileGlob.precachescriptList);
    SL_AddRefToString(filename);
    Scr_CompileRemoveRefToString(filename);
    gScrCompileGlob.precachescriptList->filename = filename;
    gScrCompileGlob.precachescriptList->sourcePos = sourcePos;
    gScrCompileGlob.precachescriptList->include = include;
    ++gScrCompileGlob.precachescriptList;
    if ( !include )
    {
        Variable = GetVariable(gScrCompilePub.scriptsPos, filename);
        *filePosId = GetObject(Variable);
        *fileCountId = GetObject(GetVariable(gScrCompilePub.scriptsCount, filename));
    }
}


void EmitInclude(sval_u val)
{
    unsigned int filename;

    assert(val.node[0].type == ENUM_include);

    filename = Scr_CreateCanonicalFilename(SL_ConvertToString(val.block->localVarsCreateCount));
    Scr_CompileRemoveRefToString(val.block->localVarsCreateCount);
    AddFilePrecache(filename, val.block->localVarsPublicCount, 1, 0, 0);
}

void EmitIncludeList(sval_u val)
{
  sval_u *node;

  for ( node = val.node->node[1].node; node; node = node[1].node )
  {
    EmitInclude(*node);
  }
}

void LinkFile(unsigned int filePosId, unsigned int fileCountId)
{
  unsigned int threadCountId;
  VariableValue pos;
  unsigned int threadCountPtr;
  unsigned int posId;
  VariableValue emptyValue;
  unsigned int nameId;

  emptyValue.type = 0;
  emptyValue.u.intValue = 0;
  for ( threadCountPtr = FindFirstSibling(fileCountId); threadCountPtr; threadCountPtr = FindNextSibling(threadCountPtr) )
  {
    threadCountId = FindObject(threadCountPtr);
    assert(threadCountId);

    nameId = GetVariableName(threadCountPtr);
    posId = FindVariable(filePosId, nameId);
    if ( posId )
    {
      pos = Scr_EvalVariable(posId);
      assert(pos.type == VAR_CODEPOS || pos.type == VAR_DEVELOPER_CODEPOS);
      assert(pos.u.codePosValue);

      LinkThread(threadCountId, &pos, 1);
    }
    else
    {
      LinkThread(threadCountId, &emptyValue, 1);
    }
  }
  ClearObject(fileCountId);
}

void CheckThreadPosition(unsigned int posId, unsigned int name, unsigned int sourcePos)
{
  char *buf;
  VariableValue pos;
  assert(!gScrVarPub.evaluate);

  pos = Scr_EvalVariable(posId);
  if ( pos.type )
  {
    if ( pos.u.intValue )
    {
      buf = gScrParserPub.sourceBufferLookup[Scr_GetSourceBuffer(pos.u.codePosValue)].buf;
      CompileError(sourcePos, "function '%s' already defined in '%s'", SL_ConvertToString(name), buf);
    }
    else
    {
      CompileError(sourcePos, "function '%s' already defined", SL_ConvertToString(name));
    }
  }
}

void Scr_CalcLocalVarsStatementList(sval_u val, scr_block_s *block)
{
  sval_u *node;

  for ( node = val.node->node[1].node; node; node = node[1].node )
  {
    Scr_CalcLocalVarsStatement(node[0], block);
  }
}

void Scr_CheckLocalVarsCount(int localVarsCount)
{
  if ( localVarsCount >= 64 )
  {
    Com_Error(ERR_DROP, "LOCAL_VAR_STACK_SIZE exceeded");
  }
}

void Scr_RegisterLocalVar(unsigned int name, sval_u sourcePos, scr_block_s *block)
{
  int i;

  if ( !block->abortLevel )
  {
    for ( i = 0; i < block->localVarsCount; ++i )
    {
      if ( block->localVars[i].name == name )
      {
        return;
      }
    }
    Scr_CheckLocalVarsCount(block->localVarsCount);
    block->localVars[block->localVarsCount].name = name;
    block->localVars[block->localVarsCount++].sourcePos = sourcePos.stringValue;
  }
}

void Scr_CalcLocalVarsSafeSetVariableField(sval_u expr, sval_u sourcePos, scr_block_s *block)
{
  Scr_RegisterLocalVar(expr.stringValue, sourcePos, block);
}

void Scr_CalcLocalVarsFormalParameterListInternal(sval_u *node, scr_block_s *block)
{
  for(node = node[1].node; node; node = node[1].node)
  {
    Scr_CalcLocalVarsSafeSetVariableField(node->node[0], node->node[1], block);
  }
}

void Scr_CalcLocalVarsFormalParameterList(sval_u exprlist, scr_block_s *block)
{
  Scr_CalcLocalVarsFormalParameterListInternal(exprlist.node->node, block);
}

void Scr_CalcLocalVarsThread(sval_u exprlist, sval_u stmtlist, sval_u *stmttblock)
{
  gScrCompileGlob.forceNotCreate = 0;
  stmttblock->block = (scr_block_s*)Hunk_AllocateTempMemoryHigh(sizeof(scr_block_s)/*, "Scr_CalcLocalVarsThread"*/);
  stmttblock->block->abortLevel = 0;
  stmttblock->block->localVarsCreateCount = 0;
  stmttblock->block->localVarsCount = 0;
  stmttblock->block->localVarsPublicCount = 0;
  memset(stmttblock->block->localVarsInitBits, 0, sizeof(stmttblock->block->localVarsInitBits));
  Scr_CalcLocalVarsFormalParameterList(exprlist, stmttblock->block);
  Scr_CalcLocalVarsStatementList(stmtlist, stmttblock->block);
}




void EmitEnd( )
{
  EmitOpcode(0, 0, 0);
  EmitPreAssignmentPos( );
}

void InitThread(int type)
{
  gScrCompileGlob.currentCaseStatement = 0;
  gScrCompileGlob.bCanBreak = 0;
  gScrCompileGlob.currentBreakStatement = 0;
  gScrCompileGlob.bCanContinue = 0;
  gScrCompileGlob.currentContinueStatement = 0;
  gScrCompileGlob.breakChildBlocks = 0;
  gScrCompileGlob.continueChildBlocks = 0;
  if ( gScrCompileGlob.firstThread[type] )
  {
    gScrCompileGlob.firstThread[type] = 0;
    EmitEnd( );
    AddOpcodePos(0, 0);
    AddOpcodePos(0xFFFFFFFE, 0);
  }
}

void SetThreadPosition(unsigned int posId)
{
  GetVariableValueAddress(posId)->u.codePosValue = (const char*)TempMalloc(0);
}

void CompileTransferRefToString(unsigned int stringValue, unsigned int user)
{
  assert(stringValue);

  if ( gScrCompilePub.developer_statement == 2 )
  {
    Scr_CompileRemoveRefToString(stringValue);
  }
  else if ( gScrCompilePub.developer_statement != 3 )
  {
    if ( gScrCompileGlob.bConstRefCount )
    {
      SL_AddRefToString(stringValue);
    }
    SL_TransferRefToUser(stringValue, user);
  }
}



bool Scr_IsLastStatement(sval_u *node)
{
  if ( !node )
  {
    return true;
  }
  if ( gScrVarPub.developer_script )
  {
    return false;
  }
  while ( node )
  {
    if ( node->codePosValue[0] != OP_ClearFieldVariable )
    {
      return false;
    }
    node = node[1].node;
  }
  return true;
}

void EmitByte(char value)
{
  gScrCompileGlob.codePos = (char*)TempMalloc(1);
  gScrCompileGlob.codePos[0] = value;
}

void EmitAssignmentPos( )
{
  char *pos;

  if ( gScrVarPub.developer && gScrCompilePub.developer_statement != 3 )
  {
    pos = (char *)TempMalloc(0);
    Scr_AddAssignmentPos(pos);
  }
}

void EmitSafeSetVariableField(sval_u expr, sval_u sourcePos, scr_block_s *block)
{
  int index;

  index = Scr_FindLocalVarIndex(expr.sourcePosValue, sourcePos, 1, block);
  EmitOpcode((index != 0) + OP_SafeSetVariableFieldCached0, 0, 0);
  EmitPreAssignmentPos( );
  if ( index )
  {
    EmitByte(index);
  }
  AddOpcodePos(sourcePos.sourcePosValue, 0);
  EmitAssignmentPos( );
}

void EmitFormalParameterListInternal(sval_u *node, scr_block_s *block)
{
  for(node = node[1].node; node; node = node[1].node)
  {
    EmitSafeSetVariableField(node->node[0], node->node[1], block);
  }
}

void EmitFormalParameterList(sval_u exprlist, sval_u sourcePos, scr_block_s *block)
{
  EmitFormalParameterListInternal(exprlist.node->node, block);
  EmitOpcode(OP_checkclearparams, 0, 0);
  AddOpcodePos(sourcePos.stringValue, 0);
}

void EmitStatementList(sval_u val, bool lastStatement, unsigned int endSourcePos, scr_block_s *block)
{
  sval_u *node;
  sval_u *nextNode;

  for ( node = val.node->node[1].node; node; node = nextNode )
  {
    nextNode = node[1].node;
    if ( lastStatement && Scr_IsLastStatement(nextNode) )
    {
      EmitStatement(node[0], 1, endSourcePos, block);
    }
    else
    {
      EmitStatement(node[0], 0, endSourcePos, block);
    }
  }
}

void EmitThreadInternal(sval_u *val, sval_u sourcePos, sval_u endSourcePos, scr_block_s *block)
{
  AddThreadStartOpcodePos(sourcePos.stringValue);
  gScrCompileGlob.cumulOffset = 0;
  gScrCompileGlob.maxOffset = 0;
  gScrCompileGlob.maxCallOffset = 0;
  CompileTransferRefToString(val[1].stringValue, 2u);
  EmitFormalParameterList(val[2], sourcePos, block);
  EmitStatementList(val[3], 1, endSourcePos.stringValue, block);
  EmitEnd( );
  AddOpcodePos(endSourcePos.stringValue, 1);
  AddOpcodePos(0xFFFFFFFE, 0);
  assert(!gScrCompileGlob.cumulOffset);

  if ( gScrCompileGlob.maxOffset + 32 * gScrCompileGlob.maxCallOffset >= 2048 )
  {
    CompileError(sourcePos.sourcePosValue, "function exceeds operand stack size");
  }
}

void EmitDeveloperThread(sval_u *val, sval_u *stmttblock)
{
  unsigned int posId;
  unsigned int savedChecksum;
  char *begin_pos;

  assert(gScrCompilePub.developer_statement == SCR_DEV_NO);

  if ( gScrVarPub.developer_script )
  {
    gScrCompilePub.developer_statement = 1;
    InitThread(1);
    posId = FindVariable(gScrCompileGlob.filePosId, val[1].stringValue);
    SetThreadPosition(posId);
    EmitThreadInternal(val, val[4], val[5], stmttblock->block);
  }
  else
  {
    begin_pos = (char*)TempMalloc(0);
    savedChecksum = gScrVarPub.checksum;
    gScrCompilePub.developer_statement = 2;
    InitThread(1);
    EmitThreadInternal(val, val[4], val[5], stmttblock->block);
    TempMemorySetPos(begin_pos);
    gScrVarPub.checksum = savedChecksum;
  }
  gScrCompilePub.developer_statement = 0;
}

void EmitNormalThread(sval_u *val, sval_u *stmttblock)
{
  unsigned int posId;

  InitThread(0);
  posId = FindVariable(gScrCompileGlob.filePosId, val[1].stringValue);
  SetThreadPosition(posId);
  EmitThreadInternal(val, val[4], val[5], stmttblock->block);
}

void EmitThread(sval_u *val)
{
  switch ( val->type )
  {
    case ENUM_thread:
      Scr_CalcLocalVarsThread(val[2], val[3], val + 6);
      if ( gScrCompileGlob.in_developer_thread )
      {
        EmitDeveloperThread(val, val + 6);
      }
      else
      {
        EmitNormalThread(val, val + 6);
      }
      break;
    case ENUM_begin_developer_thread:
      assert(!gScrCompileGlob.in_developer_thread);
      gScrCompileGlob.in_developer_thread = 1;
      break;
    case ENUM_end_developer_thread:
      assert(gScrCompileGlob.in_developer_thread);
      gScrCompileGlob.in_developer_thread = 0;
      break;
    case ENUM_usingtree:
      if ( gScrCompileGlob.in_developer_thread )
      {
        CompileError(val[2].sourcePosValue, "cannot put #using_animtree inside /# ... #/ comment");
      }
      else
      {
        Scr_UsingTree(SL_ConvertToString(val[1].stringValue), val[3].sourcePosValue);
        Scr_CompileRemoveRefToString(val[1].stringValue);
      }
      break;
    default:
      return;
  }
}

void SpecifyThread(sval_u *val)
{
  unsigned int Variable;
  char type;

  type = val->type;
  if ( val->type == ENUM_thread)
  {
    if ( !gScrCompileGlob.in_developer_thread || gScrVarPub.developer_script )
    {
      Variable = GetVariable(gScrCompileGlob.filePosId, val[1].stringValue);
      SpecifyThreadPosition(Variable, val[1].stringValue, val[4].sourcePosValue, gScrCompileGlob.in_developer_thread ? VAR_DEVELOPER_CODEPOS : VAR_CODEPOS);
    }
  }
  else if ( type == ENUM_begin_developer_thread )
  {
    if ( gScrCompileGlob.in_developer_thread )
    {
      CompileError(val[1].sourcePosValue, "cannot recurse /#");
    }
    else
    {
      gScrCompileGlob.in_developer_thread = 1;
      gScrCompileGlob.developer_thread_sourcePos = val[1].sourcePosValue;
    }
  }
  else if ( type == ENUM_end_developer_thread )
  {
    if ( gScrCompileGlob.in_developer_thread )
    {
      gScrCompileGlob.in_developer_thread = 0;
    }
    else
    {
      CompileError(val[1].sourcePosValue, "#/ has no matching /#");
    }
  }
}

void EmitThreadList(sval_u val)
{
  sval_u *node;

  gScrCompileGlob.in_developer_thread = 0;
  for ( node = val.node->node[1].node; node; node = node[1].node )
  {
    SpecifyThread(node->node);
  }
  if ( gScrCompileGlob.in_developer_thread )
  {
    CompileError(gScrCompileGlob.developer_thread_sourcePos, "/# has no matching #/");
  }
  gScrCompileGlob.firstThread[0] = 1;
  gScrCompileGlob.firstThread[1] = 1;
  assert(!gScrCompileGlob.in_developer_thread);

  for ( node = val.node->node[1].node; node; node = node[1].node )
  {
    EmitThread(node->node);
  }
  assert(!gScrCompileGlob.in_developer_thread);

}

void EmitCodepos(const char *pos)
{
  gScrCompileGlob.codePos = (char *)TempMallocAlign(4);
  *(uint32_t *)gScrCompileGlob.codePos = (uint32_t)pos;
}

void EmitFunction(sval_u func, sval_u sourcePos)
{
  unsigned int Variable; // eax
  VariableValue pos; // [esp+58h] [ebp-50h]
  unsigned int threadCountId; // [esp+68h] [ebp-40h]
  unsigned int valueId; // [esp+6Ch] [ebp-3Ch]
  unsigned int fileCountId; // [esp+78h] [ebp-30h] BYREF
  unsigned int filename; // [esp+7Ch] [ebp-2Ch]
  unsigned int posId; // [esp+80h] [ebp-28h]
  unsigned int threadName; // [esp+84h] [ebp-24h]
  bool bExists; // [esp+8Bh] [ebp-1Dh]
  int scope; // [esp+8Ch] [ebp-1Ch]
  unsigned int countId; // [esp+90h] [ebp-18h]
  unsigned int filePosId; // [esp+94h] [ebp-14h] BYREF
  VariableValue count; // [esp+98h] [ebp-10h] BYREF
  VariableValue value; // [esp+A0h] [ebp-8h] BYREF

  if ( gScrCompilePub.developer_statement == 3 )
  {
    CompileError(sourcePos.stringValue, "cannot evaluate in the debugger");
    return;
  }
  if ( gScrCompilePub.developer_statement == 2 )
  {
    Scr_CompileRemoveRefToString(func.block->localVarsCreateCount);
    if ( func.node[0].type == ENUM_far_function )
    {
      Scr_CompileRemoveRefToString(func.block->localVarsPublicCount);
      --gScrCompilePub.far_function_count;
    }
    return;
  }
  if ( func.node[0].type == ENUM_local_function )
  {
    scope = 0;
    fileCountId = gScrCompileGlob.fileCountId;
    threadName = func.block->localVarsCreateCount;
    CompileTransferRefToString(threadName, 2u);
LABEL_36:
    EmitCodepos((const char *)scope);
    Variable = GetVariable(fileCountId, threadName);
    threadCountId = GetObject(Variable);

    assert(threadCountId);

    countId = GetVariable(threadCountId, 0);
    count = Scr_EvalVariable(countId);
    assert((count.type == VAR_UNDEFINED) || (count.type == VAR_INTEGER));

    if ( !count.type )
    {
      count.type = VAR_INTEGER;
      count.u.intValue = 0;
    }
    valueId = GetNewVariable(threadCountId, count.u.intValue + 1);
    value.u.intValue = (int)gScrCompileGlob.codePos;
    if ( gScrCompilePub.developer_statement )
    {
      assert(gScrVarPub.developer_script);
      value.type = VAR_DEVELOPER_CODEPOS;
    }
    else
    {
      value.type = VAR_CODEPOS;
    }
    SetNewVariableValue(valueId, &value);
    ++count.u.intValue;
    SetVariableValue(countId, &count);
    AddOpcodePos(sourcePos.stringValue, 0);
    return;
  }
  assert(func.node[0].type == ENUM_far_function);
  scope = 1;
  filename = Scr_CreateCanonicalFilename(SL_ConvertToString(func.block->localVarsCreateCount));
  Scr_CompileRemoveRefToString(func.block->localVarsCreateCount);
  value = Scr_EvalVariable(FindVariable(gScrCompilePub.loadedscripts, filename));
  bExists = value.type != 0;
  AddFilePrecache(filename, sourcePos.stringValue, 0, &filePosId, &fileCountId);
  threadName = func.block->localVarsPublicCount;
  CompileTransferRefToString(threadName, 2u);
  if ( !bExists )
  {
    goto LABEL_36;
  }
  posId = FindVariable(filePosId, threadName);
  if ( posId )
  {
    pos = Scr_EvalVariable(posId);
    assert((pos.type == VAR_CODEPOS || pos.type == VAR_DEVELOPER_CODEPOS));
    assert(pos.u.codePosValue);

    if ( pos.type == VAR_CODEPOS )
    {
      goto LABEL_23;
    }
    assert(pos.type == VAR_DEVELOPER_CODEPOS);
    assert(gScrVarPub.developer_script);
//    assert(gScrCompilePub.developer_statement != SCR_DEV_IGNORE); //2

    if ( gScrCompilePub.developer_statement )
    {
LABEL_23:
      EmitCodepos(pos.u.codePosValue);
    }
    else
    {
      CompileError(sourcePos.stringValue, "normal script cannot reference a function in a /# ... #/ comment");
    }
  }
  else
  {
    CompileError(sourcePos.stringValue, "unknown function");
  }
}





void ScriptCompile(sval_u val, unsigned int filePosId, unsigned int fileCountId, unsigned int scriptId, PrecacheEntry *entries, int entriesCount)
{
  unsigned int Variable;
  int j;
  VariableValue pos;
  uint16_t filename;
  PrecacheEntry *precachescript;
  int far_function_count;
  PrecacheEntry *precachescript2;
  unsigned int includeFilePosId;
  unsigned int toPosId;
  unsigned int posId;
  VariableValue includePos; 
  uint16_t name;
  unsigned int includePosId;
  PrecacheEntry *precachescriptList;
  int i;
  unsigned int toThreadCountId;
  unsigned int duplicateFilePosId;
  VariableValue value;

  gScrCompileGlob.filePosId = filePosId;
  gScrCompileGlob.fileCountId = fileCountId;
  gScrCompileGlob.bConstRefCount = 0;
  gScrAnimPub.animTreeIndex = 0;
  gScrCompilePub.developer_statement = 0;
  if ( gScrCompilePub.far_function_count )
  {
    precachescriptList = &entries[entriesCount];
  }
  else
  {
    precachescriptList = 0;
  }
  entriesCount += gScrCompilePub.far_function_count;
  if ( entriesCount > 1024 )
  {
    Com_Error(ERR_FATAL, "MAX_PRECACHE_ENTRIES exceeded.\nThis means that the script recursion is too deep.\nPlease see a coder.");
  }
  gScrCompileGlob.precachescriptList = precachescriptList;
  EmitIncludeList(val.node[0]);
  EmitThreadList(val.node[1]);
  gScrCompilePub.programLen = (const char*)TempMalloc(0) - gScrVarPub.programBuffer;
  Scr_ShutdownAllocNode( );
  Hunk_ClearTempMemoryHigh( );
  far_function_count = gScrCompileGlob.precachescriptList - precachescriptList;
  duplicateFilePosId = AllocObject( );
  for ( i = 0; i < far_function_count; ++i )
  {
    precachescript = &precachescriptList[i];
    filename = precachescript->filename;
    includeFilePosId = Scr_LoadScriptInternal(SL_ConvertToString(filename), entries, entriesCount);
    if ( !includeFilePosId )
    {
      CompileError(precachescript->sourcePos, "Could not find script '%s'", SL_ConvertToString(filename));
      return;
    }
    SL_RemoveRefToString(filename);
    if ( precachescript->include )
    {
      for ( j = i + 1; j < far_function_count; ++j )
      {
        precachescript2 = &precachescriptList[j];
        if ( !precachescript2->include )
        {
          break;
        }
        if ( precachescript2->filename == filename )
        {
          CompileError(precachescript2->sourcePos, "Duplicate #include");
          return;
        }
      }
      precachescript->include = 0;
      pos.type = VAR_CODEPOS;
      for ( includePosId = FindFirstSibling(includeFilePosId); includePosId; includePosId = FindNextSibling(includePosId) )
      {
        includePos = Scr_EvalVariable(includePosId);
        assert((includePos.type == VAR_CODEPOS) || (includePos.type == VAR_DEVELOPER_CODEPOS));
        name = GetVariableName(includePosId);
        posId = FindVariable(filePosId, name);
        if ( posId )
        {
          CheckThreadPosition(posId, name, precachescript->sourcePos);
        }
        toPosId = GetVariable(duplicateFilePosId, name);
        CheckThreadPosition(toPosId, name, precachescript->sourcePos);
        pos.u.intValue = GetVariableValueAddress(includePosId)->u.pointerValue;
        SetNewVariableValue(toPosId, &pos);
        Variable = GetVariable(fileCountId, name);
        toThreadCountId = GetObject(Variable);
        LinkThread(toThreadCountId, &includePos, 0);
        RemoveVariable(fileCountId, name);
      }
    }
  }
  ClearObject(duplicateFilePosId);
  RemoveRefToEmptyObject(duplicateFilePosId);
  LinkFile(filePosId, fileCountId);
  value.type = VAR_INTEGER;
  SetVariableValue(scriptId, &value);
}

#endif