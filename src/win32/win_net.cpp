// net_wins.c

#include <q_shared.h>
#include "win_local.h"

static WSADATA	winsockdata;
static qboolean	winsockInitialized = qfalse;
static qboolean usingSocks = qfalse;
static qboolean networkingEnabled = qfalse;

static cvar_t	*net_noudp;

static cvar_t	*net_socksEnabled;
static cvar_t	*net_socksServer;
static cvar_t	*net_socksPort;
static cvar_t	*net_socksUsername;
static cvar_t	*net_socksPassword;
static struct sockaddr	socksRelayAddr;

static SOCKET	ip_socket;
static SOCKET	socks_socket;

#define	MAX_IPS		16
static	int		numIP;
static	byte	localIP[MAX_IPS][4];

//=============================================================================


/*
====================
NET_ErrorString
====================
*/
const char *NET_ErrorString( void ) {
	int		code;

	code = WSAGetLastError();
	switch( code ) {
	case WSAEINTR: return "WSAEINTR";
	case WSAEBADF: return "WSAEBADF";
	case WSAEACCES: return "WSAEACCES";
	case WSAEDISCON: return "WSAEDISCON";
	case WSAEFAULT: return "WSAEFAULT";
	case WSAEINVAL: return "WSAEINVAL";
	case WSAEMFILE: return "WSAEMFILE";
	case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK";
	case WSAEINPROGRESS: return "WSAEINPROGRESS";
	case WSAEALREADY: return "WSAEALREADY";
	case WSAENOTSOCK: return "WSAENOTSOCK";
	case WSAEDESTADDRREQ: return "WSAEDESTADDRREQ";
	case WSAEMSGSIZE: return "WSAEMSGSIZE";
	case WSAEPROTOTYPE: return "WSAEPROTOTYPE";
	case WSAENOPROTOOPT: return "WSAENOPROTOOPT";
	case WSAEPROTONOSUPPORT: return "WSAEPROTONOSUPPORT";
	case WSAESOCKTNOSUPPORT: return "WSAESOCKTNOSUPPORT";
	case WSAEOPNOTSUPP: return "WSAEOPNOTSUPP";
	case WSAEPFNOSUPPORT: return "WSAEPFNOSUPPORT";
	case WSAEAFNOSUPPORT: return "WSAEAFNOSUPPORT";
	case WSAEADDRINUSE: return "WSAEADDRINUSE";
	case WSAEADDRNOTAVAIL: return "WSAEADDRNOTAVAIL";
	case WSAENETDOWN: return "WSAENETDOWN";
	case WSAENETUNREACH: return "WSAENETUNREACH";
	case WSAENETRESET: return "WSAENETRESET";
	case WSAECONNABORTED: return "WSWSAECONNABORTEDAEINTR";
	case WSAECONNRESET: return "WSAECONNRESET";
	case WSAENOBUFS: return "WSAENOBUFS";
	case WSAEISCONN: return "WSAEISCONN";
	case WSAENOTCONN: return "WSAENOTCONN";
	case WSAESHUTDOWN: return "WSAESHUTDOWN";
	case WSAETOOMANYREFS: return "WSAETOOMANYREFS";
	case WSAETIMEDOUT: return "WSAETIMEDOUT";
	case WSAECONNREFUSED: return "WSAECONNREFUSED";
	case WSAELOOP: return "WSAELOOP";
	case WSAENAMETOOLONG: return "WSAENAMETOOLONG";
	case WSAEHOSTDOWN: return "WSAEHOSTDOWN";
	case WSASYSNOTREADY: return "WSASYSNOTREADY";
	case WSAVERNOTSUPPORTED: return "WSAVERNOTSUPPORTED";
	case WSANOTINITIALISED: return "WSANOTINITIALISED";
	case WSAHOST_NOT_FOUND: return "WSAHOST_NOT_FOUND";
	case WSATRY_AGAIN: return "WSATRY_AGAIN";
	case WSANO_RECOVERY: return "WSANO_RECOVERY";
	case WSANO_DATA: return "WSANO_DATA";
	default: return "NO ERROR";
	}
}

void NetadrToSockadr( netadr_t *a, struct sockaddr *s ) {
	memset( s, 0, sizeof(*s) );

	if( a->type == NA_BROADCAST ) {
		((struct sockaddr_in *)s)->sin_family = AF_INET;
		((struct sockaddr_in *)s)->sin_port = a->port;
		((struct sockaddr_in *)s)->sin_addr.s_addr = INADDR_BROADCAST;
	}
	else if( a->type == NA_IP ) {
		((struct sockaddr_in *)s)->sin_family = AF_INET;
		((struct sockaddr_in *)s)->sin_addr.s_addr = *(int *)&a->ip;
		((struct sockaddr_in *)s)->sin_port = a->port;
	}

}


void SockadrToNetadr( struct sockaddr *s, netadr_t *a ) {
	if (s->sa_family == AF_INET) {
		a->type = NA_IP;
		*(int *)&a->ip = ((struct sockaddr_in *)s)->sin_addr.s_addr;
		a->port = ((struct sockaddr_in *)s)->sin_port;
	}
}


/*
=============
Sys_StringToAdr

idnewt
192.246.40.70
12121212.121212121212
=============
*/

qboolean Sys_StringToSockaddr( const char *s, struct sockaddr *sadr ) {
	struct hostent	*h;
	
	memset( sadr, 0, sizeof( *sadr ) );

    ((struct sockaddr_in *)sadr)->sin_family = AF_INET;
    ((struct sockaddr_in *)sadr)->sin_port = 0;

    if( s[0] >= '0' && s[0] <= '9' ) {
        *(int *)&((struct sockaddr_in *)sadr)->sin_addr = inet_addr(s);
    } else {
        if( ( h = gethostbyname( s ) ) == 0 ) {
            return (qboolean)0;
        }
        *(int *)&((struct sockaddr_in *)sadr)->sin_addr = *(int *)h->h_addr_list[0];
    }
		
	return qtrue;
}

#undef DO

/*
=============
Sys_StringToAdr

idnewt
192.246.40.70
=============
*/
qboolean Sys_StringToAdr( const char *s, netadr_t *a ) {
	struct sockaddr sadr;
	
	if ( !Sys_StringToSockaddr( s, &sadr ) ) {
		return qfalse;
	}
	
	SockadrToNetadr( &sadr, a );
	return qtrue;
}

//=============================================================================

/*
==================
Sys_GetPacket

Never called by the game logic, just the system event queing
==================
*/
int	recvfromCount;

qboolean Sys_GetPacket( netadr_t *net_from, msg_t *net_message ) {
	int 	ret;
	struct sockaddr from;
	int		fromlen;
	SOCKET		net_socket;

	int		err;

			net_socket = ip_socket;


    if( !net_socket ) {
        return qfalse;
    }

    fromlen = sizeof(from);
    recvfromCount++;		// performance check
    ret = recvfrom( net_socket, (char *)net_message->data, net_message->maxsize, 0, (struct sockaddr *)&from, &fromlen );
    if (ret == SOCKET_ERROR)
    {
        err = WSAGetLastError();

        if( err == WSAEWOULDBLOCK || err == WSAECONNRESET ) {
            return qfalse;
        }
        Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_GetPacket: %s\n", NET_ErrorString() );
        return qfalse;
    }

    if ( net_socket == ip_socket ) {
        memset( ((struct sockaddr_in *)&from)->sin_zero, 0, 8 );
    }

    if ( usingSocks && net_socket == ip_socket && memcmp( &from, &socksRelayAddr, fromlen ) == 0 ) {
        if ( ret < 10 || net_message->data[0] != 0 || net_message->data[1] != 0 || net_message->data[2] != 0 || net_message->data[3] != 1 ) {
            return qfalse;
        }
        net_from->type = NA_IP;
        net_from->ip[0] = net_message->data[4];
        net_from->ip[1] = net_message->data[5];
        net_from->ip[2] = net_message->data[6];
        net_from->ip[3] = net_message->data[7];
        net_from->port = *(short *)&net_message->data[8];
        net_message->readcount = 10;
    }
    else {
        SockadrToNetadr( &from, net_from );
        net_message->readcount = 0;
    }

    if( ret == net_message->maxsize ) {
        Com_Printf(CON_CHANNEL_SYSTEM, "Oversize packet from %s\n", NET_AdrToString (*net_from) );
        return qfalse;
    }

    net_message->cursize = ret;
    return qtrue;
}

//=============================================================================

static char socksBuf[4096];

/*
==================
Sys_SendPacket
==================
*/
void Sys_SendPacket( int length, const void *data, netadr_t to ) {
	int				ret;
	struct sockaddr	addr;
	SOCKET			net_socket;

	if( to.type == NA_BROADCAST ) {
		net_socket = ip_socket;
	}
	else if( to.type == NA_IP ) {
		net_socket = ip_socket;
	}
	else {
		Com_Error( ERR_FATAL, "Sys_SendPacket: bad address type" );
		return;
	}

	if( !net_socket ) {
		return;
	}

	NetadrToSockadr( &to, &addr );

	if( usingSocks && to.type == NA_IP ) {
		socksBuf[0] = 0;	// reserved
		socksBuf[1] = 0;
		socksBuf[2] = 0;	// fragment (not fragmented)
		socksBuf[3] = 1;	// address type: IPV4
		*(int *)&socksBuf[4] = ((struct sockaddr_in *)&addr)->sin_addr.s_addr;
		*(short *)&socksBuf[8] = ((struct sockaddr_in *)&addr)->sin_port;
		memcpy( &socksBuf[10], data, length );
		ret = sendto( net_socket, socksBuf, length+10, 0, &socksRelayAddr, sizeof(socksRelayAddr) );
	}
	else {
		ret = sendto( net_socket, (const char *)data, length, 0, &addr, sizeof(addr) );
	}
	if( ret == SOCKET_ERROR ) {
		int err = WSAGetLastError();

		// wouldblock is silent
		if( err == WSAEWOULDBLOCK ) {
			return;
		}

		// some PPP links do not allow broadcasts and return an error
		if( ( err == WSAEADDRNOTAVAIL ) && ( ( to.type == NA_BROADCAST ) ) ) {
			return;
		}

		Com_Printf(CON_CHANNEL_SYSTEM, "NET_SendPacket: %s\n", NET_ErrorString() );
	}
}


//=============================================================================


/*
==================
Sys_IsLANAddress

LAN clients will have their rate var ignored
==================
*/
qboolean Sys_IsLANAddress( netadr_t adr ) {
	int		i;

	if( adr.type == NA_LOOPBACK ) {
		return qtrue;
	}

	if( adr.type != NA_IP ) {
		return qfalse;
	}

	// choose which comparison to use based on the class of the address being tested
	// any local adresses of a different class than the address being tested will fail based on the first byte

	if( adr.ip[0] == 127 && adr.ip[1] == 0 && adr.ip[2] == 0 && adr.ip[3] == 1 ) {
		return qtrue;
	}

	// Class A
	if( (adr.ip[0] & 0x80) == 0x00 ) {
		for ( i = 0 ; i < numIP ; i++ ) {
			if( adr.ip[0] == localIP[i][0] ) {
				return qtrue;
			}
		}
		// the RFC1918 class a block will pass the above test
		return qfalse;
	}

	// Class B
	if( (adr.ip[0] & 0xc0) == 0x80 ) {
		for ( i = 0 ; i < numIP ; i++ ) {
			if( adr.ip[0] == localIP[i][0] && adr.ip[1] == localIP[i][1] ) {
				return qtrue;
			}
			// also check against the RFC1918 class b blocks
			if( adr.ip[0] == 172 && localIP[i][0] == 172 && (adr.ip[1] & 0xf0) == 16 && (localIP[i][1] & 0xf0) == 16 ) {
				return qtrue;
			}
		}
		return qfalse;
	}

	// Class C
	for ( i = 0 ; i < numIP ; i++ ) {
		if( adr.ip[0] == localIP[i][0] && adr.ip[1] == localIP[i][1] && adr.ip[2] == localIP[i][2] ) {
			return qtrue;
		}
		// also check against the RFC1918 class c blocks
		if( adr.ip[0] == 192 && localIP[i][0] == 192 && adr.ip[1] == 168 && localIP[i][1] == 168 ) {
			return qtrue;
		}
	}
	return qfalse;
}

qboolean Sys_IsLANAddress_IgnoreSubnet(netadr_t adr)
{
    return Sys_IsLANAddress( adr );
}


/*
==================
Sys_ShowIP
==================
*/
void Sys_ShowIP(void) {
	int i;

	for (i = 0; i < numIP; i++) {
		Com_Printf(CON_CHANNEL_SYSTEM, "IP: %i.%i.%i.%i\n", localIP[i][0], localIP[i][1], localIP[i][2], localIP[i][3] );
	}
}


//=============================================================================


/*
====================
NET_IPSocket
====================
*/
int NET_IPSocket( const char *net_interface, int port ) {
	SOCKET				newsocket;
	struct sockaddr_in	address;
	qboolean			_true = qtrue;
	int					i = 1;
	int					err;

	if( net_interface ) {
		Com_Printf(CON_CHANNEL_SYSTEM, "Opening IP socket: %s:%i\n", net_interface, port );
	}
	else {
		Com_Printf(CON_CHANNEL_SYSTEM, "Opening IP socket: localhost:%i\n", port );
	}

	if( ( newsocket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ) ) == INVALID_SOCKET ) {
		err = WSAGetLastError();
		if( err != WSAEAFNOSUPPORT ) {
			Com_PrintWarning(CON_CHANNEL_SYSTEM, "UDP_OpenSocket: socket: %s\n", NET_ErrorString() );
		}
		return 0;
	}

	// make it non-blocking
	if( ioctlsocket( newsocket, FIONBIO, (unsigned long *)&_true ) == SOCKET_ERROR ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "UDP_OpenSocket: ioctl FIONBIO: %s\n", NET_ErrorString() );
		return 0;
	}

	// make it broadcast capable
	if( setsockopt( newsocket, SOL_SOCKET, SO_BROADCAST, (char *)&i, sizeof(i) ) == SOCKET_ERROR ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "UDP_OpenSocket: setsockopt SO_BROADCAST: %s\n", NET_ErrorString() );
		return 0;
	}

	if( !net_interface || !net_interface[0] || !Q_stricmp(net_interface, "localhost") ) {
		address.sin_addr.s_addr = INADDR_ANY;
	}
	else {
		Sys_StringToSockaddr( net_interface, (struct sockaddr *)&address );
	}

	if( port == PORT_ANY ) {
		address.sin_port = 0;
	}
	else {
		address.sin_port = htons( (short)port );
	}

	address.sin_family = AF_INET;

	if( bind( newsocket, (const struct sockaddr *)&address, sizeof(address) ) == SOCKET_ERROR ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "UDP_OpenSocket: bind: %s\n", NET_ErrorString() );
		closesocket( newsocket );
		return 0;
	}

	return newsocket;
}


/*
====================
NET_OpenSocks
====================
*/
void NET_OpenSocks( int port ) {
	struct sockaddr_in	address;
	struct hostent		*h;
	int					len;
	qboolean			rfc1929;
	unsigned char		buf[64];

	usingSocks = qfalse;

	Com_Printf(CON_CHANNEL_SYSTEM, "Opening connection to SOCKS server.\n" );

	if ( ( socks_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP ) ) == INVALID_SOCKET ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: socket: %s\n", NET_ErrorString() );
		return;
	}

	h = gethostbyname( net_socksServer->current.string );
	if ( h == NULL ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: gethostbyname: %s\n", NET_ErrorString() );
		return;
	}
	if ( h->h_addrtype != AF_INET ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: gethostbyname: address type was not AF_INET\n" );
		return;
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = *(int *)h->h_addr_list[0];
	address.sin_port = htons( (short)net_socksPort->current.integer );

	if ( connect( socks_socket, (struct sockaddr *)&address, sizeof( address ) ) == SOCKET_ERROR ) {
		Com_Printf(CON_CHANNEL_SYSTEM, "NET_OpenSocks: connect: %s\n", NET_ErrorString() );
		return;
	}

	// send socks authentication handshake
	if ( *net_socksUsername->current.string || *net_socksPassword->current.string ) {
		rfc1929 = qtrue;
	}
	else {
		rfc1929 = qfalse;
	}

	buf[0] = 5;		// SOCKS version
	// method count
	if ( rfc1929 ) {
		buf[1] = 2;
		len = 4;
	}
	else {
		buf[1] = 1;
		len = 3;
	}
	buf[2] = 0;		// method #1 - method id #00: no authentication
	if ( rfc1929 ) {
		buf[2] = 2;		// method #2 - method id #02: username/password
	}
	if ( send( socks_socket, (const char *)buf, len, 0 ) == SOCKET_ERROR ) {
		Com_Printf(CON_CHANNEL_SYSTEM, "NET_OpenSocks: send: %s\n", NET_ErrorString() );
		return;
	}

	// get the response
	len = recv( socks_socket, (char *)buf, 64, 0 );
	if ( len == SOCKET_ERROR ) {
		Com_Printf(CON_CHANNEL_SYSTEM, "NET_OpenSocks: recv: %s\n", NET_ErrorString() );
		return;
	}
	if ( len != 2 || buf[0] != 5 ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: bad response\n" );
		return;
	}
	switch( buf[1] ) {
	case 0:	// no authentication
		break;
	case 2: // username/password authentication
		break;
	default:
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: request denied\n" );
		return;
	}

	// do username/password authentication if needed
	if ( buf[1] == 2 ) {
		int		ulen;
		int		plen;

		// build the request
		ulen = strlen( net_socksUsername->current.string );
		plen = strlen( net_socksPassword->current.string );

		buf[0] = 1;		// username/password authentication version
		buf[1] = ulen;
		if ( ulen ) {
			memcpy( &buf[2], net_socksUsername->current.string, ulen );
		}
		buf[2 + ulen] = plen;
		if ( plen ) {
			memcpy( &buf[3 + ulen], net_socksPassword->current.string, plen );
		}

		// send it
		if ( send( socks_socket, (const char *)buf, 3 + ulen + plen, 0 ) == SOCKET_ERROR ) {
			Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: send: %s\n", NET_ErrorString() );
			return;
		}

		// get the response
		len = recv( socks_socket, (char *)buf, 64, 0 );
		if ( len == SOCKET_ERROR ) {
			Com_PrintWarning(CON_CHANNEL_SYSTEM,  "NET_OpenSocks: recv: %s\n", NET_ErrorString() );
			return;
		}
		if ( len != 2 || buf[0] != 1 ) {
			Com_PrintWarning(CON_CHANNEL_SYSTEM,  "NET_OpenSocks: bad response\n" );
			return;
		}
		if ( buf[1] != 0 ) {
			Com_PrintWarning(CON_CHANNEL_SYSTEM,  "NET_OpenSocks: authentication failed\n" );
			return;
		}
	}

	// send the UDP associate request
	buf[0] = 5;		// SOCKS version
	buf[1] = 3;		// command: UDP associate
	buf[2] = 0;		// reserved
	buf[3] = 1;		// address type: IPV4
	*(int *)&buf[4] = INADDR_ANY;
	*(short *)&buf[8] = htons( (short)port );		// port
	if ( send( socks_socket, (const char *)buf, 10, 0 ) == SOCKET_ERROR ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: send: %s\n", NET_ErrorString() );
		return;
	}

	// get the response
	len = recv( socks_socket, (char *)buf, 64, 0 );
	if( len == SOCKET_ERROR ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: recv: %s\n", NET_ErrorString() );
		return;
	}
	if( len < 2 || buf[0] != 5 ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: bad response\n" );
		return;
	}
	// check completion code
	if( buf[1] != 0 ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: request denied: %i\n", buf[1] );
		return;
	}
	if( buf[3] != 1 ) {
		Com_PrintWarning(CON_CHANNEL_SYSTEM, "NET_OpenSocks: relay address is not IPV4: %i\n", buf[3] );
		return;
	}
	((struct sockaddr_in *)&socksRelayAddr)->sin_family = AF_INET;
	((struct sockaddr_in *)&socksRelayAddr)->sin_addr.s_addr = *(int *)&buf[4];
	((struct sockaddr_in *)&socksRelayAddr)->sin_port = *(short *)&buf[8];
	memset( ((struct sockaddr_in *)&socksRelayAddr)->sin_zero, 0, 8 );

	usingSocks = qtrue;
}


/*
=====================
NET_GetLocalAddress
=====================
*/
void NET_GetLocalAddress( void ) {
	char				hostname[256];
	struct hostent		*hostInfo;
	char				*p;
	int					ip;
	int					n;

	if( gethostname( hostname, 256 ) == SOCKET_ERROR ) {
		return;
	}

	hostInfo = gethostbyname( hostname );
	if( !hostInfo ) {
		return;
	}

	Com_Printf(CON_CHANNEL_SYSTEM, "Hostname: %s\n", hostInfo->h_name );
	n = 0;
	while( ( p = hostInfo->h_aliases[n++] ) != NULL ) {
		Com_Printf(CON_CHANNEL_SYSTEM, "Alias: %s\n", p );
	}

	if ( hostInfo->h_addrtype != AF_INET ) {
		return;
	}

	numIP = 0;
	while( ( p = hostInfo->h_addr_list[numIP] ) != NULL && numIP < MAX_IPS ) {
		ip = ntohl( *(int *)p );
		localIP[ numIP ][0] = p[0];
		localIP[ numIP ][1] = p[1];
		localIP[ numIP ][2] = p[2];
		localIP[ numIP ][3] = p[3];
		Com_Printf(CON_CHANNEL_SYSTEM, "IP: %i.%i.%i.%i\n", ( ip >> 24 ) & 0xff, ( ip >> 16 ) & 0xff, ( ip >> 8 ) & 0xff, ip & 0xff );
		numIP++;
	}
}

/*
====================
NET_OpenIP
====================
*/
void NET_OpenIP( void ) {
	cvar_t	*ip;
    cvar_t  *port;
	int		i;
    
    ip = Dvar_RegisterString("net_ip", "localhost", 0x20u, "Network IP Address");
    port = Dvar_RegisterInt("net_port", 3074, 0, 0xFFFF, 0x20u, "Network port");

	// automatically scan for a valid port, so multiple
	// dedicated servers can be started without requiring
	// a different net_port for each one
	for( i = 0 ; i < 10 ; i++ ) {
		ip_socket = NET_IPSocket( ip->current.string, port->current.integer + i );
		if ( ip_socket ) {
			Dvar_SetInt( port, port->current.integer + i );
			if ( net_socksEnabled->current.enabled ) {
				NET_OpenSocks( port->current.integer + i );
			}
			NET_GetLocalAddress();
			return;
		}
	}
	Com_PrintWarning(CON_CHANNEL_SYSTEM, "WARNING: Couldn't allocate IP port\n");
}


//===================================================================


/*
====================
NET_GetCvars
====================
*/
qboolean NET_GetCvars()
{
  qboolean modified; // [esp+0h] [ebp-4h]

  modified = qfalse;
  if ( net_noudp )
  {
    if ( net_noudp->modified )
    {
      modified = qtrue;
    }
  }
  net_noudp = Dvar_RegisterBool("net_noudp", qfalse, 0x21u, "Disable UDP");
  if ( net_socksEnabled )
  {
    if ( net_socksEnabled->modified )
    {
      modified = qtrue;
    }
  }
  net_socksEnabled = Dvar_RegisterBool("net_socksEnabled", qfalse, 0x21u, "Enable network sockets");
  if ( net_socksServer )
  {
    if ( net_socksServer->modified )
    {
      modified = qtrue;
    }
  }
  net_socksServer = Dvar_RegisterString("net_socksServer", "", 0x21u, "Network socket server");
  if ( net_socksPort )
  {
    if ( net_socksPort->modified )
    {
      modified = qtrue;
    }
  }
  net_socksPort = Dvar_RegisterInt("net_socksPort", 1080, 0, 0xFFFF, 0x21u, "Network socket port");
  if ( net_socksUsername )
  {
    if ( net_socksUsername->modified )
    {
      modified = qtrue;
    }
  }
  net_socksUsername = Dvar_RegisterString("net_socksUsername", "", 0x21u, "Network socket username");
  if ( net_socksPassword )
  {
    if ( net_socksPassword->modified )
    {
      modified = qtrue;
    }
  }
  net_socksPassword = Dvar_RegisterString("net_socksPassword", "", 0x21u, "Network socket password");
  return modified;
}

/*
====================
NET_Config
====================
*/
void NET_Config( qboolean enableNetworking ) {
	qboolean	modified;
	qboolean	stop;
	qboolean	start;

	// get any latched changes to cvars
	modified = NET_GetCvars();

	if( net_noudp->current.enabled ) {
		enableNetworking = qfalse;
	}

	// if enable state is the same and no cvars were modified, we have nothing to do
	if( enableNetworking == networkingEnabled && !modified ) {
		return;
	}

	if( enableNetworking == networkingEnabled ) {
		if( enableNetworking ) {
			stop = qtrue;
			start = qtrue;
		}
		else {
			stop = qfalse;
			start = qfalse;
		}
	}
	else {
		if( enableNetworking ) {
			stop = qfalse;
			start = qtrue;
		}
		else {
			stop = qtrue;
			start = qfalse;
		}
		networkingEnabled = enableNetworking;
	}

	if( stop ) {
		if ( ip_socket && ip_socket != INVALID_SOCKET ) {
			closesocket( ip_socket );
			ip_socket = 0;
		}

		if ( socks_socket && socks_socket != INVALID_SOCKET ) {
			closesocket( socks_socket );
			socks_socket = 0;
		}
	}

	if( start ) {
		if (! net_noudp->current.enabled ) {
			NET_OpenIP();
		}
	}
}


/*
====================
NET_Init
====================
*/
void NET_Init( void ) {
	int		r;

	r = WSAStartup( MAKEWORD( 1, 1 ), &winsockdata );
	if( r ) {
		Com_Printf(CON_CHANNEL_SYSTEM,  "WARNING: Winsock initialization failed, returned %d\n", r );
		return;
	}

	winsockInitialized = qtrue;
	Com_Printf(CON_CHANNEL_SYSTEM,  "Winsock Initialized\n" );

	// this is really just to get the cvars registered
	NET_GetCvars();

	//FIXME testing!
	NET_Config( qtrue );
}


/*
====================
NET_Shutdown
====================
*/
void NET_Shutdown( void ) {
	if ( !winsockInitialized ) {
		return;
	}
	NET_Config( qfalse );
	WSACleanup();
	winsockInitialized = qfalse;
}


/*
====================
NET_Sleep

sleeps msec or until net socket is ready
====================
*/
void NET_Sleep( int msec ) {
}


/*
====================
NET_Restart_f
====================
*/
void NET_Restart( void ) {
	NET_Config( networkingEnabled );
}