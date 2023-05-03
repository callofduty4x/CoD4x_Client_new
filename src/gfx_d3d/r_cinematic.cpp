#include "r_types_d3d.h"
#include "r_local.h"
#include "r_cinematic.h"
#include "../common/qcommon.h"

extern CinematicGlob cinematicGlob;

extern "C" void Lock_Bink_textures(BINKTEXTURESET *set_textures)
{
    BINKFRAMETEXTURES *frameTextures;
    BINKFRAMEPLANESET *framePlaneSet;
    signed int flags;
    int frameNum;
    int i;
    D3DLOCKED_RECT rect;

    frameTextures = set_textures->textures;
    framePlaneSet = set_textures->bink_buffers.Frames;
    frameNum = set_textures->bink_buffers.FrameNum;

    for(i = 0; i < set_textures->bink_buffers.TotalFrames; ++i)
    {
        flags = 0x8000;
        if ( i != frameNum )
        {
            flags = 16;
        }
        if ( frameTextures->Ytexture->LockRect(0, &rect, 0, flags) >= 0 )
        {
            framePlaneSet->YPlane.Buffer = rect.pBits;
            framePlaneSet->YPlane.BufferPitch = rect.Pitch;
        }
        if ( frameTextures->cRtexture->LockRect(0, &rect, 0, flags) >= 0 )
        {
            framePlaneSet->cRPlane.Buffer = rect.pBits;
            framePlaneSet->cRPlane.BufferPitch = rect.Pitch;
        }
        if ( frameTextures->cBtexture->LockRect(0, &rect, 0, flags) >= 0 )
        {
            framePlaneSet->cBPlane.Buffer = rect.pBits;
            framePlaneSet->cBPlane.BufferPitch = rect.Pitch;
        }
        if ( frameTextures->Atexture )
        {
            if ( frameTextures->Atexture->LockRect(0, &rect, 0, flags) >= 0 )
            {
            framePlaneSet->APlane.Buffer = rect.pBits;
            framePlaneSet->APlane.BufferPitch = rect.Pitch;
            }
        }
        ++frameTextures;
        ++framePlaneSet;
    }
}


extern "C" void Unlock_Bink_textures(IDirect3DDevice9 *d3d_device, BINKTEXTURESET *set_textures, HBINK hbink)
{
    BINKFRAMETEXTURES *frameTextures;
    BINKFRAMEPLANESET *framePlaneSet;
    BINKFRAMETEXTURES *frameTexture;
    int numRects;
    int i;
    RECT rect;

    frameTextures = set_textures->textures;
    framePlaneSet = set_textures->bink_buffers.Frames;

    for(i = 0; i < set_textures->bink_buffers.TotalFrames; ++i)
    {
        frameTextures->Ytexture->UnlockRect(0);
        frameTextures->cRtexture->UnlockRect(0);
        frameTextures->cBtexture->UnlockRect(0);
        framePlaneSet->YPlane.Buffer = NULL;
        framePlaneSet->cRPlane.Buffer = NULL;
        framePlaneSet->cBPlane.Buffer = NULL;

        if ( frameTextures->Atexture )
        {
            frameTextures->Atexture->UnlockRect(0);
            framePlaneSet->APlane.Buffer = NULL;
        }
        ++frameTextures;
        ++framePlaneSet;
    }


    frameTexture = &set_textures->textures[set_textures->bink_buffers.FrameNum];
    numRects = BinkGetRects(hbink, 0);


    if ( numRects <= 0 )
    {
            return;
    }
    i = 0;
    for(i = 0; i < numRects; ++i)
    {
        rect.left = hbink->FrameRects[i].Left;
        rect.top = hbink->FrameRects[i].Top;
        rect.right = hbink->FrameRects[i].Width + rect.left;
        rect.bottom = hbink->FrameRects[i].Height + rect.top;

        frameTexture->Ytexture->AddDirtyRect(&rect);
        if ( frameTexture->Atexture )
        {
            frameTexture->Atexture->AddDirtyRect(&rect);
        }
        rect.left /= 2;
        rect.top /= 2;
        rect.right /= 2;
        rect.bottom /= 2;
        frameTexture->cRtexture->AddDirtyRect(&rect);
        frameTexture->cBtexture->AddDirtyRect(&rect);
    }
    d3d_device->UpdateTexture(frameTexture->Ytexture, set_textures->tex_draw.Ytexture);
    d3d_device->UpdateTexture(frameTexture->cRtexture, set_textures->tex_draw.cRtexture);
    d3d_device->UpdateTexture(frameTexture->cBtexture, set_textures->tex_draw.cBtexture);
    if ( frameTexture->Atexture )
    {
        d3d_device->UpdateTexture(frameTexture->Atexture, set_textures->tex_draw.Atexture);
    }
}


void R_Cinematic_ClearTexture(D3DTexture *texture, int width, int height, char clearValue)
{
  HRESULT hr;
  D3DLOCKED_RECT lockedRect;

  hr = D3DCALLNAKED(texture->LockRect(0, &lockedRect, NULL, 0x2000));
  if ( hr >= 0 )
  {
    assert(lockedRect.Pitch >= width);

    memset(lockedRect.pBits, clearValue, lockedRect.Pitch * height);
    texture->UnlockRect(0);
  }
  else
  {
    Com_PrintError(CON_CHANNEL_GFX, "LockRect failed with error 0x%08x - %s", (unsigned int)hr, R_ErrorDescription(hr));
  }
}


void R_Cinematic_ClearBinkDrawTextures(BINKTEXTURESET *set_textures)
{
  BINKFRAMETEXTURES* textures = &set_textures->tex_draw;
  assert(textures->Ytexture);
  assert(textures->cRtexture);
  assert(textures->cBtexture);

  R_Cinematic_ClearTexture(textures->Ytexture, set_textures->bink_buffers.YABufferWidth, set_textures->bink_buffers.YABufferHeight, 0);
  R_Cinematic_ClearTexture(textures->cRtexture, set_textures->bink_buffers.cRcBBufferWidth, set_textures->bink_buffers.cRcBBufferHeight, 128);
  R_Cinematic_ClearTexture(textures->cBtexture, set_textures->bink_buffers.cRcBBufferWidth, set_textures->bink_buffers.cRcBBufferHeight, 128);
  if ( textures->Atexture )
  {
    R_Cinematic_ClearTexture(textures->Atexture, set_textures->bink_buffers.YABufferWidth, set_textures->bink_buffers.YABufferHeight, 0);
  }
}


void R_Cinematic_UpdateFrame(bool force_wait)
{
  R_Cinematic_UpdateFrame();
}


void* __stdcall R_Cinematic_Bink_Alloc(unsigned int size)
{
  void *mptr;

  mptr = cinematicGlob.binkHunk.atFront;
  cinematicGlob.binkHunk.atFront = (char *)cinematicGlob.binkHunk.atFront + size;
  if ( cinematicGlob.binkHunk.atFront > cinematicGlob.binkHunk.atBack )
  {
    mptr = (void *)-1;
  }
  return mptr;
}

void __stdcall R_Cinematic_Bink_Free(void* mptr)
{

}

int CinematicHunk_GetFreeSpace(CinematicHunk *hunk)
{
  assert(hunk->base);
  assert(hunk->atFront);
  assert(hunk->atBack);
  assert(hunk->end);

  return (char*)hunk->atBack - (char*)hunk->atFront;
}
/*
bool QR_Cinematic_BinkOpenPath(const char *filepath, unsigned int playbackFlags, char *errText, int errTextSize)
{
  if(playbackFlags & 8)
  {
    return false;
  }

  cinematicGlob.binkIOSize = CinematicHunk_GetFreeSpace(&cinematicGlob.binkHunk) - 0x180000;
  BinkSetIOSize(cinematicGlob.binkIOSize);

  cinematicGlob.bink = BinkOpen(filepath, 0x1104400u);
  if ( !cinematicGlob.bink )
  {
      Com_sprintf(errText, errTextSize, "BinkOpen failed on %s because: %s\n", filepath, BinkGetError());
      Com_Printf(CON_CHANNEL_DONT_FILTER,"%s", errText);
      return false;
  }
  Com_Printf(CON_CHANNEL_DONT_FILTER,"\nSuccess Open bink file\n");

  return true;
  
  cinematicGlob.isPreloaded = 0;
  if ( cinematicGlob.bink )
  {
      cinematicGlob.fileIoState = 0;
      BinkPause(cinematicGlob.bink, 1);
      R_Cinematic_SeizeIO();
      while ( cinematicGlob.fileIoState && R_Cinematic_GetPercentageFull() < 10 )
      {
          NET_Sleep(1);
      }
      cinematicGlob.isPreloaded = 1;
      BinkPause(cinematicGlob.bink, 0);
      while ( BinkWait(cinematicGlob.bink) )
      {
          NET_Sleep(1);
      }
  }

}
*/

REGPARM(3) bool R_Cinematic_BinkOpenPath(const char *filepath, unsigned int playbackFlags, char *errText, int errTextSize);

REGPARM(3) bool R_Cinematic_BinkOpen(const char *filename, unsigned int playbackFlags, char *errText, int errTextSize)
{
    const char *cwd;
    char filepath[2][256];

    cwd = fs_basepath->current.string;
    assert(cwd);

    filepath[1][0] = 0;
    if ( playbackFlags & 0x00000020 )
    {
      assert(playbackFlags & 0x00000020);
      Com_sprintf(filepath[0], sizeof(filepath[0]), "video/%s.bik", filename);
    }
    else
    {
      Com_sprintf(filepath[0], sizeof(filepath[0]), "%s\\main\\video\\%s.bik", cwd, filename);
      Com_sprintf(filepath[1], sizeof(filepath[1]), "%s\\raw\\video\\%s.bik", cwd, filename);
    }
    if ( R_Cinematic_BinkOpenPath(filepath[0], playbackFlags, errText, errTextSize) )
    {
        return true;
    }
    if ( filepath[1][0] && R_Cinematic_BinkOpenPath(filepath[1], playbackFlags, errText, errTextSize) )
    {
        return true;
    }
    return false;
}
