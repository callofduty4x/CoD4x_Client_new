#include <game/game.h>
#include <bgame/bg_shared.h>
#include <server/server_shared.h>

const char * CS_DisplayName(clientSession_t *cs, int type)
{
  /*
  const char* clan = SV_GetPlayerClan(cs->clientIndex);
  const char* name = SV_GetPlayerName(cs->clientIndex);

  if(name && clan)
  {
    return Com_DisplayName(name, clan, type);
  }
  return "";
*/
    return cs->newnetname;
}


/*
===========
ClientCheckName
============
*/
static void ClientCleanName( const char *in, char *out, int outSize ) {
	int len, colorlessLen;
	char ch;
	char *p;
	int spaces;

	//save room for trailing null byte
	outSize--;

	len = 0;
	colorlessLen = 0;
	p = out;
	*p = 0;
	spaces = 0;

	while ( 1 ) {
		ch = *in++;
		if ( !ch ) {
			break;
		}

		// don't allow leading spaces
		if ( !*p && ch == ' ' ) {
			continue;
		}

		// check colors
		if ( ch == Q_COLOR_ESCAPE ) {
			// solo trailing carat is not a color prefix
			if ( !*in ) {
				break;
			}

			// don't allow black in a name, period
			if ( ColorIndex( *in ) == 0 ) {
				in++;
				continue;
			}

			// make sure room in dest for both chars
			if ( len > outSize - 2 ) {
				break;
			}

			*out++ = ch;
			*out++ = *in++;
			len += 2;
			continue;
		}

		// don't allow too many consecutive spaces
		if ( ch == ' ' ) {
			spaces++;
			if ( spaces > 3 ) {
				continue;
			}
		} else {
			spaces = 0;
		}

		if ( len > outSize - 1 ) {
			break;
		}

		*out++ = ch;
		colorlessLen++;
		len++;
	}
	*out = 0;

	// don't allow empty names
	if ( *p == 0 || colorlessLen == 0 ) {
		Q_strncpyz( p, "UnnamedPlayer", outSize );
	}
}

void ClientUserinfoChanged(int clientNum)
{
  gclient_s *client;
  const char *s;
  clientInfo_t *ci;
  
  char userinfo[1024];

  client = g_entities[clientNum].client;
  assert((unsigned int)clientNum < MAX_CLIENTS);

  SV_GetUserinfo(clientNum, userinfo, sizeof(userinfo));
  if ( !Info_Validate(userinfo) )
  {
    strcpy(userinfo, "\\name\\badinfo");
  }
  client->sess.localClient = SV_IsLocalClient(clientNum);
  
  s = Info_ValueForKey(userinfo, "cg_predictItems");
  if ( atoi(s) )
    client->sess.predictItemPickup = qtrue;
  else
    client->sess.predictItemPickup = qfalse;
  
  if ( client->sess.connected == CON_CONNECTED && level.manualNameChange )
  {
    s = Info_ValueForKey(userinfo, "name");
    ClientCleanName(s, client->sess.newnetname, sizeof(client->sess.newnetname));
  }
  else
  {
    s = Info_ValueForKey(userinfo, "name");
    ClientCleanName(s, client->sess.cs.name, sizeof(client->sess.cs.name));
    Q_strncpyz(client->sess.newnetname, client->sess.cs.name, sizeof(client->sess.newnetname));
    /*
    s = Info_ValueForKey(userinfo, "clanAbbrev");
    if ( *s )
      ClientCleanName(s, b, 5);
    else
      b[0] = 0;
    Q_strncpyz(client->sess.cs.clanAbbrev, b, 8);
    */
  }

  ci = &level_bgs.clientinfo[clientNum];
  
  //assert(ci->infoValid);
  
  ci->clientNum = clientNum;
  Q_strncpyz(level_bgs.clientinfo[clientNum].name, client->sess.cs.name, sizeof(level_bgs.clientinfo[clientNum].name));
  ci->team = client->sess.cs.team;
}