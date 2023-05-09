struct snd_alias_list_t* Com_FindSoundAlias(char const*);

struct SoundFile;
struct SndCurve;
struct SpeakerMap;

struct snd_alias_t
{
  const char *aliasName;
  const char *subtitle;
  const char *secondaryAliasName;
  const char *chainAliasName;
  SoundFile *soundFile;
  int sequence;
  float volMin;
  float volMax;
  float pitchMin;
  float pitchMax;
  float distMin;
  float distMax;
  int flags;
  float slavePercentage;
  float probability;
  float lfePercentage;
  float centerPercentage;
  int startDelay;
  SndCurve *volumeFalloffCurve;
  float envelopMin;
  float envelopMax;
  float envelopPercentage;
  SpeakerMap *speakerMap;
};


void *Com_GetSpeakerMap(SpeakerMap *speakerMap, int sourceChannelCount);
void Com_GetSoundFileName(const snd_alias_t *pAlias, char *filename, int size);

