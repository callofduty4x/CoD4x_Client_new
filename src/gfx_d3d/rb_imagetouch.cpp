#include "r_local.h"
#include "r_image.h"
#include "r_state.h"
#include "rb_backend.h"


int RB_CompareTouchImages(const void *e0, const void *e1)
{
  GfxImage *im0, *im1;

  im0 = *(GfxImage **)e0;
  im1 = *(GfxImage **)e1;
  if ( !im1->semantic )
  {
    return -1;
  }
  if ( !im0->semantic )
  {
    return 1;
  }
  if ( im1->cardMemory.platform[0] == im0->cardMemory.platform[0] )
  {
    return im0->semantic - im1->semantic;
  }
  return im1->cardMemory.platform[0] - im0->cardMemory.platform[0];
}


void RB_TouchImage(GfxImage *image)
{
  if ( image->mapType == MAPTYPE_2D )
  {
    R_SetCodeImageTexture(&gfxCmdBufSourceState, 9u, image);
    R_Set2D(&gfxCmdBufSourceState);
    RB_DrawStretchPic(rgp.feedbackReplaceMaterial, 0.0, 0.0, 8.0, 8.0, 0.0, 0.0, 1.0, 1.0, 0xFFFFFFFF, GFX_PRIM_STATS_CODE);
    RB_EndTessSurface();
  }
}


void RB_TouchAllImages()
{
  bool inScene;
  unsigned int i;
  ImageList imageList;


  D3DSEMSTART;

  inScene = r_dx.inScene;
  if ( !inScene )
  {
      D3DCALL(r_dx.device->BeginScene());
  }
  if ( tess.indexCount )
  {
    RB_EndTessSurface();
  }

  R_GetImageList(&imageList);
  qsort(imageList.image, imageList.count, sizeof(imageList.image[0]), RB_CompareTouchImages);
//  int imagespace = 0;
  for ( i = 0; i < imageList.count && imageList.image[i]->semantic; ++i )
  {
    RB_TouchImage(imageList.image[i]);
//    imagespace += imageList.image[i]->cardMemory.platform[PICMIP_PLATFORM_USED];
  }
  R_SetCodeImageTexture(&gfxCmdBufSourceState, 9u, NULL);
  if ( !inScene )
  {
      D3DCALL(r_dx.device->EndScene());
  }

  D3DSEMEND;
}
