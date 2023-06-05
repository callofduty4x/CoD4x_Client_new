bool UI_IsFullscreen(int localClientNum);
bool UI_SetActiveMenu(int localClientNum, int menu);
int UI_GetMenuScreen();
void UI_SetMap(const char *mapname, const char *gametype);


enum uiMenuCommand_t
{
  UIMENU_NONE,
  UIMENU_MAIN,
  UIMENU_INGAME,
  UIMENU_NEED_CD,
  UIMENU_BAD_CD_KEY,
  UIMENU_PREGAME,
  UIMENU_POSTGAME,
  UIMENU_WM_QUICKMESSAGE,
  UIMENU_WM_AUTOUPDATE,
  UIMENU_SCRIPT_POPUP,
  UIMENU_SCOREBOARD,
  UIMENU_ENDOFGAME
};