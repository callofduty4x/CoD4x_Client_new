bool Scr_IgnoreErrors( );
void Scr_InitDebuggerSystem( );
void Scr_InitDebuggerMain( );
void EmitPreAssignmentPos( );
void Scr_AddAssignmentPos(char *codePos);
void Scr_ResetAbortDebugger();
int Scr_HitBreakpoint(VariableValue *top, const char *pos, unsigned int localId, int hitBreakpoint);
void Scr_HitBuiltinBreakpoint(VariableValue *top, const char *pos, unsigned int localId, int opcode, int builtinIndex, unsigned int outparamcount);
int Scr_HitAssignmentBreakpoint(VariableValue *top, const char *pos, unsigned int localId, int forceBreak);
void Scr_CheckBreakonNotify(int notifyListOwnerId, int stringValue, VariableValue *top, const char *pos, unsigned int localId);

struct FuncDebugData
{
  int breakpointCount;
};

struct scrVmDebugPub_t
{
  FuncDebugData func_table[1024];
  int checkBreakon;
  const char *jumpbackHistory[128];
  int jumpbackHistoryIndex;
  int dummy;
};

extern struct scrVmDebugPub_t gScrVmDebugPub;