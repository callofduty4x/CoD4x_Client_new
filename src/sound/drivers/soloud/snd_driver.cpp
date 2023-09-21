#include <sound/snd_local.h>
#include <common/qcommon.h>
#include <gfx_d3d/r_cinematic.h>
#include <q_shared.h>
#include <common/com_sndalias.h>
#include <common/com_debug.h>
#include "soloud.h"
#include "soloud_speech.h"
#include "soloud_thread.h"


struct MemoryFile;
struct HSAMPLE{
  int null;

};

static constexpr int MAX_2D_CHANNELS = 8;
static constexpr int MAX_3D_CHANNELS = 32;
static constexpr int MAX_STREAM_CHANNELS = 13;

dvar_s* snd_khz;
dvar_s* snd_outputConfiguration;

const char *snd_outputConfigurationStrings[] = { "Windows default", "Mono", "Stereo", "4 speakers", "5.1 speakers" };
int mss_spec[5] = { 16, 1, 32, 80, 96 };



struct NullDriverChannel
{
  int playback_rate2d;
  int playback_rate3d;
  int playback_rate_stream;
  float volume_stream;
};

struct NullDriverLocal
{
  NullDriverChannel channels[53];
};

NullDriverLocal null_snd_drv;


struct ChannelCtx
{
  int handle;
};


struct DriverCtx
{
  SoLoud::Soloud soloud;
  ChannelCtx channels[MAX_2D_CHANNELS + MAX_3D_CHANNELS + MAX_STREAM_CHANNELS];
};


DriverCtx drv_local;

const void* SND_GetDriverHandle()
{
  dbgCon->Print("SND_GetDriverHandle()\n");
  return NULL;
}

int SND_GetSoundFileSize(const void *pSoundFile)
{
  dbgCon->Print("{}\n", __func__);

  /*
    assert(pSoundFile);
    const MssSound* internalFile = reinterpret_cast<const MssSound*>(pSoundFile);
    return internalFile->info.data_len;
    */
   return 0;
}


int SND_Get2DChannelPlaybackRate(int index)
{
  dbgCon->Print("{}\n", __func__);

  return null_snd_drv.channels[index].playback_rate2d;
}

int SND_Get3DChannelPlaybackRate(int index)
{
  dbgCon->Print("{}\n", __func__);

  return null_snd_drv.channels[index].playback_rate3d;
}

int SND_GetStreamChannelPlaybackRate(int index)
{
  dbgCon->Print("{}\n", __func__);

  return null_snd_drv.channels[index].playback_rate_stream;
}


float SND_GetStreamChannelVolume(int index)
{
  dbgCon->Print("{}\n", __func__);
  return null_snd_drv.channels[index].volume_stream;
}





void SND_GetStreamChannelSaveInfo(int index, snd_save_stream_t *info)
{
  dbgCon->Print("{}\n", __func__);

  info->fraction = 0;
  info->rate = SND_GetStreamChannelPlaybackRate(index);
  info->basevolume = g_snd.chaninfo[index].basevolume;
  info->volume = SND_GetStreamChannelVolume(index) / g_snd.volume;
  info->org[0] = 0;
  info->org[1] = 0;
  info->org[2] = 0;
}


int SND_GetDriverCPUPercentage(void)
{
  dbgCon->Print("{}\n", __func__);
  return 0;
}

int SND_GetStreamChannelLength(int index)
{
  dbgCon->Print("{}\n", __func__);
  return 0;
}


void SND_Get2DChannelSaveInfo(int index, snd_save_2D_sample_t *info)
{
  dbgCon->Print("{}\n", __func__);

  info->fraction = 0;
  info->pitch = g_snd.chaninfo[index].pitch;
  info->volume = g_snd.chaninfo[index].basevolume;
}

void SND_Get3DChannelSaveInfo(int index, snd_save_3D_sample_t *info)
{  
  dbgCon->Print("{}\n", __func__);
  info->fraction = 0;
  info->pitch = g_snd.chaninfo[index].pitch;
  info->volume = g_snd.chaninfo[index].basevolume;
  info->org[0] = 0;
  info->org[1] = 0;
  info->org[2] = 0;
}


int SND_Get2DChannelLength(int index)
{
  dbgCon->Print("{}\n", __func__);
  return 0;
}

float SND_Get2DChannelVolume(int index)
{
  dbgCon->Print("{}\n", __func__);
  return 0;
}

float SND_Get3DChannelVolume(int index)
{
  dbgCon->Print("{}\n", __func__);
  return 0;
}

int SND_Get3DChannelLength(int index)
{
  dbgCon->Print("{}\n", __func__);
  return 0;
}


bool SND_Is2DChannelFree(int index)
{
  bool free = !g_snd.chaninfo[index].paused && !g_snd.chaninfo[index].startDelay && g_snd.chaninfo[index].alias0 == 0;
  //dbgCon->Print("{} index={} free={}\n", __func__, index, free);
  return free;
}

bool SND_Is3DChannelFree(int index)
{
  bool free = !g_snd.chaninfo[index].paused && !g_snd.chaninfo[index].startDelay && g_snd.chaninfo[index].alias0 == 0;
  //dbgCon->Print("{} index={} free={}\n", __func__, index, free);
  return free;
}

bool SND_IsStreamChannelFree(int index)
{
  bool free = !g_snd.chaninfo[index].paused && !g_snd.chaninfo[index].startDelay && g_snd.chaninfo[index].alias0 == 0;
  //dbgCon->Print("{} index={} free={}\n", __func__, index, free);
  return free;
}


void SND_SetAIL_HWND(HWND hWnd)
{
  dbgCon->Print("{}\n", __func__);

}

float MSS_SpatializeStream(int index, int listener)
{
  dbgCon->Print("{}\n", __func__);

  return 0;
}

void SND_SaveEq(MemoryFile * memfile)
{
    ;
}

void SND_SetEqQ(int entchannel, int eqIndex, int band, float q)
{
    ;
}

void SND_DisableEq(int entchannel, int eqIndex, int band)
{
    ;
}

void SND_RestoreEq(MemoryFile * memfile)
{
    ;
}

void SND_SetEqFreq(int entchannel, int eqIndex, int band, float freq)
{
  ;
}

void SND_SetEqGain(int entchannel, int eqIndex, int band, float gain)
{
  ;
}

void SND_SetEqType(int entchannel, int eqIndex, int band, SND_EQTYPE type)
{
  ;
}

void SND_SetEqParams(int entchannel, int eqIndex, int band, SND_EQTYPE type, float gain, float freq, float q)
{
  ;
}

void SND_PrintEqParams(void)
{
  ;
}

void MSS_InitEq()
{
    ;
}

void MSS_InitChannels()
{
  dbgCon->Print("{}\n", __func__);

}

int SND_InitDriver(void)
{
  dbgCon->Print("{}\n", __func__);

  snd_khz = Dvar_RegisterInt("snd_khz", 44, 11, 44, 0x21u, "The game sound frequency.");
  snd_outputConfiguration = Dvar_RegisterEnum("snd_outputConfiguration", snd_outputConfigurationStrings, 0, 0x21u, "Sound output configuration");

  // initialize SoLoud.
  drv_local.soloud.init(drv_local.soloud.CLIP_ROUNDOFF, drv_local.soloud.AUTO, snd_khz->current.integer * 1000);


  g_snd.Initialized2d = 1;
  g_snd.Initialized3d = 1;
  g_snd.max_2D_channels = MAX_2D_CHANNELS;
  g_snd.max_3D_channels = MAX_3D_CHANNELS;
  g_snd.max_stream_channels = MAX_STREAM_CHANNELS;
  
  drv_local.soloud.setMaxActiveVoiceCount(g_snd.max_2D_channels + g_snd.max_3D_channels + g_snd.max_stream_channels);

  g_snd.playback_rate = 0x7FFFFFFF;
  g_snd.playback_channels = (mss_spec[snd_outputConfiguration->current.integer] != 1) + 1;
  g_snd.timescale = 1.0;

  return 0;
}

void SND_SetRoomtype(int room_type)
{
  dbgCon->Print("{}\n", __func__);

}



void SND_Set3DPosition(HSAMPLE sample, int listener, const float *org)
{
  dbgCon->Print("{}\n", __func__);

}

int SND_Set3DPosition(int index, const float *org)
{
  dbgCon->Print("{}\n", __func__);

  int listIdx = SND_GetListenerIndexNearestToOrigin(org);
  return listIdx; //listener
}

void SND_Stop2DChannel(int index)
{
  dbgCon->Print("{}\n", __func__);

}

void SND_Stop3DChannel(int index)
{
  dbgCon->Print("{}\n", __func__);

}

bool SND_IsMultiChannel(void)
{
  dbgCon->Print("{}\n", __func__);
  return false;
}

void SND_Pause2DChannel(int index)
{
  dbgCon->Print("{}\n", __func__);

  g_snd.chaninfo[index].paused = 1;
}

void SND_Pause3DChannel(int index)
{
  dbgCon->Print("{}\n", __func__);

  g_snd.chaninfo[index].paused = 1;
}

void SND_ShutdownDriver(void)
{
  dbgCon->Print("{}\n", __func__);

  drv_local.soloud.deinit();
  memset(&null_snd_drv, 0, sizeof(null_snd_drv));
}

void SND_DriverPreUpdate(int frametime)
{
  dbgCon->Print("{}\n", __func__);

  ;
}


void SND_Update2DChannel(int i, int frametime)
{
  dbgCon->Print("{}\n", __func__);

}


void SND_Update3DChannel(int i, int frametime)
{
  dbgCon->Print("{}\n", __func__);

}


void SND_DriverPostUpdate(int frametime)
{
  dbgCon->Print("{}\n", __func__);

}


void SND_Unpause2DChannel(int index, int timeshift)
{
  dbgCon->Print("{}\n", __func__);

}

void SND_Unpause3DChannel(int index, int timeshift)
{
  dbgCon->Print("{}\n", __func__);
}

void SND_StopStreamChannel(int index)
{
  dbgCon->Print("{}\n", __func__);
}


void SND_PauseStreamChannel(int index)
{
  dbgCon->Print("{}\n", __func__);
}


void SND_SetChannelLevels2DSample(HSAMPLE sample, snd_alias_t *alias, int channels) //Unofficial name
{
  dbgCon->Print("{}\n", __func__);
}

void SND_SetChannelLevels3DSample(HSAMPLE sample, snd_alias_t *alias) //Unofficial name
{
  dbgCon->Print("{}\n", __func__);
}

int SND_StartAlias2DSample(SndStartAliasInfo *startAliasInfo, int *pChannel)
{
  dbgCon->Print("{}\n", __func__);
  return -1;
}



int SND_StartAlias3DSample(SndStartAliasInfo *startAliasInfo, int *pChannel)
{
  dbgCon->Print("{}\n", __func__);
  return -1;
}


void SND_UpdateStreamChannel(int index, int frametime)
{
  dbgCon->Print("{}\n", __func__);
}


void SND_UnpauseStreamChannel(int index, int timeshift)
{
  dbgCon->Print("{}\n", __func__);
}

void SND_Update2DChannelReverb(int index)
{
  dbgCon->Print("{}\n", __func__);
}

void SND_Update3DChannelReverb(int index)
{
  dbgCon->Print("{}\n", __func__);
}



void SND_Set2DChannelFromSaveInfo(int index, snd_save_2D_sample_t *info)
{
  dbgCon->Print("{}\n", __func__);
}


void SND_Set2DChannelPlaybackRate(int index, int rate)
{
  dbgCon->Print("{}\n", __func__);
}

void SND_Set3DChannelPlaybackRate(int index, int rate)
{
  dbgCon->Print("{}\n", __func__);
}

void SND_SetStreamChannelVolume(int index, float level)
{
  dbgCon->Print("{}\n", __func__);
}

void SND_SetStreamChannelFromSaveInfo(int index, snd_save_stream_t *info)
{
  dbgCon->Print("{}\n", __func__);
}


signed int SND_StartAliasStreamOnChannel(SndStartAliasInfo *startAliasInfo, int index)
{
  char soundfilename[128];

  int entchannel = (startAliasInfo->alias0->flags >> 8) & 0x3F;
  if ( !startAliasInfo->alias0->soundFile->exists )
  {
    Com_GetSoundFileName(startAliasInfo->alias0, soundfilename ,sizeof(soundfilename));
    Com_DPrintf(CON_CHANNEL_SOUND, "Tried to play streamed sound '%s' from alias '%s', but it was not found at load time.\n", soundfilename, startAliasInfo->alias0->aliasName);

    return SND_SetPlaybackIdNotPlayed(index);
  }
  channels



  dbgCon->Print("{}\n", __func__);
  return -1;
}




void SND_UpdateStreamChannelReverb(int index)
{
  dbgCon->Print("{}\n", __func__);
}



void SND_SetStreamChannelPlaybackRate(int index, int rate)
{
  dbgCon->Print("{}\n", __func__);
}




