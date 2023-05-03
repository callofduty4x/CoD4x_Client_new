#include <ctype.h>
#include "../q_shared.h"
#include "client_shared.h"
#include "client_local.h"
#include "../common/sys_shared.h"
#include "../common/qcommon.h"
#include "keys.h"



extern bool sPasting;
extern const char *s_completionString;
extern int s_matchCount;
extern int s_prefixMatchCount;
extern char s_shortestMatch[1024];
extern bool s_hasExactMatch;

bool Field_Paste(int localClientNum, const ScreenPlacement *scrPlace, field_t *edit)
{
    signed int len;
    int i;
    char *cbd;

    cbd = Sys_GetClipboardData();
    if ( !cbd )
    {
        return 0;
    }
    sPasting = true;
    len = strlen(cbd);
    for ( i = 0; i < len; ++i )
    {
        Field_CharEvent(localClientNum, scrPlace, edit, cbd[i]);
    }
    sPasting = false;
    Sys_FreeClipboardData(cbd);
    return 1;
}

int Key_GetOverstrikeMode(int localClientNum)
{
    return playerKeys[localClientNum].overstrikeMode;
}

void Key_SetOverstrikeMode(int localClientNum, int state)
{
    playerKeys[localClientNum].overstrikeMode = state;
}

REGPARM(3) bool Field_KeyDownEvent(int localClientNum, const ScreenPlacement *scrPlace, field_t *edit, int key)
{
    signed int len;
    int isCtrlDown;
    bool isModified;

    isCtrlDown = playerKeys[localClientNum].keys[159].down;
    isModified = 0;
    len = strlen(edit->buffer);
    if ( (key == 161 || key == 192) && playerKeys[localClientNum].keys[160].down )
    {
        isModified = Field_Paste(localClientNum, scrPlace, edit);
    }
    else
    {
        switch ( key )
        {
            case 162:
                if ( edit->cursor < len )
                {
                    memmove(&edit->buffer[edit->cursor], &edit->buffer[edit->cursor + 1], len - edit->cursor);
                }
                break;
            case 157:
                if ( edit->cursor < len )
                {
                    ++edit->cursor;
                }
                if ( isCtrlDown )
                {
                    while ( edit->cursor < len && isalnum(edit->buffer[edit->cursor]) )
                    {
                        ++edit->cursor;
                    }
                    while ( edit->cursor < len && !isalnum(edit->buffer[edit->cursor]) )
                    {
                        ++edit->cursor;
                    }
                }
                break;
            case 156:
                if ( edit->cursor > 0 )
                {
                    --edit->cursor;
                }
                if ( isCtrlDown )
                {
                    while ( edit->cursor > 0 && isalnum(*((char *)&edit->fixedSize + edit->cursor + 3)) )
                    {
                        --edit->cursor;
                    }
                }
                if ( edit->cursor < edit->scroll )
                {
                    edit->scroll = edit->cursor;
                }
                break;
            default:
                if ( key == 165 || (tolower(key) == 'a' && isCtrlDown) )
                {
                    edit->cursor = 0;
                }
                else if ( key == 166 || (tolower(key) == 'e' && isCtrlDown) )
                {
                    edit->cursor = len;
                }
                else if ( key == 161 )
                {
                    Key_SetOverstrikeMode(localClientNum, Key_GetOverstrikeMode(localClientNum) == 0);
                }
                break;
        }
    }
    if ( cls.uiStarted )
    {
        Field_AdjustScroll(scrPlace, edit);
    }
    return isModified;
}

void UpdateMatches(bool searchCmds, int *matchLenAfterCmds, int *matchLenAfterDvars)
{
    s_matchCount = 0;
    s_prefixMatchCount = 0;
    s_shortestMatch[0] = 0;
    if ( searchCmds )
    {
        Cmd_ForEachConsoleAccessName(FindMatches);
        *matchLenAfterCmds = strlen(s_shortestMatch);
    }
    else
    {
        *matchLenAfterCmds = 0;
    }
    Dvar_ForEachConsoleAccessName(FindMatches);
    *matchLenAfterDvars = strlen(s_shortestMatch);
}

void keyConcatArgs()
{
  int i;
  const char *arg;

  for ( i = 1; i < Cmd_Argc(); ++i )
  {
    Q_strncat(g_consoleField.buffer, sizeof(g_consoleField.buffer), " ");
    for ( arg = Cmd_Argv(i); *arg; ++arg )
    {
      if ( *arg == ' ' )
      {
        Q_strncat(g_consoleField.buffer, sizeof(g_consoleField.buffer), "\"");
        break;
      }
    }
    Q_strncat(g_consoleField.buffer, sizeof(g_consoleField.buffer), Cmd_Argv(i));
    if ( *arg == ' ' )
    {
      Q_strncat(g_consoleField.buffer, sizeof(g_consoleField.buffer), "\"");
    }
  }
}


void ConcatRemaining(const char *src, const char *start)
{
  const char *str;
  int startlen = strlen(start);

  str = strstr((char *)src, (char *)start);
  if ( str )
  {
    Q_strncat(g_consoleField.buffer, sizeof(g_consoleField.buffer), &str[startlen]);
  }
  else
  {
    keyConcatArgs();
  }
}


void ReplaceConsoleInputArgument(int replaceCount, const char *replacement)
{
  signed int cmdLineLen;

  assert( replacement );

  if ( replacement[0] )
  {
    for ( cmdLineLen = strlen(g_consoleField.buffer); cmdLineLen && isspace(g_consoleField.buffer[cmdLineLen -1]); --cmdLineLen );
    
    assertx(replaceCount < cmdLineLen, "%s: %i, %i", g_consoleField.buffer, replaceCount, cmdLineLen);

    Q_strncpyz(&g_consoleField.buffer[cmdLineLen - replaceCount], replacement, sizeof(g_consoleField.buffer) - (cmdLineLen - replaceCount));
  }
}

void CompleteCmdArgument()
{
  const char *cmdArgPrefix;
  char arg[256];
  const char *cmdName;
  const char **files;
  int fileCount;

  cmdName = Con_TokenizeInput();
  cmdArgPrefix = Cmd_Argv(1);
  if ( *cmdArgPrefix )
  {
    files = Cmd_GetAutoCompleteFileList(cmdName, &fileCount, 11);
    Cmd_EndTokenizedString();
    if ( fileCount )
    {
      Con_AutoCompleteFromList(files, fileCount, cmdArgPrefix, arg, sizeof(arg));
      FS_FreeFileList(files);
      Com_StripExtension(arg, arg);
      ReplaceConsoleInputArgument(strlen(cmdArgPrefix), arg);
    }
  }
  else
  {
    Cmd_EndTokenizedString();
  }
}

void CompleteDvarArgument()
{
  const char *dvarName;
  dvar_s *dvar;
  const char *dvarValuePrefix;
  char dvarValue[256];

  dvarName = Con_TokenizeInput();
  dvar = Dvar_FindVar(dvarName);

  assert(dvar);

  if ( dvar->type == CVAR_ENUM )
  {
    dvarValuePrefix = Cmd_Argv(1);
    if ( dvarValuePrefix[0] )
    {
      Con_AutoCompleteFromList(dvar->enumStrings, dvar->enumCount, dvarValuePrefix, dvarValue, sizeof(dvarValue));
      ReplaceConsoleInputArgument(strlen(dvarValuePrefix), dvarValue);
    }
    Cmd_EndTokenizedString();
  }
  else
  {
    Cmd_EndTokenizedString();
  }
}



void CompleteCommand()
{
    int matchLenAfterCmds;
    field_t savedField;
    bool isDvarCommand;
    int offset;
    const char *originalCommand;
    int matchLenAfterDvars;
    bool useExactMatch;
    field_t *edit;

    offset = g_consoleField.buffer[0] == '/' || g_consoleField.buffer[0] == '\\';
    if ( !strnicmp(&g_consoleField.buffer[offset], "pb_", 3u) )
    {
/*        
        char pbbuf[265];

        strncpy(pbbuf, &g_consoleField.buffer[offset], 0xFFu);
        pbbuf[255] = 0;
        if ( !strnicmp(pbbuf, "pb_sv_", 6u) )
        {
            PbServerCompleteCommand(pbbuf, 255);
        }
        else
        {
            PbClientCompleteCommand(pbbuf, 255);
        }
        Com_sprintf(g_consoleField.buffer, 256, "\\%s", pbbuf);
        g_consoleField.cursor = strlen(g_consoleField.buffer);
        Field_AdjustScroll(&scrPlaceFull, &g_consoleField);
*/
    }
    else
    {
        s_completionString = Con_TokenizeInput();
        s_matchCount = 0;
        s_prefixMatchCount = 0;
        s_shortestMatch[0] = 0;
        if ( s_completionString[0] )
        {
            originalCommand = s_completionString;
            isDvarCommand = Cmd_Argc() > 1 && Con_IsDvarCommand(s_completionString);
            if ( isDvarCommand )
            {
                s_completionString = Cmd_Argv(1);
            }
            matchLenAfterCmds = 0;
            matchLenAfterDvars = 0;
            if ( con_matchPrefixOnly->current.enabled )
            {
                con_ignoreMatchPrefixOnly = 1;
                UpdateMatches(isDvarCommand == 0, &matchLenAfterCmds, &matchLenAfterDvars);
                if ( s_matchCount > con_inputMaxMatchesShown )
                {
                    con_ignoreMatchPrefixOnly = 0;
                    UpdateMatches(isDvarCommand == 0, &matchLenAfterCmds, &matchLenAfterDvars);
                    if ( !s_matchCount )
                    {
                        con_ignoreMatchPrefixOnly = 1;
                        UpdateMatches(isDvarCommand == 0, &matchLenAfterCmds, &matchLenAfterDvars);
                    }
                }
            }
            else
            {
                con_ignoreMatchPrefixOnly = 0;
                UpdateMatches(isDvarCommand == 0, &matchLenAfterCmds, &matchLenAfterDvars);
            }
            if ( s_matchCount )
            {
                edit = &g_consoleField;
                memcpy(&savedField, &g_consoleField, sizeof(savedField));

                useExactMatch = isDvarCommand || s_matchCount == 1 || (s_hasExactMatch && Con_AnySpaceAfterCommand());

                if ( isDvarCommand )
                {
                    Com_sprintf(edit->buffer, sizeof(edit->buffer), "\\%s %s", originalCommand, s_shortestMatch);
                }
                else
                {
                    Com_sprintf(edit->buffer, sizeof(edit->buffer), "\\%s", s_shortestMatch);
                }
                edit->cursor = strlen(edit->buffer);
                ConcatRemaining(savedField.buffer, s_completionString);
                if ( useExactMatch )
                {
                    if ( !isDvarCommand )
                    {
                        if ( Cmd_Argc() == 1 )
                        {
                            Q_strncat(g_consoleField.buffer, sizeof(g_consoleField.buffer), " ");
                        }
                        else if ( Cmd_Argc() == 2 )
                        {
                            if ( matchLenAfterCmds == matchLenAfterDvars )
                            {
                                CompleteCmdArgument();
                            }
                            else
                            {
                                CompleteDvarArgument();
                            }
                        }
                    }
                    edit->cursor = strlen(edit->buffer);
                }
                else if ( Con_HasTooManyMatchesToShow() )
                {
                    Com_Printf(0, "]%s\n", g_consoleField.buffer);
                    Con_ForEach(0, PrintMatches, PrintMatches);
                }
                Cmd_EndTokenizedString();
                Field_AdjustScroll(&scrPlaceFull, &g_consoleField);
            }
            else
            {
                Cmd_EndTokenizedString();
            }
        }
        else
        {
            Cmd_EndTokenizedString();
        }
    }
}


void Console_Key(int localClientNum, int key)
{
    char bhistoryaccess;
    bool bhistoryaccess_1;
    int isShiftDown;
    int isCtrlDown;
    int shouldCompleteCmd;
    int isAltDown;
    static bool s_shouldCompleteCmd;
    static int nextHistoryLine;
    static int historyLine;

    shouldCompleteCmd = s_shouldCompleteCmd;
    s_shouldCompleteCmd = true;
    isShiftDown = playerKeys[localClientNum].keys[160].down;
    isCtrlDown = playerKeys[localClientNum].keys[159].down;
    isAltDown = playerKeys[localClientNum].keys[158].down;

    if ( key == 'l' && isCtrlDown )
    {
        Cbuf_AddText(localClientNum, "clear\n");
        return;
    }
    if ( key != '\r' && key != 191 )
    {
        if ( key == '\t' )
        {
            if ( shouldCompleteCmd )
            {
                CompleteCommand();
            }
            else
            {
                Con_CycleAutoComplete(2 * (isShiftDown == 0) - 1);
            }
            s_shouldCompleteCmd = false;
        }
        else
        {
            if ( key == 154 && isCtrlDown )
            {
                Con_CycleAutoComplete(-1);
                return;
            }
            if ( key == 155 && isCtrlDown )
            {
                Con_CycleAutoComplete(1);
                return;
            }
            if ( key == 206 && isShiftDown )
            {
                bhistoryaccess_1 = 1;
            }
            else if ( key == 183 )
            {
                bhistoryaccess_1 = 1;
            }
            else
            {
                bhistoryaccess_1 = key == 154 || (tolower(key) == 'p' && isCtrlDown);
            }
            if ( bhistoryaccess_1 )
            {
                if ( nextHistoryLine - historyLine < MAX_CON_HISTORY_COUNT && historyLine > 0 )
                {
                    --historyLine;
                }
                memcpy(&g_consoleField, &historyEditLines[historyLine % MAX_CON_HISTORY_COUNT], sizeof(g_consoleField));
                Field_AdjustScroll(&scrPlaceFull, &g_consoleField);
                Con_AllowAutoCompleteCycling(0);
            }
            else
            {
                if ( key == 205 && isShiftDown )
                {
                    bhistoryaccess = 1;
                }
                else if ( key == 189 )
                {
                    bhistoryaccess = 1;
                }
                else if(key == 155 || (tolower(key) == 'n' && isCtrlDown))
                {
                    bhistoryaccess = true;
                }
                else
                {
                    bhistoryaccess = false;
                }
                if ( bhistoryaccess )
                {
                    if ( !Con_CycleAutoComplete(1) && historyLine != nextHistoryLine )
                    {
                        memcpy(&g_consoleField, &historyEditLines[++historyLine % MAX_CON_HISTORY_COUNT], sizeof(g_consoleField));
                        Field_AdjustScroll(&scrPlaceFull, &g_consoleField);
                    }
                }
                else
                {
                    switch ( key )
                    {
                        case 164:
                            Con_PageUp();
                            return;
                        case 163:
                            Con_PageDown();
                            return;
                        case 206:
                            Con_PageUp();
                            if ( isCtrlDown )
                            {
                                Con_PageUp();
                                Con_PageUp();
                            }
                            break;
                        case 205:
                            Con_PageDown();
                            if ( isCtrlDown )
                            {
                                Con_PageDown();
                                Con_PageDown();
                            }
                            break;
                        default:
                            if ( key == 165 && isCtrlDown )
                            {
                                Con_Top();
                                return;
                            }
                            if ( key == 166 && isCtrlDown )
                            {
                                Con_Bottom();
                                return;
                            }
                            if ( key != 162 && key != 27 )
                            {
                                if ( key == 157 || key == 187 || key == 156 || key == 185 || (key != 127 && !isCtrlDown && !isAltDown && !isShiftDown ))
                                {
                                    Con_CommitToAutoComplete();
                                }
                            }
                            else if ( Con_CancelAutoComplete() )
                            {
                                return;
                            }
                            if ( Field_KeyDownEvent(localClientNum, &scrPlaceFull, &g_consoleField, key) )
                            {
                                Con_AllowAutoCompleteCycling(1);
                            }
                            break;
                    }
                }
            }
        }
    }
    else
    {
        if ( Con_CommitToAutoComplete() )
        {
            return;
        }
        Com_Printf(0, "]%s\n", g_consoleField.buffer);
        if ( g_consoleField.buffer[0] != '\\' && g_consoleField.buffer[0] != '/' )
        {
            if ( Console_IsClientDisconnected() && Q_stricmpn(g_consoleField.buffer, "quit", 4) && Q_stricmpn(g_consoleField.buffer, "kill", 4) )
            {
                Con_Restricted_AddBuf(g_consoleField.buffer);
            }
            else
            {
                if ( !g_consoleField.buffer[0] )
                {
                    return;
                }
                if ( !Console_IsRconCmd(g_consoleField.buffer) )
                {
                    Cbuf_AddText(localClientNum, "cmd say ");
                    Cbuf_AddText(localClientNum, g_consoleField.buffer);
                    Cbuf_AddText(localClientNum, "\n");
                }
            }
        }
        else
        {
            Con_Restricted_AddBuf(&g_consoleField.buffer[1]);
        }
        if ( g_consoleField.buffer[0] )
        {
            memcpy(&historyEditLines[nextHistoryLine++ % MAX_CON_HISTORY_COUNT], &g_consoleField, sizeof(struct field_t));
            historyLine = nextHistoryLine;
        }
        Field_Clear(&g_consoleField);
        g_consoleField.widthInPixels = g_console_field_width;
        g_consoleField.charHeight = g_console_char_height;
        g_consoleField.fixedSize = 1;
        if ( Console_IsClientDisconnected() )
        {
            SCR_UpdateScreen();
        }
    }
}