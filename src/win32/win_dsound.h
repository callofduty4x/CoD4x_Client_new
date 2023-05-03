#include <stdint.h>

struct dsound_sample_t;

int mixerSetRecordLevel(const char *SrcName, uint16_t newLevel);
unsigned int mixerGetRecordLevel(char *SrcName);
int mixerGetRecordSource(char *srcName);
int mixerSetRecordSource(char *SrcName);
int mixerSetMicrophoneMute(unsigned char bMute);

