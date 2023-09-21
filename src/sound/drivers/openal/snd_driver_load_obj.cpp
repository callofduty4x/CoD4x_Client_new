#include <common/qcommon.h>

struct LoadedSound{
  int null;
};

struct MssSound{
  int null;
};

char *MSS_Alloc_LoadObj(int data_length, int data_rate)
{
  return reinterpret_cast<char*>(Hunk_AllocInternal(data_length));
}

char *MSS_Alloc_FastFile(int data_length, unsigned int data_rate)
{
  return reinterpret_cast<char*>(Z_Malloc(data_length, TAG_SND_RAWDATA, false));
}


void Load_SetSoundData(unsigned char **data, MssSound *pSoundFile)
{
  
}


LoadedSound * SND_LoadSoundFile(const char *snd_name)
{
  return nullptr;
}


