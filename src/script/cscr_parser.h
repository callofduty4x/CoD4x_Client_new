#ifndef SCRIPT_SCR_PARSER_H__
#define SCRIPT_SCR_PARSER_H__

#include <q_shared.h>

extern char g_EndPos;


struct SourceBufferInfo
{
  const char *codePos;
  char *buf;
  const char *sourceBuf;
  int len;
  int sortedIndex;
  bool archive;
  byte pad[3];
};

struct scrParserPub_t
{
  struct SourceBufferInfo *sourceBufferLookup;
  unsigned int sourceBufferLookupLen;
  const char *scriptfilename;
  const char *sourceBuf;
};

struct scr_localVar_t
{
  unsigned int name;
  unsigned int sourcePos;
};


struct scr_block_s
{
  int abortLevel;
  int localVarsCreateCount;
  int localVarsPublicCount;
  int localVarsCount;
  unsigned char localVarsInitBits[8];
  scr_localVar_t localVars[64];
};


union sval_u
{
  int type;
  unsigned int stringValue;
  unsigned int idValue;
  float floatValue;
  int intValue;
  sval_u *node;
  unsigned int sourcePosValue;
  const char *codePosValue;
  const char *debugString;
  scr_block_s *block;
};



extern scrParserPub_t gScrParserPub;


bool Scr_PrevCodePosFileNameMatches(const char *codePos, const char *fileName);
const char * Scr_PrevCodePosFunctionName(const char *codePos);
const char * Scr_PrevCodePosFileName(const char *codePos);
void Scr_PrintPrevCodePosSpreadSheet(conChannel_t channel, const char *codePos, bool summary, bool functionSummary);
void CompileError2(const char *codePos, const char *msg, ...);
void CompileError(unsigned int sourcePos, const char *msg, ...);
void Scr_ShutdownOpcodeLookup( );
void ScriptParse( sval_u* , byte);
char *Scr_AddSourceBuffer( const char *filename, const char *extFilename, const char *codePos, bool archive);
void Scr_InitOpcodeLookup( );
unsigned int Scr_GetSourceBuffer(const char *codePos);
void Scr_PrintPrevCodePos(conChannel_t channel, const char *codePos, unsigned int index);
void Scr_SetLoadedImpureScript(bool loadedImpureScript);
void AddOpcodePos(unsigned int sourcePos, int type);
void AddThreadStartOpcodePos(unsigned int sourcePos);
#endif