#include <game/game_shared.h>


extern bool con_ignoreMatchPrefixOnly;
extern int con_inputMaxMatchesShown;
extern const struct dvar_s *con_matchPrefixOnly;
extern const struct dvar_s *cl_noprint;

enum print_msg_dest_t
{
  CON_DEST_CONSOLE = 0x0,
  CON_DEST_MINICON = 0x1,
  CON_DEST_ERROR = 0x2,
  CON_DEST_GAME_FIRST = 0x3,
  CON_DEST_GAME1 = 0x3,
  CON_DEST_GAME2 = 0x4,
  CON_DEST_GAME3 = 0x5,
  CON_DEST_GAME_LAST = 0x5,
  CON_DEST_COUNT = 0x6
};

typedef struct
{
  int valid;
  int snapFlags;
  int serverTime;
  int messageNum;
  int deltaNum;
  int ping;
  int field_18;
  playerState_t ps;
  int numEntities;
  int numClients;
  int parseEntitiesNum;
  int parseClientsNum;
  int serverCommandNum;
}clSnapshot_t;

struct clientActive_t
{
  char usingAds;
  char pad[3];
  int timeoutcount;
  clSnapshot_t snap;

  int field_2F9C;
  int serverTime;
  int oldServerTime;
/*  Disabled till needed!
  int field_2FA8;
  int serverTimeDelta;
  int field_2FB0;
  int field_2FB4;
  int field_2FB8;

  gameState_t gameState;

  char mapname[64];
  int parseEntitiesNum;
  int parseClientsNum;
  int mouseDx[2];
  int mouseDy[2];
  int mouseIndex;
  byte stanceHeld;
  byte pad2[3];
  StanceState stance;
  StanceState stancePosition;
  int stanceTime;
  int cgameUserCmdWeapon;
  int cgameUserCmdOffHandIndex;
  float cgameFOVSensitivityScale;
  float cgameMaxPitchSpeed;
  float cgameMaxYawSpeed;
  vec3_t cgameKickAngles;
  vec3_t cgameOrigin;
  vec3_t cgameVelocity;
  vec3_t cgameViewangles;
  int cgameBobCycle;
  int cgameMovementDir;
  int cgameExtraButtons;
  int cgamePredictedDataServerTime;
  float viewangles[3];
  int serverId;
  int dword_C84FE8;
  char byte_C84FEC[262144];
  char gap_656BC[4];
  int dword_CC4FF0;
  char anonymous_0[4];
  usercmd_t cmds[128];
  int cmdNumber;
  ClientArchiveData_t clientArchive[256];
  int clientArchiveIndex;
  outPacket_t outPackets[32];
  clSnapshot_t snapshots[32];
  entityState_s entityBaselines[1024];
  entityState_s parseEntities[2048];
  clientState_t parseClients[2048];
  char gap_1B1AD0[264];
  int field_1B1BD8;
*/
};


extern clientActive_t clients[1];

bool Con_CycleAutoComplete(int step);
void Con_AllowAutoCompleteCycling(bool isAllowed);
void Con_PageUp();
void Con_PageDown();
void Con_Top();
void Con_Bottom();
bool Con_CommitToAutoComplete();
bool Con_CancelAutoComplete();
bool Console_IsClientDisconnected();
bool Console_IsRconCmd(const char *commandString);
void Con_Restricted_AddBuf(const char *buf);
const char * Con_TokenizeInput();
bool Con_IsDvarCommand(const char *cmd);
bool Con_HasTooManyMatchesToShow();
void Con_ForEach(bool isDvarCommand, void (*callbackDvar)(const char *), void (*callbackCmd)(const char *));
void Con_AutoCompleteFromList(const char **strings, unsigned int stringCount, const char *prefix, char *completed, unsigned int sizeofCompleted);
void Con_CheckResize();
bool Con_IsChannelOpen(int channel);
bool Con_IsChannelVisible(print_msg_dest_t dest, int channel, int errorflags);
bool Con_AnySpaceAfterCommand();


void SCR_DrawSmallStringExt(int x, int y, const char *string, const float *setColor);

void CL_LookupColor(int, unsigned char c, float *color);


static inline clientActive_t* CL_GetLocalClientGlobals(const int localClientNum)
{
    assert(localClientNum == 0);
    return &clients[localClientNum];
}