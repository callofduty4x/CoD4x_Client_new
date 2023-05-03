#include "game_shared.h"

#define MAX_HUDELEMS 1024

enum fonttype_t{
    HUDFONT_DEFAULT,
    HUDFONT_BIGFIXED,
    HUDFONT_SMALLFIXED,
    HUDFONT_OBJECTIVE
};

enum hudalign_t{
    HUDALIGN_TOP = 0,
    HUDALIGN_LEFT = 0,
    HUDALIGN_MIDDLE = 1,
    HUDALIGN_BOTTOM = 2,
    HUDALIGN_CENTER = 4,
    HUDALIGN_RIGHT = 8
};

enum hudscrnalign_t{
    HUDSCRNALIGN_TOP = 0,
    HUDSCRNALIGN_MIDDLE = 1,
    HUDSCRNALIGN_BOTTOM = 2,
    HUDSCRNALIGN_LEFT = 9,
    HUDSCRNALIGN_CENTER = 17,
    HUDSCRNALIGN_RIGHT = 25
};

enum huddisplayoptions_t{
    HUDDISPLAY_FOREGROUND = 1,
    HUDDISPLAY_HIDEINMENU = 4
};

enum hudelem_update_t
{
  HUDELEM_UPDATE_ARCHIVAL = 0x1,
  HUDELEM_UPDATE_CURRENT = 0x2,
  HUDELEM_UPDATE_ARCHIVAL_AND_CURRENT = 0x3
};


struct game_hudelem_s
{
  struct hudelem_s elem;
  int clientNum;
  int team;
  int archived;
};


extern struct game_hudelem_s g_hudelems[MAX_HUDELEMS];