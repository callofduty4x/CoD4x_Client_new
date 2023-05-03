#include <q_shared.h>


void MT_DumpTree( );
void MT_Init();
byte* MT_Alloc(int numBytes, int type);
void MT_Free(void *p, int numBytes);
bool MT_Realloc(int oldNumBytes, int newNumbytes);
byte* MT_GetRefByIndex(int index);
int MT_GetIndexByRef(byte* p);
void MT_FreeIndex(unsigned int nodeNum, int numBytes);
unsigned int MT_AllocIndex(int numBytes, int type);
