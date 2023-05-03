#include "../q_shared.h"
#include "voice_local.h"
#include "speex/speex.h"

static void* g_decoder;
int g_decode_frame_size;
static SpeexBits decodeBits;


bandwidth_enum g_current_decode_bandwidth_setting;

void Decode_SetOptions(int frequency)
{
  speex_decoder_ctl(g_decoder, SPEEX_SET_SAMPLING_RATE, &frequency);
}


bool Decode_Init(int bandwidth)
{
  int tmp;
  bandwidth_enum bandwidthEnum = (bandwidth_enum)bandwidth;
  SpeexMode *mode;

  mode = 0;
  tmp = 1;
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
  g_decoder = (void *)speex_decoder_init(mode);
  speex_decoder_ctl(g_decoder, SPEEX_SET_ENH, &tmp);
  Decode_SetOptions(g_encoder_samplerate);
  speex_decoder_ctl(g_decoder, SPEEX_GET_FRAME_SIZE, &g_decode_frame_size);
  g_current_decode_bandwidth_setting = bandwidthEnum;
  speex_bits_init(&decodeBits);
  return true;
}


void Decode_Shutdown()
{
  if ( g_decoder )
  {
    speex_bits_destroy(&decodeBits);
    speex_decoder_destroy(g_decoder);
  }
  g_decoder = 0;
}

int Decode_Sample(char *buffer, int maxLength, int16_t *out, int frame_size)
{
  int num_samples;
  float output_frame[MAX_FRAMESAMPLES +1];
  int i;

  assert(maxLength <= MAX_FRAMESAMPLES);
  assert(maxLength <= frame_size);

  speex_bits_read_from(&decodeBits, buffer, maxLength);
  if ( speex_decode(g_decoder, &decodeBits, output_frame) )
  {
    num_samples = 0;
  }
  else
  {
    num_samples = 2 * frame_size;
  }
  for ( i = 0; i < num_samples; ++i )
  {
    out[i] = (signed int)output_frame[i];
  }
  return num_samples;
}