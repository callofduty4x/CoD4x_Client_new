#include "../q_shared.h"
#define _ACCLAIM_IGAADSYSTEM

#include "mss.h"


struct MilesGlob_t
{
  HDIGDRIVER dig;
  HSAMPLE hStreams[64];
  char unknown[1992];
};

extern MilesGlob_t milesGlob;

#pragma pack(push, 1)
struct sndChannel_t
{
  char soundSourceName[64];
  int field_40;
  int16_t field_44;
  char field_46;
  char field_47;
  int field_48;
  int field_4C;
};


struct sndEnvironment_t
{
  int field_0;
  float field_4;
  float field_8;
  float field_C;
  float field_10;
  float field_14;
  float field_18;
};

struct sndChannelsAttr_t
{
  vec3_t vect[64];
  int field_300;
  char field_304[2300];
  int field_C00;
};


struct sndAxis_t
{
  int field_0;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
  int field_14;
  int field_18;
  int field_1C;
  int field_20;
};

struct sndObj_t
{
  vec3_t org;
  sndAxis_t field_C;
  int field_30;
  int field_34;
};

#pragma pack(push, 1)
struct snd_streamChannels
{
  int active_maybe;
  int field_4;
  int sampleRateDiv;
  int field_C;
  int field_10;
  int streamChannelMapIndex;
  int field_18;
  char field_1C[48];
  int field_4C;
  int channelVolume;
  int field_54;
  int field_58;
  int field_5C;
  int field_60;
  int field_64;
  int field_68;
  int field_6C;
  int field_70;
  int field_74;
  int field_78;
  int field_7C;
  int field_80;
  int field_84;
  int field_88;
};
#pragma pack(pop)


struct sndSystem_t
{
  bool8 initialized;
  bool8 field_1;
  bool8 field_2;
  bool8 field_3;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
  int field_14;
  int soundCpuUsage;
  int field_1C;
  char field_20[16384];
  int field_4020;
  float field_4024;
  float field_4028;
  float field_402C;
  float field_4030;
  sndChannelsAttr_t channelVects;
  int field_4C38;
  int field_4C3C;
  int field_4C40;
  sndChannelsAttr_t *channelVectPtr;
  int field_4C48;
  char field_4C4C[36];
  int field_4C70;
  float field_4C74;
  sndEnvironment_t sndEnv;
  char field_4C94;
  char field_4C95;
  char field_4C96;
  char field_4C97;
  int field_4C98;
  char field_4C9C[24];
  int field_4CB4;
  char field_4CB8[28];
  int field_4CD4;
  sndEnvironment_t *sndEnvPtr;
  byte field_4CDC[64];
  byte field_4D1C[64];
  sndObj_t clSndLocalClientObj[1];
  sndObj_t defaultSndObj;
  int soundTimer;
  int initTime2;
  int curSndObj;
  int field_4DD8;
  int field_4DDC;
  int field_4DE0;
  int field_4DE4;
  int field_4DE8;
  sndChannel_t sndChannels[64];
  int entChannelCount;
  int field_61F0;
  int field_61F4;
  int field_61F8;
  int field_61FC;
  int field_6200[1384];
  int field_77A0;
  int field_77A4;
  int field_77A8;
  int field_77AC;
  int field_77B0;
  int field_77B4;
  int field_77B8;
  int field_77BC;
  int field_77C0;
  int field_77C4;
  int field_77C8;
  int field_77CC;
  snd_streamChannels streamChannels[12];
};
#pragma pack(pop)


extern sndSystem_t g_snd;