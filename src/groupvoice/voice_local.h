#define MAX_FRAMESAMPLES 4096

enum bandwidth_enum
{
  BANDWIDTH_NARROW = 0x0,
  BANDWIDTH_WIDE = 0x1,
  BANDWIDTH_ULTRAWIDE = 0x2,
  NUM_BANDWIDTH_MODES = 0x3,
};

extern int g_encoder_samplerate;
extern float voice_current_voicelevel;
extern float voice_current_scaler;

bool Voice_SendVoiceData();
