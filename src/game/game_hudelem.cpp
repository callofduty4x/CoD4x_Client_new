#include "game.h"
#include "game_hudelem.h"

#ifndef NDEBUG
static struct hudelem_s g_dummyHudCurrent;
#endif

void HudElem_UpdateClient(gclient_s *client, int clientNum, hudelem_update_t which)
{
  int archivalCount;
  int currentCount;
  struct game_hudelem_s *hud;
  unsigned int i;
  struct hudelem_s *elem;

  assert(clientNum >= 0 && clientNum < level.maxclients);

  if (clientNum < 0 || clientNum >= level.maxclients)
  {
    return;
  }
  assert(level.gentities[clientNum].r.inuse);

  assert(client != NULL);

  for(i = 0, hud = g_hudelems, archivalCount = 0, currentCount = 0;i < 1024; ++i, ++hud)
  {
    if ( hud->elem.type && !(hud->elem.flags & 0x2000) && (!hud->team || hud->team == client->sess.cs.team) && (hud->clientNum == 1023 || hud->clientNum == clientNum) )
    {
      if ( hud->archived )
      {
        if ( which & 1 )
        {
          elem = &client->ps.hud.archival[archivalCount];
          if ( archivalCount < 31 )
          {
            ++archivalCount;
            memcpy(elem, hud, sizeof(struct hudelem_s));
          }
        }
      }
      else if ( which & 2 )
      {
        elem = &client->ps.hud.current[currentCount];
        if ( currentCount < 31 )
        {
          ++currentCount;
          memcpy(elem, hud, sizeof(struct hudelem_s));
        }
      }
    }
  }
  if ( which & 1 )
  {
    while ( archivalCount < 31 && client->ps.hud.archival[archivalCount].type )
    {
      memset(&client->ps.hud.archival[archivalCount], 0, sizeof(client->ps.hud.archival[0]));
      assert(client->ps.hud.archival[archivalCount].type == HE_TYPE_FREE);
      ++archivalCount;
    }
    while ( archivalCount < 31 )
    {
      assert(!memcmp( &client->ps.hud.archival[archivalCount], &g_dummyHudCurrent, sizeof( g_dummyHudCurrent ) ));
      ++archivalCount;
    }
  }
  if ( which & 2 )
  {
    while ( currentCount < 31 && client->ps.hud.current[currentCount].type )
    {
      memset(&client->ps.hud.current[currentCount], 0, sizeof(client->ps.hud.current[0]));
      assert(client->ps.hud.current[currentCount].type == HE_TYPE_FREE);
      ++currentCount;
    }
    for (;currentCount < 31;++currentCount )
    {
      assert(!memcmp( &client->ps.hud.current[currentCount], &g_dummyHudCurrent, sizeof( g_dummyHudCurrent ) ));
      ++currentCount;
    }
  }
}

void HudElem_Free(struct game_hudelem_s *hud)
{
  assert(hud != NULL);
  assert(hud - g_hudelems < MAX_HUDELEMS);
  assert(hud->elem.type > HE_TYPE_FREE && hud->elem.type < HE_TYPE_COUNT);

  Scr_FreeHudElem(hud);
  hud->elem.type = HE_TYPE_FREE;
}

void HudElem_ClientDisconnect(gentity_s *ent)
{
  unsigned int i;

  for ( i = 0; i < MAX_HUDELEMS; ++i )
  {
    if ( g_hudelems[i].elem.type )
    {
      if ( g_hudelems[i].clientNum == ent->s.number )
      {
        HudElem_Free(&g_hudelems[i]);
      }
    }
  }
}

void HudElem_DestroyAll()
{
  unsigned int i;

  for ( i = 0; i < MAX_HUDELEMS; ++i )
  {
    if ( g_hudelems[i].elem.type )
    {
      HudElem_Free(&g_hudelems[i]);
    }
  }
  memset(g_hudelems, 0, sizeof(g_hudelems));
}
