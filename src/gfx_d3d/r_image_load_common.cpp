#include "r_local.h"
#include "r_image.h"

int Image_SourceBytesPerSlice_PC(D3DFORMAT format, int width, int height)
{
    switch ( format )
    {
        case D3DFMT_D24S8:
        case D3DFMT_A8R8G8B8:
        case D3DFMT_R32F:
            return 4 * height * width;
        case D3DFMT_X8R8G8B8:
            return 3 * height * width;
        case D3DFMT_R5G6B5:
        case D3DFMT_A8L8:
        case D3DFMT_D16:
            return 2 * height * width;
        case D3DFMT_A8:
        case D3DFMT_L8:
            return height * width;
        case D3DFMT_DXT1:
            return 8 * ((height + 3) >> 2) * ((width + 3) >> 2);  
        case D3DFMT_DXT3:
        case D3DFMT_DXT5:
            return 16 * ((height + 3) >> 2) * ((width + 3) >> 2);
        default:
            assertx(0, "unhandled case: %d", format);
            return 0;
    }
}

void Image_Upload2D_CopyDataBlock_PC(int width, int height, const unsigned char *src, D3DFORMAT format, int dstPitch, char *dst)
{
    signed int srcStride;
    int y;
    int dy;

    assert(src);
    assert(dst);

    switch ( format )
    {
        case D3DFMT_DXT3:
        case D3DFMT_DXT5:
            srcStride = 16 * ((width + 3) >> 2);
            dy = 4;
            break;
        case D3DFMT_DXT1:
            srcStride = 8 * ((width + 3) >> 2);
            dy = 4;
            break;
        case D3DFMT_A8R8G8B8:
        case D3DFMT_X8R8G8B8:
        case D3DFMT_A8B8G8R8:
        case D3DFMT_G16R16:
            srcStride = 4 * width;
            dy = 1;
        break;
        case D3DFMT_R5G6B5:
        case D3DFMT_A8L8:
            srcStride = 2 * width;
            dy = 1;
        break;
        case D3DFMT_A8:
        case D3DFMT_L8:
            srcStride = width;
            dy = 1;
        break;
        case D3DFMT_A16B16G16R16:
        case D3DFMT_A16B16G16R16F:
            srcStride = 4 * width;
            dy = 1;
        break;
        case D3DFMT_R32F:
            srcStride = 4 * width;
            dy = 1;
        break;
        default:
            assertx(0, "unhandled case: %d", format);
            return;
    }
    assertx(dstPitch >= srcStride, "%i x %i: %i < %i", width, height, dstPitch, srcStride);
    if ( dstPitch == srcStride )
    {
      memcpy(dst, (char *)src, srcStride * ((height - 1) / dy + 1));
    }
    else
    {
      for ( y = 0; y < height; y += dy )
      {
        memcpy(dst, (char *)src, srcStride);
        dst += dstPitch;
        src += srcStride;
      }
    }
}

void Image_Upload3D_CopyData_PC(const GfxImage *image, _D3DFORMAT format, unsigned int mipLevel, const unsigned char *src)
{
  int depth;
  int srcRowPitch;
  int sliceIndex;
  D3DLOCKED_BOX lockedBox;
  int width;
  int height;
  char *dst;

    assert(image);
    assert(image->mapType == MAPTYPE_3D);

  if ( image->width >> mipLevel > 1 )
  {
    width = image->width >> mipLevel;
  }
  else
  {
    width = 1;
  }
  if ( image->height >> mipLevel > 1 )
  {
    height = image->height >> mipLevel;
  }
  else
  {
    height = 1;
  }
  if ( image->depth >> mipLevel > 1 )
  {
    depth = image->depth >> mipLevel;
  }
  else
  {
    depth = 1;
  }
  srcRowPitch = Image_SourceBytesPerSlice_PC(format, width, height);
  assert(image->texture.volmap);

    D3DCALL(image->texture.volmap->LockBox( mipLevel, &lockedBox, 0, 0 ));

  dst = (char *)lockedBox.pBits;
  for ( sliceIndex = 0; sliceIndex < depth; ++sliceIndex )
  {
    Image_Upload2D_CopyDataBlock_PC(width, height, src, format, lockedBox.RowPitch, dst);
    src += srcRowPitch;
    dst += lockedBox.SlicePitch;
  }

    D3DCALLNOLOCKNOERROR(image->texture.volmap->UnlockBox( mipLevel ));
}




void Image_Upload2D_CopyData_PC(const GfxImage *image, D3DFORMAT format, D3DCUBEMAP_FACES face, unsigned int mipLevel, const unsigned char *src)
{
  D3DLOCKED_RECT lockedRect;
  unsigned int width;
  unsigned int height;

  if ( image->width >> mipLevel > 1 )
  {
    width = image->width >> mipLevel;
  }
  else
  {
    width = 1;
  }
  if ( image->height >> mipLevel > 1 )
  {
    height = image->height >> mipLevel;
  }
  else
  {
    height = 1;
  }
  if ( image->mapType == MAPTYPE_2D )
  {
    assert(image->texture.map);

    D3DCALL(image->texture.map->LockRect( mipLevel, &lockedRect, 0, 0 ));
    Image_Upload2D_CopyDataBlock_PC(width, height, src, format, lockedRect.Pitch, (char *)lockedRect.pBits);
    D3DCALL(image->texture.map->UnlockRect( mipLevel ));
  }
  else
  {
    assert(image->mapType == MAPTYPE_CUBE);
    assertx(face == D3DCUBEMAP_FACE_POSITIVE_X || face == D3DCUBEMAP_FACE_NEGATIVE_X || face == D3DCUBEMAP_FACE_POSITIVE_Y || face == D3DCUBEMAP_FACE_NEGATIVE_Y || face == D3DCUBEMAP_FACE_POSITIVE_Z || face == D3DCUBEMAP_FACE_NEGATIVE_Z, "(face) = %i", face);
    assert(image->texture.cubemap);

    D3DCALL(image->texture.cubemap->LockRect( face, mipLevel, &lockedRect, 0, 0 ));

    Image_Upload2D_CopyDataBlock_PC(width, height, src, format, lockedRect.Pitch, (char *)lockedRect.pBits);
    
    D3DCALL(image->texture.cubemap->UnlockRect( face, mipLevel ));
  }
}


void Image_UploadData(const GfxImage *image, D3DFORMAT format, D3DCUBEMAP_FACES face, unsigned int mipLevel, const unsigned char *src)
{
  if ( image->mapType != MAPTYPE_CUBE || !mipLevel || gfxMetrics.canMipCubemaps )
  {
    D3DSEMSTART;
    if ( image->mapType == MAPTYPE_3D )
    {
      Image_Upload3D_CopyData_PC(image, format, mipLevel, src);
    }
    else
    {
      Image_Upload2D_CopyData_PC(image, format, face, mipLevel, src);
    }
    D3DSEMEND;
  }
}

D3DCUBEMAP_FACES Image_CubemapFace(unsigned int faceIndex)
{
  assertx(faceIndex < 6, "(faceIndex) = %i", faceIndex);
  return (D3DCUBEMAP_FACES)faceIndex;
}



unsigned int Image_CountMipmaps(unsigned int imageFlags, unsigned int width, unsigned int height, unsigned int depth)
{
  unsigned int mipRes;
  unsigned int mipCount;

  if ( imageFlags & 2 )
  {
    return 1;
  }
  mipCount = 1;
  mipRes = 1;
  while ( mipRes < width || mipRes < height || mipRes < depth )
  {
    mipRes *= 2;
    ++mipCount;
  }
  return mipCount;
}


unsigned int Image_GetCardMemoryAmountForMipLevel(D3DFORMAT format, unsigned int mipWidth, unsigned int mipHeight, unsigned int mipDepth)
{
  switch ( format )
  {
    case D3DFMT_DXT3:
    case D3DFMT_DXT5:
      return 16 * mipDepth * ((mipHeight + 3) >> 2) * ((mipWidth + 3) >> 2);
    case D3DFMT_DXT1:
      return 8 * mipDepth * ((mipHeight + 3) >> 2) * ((mipWidth + 3) >> 2);
    case D3DFMT_A8R8G8B8:
    case D3DFMT_X8R8G8B8:
    case D3DFMT_G16R16:
    case D3DFMT_D24S8:
    case D3DFMT_G16R16F:
    case D3DFMT_R32F:
      return 4 * mipDepth * mipHeight * mipWidth;

    case D3DFMT_R5G6B5:
    case D3DFMT_A8L8:
    case D3DFMT_D16:
      return 2 * mipDepth * mipHeight * mipWidth;

    case D3DFMT_A8:
    case D3DFMT_L8:
      return mipDepth * mipHeight * mipWidth;

    case D3DFMT_A8B8G8R8:
      return 4 * mipDepth * mipHeight * mipWidth;

    case D3DFMT_A16B16G16R16:
    case D3DFMT_A16B16G16R16F:
      return 8 * mipDepth * mipHeight * mipWidth;
    default:
      assertx(0, "unhandled case: %d", format);
      return 0;
  }
}


void Image_GetPicmip(const GfxImage *image, Picmip *picmip)
{
  assert(image);
  assert(picmip);

  if ( image->noPicmip )
  {
    picmip->platform[PICMIP_PLATFORM_USED] = 0;
    picmip->platform[PICMIP_PLATFORM_MINSPEC] = 0;
  }
  else
  {
    Image_PicmipForSemantic(image->semantic, picmip);
  }
}