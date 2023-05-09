#include <common/qcommon.h>
#include "snd_driver.h"

char *MSS_Alloc_LoadObj(int data_length, int data_rate)
{
  return reinterpret_cast<char*>(Hunk_AllocInternal(data_length));
}

char *MSS_Alloc_FastFile(int data_length, unsigned int data_rate)
{
  return reinterpret_cast<char*>(Z_Malloc(data_length, TAG_SND_RAWDATA, false));
}

void SND_SetData(MssSound *pSoundFile, const void *data)
{
  if ( !useFastFile->current.enabled )
  {
    pSoundFile->data = MSS_Alloc_LoadObj(pSoundFile->info.data_len, pSoundFile->info.rate);
  }else{
    pSoundFile->data = MSS_Alloc_FastFile(pSoundFile->info.data_len, pSoundFile->info.rate);
  }
  memcpy(pSoundFile->data, data, pSoundFile->info.data_len);
  pSoundFile->info.data_ptr = pSoundFile->data;
  pSoundFile->info.initial_ptr = pSoundFile->data;
}


void Load_SetSoundData(unsigned char **data, MssSound *pSoundFile)
{
  SND_SetData(pSoundFile, *data);
}


LoadedSound * SND_LoadSoundFile(const char *snd_name)
{
  LoadedSound *snd;
  char qpath[256];
  AILSOUNDINFO info;
  void *buffer;

  Com_sprintf(qpath, sizeof(qpath), "sound/%s", snd_name);
  if ( FS_ReadFile(qpath, &buffer) < 0 )
  {
    Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound file '%s' not found\n", qpath);
    return nullptr;
  }
  else
  {
    if ( AIL_WAV_info(buffer, &info) )
    {
      if ( info.data_len )
      {
        snd = reinterpret_cast<LoadedSound *>(Hunk_AllocInternal(sizeof(LoadedSound)));
        snd->name = snd_name;
        snd->sound.info = info;
        SND_SetData(&snd->sound, info.data_ptr);
        return snd;
      }
      Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound file '%s' is zero length, invalid\n", snd_name);
      snd = nullptr;
    }
    else
    {
      Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound file '%s' is in an invalid or corrupted format\n", snd_name);
      snd = nullptr;
    }
    FS_FreeFile(buffer);
  }
  return snd;
}


