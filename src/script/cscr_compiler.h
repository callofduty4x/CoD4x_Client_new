#ifndef SCRIPT_CSCR_COMPILER_H_
#define SCRIPT_CSCR_COMPILER_H_
#include <q_shared.h>
#include "cscr_parser.h"
#include "scr_shared.h"
#include "cscr_variable.h"

struct scrCompilePub_t
{
  int value_count;
  int far_function_count;
  unsigned int loadedscripts;
  unsigned int scriptsPos;
  unsigned int builtinFunc;
  unsigned int builtinMeth;
  uint16_t canonicalStrings[65536];
  const char *in_ptr;
  const char *parseBuf;
  byte script_loading;
  byte allowedBreakpoint;
  int16_t pad;
  int developer_statement;
  char *opcodePos;
  unsigned int programLen;
  int func_table_size;
  int func_table[1024];
  //unsigned int scriptsCount;
};

struct CaseStatementInfo
{
  unsigned int name;
  const char *codePos;
  unsigned int sourcePos;
  CaseStatementInfo *next;
};

struct BreakStatementInfo
{
  const char *codePos;
  const char *nextCodePos;
  BreakStatementInfo *next;
};

struct ContinueStatementInfo
{
  const char *codePos;
  const char *nextCodePos;
  ContinueStatementInfo *next;
};


struct VariableCompileValue
{
  VariableValue value;
  sval_u sourcePos;
};

struct scrCompileGlob_t
{
  char *codePos;
  char *prevOpcodePos;
  unsigned int filePosId;
  unsigned int fileCountId;
  int cumulOffset;
  int maxOffset;
  int maxCallOffset;
  bool bConstRefCount;
  bool in_developer_thread;
  unsigned int developer_thread_sourcePos;
  bool firstThread[2];
  CaseStatementInfo *currentCaseStatement;
  bool bCanBreak;
  BreakStatementInfo *currentBreakStatement;
  bool bCanContinue;
  ContinueStatementInfo *currentContinueStatement;
  scr_block_s **breakChildBlocks;
  int *breakChildCount;
  scr_block_s *breakBlock;
  scr_block_s **continueChildBlocks;
  int *continueChildCount;
  bool forceNotCreate;
  PrecacheEntry *precachescriptList;
  VariableCompileValue value_start[32];
};


enum ParseCompile_Enums_s : __int32
{
  ENUM_NOP = 0x0,
  ENUM_program = 0x1,
  ENUM_assignment = 0x2,
  ENUM_unknown_variable = 0x3,
  ENUM_local_variable = 0x4,
  ENUM_local_variable_frozen = 0x5,
  ENUM_primitive_expression = 0x6,
  ENUM_integer = 0x7,
  ENUM_float = 0x8,
  ENUM_minus_integer = 0x9,
  ENUM_minus_float = 0xA,
  ENUM_string = 0xB,
  ENUM_istring = 0xC,
  ENUM_array_variable = 0xD,
  ENUM_unknown_field = 0xE,
  ENUM_field_variable = 0xF,
  ENUM_field_variable_frozen = 0x10,
  ENUM_variable = 0x11,
  ENUM_function = 0x12,
  ENUM_call_expression = 0x13,
  ENUM_local_function = 0x14,
  ENUM_far_function = 0x15,
  ENUM_function_pointer = 0x16,
  ENUM_call = 0x17,
  ENUM_method = 0x18,
  ENUM_call_expression_statement = 0x19,
  ENUM_script_call = 0x1A,
  ENUM_return = 0x1B,
  ENUM_return2 = 0x1C,
  ENUM_wait = 0x1D,
  ENUM_script_thread_call = 0x1E,
  ENUM_undefined = 0x1F,
  ENUM_self = 0x20,
  ENUM_self_frozen = 0x21,
  ENUM_level = 0x22,
  ENUM_game = 0x23,
  ENUM_anim = 0x24,
  ENUM_if = 0x25,
  ENUM_if_else = 0x26,
  ENUM_while = 0x27,
  ENUM_for = 0x28,
  ENUM_inc = 0x29,
  ENUM_dec = 0x2A,
  ENUM_binary_equals = 0x2B,
  ENUM_statement_list = 0x2C,
  ENUM_developer_statement_list = 0x2D,
  ENUM_expression_list = 0x2E,
  ENUM_bool_or = 0x2F,
  ENUM_bool_and = 0x30,
  ENUM_binary = 0x31,
  ENUM_bool_not = 0x32,
  ENUM_bool_complement = 0x33,
  ENUM_size_field = 0x34,
  ENUM_self_field = 0x35,
  ENUM_precachetree = 0x36,
  ENUM_waittill = 0x37,
  ENUM_waittillmatch = 0x38,
  ENUM_waittillFrameEnd = 0x39,
  ENUM_notify = 0x3A,
  ENUM_endon = 0x3B,
  ENUM_switch = 0x3C,
  ENUM_case = 0x3D,
  ENUM_default = 0x3E,
  ENUM_break = 0x3F,
  ENUM_continue = 0x40,
  ENUM_expression = 0x41,
  ENUM_empty_array = 0x42,
  ENUM_animation = 0x43,
  ENUM_thread = 0x44,
  ENUM_begin_developer_thread = 0x45,
  ENUM_end_developer_thread = 0x46,
  ENUM_usingtree = 0x47,
  ENUM_false = 0x48,
  ENUM_true = 0x49,
  ENUM_animtree = 0x4A,
  ENUM_breakon = 0x4B,
  ENUM_breakpoint = 0x4C,
  ENUM_prof_begin = 0x4D,
  ENUM_prof_end = 0x4E,
  ENUM_vector = 0x4F,
  ENUM_object = 0x50,
  ENUM_thread_object = 0x51,
  ENUM_local = 0x52,
  ENUM_statement = 0x53,
  ENUM_bad_expression = 0x54,
  ENUM_bad_statement = 0x55,
  ENUM_include = 0x56,
  ENUM_argument = 0x57
};


extern struct scrCompilePub_t gScrCompilePub;

void ScriptCompile(sval_u val, unsigned int filePosId, unsigned int scriptId, PrecacheEntry *entries, int entriesCount);
void LinkThread(unsigned int threadCountId, VariableValue *pos, bool allowFarCall);
void Scr_CalcLocalVarsStatement(sval_u val, scr_block_s *block);
void EmitOpcode(unsigned int op, int offset, int callType);
void EmitStatement(sval_u val, bool lastStatement, unsigned int endSourcePos, scr_block_s *block);
int Scr_FindLocalVarIndex(unsigned int name, sval_u sourcePos, bool create, scr_block_s *block);
unsigned int SpecifyThreadPosition(unsigned int posId, unsigned int name, unsigned int sourcePos, int type);
#endif