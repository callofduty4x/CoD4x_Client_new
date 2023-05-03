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



#ifndef __QCOMMON_MEM_H__
#define __QCOMMON_MEM_H__

//#define ZONE_DEBUG

#include <stdlib.h>
#ifndef __cplusplus
  #include <stdbool.h>
#endif
#include "../q_shared.h"

// define the new memory tags for the zone
//
#define TAGDEF(blah) TAG_ ## blah
enum {
	#include "tags.h"
};
typedef char memtag_t;

#ifdef __cplusplus
extern "C"{
#endif

#ifdef DEBUG_ZONE_ALLOCS
void *_D_Z_Malloc ( unsigned int iSize, memtag_t eTag, bool bZeroit, const char *psFile, int iLine);
#else
void *Z_Malloc(unsigned int iSize, memtag_t eTag, bool bZeroit);
#endif
int Z_Free(void *pvAddress);

#ifdef __cplusplus
};
#endif

/* This struct really really needs to be verified before using! */
struct HunkUser
{
  struct HunkUser *current;
  struct HunkUser *next;
  int maxSize;
  int end;
  int pos;
  const char *name;
  int fixed;
  int type;
  char buf[1];
};


void Com_InitHunkMemory(void);
void Hunk_InitDebugMemory(void);
#ifdef __cplusplus
extern "C"
{
  void Hunk_ClearTempMemory(void);
  void Hunk_ClearTempMemoryHigh(void);
  void Hunk_Clear();
};
#endif
struct HunkUser * Hunk_UserCreate(int maxSize, const char *name, byte fixed, byte a4, int type);
void TempMemoryReset(struct HunkUser *hu);
void* Hunk_AllocateTempMemory(int size);
void* Hunk_AllocateTempMemoryHigh(int size);
void Hunk_ResetDebugMem();
void TempMemorySetPos(char *pos);
void Hunk_FreeTempMemory(void *buffer);
void* TempMalloc( int );
void* TempMallocAlign( int );
void* TempMallocAlignStrict( int );
char *CopyString( const char *in );
void FreeString( char *free );
void Sys_OutOfMemError(const char* filename, int line);
void Z_FreeTags( int tag );
void Com_InitSmallZoneMemory( void );
void Com_InitZoneMemory( void );
char* Z_MallocGarbage(int, const char*, int);

#ifndef BSPC
void* Hunk_Alloc(int size, const char* name, int type);
void Hunk_Clear();
#endif

void Hunk_UserDestroy(struct HunkUser *user);
void *Hunk_AllocInternal(int size);
#define L_Malloc malloc
#define L_Free free

void Hunk_FreeDebugMem(void *mem);
void Hunk_ShutdownDebugMemory();
void Hunk_CheckTempMemoryHighClear();

#ifdef ZONE_DEBUG
#define Z_TagMalloc(size, tag)			Z_TagMallocDebug(size, tag, #size, __FILE__, __LINE__)
#define Z_Malloc(size)					Z_MallocDebug(size, #size, __FILE__, __LINE__)
#define S_Malloc(size)					S_MallocDebug(size, #size, __FILE__, __LINE__)
void *Z_TagMallocDebug( int size, int tag, char *label, char *file, int line );	// NOT 0 filled memory
void *Z_MallocDebug( int size, char *label, char *file, int line );			// returns 0 filled memory
void *S_MallocDebug( int size, char *label, char *file, int line );			// returns 0 filled memory
#else
void *Z_TagMalloc( int size, int tag );	// NOT 0 filled memory
void *S_Malloc( int size );			// NOT 0 filled memory only for small allocations
#endif



#endif


