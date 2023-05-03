#include <stdio.h>
#include "../q_shared.h"
#include "unzip.h"
#include "qcommon.h"
#include "sys_shared.h"

#define MAX_ZPATH	256
#define MAX_FILE_HANDLES 64


extern int fs_checksumFeed;
extern int fs_fakeChkSum;


union qfile_gus {
	FILE*	o;
	unzFile	z;
};

typedef struct qfile_us {
	qfile_gus	file;
	qboolean	iwdIsClone;
} qfile_ut;

struct fileInPack_s {
	unsigned long	pos;	// file info position in zip
	char	*name;	// name of the file
	struct	fileInPack_s*	next;	// next file in the hash
};

struct pack_t
{	//Verified
	char	pakFilename[MAX_OSPATH];	// c:\quake3\baseq3\pak0.pk3
	char	pakBasename[MAX_OSPATH];	// pak0
	char	pakGamename[MAX_OSPATH];	// baseq3
	unzFile	handle;	// handle to zip file +0x300
	int	checksum;	// regular checksum
	int	pure_checksum;	// checksum for pure
	int	hasOpenFile;
	int	numFiles;	// number of files in pk3
	int	referenced;	// referenced file flags
	int	hashSize;	// hash table size (power of 2) +0x318
	fileInPack_s*	*hashTable;	// hash table +0x31c
	fileInPack_s*	buildBuffer;	// buffer with the filenames etc. +0x320
};

struct fileHandleData_t{
	qfile_ut	handleFiles;
	qboolean	handleSync;
	int			fileSize;
	int			zipFilePos;
	pack_t*		zipFile;
	qboolean	streamed;
	char		name[MAX_ZPATH];
}; //0x11C (284) Size

struct directory_t
{	//Verified
	char	path[MAX_OSPATH];	// c:\quake3
	char	gamedir[MAX_OSPATH];	// baseq3
};

struct searchpath_s {	//Verified
	struct searchpath_s *next;
	pack_t	*pack;	// only one of pack / dir will be non NULL
	directory_t	*dir;
	qboolean	bLocalized;
	int ignore;
	int ignorePureCheck;
	int language;
};

extern fileHandleData_t fsh[MAX_FILE_HANDLES +1];
extern searchpath_s *fs_searchpaths;
extern int fs_numServerIwds;
extern int fs_serverIwds[1024];

int 		FS_UseSearchPath(const searchpath_s *pSearch);
FILE	    *FS_FileForHandle( fileHandle_t f );
extern "C"  int FS_FileSeek(FILE *file, int offset, int whence);
extern "C"  int FS_FileGetFileSize(FILE *file);
extern "C"  unsigned int FS_FileRead(void *ptr, unsigned int len, FILE *stream);

void FS_CheckFileSystemStarted()
{
    assert(fs_searchpaths);
}



bool FS_IsBackupSubStr(const char *filenameSubStr)
{
  if ( filenameSubStr[0] == '.' && filenameSubStr[1] == '.' )
  {
    return true;
  }
  if( filenameSubStr[0] == ':' && filenameSubStr[1] == ':' )
  {
    return true;
  }
  return false;
}


REGPARM(3) bool FS_SanitizeFilename(const char *filename, char *sanitizedName, int sanitizedNameSize)
{
  int srcIndex;
  int dstIndex;

  assert(filename);
  assert(sanitizedName);
  assert(sanitizedNameSize > 0);

  for ( srcIndex = 0; filename[srcIndex] == '/' || filename[srcIndex] == '\\'; ++srcIndex );

  dstIndex = 0;
  while ( filename[srcIndex] )
  {
    if ( FS_IsBackupSubStr(&filename[srcIndex]) )
    {
      return false;
    }
    if ( filename[srcIndex] != '.' || (filename[srcIndex + 1] != 0 && 
	filename[srcIndex + 1] != '/' && filename[srcIndex + 1] != '\\' ))
    {
      if ( dstIndex + 1 >= sanitizedNameSize )
      {
        assert(dstIndex + 1 < sanitizedNameSize);
        return false;
      }
      if ( filename[srcIndex] == '/' || filename[srcIndex] == '\\' )
      {
        sanitizedName[dstIndex] = '/';
        while ( 1 )
        {
          if ( !(filename[srcIndex +1] == '/' || filename[srcIndex +1] == '\\') )
          {
            break;
          }
          ++srcIndex;
        }
      }
      else
      {
        sanitizedName[dstIndex] = filename[srcIndex];
      }
      ++dstIndex;
    }
    ++srcIndex;
  }
  assert ( dstIndex <= srcIndex);
  sanitizedName[dstIndex] = 0;
  return true;
}

/*
=================================================================================

DIRECTORY SCANNING FUNCTIONS

=================================================================================
*/

#define	MAX_FOUND_FILES	0x4000

static int FS_ReturnPath( const char *zname, char *zpath, int *depth ) {
	int len, at, newdep;

	newdep = 0;
	zpath[0] = 0;
	len = 0;

    for ( at = 0; zname[at] != 0; ++at )
    {
        if ( zname[at] == '/' || zname[at] == '\\' )
        {
            len = at;
            ++newdep;
        }
    }

	strcpy(zpath, zname);
	zpath[len] = 0;
	*depth = newdep;

	return len;
}

int FS_AddFileToList(HunkUser *user, const char *name, const char **list, int nfiles)
{
    int i;

    if ( nfiles == MAX_FOUND_FILES -1 )
    {
        return MAX_FOUND_FILES -1;
    }
    for ( i = 0; i < nfiles; ++i )
    {
        if ( !Q_stricmp(name, list[i]) )
        {
            return nfiles;
        }
    }
    list[nfiles] = Hunk_CopyString(user, name);
    return nfiles + 1;
}

int FS_IwdIsPure(pack_t *iwd)
{
    int i;

    if ( !fs_numServerIwds )
    {
        return 1;
    }
    for ( i = 0; i < fs_numServerIwds; ++i )
    {
        if ( iwd->checksum == fs_serverIwds[i] )
        {
            return 1;
        }
    }
    return 0;
}

const char * FS_ReferencedIwdPureChecksums()
{
  int checksum;
  searchpath_s *search;
  int numIwds;
  static char info6[16384];

  info6[0] = 0;
  checksum = fs_checksumFeed;
  numIwds = 0;
  info6[strlen(info6) + 1] = 0;
  info6[strlen(info6) + 2] = 0;
  info6[strlen(info6)] = '@';
  info6[strlen(info6)] = ' ';
  for ( search = fs_searchpaths; search; search = search->next )
  {
    if ( search->pack )
    {
      if ( !search->bLocalized )
      {
        if ( search->pack->referenced )
        {
          Q_strncat(info6, sizeof(info6), va("%i ", search->pack->pure_checksum));
          checksum ^= search->pack->pure_checksum;
          ++numIwds;
        }
      }
    }
  }
  if ( fs_fakeChkSum )
  {
    Q_strncat(info6, sizeof(info6), va("%i ", fs_fakeChkSum));
  }
  Q_strncat(info6, sizeof(info6), va("%i ", numIwds ^ checksum));
  return info6;
}


const char ** FS_ListFilteredFiles(searchpath_s *searchPath, const char *path, const char *extension, const char *filter, FsListBehavior_e behavior, int *numfiles, int allocTrackType)
{
    char netpath[256];
    int numSysFiles;
    const char **sysFiles;
    char szTrimmedName[64];
    int depth;
    char *name;
    int zpathLen;
    int pathDepth;
    pack_t *iwd;
    char zpath[256];
    bool isDirSearch;
    const char **list;
    int extensionLength;
    int nfiles;
    int pathLength;
    fileInPack_s *buildBuffer;
    HunkUser *user;
    int temp;
    char sanitizedPath[256];
    searchpath_s *search;
    int i;
    int length;


    FS_CheckFileSystemStarted();
    if ( !path )
    {
        *numfiles = 0;
        return NULL;
    }
    if ( !extension )
    {
        extension = "";
    }
    if ( !FS_SanitizeFilename(path, sanitizedPath, sizeof(sanitizedPath)) )
    {
        *numfiles = 0;
        return 0;
    }
    isDirSearch = Q_stricmp(extension, "/") == 0;
    
    pathLength = strlen(sanitizedPath);
    if ( pathLength > 0 && (sanitizedPath[pathLength -1] == '\\' || sanitizedPath[pathLength -1] == '/'))
    {
        --pathLength;
    }

    extensionLength = strlen(extension);
    nfiles = 0;
    FS_ReturnPath(sanitizedPath, zpath, &pathDepth);
    if ( sanitizedPath[0] )
    {
        ++pathDepth;
    }
    

    user = Hunk_UserCreate(0x20000, "FS_ListFilteredFiles", 0, 0, 3);
    list = (const char **)Hunk_UserAlloc(user, MAX_FOUND_FILES * sizeof(char*) +4, 4);


    *list = (const char *)user;
    ++list;
  
    for ( search = searchPath; search; search = search->next )
    {
        if ( FS_UseSearchPath(search) )
        {
 
            if ( search->pack )
            {

                if ( search->bLocalized || FS_IwdIsPure(search->pack) )
                {
                    iwd = search->pack;
                    buildBuffer = iwd->buildBuffer;
                    for ( i = 0; i < iwd->numFiles; ++i )
                    {
                        name = buildBuffer[i].name;
                        if ( filter )
                        {
                            if ( Com_FilterPath(filter, name, 0) )
                            {
                                nfiles = FS_AddFileToList(user, name, list, nfiles);
                            }
                            continue;
                        }
                        zpathLen = FS_ReturnPath(name, zpath, &depth);
                        if ( depth == pathDepth && pathLength <= zpathLen && (pathLength <= 0 || name[pathLength] == '/') && !Q_stricmpn(name, sanitizedPath, pathLength) )
                        {
                            length = strlen(name);
                            if ( isDirSearch )
                            {
                                assert(extensionLength == 1);
                                assert(extension[0] == '/' && extension[1] == '\0');
                            }
                            if ( (isDirSearch && length > 0 && name[length - 1] == '/') || !extensionLength || (length > extensionLength && name[length - extensionLength - 1] == '.' && !Q_stricmp(&name[length - extensionLength], extension)) )
                            {
                                temp = pathLength;
                                if ( pathLength )
                                {
                                    ++temp;
                                }
                                if ( isDirSearch )
                                {
                                    strcpy(szTrimmedName, &name[temp]);

                                    szTrimmedName[strlen(szTrimmedName) - 1] = 0;
                                    nfiles = FS_AddFileToList(user, szTrimmedName, list, nfiles);
                                }
                                else
                                {
                                    nfiles = FS_AddFileToList(user, &name[temp], list, nfiles);
                                }
                            }
                        }
                    }
                }

            }
            else if ( search->dir )
            {
                if ( (!fs_restrict->current.enabled && !fs_numServerIwds) || behavior != FS_LIST_PURE_ONLY)
                {
                    FS_BuildOSPath(search->dir->path, search->dir->gamedir, sanitizedPath, netpath);
                    sysFiles = Sys_ListFiles(netpath, extension, filter, &numSysFiles, isDirSearch);
                    for ( i = 0; i < numSysFiles; ++i )
                    {
                        nfiles = FS_AddFileToList(user, sysFiles[i], list, nfiles);
                    }
                    FS_FreeFileList(sysFiles);
                }
            }

        }
    }
    *numfiles = nfiles;
    if ( nfiles )
    {
        list[nfiles] = 0;
        return list;
    }
    Hunk_UserDestroy(user);
    return NULL;

}


int FS_filelength(int f)
{
    FILE *h;

    assert(f);

    FS_CheckFileSystemStarted();
    if ( fsh[f].zipFile )
    {
        unsigned long sz;
        if(unzGetCurrentFileSize(fsh[f].handleFiles.file.z, &sz) != UNZ_OK)
        {
            return 0;
        }
        return sz;
    }
    h = FS_FileForHandle(f);
    return FS_FileGetFileSize(h);
}


int FS_SkipDataInCurrentZipFile(unzFile file, unsigned int len)
{
	char dummybuffer[0x10000];
	int efflen;
	int readlen = 0;
	int r;


	while(len > 0)
	{
		if(len > sizeof(dummybuffer))
		{
			efflen = sizeof(dummybuffer);
		}else{
			efflen = len;
		}

		r = unzReadCurrentFile(file, dummybuffer, efflen);
		if(r > 0)
		{
			readlen += r;
		}
		len -= efflen;
	}
	return readlen;
}

int FS_Seek(fileHandle_t f, long offset, fsOrigin_t origin)
{
    FILE *iofh;
    int iZipPos;
    unsigned int iZipOffset;

    FS_CheckFileSystemStarted();
    
    assert(!fsh[f].streamed);

    if ( !fsh[f].zipFile )
    {
        iofh = FS_FileForHandle(f);
        return FS_FileSeek(iofh, offset, origin);
    }
    if ( !offset && origin == FS_SEEK_SET )
    {
        unzSetCurrentFileInfoPosition(fsh[f].handleFiles.file.z, fsh[f].zipFilePos);
        return unzOpenCurrentFile(fsh[f].handleFiles.file.z);
    }
    if ( !offset && origin == FS_SEEK_CUR)
    {
        return 0;
    }
    
    iZipPos = unztell(fsh[f].handleFiles.file.z);

    switch ( origin )
    {
        case FS_SEEK_CUR:
            assert(offset != 0);
            if ( offset >= 0 )
            {
                iZipOffset = offset;
            }
            else
            {
                unzSetCurrentFileInfoPosition(fsh[f].handleFiles.file.z, fsh[f].zipFilePos);
                unzOpenCurrentFile(fsh[f].handleFiles.file.z);
                iZipOffset = offset + iZipPos;
            }
            break;
        case FS_SEEK_END:
            if ( offset + FS_filelength(f) >= iZipPos )
            {
                iZipOffset = offset + FS_filelength(f) - iZipPos;
            }
            else
            {
                unzSetCurrentFileInfoPosition(fsh[f].handleFiles.file.z, fsh[f].zipFilePos);
                unzOpenCurrentFile(fsh[f].handleFiles.file.z);
                iZipOffset = offset + FS_filelength(f);
            }
            break;
        case FS_SEEK_SET:
            if ( offset >= iZipPos )
            {
                iZipOffset = offset - iZipPos;
            }
            else
            {
                unzSetCurrentFileInfoPosition(fsh[f].handleFiles.file.z, fsh[f].zipFilePos);
                unzOpenCurrentFile(fsh[f].handleFiles.file.z);
                iZipOffset = offset;
            }
            break;
        default:
            assertx(0, "Bad origin %i in FS_Seek", origin);
            return -1;
    }

    if ( FS_SkipDataInCurrentZipFile(fsh[f].handleFiles.file.z, iZipOffset) > 0)
    {
        return 0;
    }
    return -1;
}


int FS_Read(void *buffer, int len, int h)
{
  int tries;
  unsigned int remaining; 
  char *buf; 
  FILE *f; 
  int read; 

  FS_CheckFileSystemStarted();
  if ( !h )
  {
    return 0;
  }
  if ( fsh[h].zipFile )
  {
    return unzReadCurrentFile(fsh[h].handleFiles.file.z, (char *)buffer, len);
  }
  f = FS_FileForHandle(h);
  buf = (char *)buffer;
  remaining = len;
  tries = 0;
  while ( remaining )
  {
    read = FS_FileRead(buf, remaining, f);
    if ( !read )
    {
      if ( tries )
      {
        return len - remaining;
      }
      tries = 1;
    }
    if ( read == -1 )
    {
      if ( h >= 50 && h < 61 )
      {
        return -1;
      }
      Com_Error(ERR_FATAL, "FS_Read: -1 bytes read");
    }
    remaining -= read;
    buf += read;
  }
  return len;
}
