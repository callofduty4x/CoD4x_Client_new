#include "../q_shared.h"
#include "../gfx_d3d/r_shared.h"

#define	MAX_GLOBAL_SERVERS			10000
#define	MAX_OTHER_SERVERS			128

struct Material;
struct Font_s;

struct clientUIActive_t
{
	byte unk1;
	byte cl_running;
	byte unk3;
	byte unk4;
	int  keyCatchers;
	int  unk6;
	connstate_t state;
};

struct ScreenPlacement
{
  float scaleVirtualToReal[2];
  float scaleVirtualToFull[2];
  float scaleRealToVirtual[2];
  float virtualViewableMin[2];
  float virtualViewableMax[2];
  float realViewportSize[2];
  float realViewableMin[2];
  float realViewableMax[2];
  float subScreenLeft;
};

typedef struct
{
  int startTime;
  int duration;
  int fadein;
  int fadeout;
  Material *material[2];
}clientLogo_t;



struct trDebugString_t
{
  float xyz[3];
  float color[4];
  float scale;
  char text[96];
};


struct clientDebugStringInfo_t
{
  int max;
  int num;
  struct trDebugString_t *strings;
  int *durations;
};


struct trDebugLine_t
{
  vec3_t start;
  vec3_t end;
  vec4_t color;
  int depthTest;
};


struct clientDebugLineInfo_t
{
  int max;
  int num;
  struct trDebugLine_t *lines;
  int *durations;
};

struct clientDebug_t
{
  int prevFromServer;
  int fromServer;
  struct clientDebugStringInfo_t clStrings;
  struct clientDebugStringInfo_t svStringsBuffer;
  struct clientDebugStringInfo_t svStrings;
  struct clientDebugLineInfo_t clLines;
  struct clientDebugLineInfo_t svLinesBuffer;
  struct clientDebugLineInfo_t svLines;
};


typedef struct{
  netadr_t adr;
  char allowAnonymous;
  char pswrd;
  char pure;
  char con_disabled;
  char netType;
  byte clients;
  byte maxClients;
  char visible;
  char friendlyFire;
  char kc;
  char hardcore;
  char od;
  char hw;
  char dom;
  char voice;
  char punkbuster;
  char field_24;
  char mod;
  uint16_t minPing;
  uint16_t maxPing;
  uint16_t ping;
  uint32_t queryTime;
  char serveralive;
  char hostName[32];
  char mapName[32];
  char game[24];
  char gameType[16];
  byte humanPlayers;
  char padding[2];
}serverInfo_t;


struct clientStatic_t
{
	qboolean	quit;
	qboolean	hunkUsersStarted;

	char		servername[MAX_OSPATH];		// name of server from original connect (used by reconnect)

	qboolean	rendererStarted;
	qboolean	soundStarted;

	qboolean	uiStarted;
	int			frametime;			// msec since last frame

	int			realtime;			// ignores pause
	int			realFrametime;		// ignoring pause, so console always works

	clientLogo_t logo;

	vec3_t mapCenter;

	int			numlocalservers;
	serverInfo_t	localServers[MAX_OTHER_SERVERS];


	int currentPingServer; //Index of the current server which gets send a ping request
	int countPingServers; //Count how many servers got pinged
	int totalSeenServers;
	int globalServerRequestTime;
	int numglobalservers;
	serverInfo_t globalServers[MAX_GLOBAL_SERVERS];
	serverInfo_t mplayerServers[MAX_GLOBAL_SERVERS];
	int numFavoriteServers;
	serverInfo_t favoriteServers[MAX_OTHER_SERVERS];

	int pingUpdateSource;		// source currently pinging or updating

/*
	// update server info
	int			nummplayerservers;
	int			masterNum;
	int			downloadFilesCompleted; //Is required to really go to next file when WWW download failed once and FS is not yet restarted
	qboolean	wwwdlCheckedHead;
	int			updateServerChallenge;
	char		updateChallenge[MAX_TOKEN_CHARS];
	char		updateInfoString[MAX_INFO_STRING];
*/
	netadr_t	authorizeServer;
	Material*	whiteMaterial;
	Material*	consoleMaterial;
	Font_s*		consoleFont;

	// DHM - Nerve :: Auto-update Info
	char 		emptydata[5*64];
	netadr_t 	updateServer;

	vidConfig_t vidConfig;
	struct clientDebug_t debug;

	fileHandle_t download;
	char downloadTempName[MAX_OSPATH];
	char downloadName[MAX_OSPATH];
	int downloadNumber;
	int downloadBlock;
	int downloadCount;
	int downloadSize;
	char downloadList[MAX_INFO_STRING];
	qboolean downloadRestart;
	int field_30491C;
	int disconnectForWWWdl;
	int field_304924;
	int cl_wwwDlDisconnected;
	char wwwDownloadName[MAX_QPATH];
	vec3_t debugRenderPos;
};

extern clientStatic_t cls;
extern ScreenPlacement scrPlaceFull;



void        CL_VoiceTransmit(int localClientNum);
int         Client_SendVoiceData(int bytes, char *enc_buffer);
void        Key_Shutdown();
void        Con_Shutdown();
void        Con_ShutdownChannels();
qboolean    CL_MouseEvent(int x, int y, int dx, int dy);
void        CL_Shutdown(int localClientNum);
void        CL_ShutdownRef();
int         Key_ClearStates(int a1);

clientUIActive_t *CL_GetLocalClientUIGlobals(const int localClientNum);
bool CL_AllLocalClientsDisconnected();
void SCR_UpdateScreen();
