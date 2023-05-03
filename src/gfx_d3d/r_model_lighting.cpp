#include "r_types_d3d.h"
#include "r_local.h"
#include "r_image.h"
#include "rb_backend.h"

extern int s_modelLightingSampleDelta[64];


struct XModelId
{
  unsigned int baseIndex;
};

struct GfxModelLightingGlob
{
  float invImageHeight;
  XModelId xmodel;
  unsigned int totalEntryLimit;
  unsigned int entryBitsY;
  unsigned int imageHeight;
  GfxEntity *entities;
  unsigned int modFrameCount;
  GfxImage *image;
  GfxImage *altlightimage;
  GfxImage *unknownImage;
  unsigned int xmodelEntryLimit;
  struct GfxLightingInfo *lightingInfo;
  float (*lightingOrigins)[3];
  int allocModelFail;
  unsigned int *pixelFreeBits[4];
  unsigned int *prevPrevPixelFreeBits;
  unsigned int *prevPixelFreeBits;
  unsigned int *currPixelFreeBits;
  unsigned int pixelFreeBitsSize;
  unsigned int pixelFreeBitsWordCount;
  unsigned int pixelFreeRover;
  D3DLOCKED_BOX lockedBox;
  int a;
  int b;
};

extern GfxModelLightingGlob modelLightGlob;


void R_SetModelLightingSampleDeltas()
{
  unsigned int i;
  unsigned int sampleIndex;
  unsigned int dz;
  unsigned int dy;

  sampleIndex = 0;
  for ( dz = 0; dz < 4; ++dz )
  {
    for ( dy = 0; dy < 4; ++dy )
    {
      for ( i = 0; i < 4; ++i )
      {
        s_modelLightingSampleDelta[sampleIndex++] = modelLightGlob.lockedBox.SlicePitch * dz + modelLightGlob.lockedBox.RowPitch * dy + 4 * i;
      }
    }
  }
}



void RB_PatchModelLighting(GfxModelLightingPatch *patchList, unsigned int patchCount)
{
    unsigned char *pixels;
    unsigned int sampleIndex;
    unsigned int patchIter;
    GfxModelLightingPatch *patch;
    GfxImage* image;
    int flags;
    D3DBOX box;

    if ( !patchCount )
    {
        return;
    }
    assert(modelLightGlob.lockedBox.pBits == NULL);
    
    bool useAltModelLightingUpdate = Dvar_GetBool("r_altModelLightingUpdate");

    if ( useAltModelLightingUpdate )
    {
      image = modelLightGlob.altlightimage;
      memset(&box, 0, sizeof(box));
      box.Back = 4;
      flags = D3DLOCK_NO_DIRTY_UPDATE;
    }else{
      image = modelLightGlob.image;
      flags = 0;
    }

    D3DCALL(image->texture.volmap->LockBox(0, &modelLightGlob.lockedBox, 0, flags));

    R_SetModelLightingSampleDeltas();
    R_SetLightGridSampleDeltas(modelLightGlob.lockedBox.RowPitch, modelLightGlob.lockedBox.SlicePitch);

    for ( patchIter = 0; patchIter < patchCount; ++patchIter )
    {
      patch = &patchList[patchIter];
      unsigned int x = 4 * (patch->modelLightingIndex & 0x3F);
      unsigned int y = ((unsigned int)patch->modelLightingIndex >> 4) & 0xFFFFFFC;
      
      if ( useAltModelLightingUpdate )
      {
        box.Bottom = y + 4;
        box.Left = x;
        box.Right = x + 4;
        box.Top = y;
        D3DCALL(image->texture.volmap->AddDirtyBox( &box ));
      }

      pixels = (unsigned char *)modelLightGlob.lockedBox.pBits + 4 * x + modelLightGlob.lockedBox.RowPitch * y;

      if ( patch->colorsCount )
      {
        R_ApplyLightGridColorsPatch(patch, pixels);
      }
      else
      {
        for ( sampleIndex = 0; sampleIndex < ARRAY_COUNT(s_modelLightingSampleDelta); ++sampleIndex )
        {
          *(DWORD *)&pixels[s_modelLightingSampleDelta[sampleIndex]] = *(DWORD *)patch->groundLighting;
        }
      }
    }
    
    assert(modelLightGlob.lockedBox.pBits);
    
    D3DCALL(image->texture.volmap->UnlockBox(0));
    modelLightGlob.lockedBox.pBits = 0;    
    
    if ( useAltModelLightingUpdate )
    {
      assert(image->texture.basemap != NULL);
      assert(modelLightGlob.image->texture.basemap != NULL);
      D3DCALL(r_dx.device->UpdateTexture(image->texture.basemap, modelLightGlob.image->texture.basemap));
    }

}


void R_InitModelLightingImage()
{
  assert(modelLightGlob.totalEntryLimit > 0);

  modelLightGlob.image = Image_AllocProg(12, 4, 1);
  
  bool useAltModelLightingUpdate = Dvar_GetBool("r_altModelLightingUpdate");
  
  if(useAltModelLightingUpdate)
  {
    Image_SetupAndLoad(modelLightGlob.image, 256, modelLightGlob.imageHeight, 4, 0x1000A, D3DFMT_A8R8G8B8, "<model lighting>");

    modelLightGlob.altlightimage = Image_AllocProg(13, 4, 1);
    Image_SetupAndLoad(modelLightGlob.altlightimage, 256, modelLightGlob.imageHeight, 4, 0x4000A, D3DFMT_A8R8G8B8, "<model alternative lighting>");
  }else{
    Image_SetupAndLoad(modelLightGlob.image, 256, modelLightGlob.imageHeight, 4, 10, D3DFMT_A8R8G8B8, "<model lighting>");
    modelLightGlob.altlightimage = NULL;
  }
  modelLightGlob.unknownImage = modelLightGlob.image;

}