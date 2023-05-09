#include <sound/snd_local.h>
#include <common/qcommon.h>
#include <gfx_d3d/r_cinematic.h>
#include <q_shared.h>
#include <common/com_sndalias.h>


struct MemoryFile;
struct HSAMPLE{
  int null;

};

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


const void* SND_GetDriverHandle()
{
  return NULL;
}

int SND_GetSoundFileSize(const void *pSoundFile)
{
  /*
    assert(pSoundFile);
    const MssSound* internalFile = reinterpret_cast<const MssSound*>(pSoundFile);
    return internalFile->info.data_len;
    */
   return 0;
}


int SND_Get2DChannelPlaybackRate(int index)
{
  return null_snd_drv.channels[index].playback_rate2d;
}

int SND_Get3DChannelPlaybackRate(int index)
{
  return null_snd_drv.channels[index].playback_rate3d;
}

int SND_GetStreamChannelPlaybackRate(int index)
{
  return null_snd_drv.channels[index].playback_rate_stream;
}


float SND_GetStreamChannelVolume(int index)
{
  return null_snd_drv.channels[index].volume_stream;
}





void SND_GetStreamChannelSaveInfo(int index, snd_save_stream_t *info)
{
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
  return 0;
}

int SND_GetStreamChannelLength(int index)
{
  return 0;
}


void SND_Get2DChannelSaveInfo(int index, snd_save_2D_sample_t *info)
{
  info->fraction = 0;
  info->pitch = g_snd.chaninfo[index].pitch;
  info->volume = g_snd.chaninfo[index].basevolume;
}

void SND_Get3DChannelSaveInfo(int index, snd_save_3D_sample_t *info)
{  
  info->fraction = 0;
  info->pitch = g_snd.chaninfo[index].pitch;
  info->volume = g_snd.chaninfo[index].basevolume;
  info->org[0] = 0;
  info->org[1] = 0;
  info->org[2] = 0;
}


int SND_Get2DChannelLength(int index)
{
  return 0;
}

float SND_Get2DChannelVolume(int index)
{
  return 0;
}

float SND_Get3DChannelVolume(int index)
{
  return 0;
}

int SND_Get3DChannelLength(int index)
{
  return 0;
}


bool SND_Is2DChannelFree(int index)
{
  return !g_snd.chaninfo[index].paused && !g_snd.chaninfo[index].startDelay && g_snd.chaninfo[index].alias0 == 0;
}

bool SND_Is3DChannelFree(int index)
{
  return !g_snd.chaninfo[index].paused && !g_snd.chaninfo[index].startDelay && g_snd.chaninfo[index].alias0 == 0;
}

bool SND_IsStreamChannelFree(int index)
{
  return !g_snd.chaninfo[index].paused && !g_snd.chaninfo[index].startDelay && g_snd.chaninfo[index].alias0 == 0;
}


void SND_SetAIL_HWND(HWND hWnd)
{

}

float MSS_SpatializeStream(int index, int listener)
{
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

}

int SND_InitDriver(void)
{
  return 0;
}

void SND_SetRoomtype(int room_type)
{

}



void SND_Set3DPosition(HSAMPLE sample, int listener, const float *org)
{

}

int SND_Set3DPosition(int index, const float *org)
{
  int listIdx = SND_GetListenerIndexNearestToOrigin(org);
  return listIdx; //listener
}

void SND_Stop2DChannel(int index)
{

}

void SND_Stop3DChannel(int index)
{

}

bool SND_IsMultiChannel(void)
{
  return false;
}

void SND_Pause2DChannel(int index)
{
  g_snd.chaninfo[index].paused = 1;
}

void SND_Pause3DChannel(int index)
{
  g_snd.chaninfo[index].paused = 1;
}

void SND_ShutdownDriver(void)
{
  memset(&null_snd_drv, 0, sizeof(null_snd_drv));
}

void SND_DriverPreUpdate(int frametime)
{
    ;
}


void SND_Update2DChannel(int i, int frametime)
{
 
}


void SND_Update3DChannel(int i, int frametime)
{
 
}


void SND_DriverPostUpdate(int frametime)
{

}


void SND_Unpause2DChannel(int index, int timeshift)
{

}

void SND_Unpause3DChannel(int index, int timeshift)
{

}

void SND_StopStreamChannel(int index)
{

}


void SND_PauseStreamChannel(int index)
{

}


void SND_SetChannelLevels2DSample(HSAMPLE sample, snd_alias_t *alias, int channels) //Unofficial name
{

}

void SND_SetChannelLevels3DSample(HSAMPLE sample, snd_alias_t *alias) //Unofficial name
{

}

int SND_StartAlias2DSample(SndStartAliasInfo *startAliasInfo, int *pChannel)
{
  return -1;
}



int SND_StartAlias3DSample(SndStartAliasInfo *startAliasInfo, int *pChannel)
{
  return -1;
}


void SND_UpdateStreamChannel(int index, int frametime)
{

}


void SND_UnpauseStreamChannel(int index, int timeshift)
{

}

void SND_Update2DChannelReverb(int index)
{

}

void SND_Update3DChannelReverb(int index)
{

}



void SND_Set2DChannelFromSaveInfo(int index, snd_save_2D_sample_t *info)
{

}


void SND_Set2DChannelPlaybackRate(int index, int rate)
{

}

void SND_Set3DChannelPlaybackRate(int index, int rate)
{

}

void SND_SetStreamChannelVolume(int index, float level)
{

}

void SND_SetStreamChannelFromSaveInfo(int index, snd_save_stream_t *info)
{

}


signed int SND_StartAliasStreamOnChannel(SndStartAliasInfo *startAliasInfo, int index)
{
  return -1;
}




void SND_UpdateStreamChannelReverb(int index)
{

}



void SND_SetStreamChannelPlaybackRate(int index, int rate)
{

}



