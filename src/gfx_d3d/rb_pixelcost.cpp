#include "r_material.h"
#include "r_local.h"
#include "r_state.h"
#include "rb_backend.h"
#include "../common/sys_shared.h"
#include <intrin.h>

enum GfxPixelCostMode pixelCostMode;

const Material* R_PixelCost_GetAccumulationMaterial(const Material *material)
{
  int index;

  if ( pixelCostMode == GFX_PIXEL_COST_MODE_ADD_COST_IGNORE_DEPTH )
  {
    return rgp.pixelCostAddDepthDisableMaterial;
  }
  if ( pixelCostMode == GFX_PIXEL_COST_MODE_ADD_PASSES_IGNORE_DEPTH )
  {
    return rgp.pixelCostAddDepthDisableMaterial;
  }
  if ( material->techniqueSet->techniques[TECHNIQUE_UNLIT] )
  {
    index = (uint8_t)material->stateBitsEntry[4];
  }
  else
  {
    index = 0;
  }
  switch ( material->stateBitsTable[index].loadBits[1] & 0xF )
  {
      case 0u:
      case 1u:
          return rgp.pixelCostAddDepthAlwaysMaterial;

      case 2u:
      case 3u:
          return rgp.pixelCostAddDepthDisableMaterial;

      case 4u:
      case 5u:
          return rgp.pixelCostAddDepthLessMaterial;

      case 6u:
      case 7u:
          return rgp.pixelCostAddDepthDisableMaterial;

      case 8u:
      case 9u:
          return rgp.pixelCostAddDepthEqualMaterial;

      case 10u:
      case 11u:
          return rgp.pixelCostAddDepthDisableMaterial;

      case 12u:
          return rgp.pixelCostAddNoDepthWriteMaterial;

      case 13u:
          return rgp.pixelCostAddDepthWriteMaterial;

      case 14u:
      case 15u:
          return rgp.pixelCostAddDepthDisableMaterial;

      default:
          assertx(0, "unhandled case %i", material->stateBitsTable[index].loadBits[1] & 0xF);
  }
  return rgp.pixelCostAddNoDepthWriteMaterial;
}


void R_PixelCost_SetConstant(GfxCmdBufSourceState *source, int cost)
{
  float weights[4];

  if ( gfxAssets.pixelCountQuery )
  {
    weights[0] = (float)((float)(cost >> 6) + 0.0099999998) * 0.0039215689;
    weights[1] = (float)((float)((cost >> 4) & 3) + 0.0099999998) * 0.0039215689;
    weights[2] = (float)((float)((cost >> 2) & 3) + 0.0099999998) * 0.0039215689;
    weights[3] = (float)((float)(cost & 3) + 0.0099999998) * 0.0039215689;
  }
  else
  {
    weights[0] = 0.094156861;
    weights[1] = 0.031411767;
    weights[2] = 0.0;
    weights[3] = 0.0039607841;
  }
  R_SetCodeConstantFromVec4(source, CONST_SRC_CODE_MAYBE_DIRTY_PS_END, weights);
}

struct __align(4) GfxPixelCostKeyDetailed
{
  Material *material;
  MaterialTechniqueType techType;
};

union GfxPixelCostKey
{
  GfxPixelCostKeyDetailed mtl;
  uint64_t packed;
};


struct GfxPixelCostRecord
{
  uint16_t costHistory[12];
  GfxPixelCostKey key;
};


struct GfxPixelCostGlob
{
  GfxPixelCostMode savedMode;
  long double msecOverhead;
  uint64_t timeBegin;
  long double msecElapsed;
  int frameIndex;
  int expectedCount;
  int recordCount;
  GfxPixelCostRecord records[2048];
};



GfxPixelCostGlob pixelCostGlob;

int RB_PixelCost_GetCostForRecordIndex(int recordIndex)
{
    long double costDelta;
    signed int uc;
    int avgCost;
    int cost;
    unsigned int frameIndex;
    int totalCost;
    unsigned int validCount;
    double standardDeviationSum;
    int costHistory[12];

    totalCost = 0;
    validCount = 0;
    for ( frameIndex = 0; frameIndex < ARRAY_COUNT(costHistory); ++frameIndex )
    {
        cost = pixelCostGlob.records[recordIndex].costHistory[frameIndex];
        if ( pixelCostGlob.records[recordIndex].costHistory[frameIndex] )
        {
            totalCost += cost;
            costHistory[validCount] = cost;
            ++validCount;
        }
    }
    if ( validCount == 1 )
    {
        return totalCost;
    }
    if ( validCount == 2 )
    {
        if ( costHistory[0] < costHistory[1] )
        {
            return totalCost - costHistory[1];
        }
        return totalCost - costHistory[0];
    }

    assert(validCount > 0);

    standardDeviationSum = 0.0;
    avgCost = totalCost / validCount;
    for ( frameIndex = 0; frameIndex < validCount; ++frameIndex )
    {
      costDelta = (double)(costHistory[frameIndex] - avgCost);
      standardDeviationSum = costDelta * costDelta + standardDeviationSum;
    }
    uc = (signed int)(sqrt(standardDeviationSum / (double)validCount) * 1.5);
    if ( uc <= 10 )
    {
      uc = 10;
    }
    for ( frameIndex = validCount - 1; frameIndex >= 0; --frameIndex )
    {
      if ( (double)(signed int)abs(costHistory[frameIndex] - avgCost) > (double)uc )
      {
        totalCost -= costHistory[frameIndex];
        --validCount;
      }
    }
    assert(validCount >= 2);
    return totalCost / validCount;
}

uint64_t R_PixelCost_PackedKeyForMaterial(Material *material, MaterialTechniqueType techType)
{
    GfxPixelCostKey key;

    assert(material);

    key.mtl.material = material;
    key.mtl.techType = techType;

    return key.packed;
}

bool RB_PixelCost_DoesPrimMatch(uint64_t packedKey)
{
    return pixelCostGlob.records[pixelCostGlob.recordCount].key.packed == packedKey;
}

void RB_PixelCost_ResetPrim(uint64_t packedKey)
{
  GfxPixelCostRecord *record;

  record = &pixelCostGlob.records[pixelCostGlob.expectedCount];
  record->key.packed = packedKey;
  memset(record->costHistory, 0, sizeof(record->costHistory));
}

void RB_PixelCost_AccumulateMsec()
{
  int timeQuantized;

  timeQuantized = (signed int)ceil(pixelCostGlob.msecElapsed * 3932.1);
  pixelCostGlob.records[pixelCostGlob.recordCount++].costHistory[pixelCostGlob.frameIndex] = _clip2domain(timeQuantized, 1, 65535);
}

GfxRenderTargetId RB_PixelCost_OverrideRenderTarget(GfxRenderTargetId targetId)
{
  if ( targetId <= R_RENDERTARGET_FRAME_BUFFER )
  {
    return R_RENDERTARGET_FRAME_BUFFER;
  }
  if ( targetId <= R_RENDERTARGET_PINGPONG_1 )
  {
    return R_RENDERTARGET_SCENE;
  }
  return targetId;
}

#define RB_PixelCost_IsAccumulating() (pixelCostMode > GFX_PIXEL_COST_MODE_MEASURE_MSEC)

void R_PixelCost_BeginMeasure()
{
    R_AcquireGpuFenceLock();
    R_FinishGpuFence();
    R_InsertGpuFence();
    R_FinishGpuFence();
    R_ReleaseGpuFenceLock();
    pixelCostGlob.timeBegin = __rdtsc();
}

void R_PixelCost_EndMeasure()
{
  R_AcquireGpuFenceLock();
  R_FinishGpuFence();
  R_InsertGpuFence();
  R_FinishGpuFence();
  R_ReleaseGpuFenceLock();
  
  pixelCostGlob.msecElapsed = (double)(__rdtsc() - pixelCostGlob.timeBegin) * msecPerRawTimerTick - pixelCostGlob.msecOverhead;
  if ( pixelCostGlob.msecElapsed < 0.0 )
  {
    pixelCostGlob.msecElapsed = 0.0;
  }
}

void R_PixelCost_BeginSurface(GfxCmdBufContext context)
{
  int cost;
  uint64_t packedKey;

  if ( pixelCostMode == GFX_PIXEL_COST_MODE_MEASURE_COST )
  {
    packedKey = R_PixelCost_PackedKeyForMaterial(context.state->material, context.state->techType);
    if ( !RB_PixelCost_DoesPrimMatch(packedKey) )
    {
      RB_PixelCost_ResetPrim(packedKey);
    }
    ++pixelCostGlob.expectedCount;
    R_PixelCost_BeginMeasure();
    RB_HW_BeginOcclusionQuery(gfxAssets.pixelCountQuery, NULL);
  }
  else if ( pixelCostMode == GFX_PIXEL_COST_MODE_MEASURE_MSEC )
  {
    packedKey = R_PixelCost_PackedKeyForMaterial(context.state->material, context.state->techType);
    if ( !RB_PixelCost_DoesPrimMatch(packedKey) )
    {
      RB_PixelCost_ResetPrim(packedKey);
    }
    ++pixelCostGlob.expectedCount;
    R_PixelCost_BeginMeasure();
  }
  else
  {
    assert(RB_PixelCost_IsAccumulating());
    cost = RB_PixelCost_GetCostForRecordIndex(pixelCostGlob.recordCount);
    R_PixelCost_SetConstant(context.source, cost);
  }
}


void R_PixelCost_EndSurface(GfxCmdBufContext context)
{
  signed int c0;
  unsigned int cost;
  unsigned int pixelCount;

  if ( pixelCostMode == GFX_PIXEL_COST_MODE_MEASURE_COST )
  {
    D3DCALLNOLOCKNOERROR(gfxAssets.pixelCountQuery->Issue(1));
    R_PixelCost_EndMeasure();
    pixelCount = RB_HW_ReadOcclusionQuery(gfxAssets.pixelCountQuery);
    if ( pixelCount )
    {
      c0 = (signed int)ceil((double)(context.source->renderTargetHeight * context.source->renderTargetWidth) * 
            pixelCostGlob.msecElapsed / (double)pixelCount * 30.72);
      cost = __max(c0, 1);
    }
    else
    {
      cost = 1;
    }
    if ( cost > 65535 )
    {
      cost = 65535;
    }
    pixelCostGlob.records[pixelCostGlob.recordCount].costHistory[pixelCostGlob.frameIndex] = cost;
    pixelCostGlob.recordCount++;
  }
  else if ( pixelCostMode == GFX_PIXEL_COST_MODE_MEASURE_MSEC )
  {
    R_PixelCost_EndMeasure();
    RB_PixelCost_AccumulateMsec();
  }
  else
  {
    assert(RB_PixelCost_IsAccumulating());
    ++pixelCostGlob.recordCount;
  }
}

void RB_PixelCost_Init()
{
  
}

