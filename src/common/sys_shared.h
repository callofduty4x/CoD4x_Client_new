#include "../win32/win_shared.h"

bool IN_IsTalkKeyHeld();
void __noreturn Sys_DirectXFatalError();
extern double msecPerRawTimerTick;
struct _OVERLAPPED;
extern "C"
{
    bool iReadFileEx(void* hFile, void* lpBuffer, DWORD nNumberOfBytesToRead, _OVERLAPPED* lpOverlapped, void (__stdcall *lpCompletionRoutine)(long unsigned int, long unsigned int,  struct _OVERLAPPED *));
    DWORD iGetLastError();
    DWORD iSleepEx(DWORD dwMilliseconds, bool bAlertable);
    bool  iCloseHandle(void* hObject);
    DWORD iGetFileSize(void* hFile, DWORD* lpFileSizeHigh);


}

char * Sys_GetClipboardData();
void Sys_FreeClipboardData(char *ptr);
const char ** Sys_ListFiles(const char *directory, const char *extension, const char *filter, int *numfiles, int wantsubs);

unsigned int Sys_MillisecondsRaw( void );
void        Sys_Quit();