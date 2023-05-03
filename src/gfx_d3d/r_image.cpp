#include "r_local.h"
#include "r_image.h"
#include "rb_backend.h"
#include "../common/sys_thread.h"
#include "../database/db_shared.h"


extern GfxImage *g_imageProgs[126];

bool Image_IsCodeImage(int track)
{
  //return header.image->track <= 4u && (1 << header.image->track) & 0x13;  //Mac OS

  return track >= 0 && (track <= 1 || track == 4);  //Windows
}

bool R_DuplicateTexture(GfxImage *dstImage, GfxImage *srcImage)
{
  if ( !srcImage || !srcImage->texture.basemap )
  {
    return 0;
  }
  dstImage->texture.basemap = srcImage->texture.basemap;
  D3DCALLNOLOCKNOERROR(dstImage->texture.basemap->AddRef( ));
  return 1;
}

bool Image_IsProg(GfxImage *image)
{
  return image >= (GfxImage *)g_imageProgs && image <= (GfxImage *)g_imageProgs + 126;
}

bool Image_AssignDefaultTexture(GfxImage *image)
{
  if ( image->mapType != 3 )
  {
    return 0;
  }
  if ( image->semantic == 5 )
  {
    return R_DuplicateTexture(image, rgp.identityNormalMapImage);
  }
  if ( image->semantic == 8 )
  {
    return R_DuplicateTexture(image, rgp.blackImage);
  }
  return R_DuplicateTexture(image, rgp.whiteImage);
}

void Image_Release(GfxImage *image)
{
  int platform;

  assert(image);

  if ( !Image_IsCodeImage(image->track) )
  {
    for ( platform = 0; platform < PICMIP_PLATFORM_COUNT; ++platform )
    {
      imageGlobals.totalMemory.platform[platform] -= image->cardMemory.platform[platform];
    }
  }
  if ( image->texture.basemap )
  {
    if ( Sys_IsRenderThread() )
    {
      D3DCALLNOLOCKNOERROR(image->texture.basemap->Release( ));
    }
    else
    {
      RB_Resource_Release((IUnknown *)&image->texture.basemap);
    }
    image->texture.basemap = 0;
    image->cardMemory.platform[PICMIP_PLATFORM_USED] = 0;
    image->cardMemory.platform[PICMIP_PLATFORM_MINSPEC] = 0;
  }
  else{
#ifndef NDEBUG
    if ( r_loadForRenderer->current.enabled )
    {
        assert(!image->cardMemory.platform[PICMIP_PLATFORM_USED]);
    }
#endif
  }
  //Image_TrackBytes -= image->loadedSize;
  //image->loadedSize = 0;
  image->mapType = MAPTYPE_NONE;
}

void Image_Rebuild(GfxImage *image)
{
  assert(image);
  assert(image->category != IMG_CATEGORY_UNKNOWN);

  assert(image->category >= IMG_CATEGORY_FIRST_UNMANAGED);
  assert(!image->texture.basemap);

  switch(image->category)
  {
    case IMG_CATEGORY_FIRST_UNMANAGED:
      Image_BuildWaterMap(image);
      break;
    case IMG_CATEGORY_NON_PROG:
      assertx(0, "non-prog image cannot be a render target");
      break;
    default:
      assertx(0, "unhandled case %i", image->category);
  }
}

void R_FreeLostImage(XAssetHeader header)
{
  GfxImage* image = header.image;
  assert(image);
  assert(image->category != IMG_CATEGORY_UNKNOWN);

  if ( image->category >= IMG_CATEGORY_FIRST_UNMANAGED )
  {
    Image_Release(image);
  }
}



void R_RebuildLostImage(XAssetHeader header, void* arg)
{
  GfxImage* image = header.image;

  assert(image);
  assert(image->category != IMG_CATEGORY_UNKNOWN);

  if ( !image->texture.basemap )
  {
    if ( image->category < IMG_CATEGORY_FIRST_UNMANAGED )
    {
      if ( image->category == 3 )
      {
#ifdef BLACKOPS
        if ( !image->delayLoadPixels && !Image_LoadFromFile(image, image->skippedMipLevels == 0) && !Image_AssignDefaultTexture(image) )
#else
        if ( !image->delayLoadPixels && !Image_LoadFromFile(image ) && !Image_AssignDefaultTexture(image) )
#endif
        {
          Com_Error(ERR_DROP, "Couldn't load image '%s' to recover from a lost device", image->name);
        }
      }
      else
      {
        Com_Error(ERR_DROP, "No way to recover image '%s' from a lost device", image->name);
      }
    }
    else if ( !Image_IsProg(image) && image->category == IMG_CATEGORY_FIRST_UNMANAGED)
    {
      Image_Rebuild(image);
    }
  }
}


void Image_Reload(GfxImage *image)
{
  assert(image);

  Image_Release(image);
#ifdef BLACKOPS
  if ( !Image_LoadFromFile(image, image->skippedMipLevels == 0) )
#else
  if ( !Image_LoadFromFile(image))
#endif
  {
    Com_Error(ERR_DROP, "failed to load image '%s'", image->name);
  }
}



void Image_CreateCubeTexture_PC(GfxImage *image, uint16_t edgeLen, int mipmapCount, D3DFORMAT imageFormat)
{
  assert(image);
  assert(image->texture.basemap  == NULL);

  image->width = edgeLen;
  image->height = edgeLen;
  image->depth = 1;
  image->mapType = MAPTYPE_CUBE;
  if ( !gfxMetrics.canMipCubemaps )
  {
    mipmapCount = 1;
  }

//  assert(Sys_IsRenderThread());

  D3DSEMSTART;

  D3DCALL(r_dx.device->CreateCubeTexture( edgeLen, mipmapCount, 0, imageFormat, D3DPOOL_MANAGED, &image->texture.cubemap, 0 ));

  D3DSEMEND;
}

unsigned int Image_GetUsage(int imageFlags, D3DFORMAT imageFormat)
{
  if ( imageFlags & 0x20000 )
  {
    if ( imageFormat != D3DFMT_D24S8 && imageFormat != D3DFMT_D24X8 && imageFormat != D3DFMT_D16 )
    {
      return D3DUSAGE_RENDERTARGET; //1
    }
    else
    {
      return D3DUSAGE_DEPTHSTENCIL; //2
    }
  }
  else if ( imageFlags & 0x10000 )
  {
    return D3DUSAGE_DYNAMIC; //0x200
  }
  return 0;

}

void Image_Create2DTexture_PC(GfxImage *image, uint16_t width, uint16_t height, int mipmapCount, int imageFlags, D3DFORMAT imageFormat)
{
  unsigned int usage;
  D3DPOOL memPool;

  assert(image);
  assert(image->texture.basemap == NULL);
  
  image->width = width;
  image->height = height;
  image->depth = 1;
  image->mapType = MAPTYPE_2D;
  usage = Image_GetUsage(imageFlags, imageFormat);
  if ( imageFlags & 0x40000 )
  {
    memPool = D3DPOOL_SYSTEMMEM;
  }
  else if(usage == 0)
  {
    memPool = D3DPOOL_MANAGED;
  }else{
    memPool = D3DPOOL_DEFAULT;
  }
#pragma msg "Disable maybe"
  if ( imageFlags & 0x100 )
  {
    memPool = D3DPOOL_SYSTEMMEM;
  }

//  assert(Sys_IsRenderThread());

  D3DSEMSTART;

  D3DCALL(r_dx.device->CreateTexture( width, height, mipmapCount, usage, imageFormat, memPool, &image->texture.map, 0 ));

  D3DSEMEND;
}

void Image_Create3DTexture_PC(GfxImage *image, uint16_t width, uint16_t height, uint16_t depth, int mipmapCount, int imageFlags, D3DFORMAT imageFormat)
{
  D3DPOOL memPool;

  assert(image);
  assert(image->texture.volmap == NULL);

  image->width = width;
  image->height = height;
  image->depth = depth;
  image->mapType = MAPTYPE_3D;
  unsigned int usage = Image_GetUsage(imageFlags, imageFormat);

  if ( imageFlags & 0x40000 )
  {
    memPool = D3DPOOL_SYSTEMMEM;
  }
  else if(usage == 0)
  {
    memPool = D3DPOOL_MANAGED;
  }else{
    memPool = D3DPOOL_DEFAULT;
  }

//  assert(Sys_IsRenderThread());

  D3DSEMSTART;

  D3DCALL(r_dx.device->CreateVolumeTexture( width, height, depth, mipmapCount, 0, imageFormat, memPool, &image->texture.volmap, 0 ));

  D3DSEMEND;

}



void Load_Texture(GfxImageLoadDef **remoteLoadDef, GfxImage *image)
{
  signed int mipWidth;
  signed int mipHeight;
  signed int mipDepth;
  GfxImageLoadDef *loadDef;
  int externalDataSize;
  signed int mipCount;
  const unsigned char *data;
  int faceCount;
  int faceIndex;
  D3DFORMAT imageFormat;
  int mipLevel;
  D3DCUBEMAP_FACES face;

  loadDef = *remoteLoadDef;
  assert(loadDef == image->texture.loadDef);

  image->texture.basemap = NULL;
  if ( !r_loadForRenderer || !r_loadForRenderer->current.enabled)
  {
    return;
  }
  imageFormat = loadDef->format;
  if ( loadDef->texture.basemap )
  {
    image->delayLoadPixels = 0;
    if ( image->mapType == MAPTYPE_2D )
    {
      Image_Create2DTexture_PC(image, loadDef->width, loadDef->height, loadDef->levelCount, 0, imageFormat);
      faceCount = 1;
    }
    else if ( image->mapType == MAPTYPE_3D )
    {
      Image_Create3DTexture_PC(image, loadDef->width, loadDef->height, loadDef->depth, loadDef->levelCount, 0, imageFormat);
      faceCount = 1;
    }
    else
    {
      assert(image->mapType == MAPTYPE_CUBE);
      Image_CreateCubeTexture_PC(image, loadDef->width, loadDef->levelCount, imageFormat);
      faceCount = 6;
    }
    data = loadDef->data;
    mipCount = Image_CountMipmaps(loadDef->flags, image->width, image->height, image->depth);
    for ( faceIndex = 0; faceIndex < faceCount; ++faceIndex )
    {
      if ( faceCount != 1 )
      {
        face = Image_CubemapFace(faceIndex);
      }else{
        face = D3DCUBEMAP_FACE_POSITIVE_X;
      }
      for ( mipLevel = 0; mipLevel < mipCount; ++mipLevel )
      {
#ifndef BLACKOPS
        Image_UploadData(image, imageFormat, face, mipLevel, data);
#endif
        if ( (signed int)(image->width >> mipLevel) > 1 )
        {
          mipWidth = (unsigned int)image->width >> mipLevel;
        }
        else
        {
          mipWidth = 1;
        }
        if ( (signed int)(image->height >> mipLevel) > 1 )
        {
          mipHeight = (unsigned int)image->height >> mipLevel;
        }
        else
        {
          mipHeight = 1;
        }
        if ( (signed int)(image->depth >> mipLevel) > 1 )
        {
          mipDepth = (unsigned int)image->depth >> mipLevel;
        }
        else
        {
          mipDepth = 1;
        }
        data += Image_GetCardMemoryAmountForMipLevel(imageFormat, mipWidth, mipHeight, mipDepth);
      }
    }
#ifdef BLACKOPS
    char *imageBuffer;

    imageBuffer = (char *)Z_VirtualAlloc(data - loadDef->data, "Image_AllocTempMemory", 20);
    memcpy(imageBuffer, loadDef->data, data - loadDef->data);
    RB_Resource_CreateTexture(image, imageBuffer, mipCount, 0, imageFormat);
    assert(data == &loadDef->data[loadDef->resourceSize]);
#endif
  }
  else if ( image->category == IMG_CATEGORY_FIRST_UNMANAGED )
  {
    unsigned int width, height;
    image->delayLoadPixels = 0;

    if ( image->width >> (unsigned int)r_picmip_water->current.integer < 4 )
    {
      width = 4;
    }
    else
    {
      width = image->width >> (unsigned int)r_picmip_water->current.integer;
    }

    if ( image->height >> (unsigned int)r_picmip_water->current.integer < 4 )
    {
      height = 4;
    }
    else
    {
      height = image->height >> (unsigned int)r_picmip_water->current.integer;
    }

    image->cardMemory.platform[PICMIP_PLATFORM_USED] = 0;
    image->cardMemory.platform[PICMIP_PLATFORM_MINSPEC] = 0;

    Image_Create2DTexture_PC(image, width, height, loadDef->levelCount, 0x10000, imageFormat);
  }
  else
  {
//    assertx((unsigned int)( image->cardMemory.platform[PICMIP_PLATFORM_USED] ) == Image_GetCardMemoryAmount( loadDef->flags, (GfxPixelFormat)( loadDef->format ), image->width, image->height, image->depth ), "(image->name) = %s", image->name);
    assertx(image->texture.basemap == NULL, "(image->name) = %s", image->name);

    //image->delayLoadPixels = 0;
    if ( !image->delayLoadPixels )
    {
      externalDataSize = image->cardMemory.platform[PICMIP_PLATFORM_USED];
      image->cardMemory.platform[PICMIP_PLATFORM_USED] = 0;
      image->cardMemory.platform[PICMIP_PLATFORM_MINSPEC] = 0;
      if ( !Image_LoadFromFile( image ) )
      {
        Com_Error(ERR_DROP, "Couldn't load image '%s'\n", image->name);
      }
      DB_LoadedExternalData(externalDataSize);
    }
  }

}

D3DSurface *Image_GetSurface(GfxImage *image)
{
  D3DSurface *surface; 

  assert(image);
  assert(image->mapType == MAPTYPE_2D);
  assert(image->texture.map);

  D3DCALL(image->texture.map->GetSurfaceLevel( 0, &surface ));

  return surface;
}

void R_DelayLoadImage(XAssetHeader header, void* arg)
{
  GfxImage* image = header.image;
  int externalDataSize;

  if ( image->delayLoadPixels )
  {
    image->delayLoadPixels = 0;
    externalDataSize = image->cardMemory.platform[PICMIP_PLATFORM_USED];
    image->cardMemory.platform[PICMIP_PLATFORM_USED] = 0;
    image->cardMemory.platform[PICMIP_PLATFORM_MINSPEC] = 0;

    if ( r_loadForRenderer->current.enabled && !r_dx.deviceLost )
    {
      if ( !Image_LoadFromFile(header.image ) )
      {
        Image_AssignDefaultTexture(header.image);
      }
      if ( !image->texture.basemap )
      {
        HRESULT hr = D3DCALLNOLOCKNOERROR(r_dx.device->TestCooperativeLevel( ));
        if ( hr != D3DERR_DEVICELOST && hr != D3DERR_DEVICENOTRESET )
        {
          Com_Error(ERR_FATAL, "Couldn't load image '%s', D3DError: %s\n", image->name, R_ErrorDescription(hr));
        }
      }
    }
    DB_LoadedExternalData(externalDataSize);
  }
}


void Image_Free(GfxImage *image)
{
  Image_Release(image);
}

unsigned int Image_GetAvailableHashLocation(const char *name)
{
  unsigned int stuck;
  unsigned int hashIndex;

  hashIndex = R_HashAssetName(name) & MAX_IMAGES_MASK;
  
  for(stuck = 0 ; stuck < MAX_IMAGES ; ++stuck)
  {
    if ( !imageGlobals.imageHashTable[hashIndex] )
    {
      break;
    }
    hashIndex = (hashIndex + 1) & MAX_IMAGES_MASK;
  }
  return hashIndex;
}

void R_ShutdownImages()
{
  GfxImage *image;
  int imagecount;
  unsigned int i;
  GfxImage *imagelist[MAX_IMAGES];
  int j;

  RB_UnbindAllImages();
  imagecount = 0;
  for ( i = 0; i < ARRAY_COUNT(imageGlobals.imageHashTable); ++i )
  {
    image = imageGlobals.imageHashTable[i];
    if ( image )
    {
      if ( Image_IsProg(image) )
      {
        imagelist[imagecount++] = image;
      }
      else
      {
        Image_Free(imageGlobals.imageHashTable[i]);
      }
    }
  }
  memset(&imageGlobals.imageHashTable, 0, sizeof(imageGlobals.imageHashTable));
  for ( j = 0; j < imagecount; ++j )
  {
    imageGlobals.imageHashTable[Image_GetAvailableHashLocation(image->name)] = imagelist[j];
  }
}


void Image_UpdatePicmip(GfxImage* image)
{
  Picmip picmip;

  assert(image);
  if(image->category != 3 || image->noPicmip)
  {
    return;
  }
  Image_GetPicmip(image, &picmip);
  if( picmip.platform[PICMIP_PLATFORM_USED] != image->picmip.platform[PICMIP_PLATFORM_USED] )
  {
    Image_Reload(image);
  }
}


void R_ImageList_f()
{
  Com_Printf(CON_CHANNEL_GFX, "Not implemented\n");
}


void Image_SetupRenderTarget(GfxImage *image, uint16_t width, uint16_t height, D3DFORMAT imageFormat, const char *rendertargetname, unsigned int allocFlags)
{
  assert(image);
  assert(image->semantic == TS_2D);

  if ( !_stricmp(image->name, "$16bit_system") || !_stricmp(image->name, "$8bit_system") )
  {
    Image_SetupAndLoad(image, width, height, 1, 259, imageFormat, rendertargetname);
  }
  else
  {
    Image_SetupAndLoad(image, width, height, 1, 131075, imageFormat, rendertargetname);
  }
}

void Image_LoadFromData(GfxImage *image, GfxImageFileHeader *fileHeader, unsigned char *srcData, unsigned int allocFlags)
{
/*
  image->loadedSize = fileHeader->fileSizeForPicmip[(unsigned __int8)image->skippedMipLevels] - 48;
  image->baseSize = fileHeader->fileSizeForPicmip[0] - 48;
  Image_TrackBytes += image->loadedSize;
*/
  image->texture.basemap = 0;
  switch ( fileHeader->format )
  {
    case 1:
      Image_LoadBitmap(image, fileHeader, srcData, D3DFMT_A8R8G8B8, 4);
      break;
    case 2:
      Image_LoadBitmap(image, fileHeader, srcData, D3DFMT_X8R8G8B8, 3);
      break;
    case 3:
      Image_LoadBitmap(image, fileHeader, srcData, D3DFMT_A8L8, 2);
      break;
    case 4:
      Image_LoadBitmap(image, fileHeader, srcData, D3DFMT_L8, 1);
      break;
    case 5:
      Image_LoadBitmap(image, fileHeader, srcData, D3DFMT_A8, 1);
      break;
    case 6:
      Image_LoadWavelet(image, fileHeader, srcData, D3DFMT_A8R8G8B8, 4);
      break;
    case 7:
      Image_LoadWavelet(image, fileHeader, srcData, D3DFMT_X8R8G8B8, 3);
      break;
    case 8:
      Image_LoadWavelet(image, fileHeader, srcData, D3DFMT_A8L8, 2);
      break;
    case 9:
      Image_LoadWavelet(image, fileHeader, srcData, D3DFMT_L8, 1);
      break;
    case 0xA:
      Image_LoadWavelet(image, fileHeader, srcData, D3DFMT_A8, 1);
      break;
    case 0xB:
      Image_LoadDxtc(image, fileHeader, srcData, D3DFMT_DXT1, 8);
      break;
    case 0xC:
      Image_LoadDxtc(image, fileHeader, srcData, D3DFMT_DXT3, 16);
      break;
    case 0xD:
      Image_LoadDxtc(image, fileHeader, srcData, D3DFMT_DXT5, 16);
      break;
    case 0x13:
      Image_LoadDxtc(image, fileHeader, srcData, D3DFMT_A16B16G16R16F, 128);
      break;
    default:
      assertx(0, "unhandled case: %d", (uint8_t)fileHeader->format);
      break;
  }
}
