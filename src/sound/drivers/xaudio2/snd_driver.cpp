#include <windows.h>
#include <xaudio2.h>
#include <x3daudio.h>

#include <q_shared.h>
#include <common/qcommon_mem.h>
#include <common/temp_compat.h>
#include <sound/snd_local.h>


char* xaStreamInitialReadBuffer;

struct IXAudioVoice
{
};


struct IXAudioSourceVoice : IXAudioVoice
{
};


struct IXAudioSubmixVoice : IXAudioVoice
{
};

struct XAUDIOCHANNELMAPENTRY
{
  unsigned __int8 InputChannel;
  unsigned __int8 OutputChannel;
  float Volume;
};


struct XAUDIOCHANNELMAP
{
  unsigned __int8 EntryCount;
  XAUDIOCHANNELMAPENTRY *paEntries;
};

struct XaLocal
{
  uint8_t xaudioHandle[20];
  IXAudioSourceVoice *voice_2D[8];
  IXAudioSourceVoice *voice_3D[32];
  IXAudioSourceVoice *voice_stream[13];
  IXAudioSubmixVoice *submixReverb;
  XAUDIOCHANNELMAP monoSourcePassthroughChannelMap;
  XAUDIOCHANNELMAPENTRY monoSourcePassthroughChannelEntry[1];
  XAUDIOCHANNELMAP stereoSourcePassthroughChannelMap;
  XAUDIOCHANNELMAPENTRY stereoSourcePassthroughChannelEntry[2];
  /*XaEqEffect eq[2][3];
  float eqLerp;
  XAUDIOFXTABLEENTRY effectInfo;
  int baseVolEntryCount_2D[8][2];
  float baseVolEntries_2D[8][2][12];
  int baseVolEntryCount_stream[13][2];
  float baseVolEntries_stream[13][2][12];
  XaReverbSettings *reverbSettings;
  XAUDIOSOURCEFORMAT streamSourceFormat[13];
  XaStreamReadInfo streamReadInfo[13];
  SndStartAliasInfo startAliasInfo[13];
  float realVolume[13];
  int playbackRate[53];
  X3DAUDIO_LISTENER listener;
  X3DAUDIO_EMITTER emitter;
  unsigned int calc3DFlags;
  X3DAUDIO_DSP_SETTINGS dspSettings;
  XaVolumeCoefficients volumeCoefficients;
  float delayTimes[6];
  X3DAUDIO_CONE cone;
  XAUDIOVOICEOUTPUTVOLUME voiceVolume;
  XAUDIOVOICEOUTPUTVOLUMEENTRY voiceEntry[2];
  XAUDIOCHANNELVOLUME channelVolume[2];
  XAUDIOCHANNELVOLUMEENTRY channelVolumeEntries[2][12];
  X3DAUDIO_DISTANCE_CURVE linearVolumeFalloffCurve;
  X3DAUDIO_DISTANCE_CURVE_POINT linearVolumeFalloffCurvePoints[9];
  float azimuths[2];
  unsigned __int8 sourceVoiceOutputCount;
  XAUDIOVOICEOUTPUT output;
  XAUDIOVOICEOUTPUTENTRY outputEntry[2];
  XAUDIOCHANNELMAP channel;
  XAUDIOCHANNELMAPENTRY channelEntry[12];*/
};


XaLocal xaGlob;
dvar_s* snd_speakerConfiguration;
dvar_s* snd_omnidirectionalPercentage;
dvar_s* snd_xenonDebugLevel;

const char *snd_xenonDebugLevelStrings[] = {"none", "fatal", "error", "resource", "warning", "processwarning",
                                        "info", "verbose", NULL};

char * snd_speakerConfigurationStrings[] = {"stereo", "5.1", NULL};


HRESULT hr;
hr = CoInitializeEx( nullptr, COINIT_MULTITHREADED );
if (FAILED(hr))
    return hr;

int XA_Init2D()
{
/*
  __int16 v0; // r30
  int v1; // r5
  int result; // r3
  unsigned __int8 v3; // r10
  XAUDIOENGINEINIT v4; // [sp+50h] [-20h] BYREF

  *(_WORD *)&v4.ThreadUsage = v0;
  v4.pEffectTable = &XAudioDefaultEffectTable;
  v4.SubmixStageCount = 1;
  v4.MaxVoiceChannelCount = XA_GetSpeakerCount();
  v4.pMasteringVoiceInit = 0;
  v1 = XAudioInitialize(&v4);
  if ( v1 >= 0 )
  */
  {
    g_snd.Initialized2d = 1;
    g_snd.max_2D_channels = 8;
    g_snd.max_stream_channels = 13;
    g_snd.playback_rate = 0x7FFFFFFF;
    //g_snd.playback_bits = 16;
    g_snd.timescale = 1.0;
    g_snd.playback_channels = XA_GetSpeakerCount();
    return 1;
  }
  Com_PrintError(9, "XAudioInitialize() failed due to error %#X\n", v1);
  return 0;
}


int SND_InitDriver()
{
  const char *v0; // r5
  unsigned __int16 v1; // r4
  unsigned __int8 *v2; // r4
  bool speakerCount; // cr58
  unsigned int SpeakerChannelMask; // r3
  int v6; // r3
  const char *v7; // r5

  assert(!xaStreamInitialReadBuffer);

  xaStreamInitialReadBuffer = reinterpret_cast<char*>(PMem_Alloc(0x20000u, 0x800u, 4u, 1u));
  //track_static_alloc_internal(xaStreamInitialReadBuffer, 0x20000, "SND_InitDriver", 14);
  PMem_SoundInit();
  memset(&xaGlob, 0, sizeof(xaGlob));
  snd_speakerConfiguration = Dvar_RegisterEnum("snd_speakerConfiguration", snd_speakerConfigurationStrings, 1, 0x21u, "Speaker configuration");
  snd_omnidirectionalPercentage = Dvar_RegisterFloat("snd_omnidirectionalPercentage", 0.25, 0.0, 1.0, 0x81, "Percentage of sound volume that is 'directionless'");
  snd_xenonDebugLevel = Dvar_RegisterEnum("snd_xenonDebugLevel", snd_xenonDebugLevelStrings, 0, 0x80u, "Debug output level");

  if ( !XA_Init2D() )
  {
    return 0;
  }
  speakerCount = XA_GetSpeakerCount() == 2;
  SpeakerChannelMask = 3;
  if ( !speakerCount )
    SpeakerChannelMask = 63;
  X3DAudioInitialize(SpeakerChannelMask, 13397.244, xaStreamInitialReadBuffer);
  g_snd.Initialized3d = 1;
  g_snd.max_3D_channels = 32;
  if ( !Stream_Init() )
  {
    SND_ShutdownDriver();
    return 0;
  }
  v6 = XA_InitChannels();
  XA_InitSpatializationParams(v6);
  xaGlob.reverbSettings = (XaReverbSettings *)DB_FindXAssetHeader((XAssetHeader *)0x18, (XAssetType)"singleton", v7)->xmodelPieces;
  SND_SetRoomtype(0);
  XA_InitEq();
  Com_PacketCacheInit();
  Sys_SetSndInitializedEvent();
  return 1;
}
