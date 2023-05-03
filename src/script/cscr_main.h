#include "cscr_compiler.h"

bool Scr_IsInOpcodeMemory(const char *pos);
void Scr_BeginLoadAnimTrees(int user);
unsigned int Scr_LoadScriptInternal(const char *filename, PrecacheEntry *entries, int entriesCount);
extern cvar_t* scrShowVarUsage;
extern cvar_t* scrShowStrUsage;