#include <windows.h>
#include "win_local.h"

HWND splashWndHwnd;

void Sys_ShowSplashWindow()
{
		if(splashWndHwnd){
			ShowWindow(splashWndHwnd ,SW_SHOW );
			UpdateWindow(splashWndHwnd);
		}
}

void Sys_DestroySplashWindow()
{
    if ( splashWndHwnd )
    {
        ShowWindow(splashWndHwnd, 0);
        DestroyWindow(splashWndHwnd);
        splashWndHwnd = 0;
    }
}

void Sys_HideSplashWindow()
{
	if ( splashWndHwnd )
	{
		ShowWindow(splashWndHwnd, 0);
	}
}


void Sys_CreateSplashWindow()
{
  int x; 
  int y; 
  HANDLE image; 
  struct HWND__ *subWnd;
  int subX; 
  int subY; 
  struct tagRECT Rect;
  WNDCLASSA WndClass;

  WndClass.style = 0;
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.lpszMenuName = 0;
  WndClass.lpfnWndProc = DefWindowProcA;
  WndClass.hInstance = g_wv.hInstance;
  WndClass.hIcon = LoadIconA(g_wv.hInstance, (LPCSTR)1);
  WndClass.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
  WndClass.hbrBackground = (HBRUSH)6;
  WndClass.lpszClassName = "CoD Splash Screen";
  if ( RegisterClassA(&WndClass) )
  {
    x = GetSystemMetrics(16);
    y = GetSystemMetrics(17);
    image = LoadImageA(0, "cod.bmp", 0, 0, 0, 0x10u);
    if ( image )
    {
      splashWndHwnd = CreateWindowExA(0x40000u, "CoD Splash Screen", "Call of Duty 4 Multiplayer", 0x80880000, (x - 320) / 2, (y - 100) / 2, 320, 100, 0, 0, g_wv.hInstance, 0);
      if ( splashWndHwnd )
      {
        subWnd = CreateWindowExA(0, "Static", 0, 0x5000000Eu, 0, 0, 320, 100, splashWndHwnd, 0, g_wv.hInstance, 0);
        if ( subWnd )
        {
          SendMessageA(subWnd, 0x172u, 0, (LPARAM)image);
          GetWindowRect(subWnd, &Rect);
          subX = Rect.right - Rect.left + 2;
          Rect.left = (x - subX) / 2;
          subY = Rect.bottom - Rect.top + 2;
          Rect.top = (y - subY) / 2;
          Rect.right = Rect.left + subX;
          Rect.bottom = Rect.top + subY;
          AdjustWindowRect(&Rect, 0x5000000Eu, 0);
          SetWindowPos(splashWndHwnd, 0, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 4u);
        }
      }
    }
  }
}