#include <script/scr_shared.h>
#include <script/scr_shared.h>
#include <common/stringed_interface.h>
#include <game/game.h>
#include <cctype>



void Scr_LocalizationError(int iParm, const char *pszErrorMessage)
{
  Scr_ParamError(iParm, pszErrorMessage);
}

void Scr_ValidateLocalizedStringRef(int parmIndex, const char *token, int tokenLen)
{
  int charIter;

  assert( token != 0 );
  assert( tokenLen >= 0 );

  if ( tokenLen > 1 )
  {
    for ( charIter = 0; charIter < tokenLen; ++charIter )
    {
      if ( !isalnum(token[charIter]) && token[charIter] != '_' )
      {
        Scr_ParamError(parmIndex, va("Illegal localized string reference: %s must contain only alpha-numeric characters and underscores", token));
      }
    }
  }
}

void Scr_ConstructMessageString(int firstParmIndex, int lastParmIndex, const char *errorContext, char *string, unsigned int stringLimit)
{
  unsigned int charIndex;
  unsigned int tokenLen;
  int type;
  gentity_s *ent;
  int parmIndex;
  const char *token;
  unsigned int stringLen;

  stringLen = 0;
  for ( parmIndex = firstParmIndex; parmIndex <= lastParmIndex; ++parmIndex )
  {
    type = Scr_GetType(parmIndex);
    if ( type == VAR_ISTRING )
    {
      token = Scr_GetIString(parmIndex);
      tokenLen = strlen(token);
      Scr_ValidateLocalizedStringRef(parmIndex, token, tokenLen);
      if ( stringLen + tokenLen + 1 >= stringLimit )
      {
        Scr_ParamError(parmIndex, va("%s is too long. Max length is %i\n", errorContext, stringLimit));
      }
      if ( stringLen )
      {
        string[stringLen++] = 20;
      }
    }
    else if ( type != VAR_POINTER || Scr_GetPointerType(parmIndex) != VAR_ENTITY )
    {
      token = Scr_GetString(parmIndex);
      tokenLen = strlen(token);
      for ( charIndex = 0; charIndex < tokenLen; ++charIndex )
      {
        if ( token[charIndex] == 20 || token[charIndex] == 21 || token[charIndex] == 22 )
        {
          Scr_ParamError(parmIndex, va("bad escape character (%i) present in string", token[charIndex]));
        }
        if ( isalpha(token[charIndex]) )
        {
          if ( loc_warnings->current.enabled )
          {
            if ( loc_warningsAsErrors->current.enabled )
            {
              Scr_LocalizationError(parmIndex, va("non-localized %s strings are not allowed to have letters in them: \"%s\"", errorContext, token));
            }
            else
            {
              Com_PrintWarning(CON_CHANNEL_PLAYERWEAP,
                "WARNING: Non-localized %s string is not allowed to have letters in it. Must be changed over to a localized string: \"%s\"\n",
                errorContext, token);
            }
          }
          break;
        }
      }
      if ( stringLen + tokenLen + 1 >= stringLimit )
      {
        Scr_ParamError(parmIndex, va("%s is too long. Max length is %i\n", errorContext, stringLimit));
      }
      if ( tokenLen )
      {
        string[stringLen++] = 21;
      }
    }
    else
    {
      ent = Scr_GetEntity(parmIndex);
      if ( !ent->client )
      {
        Scr_ParamError(parmIndex, "Entity is not a player");
      }
      token = va("%s^7", CS_DisplayName(&ent->client->sess, 3));
      tokenLen = strlen(token);
      if ( stringLen + tokenLen + 1 >= stringLimit )
      {
        Scr_ParamError(parmIndex, va("%s is too long. Max length is %i\n", errorContext, stringLimit));
      }
      if ( tokenLen )
      {
        string[stringLen++] = 21;
      }
    }
    for ( charIndex = 0; charIndex < tokenLen; ++charIndex )
    {
      if ( token[charIndex] != 20 && token[charIndex] != 21 && token[charIndex] != 22 )
      {
        string[stringLen] = token[charIndex];
      }
      else
      {
        string[stringLen] = '.';
      }
      ++stringLen;
    }
  }
  string[stringLen] = 0;
}


void Scr_ToLower()
{
  char tempString[1024];
  const char *s;
  int i;

  s = Scr_GetString(0);
  for (i = 0; i < 1024; ++i )
  {
    tempString[i] = tolower(*s);
    if ( !tempString[i] )
    {
      Scr_AddString(tempString);
      return;
    }
    ++s;
  }
  Scr_Error("string too long");
}

