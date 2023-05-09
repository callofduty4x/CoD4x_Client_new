/*
===========================================================================
    Copyright (C) 2010-2013  Ninja and TheKelm
    Copyright (C) 1999-2005 Id Software, Inc.

    This file is part of CoD4X18-Server source code.

    CoD4X18-Server source code is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    CoD4X18-Server source code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
===========================================================================
*/

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#define _ACCLAIM_IGAADSYSTEM

//#include "../sound/mss.h"
#include <gfx_d3d/bink.h>


LPVOID __cdecl iVirtualAlloc(LPVOID address, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
    return VirtualAlloc(address, dwSize, flAllocationType, flProtect);
}

BOOL __cdecl iVirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
{
    return VirtualFree(lpAddress, dwSize, dwFreeType);
}

DWORD __cdecl iSleepEx(DWORD dwMilliseconds, BOOL bAlertable)
{
    return SleepEx(dwMilliseconds, bAlertable);
}

BOOL __cdecl iCloseHandle(HANDLE hObject)
{
    return CloseHandle(hObject);
}

DWORD __cdecl iGetLastError()
{
    return GetLastError();
}

void __cdecl iSetLastError(DWORD dwErrCode)
{
    return SetLastError(dwErrCode);
}

BOOL __cdecl iReadFileEx(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    return ReadFileEx(hFile, lpBuffer, nNumberOfBytesToRead, lpOverlapped, lpCompletionRoutine);
}

HANDLE __cdecl iCreateFileA(char *lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

DWORD __cdecl iGetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh)
{
    return GetFileSize(hFile, lpFileSizeHigh);
}

DWORD __cdecl iGetFileAttributesA(const char *lpFileName)
{
    return GetFileAttributesA(lpFileName);
}

BOOL __cdecl iSetFileAttributesA(const char *lpFileName, DWORD dwFileAttributes)
{
    return SetFileAttributesA(lpFileName, dwFileAttributes);
}

DWORD __cdecl iInterlockedExchangeAdd(DWORD volatile *Addend, DWORD value)
{
	return InterlockedExchangeAdd((LONG volatile *)Addend, value);
}

DWORD __cdecl iInterlockedDecrement(DWORD volatile *Addend)
{
	return InterlockedDecrement((LONG volatile *)Addend);
}

DWORD __cdecl iInterlockedIncrement(DWORD volatile *Addend)
{
	return InterlockedIncrement((LONG volatile *)Addend);
}

DWORD __cdecl iInterlockedCompareExchange(DWORD volatile *Destination, DWORD Exchange, DWORD Comparand)
{
	return InterlockedCompareExchange((LONG volatile *)Destination, Exchange, Comparand);
}
LONG iInterlockedExchange(LONG volatile *Target, LONG Value)
{
    return InterlockedExchange(Target, Value);
}

void iEnterCriticalSection(PCRITICAL_SECTION lpCriticalSection)
{
    EnterCriticalSection(lpCriticalSection);
}

void iLeaveCriticalSection(PCRITICAL_SECTION lpCriticalSection)
{
    LeaveCriticalSection(lpCriticalSection);
}

void iInitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{
    InitializeCriticalSection(lpCriticalSection);
}

HANDLE __cdecl iCreateEventA(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName)
{
    return CreateEventA(lpEventAttributes, bManualReset, bInitialState, lpName);
}

BOOL iSetEvent(HANDLE hEvent)
{
    return SetEvent(hEvent);
}

BOOL iResetEvent(HANDLE hEvent)
{
    return ResetEvent(hEvent);
}

DWORD iResumeThread(HANDLE hThread)
{
    return ResumeThread(hThread);
}

DWORD iSuspendThread(HANDLE hThread)
{
    return SuspendThread(hThread);
}

DWORD_PTR iSetThreadAffinityMask(HANDLE hThread, DWORD_PTR dwThreadAffinityMask)
{
    return SetThreadAffinityMask(hThread, dwThreadAffinityMask);
}

BOOL iSetThreadPriority(HANDLE hThread, int nPriority)
{
    return SetThreadPriority(hThread, nPriority);
}

BOOL iDuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle, HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwOptions)
{
    return DuplicateHandle(hSourceProcessHandle, hSourceHandle, hTargetProcessHandle, lpTargetHandle, dwDesiredAccess, bInheritHandle, dwOptions);
}
DWORD itimeGetTime()
{
    return timeGetTime();
}
DWORD iWaitForSingleObject(HANDLE hHandle, DWORD  dwMilliseconds)
{
    return  WaitForSingleObject(hHandle, dwMilliseconds);
}
DWORD iGetCurrentThreadId()
{
    return GetCurrentThreadId();
}
HANDLE WinGetCurrentThread( )
{
    return GetCurrentThread( );
}
HWND iGetActiveWindow()
{
    return GetActiveWindow();
}
int iMessageBoxA(HWND   hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT   uType)
{
    return MessageBoxA(hWnd, lpText, lpCaption, uType);
}
HANDLE iCreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, __drv_aliasesMem LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
{
    return CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}
BOOL iShowWindow(HWND hWnd, int nCmdShow)
{
    return ShowWindow(hWnd, nCmdShow);
}
BOOL iGetWindowRect(HWND   hWnd, LPRECT lpRect)
{
    return GetWindowRect(hWnd, lpRect);
}
/*IDirect3D9 * iDirect3DCreate9(UINT SDKVersion)
{
    return Direct3DCreate9(SDKVersion);
}*/
HRESULT iD3DXCreateBuffer(DWORD NumBytes, LPD3DXBUFFER *ppBuffer)
{
    return D3DXCreateBuffer(NumBytes, ppBuffer);
}
UINT iMapVirtualKeyA(UINT uCode, UINT uMapType)
{
    return MapVirtualKeyA(uCode, uMapType);
}


#define iAILCALL __cdecl
#define iRADEXPLINK __cdecl
#undef RADEXPFUNC
#undef DXDEC
#define RADEXPFUNC
#define DXDEC
/*
DXDEC void iAILCALL iAIL_set_file_callbacks(AIL_file_open_callback opencb, AIL_file_close_callback closecb, AIL_file_seek_callback seekcb, AIL_file_read_callback readcb)
{
    AIL_set_file_callbacks(opencb, closecb, seekcb, readcb);
}
DXDEC char*     iAILCALL iAIL_set_redist_directory(char const*dir)
{
    return AIL_set_redist_directory(dir);
}
DXDEC  S32     iAILCALL  iAIL_startup (void)
{
    return AIL_startup();
}
DXDEC SINTa iAILCALL iAIL_set_preference(U32 number, SINTa value)
{
    return AIL_set_preference(number, value);
}
DXDEC HDIGDRIVER iAILCALL iAIL_open_digital_driver( U32 frequency, S32 bits, S32 channel, U32 flags )
{
    return AIL_open_digital_driver( frequency, bits, channel, flags );
}
DXDEC MSSVECTOR3D * iAILCALL iAIL_speaker_configuration (HDIGDRIVER dig, S32 *n_physical_channels, S32 *n_logical_channels, F32 *falloff_power,  MSS_MC_SPEC *channel_spec)
{
    return AIL_speaker_configuration (dig, n_physical_channels, n_logical_channels, falloff_power,  channel_spec);
}
DXDEC  void iAILCALL iAIL_set_3D_distance_factor(HDIGDRIVER dig, F32 factor)
{
    AIL_set_3D_distance_factor(dig, factor);
}
DXDEC void iAILCALL iAIL_set_3D_rolloff_factor(HDIGDRIVER dig, F32 factor)
{
    AIL_set_3D_rolloff_factor(dig, factor);
}
DXDEC void iAILCALL iAIL_set_speaker_configuration(HDIGDRIVER dig, MSSVECTOR3D *array,S32  n_channels, F32 falloff_power)
{
    AIL_set_speaker_configuration(dig, array, n_channels, falloff_power);
}
DXDEC char *iAILCALL iAIL_last_error(void){
    return AIL_last_error();
}
DXDEC HSAMPLE iAILCALL iAIL_allocate_sample_handle(HDIGDRIVER dig)
{
    return AIL_allocate_sample_handle(dig);
}
DXDEC  void iAILCALL iAIL_init_sample(HSAMPLE S, S32 format, U32 flags)
{
    AIL_init_sample(S, format, flags);
}
DXDEC void iAILCALL iAIL_set_room_type (HDIGDRIVER dig, S32 room_type)
{
    AIL_set_room_type (dig, room_type);
}
DXDEC void iAILCALL iAIL_set_digital_master_reverb_levels (HDIGDRIVER dig, F32 dry_level, F32 wet_level)
{
    AIL_set_digital_master_reverb_levels (dig, dry_level, wet_level);
}
DXDEC void iAILCALL iAIL_end_sample(HSAMPLE S)
{
    AIL_end_sample(S);
}
DXDEC void iAILCALL iAIL_stop_sample (HSAMPLE S)
{
    AIL_stop_sample (S);
}
DXDEC  void iAILCALL iAIL_shutdown(void)
{
    AIL_shutdown();
}
DXDEC U32 iAILCALL iAIL_sample_status(HSAMPLE S)
{
    return AIL_sample_status(S);
}
DXDEC S32 iAILCALL iAIL_set_sample_info(HSAMPLE S, AILSOUNDINFO const * info)
{
    return AIL_set_sample_info(S, info);
}
DXDEC void iAILCALL iAIL_set_sample_loop_count (HSAMPLE S, S32 loop_count)
{
    AIL_set_sample_loop_count (S, loop_count);
}
DXDEC void iAILCALL iAIL_set_sample_ms_position (HSAMPLE S, S32 milliseconds)
{
    AIL_set_sample_ms_position (S, milliseconds);
}
DXDEC  void iAILCALL iAIL_resume_sample (HSAMPLE S)
{
    AIL_resume_sample (S);
}
DXDEC S32 iAILCALL iAIL_stream_status(HSTREAM stream)
{
    return AIL_stream_status(stream);
}
DXDEC void iAILCALL iAIL_sample_ms_position (HSAMPLE S, S32 * total_milliseconds, S32 * current_milliseconds)
{
    AIL_sample_ms_position (S, total_milliseconds, current_milliseconds);
}
DXDEC S32 iAILCALL iAIL_sample_3D_position(HSAMPLE  obj, F32 *X, F32 *Y, F32 *Z)
{
    return AIL_sample_3D_position(obj, X, Y, Z);
}
DXDEC  S32 iAILCALL iAIL_digital_CPU_percent(HDIGDRIVER dig)
{
    return AIL_digital_CPU_percent(dig);
}
DXDEC void iAILCALL iAIL_sample_volume_levels(HSAMPLE S, F32 *left_level, F32 *right_level)
{
    AIL_sample_volume_levels(S, left_level, right_level);
}
DXDEC void iAILCALL iAIL_sample_volume_pan (HSAMPLE S, F32* volume, F32* pan)
{
    AIL_sample_volume_pan (S, volume, pan);
}
DXDEC void iAILCALL iAIL_close_stream(HSTREAM stream)
{
    AIL_close_stream(stream);
}
DXDEC void iAILCALL iAIL_stream_info(HSTREAM stream, S32* datarate, S32* sndtype, S32* length, S32* memory)
{
    AIL_stream_info(stream, datarate, sndtype, length, memory);
}
DXDEC void iAILCALL iAIL_set_stream_loop_count(HSTREAM stream, S32 count)
{
    AIL_set_stream_loop_count(stream, count);
}
DXDEC void iAILCALL iAIL_stream_ms_position(HSTREAM S, S32 *total_milliseconds, S32 *current_milliseconds)
{
    AIL_stream_ms_position(S, total_milliseconds, current_milliseconds);
}
DXDEC  void iAILCALL iAIL_set_stream_ms_position(HSTREAM S, S32 milliseconds)
{
    AIL_set_stream_ms_position(S, milliseconds);
}
DXDEC void iAILCALL iAIL_set_sample_3D_position(HSAMPLE obj, F32 X, F32 Y, F32 Z)
{
    AIL_set_sample_3D_position(obj, X, Y, Z);
}
DXDEC void iAILCALL iAIL_set_sample_3D_distances (HSAMPLE S, F32 max_dist, F32 min_dist, S32 auto_3D_wet_atten)
{
    AIL_set_sample_3D_distances (S, max_dist, min_dist, auto_3D_wet_atten);
}
DXDEC void iAILCALL iAIL_pause_stream(HSTREAM stream, S32 onoff)
{
    AIL_pause_stream(stream, onoff);
}
DXDEC HSTREAM iAILCALL iAIL_open_stream(HDIGDRIVER dig, char const * filename, S32 stream_mem)
{
    return AIL_open_stream(dig, filename, stream_mem);
}
DXDEC F32 FAR* iAILCALL iAIL_sample_channel_levels (HSAMPLE S, S32 FAR *n_levels)
{
    return AIL_sample_channel_levels (S, n_levels);
}
DXDEC void iAILCALL iAIL_set_sample_channel_levels (HSAMPLE S, F32 FAR *level_array, S32 n_levels)
{
    AIL_set_sample_channel_levels (S, level_array, n_levels);
}
DXDEC void iAILCALL iAIL_set_sample_reverb_levels(HSAMPLE S, F32 dry_level, F32 wet_level)
{
    AIL_set_sample_reverb_levels(S, dry_level, wet_level);
}
DXDEC  S32 iAILCALL iAIL_sample_playback_rate(HSAMPLE S)
{
    return AIL_sample_playback_rate(S);
}
DXDEC void iAILCALL iAIL_set_sample_volume_levels(HSAMPLE S, F32 left_level, F32 right_level)
{
    AIL_set_sample_volume_levels(S, left_level, right_level);
}
DXDEC HSAMPLE iAILCALL iAIL_stream_sample_handle(HSTREAM stream)
{
    return AIL_stream_sample_handle(stream);
}
DXDEC void iAILCALL iAIL_set_sample_playback_rate(HSAMPLE S, S32 playback_rate)
{
    AIL_set_sample_playback_rate(S, playback_rate);
}
DXDEC S32 iAILCALL iAIL_WAV_info(void const* WAV_image, AILSOUNDINFO* info)
{
    return AIL_WAV_info(WAV_image, info);
}*/
RADEXPFUNC HBINK iRADEXPLINK iBinkOpen(const char PTR4* name,U32 flags)
{
    return BinkOpen(name,flags);
}
HBINK iBinkOSOpen(const char *name, unsigned int flags) //Must be different on Mac OS X
{
    return BinkOpen(name,flags);
}
RADEXPFUNC void iRADEXPLINK iBinkSetIOSize(U32 iosize)
{
    BinkSetIOSize(iosize);
}
RADEXPFUNC char PTR4* iRADEXPLINK iBinkGetError(void)
{
    return BinkGetError( );
}
RADEXPFUNC void iRADEXPLINK iBinkClose(HBINK bnk)
{
    BinkClose(bnk);
}
RADEXPFUNC S32 iRADEXPLINK iBinkWait(HBINK bnk)
{
    return BinkWait(bnk);
}
RADEXPFUNC void iRADEXPLINK iBinkGetRealtime(HBINK bink,BINKREALTIME PTR4* run,U32 frames)
{
    BinkGetRealtime(bink,run,frames);
}
RADEXPFUNC S32 iRADEXPLINK iBinkDoFrame(HBINK bnk)
{
    return BinkDoFrame(bnk);
}
RADEXPFUNC void iRADEXPLINK iBinkNextFrame(HBINK bnk)
{
    BinkNextFrame(bnk);
}
RADEXPFUNC void iRADEXPLINK iBinkSetMemory(BINKMEMALLOC a,BINKMEMFREE f)
{
    BinkSetMemory(a, f);
}
RADEXPFUNC void iRADEXPLINK iBinkSetSoundTrack(U32 total_tracks, U32 PTR4* tracks)
{
    BinkSetSoundTrack(total_tracks, tracks);
}
RADEXPFUNC void iRADEXPLINK iBinkGetFrameBuffersInfo( HBINK bink, BINKFRAMEBUFFERS * fbset )
{
    BinkGetFrameBuffersInfo( bink, fbset );
}
RADEXPFUNC void iRADEXPLINK iBinkRegisterFrameBuffers( HBINK bink, BINKFRAMEBUFFERS * fbset )
{
    BinkRegisterFrameBuffers( bink, fbset );
}
RADEXPFUNC S32 iRADEXPLINK iBinkControlBackgroundIO(HBINK bink,U32 control)
{
    return BinkControlBackgroundIO(bink, control);
}
RADEXPFUNC S32 iRADEXPLINK iBinkPause(HBINK bnk,S32 pause)
{
    return BinkPause(bnk, pause);
}
RADEXPFUNC void iRADEXPLINK iBinkSetMixBinVolumes(HBINK bnk,U32 trackid, U32 PTR4* vol_mix_bins, S32 PTR4* volumes, U32 total)
{
    BinkSetMixBinVolumes(bnk,trackid, vol_mix_bins, volumes, total);
}
RADEXPFUNC void iRADEXPLINK iBinkSetVolume(HBINK bnk, U32 trackid, S32 volume)
{
    BinkSetVolume(bnk, trackid, volume);
}
RADEXPFUNC s32  iRADEXPLINK iBinkSetSoundSystem(BINKSNDSYSOPEN open, u32 param)
{
    return BinkSetSoundSystem(open, param);
}
