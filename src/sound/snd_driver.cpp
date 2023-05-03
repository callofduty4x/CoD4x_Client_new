#include <windows.h>
#include "snd_local.h"
#include "../common/qcommon.h"

void SND_SetAIL_HWND(HWND hWnd)
{
    if ( g_snd.initialized ){
        AIL_set_DirectSound_HWND(milesGlob.dig, hWnd);
    }
}

U32 AILCALLBACK MSS_FileOpenCallback(const MSS_FILE *Filename, UINTa* FileHandle)
{
  if(FS_FOpenFileReadStream(Filename, (int*)FileHandle) < 0)
  {
    return false;
  }
  return true;
}

void AILCALLBACK MSS_FileCloseCallback(UINTa FileHandle)
{
    FS_FCloseFile(FileHandle);
}

S32 AILCALLBACK MSS_FileSeekCallback(UINTa FileHandle, S32 Offset, U32 Type)
{
  switch (Type)
  {
    case AIL_FILE_SEEK_CURRENT:
      FS_Seek(FileHandle, Offset, FS_SEEK_CUR);
      break;
    case AIL_FILE_SEEK_END:
      FS_Seek(FileHandle, Offset, FS_SEEK_END);
      break;
    case AIL_FILE_SEEK_BEGIN:
      FS_Seek(FileHandle, Offset, FS_SEEK_SET);
      break;
    default:
      return 0;
  }
  unsigned int newfilepos = FS_FTell(FileHandle);
  
  return newfilepos;


}

U32 AILCALLBACK MSS_FileReadCallback(UINTa FileHandle, void* Buffer, U32 Bytes)
{
  int readbytes = FS_Read(Buffer, Bytes, FileHandle);
  return readbytes;

}
