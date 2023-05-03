#include "../q_shared.h"
#include "voice_local.h"
#include "speex/speex.h"

static void* g_encoder;
static SpeexBits encodeBits;
static bool g_speex_initialized;
static int g_encoder_quality;
int g_encoder_samplerate;
static int g_frame_size;
int g_current_bandwidth_setting;
extern cvar_t* sv_voiceQuality;

void Encode_SetOptions(int frequency, int quality)
{
  bool yes;

  yes = 1;

  speex_encoder_ctl(g_encoder, SPEEX_SET_SAMPLING_RATE, &frequency);
  speex_encoder_ctl(g_encoder, SPEEX_SET_QUALITY, &quality);
  speex_encoder_ctl(g_encoder, SPEEX_GET_FRAME_SIZE, &g_frame_size);
  speex_encoder_ctl(g_encoder, SPEEX_SET_VAD, &yes);
  speex_encoder_ctl(g_encoder, SPEEX_SET_DTX, &yes);
  
  g_encoder_quality = quality;
  g_encoder_samplerate = frequency;
}

bool Encode_Init(int bandwidth)
{
  SpeexMode *mode;
  bandwidth_enum bandwidthEnum = (bandwidth_enum)bandwidth;

  switch(bandwidthEnum)
  {
    case BANDWIDTH_NARROW:
        mode = (SpeexMode *)&speex_nb_mode;
        break;
    case BANDWIDTH_WIDE:
        mode = (SpeexMode *)&speex_wb_mode;
        break;
    case BANDWIDTH_ULTRAWIDE:    
        mode = (SpeexMode *)&speex_uwb_mode;
        break;
    default:
        Com_Printf(CON_CHANNEL_SOUND, "Unknown bandwidth mode %i\n", bandwidthEnum);
        return false;        
  }
  g_encoder = speex_encoder_init(mode);
  speex_bits_init(&encodeBits);
  g_speex_initialized = true;
  Encode_SetOptions(g_encoder_samplerate, g_encoder_quality);
  speex_encoder_ctl(g_encoder, SPEEX_GET_FRAME_SIZE, &g_frame_size);
  g_current_bandwidth_setting = bandwidthEnum;
  return g_encoder != NULL;
}

bool Encode_Shutdown()
{
  if ( g_encoder )
  {
    speex_encoder_destroy(g_encoder);
  }
  g_encoder = 0;
  if ( g_speex_initialized )
  {
    speex_bits_destroy(&encodeBits);
    g_speex_initialized = false;
  }
  return true;
}

int Encode_GetFrameSize()
{
  return g_frame_size;
}

int Encode_Sample(int16_t *buffer_in, char *buffer_out, int maxLength)
{
  if ( sv_voiceQuality->current.integer != g_encoder_quality )
  {
    g_encoder_quality = sv_voiceQuality->current.integer;
    speex_encoder_ctl(g_encoder, SPEEX_SET_QUALITY, &g_encoder_quality);
  }
  speex_bits_reset(&encodeBits);
  speex_encode_int(g_encoder, buffer_in, &encodeBits);
  return speex_bits_write(&encodeBits, buffer_out, maxLength);
}

