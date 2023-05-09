#include <q_shared.h>

struct snd_alias_t;
struct SndCurve;

extern dvar_s* snd_enableReverb;

struct snd_volume_info_t
{
  float volume;
  float goalvolume;
  float goalrate;
};

struct __align(4) snd_channelvolgroup
{
  snd_volume_info_t channelvol[64];
  bool active;
};

struct __align(4) snd_enveffect
{
  int roomtype;
  float drylevel;
  float drygoal;
  float dryrate;
  float wetlevel;
  float wetgoal;
  float wetrate;
  bool active;
};

struct orientation_t
{
  float origin[3];
  float axis[3][3];
};

struct __align(4) snd_listener
{
  orientation_t orient;
  int clientNum;
  bool active;
};

struct snd_amplifier
{
  snd_listener *listener;
  int minRadius;
  int maxRadius;
  float falloffExp;
  float minVol;
  float maxVol;
};

struct snd_entchannel_info_t
{
  char name[64];
  int priority;
  bool is3d;
  bool isRestricted;
  bool isPausable;
  int maxVoices;
  int voiceCount;
};

enum SndFileLoadingState
{
  SFLS_UNLOADED = 0x0,
  SFLS_LOADING = 0x1,
  SFLS_LOADED = 0x2,
};

struct SndFileSpecificChannelInfo
{
  SndFileLoadingState loadingState;
  int srcChannelCount;
  int baserate;
  int endtime;
};


union SndEntHandle
{
  struct
  {
    unsigned int entIndex;
  }field;
  int handle;
};

enum SndLengthId
{
  SndLengthNotify_Script,
  SndLengthNotify_Subtitle,
  SndLengthNotifyCount
};

struct sndLengthNotifyInfo
{
  SndLengthId id[4];
  void *data[4];
  int count;
};



struct snd_channel_info_t
{
  SndFileSpecificChannelInfo soundFileInfo;
  SndEntHandle sndEnt;
  int entchannel;
  int startDelay;
  int startTime;
  int looptime;
  int totalMsec;
  int playbackId;
  sndLengthNotifyInfo lengthNotifyInfo;
  float basevolume;
  float pitch;
  snd_alias_t *alias0;
  snd_alias_t *alias1;
  int saveIndex0;
  int saveIndex1;
  float lerp;
  float org[3];
  float offset[3];
  bool paused;
  bool master;
  bool timescale;
  snd_alias_system_t system;
};

struct snd_background_info_t
{
  float goalvolume;
  float goalrate;
};

struct snd_local_t
{
  bool Initialized2d;
  bool Initialized3d;
  bool paused;
  int playbackIdCounter;
  unsigned int playback_rate;
  int playback_channels;
  float timescale;
  int pausetime;
  int cpu;
  
  struct __align(4)
  {
    char buffer[16384];
    int size;
    bool compress;
  }restore;

  float volume;
  snd_volume_info_t mastervol;
  snd_channelvolgroup channelVolGroups[4];
  snd_channelvolgroup *channelvol;
  snd_background_info_t background[5];
  int ambient_track;
  float slaveLerp;
  snd_enveffect envEffects[3];
  snd_enveffect *effect;
  bool defaultPauseSettings[64];
  bool pauseSettings[64];
  snd_listener listeners[2];
  int time;
  int looptime;
  snd_amplifier amplifier;
  snd_entchannel_info_t entchaninfo[64]; //4dec
  int entchannel_count;
  snd_channel_info_t chaninfo[53];
  int max_2D_channels;
  int max_3D_channels;
  int max_stream_channels;
};

enum SND_EQTYPE
{
  SND_EQTYPE_FIRST = 0x0,
  SND_EQTYPE_LOWPASS = 0x0,
  SND_EQTYPE_HIGHPASS = 0x1,
  SND_EQTYPE_LOWSHELF = 0x2,
  SND_EQTYPE_HIGHSHELF = 0x3,
  SND_EQTYPE_BELL = 0x4,
  SND_EQTYPE_LAST = 0x4,
  SND_EQTYPE_COUNT = 0x5,
  SND_EQTYPE_INVALID = 0x5
};

struct SndStartAliasInfo
{
  snd_alias_t *alias0;
  snd_alias_t *alias1;
  float lerp;
  SndEntHandle sndEnt;
  float org[3];
  float volume;
  float pitch;
  int timeshift;
  float fraction;
  int startDelay;
  bool master;
  bool timescale;
  snd_alias_system_t system;
};

struct LoadedSound;


struct StreamFileNameRaw
{
  const char *dir;
  const char *name;
};


union StreamFileInfo
{
  StreamFileNameRaw raw;
};


struct StreamFileName
{
  StreamFileInfo info;
};

struct StreamedSound
{
  StreamFileName filename;
};

union SoundFileRef
{
  LoadedSound *loadSnd;
  StreamedSound streamSnd;
};

struct SoundFile
{
  char type;
  char exists;
  SoundFileRef u;
};

struct snd_save_stream_t
{
  float fraction;
  int rate;
  float basevolume;
  float volume;
  float pan;
  float org[3];
};

struct snd_save_2D_sample_t
{
  float fraction;
  float pitch;
  float volume;
  float pan;
};

struct snd_save_3D_sample_t
{
  float fraction;
  float pitch;
  float volume;
  float org[3];
};

extern snd_local_t g_snd;

int       SND_GetListenerIndexNearestToOrigin(const vec_t *origin);
void      SND_ResetChannelInfo(int index);
void      SND_RemoveVoice(int entchannel);
void      SND_StopChannelAndPlayChainAlias(int chanId);
float     SND_GetLerpedSlavePercentage(float baseSlavePercentage);
void      SND_GetCurrent3DPosition(SndEntHandle sndEnt, const float *offset, float *pos_out);
float     SND_Attenuate(SndCurve *volumeFalloffCurve, float radius, float mindist, float maxdist);
bool      SND_HasFreeVoice(int entchannel);
int       SND_FindFree2DChannel(SndStartAliasInfo *startAliasInfo, int entchannel);
int       SND_FindFree3DChannel(SndStartAliasInfo *startAliasInfo, int entchannel);
int       SND_SetPlaybackIdNotPlayed(int index);
void      SND_SetChannelStartInfo(int index, SndStartAliasInfo *SndStartAliasInfo);
void      SND_SetSoundFileChannelInfo(int index, int srcChannelCount, int baserate, int total_msec, int start_msec, SndFileLoadingState loadingState);
int       SND_AcquirePlaybackId(int index, int totalMsec);
void      SND_AddVoice(int entchannel);
bool      SND_IsAliasChannel3D(int entchannel);
bool      SND_UpdateBackgroundVolume(int track, int frametime);
