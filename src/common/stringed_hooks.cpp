#include <ctype.h>
#include "../q_shared.h"
#include "stringed_public.h"
#include "stringed_interface.h"


#define MAX_TOKENBUF_SZ 1024

int SEH_GetLocalizedTokenReference(char *token, const char *reference, const char *messageType, msgLocErrType_t errType)
{
    const char *translation;
    char tmpbuf[1024];

    translation = SEH_StringEd_GetString(reference);
    if ( !translation )
    {
        if ( loc_warnings && loc_warnings->current.enabled )
        {
            if ( loc_warningsAsErrors && loc_warningsAsErrors->current.enabled && errType != 1 )
            {
                Com_Error(ERR_LOCALIZATION, "Could not translate part of %s: \"%s\"", messageType, reference);
            }
            else
            {
                Com_PrintWarning(CON_CHANNEL_SYSTEM, "WARNING: Could not translate part of %s: \"%s\"\n", messageType, reference);
            }
            Com_sprintf(tmpbuf, sizeof(tmpbuf), "^1UNLOCALIZED(^7%s^1)^7", reference);
        }
        else
        {
            Com_sprintf(tmpbuf, sizeof(tmpbuf), "%s", reference);
        }
        if ( errType == 1 )
        {
            return 0;
        }
        translation = tmpbuf;
    }
    Q_strncpyz(token, translation, MAX_TOKENBUF_SZ);
    return 1;
}


#define MAX_TEMP_STRINGS 10

const char* SEH_LocalizeTextMessage(const char *pszInputBuffer, const char *pszMessageType, msgLocErrType_t errType)
{
    char szInsertBuf[MAX_TOKENBUF_SZ];
    char szTokenBuf[MAX_TOKENBUF_SZ];
    int bLocOn;
    int iTokenLen;
    int iInsertLevel;
    int iLen;
    int bInsertEnabled;
    int insertIndex;
    const char *pszIn;
    int bLocSkipped;
    const char *pszTokenStart;
    int i;
    char *pszString;
    int digit;
    
    static int iCurrString;
    static char szStrings[MAX_TEMP_STRINGS][MAX_TOKENBUF_SZ];

    iCurrString = (iCurrString + 1) % MAX_TEMP_STRINGS;
    memset(szStrings[iCurrString], 0, sizeof(szStrings[0]));
    pszString = szStrings[iCurrString];
    iLen = 0;
    bLocOn = 1;
    bInsertEnabled = 1;
    iInsertLevel = 0;
    insertIndex = 1;
    bLocSkipped = 0;
    pszTokenStart = pszInputBuffer;
    pszIn = pszInputBuffer;
    while ( *pszTokenStart )
    {
        if ( *pszIn && *pszIn != 20 && *pszIn != 21 && *pszIn != 22 )
        {
            ++pszIn;
        }
        else
        {
            if ( pszIn > pszTokenStart )
            {
                iTokenLen = pszIn - pszTokenStart;
                Q_strncpyz(szTokenBuf, pszTokenStart, pszIn - pszTokenStart + 1);
                if ( bLocOn )
                {
                    if ( !SEH_GetLocalizedTokenReference(szTokenBuf, szTokenBuf, pszMessageType, errType) )
                    {
                        return 0;
                    }
                    iTokenLen = &szTokenBuf[strlen(szTokenBuf) + 1] - &szTokenBuf[1];
                }
                if ( iTokenLen + iLen >= (signed)sizeof(szTokenBuf) )
                {
                    if ( loc_warnings && loc_warnings->current.enabled)
                    {
                        if ( loc_warningsAsErrors && loc_warningsAsErrors->current.enabled)
                        {
                            if ( errType != 1 )
                            {
                                Com_Error(ERR_DROP, "%s too long when translated: \"%s\"", pszMessageType, pszInputBuffer);
                            }
                        }
                    }
                    Com_Printf(CON_CHANNEL_SYSTEM, "%s too long when translated: \"%s\"\n", pszMessageType, pszInputBuffer);
                }
                for ( i = 0; i < iTokenLen - 2; ++i )
                {
                    if ( !strncmp(&szTokenBuf[i], "&&", 2u) )
                    {
                        if ( isdigit(szTokenBuf[i + 2]) )
                        {
                            if ( bInsertEnabled )
                            {
                                ++iInsertLevel;
                            }
                            else
                            {
                                szTokenBuf[i] = 22;
                                bLocSkipped = 1;
                            }
                        }
                    }
                }
                if ( iInsertLevel <= 0 || iLen <= 0 )
                {
                    strcpy(&pszString[iLen], szTokenBuf);
                }
                else
                {
                    for ( i = 0; i < iLen - 2; ++i )
                    {
                        if ( !strncmp(&pszString[i], "&&", 2u) )
                        {
                            if ( isdigit(pszString[i + 2]) )
                            {
                                digit = pszString[i + 2] - '0';
                                if ( !digit )
                                {
                                    Com_Printf(CON_CHANNEL_SYSTEM, "%s cannot have &&0 as conversion format: \"%s\"\n", pszMessageType, pszInputBuffer);
                                }
                                if ( digit == insertIndex )
                                {
                                    strcpy(szInsertBuf, &pszString[i + 3]);
                                    pszString[i] = 0;
                                    ++insertIndex;
                                    break;
                                }
                            }
                        }
                    }
                    strcpy(&pszString[i], szTokenBuf);
                    strcpy(&pszString[iTokenLen + i], szInsertBuf);
                    iLen -= 3;
                    --iInsertLevel;
                }
                iLen += iTokenLen;
            }
            bInsertEnabled = 1;
            if ( *pszIn == 20 )
            {
                bLocOn = 1;
                ++pszIn;
            }
            else if ( *pszIn == 21 )
            {
                bLocOn = 0;
                ++pszIn;
            }
            if ( *pszIn == 22 )
            {
                bInsertEnabled = 0;
                ++pszIn;
            }
            pszTokenStart = pszIn;
        }
    }
    if ( bLocSkipped )
    {
        for ( i = 0; i < iLen; ++i )
        {
            if ( pszString[i] == 22 )
            {
                pszString[i] = '%';
            }
        }
    }
    return pszString;
}

