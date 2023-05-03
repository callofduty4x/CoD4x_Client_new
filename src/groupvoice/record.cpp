
#include "dsound_glob.h"
#include "sound_interface.h"
#include "coder.h"
#include "voice_local.h"
#include "../common/sys_shared.h"
#include "../client/client_shared.h"

#define ENC_BUFFER_SIZE 4096
#define AUDIO_BUFFER_SIZE 640

int Record_QueueAudioDataForEncoding(audioSample_t *sample);


int Record_AudioCallback(audioSample_t *sample)
{
  return Record_QueueAudioDataForEncoding(sample);
}


void Record_SetRecordingCallback(int (*new_audioCallback)(audioSample_t *))
{
  current_audioCallback = new_audioCallback;
}

int Record_Init(bool callInit, const void *handle)
{
  Record_SetRecordingCallback(Record_AudioCallback);
  if(DSOUNDRecord_Init(true, handle))
  {
    return 1;
  }
  return 0;
}

void Record_Frame()
{
  DSOUNDRecord_Frame();
}

void Record_Shutdown()
{
  Encode_Shutdown();
  DSOUNDRecord_Shutdown();
}

int Record_DestroySample(dsound_sample_t *sample)
{
  if(DSOUNDRecord_DestroySample(sample))
  {
    return 1;
  }
  return 0;
}

dsound_sample_t * Record_NewSample()
{
  return DSOUNDRecord_NewSample();
}

int Record_Stop(dsound_sample_t *sample)
{
  return DSOUNDRecord_Stop(sample);
}

int Record_Start(dsound_sample_t *sample)
{
  return DSOUNDRecord_Start(sample);
}

int Record_QueueAudioDataForEncoding(audioSample_t *sample)
{
  int bytes;
  int samples_copied;
  int total_bytes;
  char dst[8196];
  int i;
  int encode_framesz;
  static int samples_in_partial_audio_buffer;
  static int enc_buffer_pos;
  static char partial_audio_buffer[2*AUDIO_BUFFER_SIZE];
  static char enc_buffer[ENC_BUFFER_SIZE];

  voice_current_voicelevel = 0.0;
  if ( sample->bytesPerSample == 2 && sample->lengthInSamples > 0 )
  {
    for ( i = 0; i < sample->lengthInSamples; ++i )
    {
      ((int16_t*)sample->buffer)[i] = (signed int)((float)((int16_t*)sample->buffer)[i] * voice_current_scaler);
      voice_current_voicelevel = (float)(signed int)abs(((int16_t*)sample->buffer)[i]) + voice_current_voicelevel;
    }
    voice_current_voicelevel = voice_current_voicelevel / (float)sample->lengthInSamples;
  }
  if ( !Voice_SendVoiceData() )
  {
    return 0;
  }
  if ( !IN_IsTalkKeyHeld() )
  {
    CL_VoiceTransmit(0);
    return 0;
  }
  encode_framesz = Encode_GetFrameSize();
  sample->sampleOffset = 0;
  total_bytes = 0;
  if ( encode_framesz <= 0 )
  {
    Com_Printf(CON_CHANNEL_SOUND, "Invalid encode frame size of %i\n", encode_framesz);
    return 0;
  }
  if ( sample->lengthInBytes <= 0 )
  {
    Com_Printf(CON_CHANNEL_SOUND, "Invalid sample length of %i samples\n", sample->lengthInSamples);
    return 0;
  }
  if ( sample->sampleOffset < 0 )
  {
    Com_Printf(CON_CHANNEL_SOUND, "Invalid sample offset of %i\n", sample->sampleOffset);
    return 0;
  }


  while ( encode_framesz <= samples_in_partial_audio_buffer + sample->lengthInSamples - sample->sampleOffset )
  {
    samples_copied = 0;
    if ( samples_in_partial_audio_buffer )
    {
      if ( samples_in_partial_audio_buffer < encode_framesz - 4 )
      {
        samples_copied = samples_in_partial_audio_buffer;
      }
      else
      {
        samples_copied = encode_framesz - 4;
      }
      samples_in_partial_audio_buffer = samples_copied;
      
      assert(2*ENC_BUFFER_SIZE >= samples_copied * sample->bytesPerSample);
      assert(2*AUDIO_BUFFER_SIZE >= samples_copied * sample->bytesPerSample);

      memcpy(dst, partial_audio_buffer, sample->bytesPerSample * samples_copied);
      samples_in_partial_audio_buffer -= samples_copied;
    }
    memcpy(&dst[2 * samples_copied], &sample->buffer[sample->bytesPerSample * sample->sampleOffset], sample->bytesPerSample * (encode_framesz - samples_copied));
    sample->sampleOffset += encode_framesz - samples_copied;
    bytes = Encode_Sample((int16_t *)dst, &enc_buffer[enc_buffer_pos], ENC_BUFFER_SIZE - enc_buffer_pos);
    total_bytes += bytes;
    Client_SendVoiceData(bytes, &enc_buffer[enc_buffer_pos]);
  }
  if ( sample->sampleOffset < sample->lengthInSamples )
  {
    memcpy(
      &partial_audio_buffer[2 * samples_in_partial_audio_buffer],
      &sample->buffer[sample->bytesPerSample * sample->sampleOffset],
      sample->bytesPerSample * (sample->lengthInSamples - sample->sampleOffset));
    samples_in_partial_audio_buffer += sample->lengthInSamples - sample->sampleOffset;
  }
  return total_bytes;
}