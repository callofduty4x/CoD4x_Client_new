#ifndef __CSCR_VARIABLE_H__
#define __CSCR_VARIABLE_H__

#include <q_shared.h>
#include "scr_local.h"
#include "scr_shared.h"
 
typedef struct
{
  const char *fieldBuffer;
  uint16_t canonicalStrCount;
  byte developer;
  byte developer_script;
  byte evaluate;
  byte pad[3];
  const char *error_message;
  int error_index;
  unsigned int time;
  unsigned int timeArrayId;
  unsigned int pauseArrayId;
  unsigned int levelId;
  unsigned int gameId;
  unsigned int animId;
  unsigned int freeEntList;
  unsigned int tempVariable;
  byte bInited;
  byte pad2;
  uint16_t savecount;
  unsigned int checksum;
  unsigned int entId;
  unsigned int entFieldName;
  struct HunkUser *programHunkUser;
  const char *programBuffer;
  const char *endScriptBuffer;
  const char *varUsagePos;
  int totalObjectRefCount;
  int numScriptValues;
  int numScriptObjects;
  int numScriptThreads;
  int totalVectorRefCount;
}scrVarPub_t;

extern scrVarPub_t gScrVarPub;

struct __align(4) scrVarDebugPub_t
{
  const char **varUsage;
  uint16_t *extRefCount;
  int *leakCount;
  bool dummy;
};

extern struct scrVarDebugPub_t *gScrVarDebugPub;
extern const char *var_typename[];

union ObjectInfo_u
{
  uint16_t size;
  uint16_t entnum;
  uint16_t nextEntId;
  uint16_t self;
};

struct ObjectInfo
{
  uint16_t refCount;
  union ObjectInfo_u u;
};

union VariableValueInternal_u
{
  uint16_t next;
  union VariableUnion u;
  struct ObjectInfo o;
};

union VariableValueInternal_w
{
  unsigned int status;
  unsigned int type;
  unsigned int name;
  unsigned int classnum;
  unsigned int notifyName;
  unsigned int waitTime;
  unsigned int parentLocalId;
};

union VariableValueInternal_v
{
  uint16_t next;
  uint16_t index;
};

union Variable_u
{
  uint16_t prev;
  uint16_t prevSibling;
};

struct Variable
{
  uint16_t id;
  union Variable_u u;
};

struct VariableValueInternal
{
  struct Variable hash;
  union VariableValueInternal_u u;
  union VariableValueInternal_w w;
  union VariableValueInternal_v v;
  uint16_t nextSibling;
};

#define VAR_NAME_LOW_MASK 0x00FFFFFF



void Scr_AddClassField(unsigned int classnum, const char *name, unsigned int offset);
void Scr_AddArrayKeys(unsigned int parentId);
void Scr_RemoveClassMap(unsigned int classnum);
unsigned int Scr_FindField(const char *name, int *type);
int Scr_GetOffset(unsigned int classnum, const char *name);
void Scr_FreeEntityNum(int entnum, unsigned int classnum);
void Scr_AddFields(const char *path, const char *extension);
void Scr_FreeEntityList( );
void Scr_AllocGameVariable();
void Scr_RemoveThreadNotifyName(unsigned int startLocalId);
void RemoveObjectVariable(unsigned int parentId, unsigned int id);
unsigned int GetArraySize(unsigned int id);
void Scr_IncNumScriptThreads();
void Scr_DecNumScriptThreads();
unsigned int GetParentLocalId(unsigned int threadId);
void Scr_SetThreadWaitTime(unsigned int startLocalId, unsigned int waitTime);
unsigned int GetVariable(unsigned int parentId, unsigned int unsignedValue);
unsigned int GetNewObjectVariable(unsigned int parentId, unsigned int id);
unsigned int FindObjectVariable(unsigned int parentId, unsigned int id);
void Scr_StopThread(unsigned int threadId);
void SetNewVariableValue(unsigned int id, VariableValue *value);
void Scr_KillThread(unsigned int parentId);
void Scr_SetThreadNotifyName(unsigned int startLocalId, unsigned int stringValue);
unsigned int Scr_GetSelf(unsigned int threadId);
unsigned int FindObject(unsigned int id);
VariableValueInternal_u *GetVariableValueAddress(unsigned int id);
unsigned int FindLastSibling(unsigned int parentId);
unsigned int Scr_GetVarId(unsigned int index);
unsigned int GetVariableKeyObject(unsigned int id);
unsigned int GetValueType(unsigned int id);
void AddRefToValue(int type, union VariableUnion u);
void Scr_EvalEquality(VariableValue *value1, VariableValue *value2);
bool Scr_CastString(VariableValue *value);
void Scr_KillEndonThread(unsigned int threadId);
unsigned int GetStartLocalId(unsigned int threadId);
unsigned int FindNextSibling(unsigned int id);
unsigned int FindPrevSibling(unsigned int id);
unsigned int Scr_GetObjectType(unsigned int id);
unsigned int Scr_GetThreadNotifyName(unsigned int startLocalId);
unsigned int Scr_GetThreadWaitTime(unsigned int startLocalId);
void Scr_ClearWaitTime(unsigned int startLocalId);
unsigned int GetSafeParentLocalId(unsigned int threadId);
unsigned int Scr_GetVariableFieldIndex(unsigned int parentId, unsigned int name);
unsigned int AllocThread(unsigned int self);
unsigned int AllocChildThread(unsigned int self, unsigned int parentLocalId);
unsigned int GetNewObjectVariableReverse(unsigned int parentId, unsigned int id);
void Scr_DumpScriptVariablesDefault( );
void Scr_DumpScriptVariablesFull( );
void Scr_EvalOr(VariableValue *value1, VariableValue *value2);
qboolean IsFieldObject(unsigned int id);
void Scr_EvalArray(VariableValue *value, VariableValue *index);
void SetVariableValue(unsigned int id, VariableValue *value);
unsigned int Scr_EvalArrayRef(unsigned int parentId);
bool IsValidArrayIndex(unsigned int unsignedValue);
void RemoveNextVariable(unsigned int parentId);
void ClearVariableField(unsigned int parentId, unsigned int name, VariableValue *value);
void ClearArray(unsigned int parentId, VariableValue *value);
unsigned int Scr_EvalFieldObject(unsigned int tempVariable, VariableValue *value);
void Scr_EvalInequality(VariableValue *value1, VariableValue *value2);
void Scr_EvalLess(VariableValue *value1, VariableValue *value2);
void Scr_EvalGreater(VariableValue *value1, VariableValue *value2);
void Scr_EvalGreaterEqual(VariableValue *value1, VariableValue *value2);
void Scr_EvalLessEqual(VariableValue *value1, VariableValue *value2);
void Scr_EvalShiftLeft(VariableValue *value1, VariableValue *value2);
void Scr_EvalShiftRight(VariableValue *value1, VariableValue *value2);
void Scr_EvalPlus(VariableValue *value1, VariableValue *value2);
void Scr_EvalMinus(VariableValue *value1, VariableValue *value2);
void Scr_EvalMultiply(VariableValue *value1, VariableValue *value2);
void Scr_EvalDivide(VariableValue *value1, VariableValue *value2);
void Scr_EvalMod(VariableValue *value1, VariableValue *value2);
void Scr_EvalSizeValue(VariableValue *value);
unsigned int GetObjectVariable(unsigned int parentId, unsigned int id);
unsigned int Scr_EvalVariableObject(unsigned int id);
void Scr_CastBool(VariableValue *value);
void Scr_EvalBoolNot(VariableValue *value);
void Scr_EvalBoolComplement(VariableValue *value);
void Scr_EvalExOr(VariableValue *value1, VariableValue *value2);
void Scr_EvalAnd(VariableValue *value1, VariableValue *value2);
unsigned int FindEntityId(int entnum, unsigned int classnum);
void Scr_CastVector(VariableValue *value);
void ClearVariableValue(unsigned int id);
void SetVariableFieldValue(unsigned int id, VariableValue *value);
unsigned int GetVariableIndexInternal(unsigned int parentId, unsigned int name);
void RemoveVariableValue(unsigned int parentId, unsigned int index);
unsigned int GetArrayVariableIndex(unsigned int parentId, unsigned int unsignedValue);
unsigned int GetInternalVariableIndex(unsigned int unsignedValue);
unsigned int Scr_GetEntityId(int entnum, unsigned int classnum);
scr_entref_t Scr_GetEntityIdRef(unsigned int entId);
unsigned int FindFirstSibling(unsigned int id);
void SafeRemoveVariable(unsigned int parentId, unsigned int unsignedValue);
void Scr_ShutdownVariables( );
void FreeValue(unsigned int id);
void Scr_CastDebugString(VariableValue *value);
void Scr_FreeGameVariable(int bComplete);
void RemoveRefToEmptyObject(unsigned int id);
void ClearObject(unsigned int parentId);
void Scr_FreeObjects( );
void Scr_InitClassMap( );
unsigned int AllocValue( );
void Scr_EvalBinaryOperator(int op, VariableValue *value1, VariableValue *value2);
int Scr_GetClassnumForCharId(char charId);
bool IsObjectFree(unsigned int id);
unsigned int GetVariableName(unsigned int id);
unsigned int FindArrayVariable(unsigned int parentId, int intValue);
void Scr_FreeValue(unsigned int id);
unsigned int GetArrayVariable(unsigned int parentId, unsigned int unsignedValue);
VariableValue Scr_EvalVariable(unsigned int id);
unsigned int GetObject( unsigned int );
unsigned int FindObject( unsigned int );
unsigned int GetNewVariable( unsigned int, unsigned int );
void Scr_SetClassMap( unsigned int );
void RemoveRefToValue(int type, union VariableUnion val);
void Scr_DumpScriptThreads( );
void RemoveVariable(unsigned int parentId, unsigned int unsignedValue);
unsigned int GetArray(unsigned int id);
unsigned int GetNewArrayVariable(unsigned int parentId, unsigned int unsignedValue);
void AddRefToObject(unsigned int id);
void RemoveRefToObject(unsigned int id);
unsigned int FindVariable(unsigned int parentId, unsigned int unsignedValue);
void Scr_ClearScrVarDebugPub( );


#endif
