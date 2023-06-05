#include <common/qcommon.h>
#include <common/sys_thread.h>
#include <gfx_d3d/r_shared.h>
#include "db_local.h"
#include <common/ctrycatch.h>

struct XAssetEntry
{
  struct XAsset asset;
  byte zoneIndex;
  bool inuse;
  uint16_t nextHash;
  uint16_t nextOverride;
  uint16_t usageFrame;
};

union XAssetEntryPoolEntry
{
  struct XAssetEntry entry;
  union XAssetEntryPoolEntry *next;
};

extern uint16_t db_hashTable[32768];
extern union XAssetEntryPoolEntry g_assetEntryPool[32768];
const char* DB_GetXAssetName(XAsset const*);
void DB_TryLoadXFile();


void DB_SyncXAssets()
{
    assert(Sys_IsMainThread() || Sys_IsRenderThread());
    
    R_BeginRemoteScreenUpdate();
    Sys_SyncDatabase();
    R_EndRemoteScreenUpdate(0);
    DB_PostLoadXZone();
}



void DB_PrintEntries_f()
{
  unsigned int nextAssetEntryIndex;
  unsigned int hash;
  unsigned int assetEntryIndex;
  XAssetEntryPoolEntry *assetEntry;

  for ( hash = 0; hash < ARRAY_COUNT(db_hashTable); ++hash )
  {
    for ( assetEntryIndex = db_hashTable[hash]; assetEntryIndex; assetEntryIndex = nextAssetEntryIndex )
    {
      assetEntry = &g_assetEntryPool[assetEntryIndex];
      nextAssetEntryIndex = assetEntry->entry.nextHash;

      Com_Printf(CON_CHANNEL_SYSTEM, "%s: %s\n", g_assetNames[assetEntry->entry.asset.type], DB_GetXAssetName(&assetEntry->entry.asset));


    }
  }
}

void __noreturn DB_Thread(unsigned int threadContext)
{
  assert(threadContext == THREAD_CONTEXT_DATABASE);

  //R_ReleaseDXDeviceOwnership();
  while ( 1 )
  {
    Sys_WaitStartDatabase();
    TRY(Exception_type::SystemException)
    {
      DB_TryLoadXFile();
    }
    CATCH
    {
      Com_ErrorAbort();
    }
    ENDTRY
  }
}