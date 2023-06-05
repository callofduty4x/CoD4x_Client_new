#include <q_shared.h>
#include <game/game_shared.h>
#include <common/netchan.h>
#include <bgame/bg_shared.h>

extern dvar_s* sv_maxclients;
extern dvar_s* sv_privateClients;

#define	MAX_ENT_CLUSTERS	16
#define MAX_BPS_WINDOW 20


enum clientConnectState_t
{
  CS_FREE = 0x0,
  CS_ZOMBIE = 0x1,
  CS_CONNECTED = 0x2,
  CS_PRIMED = 0x3,
  CS_ACTIVE = 0x4
};

enum serverState_t
{
  SS_DEAD = 0x0,
  SS_LOADING = 0x1,
  SS_GAME = 0x2
};

struct svscmd_info_t
{
  char cmd[1024];
  int time;
  int type;
};

struct clientHeader_t
{
  int state;
  int sendAsActive;
  int deltaMessage;
  int rateDelayed;
  netchan_t netchan;
  vec3_t predictedOrigin;
  int predictedOriginServerTime;
};

typedef struct
{
  byte bytedata[2000];
  int longdata[1547];
}statData_t;

struct __align(1) stats_t
{
  int checksum;
  statData_t data;
};


#pragma pack(push,1)
struct __align(1) VoicePacket_t
{
  char talker;
  char data[256];
  int dataSize;
};
#pragma pack(pop)

struct clientSnapshot_t
{
  playerState_s ps;
  int num_entities;
  int num_clients;
  int first_entity;
  int first_client;
  int messageSent;
  int messageAcked;
  int messageSize;
  int serverTime;
};

struct __align(2) client_t
{
  clientHeader_t header;
  const char *dropReason;
  char userinfo[1024];
  svscmd_info_t reliableCommands[128];
  int reliableSequence;
  int reliableAcknowledge;
  int reliableSent;
  int messageAcknowledge;
  int gamestateMessageNum;
  int challenge;
  usercmd_s lastUsercmd;
  int lastClientCommand;
  char lastClientCommandString[1024];
  gentity_s *gentity;
  char name[16];
  int downloading;
  char downloadName[64];
  fileHandle_t download;
  int downloadSize;
  int downloadCount;
  int downloadClientBlock;
  int downloadCurrentBlock;
  int downloadXmitBlock;
  byte *downloadBlocks[8];
  int downloadBlockSize[8];
  qboolean downloadEOF;
  int downloadSendTime;
  char downloadURL[256];
  qboolean wwwOk;
  qboolean downloadingWWW;
  qboolean clientDownloadingWWW;
  qboolean wwwFallback;
  int nextReliableTime;
  int floodprotect;
  int lastPacketTime;
  int lastConnectTime;
  int nextSnapshotTime;
  int timeoutCount;
  clientSnapshot_t frames[32];
  int ping;
  int rate;
  int snapshotMsec;
  int snapshotBackoffCount;
  int pureAuthentic;
  char netchanOutgoingBuffer[131072];
  char netchanIncomingBuffer[2048];
  char cdkeyHash[33];
  uint16_t clscriptid;
  qboolean bIsTestClient;
  int serverId;
  VoicePacket_t voicedata[40];
  int voicePacketCount;
  bool muteList[64];
  bool sendVoice;
  char stats[8192];
  byte statPacketsReceived;
  bool tempPacketDebugging;
};


struct cachedSnapshot_t
{
  int archivedFrame;
  int time;
  int num_entities;
  int first_entity;
  int num_clients;
  int first_client;
  int usesDelta;
};

struct archivedEntityShared_t
{
  int svFlags;
  int clientMask[2];
  float absmin[3];
  float absmax[3];
};

struct archivedEntity_s
{
  entityState_s s;
  archivedEntityShared_t r;
};

struct archivedSnapshot_s
{
  int start;
  int size;
};

struct cachedClient_s
{
  int playerStateExists;
  clientState_s cs;
  playerState_s ps;
};

struct __align(4) challenge_t
{
  netadr_t adr;
  int challenge;
  int time;
  int pingTime;
  int firstTime;
  int firstPing;
  int connected;
  char cdkeyHash[33];
};

struct tempBanSlot_t
{
  char cdkeyHash[32];
  int banTime;
};

struct __align(128) serverStatic_t
{
  cachedSnapshot_t cachedSnapshotFrames[512];
  archivedEntity_s cachedSnapshotEntities[16384];
  int initialized;
  int time;
  int snapFlagServerBit;
  client_t clients[64];
  int numSnapshotEntities;
  int numSnapshotClients;
  int nextSnapshotEntities;
  int nextSnapshotClients;
  entityState_s snapshotEntities[172032];
  clientState_s snapshotClients[131072];
  int nextArchivedSnapshotFrames;
  archivedSnapshot_s archivedSnapshotFrames[1200];
  char archivedSnapshotBuffer[33554432];
  int nextArchivedSnapshotBuffer;
  int nextCachedSnapshotEntities;
  int nextCachedSnapshotClients;
  int nextCachedSnapshotFrames;
  cachedClient_s cachedSnapshotClients[4096];
  int nextHeartbeatTime;
  int nextStatusResponseTime;
  challenge_t challenges[1024];
  netadr_t redirectAddress;
  netadr_t authorizeAddress;
  int sv_lastTimeMasterServerCommunicated;
  netProfileInfo_t OOBProf;
  tempBanSlot_t tempBans[16];
  float mapCenter[3];
};

extern serverStatic_t svs;


typedef struct svEntity_s {
	uint16_t worldSector;
	uint16_t nextEntityInWorldSector;
	archivedEntity_s		baseline;		// 0x04  for delta compression of initial sighting
	int			numClusters;		// if -1, use headnode instead
	int			clusternums[MAX_ENT_CLUSTERS];
	int			lastCluster;		// if all the clusters don't fit in clusternums
	int			linkcontents;
	float		linkmin[2];
	float		linkmax[2];
}svEntity_t; //size: 0x178

typedef struct {
	serverState_t		state;
	int			timeResidual;		// <= 1000 / sv_frame->value
	bool    inFrame;
	qboolean		restarting;		// if true, send configstring changes during SS_LOADING
	int			start_frameTime;		//restartedServerId;	serverId before a map_restart
	int			checksumFeed;		// 0x14 the feed key that we use to compute the pure checksum strings

	struct cmodel_s		*models[MAX_MODELS];

	uint16_t			emptyConfigString;
	uint16_t			configstrings[MAX_CONFIGSTRINGS];

	svEntity_t		svEntities[MAX_GENTITIES]; //0x1b30 size: 0x5e000

	// the game virtual machine will update these on init and changes
	gentity_s		*gentities;	//0x5fb30
	int			gentitySize;	//0x5fb34
	int			num_entities;		// current number, <= MAX_GENTITIES

	playerState_t		*gameClients;		//0x5fb3c
	int			gameClientSize;		//0x5fb40 will be > sizeof(playerState_t) due to game private data
/*
	int				restartTime;
	int				time;*/

	int			skelTimeStamp;
	int			skelMemPos;
	int			bpsWindow[MAX_BPS_WINDOW];
	int			bpsWindowSteps;
	int			bpsTotalBytes;
	int			bpsMaxBytes;
	int			ubpsWindow[MAX_BPS_WINDOW];
	int			ubpsTotalBytes;
	int			ubpsMaxBytes;
	float		ucompAve;
	int			ucompNum;
	char		gametype[MAX_QPATH];
	bool		killserver;
	const char* killreason;
} server_t;//Size: 0x5fc50

extern server_t sv;

#define MAX_STATPACKETS 7

enum svscmd_type
{
  SV_CMD_CAN_IGNORE,
  SV_CMD_RELIABLE
};


void            SV_FreeClientScriptId(client_t *cl);
void            SV_UserinfoChanged( client_t *cl );
void            SV_ClientEnterWorld( client_t *client, usercmd_s *cmd );
void            SV_SendServerCommand(client_t *cl, svscmd_type type, const char *fmt, ...);
