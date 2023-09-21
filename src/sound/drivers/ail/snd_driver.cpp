#include <sound/snd_local.h>
#include <common/qcommon.h>
#include <gfx_d3d/r_cinematic.h>
#include <q_shared.h>
#include <common/com_sndalias.h>
#include "mss.h"
#include "snd_driver.h"


struct MemoryFile;

dvar_s* snd_khz;
dvar_s* snd_outputConfiguration;

const char *snd_outputConfigurationStrings[] = { "Windows default", "Mono", "Stereo", "4 speakers", "5.1 speakers" };
int mss_spec[5] = { 16, 1, 32, 80, 96 };

struct MssFileHandle
{
  unsigned int id;
  MssFileHandle *next;
  int handle;
  char fileName[128];
  unsigned int hashCode;
  int offset;
  int fileOffset;
  int fileLength;
};


struct __align(4) MssLocal
{
  _DIG_DRIVER *driver;
  _SAMPLE *handle_sample[40];
  _STREAM *handle_stream[13];
  MssFileHandle fileHandle[13];
  MssFileHandle *freeFileHandle;
  bool isMultiChannel;
};

MssLocal milesGlob;

const void* SND_GetDriverHandle()
{
  return reinterpret_cast<const void*>(milesGlob.driver);
}

void SND_SetAIL_HWND(HWND hWnd)
{
    if ( g_snd.Initialized2d ){
        AIL_set_DirectSound_HWND(milesGlob.driver, hWnd);
    }
}

U32 AILCALLBACK MSS_FileOpenCallback(const MSS_FILE *Filename, UINTa* FileHandle)
{
  if(FS_FOpenFileReadStream(Filename, (int*)FileHandle) < 0)
  {
    return false;
  }
  return true;
}

void AILCALLBACK MSS_FileCloseCallback(UINTa FileHandle)
{
    FS_FCloseFile(FileHandle);
}

S32 AILCALLBACK MSS_FileSeekCallback(UINTa FileHandle, S32 Offset, U32 Type)
{
  switch (Type)
  {
    case AIL_FILE_SEEK_CURRENT:
      FS_Seek(FileHandle, Offset, FS_SEEK_CUR);
      break;
    case AIL_FILE_SEEK_END:
      FS_Seek(FileHandle, Offset, FS_SEEK_END);
      break;
    case AIL_FILE_SEEK_BEGIN:
      FS_Seek(FileHandle, Offset, FS_SEEK_SET);
      break;
    default:
      return 0;
  }
  unsigned int newfilepos = FS_FTell(FileHandle);
  
  return newfilepos;


}

U32 AILCALLBACK MSS_FileReadCallback(UINTa FileHandle, void* Buffer, U32 Bytes)
{
  int readbytes = FS_Read(Buffer, Bytes, FileHandle);
  return readbytes;

}

float MSS_SpatializeStream(int index, int listener)
{
  float lerp = g_snd.chaninfo[index].lerp;

  float lerpDistMin = (1.0 - lerp) * g_snd.chaninfo[index].alias0->distMin + lerp * g_snd.chaninfo[index].alias1->distMin;
  float lerpDistMax = (1.0 - lerp) * g_snd.chaninfo[index].alias0->distMax + lerp * g_snd.chaninfo[index].alias1->distMax;
  float radius = Vec3Distance(g_snd.chaninfo[index].org, g_snd.listeners[listener].orient.origin);
  float attenuation = SND_Attenuate(g_snd.chaninfo[index].alias0->volumeFalloffCurve, radius, lerpDistMin, lerpDistMax);
  return attenuation;
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
  int i;
  _SAMPLE *sample_handle;

  for ( i = 0; i < g_snd.max_2D_channels + g_snd.max_3D_channels; ++i )
  {
    sample_handle = AIL_allocate_sample_handle(milesGlob.driver /*, i > 7*/);
    milesGlob.handle_sample[i] = sample_handle;
    if ( !sample_handle )
    {
        Com_Error(ERR_DROP, "MILES sound sample allocation failed on channel %i", i + 1);
    }
    AIL_init_sample(milesGlob.handle_sample[i], 1, 0);
  }
  g_snd.ambient_track = 1;
}

bool MSS_InitDigitalDriver()
{
    struct _DIG_DRIVER *driver;
    S32 n_logical_channels;
    MSS_MC_SPEC speakConf;
    const char* error;

    Com_Printf(CON_CHANNEL_SOUND, "Attempting %i kHz %i bit [%s] sound\n", 44, 16, snd_outputConfigurationStrings[snd_outputConfiguration->current.integer]);
    AIL_set_preference(1, 53);
    driver = AIL_open_digital_driver(44100, 16, mss_spec[snd_outputConfiguration->current.integer], 0);
    if ( driver )
    {
      AIL_speaker_configuration(driver, 0, &n_logical_channels, 0, &speakConf);
      milesGlob.isMultiChannel = n_logical_channels > 2 || !n_logical_channels;
    }
    milesGlob.driver = driver;
    if ( milesGlob.driver )
    {
      AIL_set_3D_distance_factor(milesGlob.driver, 0.0254);
      AIL_set_3D_rolloff_factor(milesGlob.driver, 0);
      AIL_set_speaker_configuration(milesGlob.driver, 0, 0, 3.0);
      g_snd.Initialized2d = 1;
      g_snd.Initialized3d = 1;
      g_snd.max_2D_channels = 8;
      g_snd.max_3D_channels = 32;
      g_snd.max_stream_channels = 13;
      g_snd.playback_rate = 0x7FFFFFFF;
      g_snd.playback_channels = (mss_spec[snd_outputConfiguration->current.integer] != 1) + 1;
      g_snd.timescale = 1.0;
      return true;
    
    }

    error = AIL_last_error();
    Com_PrintError(CON_CHANNEL_SOUND, "ERROR: Couldn't initialize digital driver: %s\n", error);
    return false;
}


int SND_InitDriver(void)
{
  snd_khz = Dvar_RegisterInt("snd_khz", 44, 11, 44, 0x21u, "The game sound frequency.");
  AIL_set_file_callbacks(MSS_FileOpenCallback, MSS_FileCloseCallback, MSS_FileSeekCallback, MSS_FileReadCallback);
  AIL_set_redist_directory("miles");
  snd_outputConfiguration = Dvar_RegisterEnum("snd_outputConfiguration", snd_outputConfigurationStrings, 0, 0x21u, "Sound output configuration");
  if ( AIL_startup( ) )
  {
    if(MSS_InitDigitalDriver())
    {
        MSS_InitChannels();
        MSS_InitEq();
        return 1;
    }else{

        AIL_shutdown();
        memset(&milesGlob, 0, sizeof(milesGlob));
    }
  }
  if ( Dvar_GetInt("r_vc_compile") != 2 )
  {
    Com_Printf(CON_CHANNEL_SOUND, "Miles sound system initialization failed\n");
  }
  return 0;
}

void SND_SetRoomtype(int room_type)
{
  AIL_set_room_type(milesGlob.driver, room_type);
  AIL_set_digital_master_reverb_levels(milesGlob.driver, 1.0, g_snd.effect->wetlevel);
}



void SND_Set3DPosition(HSAMPLE sample, int listener, const float *org)
{
  vec3_t vect, vect2;
  
  VectorSubtract(org, g_snd.listeners[listener].orient.origin, vect);

  MatrixTransposeTransformVector(vect, g_snd.listeners[listener].orient.axis, vect2);
  AIL_set_sample_3D_position(sample, -vect2[1], vect2[2], vect2[0]);
}

int SND_Set3DPosition(int index, const float *org)
{
  HSAMPLE sample = milesGlob.handle_sample[index];
  int listIdx = SND_GetListenerIndexNearestToOrigin(org);
  SND_Set3DPosition(sample, listIdx, org);
  return listIdx; //listener
}

void SND_Stop2DChannel(int index)
{
  AIL_end_sample(milesGlob.handle_sample[index]);
  SND_ResetChannelInfo(index);
  SND_RemoveVoice(g_snd.chaninfo[index].entchannel);
}

void SND_Stop3DChannel(int index)
{
  AIL_end_sample(milesGlob.handle_sample[index]);
  SND_ResetChannelInfo(index);
  SND_RemoveVoice(g_snd.chaninfo[index].entchannel);
}

bool SND_IsMultiChannel(void)
{
  return milesGlob.isMultiChannel;
}

void SND_Pause2DChannel(int index)
{
  AIL_stop_sample(milesGlob.handle_sample[index]);
  g_snd.chaninfo[index].paused = 1;
}

void SND_Pause3DChannel(int index)
{
  AIL_stop_sample(milesGlob.handle_sample[index]);
  g_snd.chaninfo[index].paused = 1;
}

void SND_ShutdownDriver(void)
{
  R_Cinematic_StopPlayback();
  R_Cinematic_SyncNow();
  AIL_shutdown();

  memset(&milesGlob, 0, sizeof(milesGlob));
}

void SND_DriverPreUpdate(int frametime)
{
    ;
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

  if ( !milesGlob.handle_sample[index] )
  {
    return true;
  }
  return !g_snd.chaninfo[index].paused && !g_snd.chaninfo[index].startDelay && g_snd.chaninfo[index].alias0 == 0;
}

void SND_Update2DChannel(int i, int frametime)
{
  snd_alias_t *alias0;
  int flags;
  int startDelay;
  int timeoffset;
  float newvolume;
  float LerpedSlavePercentage;
  float basevolume;

  if ( g_snd.chaninfo[i].paused )
  {
    return;
  }
  alias0 = g_snd.chaninfo[i].alias0;
  if ( !alias0 || !g_snd.chaninfo[i].alias1 )
  {
    return;
  }
  basevolume = g_snd.chaninfo[i].basevolume;
  if ( (!g_snd.chaninfo[i].startDelay && AIL_sample_status(milesGlob.handle_sample[i]) == 2) || 
        (alias0->chainAliasName && g_snd.chaninfo[i].totalMsec + g_snd.chaninfo[i].startTime - g_snd.time <= 0) )
  {
    SND_StopChannelAndPlayChainAlias(i);
    return;
  }
  flags = alias0->flags;

  if ( g_snd.slaveLerp != 0.0 && !g_snd.chaninfo[i].master && (flags & 4) != 0 )
  {
    LerpedSlavePercentage = SND_GetLerpedSlavePercentage(alias0->slavePercentage);
    basevolume *= LerpedSlavePercentage;
  }

  newvolume = (float)(basevolume * g_snd.channelvol->channelvol[(flags & 0x3F00) >> 8].volume) * g_snd.volume;
  AIL_set_sample_volume_levels(milesGlob.handle_sample[i], newvolume, newvolume);

  startDelay = g_snd.chaninfo[i].startDelay;
  if ( startDelay )
  {
    timeoffset = startDelay - frametime;
    if ( timeoffset <= 0 )
    {
      timeoffset = 0;
    }
    g_snd.chaninfo[i].startDelay = timeoffset;
    if ( !timeoffset )
    {
      AIL_resume_sample(milesGlob.handle_sample[i]/*, frametime*/);
    }
  }
}


void SND_Update3DChannel(int i, int frametime)
{
    snd_alias_t *alias0, *alias1;
    int ListenerIndexNearestToOrigin;
    float attenuatedVolume;
    int flags;
    float newvolume;
    int startDelay;
    float attenuation;
    float LerpedSlavePercentage;
    float lerpDistMin;
    float lerp;
    float lerpDistMax;
    float basevolume;
    vec3_t org;
    float radius;

    if ( !g_snd.chaninfo[i].paused )
    {
        return;
    }
    alias0 = g_snd.chaninfo[i].alias0;
    alias1 = g_snd.chaninfo[i].alias1;
    if ( alias0 == nullptr || alias1 == nullptr)
    {
        return;
    }
    lerp = g_snd.chaninfo[i].lerp;
    basevolume = g_snd.chaninfo[i].basevolume;
    if ( (!g_snd.chaninfo[i].startDelay && AIL_sample_status(milesGlob.handle_sample[i]) == 2)
        || (alias0->chainAliasName && g_snd.chaninfo[i].totalMsec + g_snd.chaninfo[i].startTime - g_snd.time <= 0) )
    {
        SND_StopChannelAndPlayChainAlias(i);
        return;
    }

    SND_GetCurrent3DPosition(g_snd.chaninfo[i].sndEnt, g_snd.chaninfo[i].offset, org);

    ListenerIndexNearestToOrigin = SND_Set3DPosition(i, org);

    lerpDistMin = (1.0 - lerp) * alias0->distMin + lerp * alias1->distMin;
    lerpDistMax = (1.0 - lerp) * alias0->distMax + lerp * alias1->distMax;

    radius = Vec3Distance(org, g_snd.listeners[ListenerIndexNearestToOrigin].orient.origin);
    attenuation = SND_Attenuate(alias0->volumeFalloffCurve, radius, lerpDistMin, lerpDistMax);
    
    
    attenuatedVolume = attenuation * basevolume;
    flags = alias0->flags;

    if ( g_snd.slaveLerp != 0.0 && !g_snd.chaninfo[i].master  && (flags & 4) != 0 )
    {
        LerpedSlavePercentage = SND_GetLerpedSlavePercentage(alias0->slavePercentage);
        attenuatedVolume *= LerpedSlavePercentage;
    }

    newvolume = attenuatedVolume * g_snd.channelvol->channelvol[(flags & 0x3F00) >> 8].volume * g_snd.volume;
    if ( g_snd.chaninfo[i].soundFileInfo.srcChannelCount != 2 )
    {
        newvolume = newvolume * 0.5;
    }
    AIL_set_sample_volume_levels(milesGlob.handle_sample[i], newvolume, newvolume);


    startDelay = g_snd.chaninfo[i].startDelay;
    if ( startDelay )
    {
        int timeoffset = startDelay - frametime;
        if ( timeoffset <= 0 )
        {
            timeoffset = 0;
        }
        g_snd.chaninfo[i].startDelay = timeoffset;
        if ( !timeoffset )
        {
            AIL_resume_sample(milesGlob.handle_sample[i]/*, frametime*/);
        }
    }

}


void SND_DriverPostUpdate(int frametime)
{
  ;
}

int SND_GetSoundFileSize(const void *pSoundFile)
{
    assert(pSoundFile);
    const MssSound* internalFile = reinterpret_cast<const MssSound*>(pSoundFile);
    return internalFile->info.data_len;
}

void SND_Unpause2DChannel(int index, int timeshift)
{
    if ( !g_snd.chaninfo[index].startDelay )
    {
        AIL_resume_sample(milesGlob.handle_sample[index]);
    }
    g_snd.chaninfo[index].soundFileInfo.endtime += timeshift;
    g_snd.chaninfo[index].startTime += timeshift;
    g_snd.chaninfo[index].paused = false;
}

void SND_Unpause3DChannel(int index, int timeshift)
{
    if ( !g_snd.chaninfo[index].startDelay )
    {
        AIL_resume_sample(milesGlob.handle_sample[index]);
    }
    g_snd.chaninfo[index].soundFileInfo.endtime += timeshift;
    g_snd.chaninfo[index].startTime += timeshift;
    g_snd.chaninfo[index].paused = false;
}

void SND_StopStreamChannel(int index)
{
    RANGEASSERT(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));

    AIL_close_stream(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]);
    milesGlob.handle_sample[index] = nullptr;
    SND_ResetChannelInfo(index);
    SND_RemoveVoice(g_snd.chaninfo[index].entchannel);
}

int SND_Get2DChannelLength(int index)
{
    int total_milliseconds;

    assertarray(index, milesGlob.handle_sample);

    AIL_sample_ms_position(milesGlob.handle_sample[index], &total_milliseconds, 0);
    return total_milliseconds;
}

float SND_Get2DChannelVolume(int index)
{
    float left_level, right_level;
    
    assertarray(index, milesGlob.handle_sample);

    AIL_sample_volume_levels(milesGlob.handle_sample[index], &left_level, &right_level);
    if ( g_snd.chaninfo[index].soundFileInfo.srcChannelCount == 2 )
    {
        return left_level;
    }
    return left_level + right_level;
}

int SND_Get3DChannelLength(int index)
{
    int total_milliseconds;

    assertarray(index, milesGlob.handle_sample);

    AIL_sample_ms_position(milesGlob.handle_sample[index], &total_milliseconds, 0);
    return total_milliseconds;
}

float SND_Get3DChannelVolume(int index)
{
    float left_level, right_level;
    
    assertarray(index, milesGlob.handle_sample);

    AIL_sample_volume_levels(milesGlob.handle_sample[index], &left_level, &right_level);
    if ( g_snd.chaninfo[index].soundFileInfo.srcChannelCount == 2 )
    {
        return left_level;
    }
    return left_level + right_level;
}

void SND_PauseStreamChannel(int index)
{
    assertrange(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));

    AIL_pause_stream(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)], 1);
    g_snd.chaninfo[index].paused = true;
}


void SND_SetChannelLevels2DSample(HSAMPLE sample, snd_alias_t *alias, int channels) //Unofficial name
{
  float level_array[18];
  MSSChannelMap *SpeakerMap = reinterpret_cast<MSSChannelMap*>(Com_GetSpeakerMap(alias->speakerMap, channels));

  if ( SpeakerMap )
  {
    memset(level_array, 0, sizeof(level_array));

    for(int i = 0; i < SpeakerMap->speakerCount; ++i)
    {
        MSSSpeakerLevels* speakers = &SpeakerMap->speakers[i];
        float level = speakers->levels[0];
        if ( speakers->levels[0] < speakers->levels[1] )
        {
          level = speakers->levels[1];
        }
        level_array[i] = level;
    }
    AIL_set_sample_channel_levels(sample, level_array, SpeakerMap->speakerCount);
  }
}

void SND_SetChannelLevels3DSample(HSAMPLE sample, snd_alias_t *alias) //Unofficial name
{
  if ( SND_IsMultiChannel() )
  {
    int n_levels;
    float level_array[2];

    AIL_sample_channel_levels(sample, &n_levels);
    
    for( int i = 0; i < n_levels; ++i )
    {
        level_array[i] = 1.0;
    }
    if ( alias->centerPercentage != 0.0 && milesGlob.isMultiChannel )
    {
      for(int i = 0; i < n_levels; ++i)
      {
        level_array[i] *= (1.0 - alias->centerPercentage);
      }
    }
    AIL_set_sample_channel_levels(sample, level_array, n_levels);
  }
}

int SND_StartAlias2DSample(SndStartAliasInfo *startAliasInfo, int *pChannel)
{
  int entchannel;
  int playbackId;
  int playbackRate;
  double LerpedSlavePercentage;
  float wetlevel;
  float fraction;
  float timeskew;
  int newSampleChannel;
  struct _SAMPLE *sample;
  int timeshift;
  MssSound *p_sound;
  float newvolume;
  int total_milliseconds;

  entchannel = (startAliasInfo->alias0->flags >> 8) & 0x3F;
  if ( !SND_HasFreeVoice(entchannel) )
  {
    return -1;
  }
  newSampleChannel = SND_FindFree2DChannel(startAliasInfo, entchannel);
  if ( pChannel )
  {
    *pChannel = newSampleChannel;
  }
  if ( newSampleChannel < 0 )
  {
    return -1;
  }
  sample = milesGlob.handle_sample[newSampleChannel];

  p_sound = &startAliasInfo->alias0->soundFile->u.loadSnd->sound;
  
  
  AIL_set_sample_info(sample, &p_sound->info);
  
  playbackRate = AIL_sample_playback_rate(sample);
  
  LerpedSlavePercentage = startAliasInfo->pitch * (float)playbackRate;
  if ( startAliasInfo->timescale )
  {
    LerpedSlavePercentage *= g_snd.timescale;
  }
  
  AIL_set_sample_playback_rate(sample, static_cast<int>(LerpedSlavePercentage));

  newvolume = startAliasInfo->volume * g_snd.volume * g_snd.channelvol->channelvol[entchannel].volume;
  if ( g_snd.slaveLerp != 0.0 && !startAliasInfo->master && (startAliasInfo->alias0->flags & 4) != 0 )
  {
    LerpedSlavePercentage = SND_GetLerpedSlavePercentage(startAliasInfo->alias0->slavePercentage);
    newvolume = newvolume * LerpedSlavePercentage;
  }

  SND_SetChannelLevels2DSample(sample, startAliasInfo->alias0, p_sound->info.channels);

  AIL_set_sample_volume_levels(milesGlob.handle_sample[newSampleChannel], newvolume, newvolume);
  AIL_set_sample_loop_count(sample, !(startAliasInfo->alias0->flags & 1));
  
  if ( startAliasInfo->alias0 && (!snd_enableReverb->current.enabled || (startAliasInfo->alias0->flags & 0x10) != 0) ){
    wetlevel = 0.0;
  }else{
    wetlevel = g_snd.effect->wetlevel;
  }

  AIL_set_sample_reverb_levels(sample, 1.0, wetlevel);
  // SND_Get2DChannelLength
  AIL_sample_ms_position(sample, &total_milliseconds, 0);
  timeshift = startAliasInfo->timeshift;
  
  if ( timeshift >= total_milliseconds )
  {
    return SND_SetPlaybackIdNotPlayed(newSampleChannel);
  }
  fraction = startAliasInfo->fraction;
  
  if ( fraction != 0.0 )
  {
    timeshift = static_cast<int>(fraction * static_cast<float>(total_milliseconds));
    
  }else if ( !timeshift && (startAliasInfo->alias0->flags & 0x20) != 0){
    timeskew = static_cast<float>(total_milliseconds) * randomf();
    timeshift = static_cast<int>(timeskew) & 0xFFFFFF80;
  }

  if(timeshift)
  {
    startAliasInfo->startDelay = 0;
  }

  AIL_set_sample_ms_position(sample, timeshift);
  if ( !startAliasInfo->startDelay )
  {
    if ( !g_snd.paused || !g_snd.pauseSettings[entchannel])
    {
        AIL_resume_sample(sample);
    }
  }

  total_milliseconds += startAliasInfo->startDelay;
  if ( (startAliasInfo->alias0->flags & 1) != 0 )
  {
    total_milliseconds = 0;
  }
  SND_SetChannelStartInfo(newSampleChannel, startAliasInfo);
  SND_SetSoundFileChannelInfo(newSampleChannel, p_sound->info.channels, p_sound->info.rate, total_milliseconds, timeshift, SFLS_LOADED);
  playbackId = SND_AcquirePlaybackId(newSampleChannel, total_milliseconds);
  if ( playbackId != -1 )
  {
    SND_AddVoice(entchannel);
  }
  return playbackId;
}



int SND_StartAlias3DSample(SndStartAliasInfo *startAliasInfo, int *pChannel)
{
  int entchannel;
  int playbackId;
  int playbackRate;
  double LerpedSlavePercentage;
  float wetlevel;
  float fraction;
  float timeskew;
  int newSampleChannel;
  struct _SAMPLE *sample;
  int timeshift;
  MssSound *p_sound;
  float newvolume;
  int total_milliseconds;

  entchannel = (startAliasInfo->alias0->flags >> 8) & 0x3F;
  if ( !SND_HasFreeVoice(entchannel) )
  {
    return -1;
  }
  newSampleChannel = SND_FindFree3DChannel(startAliasInfo, entchannel);
  if ( pChannel )
  {
    *pChannel = newSampleChannel;
  }
  if ( newSampleChannel < 0 )
  {
    return -1;
  }
  sample = milesGlob.handle_sample[newSampleChannel];

  p_sound = &startAliasInfo->alias0->soundFile->u.loadSnd->sound;
  float lerp = startAliasInfo->lerp;
  
  float lerpDistMin = (1.0 - lerp) * startAliasInfo->alias0->distMin + lerp * startAliasInfo->alias1->distMin;
  float lerpDistMax = (1.0 - lerp) * startAliasInfo->alias0->distMax + lerp * startAliasInfo->alias1->distMax;

  AIL_set_sample_info(sample, &p_sound->info);
  
  int listenerIndexNearestToOrigin = SND_GetListenerIndexNearestToOrigin(startAliasInfo->org);

  float radius = Vec3Distance(startAliasInfo->org, g_snd.listeners[listenerIndexNearestToOrigin].orient.origin);
  float attenuation = SND_Attenuate(startAliasInfo->alias0->volumeFalloffCurve, radius, lerpDistMin, lerpDistMax);

  newvolume = startAliasInfo->volume * g_snd.volume * g_snd.channelvol->channelvol[entchannel].volume;
  newvolume *= attenuation;
  if ( g_snd.slaveLerp != 0.0 && !startAliasInfo->master && (startAliasInfo->alias0->flags & 4) != 0 )
  {
    LerpedSlavePercentage = SND_GetLerpedSlavePercentage(startAliasInfo->alias0->slavePercentage);
    newvolume = newvolume * LerpedSlavePercentage;
  }

  SND_SetChannelLevels3DSample(sample, startAliasInfo->alias0);

  if ( g_snd.chaninfo[newSampleChannel].soundFileInfo.srcChannelCount != 2 )
  {
      newvolume = newvolume * 0.5;
  }
  AIL_set_sample_volume_levels(sample, newvolume, newvolume);
  AIL_set_sample_3D_distances(sample, startAliasInfo->alias0->distMax, startAliasInfo->alias0->distMin, 1);

  playbackRate = AIL_sample_playback_rate(sample);
  
  LerpedSlavePercentage = startAliasInfo->pitch * (float)playbackRate;
  if ( startAliasInfo->timescale )
  {
    LerpedSlavePercentage *= g_snd.timescale;
  }
  
  AIL_set_sample_playback_rate(sample, static_cast<int>(LerpedSlavePercentage));

  SND_Set3DPosition(newSampleChannel, startAliasInfo->org);
  AIL_set_sample_loop_count(sample, !(startAliasInfo->alias0->flags & 1));


  if ( startAliasInfo->alias0 && (!snd_enableReverb->current.enabled || (startAliasInfo->alias0->flags & 0x10) != 0) ){
    wetlevel = 0.0;
  }else{
    wetlevel = g_snd.effect->wetlevel;
  }

  AIL_set_sample_reverb_levels(sample, 1.0, wetlevel);

  if ( startAliasInfo->timescale )
  {
    total_milliseconds = (float)(1000 * p_sound->info.samples) * g_snd.timescale / (float)LerpedSlavePercentage;
  }
  else
  {
    total_milliseconds = 1000 * p_sound->info.samples / (float)LerpedSlavePercentage;
  }

  timeshift = startAliasInfo->timeshift;
 
  if ( timeshift >= total_milliseconds )
  {
    return SND_SetPlaybackIdNotPlayed(newSampleChannel);
  }

  fraction = startAliasInfo->fraction;
  
  if ( fraction != 0.0 )
  {
    timeshift = static_cast<int>(fraction * static_cast<float>(total_milliseconds));
  }else if ( timeshift ){
    timeshift = startAliasInfo->timeshift;
  }else if ( (startAliasInfo->alias0->flags & 0x20) != 0){
    timeskew = static_cast<float>(total_milliseconds) * randomf();
    timeshift = static_cast<int>(timeskew) & 0xFFFFFF80;
  }
  if(timeshift)
  {
    startAliasInfo->startDelay = 0;
  }
  
  float ftimesh = static_cast<float>(timeshift) / static_cast<float>(total_milliseconds) * static_cast<float>(p_sound->info.data_len);
  AIL_set_sample_ms_position(sample, ftimesh);

  if ( !startAliasInfo->startDelay )
  {
    if ( !g_snd.paused || !g_snd.pauseSettings[entchannel])
    {
        AIL_resume_sample(sample);
    }
  }

  total_milliseconds += startAliasInfo->startDelay;
  if ( (startAliasInfo->alias0->flags & 1) != 0 )
  {
    total_milliseconds = 0;
  }
  SND_SetChannelStartInfo(newSampleChannel, startAliasInfo);
  SND_SetSoundFileChannelInfo(newSampleChannel, p_sound->info.channels, p_sound->info.rate, total_milliseconds, timeshift, SFLS_LOADED);
  playbackId = SND_AcquirePlaybackId(newSampleChannel, total_milliseconds);
  if ( playbackId != -1 )
  {
    SND_AddVoice(entchannel);
  }
  return playbackId;
}


void SND_UpdateStreamChannel(int index, int frametime)
{
  int startDelay;
  int timeoffset;
  float newvolume;
  float LerpedSlavePercentage;
  float basevolume;

  if ( g_snd.chaninfo[index].paused )
  {
    return;
  }
  if(index <= 44 && !SND_UpdateBackgroundVolume(index - ARRAY_COUNT(milesGlob.handle_sample), frametime))
  {
    return;
  }
  if ( !g_snd.chaninfo[index].alias0 || !g_snd.chaninfo[index].alias1 )
  {
    return;
  }

  basevolume = g_snd.chaninfo[index].basevolume;
  if ( !g_snd.chaninfo[index].startDelay && AIL_stream_status(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]) == 2 )
  {
    SND_StopChannelAndPlayChainAlias(index);
    return;
  }

  int entchannel = (g_snd.chaninfo[index].alias0->flags >> 8) & 0x3F;
  if ( SND_IsAliasChannel3D(entchannel) )
  {
    SND_GetCurrent3DPosition(g_snd.chaninfo[index].sndEnt, g_snd.chaninfo[index].offset, g_snd.chaninfo[index].org);
    
    int listenerIndexNearestToOrigin = SND_GetListenerIndexNearestToOrigin(g_snd.chaninfo[index].org);
    
    SND_Set3DPosition(AIL_stream_sample_handle(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]), listenerIndexNearestToOrigin, g_snd.chaninfo[index].org);
    float attenuation = MSS_SpatializeStream(index, listenerIndexNearestToOrigin);
    basevolume *= attenuation;
  }
  
  if ( g_snd.slaveLerp != 0.0 && !g_snd.chaninfo[index].master && (g_snd.chaninfo[index].alias0->flags & 4) != 0 )
  {
    LerpedSlavePercentage = SND_GetLerpedSlavePercentage(g_snd.chaninfo[index].alias0->slavePercentage);
    basevolume *= LerpedSlavePercentage;
  }

  newvolume = (float)(basevolume * g_snd.channelvol->channelvol[entchannel].volume) * g_snd.volume;
  
  if ( g_snd.chaninfo[index].soundFileInfo.srcChannelCount != 2 && SND_IsAliasChannel3D(entchannel) )
  {
    newvolume *= 0.5;
  }
  AIL_set_sample_volume_levels(AIL_stream_sample_handle(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]), newvolume, newvolume);

  startDelay = g_snd.chaninfo[index].startDelay;
  if ( startDelay )
  {
    timeoffset = startDelay - frametime;
    if ( timeoffset <= 0 )
    {
      timeoffset = 0;
    }
    g_snd.chaninfo[index].startDelay = timeoffset;
    if ( !timeoffset )
    {
      AIL_pause_stream(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)], 0);
    }
  }
}


void SND_Get2DChannelSaveInfo(int index, snd_save_2D_sample_t *info)
{
  int total_milliseconds;
  int current_milliseconds;

  AIL_sample_ms_position(milesGlob.handle_sample[index], &total_milliseconds, &current_milliseconds);

  info->fraction = (float)current_milliseconds / (float)total_milliseconds;
  info->pitch = g_snd.chaninfo[index].pitch;
  AIL_sample_volume_pan(milesGlob.handle_sample[index], &info->volume, 0);
  if ( g_snd.volume == 0.0 )
  {
    info->volume = g_snd.chaninfo[index].basevolume;
  }else{
    info->volume = info->volume / g_snd.volume;
  }
}

void SND_Get3DChannelSaveInfo(int index, snd_save_3D_sample_t *info)
{
  int total_milliseconds;
  int current_milliseconds;

  AIL_sample_ms_position(milesGlob.handle_sample[index], &total_milliseconds, &current_milliseconds);
  
  info->fraction = (float)current_milliseconds / (float)total_milliseconds;
  info->pitch = g_snd.chaninfo[index].pitch;
  AIL_sample_volume_pan(milesGlob.handle_sample[index], &info->volume, 0);
  if ( g_snd.volume == 0.0 )
  {
    info->volume = g_snd.chaninfo[index].basevolume;
  }else{
    info->volume = info->volume / g_snd.volume;
  }
  AIL_sample_3D_position(milesGlob.handle_sample[index], &info->org[0], &info->org[2], &info->org[1]);
}

void SND_UnpauseStreamChannel(int index, int timeshift)
{
  assertrange(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));

  if ( !g_snd.chaninfo[index].startDelay )
  {
    AIL_pause_stream(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)], 0);
  }
  g_snd.chaninfo[index].soundFileInfo.endtime += timeshift;
  g_snd.chaninfo[index].startTime += timeshift;
  g_snd.chaninfo[index].paused = 0;
}

void SND_Update2DChannelReverb(int index)
{
  if ( g_snd.chaninfo[index].alias0 && (!snd_enableReverb->current.enabled || (g_snd.chaninfo[index].alias0->flags & 0x10) != 0) )
  {
    AIL_set_sample_reverb_levels(milesGlob.handle_sample[index], 1.0, 0.0);
  }else{
    AIL_set_sample_reverb_levels(milesGlob.handle_sample[index], 1.0, g_snd.effect->wetlevel);
  }
}

void SND_Update3DChannelReverb(int index)
{
  if ( g_snd.chaninfo[index].alias0 && (!snd_enableReverb->current.enabled || (g_snd.chaninfo[index].alias0->flags & 0x10) != 0) )
  {
    AIL_set_sample_reverb_levels(milesGlob.handle_sample[index], 1.0, 0.0);
  }else{
    AIL_set_sample_reverb_levels(milesGlob.handle_sample[index], 1.0, g_snd.effect->wetlevel);
  }
}

int SND_GetDriverCPUPercentage(void)
{
  return AIL_digital_CPU_percent(milesGlob.driver);
}

int SND_GetStreamChannelLength(int index)
{
  assertrange(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));

  int total_milliseconds;

  AIL_stream_ms_position(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)], &total_milliseconds, 0);
  return total_milliseconds;
}


void SND_GetStreamChannelSaveInfo(int index, snd_save_stream_t *info)
{
  HSAMPLE handle;
  int total_milliseconds;
  int current_milliseconds;

  assertrange(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));

  handle = AIL_stream_sample_handle(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]);
  AIL_stream_ms_position(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)], &total_milliseconds, &current_milliseconds);
  
  info->fraction = (float)current_milliseconds / (float)total_milliseconds;
  if ( g_snd.chaninfo[index].timescale )
  {
    info->rate = (int)((float)AIL_sample_playback_rate(handle) / g_snd.timescale);
  }
  else
  {
    info->rate = AIL_sample_playback_rate(handle);
  }
  info->basevolume = g_snd.chaninfo[index].basevolume;
  AIL_sample_volume_pan(handle, &info->volume, 0);
  if ( g_snd.volume == 0.0 )
  {
    info->volume = g_snd.chaninfo[index].basevolume;
  }else{
    info->volume = info->volume / g_snd.volume;
  }
  VectorCopy(g_snd.chaninfo[index].org, info->org);
}

void SND_Set2DChannelFromSaveInfo(int index, snd_save_2D_sample_t *info)
{
  float newvolume;

  newvolume = info->volume * g_snd.volume;
  AIL_set_sample_volume_levels(milesGlob.handle_sample[index], newvolume, newvolume);
}


void SND_Set2DChannelPlaybackRate(int index, int rate)
{
  AIL_set_sample_playback_rate(milesGlob.handle_sample[index], rate);
}

void SND_Set3DChannelPlaybackRate(int index, int rate)
{
  AIL_set_sample_playback_rate(milesGlob.handle_sample[index], rate);
}

void SND_SetStreamChannelVolume(int index, float level)
{
  int entchannel = (g_snd.chaninfo[index].alias0->flags >> 8) & 0x3F;

  assertrange(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));
  HSAMPLE sample = AIL_stream_sample_handle(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]);

  if ( g_snd.chaninfo[index].soundFileInfo.srcChannelCount != 2 && SND_IsAliasChannel3D( entchannel ) )
  {
    AIL_set_sample_volume_levels(sample, level * 0.5, level * 0.5);
  }else{
    AIL_set_sample_volume_levels(sample, level, level);
  }
}

void SND_SetStreamChannelFromSaveInfo(int index, snd_save_stream_t *info)
{
  float level;

  level = info->volume * g_snd.volume;
  SND_SetStreamChannelVolume(index, level);

}


signed int SND_StartAliasStreamOnChannel(SndStartAliasInfo *startAliasInfo, int index)
{
  double wetlevel;
  int timeshift;
  char soundfilename[128];
  char sndpathname[256];

  int entchannel = (startAliasInfo->alias0->flags >> 8) & 0x3F;

  if ( !SND_HasFreeVoice(entchannel) )
  {
    return -1;
  }
  if ( !startAliasInfo->alias0->soundFile->exists )
  {
    Com_GetSoundFileName(startAliasInfo->alias0, soundfilename ,sizeof(soundfilename));
    Com_DPrintf(CON_CHANNEL_SOUND, "Tried to play streamed sound '%s' from alias '%s', but it was not found at load time.\n", soundfilename, startAliasInfo->alias0->aliasName);

    return SND_SetPlaybackIdNotPlayed(index);
  }

  assertrange(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));

  if ( milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)] )
  {
    AIL_close_stream(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample) ]);
    milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)] = 0;
  }
  
  Com_GetSoundFileName(startAliasInfo->alias0, soundfilename ,sizeof(soundfilename));
  Com_sprintf(sndpathname, sizeof(sndpathname), "sound/%s", soundfilename);

  HSTREAM stream = AIL_open_stream(milesGlob.driver, sndpathname, 0);
  if ( !stream )
  {
    Com_PrintError(CON_CHANNEL_SOUND, "Couldn't play stream '%s' from alias '%s' - %s\n", sndpathname, startAliasInfo->alias0->aliasName, AIL_last_error());
    return SND_SetPlaybackIdNotPlayed(index);
  }
  milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)] = stream;
  HSAMPLE sample = AIL_stream_sample_handle(stream);
  int sndtype;
  AIL_stream_info(stream, 0, &sndtype, 0, 0);

  //SND_UpdateEq_Maybe(entchannel, sample);
  int playbackRate = AIL_sample_playback_rate(sample);
  float playbackRateAdjusted = static_cast<float>(playbackRate) * startAliasInfo->pitch;
  if ( startAliasInfo->timescale )
  {
    playbackRateAdjusted *= g_snd.timescale;
  }
  AIL_set_sample_playback_rate(sample, playbackRateAdjusted);

  float newvolume = startAliasInfo->volume * g_snd.volume * g_snd.channelvol->channelvol[entchannel].volume;
  if ( g_snd.slaveLerp != 0.0 && !startAliasInfo->master && (startAliasInfo->alias0->flags & 4) != 0 )
  {
    float LerpedSlavePercentage = SND_GetLerpedSlavePercentage(startAliasInfo->alias0->slavePercentage);
    newvolume = newvolume * LerpedSlavePercentage;
  }
  AIL_set_stream_loop_count(stream, !(startAliasInfo->alias0->flags & 1));
  if ( startAliasInfo->alias0 && (!snd_enableReverb->current.enabled || (startAliasInfo->alias0->flags & 0x10) != 0) )
  {
    wetlevel = 0.0;
  }else{
    wetlevel = g_snd.effect->wetlevel;
  }
  AIL_set_sample_reverb_levels(sample, 1.0, wetlevel);

  int total_milliseconds;
  AIL_stream_ms_position(stream, &total_milliseconds, nullptr);
  timeshift = startAliasInfo->timeshift;

  if ( timeshift >= total_milliseconds )
  {
    return SND_SetPlaybackIdNotPlayed(index);
  }

  if ( !total_milliseconds )
  {
    Com_PrintError(CON_CHANNEL_ERROR, "ERROR: Sound file '%s' is zero length, invalid\n", sndpathname);
    return SND_SetPlaybackIdNotPlayed(index);
  }

  if ( startAliasInfo->fraction != 0.0 )
  {
    timeshift = static_cast<int>(startAliasInfo->fraction * static_cast<float>(total_milliseconds));
  }else if ( timeshift ){
    timeshift = startAliasInfo->timeshift;
  }else if ( (startAliasInfo->alias0->flags & 0x20) != 0){
    float timeskew = static_cast<float>(total_milliseconds) * randomf();
    timeshift = static_cast<int>(timeskew) & 0xFFFFFF80;
  }
  if(timeshift)
  {
    startAliasInfo->startDelay = 0;
  }

  AIL_set_stream_ms_position(stream, timeshift);
  if ( !startAliasInfo->startDelay && (!g_snd.paused || !g_snd.pauseSettings[entchannel]) )
  {
    AIL_pause_stream(stream, 0);
  }
  total_milliseconds += startAliasInfo->startDelay;
  if ( (startAliasInfo->alias0->flags & 1) != 0 )
  {
    total_milliseconds = 0;
  }

  VectorCopy( startAliasInfo->org, g_snd.chaninfo[index].org );
  SND_SetChannelStartInfo(index, startAliasInfo);
  
  int chanCount = ((sndtype & 2) != 0) + 1;
  SND_SetSoundFileChannelInfo(index, chanCount, playbackRate, total_milliseconds, timeshift, SFLS_LOADED);

  if ( SND_IsAliasChannel3D(entchannel) )
  {
    SND_GetCurrent3DPosition(g_snd.chaninfo[index].sndEnt, g_snd.chaninfo[index].offset, g_snd.chaninfo[index].org);
    int listener = SND_GetListenerIndexNearestToOrigin(g_snd.chaninfo[index].org);
    SND_Set3DPosition(AIL_stream_sample_handle(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]), listener, g_snd.chaninfo[index].org);

    float attenuation = MSS_SpatializeStream(index, listener);
    newvolume *= attenuation;
    AIL_set_sample_3D_distances(sample, startAliasInfo->alias0->distMax, startAliasInfo->alias0->distMin, 1);
    SND_SetChannelLevels3DSample(sample, startAliasInfo->alias0); //Unofficial name
  }
  else
  {
    SND_SetChannelLevels2DSample(sample, startAliasInfo->alias0, chanCount); //Unofficial name
  }

  SND_SetStreamChannelVolume(index, newvolume);
  int playbackId = SND_AcquirePlaybackId(index, total_milliseconds);
  if ( playbackId != -1 )
  {
    SND_AddVoice(entchannel);
  }
  return playbackId;

}


float SND_GetStreamChannelVolume(int index)
{
  float right_level;
  float left_level;

  assertrange(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));
  
  int entchannel = (g_snd.chaninfo[index].alias0->flags >> 8) & 0x3F;

  AIL_sample_volume_levels(AIL_stream_sample_handle(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]), &left_level, &right_level);

  if ( g_snd.chaninfo[index].soundFileInfo.srcChannelCount != 2 && SND_IsAliasChannel3D(entchannel) )
  {
    return left_level + right_level;
  }
  return left_level;
}

int SND_Get2DChannelPlaybackRate(int index)
{
  return AIL_sample_playback_rate(milesGlob.handle_sample[index]);
}

int SND_Get3DChannelPlaybackRate(int index)
{
  return AIL_sample_playback_rate(milesGlob.handle_sample[index]);
}


void SND_UpdateStreamChannelReverb(int index)
{
  assertrange(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));
  HSAMPLE sample = AIL_stream_sample_handle(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]);

  if ( g_snd.chaninfo[index].alias0 && (!snd_enableReverb->current.enabled || (g_snd.chaninfo[index].alias0->flags & 0x10) != 0) )
  {
    AIL_set_sample_reverb_levels(sample, 1.0, 0.0);
  }else{
    AIL_set_sample_reverb_levels(sample, 1.0, g_snd.effect->wetlevel);
  }
}


int SND_GetStreamChannelPlaybackRate(int index)
{
  assertrange(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));
  HSAMPLE sample = AIL_stream_sample_handle(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]);

  return AIL_sample_playback_rate(sample);
}

void SND_SetStreamChannelPlaybackRate(int index, int rate)
{
  assertrange(index, ARRAY_COUNT(milesGlob.handle_sample), ARRAY_COUNT(milesGlob.handle_sample) + ARRAY_COUNT(milesGlob.handle_stream));
  
  HSAMPLE sample = AIL_stream_sample_handle(milesGlob.handle_stream[index - ARRAY_COUNT(milesGlob.handle_sample)]);
  AIL_set_sample_playback_rate(sample, rate);
}



