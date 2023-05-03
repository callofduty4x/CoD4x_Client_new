#include "../q_shared.h"
#include "qcommon_mem.h"

void* Z_MallocInternal(unsigned int iSize);

#ifdef DEBUG_ZONE_ALLOCS
extern "C" void *_D_Z_Malloc ( int iSize, memtag_t eTag, bool bZeroit, const char *psFile, int iLine)
#else
extern "C" void *Z_Malloc(unsigned int iSize, memtag_t eTag, bool bZeroit)
#endif
{
    return Z_MallocInternal(iSize);
}
extern "C" int Z_Free(void *pvAddress)
{
    free(pvAddress);
    return 0;
}

void* Z_MallocInternal(unsigned int iSize)
{
    return malloc(iSize);
}

void *Z_TagMalloc( int size, int tag )
{
    return Z_MallocInternal(size);
}