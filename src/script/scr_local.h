#ifndef __SCR_LOCAL_H__
#define __SCR_LOCAL_H__

#include "../q_shared.h"
#include <stdint.h>

struct VariableStackBuffer
{
  const char *pos;
  uint16_t size;
  uint16_t bufLen;
  uint16_t localId;
  unsigned char time;
  char buf[1];
};

/* 7500 */
union VariableUnion
{
  int intValue;
  float floatValue;
  unsigned int stringValue;
  const float *vectorValue;
  const char *codePosValue;
  unsigned int pointerValue;
  struct VariableStackBuffer *stackValue;
  unsigned int entityOffset;
};

typedef struct
{
  union VariableUnion u;
  int type;
}VariableValue;


struct function_stack_t
{
  const char *pos;
  unsigned int localId;
  unsigned int localVarCount;
  VariableValue *top;
  VariableValue *startTop;
};


struct function_frame_t
{
  struct function_stack_t fs;
  int topType;
};

typedef struct
{
  unsigned int *localVars;
  VariableValue *maxstack;
  int function_count;
  struct function_frame_t *function_frame;
  VariableValue *top;
  bool debugCode;
  bool abort_on_error;
  bool terminal_error;
  bool pad;
  unsigned int inparamcount;
  unsigned int outparamcount;
  struct function_frame_t function_frame_start[32];
  VariableValue stack[2048];
  unsigned int breakpointOutparamcount;
  bool showError;
}scrVmPub_t;

struct scrVmGlob_t
{
  VariableValue eval_stack[2];
  const char *dialog_error_message;
  int loading;
  int starttime;
  unsigned int localVarsStack[2048];
  bool recordPlace;
  const char *lastFileName;
  int lastLine;
};



extern scrVmPub_t gScrVmPub;
extern scrVmGlob_t gScrVmGlob;

void Scr_TerminalError(const char *error);
unsigned int SL_GetCanonicalString(const char *str);

#endif