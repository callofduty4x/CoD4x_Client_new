#include "db_local.h"
#include "../q_shared.h"
#include "../zlib/zlib.h"
#include "../common/sys_thread.h"
#include "../common/sys_shared.h"
#include <windows.h>


volatile unsigned int g_loadingAssets;
bool g_minimumFastFileLoaded;
volatile int g_totalSize;
volatile int g_loadedSize;
volatile int g_totalExternalBytes;
volatile int g_loadedExternalBytes;
volatile int g_totalStreamBytes;
bool g_trackLoadProgress;
int g_totalWait;

int g_block_mem_type[] = { 0, 1, 1, 2, 1, 1, 2, 2, 2 };

const char *g_block_mem_name[9] =
{
  "temp",
  "runtime",
  "large_runtime",
  "physical_runtime",
  "virtual",
  "large",
  "physical",
  "vertex",
  "index"
};

struct XBlock
{
  byte *data;
  unsigned int size;
};


#define FASTFILE_VERSION 5
#define XBLOCK_COUNT_IW3 9
#define XBLOCK_COUNT_T5 7
#define XBLOCK_COUNT XBLOCK_COUNT_IW3
#define INVALID_DBFILE -1

struct XFile
{
  unsigned int size;
  unsigned int externalSize;
  unsigned int blockSize[XBLOCK_COUNT];
};

#define DEFLATE_BUFFER_SIZE 0x8000
#define DBFILE_BUFFER_SIZE 0x80000

struct DB_LoadData
{
  HANDLE f;
  const char *filename;
  struct XBlock *blocks;
  int outstandingReads;
  struct _OVERLAPPED overlapped;
  struct z_stream_s stream;
  char *compressBufferStart;
  char *compressBufferEnd;
  void (*interrupt)();
  int allocType;
  int deflateBufferPos;
  int deflateRemainingFileSize;
  int flags;
  int startTime;
  bool abort;
  bool ateof;
  byte deflateBuffer[DEFLATE_BUFFER_SIZE];
};

struct DB_LoadData g_load;


bool DB_IsMinimumFastFileLoaded()
{
  return g_minimumFastFileLoaded;
}

void DB_ResetMinimumFastFileLoaded()
{
  g_minimumFastFileLoaded = 0;
}

void DB_ResetZoneSize(bool trackLoadProgress)
{
  g_totalSize = 0;
  g_loadedSize = 0;
  g_totalExternalBytes = 0;
  g_loadedExternalBytes = 0;
  g_totalStreamBytes = 0;
  g_trackLoadProgress = trackLoadProgress;
}

void DB_LoadedExternalData(int size)
{
  InterlockedExchangeAdd((volatile long int*)&g_loadedExternalBytes, size);
}


double DB_GetLoadedFraction()
{
  double loadedBytesInternal;
  double totalBytesInternal;
  double loadedBytesExternal;

    if ( !g_totalSize )
    {
        return 0.0;
    }

    totalBytesInternal = (double)g_totalSize * 262144.0;
    loadedBytesInternal = (double)g_loadedSize * 262144.0;

    assert(loadedBytesInternal >= 0);

    if ( loadedBytesInternal > totalBytesInternal )
    {
      loadedBytesInternal = totalBytesInternal;
    }
    if(loadedBytesInternal <= 0)
    {
        return 0.0;
    }
    loadedBytesExternal = (double)g_loadedExternalBytes;
    if ( (double)g_loadedExternalBytes > (double)g_totalExternalBytes )
    {
      loadedBytesExternal = (double)g_totalExternalBytes;
    }
    if ( g_loadedSize < g_totalSize )
    {
        return loadedBytesInternal / totalBytesInternal;
    }

    if ( g_loadedSize >= g_totalSize )
    {
        return 1.0;
    }
    return 0.5 * ( (loadedBytesInternal + loadedBytesExternal) / (totalBytesInternal + (double)g_totalExternalBytes) );
}

void __stdcall DB_FileReadCompletionDummyCallback(long unsigned int dwErrorCode, long unsigned int dwNumberOfBytesTransfered, struct _OVERLAPPED *lpOverlapped)
{

}



bool DB_ReadData()
{
  char *fileBuffer;

  assert(g_load.compressBufferStart);
  assert(g_load.f);

  if ( g_load.interrupt )
  {
    g_load.interrupt();
  }
  fileBuffer = &g_load.compressBufferStart[g_load.overlapped.Offset % DBFILE_BUFFER_SIZE];

  Sys_WaitDatabaseThread();

  if ( iReadFileEx(g_load.f, fileBuffer, 0x40000u, &g_load.overlapped, DB_FileReadCompletionDummyCallback) )
  {
    ++g_load.outstandingReads;
    g_load.overlapped.Offset += 0x40000;
    return true;
  }
  return false;
}


//g_load.outstandingReads get increased by 1 when we have read data of amount 0x40000 or less on end of file
//g_load.outstandingReads gets lowered by 1 when 

void DB_ReadXFileStage()
{
    g_load.ateof = false;
    if ( !g_load.f )
    {
        return;
    }
    assert ( !g_load.outstandingReads );
    if ( !DB_ReadData() )
    {
      if(iGetLastError() == 38)
      {
        g_load.ateof = true;
      }else{
        Com_Error(ERR_DROP, "Read error of file '%s'", g_load.filename);
      }
    }
}


void DB_WaitXFileStage()
{
    int waitStart;
    assert(g_load.f);
    assert(g_load.outstandingReads > 0);

    --g_load.outstandingReads;
    waitStart = Sys_Milliseconds();
    iSleepEx(-1, TRUE);
    g_totalWait += Sys_Milliseconds() - waitStart;
    InterlockedIncrement((DWORD*)&g_loadedSize);
    g_load.stream.avail_in += 0x40000;
}

void DB_CancelLoadXFile()
{
  if ( g_load.compressBufferStart )
  {
    while ( g_load.outstandingReads > 0)
    {
      DB_WaitXFileStage();
    }

    DB_AuthLoad_InflateEnd(&g_load.stream);

    assert ( g_load.f );
    assert ( (signed int)g_load.f != INVALID_DBFILE );

    iCloseHandle(g_load.f);
  }
}

void DB_LoadXFileSetSize(int size)
{
  assert(g_load.deflateRemainingFileSize == 0);
  g_load.deflateRemainingFileSize = size;
}



void DB_LoadXFileData(byte *pos, int size)
{
  signed int lastAvailOutSize;
  int lastDeflateRemainingFileSize;
  int bytesToCopy;
  int err;

  assert(size);
  assert(g_load.f);
  assert(!g_load.stream.avail_out);
  if ( size <= 0 )
  {
    return;
  }
  while( size + g_load.deflateBufferPos > DEFLATE_BUFFER_SIZE && size > 0)
  {
      assert(g_load.deflateBufferPos <= DEFLATE_BUFFER_SIZE);

      if ( g_load.deflateBufferPos < DEFLATE_BUFFER_SIZE )
      {
        bytesToCopy = DEFLATE_BUFFER_SIZE - g_load.deflateBufferPos;
        if ( g_load.deflateBufferPos == DEFLATE_BUFFER_SIZE -1 )
        {
          *pos = g_load.deflateBuffer[g_load.deflateBufferPos];
        }
        else
        {
          memcpy(pos, &g_load.deflateBuffer[g_load.deflateBufferPos], bytesToCopy);
        }
        g_load.deflateBufferPos += bytesToCopy;
        pos += bytesToCopy;
        size -= bytesToCopy;
      }
      if ( g_load.deflateRemainingFileSize < DEFLATE_BUFFER_SIZE )
      {
        lastDeflateRemainingFileSize = g_load.deflateRemainingFileSize;
      }
      else
      {
        lastDeflateRemainingFileSize = DEFLATE_BUFFER_SIZE;
      }
      g_load.stream.avail_out = lastDeflateRemainingFileSize;
      g_load.deflateBufferPos = DEFLATE_BUFFER_SIZE - lastDeflateRemainingFileSize;
      g_load.stream.next_out = &g_load.deflateBuffer[DEFLATE_BUFFER_SIZE - lastDeflateRemainingFileSize];
      if ( lastDeflateRemainingFileSize < size )
      {
        lastAvailOutSize = g_load.stream.avail_out;
      }
      else
      {
        lastAvailOutSize = size;
      }
      size -= lastAvailOutSize;
      g_load.deflateRemainingFileSize -= g_load.stream.avail_out;
      do
      {
        if ( !g_load.stream.avail_in )
        {
          DB_WaitXFileStage();
          DB_ReadXFileStage();
          continue;
        }
        err = DB_AuthLoad_Inflate(&g_load.stream, 2);
        if ( err && err != 1)
        {
          //R_ShowDirtyDiscError();
          DB_CancelLoadXFile();
          Com_Error(ERR_DROP, "Fastfile for zone '%s' appears corrupt or unreadable (code %i.)", g_load.filename, err + 110);
        }
        if(err == Z_STREAM_END)
        {
          if(g_load.stream.avail_out > 0 && g_load.ateof)
          {
            DB_CancelLoadXFile();
            Com_Error(ERR_DROP, "Fastfile for zone '%s' appears corrupt or unreadable. Unexpected end of stream. Missing %d bytes.",
              g_load.filename, g_load.stream.avail_out + g_load.deflateRemainingFileSize);
          }
        }
        if ( g_load.f)
        {
          assert((unsigned int)( g_load.stream.next_in - (byte*)g_load.compressBufferStart ) <= DBFILE_BUFFER_SIZE);
          if( g_load.stream.next_in == (byte*)g_load.compressBufferEnd)
          {
            g_load.stream.next_in = (byte*)g_load.compressBufferStart;
          }
        }
//        assertx(err == Z_OK, "Invalid fast file '%s' (%d != Z_OK)", g_load.filename, err);
        if ( g_load.stream.avail_out )
        {
          DB_WaitXFileStage();
          DB_ReadXFileStage();
        }
      }while(g_load.stream.avail_out);
      assert(lastAvailOutSize <= DEFLATE_BUFFER_SIZE);
      if ( lastAvailOutSize == 1 )
      {
        *pos = g_load.deflateBuffer[g_load.deflateBufferPos];
      }
      else
      {
        memcpy(pos, &g_load.deflateBuffer[g_load.deflateBufferPos], lastAvailOutSize);
      }
      g_load.deflateBufferPos += lastAvailOutSize;
      pos += lastAvailOutSize;
  }
  if ( size == 1 )
  {
    *pos = g_load.deflateBuffer[g_load.deflateBufferPos];
  }
  else
  {
    memcpy(pos, &g_load.deflateBuffer[g_load.deflateBufferPos], size);
  }
  g_load.deflateBufferPos += size;
}



void Load_XAssetListCustom()
{
  static struct XAssetList g_varXAssetList;

  varXAssetList = &g_varXAssetList;
  DB_LoadXFileData((byte *)&g_varXAssetList, 16);
  DB_PushStreamPos(4u);
  varScriptStringList = (ScriptStringList *)varXAssetList;
  Load_ScriptStringList(0);
  DB_PopStreamPos();
}


void DB_AllocXBlocks(unsigned int *blockSize, const char *filename, XBlock *blocks, unsigned int allocType, int flags)
{
  unsigned int blockIndex;
  byte *buf;
  unsigned int size;
  float total_size;

  total_size = 0.0;
  for ( blockIndex = 0; blockIndex < XBLOCK_COUNT; ++blockIndex )
  {
    size = blockSize[blockIndex];
    if ( size )
    {
      total_size = (double)size + total_size;
      buf = DB_MemAlloc(size, g_block_mem_type[blockIndex], allocType, filename, flags);
      if ( !buf )
      {
        Com_Error(ERR_DROP, "Could not allocate %.2f MB of type '%s' for zone '%s' needed an additional %.2f MB",
          (double)size * 0.00000095367432, g_block_mem_name[blockIndex], filename, (float)((float)PMem_GetOverAllocatedSize() * 0.00000095367432));
      }
      blocks[blockIndex].size = size;
      blocks[blockIndex].data = buf;
    }
  }
  Com_Printf(CON_CHANNEL_SYSTEM, "used %0.2f MB memory in DB alloc\n", (float)(total_size / 1048576.0));

//#pragma message "StaticIndexBuffer? StaticVertexBuffer?"
}


void Load_XAssetArrayCustom(int count)
{
  XAsset *var;
  int i;

  Load_Stream(1, varXAsset, 8 * count);
  var = (XAsset *)varXAsset;
  for ( i = 0; i < count; ++i )
  {
    varXAsset = var;
    Load_XAsset(0);
/*
    int spos = g_streamPos - g_streamBlocks[g_streamPosIndex].data;
    Com_Printf(CON_CHANNEL_SYSTEM, "%d, %d   -   Loaded %s\n", spos, g_streamPosIndex ,DB_GetXAssetName(varXAsset));
*/
    ++var;
    if ( g_load.abort )
    {
      break;
    }
  }
}

bool s_usageUpToDate[ASSET_TYPE_COUNT];
int s_usageCounts[ASSET_TYPE_COUNT];
/*
void DB_GetAssetTypeUsageInfo(XAssetType assetType, const char **outName, int *outUsed, int *outPool)
{
  if ( !s_usageUpToDate[assetType] )
  {
    s_usageUpToDate[assetType] = 1;
    s_usageCounts[assetType] = DB_GetAllXAssetOfType(assetType, 0, 0);
  }
  *outUsed = s_usageCounts[assetType];
  *outPool = g_poolSize[assetType];
  *outName = g_assetNames[assetType];
}
*/

void DB_MarkAssetTypeUsageDirty()
{
  memset(s_usageUpToDate, 0, sizeof(s_usageUpToDate));
}


void DB_LoadXFileInternal()
{
  bool fileIsSecure;
  int err;
  unsigned int version;
  XFile file;
  int fileSize;
  const char *failureReason;
  char magic[8];

  g_totalWait = 0;
  assert(g_load.f);

  DB_ReadXFileStage();

  if ( !g_load.outstandingReads )
  {
    Com_Error(ERR_DROP, "Fastfile for zone '%s' is empty.", g_load.filename);
  }

  DB_WaitXFileStage();
  DB_ReadXFileStage();

  assert(sizeof( magic ) <= g_load.stream.avail_in);

  memcpy(magic, g_load.stream.next_in, sizeof(magic));

  g_load.stream.next_in += 8;
  g_load.stream.avail_in -= 8;
  if ( memcmp(magic, "IWff0100", 8u) )
  {
    if ( memcmp(magic, "IWffu100", 8u) )
    {
//      R_ShowDirtyDiscError();
      Com_Error(ERR_DROP, "Fastfile for zone '%s' is corrupt or unreadable.", g_load.filename);
    }
  }

  assert(sizeof( version ) <= g_load.stream.avail_in);
  version = *(unsigned int*)g_load.stream.next_in;

  g_load.stream.next_in += 4;
  g_load.stream.avail_in -= 4;
  if ( version != FASTFILE_VERSION )
  {
    if ( version >= FASTFILE_VERSION )
    {
      Com_Error(ERR_DROP, "Fastfile for zone '%s' is newer than client executable (version %d, expecting %d)", g_load.filename, version, FASTFILE_VERSION);
    }
    else
    {
      Com_Error(ERR_DROP, "Fastfile for zone '%s' is out of date (version %d, expecting %d)", g_load.filename, version, FASTFILE_VERSION);
    }
  }
  fileIsSecure = memcmp(magic, "IWffu100", 8u) != 0;
  err = DB_AuthLoad_InflateInit(&g_load.stream, fileIsSecure, g_load.filename);
  failureReason = 0;
  if ( fileIsSecure )
  {
    failureReason = "authenticated file not supported";
  }
  if ( err )
  {
    failureReason = "init failed";
  }
  if ( failureReason )
  {
//    R_ShowDirtyDiscError();
    DB_CancelLoadXFile();
    Com_Error(ERR_DROP, "Fastfile for zone '%s' could not be loaded (%s)", g_load.filename, failureReason);
  }

  assert(g_load.deflateBufferPos == DEFLATE_BUFFER_SIZE);

  DB_LoadXFileSetSize(sizeof(file));
  DB_LoadXFileData((byte*)&file, sizeof(file));

  DB_LoadXFileSetSize(file.size);

  if ( g_trackLoadProgress )
  {
    fileSize = iGetFileSize(g_load.f, 0);
    if ( file.externalSize + fileSize >= 0x100000 )
    {
      g_totalSize = (fileSize + 0x3FFFF) / 0x40000 - g_loadedSize;
      g_loadedSize = 0;
      g_totalExternalBytes = file.externalSize - g_loadedExternalBytes;
      g_loadedExternalBytes = 0;
    }
  }
  Com_Printf(CON_CHANNEL_SYSTEM, "Loading fastfile '%s'\n", g_load.filename);

  DB_AllocXBlocks(file.blockSize, g_load.filename, g_load.blocks, g_load.allocType, g_load.flags);

  DB_InitStreams(g_load.blocks);

  Load_XAssetListCustom();

//  PrintScriptStrings();

  DB_PushStreamPos(4u);

  if ( varXAssetList->assets )
  {
    varXAssetList->assets = AllocLoad_XAsset();
    varXAsset = varXAssetList->assets;
    Load_XAssetArrayCustom(varXAssetList->assetCount);
  }

  DB_PopStreamPos();
  Load_DelayStream();

  --g_loadingAssets;

  DB_MarkAssetTypeUsageDirty();
  DB_LoadDelayedImages();

  assert(g_load.compressBufferStart);

  Com_Printf(CON_CHANNEL_FILES, "Loaded fastfile '%s' in %ims (%dms waiting)\n", g_load.filename, Sys_Milliseconds() - g_load.startTime, g_totalWait);
  if ( g_load.flags & 1 )
  {
    g_minimumFastFileLoaded = 1;
  }
  DB_CancelLoadXFile();
}
