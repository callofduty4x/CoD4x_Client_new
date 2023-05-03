#include <game_mp/game_mp_shared.h>
#include <game/game_shared.h>
#include <script/scr_shared.h>
#include "server.h"
#include "server_shared.h"

gentity_s* SV_AddTestClient( )
{

    int i;
    unsigned short qport;
    client_t *cl = NULL;
    const char* denied;
    char name[16];
    char userinfo[MAX_INFO_STRING];
    netadr_t botnet;
    usercmd_s ucmd;
    static int botport;

	//Find a free serverslot for our bot
	for ( i = sv_privateClients->current.integer; i < sv_maxclients->current.integer; i++) {
		cl = &svs.clients[i];
		if (cl->header.state == CS_FREE) {
			break;
		}
	}
	if( i == sv_maxclients->current.integer )
		return NULL;		//No free slot

	Q_strncpyz(name, va("bot%d", i),sizeof(name));

//Connect our bot
    botport ++;
    qport = botport;
	*userinfo = 0;

	Info_SetValueForKey( userinfo, "cg_predictItems", "1");
	Info_SetValueForKey( userinfo, "color", "4");
	Info_SetValueForKey( userinfo, "head", "default");
	Info_SetValueForKey( userinfo, "model", "multi");
	Info_SetValueForKey( userinfo, "snaps", "20");
	Info_SetValueForKey( userinfo, "rate", "99999");
	Info_SetValueForKey( userinfo, "name", name);
	Info_SetValueForKey( userinfo, "protocol", va("%i", 6));
	Info_SetValueForKey( userinfo, "qport", va("%hi", qport));

	Com_Memset(&botnet,0,sizeof(botnet));
	botnet.type = NA_BOT;
	Info_SetValueForKey( userinfo, "ip", NET_AdrToString( botnet ) );

	//gotnewcl:
	Com_Memset(cl, 0x00, sizeof(client_t));
	// (build a new connection
	// accept the new client
	// this is the only place a client_t is ever initialized)
	Q_strncpyz(cl->cdkeyHash, "BOT-Client",33);	// save the pbguid

	// save the userinfo
	Q_strncpyz(cl->userinfo, userinfo, sizeof(cl->userinfo) );

	cl->voicePacketCount = 0;
	cl->sendVoice = 0;
    cl->gentity = SV_GentityNum(i);
    cl->clscriptid = Scr_AllocArray();

	denied = ClientConnect(i, cl->clscriptid);
	if ( denied ) {
		Com_Printf(CON_CHANNEL_SERVER,"Bot couldn't connect: %s\n", denied);
		SV_FreeClientScriptId(cl);
		return NULL;
	}
	Com_Printf(CON_CHANNEL_SERVER, "Going from CS_FREE to CS_CONNECTED for %s num %i\n", name, i);

	// save the addressgamestateMessageNum
	// init the netchan queue
	Netchan_Setup( NS_SERVER, &cl->header.netchan, botnet, qport,
			 cl->netchanOutgoingBuffer, sizeof(cl->netchanOutgoingBuffer),
			 cl->netchanIncomingBuffer, sizeof(cl->netchanIncomingBuffer));

/*	for(index = 0; index < MAX_RELIABLE_COMMANDS; index++ ){
		if(index < MAX_RELIABLE_COMMANDS / 2){
			cl->reliableCommands[index] = &cl->lowReliableCommands[index & (MAX_RELIABLE_COMMANDS - 1)];
		} else {
			cl->reliableCommands[index] = &svs.extclients[i].highReliableCommands[index & (MAX_RELIABLE_COMMANDS - 1)];
		}
	}
*/
	cl->header.state = CS_CONNECTED;
	cl->nextSnapshotTime = svs.time;
	cl->lastPacketTime = svs.time;
	cl->lastConnectTime = svs.time;

	SV_UserinfoChanged(cl);

	Q_strncpyz(cl->name, name, sizeof(cl->name));

	// when we receive the first packet from the client, we will
	// notice that it is from a different serverid and that the
	// gamestate message was not just sent, forcing a retransmit
	cl->gamestateMessageNum = -1; //newcl->gamestateMessageNum = -1;

	cl->bIsTestClient = qtrue;
    //Let enter our new bot the game

	Com_Memset(&ucmd, 0, sizeof(ucmd));

	SV_ClientEnterWorld(cl, &ucmd);

	return SV_GentityNum(i);
}


int SV_GetClientStat(int clientNum, signed int index)
{
  client_t *cl;
  int arrayentry;
  stats_t* stats;

  assert(svs.clients[clientNum].statPacketsReceived == ( 1 << MAX_STATPACKETS ) - 1);
  assert(svs.clients[clientNum].header.state >= CS_CONNECTED);

  cl = &svs.clients[clientNum];
  stats = reinterpret_cast<stats_t*>(cl->stats);
  if ( index < 2000 )
  {
	arrayentry = index;
    return stats->data.bytedata[arrayentry];

  }else if( index < 3498 ){
	arrayentry = index - 2000;
    return stats->data.longdata[arrayentry];

  }else{
    assertx(0, "Unhandled stat index %i", index);
	return 0;
  }
}

void SV_SetClientStat(int clientNum, signed int index, int value)
{
  client_t *cl;
  int arrayentry;
  stats_t* stats;

  
  assert(svs.clients[clientNum].statPacketsReceived == ( 1 << MAX_STATPACKETS ) - 1);
  assert(svs.clients[clientNum].header.state >= CS_CONNECTED);

  cl = &svs.clients[clientNum];
  stats = reinterpret_cast<stats_t*>(cl->stats);

  if ( index < 2000 )
  {
	arrayentry = index;
    if ( stats->data.bytedata[arrayentry] == value )
	{
      return;
	}
    stats->data.bytedata[arrayentry] = value;

  }else if( index < 3498 ){
	arrayentry = index - 2000;
    if ( stats->data.longdata[arrayentry] == value )
    {
		return;
	}
    stats->data.longdata[arrayentry] = value;

  }else{
    assertx(0, "Unhandled stat index %i", index);
	return;
  }
  SV_SendServerCommand(cl, SV_CMD_RELIABLE, "%c %i %i", 'N', index, value);

}



