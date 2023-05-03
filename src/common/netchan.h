#include <q_shared.h>

struct netProfilePacket_t
{
  int iTime;
  int iSize;
  int bFragment;
};

/* 812 */
struct netProfileStream_t
{
  netProfilePacket_t packets[60];
  int iCurrPacket;
  int iBytesPerSecond;
  int iLastBPSCalcTime;
  int iCountedPackets;
  int iCountedFragments;
  int iFragmentPercentage;
  int iLargestPacket;
  int iSmallestPacket;
};

struct netProfileInfo_t
{
  netProfileStream_t send;
  netProfileStream_t recieve;
};

struct netchan_t
{
  int outgoingSequence;
  netsrc_t sock;
  int dropped;
  int incomingSequence;
  netadr_t remoteAddress;
  int qport;
  int fragmentSequence;
  int fragmentLength;
  char *fragmentBuffer;
  int fragmentBufferSize;
  int unsentFragments;
  int unsentFragmentStart;
  int unsentLength;
  char *unsentBuffer;
  int unsentBufferSize;
  netProfileInfo_t prof;
};

void Netchan_Setup(netsrc_t sock, netchan_t *chan, netadr_t adr, int qport, char *outgoingBuffer, int outgoingBufferSize, char *incomingBuffer, int incomingBufferSize);

