#include "server.h"

void SV_GetUserinfo(int index, char *buffer, int bufferSize)
{
    assert(static_cast<unsigned int>(index) < static_cast<unsigned int>(sv_maxclients->current.integer));

    if ( bufferSize < 1 )
    {
        Com_Error(ERR_FATAL, "SV_GetUserinfo: bufferSize == %i", bufferSize);
    }
    if ( index < 0 || index >= sv_maxclients->current.integer )
    {
        Com_Error(ERR_FATAL, "SV_GetUserinfo: bad index %i", index);
    }
    Q_strncpyz(buffer, svs.clients[index].userinfo, bufferSize);
}

void SV_SetUserinfo(int index, const char *val)
{
    if ( index < 0 || index >= sv_maxclients->current.integer )
    {
        Com_Error(ERR_DROP, "SV_SetUserinfo: bad index %i", index);
    }
    if ( !val )
    {
        val = "";
    }
    Q_strncpyz(svs.clients[index].userinfo, val, sizeof(svs.clients[index].userinfo));
    Q_strncpyz(svs.clients[index].name, Info_ValueForKey(val, "name"), sizeof(svs.clients[index].name));
}



