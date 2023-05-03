#include "server_game_shared.h"
#include <bgame/bg_shared.h>

/***************** Verified *******************************/

#define GENTITYNUM_BITS     10  // JPW NERVE put q3ta default back for testing	// don't need to send any more
//#define	GENTITYNUM_BITS		11		// don't need to send any more		(SA) upped 4/21/2001 adjusted: tr_local.h (802-822), tr_main.c (1501), sv_snapshot (206)
#define MAX_GENTITIES       ( 1 << GENTITYNUM_BITS )

// entitynums are communicated with GENTITY_BITS, so any reserved
// values thatare going to be communcated over the net need to
// also be in this range
#define ENTITYNUM_NONE      ( MAX_GENTITIES - 1 )

/**********************************************************/

#define ENTITYNUM_WORLD     ( MAX_GENTITIES - 2 )
#define ENTITYNUM_MAX_NORMAL    ( MAX_GENTITIES - 2 )

#define MAX_NETNAME         16
#define UNUSED_LOCAL_CLIENT_NUM -1

enum sessionState_t
{	SESS_STATE_PLAYING, SESS_STATE_DEAD,
	SESS_STATE_SPECTATOR, SESS_STATE_INTERMISSION
};//0x2f64

enum clientConnected_t{
	CON_DISCONNECTED,
	CON_CONNECTING,
	CON_CONNECTED
};

enum spectatorState_t
{
	SPECTATOR_NOT,
	SPECTATOR_FREE,
	SPECTATOR_FOLLOW,
	SPECTATOR_SCOREBOARD
};

enum playerTeamStateState_t{
	TEAM_BEGIN,     // Beginning a team game, spawn at base
	TEAM_ACTIVE     // Now actively playing
};

struct playerTeamState_t
{
	int location;
};

// client data that stays across multiple respawns, but is cleared
// on each level change or team change at ClientBegin()
struct clientSession_t
{

	sessionState_t sessionState; //0x2f64

	int forceSpectatorClient;
	int killCamEntity;
	int status_icon;
	int archiveTime;			//0x2f74


    int	score; //0x2f78
    int	deaths; //0x2f7c
    int	kills; //0x2f80
    int	assists; //0x2f84
	
	uint16_t scriptPersId;          //0x2f88 the first spawn should be at a cool location
	byte pad2;
	byte pad;
	clientConnected_t connected;	//0x2f8c 
	usercmd_s cmd;                  //0x2f90 we would lose angles if not persistant
	usercmd_s oldcmd;               //0x2fb0 previous command processed by pmove()
	qboolean localClient;           //0x2fd0 true if "ip" info key is "localhost"
	qboolean predictItemPickup;     //0x2fd4 based on cg_predictItems userinfo

	char newnetname[MAX_NETNAME];	//0x2fd8

	int maxHealth;                  // 0x2fe8 for handicapping
	int enterTime;                  // 0x2fec level.time the client entered the game

	playerTeamState_t teamState;    // status in teamplay games
	int voteCount;                  // 0x2ff4 to prevent people from constantly calling votes
	int teamVoteCount;              // to prevent people from constantly calling votes		// N/A

	float moveSpeedScaleMultiplier;	// 0x2ffc

	int viewmodelIndex;				// 0x3000 //Model-index

	qboolean noSpectate;			// 0x3004
	int teamInfo;					// 0x3008 is free (unused)addr 
	
	clientState_s cs;
	int psOffsetTime;
	
};

// this structure is cleared on each ClientSpawn(),
// except for 'client->pers' and 'client->sess'
struct gclient_s {
	// ps MUST be the first element, because the server expects it
	playerState_t ps;               //0x00 communicated by server to clients

	// the rest of the structure is private to game
	
	clientSession_t sess;		//0x2f64
	int spectatorClient;        //0x3074 for chasecam and follow mode
	qboolean noclip;		//0x3078
	qboolean ufo;			//0x307c
	qboolean bFrozen;	//0x3080

	int lastCmdTime;                //0x3084 level.time of last usercmd_t, for EF_CONNECTION
									// we can't just use pers.lastCommand.time, because
									// of the g_sycronousclients case
	//Buttonlogic
	int buttons;			//0x3088
	int oldbuttons;	
	int latched_buttons;
	int buttonsSinceLastFrame;		//0x3094

	vec3_t oldOrigin;

	// sum up damage over an entire frame, so
	// shotgun blasts give a single big kick
	float fGunPitch;	
	float fGunYaw;
	int damage_blood;               // damage taken out of health
	vec3_t damage_from;             //0x30b0 origin for vector calculation
	qboolean damage_fromWorld;      //0x30bc if true, don't use the damage_from vector

	int accurateCount;              // for "impressive" reward sound	N/A

	int accuracy_shots;             // total number of shots		N/A
	int accuracy_hits;              // total number of hits			N/A

	int inactivityTime;             //0x30cc kick players when time > this
	qboolean inactivityWarning;     //0x30d0 qtrue if the five second warning has been given
	int lastVoiceTime;				//0x30d4 ??
	int switchTeamTime;             //0x30d8
    
	int currentAimSpreadScale;		//0x30dc

	int jumpHeight; //Used for per player jump height -- bad place here. This should be part of playerState_t
	int lastFollowedClient;

	int dropWeaponTime;				//JPW NERVE last time a weapon was dropped

	int sniperRifleFiredTime;       //Free member
	float sniperRifleMuzzleYaw;		//Free member
	int PCSpecialPickedUpCount;		//Free member

	EntHandle useHoldEntity; //0x30f8

	int useHoldTime;             //0x30fc time the player switched teams

	int useButtonDone;
	
	int iLastCompassPlayerInfoEnt;

	int compassPingTime;

	int damageTime;
	float v_dmg_roll;
	float v_dmg_pitch;
	vec3_t swayViewAngles;
	vec3_t swayOffset;
	vec3_t swayAngles;
	vec3_t vLastMoveAng;
  	float fLastIdleFactor;

	vec3_t vGunOffset;
  	vec3_t vGunSpeed;

	int weapIdleTime;
	int lastServerTime;
  	int lastSpawnTime;
  	unsigned int lastWeapon;
    bool previouslyFiring;
	bool previouslyUsingNightVision;
	bool previouslySprinting;
	char veh_oldforwardmove; //non original member, used to determine steering direction after player lifted pedal
	qboolean hasRadar;
	int lastStand;
	int lastStandTime;
};

struct keyValueStr_t
{
    const char *key;
    const char *value;
};

struct SpawnVar
{
    bool spawnVarsValid;
    byte pad[3];
    int numSpawnVars;
    keyValueStr_t spawnVars[64];
    int numSpawnVarChars;
    char spawnVarChars[2048];
};

struct trigger_info_t
{
    uint16_t entnum;
    uint16_t otherEntnum;
    int useCount;
    int otherUseCount;
};

struct com_parse_mark_t
{
    int lines;
    const char *text;
    int ungetToken;
    int backup_lines;
    const char *backup_text;
};

struct cached_tag_mat_t
{
    int time;
    int entnum;
    uint16_t name;
    uint16_t pad;
    float tagMat[4][3];
};

typedef struct
{                              //0x8370440
    struct gclient_s *clients; // [maxclients]

    struct gentity_s *gentities;

    int gentitySize;

    int num_entities; // current number, <= MAX_GENTITIES

    struct gentity_s *firstFreeEnt;
    struct gentity_s *lastFreeEnt;

    fileHandle_t logFile;

    int initializing;
    int clientIsSpawning;
    objective_s objectives[16];

    // store latched cvars here that we want to get at often
    int maxclients; //0x1e4
    int framenum;
    int time;         // in msec		0x1ec
    int previousTime; // 0x1f0 so movers can back up when blocked
    int frameTime;    // Gordon: time the frame started, for antilag stuff

    int startTime; // level.time the map was started

    int teamScores[TEAM_NUM_TEAMS]; //0x1fc
    int lastTeammateHealthTime;     // last time of client team location update

    qboolean bUpdateScoresForIntermission; //???? Not known 0x210
    byte teamHasRadar[TEAM_NUM_TEAMS];
    int manualNameChange;           //0x218 Manual Change mode
    int numConnectedClients;        // connected, non-spectators
    int sortedClients[MAX_CLIENTS]; //sorted by rank or score ? 0x220

    // voting state
    char voteString[MAX_STRING_CHARS];        //0x320
    char voteDisplayString[MAX_STRING_CHARS]; //0x720
    int voteTime;                             // level.time vote was called	0xb20
    int voteExecuteTime;                      // time the vote is executed
    int voteYes;                              //0xb28
    int voteNo;                               //0xb2c
    int numVotingClients;                     // set by CalculateRanks

    SpawnVar spawnVars;
    int savePersist;

    struct gentity_s *droppedWeaponCue[32];
    float fFogOpaqueDist;
    float fFogOpaqueDistSqrd;
    int remapCount;
    int currentPlayerClone;
    trigger_info_t pendingTriggerList[256];
    trigger_info_t currentTriggerList[256];
    int pendingTriggerListSize;
    int currentTriggerListSize;
    int finished;
    int bPlayerIgnoreRadiusDamage;
    int bPlayerIgnoreRadiusDamageLatched;
    int registerWeapons;
    int bRegisterItems;
    int currentEntityThink;
    void *openScriptIOFileHandles[1];
    char *openScriptIOFileBuffers[1];
    com_parse_mark_t currentScriptIOLineMark[1];
    cached_tag_mat_t cachedTagMat;
    int scriptPrintChannel;
    float compassMapUpperLeft[2];
    float compassMapWorldSize[2];
    float compassNorth[2];
    struct scr_vehicle_s *vehicles;
    int framerate;
} level_locals_t;

extern level_locals_t level;



const char * CS_DisplayName(clientSession_t *cs, int type);

void Scr_FreeHudElem( struct game_hudelem_s* );
