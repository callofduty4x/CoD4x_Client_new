#include "game_shared.h"

enum team_s: int;

struct trigger_ent_t
{
  int threshold;
  int accumulate;
  int timestamp;
  int singleUserEntIndex;
  byte requireLookAt;
};

struct item_ent_t
{
  int ammoCount;
  int clipAmmoCount;
  int index;
};


struct mover_ent_t
{
  float decelTime;
  float aDecelTime;
  float speed;
  float aSpeed;
  float midTime;
  float aMidTime;
  vec3_t pos1;
  vec3_t pos2;
  vec3_t pos3;
  vec3_t apos1;
  vec3_t apos2;
  vec3_t apos3;
};

struct corpse_ent_t
{
  int deathAnimStartTime;
};


enum MissileStage
{
  MISSILESTAGE_SOFTLAUNCH = 0x0,
  MISSILESTAGE_ASCENT = 0x1,
  MISSILESTAGE_DESCENT = 0x2,
};

enum MissileFlightMode
{
  MISSILEFLIGHTMODE_TOP = 0x0,
  MISSILEFLIGHTMODE_DIRECT = 0x1,
};


struct missile_ent_t
{
  float time;
  int timeOfBirth;
  float travelDist;
  vec3_t surfaceNormal;
  team_s team;
  vec3_t curvature;
  int targetEntNum;
  vec3_t targetOffset;
  enum MissileStage stage;
  enum MissileFlightMode flightMode;
};


struct entityShared_s
{
	byte		linked;				//0xf4 qfalse if not in any good cluster

	byte		bmodel;				//0xf5 if false, assume an explicit mins / maxs bounding box
							// only set by trap_SetBrushModel
	byte		svFlags;
	byte		pad1;

	int			clientMask[2];
	byte		inuse;
	byte		pad2[3];
	int			broadcastTime;

	vec3_t		mins, maxs;		//0x108  //0x114  from SharedEntity_t

	int			contents;		// CONTENTS_TRIGGER, CONTENTS_SOLID, CONTENTS_BODY, etc
						// a non-solid entity should set to 0

	vec3_t		absmin, absmax;		//0x124  //0x130 derived from mins/maxs and origin + rotation

	// currentOrigin will be used for all collision detection and world linking.
	// it will not necessarily be the same as the trajectory evaluation for the current
	// time, because each entity must be moved one at a time after time is advanced
	// to avoid simultanious collision issues
	vec3_t		currentOrigin;		//0x13c
	vec3_t		currentAngles;		//0x148

	// when a trace call is made and passEntityNum != ENTITYNUM_NONE,
	// an ent will be excluded from testing if:
	// ent->s.number == passEntityNum	(don't interact with self)
	// ent->r.ownerNum == passEntityNum	(don't interact with your own missiles)
	// entity[ent->r.ownerNum].r.ownerNum == passEntityNum	(don't interact with other missiles from owner)
  	EntHandle	ownerNum;
	int			eventTime;
};

struct gentity_s {
	entityState_s s;
	entityShared_s r;               // shared by both the server system and game

	// DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
	// EXPECTS THE FIELDS IN THAT ORDER!
	//================================

	struct gclient_s    *client;            // NULL if not a client		0x15c

	struct turretInfo_s *pTurretInfo;
	struct scr_vehicle_s *scr_vehicle;

	uint16_t model;
	byte physicsObject;
	byte takedamage;
	byte active;
	byte nopickup;
	byte handler;
	byte team;

	uint16_t classname;
	uint16_t target;

	uint16_t targetname;
	uint16_t pad;
	unsigned int attachIgnoreCollision;

	int spawnflags;
	int flags;
	int eventTime;

	int freeAfterEvent;
	int unlinkAfterEvent;
	int clipmask;
	int processedFrame;
	EntHandle parent;
	int nextthink;

  int health; /* 0x1A0 */
	int maxHealth;
	int damage;
	int count;

	struct gentity_s *chain;

	//	char unknown[104];
	union{
		struct item_ent_t item[2];
		struct trigger_ent_t trigger;
		struct mover_ent_t mover;
		struct corpse_ent_t corpse;
		struct missile_ent_t missile;
	};

	EntHandle missileTargetEnt;

	struct tagInfo_s* tagInfo;
	struct gentity_s *tagChildren;
	uint16_t attachModelNames[19];
	uint16_t attachTagNames[19];
	int useCount;
	struct gentity_s *nextFree;
}; /* Size: 0x274 */


extern gentity_s g_entities[];


