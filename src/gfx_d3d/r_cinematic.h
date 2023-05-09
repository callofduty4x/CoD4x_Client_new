#include "r_types_d3d.h"
#include "r_image.h"
#define _ACCLAIM_IGAADSYSTEM
#include "bink.h"

struct BINKFRAMETEXTURES
{
  unsigned int Ysize;
  unsigned int cRsize;
  unsigned int cBsize;
  unsigned int Asize;
  D3DTexture *Ytexture;
  D3DTexture *cRtexture;
  D3DTexture *cBtexture;
  D3DTexture *Atexture;
};

struct BINKTEXTURESET
{
  BINKFRAMETEXTURES textures[2];
  BINKFRAMEBUFFERS bink_buffers;
  BINKFRAMETEXTURES tex_draw;
};


enum CinematicEnum
{
  CINEMATIC_NOT_PAUSED = 0x0,
  CINEMATIC_PAUSED = 0x1,
  CINEMATIC_SCRIPT_PAUSED = 0x2,
};

struct CinematicTextureSet
{
  GfxImage imageY[2];
  GfxImage imageCr[2];
  GfxImage imageCb[2];
  GfxImage imageA[2];
  GfxImage drawImageY;
  GfxImage drawImageCr;
  GfxImage drawImageCb;
  GfxImage drawImageA;
};

struct CinematicHunk
{
  void *base;
  void *atFront;
  void *atBack;
  void *end;
};


struct __align(4) CinematicGlob
{
  char currentCinematicName[256];
  char targetCinematicName[256];
  char nextCinematicName[256];
  unsigned int nextCinematicPlaybackFlags;
  unsigned int playbackFlags;
  bool targetCinematicChanged;
  bool cinematicFinished;
  char d[6];
  unsigned int binkIOSize;
  bool c;
  bool e;
  uint8_t fileIoState;
  BINK *bink;
  BINKTEXTURESET binkTextureSet;
  CinematicHunk masterHunk;
  CinematicHunk binkHunk;
  CinematicHunk residentHunk;
  int activeImageFrame;
  int framesStopped;
  CinematicEnum currentPaused;
  CinematicEnum targetPaused;
  CinematicTextureSet textureSets[2];
  int activeTextureSet;
  int t;
  void *memPool;
  float playbackVolume;
  bool underrun;
};


void      R_Cinematic_StopPlayback();
void      R_Cinematic_SyncNow();
