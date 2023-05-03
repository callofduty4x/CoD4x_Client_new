#include <ctype.h>
#include "../q_shared.h"
#include "../common/com_sndalias.h"
#include "../effectscore/fx_shared.h"
#include "../common/com_debug.h"
#include "../database/db_shared.h"

struct EntSoundInfo_s
{
  vec3_t origin;
  struct snd_alias_list_t *sound;
};

struct EfxDefMapEntry_t
{
  char effectName[64];
  char mappedEffectName[64];
};

extern EfxDefMapEntry_t g_effectDefMap[32];
extern int g_effectDefMapEntries;

//REGPARM(3) const char* CG_ParseString(const char *indata, char *outstring, unsigned int outmaxlen);

const char* CG_ParseString(const char *indata, char *outstring, unsigned int maxoutlen)
{
  unsigned int i;
  char errbuf[128];
  const char* itrdata;


  if ( indata[0] != '"' )
  {
    Q_strncpyz(errbuf, indata, sizeof(errbuf));
    Com_PrintError(ERR_FATAL, "Expected a quoted string instead of '%s'\n", errbuf);
  }
 
  for ( i = 0, itrdata = &indata[1]; *itrdata != '"' && *itrdata; ++i, ++itrdata)
  {
    if ( i >= maxoutlen )
    {
      break;
    }
    outstring[i] = *itrdata;
  }
  if ( i >= maxoutlen)
  {
    Q_strncpyz(errbuf, indata, sizeof(errbuf));
    Com_PrintError(ERR_FATAL, "String was longer than expected '%s'\n", errbuf);
    return NULL;
  }
  outstring[i] = 0;
  return itrdata + 1;
}


const char* CG_ParseLineEnd(const char* data)
{
    for( ;*data && *data != '\n' && *data != '\r'; ++data);
    return data;
}

const char* CG_EfxParseWhiteSpace(const char *data)
{
    for(;isspace(*data);++data);

    return data;
}

bool CG_EfxStringCompareLenLimited(const char *cmp2, const char *cmp1)
{
  return Q_strncmp(cmp1, cmp2, strlen(cmp1)) == 0;
}

const char* CG_EfxParseToken(const char *data, const char *token)
{
  int len;

  len = strlen(token);
  if ( !Q_strncmp(token, data, len) )
  {
    return data + len;
  }
  Com_PrintError(ERR_FATAL, "Unexpected text '%s' when trying to find '%s' in map's effect file\n", data, token);
  return NULL;
}

const char * CG_EfxParseTokenLineFeedWhiteSpace(const char *data, const char *token)
{
    data = CG_EfxParseToken(data, token);
    if ( !data )
    {
        return NULL;
    }
    for( ;*data && *data != '\n' && *data != '\r'; ++data);

    return CG_EfxParseWhiteSpace(data);
}

const char* CG_ParseVec3Finish(const char *data, float *outvect)
{
  if ( sscanf(data, "%f, %f, %f", outvect, outvect + 1, outvect + 2) == 3 )
  {
    for( ;*data && *data != '\n' && *data != '\r'; ++data);

    return CG_EfxParseWhiteSpace(data);
  }
  Com_PrintError(ERR_FATAL, "Expected 3 floats instead of '%s'\n", data);
  return NULL;
}

const char *CG_ParseFloatFinish(const char *data, float *out)
{
  if ( sscanf(data, "%f", out) == 1 )
  {
    data = CG_ParseLineEnd(data);
    
    return CG_EfxParseWhiteSpace(data);
  }
  Com_PrintError(ERR_FATAL, "Expected a float instead of '%s'\n", data);
  return NULL;
}

const char* CG_ParseStringFinish(const char *data, char *outbuf, int maxoutbuflen)
{
  data = CG_ParseString(data, outbuf, maxoutbuflen);
  if ( !data )
  {
    return NULL;
  }
  data = CG_ParseLineEnd(data);

  return CG_EfxParseWhiteSpace(data);
}



bool CG_EfxGetMappedId(const char *name, char *mappedName, int maxmappednamelen)
{
    int i;

    for(i = 0; i < g_effectDefMapEntries; ++i)
    {
        if(!strcmp(g_effectDefMap[i].effectName, name))
        {
            Q_strncpyz(mappedName, g_effectDefMap[i].mappedEffectName, maxmappednamelen);
            return true;
        }
    }
    Com_PrintError(ERR_FATAL, "Couldn't find '%s' in _fx.gsc map.\n", name);
    return false;
}

extern int g_clientEntSoundCount;
extern EntSoundInfo_s g_clientEntSounds[128];

void CG_EfxLoadSoundAlias(const char *aliasname, float *origin)
{
  EntSoundInfo_s *entsnd;

  if ( g_clientEntSoundCount == 128 )
  {
    Com_PrintError(1, "Too many client ent sounds.  Increase MAX_CLIENT_ENT_SOUNDS.\n");
  }
  else
  {
    entsnd = &g_clientEntSounds[g_clientEntSoundCount];
    VectorCopy(origin, entsnd->origin);
    g_clientEntSounds[g_clientEntSoundCount].sound = Com_FindSoundAlias(aliasname);
    ++g_clientEntSoundCount;
  }
}

const char * CG_EfxParseAndLoadOneShotEffect(int localclientnum, const char *data)
{
  float delay;
  vec3_t origin;
  vec3_t angles;
  float axis[3][3];
  char mappedFxId[64];
  char soundaliasname[256];
  char fxid[256];

  data = CG_EfxParseToken(data, "ent = maps\\mp\\_utility::createOneshotEffect( ");
  if ( !data )
    return 0;
  data = CG_ParseLineEnd(data);

  data = CG_EfxParseWhiteSpace(data);
  if ( !data )
    return 0;
  data = CG_EfxParseToken(data, "ent.v[ \"origin\" ] = (");
  if ( !data )
    return 0;
  data = CG_ParseVec3Finish(data, origin);
  if ( !data )
    return 0;
  data = CG_EfxParseToken(data, "ent.v[ \"angles\" ] = (");
  if ( !data )
    return 0;
  data = CG_ParseVec3Finish(data, angles);
  if ( !data )
    return 0;
  data = CG_EfxParseToken(data, "ent.v[ \"fxid\" ] = ");
  if ( !data )
    return 0;
  data = CG_ParseStringFinish(data, fxid, sizeof(fxid));
  if ( !data )
    return 0;
  data = CG_EfxParseToken(data, "ent.v[ \"delay\" ] = ");
  if ( !data )
    return 0;
  data = CG_ParseFloatFinish(data, &delay);
  if ( !data )
    return 0;
  if ( CG_EfxStringCompareLenLimited(data, "ent.v[ \"soundalias\" ] = ") )
  {
    data = CG_EfxParseToken(data, "ent.v[ \"soundalias\" ] = ");
    if ( !data )
      return 0;
    data = CG_ParseStringFinish(data, soundaliasname, sizeof(soundaliasname));
    if ( !data )
      return 0;
    if ( !localclientnum )
      CG_EfxLoadSoundAlias(soundaliasname, origin);
  }
  if ( CG_EfxGetMappedId(fxid, mappedFxId, sizeof(mappedFxId)) )
  {
    FxEffectDef* fx = FX_Register(mappedFxId);
    AnglesToAxis(angles, axis);
    FX_SpawnOrientedEffect(localclientnum, fx, (signed int)(delay * 1000.0), origin, axis, 1023);

  }
  return data;
}




const char* CG_EfxParseAndLoadLoopSound(int localclientnum, const char *data)
{
  vec3_t origin;
  vec3_t tmpvec;
  char aliasname[256];

  data = CG_EfxParseToken(data, "ent = maps\\mp\\_createfx::createLoopSound();");
  if ( !data )
    return 0;
  data = CG_EfxParseWhiteSpace(data);
  if ( !data )
    return 0;
  data = CG_EfxParseToken(data, "ent.v[ \"origin\" ] = (");
  if ( !data )
    return 0;
  data = CG_ParseVec3Finish(data, origin);
  if ( !data )
    return 0;
  data = CG_EfxParseToken(data, "ent.v[ \"angles\" ] = (");
  if ( !data )
    return 0;
  data = CG_ParseVec3Finish(data, tmpvec);
  if ( !data )
    return 0;
  data = CG_EfxParseToken(data, "ent.v[ \"soundalias\" ] = ");
  if ( !data )
    return 0;
  data = CG_ParseStringFinish(data, aliasname, sizeof(aliasname));
  if ( !data )
    return 0;
  if ( !localclientnum )
    CG_EfxLoadSoundAlias(aliasname, origin);
  return data;
}






REGPARM(2) void CG_ParseClientEffects(int localclientnum, const char *data)
{

    if ( !(data = CG_EfxParseToken(data, "//_createfx generated. Do not touch!!")) )
    {
        return;
    }
    if ( !(data = CG_EfxParseWhiteSpace(data)) )
    {
        return;
    }
    if ( !( data = CG_EfxParseToken(data, "main()") ) )
    {
        return;
    }
    if ( !( data = CG_EfxParseWhiteSpace(data) ) )
    {
        return;
    }
    if ( !( data = CG_EfxParseToken(data, "{") ) )
    {
        return;
    }
    if ( !( data = CG_EfxParseWhiteSpace(data) ) )
    {
        return;
    }

    if ( !Q_strncmp("//", data, 2) )
    {
        data = CG_EfxParseTokenLineFeedWhiteSpace(data, "//");
    }
    if ( data )
    {
        while ( data[0] != '}' && data[0] )
        {
            if ( !Q_strncmp("ent = maps\\mp\\_createfx::createLoopSound();", data, 43) )
            {
                data = CG_EfxParseAndLoadLoopSound(localclientnum, data);
                if ( !data )
                {
                    return;
                }
            }else if ( !Q_strncmp("ent = maps\\mp\\_utility::createOneshotEffect( ", data, 45) ){
                if ( !(data = CG_EfxParseAndLoadOneShotEffect(localclientnum, data)) )
                {
                    return;
                }
            }else{
                Com_PrintError(CON_CHANNEL_ERROR, "Expected 'ent = maps\\mp\\_createfx::createLoopSound();' or 'ent = maps\\mp\\_utility::createOneshotEffect' instead of '%s' in map's effect file\n", data);
                return;
            }
        }
    }
    data = CG_EfxParseTokenLineFeedWhiteSpace(data, "}");
    if ( data && data[0] )
    {
        Com_PrintError(CON_CHANNEL_ERROR, "Unexpected data after parsing '%s' map's effect file\n", data);
    }

}

void CG_EfxRemapEffect(const char *name, char *remappedname)
{
    int i;

    for(i = 0; i < g_effectDefMapEntries; ++i)
    {
        if ( !strcmp(g_effectDefMap[i].effectName, name) )
        {
            if ( strcmp(g_effectDefMap[i].mappedEffectName, remappedname) != 0)
            {
                Com_PrintError(1, "Tried to remap '%s' to '%s' previously mapped to '%s'\n", g_effectDefMap[i].effectName, g_effectDefMap[i].mappedEffectName, remappedname);
            }
            return;
        }
    }

    if(i == ARRAY_COUNT(g_effectDefMap))
    {
        Com_PrintError(1, "Failed to added mapping from '%s' to '%s'.  Increase MAX_CLIENT_EFFECT_DEFS.\n", name, remappedname);
        return;        
    }
    Q_strncpyz(g_effectDefMap[g_effectDefMapEntries].effectName, name, sizeof(g_effectDefMap[0].effectName));
    Q_strncpyz(g_effectDefMap[g_effectDefMapEntries].mappedEffectName, remappedname, sizeof(g_effectDefMap[0].mappedEffectName));
    ++g_effectDefMapEntries;
}

const char* CG_ParseClientEffectMapping_single(const char* data)
{
    char effectName[64];
    char remappedName[64];


    if ( !data[0] )
    {
        return NULL;
    }

    data = CG_EfxParseWhiteSpace(data);


    if ( Q_strncmp("level._effect[", data, 14) != 0)
    {
        data = CG_ParseLineEnd(data);
        return data;
    }
    data = CG_EfxParseToken(data, "level._effect[");
    if(!data)
    {
        return NULL;
    }
    data = CG_EfxParseWhiteSpace(data);
    data = CG_ParseString(data, effectName, sizeof(effectName));
    if(!data)
    {
        return NULL;
    }
    data = CG_EfxParseWhiteSpace(data);
    data = CG_EfxParseToken(data, "]");
    if(!data)
    {
        return NULL;
    }
    data = CG_EfxParseWhiteSpace(data);
    data = CG_EfxParseToken(data, "=");
    if(!data)
    {
        return NULL;
    }
    data = CG_EfxParseWhiteSpace(data);
    data = CG_EfxParseToken(data, "loadfx");
    if ( !data )
    {
        return NULL;    
    }
    data = CG_EfxParseWhiteSpace(data);
    data = CG_EfxParseToken(data, "(");
    if ( !data )
    {
        return NULL;    
    }
    data = CG_EfxParseWhiteSpace(data);
    data = CG_ParseStringFinish(data, remappedName, sizeof(remappedName));
    if ( !data )
    {
        return NULL;    
    }
    CG_EfxRemapEffect(effectName, remappedName);

    return data;
}

void CG_ParseClientEffectMapping(const char *data)
{
    g_effectDefMapEntries = 0;
    if(!data[0])
    {
        return;
    }
    do
    {
        data = CG_ParseClientEffectMapping_single( data );

    }while( data != NULL );

}


void CG_LoadClientEffectMapping_FastFile(const char *effectfilename)
{
  XAssetHeader rawfile;

  rawfile.rawfile = DB_FindXAssetHeader(ASSET_TYPE_RAWFILE, effectfilename).rawfile;
  if ( rawfile.rawfile )
  {
    CG_ParseClientEffectMapping(rawfile.rawfile->buffer);
  }
  else
  {
    Com_PrintError(1, "file not found: %s\n", effectfilename);
  }
}