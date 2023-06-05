#include <q_shared.h>
#include "qcommon_mem.h"
//#include "mem_track.h"

//byte* _PMem_AllocNamed(unsigned int size, unsigned int alignment, unsigned int type, unsigned int allocType, const char *name, EMemTrack memTrack);
//byte* _PMem_Alloc(unsigned int size, unsigned int alignment, unsigned int type, unsigned int allocType, EMemTrack memTrack, const char *file, int lineNum);
int PMem_GetOverAllocatedSize();

void PMem_Init();
void PMem_BeginAlloc(const char *name, unsigned int allocType/*, enum EMemTrack memTrack*/);
void PMem_EndAlloc(const char *name, unsigned int allocType);
void PMem_Free(const char *name);

