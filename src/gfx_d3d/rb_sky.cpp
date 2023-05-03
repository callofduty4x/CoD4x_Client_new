#include "rb_backend.h"
#include "r_local.h"
#include "gfx_world.h"
#include "r_state.h"
#include "../common/cm_public.h"
#include "../common/qcommon.h"

struct SunFlareDynamic
{
  float flareIntensity;
  float currentBlind;
  float currentGlare;
  int lastTime;
  float lastVisibility;
  float lastDot;
  char error;
  char sunQueryIssued[2];
  char pad;
  D3DQuery *sunQuery[2];
  int hitNum;
};

extern SunFlareDynamic sunFlareArray[6];

GfxVertex* RB_SetTessQuad(GfxColor color)
{
  uint16_t vertexCount;
  GfxVertex *vert;

  assert(tess.vertexCount == 0);
  assert(tess.indexCount == 0);

  vertexCount = tess.vertexCount;
  tess.indices[tess.indexCount] = vertexCount + 3;
  tess.indices[tess.indexCount + 1] = vertexCount;
  tess.indices[tess.indexCount + 2] = vertexCount + 2;
  tess.indices[tess.indexCount + 3] = vertexCount + 2;
  tess.indices[tess.indexCount + 4] = vertexCount;
  tess.indices[tess.indexCount + 5] = vertexCount + 1;
  vert = &tess.verts[vertexCount];
  vert->normal.packed = 0x3FFE7F7F;
  vert->texCoord[0] = 0.0;
  vert->texCoord[1] = 0.0;
  vert->color = color;
  vert[1].normal.packed = 0x3FFE7F7F;
  vert[1].texCoord[0] = 1.0;
  vert[1].texCoord[1] = 0.0;
  vert[1].color = color;
  vert[2].normal.packed = 0x3FFE7F7F;
  vert[2].texCoord[0] = 1.0;
  vert[2].texCoord[1] = 1.0;
  vert[2].color = color;
  vert[3].normal.packed = 0x3FFE7F7F;
  vert[3].texCoord[0] = 0.0;
  vert[3].texCoord[1] = 1.0;
  vert[3].color = color;
  tess.vertexCount += 4;
  tess.indexCount += 6;
  return vert;
}

void RB_TessSunBillboard(float widthInClipSpace, float heightInClipSpace, GfxColor color)
{
  vec4_t sunTransformedPosition;
  GfxVertex *vert;
  GfxMatrix *transform;

  transform = &gfxCmdBufSourceState.viewParms3D->viewProjectionMatrix;
  
  assert(rgp.world);

  sunTransformedPosition[0] = rgp.world->sun.sunFxPosition[0] * transform->m[0][0] + rgp.world->sun.sunFxPosition[1] * transform->m[1][0] + rgp.world->sun.sunFxPosition[2] * transform->m[2][0];
  sunTransformedPosition[1] = rgp.world->sun.sunFxPosition[0] * transform->m[0][1] + rgp.world->sun.sunFxPosition[1] * transform->m[1][1] + rgp.world->sun.sunFxPosition[2] * transform->m[2][1];
  sunTransformedPosition[2] = rgp.world->sun.sunFxPosition[0] * transform->m[0][2] + rgp.world->sun.sunFxPosition[1] * transform->m[1][2] + rgp.world->sun.sunFxPosition[2] * transform->m[2][2];
  sunTransformedPosition[3] = rgp.world->sun.sunFxPosition[0] * transform->m[0][3] + rgp.world->sun.sunFxPosition[1] * transform->m[1][3] + rgp.world->sun.sunFxPosition[2] * transform->m[2][3];
  
  vert = RB_SetTessQuad(color);
  Vector4Copy(sunTransformedPosition, vert[0].xyzw);
  Vector4Copy(sunTransformedPosition, vert[1].xyzw);
  Vector4Copy(sunTransformedPosition, vert[2].xyzw);
  Vector4Copy(sunTransformedPosition, vert[3].xyzw);

  vert->xyzw[0] = vert->xyzw[0] + (widthInClipSpace * sunTransformedPosition[3]);
  vert->xyzw[1] = vert->xyzw[1] + (heightInClipSpace * sunTransformedPosition[3]);
  vert->xyzw[2] = vert->xyzw[2] + (-0.0005 * sunTransformedPosition[3]);
  vert[1].xyzw[0] = vert[1].xyzw[0] + (widthInClipSpace * sunTransformedPosition[3]);
  vert[1].xyzw[1] = vert[1].xyzw[1] - (heightInClipSpace * sunTransformedPosition[3]);
  vert[1].xyzw[2] = vert[1].xyzw[2] + (-0.0005 * sunTransformedPosition[3]);
  vert[2].xyzw[0] = vert[2].xyzw[0] - (widthInClipSpace * sunTransformedPosition[3]);
  vert[2].xyzw[1] = vert[2].xyzw[1] - (heightInClipSpace * sunTransformedPosition[3]);
  vert[2].xyzw[2] = vert[2].xyzw[2] + (-0.0005 * sunTransformedPosition[3]);
  vert[3].xyzw[0] = vert[3].xyzw[0] - (widthInClipSpace * sunTransformedPosition[3]);
  vert[3].xyzw[1] = vert[3].xyzw[1] + (heightInClipSpace * sunTransformedPosition[3]);
  vert[3].xyzw[2] = vert[3].xyzw[2] + (-0.0005 * sunTransformedPosition[3]);
}


void RB_AllocSunSpriteQueries()
{
  unsigned int viewIndex;
  unsigned int queryIndex;

  for ( viewIndex = 0; viewIndex < gfxCfg.maxClientViews; ++viewIndex )
  {
    for ( queryIndex = 0; queryIndex < ARRAY_COUNT(sunFlareArray[0].sunQuery); ++queryIndex )
    {
      sunFlareArray[viewIndex].sunQuery[queryIndex] = RB_HW_AllocOcclusionQuery();
      sunFlareArray[viewIndex].sunQueryIssued[queryIndex] = 0;
    }
  }
}

unsigned int RB_CalcSunSpriteSamples()
{
  D3DQuery *occlusionQuery;
  HRESULT hr;
  unsigned int sampleCount;

  assert(vidConfig.displayWidth >= 16);
  assert(vidConfig.displayHeight >= 16);

  occlusionQuery = sunFlareArray[0].sunQuery[0];
  if ( !sunFlareArray[0].sunQuery[0] )
  {
    return 0;
  }
  RB_ResetStatTracking(0);
  if ( tess.indexCount )
  {
    RB_EndTessSurface();
  }

  D3DCALL(r_dx.device->BeginScene());

  R_ClearScreenInternal(gfxCmdBufState.prim.device, 2, colorWhite, 1.0, 0, 0);
  R_SetCodeConstantFromVec4(&gfxCmdBufSourceState, CONST_SRC_CODE_MATERIAL_COLOR, colorWhite);

  D3DCALL(occlusionQuery->Issue( (1 << 1) ));

  R_Set2D(&gfxCmdBufSourceState);

  assert(rgp.additiveMaterial);

  RB_DrawStretchPic(rgp.additiveMaterial, 0.0, 0.0, 16.0, 16.0, 0.0, 0.0, 1.0, 1.0, 0xFFFFFFFF, GFX_PRIM_STATS_CODE);

  assert(gfxCmdBufSourceState.viewMode == VIEW_MODE_2D);

  RB_EndTessSurface();

  D3DCALL(occlusionQuery->Issue( (1 << 0) ));

  D3DCALL(r_dx.device->EndScene());

  while ( 1 )
  {
    hr = D3DCALLNOLOCKNOERROR(occlusionQuery->GetData(&sampleCount, 4, 1));
    if ( hr != 1 )
    {
      break;
    }
    Sys_Sleep(0);
  }
  if ( hr )
  {
    sampleCount = 256;
  }
  return sampleCount;
}


void RB_FreeSunSpriteQueries()
{
  unsigned int viewIndex;
  unsigned int queryIndex;

  for ( viewIndex = 0; viewIndex < 4; ++viewIndex )
  {
    for ( queryIndex = 0; queryIndex < 2; ++queryIndex )
    {
      if ( sunFlareArray[viewIndex].sunQuery[queryIndex] )
      {
        D3DRELEASEBUFFER(sunFlareArray[viewIndex].sunQuery[queryIndex]);
      }
    }
  }
}


double RB_GetSunSampleRectRelativeArea(int widthInPixels, int heightInPixels)
{
  GfxMatrix *transform;
  int top;
  int right;
  int left;
  float sunTransformedPosition_12;
  int bottom;

  transform = &gfxCmdBufSourceState.viewParms3D->viewProjectionMatrix;

  assert(rgp.world);

  sunTransformedPosition_12 = rgp.world->sun.sunFxPosition[0] * transform->m[0][3] + rgp.world->sun.sunFxPosition[1] * transform->m[1][3] + 
                                rgp.world->sun.sunFxPosition[2] * transform->m[2][3];
  if ( sunTransformedPosition_12 <= 0.0 )
  {
    return 0.0;
  }

  float oldWidth = (float)vidConfig.displayWidth;
  float oldHeight = (float)vidConfig.displayHeight;

  float sunTransformedPosition_l = rgp.world->sun.sunFxPosition[0] * transform->m[0][0] + rgp.world->sun.sunFxPosition[1] * transform->m[1][0] + 
      rgp.world->sun.sunFxPosition[2] * transform->m[2][0];

  left = (signed int)((((((sunTransformedPosition_l / sunTransformedPosition_12) + 1.0) * oldWidth) - widthInPixels) * 0.5) + 0.5);

  float sunTransformedPosition_t = rgp.world->sun.sunFxPosition[0] * transform->m[0][1] + rgp.world->sun.sunFxPosition[1] * transform->m[1][1] + 
          rgp.world->sun.sunFxPosition[2] * transform->m[2][1];

  top = (signed int)((((((sunTransformedPosition_t / sunTransformedPosition_12) + 1.0) * oldHeight) - heightInPixels) * 0.5) + 0.5);

  right = widthInPixels + left;
  bottom = heightInPixels + top;
  if ( left < 0 )
  {
    left = 0;
  }
  if ( right > oldWidth )
  {
    right = oldWidth;
  }
  if ( top < 0 )
  {
    top = 0;
  }
  if ( bottom > oldHeight )
  {
    bottom = oldHeight;
  }
  if ( right > left && bottom > top )
  {
    return (double)((bottom - top) * (right - left)) / (double)(heightInPixels * widthInPixels);
  }
  return 0.0;
}

void RB_UpdateSunVisibilityWithoutQuery(SunFlareDynamic *sunFlare)
{
  vec3_t sunTraceEnd;

  assert(sunFlare);

  sunFlare->lastVisibility = RB_GetSunSampleRectRelativeArea(16, 16);
  if ( sunFlare->lastVisibility != 0.0 )
  {
    sunTraceEnd[0] = 262144.0 * rgp.world->sun.sunFxPosition[0] + gfxCmdBufSourceState.viewParms3D->origin[0];
    sunTraceEnd[1] = 262144.0 * rgp.world->sun.sunFxPosition[1] + gfxCmdBufSourceState.viewParms3D->origin[1];
    sunTraceEnd[2] = 262144.0 * rgp.world->sun.sunFxPosition[2] + gfxCmdBufSourceState.viewParms3D->origin[2];
    sunFlare->hitNum = CM_BoxSightTrace(sunFlare->hitNum, gfxCmdBufSourceState.viewParms3D->origin, sunTraceEnd, vec3_origin, vec3_origin, 0, 0x2003);
    if ( sunFlare->hitNum )
    {
      sunFlare->lastVisibility = 0.0;
    }
  }
}

void RB_DrawSunQuerySprite(SunFlareDynamic *sunFlare)
{
  float drawRatio;
  int sunSpriteSamples;
  int drawnSampleCount;
  float lastVisibility;
  int queryIndex;

  PIXBeginNamedEvent(-1, "RB_DrawSunQuerySprite");

  assert(sunFlare);

  queryIndex = r_glob.backEndFrameCount % ARRAY_COUNT( sunFlare->sunQuery );

  if ( !sunFlare->sunQuery[queryIndex] )
  {
    RB_UpdateSunVisibilityWithoutQuery(sunFlare);
    /*
    if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
    {
      D3DPERF_EndEvent();
    }
    */
    return;
  }
  RB_SetTessTechnique(rgp.additiveMaterial, TECHNIQUE_UNLIT);
//  R_TrackPrims(&gfxCmdBufState.prim, GFX_PRIM_STATS_FX);
  RB_SetIdentity();
  RB_TessSunBillboard(16.0 / (float)gfxCmdBufSourceState.renderTargetWidth, 16.0 / (float)gfxCmdBufSourceState.renderTargetHeight, { .packed = 0xFF000000 });
  if ( sunFlare->sunQueryIssued[queryIndex] )
  {
    drawnSampleCount = RB_HW_ReadOcclusionQuery(sunFlare->sunQuery[queryIndex]);
    if ( drawnSampleCount == -1 )
    {
      sunFlare->error = 1;
    }
    sunSpriteSamples = r_dx.sunSpriteSamples;
    assert(sunSpriteSamples > 0);

    if ( drawnSampleCount > sunSpriteSamples )
    {
      sunFlare->error = 1;
    }
    drawRatio = (double)drawnSampleCount / (double)sunSpriteSamples;
    lastVisibility = __min(drawRatio, 1.0);
  }
  else
  {
    lastVisibility = 0.0;
  }
  if ( !sunFlare->error )
  {
    sunFlare->lastVisibility = lastVisibility;
  }
  sunFlare->error = 0;

  if ( pixelCostMode == GFX_PIXEL_COST_MODE_MEASURE_COST || pixelCostMode == GFX_PIXEL_COST_MODE_MEASURE_MSEC )
  {
    RB_EndTessSurface();
  }
  else
  {
    RB_HW_BeginOcclusionQuery(sunFlare->sunQuery[queryIndex], NULL);
#pragma msg "debug starting here if sun is corrupted"
    RB_EndTessSurface();
    D3DCALLNOLOCKNOERROR(sunFlare->sunQuery[queryIndex]->Issue(1));
    sunFlare->sunQueryIssued[queryIndex] = 1;
  }
/*
  if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
  {
    D3DPERF_EndEvent();
  }
*/
}

void RB_DrawSunSprite()
{
  vec3_t v;

  RB_SetTessTechnique(rgp.world->sun.spriteMaterial, TECHNIQUE_UNLIT);
  GfxVertex *vert = RB_SetTessQuad({.packed = 0xFFFFFFFF});
  float spriteScale = rgp.world->sun.spriteSize * 0.001311092986725271;
  vec_t* sunFxPosition = rgp.world->sun.sunFxPosition;
  if ( sunFxPosition[2] * sunFxPosition[2] <= 0.99 )
  {
    v[0] = -sunFxPosition[2] * -sunFxPosition[0];
    v[1] = sunFxPosition[2] * sunFxPosition[1];
    v[2] = -sunFxPosition[0] * sunFxPosition[0] - sunFxPosition[1] * sunFxPosition[1];
  }
  else
  {
    v[0] = 0.0;
    v[1] = sunFxPosition[2];
    v[2] = -sunFxPosition[1];
  }

  Vec3Normalize(v);
  VectorScale(v, spriteScale, v);

  vec3_t v13, v14;

  v13[0] = sunFxPosition[2] * v[1] - sunFxPosition[1] * v[2];
  v13[1] = sunFxPosition[0] * v[2] - sunFxPosition[2] * v[0];
  v13[2] = sunFxPosition[1] * v[0] - sunFxPosition[0] * v[1];
  v14[0] = v13[0] + v[0];
  v14[1] = v13[1] + v[1];
  v14[2] = v13[2] + v[2];
  VectorSubtract(v, v13 ,v);

  vert[0].xyzw[0] = sunFxPosition[0] + v14[0];
  vert[0].xyzw[1] = sunFxPosition[1] + v14[1];
  vert[0].xyzw[2] = sunFxPosition[2] + v14[2];
  vert[0].xyzw[3] = 0.0;
  vert[1].xyzw[0] = sunFxPosition[0] + v[0];
  vert[1].xyzw[1] = sunFxPosition[1] + v[1];
  vert[1].xyzw[2] = sunFxPosition[2] + v[2];
  vert[1].xyzw[3] = 0.0;
  vert[2].xyzw[0] = sunFxPosition[0] - v14[0];
  vert[2].xyzw[1] = sunFxPosition[1] - v14[1];
  vert[2].xyzw[2] = sunFxPosition[2] - v14[2];
  vert[2].xyzw[3] = 0.0;
  vert[3].xyzw[0] = sunFxPosition[0] - v[0];
  vert[3].xyzw[1] = sunFxPosition[1] - v[1];
  vert[3].xyzw[2] = sunFxPosition[2] - v[2];
  vert[3].xyzw[3] = 0.0;
  RB_EndTessSurface();


}

void RB_AddSunEffects(SunFlareDynamic *sunFlare)
{
  assert(rgp.world);
  assert(sunFlare);

  sunFlare->lastDot = (float)((float)(rgp.world->sun.sunFxPosition[0] * gfxCmdBufSourceState.viewParms3D->axis[0][0])
                    + (float)(rgp.world->sun.sunFxPosition[1] * gfxCmdBufSourceState.viewParms3D->axis[0][1]))
                    + (float)(rgp.world->sun.sunFxPosition[2] * gfxCmdBufSourceState.viewParms3D->axis[0][2]);
  if ( sunFlare->lastDot > 0.0 )
  {
    RB_DrawSunSprite();
  }
}

void RB_DrawSun(int localClientNum)
{
  SunFlareDynamic *sunFlare;

  PIXBeginNamedEvent(-1, "RB_DrawSun");
  assert(rgp.world);

  assert((unsigned)localClientNum < gfxCfg.maxClientViews);

  if ( r_drawSun->current.enabled && rgp.world->sun.hasValidData)
  {
      sunFlare = &sunFlareArray[localClientNum];
      RB_SetIdentity();
      RB_DrawSunQuerySprite(sunFlare);
      RB_AddSunEffects(sunFlare);
      if ( tess.indexCount )
      {
        RB_EndTessSurface();
      }
      return;
  }
/*  
  if ( GetCurrentThreadId() == g_DXDeviceThread.owner && 0 == g_DXDeviceThread.aquired )
  {
    D3DPERF_EndEvent();
  }
*/
}

