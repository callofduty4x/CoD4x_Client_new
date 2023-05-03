#include "../q_shared.h"
#include "../common/qcommon.h"
#include <windows.h>

HWND g_hwndGame[4];
unsigned int g_hiddenCount;

WINAPI int HideWindowCallback(HWND hwnd, long int lParam)
{
  int styleEx;
  char caption[1024];
  int style;

  if ( GetWindowTextA(hwnd, caption, 1024) && strcmp(caption, Com_GetBuildDisplayName()) )
  {
    return 1;
  }
  style = GetWindowLongA(hwnd, -16);
  styleEx = GetWindowLongA(hwnd, -20);
  if ( style & 0x10000000 )
  {
    g_hwndGame[g_hiddenCount++] = hwnd;
    SetWindowLongA(hwnd, -16, style & 0xEFFFFFFF);
    SetWindowLongA(hwnd, -20, styleEx & 0xFFFFFFF7);
  }
  return 1;
}

void FixWindowsDesktop()
{
  DWORD ti;
  HDC hdc;
  uint16_t ramp[3][256];
  unsigned int i;
  HWND hwndDesktop;

  ChangeDisplaySettingsA(0, 0);
  ti = GetCurrentThreadId();
  EnumThreadWindows(ti, HideWindowCallback, 0);
  hwndDesktop = GetDesktopWindow();
  hdc = GetDC(hwndDesktop);
  for ( i = 0; (signed int)i < 256; ++i )
  {
    ramp[0][i] = 257 * i;
    ramp[1][i] = 257 * i;
    ramp[2][i] = 257 * i;
  }
  SetDeviceGammaRamp(hdc, ramp);
  ReleaseDC(hwndDesktop, hdc);
}
