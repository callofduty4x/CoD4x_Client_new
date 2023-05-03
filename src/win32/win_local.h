#include <q_shared.h>
#include <windows.h>
#include "win_shared.h"


typedef struct{
	HINSTANCE reflib_library;           // Handle to refresh DLL
	qboolean reflib_active;
	HWND hWnd;							//0xcc1b6fc
	HINSTANCE hInstance;				//0xcc1b700
	qboolean activeApp;
	qboolean isMinimized;				//0xcc1b708
	qboolean recenterMouse;
	// when we get a windows message, we store the time off so keyboard processing
	// can know the exact time of an event
	unsigned sysMsgTime;				//0xcc1b710
} WinVars_t;


extern WinVars_t g_wv;
enum sysEventType_t: int;
void 		FixWindowsDesktop();
void 		Sys_QueEvent(int time, sysEventType_t type, int value, int value2, int ptrLength, void *ptr);
void 		Conbuf_AppendTextInMainThread(const char *msg);
const char* Win_LocalizeRef(char const*);
void 		Win_ShutdownLocalization();
char *		Sys_ConsoleInput( void );
void		Sys_CreateConsole( qboolean show );
void		Sys_ShowEarlyErrorDialog(const char* functionName);
void		Sys_InitializeCriticalSections( void );
void		Sys_InitMainThread();
void 		Win_InitLocalization();
void		InitTiming();
void		Sys_FindInfo();
void		Sys_CreateSplashWindow();
LONG WINAPI MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
extern "C" int64_t 	X86_Benchmark();
