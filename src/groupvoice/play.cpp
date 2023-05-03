#include "dsound_glob.h"
#include "sound_interface.h"

int Sound_Init(const void *handle)
{
  if(DSound_Init(1, handle))
  {
    return 1;
  }
  return 0;
}

void Sound_Shutdown()
{
  DSound_Shutdown();
}

void Sound_SampleFrame(dsound_sample_t *sample)
{
  DSound_SampleFrame(sample);
}

bool Sound_StopSample(dsound_sample_t *sample)
{
  return DSound_StopSample(sample);
}

int Sound_DestroySample(dsound_sample_t *sample)
{
  return Record_DestroySample(sample);
}

dsound_sample_t *Sound_NewSample()
{
  return DSound_NewSample();
}

unsigned int Sound_UpdateSample(dsound_sample_t *sample, char *data, unsigned int data_len)
{
  return DSound_UpdateSample(sample, data, data_len);
}

void Sound_Frame()
{
  DSound_Frame();
}