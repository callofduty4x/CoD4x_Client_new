#ifndef __DSOUND_GLOB_H__
#define __DSOUND_GLOB_H__

#include "../q_shared.h"
#include <dsound.h>

struct __align(4) dsound_sample_t
{
  IDirectSoundCaptureBuffer *DSCB;
  IDirectSoundBuffer *DSB;
  unsigned int dwBufferSize;
  unsigned int dwCaptureOffset;
  unsigned int currentOffset;
  unsigned int lastOffset;
  unsigned int currentBufferLength;
  int stopPosition;
  unsigned int lastPlayPos;
  int bytesBuffered;
  int mode;
  int frequency;
  int volume;
  int pan;
  int channels;
  bool playing;
  int channel;
  char playMode;
};

struct audioSample_t
{
  char *buffer;
  int lengthInBytes;
  int lengthInSamples;
  int bytesPerSample;
  int frequency;
  bool stereo;
  int channels;
  int sampleOffset;
};


extern int (*current_audioCallback)(struct audioSample_t *);
extern int g_current_bandwidth_setting;


bool DSound_Init(bool callDsoundInit, const void *handle);
void DSound_Shutdown();
bool DSound_StopSample(dsound_sample_t *sample);
dsound_sample_t *DSound_NewSample();
unsigned int DSound_UpdateSample(dsound_sample_t *sample, char *data, unsigned int data_len);
void DSound_SampleFrame(dsound_sample_t *sample);
void DSound_Frame();

bool DSOUNDRecord_Init(bool bCallDsoundInit, const void* handle);
void DSOUNDRecord_Frame();
void DSOUNDRecord_Shutdown();
bool DSOUNDRecord_DestroySample(dsound_sample_t *pRecSample);
dsound_sample_t * DSOUNDRecord_NewSample();
HRESULT DSOUNDRecord_Stop(dsound_sample_t *pRecSample);
HRESULT DSOUNDRecord_Start(dsound_sample_t *pRecSample);


void Sound_SampleFrame(dsound_sample_t *sample);
void Sound_Frame();
int Record_Init(bool callInit, const void *handle);
void Record_Shutdown();
int Sound_Init(const void *handle);
dsound_sample_t *Sound_NewSample();
int Sound_DestroySample(dsound_sample_t *sample);
void Sound_Shutdown();
int Record_Stop(dsound_sample_t *sample);
int Record_DestroySample(dsound_sample_t *sample);
unsigned int Sound_UpdateSample(dsound_sample_t *sample, char *data, unsigned int data_len);
dsound_sample_t * Record_NewSample();
int Record_Start(dsound_sample_t *sample);
void Record_Frame();
bool Sound_StopSample(dsound_sample_t *sample);


#endif