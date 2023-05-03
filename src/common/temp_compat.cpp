#include <q_shared.h>
#include <database/db_local.h>
#include <common/mem_track.h>
#include "temp_compat.h"


XAssetHeader DB_FindXAssetHeader(XAssetType type, const char *name, bool errorIfMissing, int waitTime)
{
  return DB_FindXAssetHeader(type, name);
}

byte* _PMem_AllocNamed(unsigned int size, unsigned int alignment, unsigned int type, unsigned int allocType, const char *name, EMemTrack memTrack)
{
    return PMem_Alloc(size, alignment, type, allocType);
}
