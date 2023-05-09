#include <q_shared.h>

#define _ACCLAIM_IGAADSYSTEM
#include "mss.h"



struct MssSound
{
  _AILSOUNDINFO info;
  char *data;
};

struct LoadedSound
{
  const char *name;
  MssSound sound;
};


struct MSSSpeakerLevels
{
  int speaker;
  int numLevels;
  float levels[2];
};


struct MSSChannelMap
{
  int speakerCount;
  MSSSpeakerLevels speakers[6];
};


