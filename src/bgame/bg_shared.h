#ifndef BGAME_BG_SHARED_H_
#define BGAME_BG_SHARED_H_

#include <q_shared.h>

struct playerState_s;
struct XAnimTree_s;
struct snd_alias_list_t;
struct XAnim_s;
struct XModel;
struct animation_s;

struct viewState_t
{
  playerState_s *ps;
  int damageTime;
  int time;
  float v_dmg_pitch;
  float v_dmg_roll;
  float xyspeed;
  float frametime;
  float fLastIdleFactor;
  int *weapIdleTime;
};

unsigned int BG_GetNumWeapons();

typedef enum {
	TEAM_FREE,
	TEAM_RED,
	TEAM_BLUE,
	TEAM_SPECTATOR,

	TEAM_NUM_TEAMS
} team_t;


/* 7131 */
struct lerpFrame_t
{
  float yawAngle;
  int yawing;
  float pitchAngle;
  int pitching;
  int animationNumber;
  animation_s *animation;
  int animationTime;
  float oldFramePos[3];
  float animSpeedScale;
  int oldFrameSnapshotTime;
};


struct clientControllers_t
{
  vec3_t angles[6];
  vec3_t tag_origin_angles;
  vec3_t tag_origin_offset;
};


#pragma pack(push, 4)
typedef struct clientInfo_s
{
  int infoValid;
  int nextValid;
  int clientNum;
  char name[16];
  team_t team;
  team_t oldteam;
  int rank;
  int unk1;
  int unk2;
  int score;
  int location;
  int health;
  char model[64];
  char attachModelNames[6][64];
  char attachTagNames[6][64];
  lerpFrame_t legs;
  lerpFrame_t torso;
  float lerpMoveDir;
  float lerpLean;
  float playerAngles[3];
  int leftHandGun;
  int dobjDirty;
  clientControllers_t control;
  unsigned int clientConditions[10][2];
  XAnimTree_s *pXAnimTree;
  int iDObjWeapon;
  char weaponModel;
  char pad[3];
  int stanceTransitionTime;
  int turnAnimEndTime;
  char turnAnimType;
  char pad2[3];  
  int attachedVehEntNum;
  int attachedVehSlotIndex;
  byte hideWeapon;
  byte usingKnife;
  char pad3[2];
}clientInfo_t;
#pragma pack(pop)

struct DObjModel_s;
struct DObj_s;

struct clientState_s
{
  int clientIndex;
  team_t team;
  int modelindex;
  int attachModelIndex[6];
  int attachTagIndex[6];
  char name[16];
  float maxSprintTimeMultiplier;
  int rank;
  int prestige;
  int perks;
  int attachedVehEntNum;
  int attachedVehSlotIndex;
};


/***************************************************************************
CG_Animation types
****************************************************************************/

#pragma pack(push, 8)
struct animation_s
{
  char name[64];
  int initialLerp;
  float moveSpeed;
  int duration;
  int nameHash;
  int flags;
  int64_t movetype;
  int noteType;
};
#pragma pack(pop)


struct scr_animtree_t
{
  XAnim_s *anims;
};

struct scr_anim_s
{
  union
  {
    struct
    {
      uint16_t index;
      uint16_t tree;
    };
    const char *linkPointer;
  };
};

struct animScriptCommand_t
{
  int16_t bodyPart[2];
  int16_t animIndex[2];
  int16_t animDuration[2];
  snd_alias_list_t *soundAlias;
};

struct animScriptCondition_t
{
  int index;
  unsigned int value[2];
};


struct animScriptItem_t
{
  int numConditions;
  animScriptCondition_t conditions[10];
  int numCommands;
  animScriptCommand_t commands[8];
};


struct animScript_t
{
  int numItems;
  animScriptItem_t *items[128];
};


#pragma pack(push, 8)
struct animScriptData_t
{
  animation_s animations[512];
  unsigned int numAnimations;
  animScript_t scriptAnims[1][43];
  animScript_t scriptCannedAnims[1][43];
  animScript_t scriptStateChange[1][1];
  animScript_t scriptEvents[21];
  animScriptItem_t scriptItems[2048];
  int numScriptItems;
  scr_animtree_t animTree;
  uint16_t torsoAnim;
  uint16_t legsAnim;
  uint16_t turningAnim;
  uint16_t pad;
  snd_alias_list_t *( *soundAlias)(const char *);
  int ( *playSoundAlias)(int, snd_alias_list_t *);
  int pad2;
};
#pragma pack(pop)


struct bgs_t
{
  animScriptData_t animScriptData;
  struct 
  {
    scr_animtree_t tree;
    scr_anim_s torso;
    scr_anim_s legs;
    scr_anim_s turning;
  }generic_human;
  int time;
  int latestSnapshotTime;
  int frametime;
  int anim_user;
  XModel *( *GetXModel)(const char *);
  void ( *CreateDObj)(DObjModel_s *, uint16_t, XAnimTree_s *, int, int, clientInfo_t *);
  uint16_t ( *AttachWeapon)(DObjModel_s *, uint16_t, clientInfo_t *);
  struct DObj_s *( *GetDObj)(int, int);
  void ( *SafeDObjFree)(int, int);
  void *( *AllocXAnim)(int);
  clientInfo_t clientinfo[64];
};

extern bgs_t level_bgs;

#endif