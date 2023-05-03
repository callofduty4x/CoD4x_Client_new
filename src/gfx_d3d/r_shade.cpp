#include "r_local.h"
#include "r_setstate_d3d.h"
#include "rb_backend.h"
#include "r_image.h"


void R_TextureFromCodeError(GfxCmdBufState *state, unsigned int codeTexture)
{ 
  //Com_Error(ERR_FATAL, "Tried to use '%s' when it isn't valid\n", rg.codeImageNames[codeTexture]);

  if ( rg.codeImageNames[codeTexture] )
  {
    Com_Error(ERR_DROP, "Code texture %u '%s' isn't valid. Material='%s', tech='%s', techType=%d\n", codeTexture, rg.codeImageNames[codeTexture], state->material->info.name, state->technique->name, (uint8_t)state->techType);
  }
  else
  {
    Com_Error(ERR_DROP, "Code texture %u '%s' isn't valid. Material='%s', tech='%s', techType=%d\n", codeTexture, "noname", state->material->info.name, state->technique->name, (uint8_t)state->techType);
  }
}

void R_OverrideImage(const GfxImage **image, MaterialTextureDef *texdef)
{
  uint8_t semantic;
  assert(image);
  assert(texdef);

  if ( (*image)->mapType != MAPTYPE_2D )
  {
    return;
  }
  semantic = texdef->semantic;
  switch ( semantic )
  {
/*
    case 0u:
    case 1u:
    case 0xBu:
    case 0x1Au:
    case 0x1Bu:
      return; */
    case 2u:
/*    
    case 0xCu:
    case 0xDu:
    case 0xEu:
    case 0xFu:
    case 0x10u:
    case 0x11u:
    case 0x12u:
    case 0x13u:
    case 0x14u:
    case 0x15u:
    case 0x16u:
    case 0x17u:
    case 0x18u:
    case 0x19u:
    case 0x1Cu: */
      if ( r_colorMap->current.integer != R_COLOR_OVERRIDE_NONE )
      {
        *image = R_OverrideGrayscaleImage(r_colorMap);
      }
      break;
    case 5u:
      if ( r_normalMap->current.integer )
      {
        assert(r_normalMap->current.integer == R_NORMAL_OVERRIDE_NONE);
      }
      else
      {
        *image = rgp.identityNormalMapImage;
      }
      break;
    case 8u:
    /*
      if ( r_specularRoughnessMap->current.integer )
      {
        switch ( r_specularRoughnessMap->current.integer )
        {
          case 1:
            *image = rgp.blackTransparentImage;
            break;
          case 2:
            *image = rgp.blackImage;
            break;
          case 3:
            *image = rgp.whiteTransparentImage;
            break;
          case 4:
            *image = rgp.whiteImage;
            break;
        }
      }
    */
      if ( r_specularMap->current.integer != R_COLOR_OVERRIDE_NONE )
      {
        *image = R_OverrideGrayscaleImage(r_specularMap);
      }


      break;
    default:
      //assertx(0, "unhandled case %i", semantic);
      break;
  }
}

void R_SetState(GfxCmdBufState *state, const unsigned int *stateBits)
{
  if ( stateBits[0] != state->refStateBits[0] )
  {
    R_ChangeState_0(state, stateBits[0]);
    state->refStateBits[0] = stateBits[0];
  }
  if ( stateBits[1] != state->refStateBits[1] )
  {
    R_ChangeState_1(state, stateBits[1]);
    state->refStateBits[1] = stateBits[1];
  }
}


void R_SetVertexShaderConstantFromLiteral(GfxCmdBufState *state, unsigned int dest, const float *literal)
{
  signed int rowCount;
  const float *data;
  unsigned int idx;
  D3DDevice *device;

  assert(dest < ARRAY_COUNT( state->vertexShaderConstState ));


  state->vertexShaderConstState[dest] = -1;
  rowCount = 1;
  data = literal;
  idx = dest;
  device = state->prim.device;

  R_HW_SetVertexShaderConstant(device, dest, data, rowCount);

  if ( r_logFile->current.integer )
  {
    while ( rowCount )
    {
      RB_LogPrintf("vertex const %i: %g %g %g %g\n", idx, data[0], data[1], data[2], data[3]);
      ++idx;
      data += 4;
      --rowCount;
    }
  }
}


MaterialTextureDef * R_SetPixelSamplerFromMaterial(GfxCmdBufContext *context, MaterialShaderArgument *arg, MaterialTextureDef *texDef)
{
  const GfxImage *image;
  Material *material;
  char samplerState;

  material = context->state->material;
  while ( texDef->nameHash != arg->u.nameHash )
  {
    ++texDef;
    assertx(texDef != &material->textureTable[material->textureCount], "material '%s' is missing a required named texture", material->info.name);
  }
  if ( texDef->semantic == 11 )
  {
    image = texDef->u.water->image;
    R_UploadWaterTexture(texDef->u.water, context->source->sceneDef.floatTime);
  }
  else
  {
    image = texDef->u.image;
  }
  samplerState = texDef->samplerState;
  if ( rg.hasAnyImageOverrides )
  {
    R_OverrideImage(&image, texDef);
  }
/*  
  if ( texDef->isMatureContent )
  {
    if ( context->source->input.data->hideMatureContent )
    {
      if ( (unsigned __int16)((unsigned __int16)(material->info.layeredSurfaceTypes >> 16) >> 21) > 1u )
      {
        image = rgp.blankImage;
      }
    }
  }
*/
  R_SetSampler(*context, arg->dest, samplerState, image);
  return texDef;
}

const float *R_GetCodeConstant(GfxCmdBufContext *context, unsigned int constant)
{
//  assert(context.local.state);
//  assert(context.local.source);
  assert( constant < MAX_GFXCMDINPUTCONST);

  return context->source->input.consts[constant];
}

bool R_IsShaderConstantUpToDate(GfxCmdBufSourceState *source, uint64_t *constant, MaterialShaderArgument *routingData)
{
  GfxShaderConstantState newState;
  assert(source);

  newState.fields.codeConst = routingData->u.codeConst;
  newState.fields.version = source->constVersions[routingData->u.codeConst.index];
  if ( *constant == newState.packed )
  {
    return true;
  }
  *constant = newState.packed;
  assert(routingData->u.codeConst.rowCount == 1);
  return false;
}

bool R_IsShaderMatrixUpToDate(GfxCmdBufSourceState *source, uint64_t *constant, MaterialShaderArgument *routingData)
{
  GfxShaderConstantState newState;
  unsigned int rowCount;

  newState.fields.codeConst = routingData->u.codeConst;
  newState.fields.version = source->matrixVersions[(routingData->u.codeConst.index - MAX_GFXCMDINPUTCONST) / 4];
  if ( *constant == newState.packed )
  {
    return true;
  }

  *constant = newState.packed;
  rowCount = (uint8_t)routingData->u.codeConst.rowCount;
  assert(rowCount);
  --rowCount;
  while ( rowCount )
  {
    ++constant;
    *constant = -1;
    --rowCount;
  }
  return false;
}

bool R_IsVertexShaderConstantUpToDate(GfxCmdBufContext context, MaterialShaderArgument *routingData)
{
  uint16_t dest = routingData->dest;
  assert(dest < ARRAY_COUNT( context.state->vertexShaderConstState ));

  if ( (signed int)routingData->u.codeConst.index < MAX_GFXCMDINPUTCONST )
  {
    return R_IsShaderConstantUpToDate(context.source, &context.state->vertexShaderConstState[dest], routingData);
  }
  return R_IsShaderMatrixUpToDate(context.source, &context.state->vertexShaderConstState[dest], routingData);

}

void R_SetVertexShaderConstantFromCode_Old(GfxCmdBufContext context, MaterialShaderArgument *routingData)
{
  unsigned int rowCount;
  unsigned int dest;
  D3DDevice *device;
  GfxCmdBufContext source;
  const float *data;

  if ( R_IsVertexShaderConstantUpToDate(context, routingData) != 0 )
  {
    return;
  }
  source = context;
  if ( (signed int)routingData->u.codeConst.index < MAX_GFXCMDINPUTCONST )
  {
    data = R_GetCodeConstant(&source, routingData->u.codeConst.index);
  }
  else
  {
    data = R_GetCodeMatrix(source.source, routingData->u.codeConst.index, (uint8_t)routingData->u.codeConst.firstRow);
  }
  rowCount = (uint8_t)routingData->u.codeConst.rowCount;
  dest = routingData->dest;
  device = context.state->prim.device;

  R_HW_SetVertexShaderConstant(device, dest, data, rowCount);
  
  if ( r_logFile->current.integer )
  {
    while ( rowCount )
    {
      RB_LogPrintf("vertex const %i: %g %g %g %g\n", dest, data[0], data[1], data[2], data[3]);
      ++dest;
      data += 4;
      --rowCount;
    }
  }
}


void R_SetPassShaderStableArguments(GfxCmdBufContext *context, unsigned int argCount, MaterialShaderArgument *arg)
{
  const GfxImage *image;
  Material *material;
  MaterialTextureDef *texDef;
  char samplerState;
  MaterialConstantDef *constDef;

  material = context->state->material;
  constDef = material->constantTable;
  while ( !arg->type )
  {
    while ( constDef->nameHash != arg->u.codeSampler )
    {
      ++constDef;
      assertx(constDef != &material->constantTable[material->constantCount], "material '%s' is missing a required named constant", material->info.name);
    }
    R_SetVertexShaderConstantFromLiteral(context->state, arg->dest, constDef->literal);
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }

  while ( arg->type == 1 )
  {
    R_SetVertexShaderConstantFromLiteral(context->state, arg->dest, arg->u.literalConst);
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }

  texDef = material->textureTable;
  while ( arg->type == 2 )
  {
    texDef = R_SetPixelSamplerFromMaterial(context, arg, texDef);
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }

  while ( arg->type == 3 )
  {
/*
    if ( Use_R_SetVertexShaderConstantFromCode_New )
    {
      R_SetVertexShaderConstantFromCode_New(context, arg);
    }
    else
*/
    {
      R_SetVertexShaderConstantFromCode_Old(*context, arg);
    }
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }
  while ( arg->type == 4 )
  {
/*
    if ( context->source->input.codeImageRenderTargetControl[arg->u.codeSampler].fields.renderTargetId )
    {
      R_SetTextureSamplerCodeImageRenderTarget(*context, arg->dest, context->source->input.codeImageRenderTargetControl[arg->u.codeSampler]);
      ++arg;
      if ( !--argCount )
      {
        return;
      }
    }
    else
*/
    {
      image = R_GetTextureFromCode(context->source, arg->u.codeSampler, &samplerState);
      if ( !image )
      {
        R_TextureFromCodeError(context->state, arg->u.codeSampler);
      }
      R_SetSampler(*context, arg->dest, samplerState, image);
      ++arg;
      if ( !--argCount )
      {
        return;
      }
    }
  }
}


void R_SetupPass(GfxCmdBufContext context, unsigned int passIndex)
{

  GfxStateBits *refStateBits;
  MaterialPass *pass;
  Material *material;
  unsigned int stateBits[2];

  pass = &context.state->technique->passArray[passIndex];
  context.state->pass = pass;
  context.state->passIndex = passIndex;
  material = context.state->material;

#if 0
  if ( (unsigned __int8)material->stateBitsEntry[(unsigned __int8)context.state->techType] >= (unsigned int)(unsigned __int8)material->stateBitsCount
    && !(unsigned __int8)Assert_MyHandler(
                           "C:\\projects_pc\\cod\\codsrc\\src\\gfx_d3d\\r_shade.cpp",
                           1376,
                           0,
                           "material->stateBitsEntry[context.local.state->techType] doesn't index material->stateBitsCount\n\t%i not in [0, %i)",
                           (unsigned __int8)material->stateBitsEntry[(unsigned __int8)context.state->techType],
                           (unsigned __int8)material->stateBitsCount) )
  {
    __debugbreak();
  }
#endif
  refStateBits = &material->stateBitsTable[passIndex + (uint8_t)material->stateBitsEntry[(uint8_t)context.state->techType]];
  stateBits[0] = refStateBits->loadBits[0];
  stateBits[1] = refStateBits->loadBits[1];

  R_SetState(context.state, stateBits);

  if ( r_logFile->current.integer )
  {
    _RB_LogPrintf("---------- R_SetupPass\n"
                  "---------- vertex shader: %s\n"
                  "---------- pixel shader: %s\n"
                  "---------- state bits: 0x%08x, 0x%08x\n", 
                  pass->vertexShader->name, pass->pixelShader->name, stateBits[0], stateBits[1]);
  }

  R_SetPixelShader(context.state, pass->pixelShader);

  if ( pass->stableArgCount )
  {
    R_SetPassShaderStableArguments(&context, (uint8_t)pass->stableArgCount, &pass->args[(uint8_t)pass->perPrimArgCount + (uint8_t)pass->perObjArgCount]);
  }
}


void R_SetPassShaderPrimArguments(GfxCmdBufContext *context, unsigned int argCount, MaterialShaderArgument *arg)
{
  while ( arg->type == 3 )
  {
/*
    if ( Use_R_SetVertexShaderConstantFromCode_New )
    {
      R_SetVertexShaderConstantFromCode_New(context, arg);
    }
    else
*/
    {
      R_SetVertexShaderConstantFromCode_Old(*context, arg);
    }
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }
  assertx(0, "unreachable");
}

void R_SetupPassPerPrimArgs(GfxCmdBufContext context)
{
  MaterialPass *pass;

  pass = context.state->pass;
  if ( pass->perPrimArgCount )
  {
    R_SetPassShaderPrimArguments(&context, (uint8_t)pass->perPrimArgCount, pass->args);
  }
}



void R_SetPassShaderObjectArguments(GfxCmdBufContext *context, unsigned int argCount, MaterialShaderArgument *arg)
{
  const GfxImage *image;
  char samplerState;

  while ( arg->type == 3 )
  {
/*
    if ( Use_R_SetVertexShaderConstantFromCode_New )
    {
      R_SetVertexShaderConstantFromCode_New(context, arg);
    }
    else
*/
    {
      R_SetVertexShaderConstantFromCode_Old(*context, arg);
    }
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }
  while ( arg->type == 4 )
  {
/*
    if ( context->source->input.codeImageRenderTargetControl[arg->u.codeSampler].fields.renderTargetId )
    {
      R_SetTextureSamplerCodeImageRenderTarget(*context, arg->dest, context->source->input.codeImageRenderTargetControl[arg->u.codeSampler]);
      ++arg;
      if ( !--argCount )
      {
        return;
      }
    }
    else
*/
    {
      image = R_GetTextureFromCode(context->source, arg->u.codeSampler, &samplerState);
      if ( !image )
      {
        R_TextureFromCodeError(context->state, arg->u.codeSampler);
      }
      R_SetSampler(*context, arg->dest, samplerState, image);
      ++arg;
      if ( !--argCount )
      {
        return;
      }
    }
  }
  assertx(0, "unreachable");
}



void R_SetupPassPerObjectArgs(GfxCmdBufContext context)
{
  MaterialPass *pass;

  pass = context.state->pass;
  if ( pass->perObjArgCount )
  {
    R_SetPassShaderObjectArguments(&context, (uint8_t)pass->perObjArgCount, &pass->args[(uint8_t)pass->perPrimArgCount]);
  }
}


void R_SetPassVertexShaderStableArguments(GfxCmdBufContext *context, unsigned int argCount, MaterialShaderArgument *arg)
{
  while ( (signed int)arg->type < 3 )
  {
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }
  do
  {
    if ( arg->type != 3 )
    {
      break;
    }
/*    
    if ( Use_R_SetVertexShaderConstantFromCode_New )
    {
      R_SetVertexShaderConstantFromCode_New(context, arg);
    }
    else
*/
    {
      R_SetVertexShaderConstantFromCode_Old(*context, arg);
    }
    ++arg;
    --argCount;
  }
  while ( argCount );
}

void R_SetupPassVertexShaderArgs(GfxCmdBufContext context)
{
  MaterialPass *pass;

  pass = context.state->pass;
  if ( pass->stableArgCount )
  {
    R_SetPassVertexShaderStableArguments(&context, (uint8_t)pass->stableArgCount, &pass->args[(uint8_t)pass->perPrimArgCount + (uint8_t)pass->perObjArgCount]);
  }
}


bool R_IsPixelShaderConstantUpToDate(GfxCmdBufContext *context, MaterialShaderArgument *routingData)
{
  GfxShaderConstantState newState;

  assert(routingData->dest < ARRAY_COUNT( context->state->pixelShaderConstState ));
  assert(routingData->u.codeConst.rowCount == 1);
  assert(context->source);

  newState.fields.codeConst = routingData->u.codeConst;
  newState.fields.version = context->source->constVersions[routingData->u.codeConst.index];
  
  assert(newState.fields.version);
  
  if ( context->state->pixelShaderConstState[routingData->dest] == newState.packed )
  {
    return true;
  }
  context->state->pixelShaderConstState[routingData->dest] = newState.packed;
  return false;
}

void R_SetPixelShaderConstantFromLiteral(GfxCmdBufState *state, unsigned int dest, const float *literal)
{
  assert ( dest < ARRAY_COUNT( state->pixelShaderConstState ));

  state->pixelShaderConstState[dest] = -1;
  R_HW_SetPixelShaderConstant(state->prim.device, dest, literal, 1u);
}

void R_SetPixelShaderConstantFromCode(GfxCmdBufContext *context, MaterialShaderArgument *routingData)
{
  const float *data;

  assertx(context->source->constVersions[routingData->u.codeConst.index], "constant: %d, material: %s, technique: %s", routingData->u.codeConst.index, context->state->material->info.name, context->state->technique->name);
  assert(routingData->u.codeConst.index < CONST_SRC_FIRST_CODE_MATRIX);

  data = R_GetCodeConstant(context, routingData->u.codeConst.index);
  R_HW_SetPixelShaderConstant(context->state->prim.device, routingData->dest, data, (uint8_t)routingData->u.codeConst.rowCount);
}

void R_SetPassPixelShaderStableArguments(GfxCmdBufContext *context, unsigned int argCount, MaterialShaderArgument *arg)
{
  Material *material;
  MaterialConstantDef *constDef;

  material = context->state->material;
  while ( (signed int)arg->type < 5 )
  {
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }
  while ( arg->type == 5 )
  {
    if ( !R_IsPixelShaderConstantUpToDate(context, arg) )
    {
      R_SetPixelShaderConstantFromCode(context, arg);
    }
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }
  constDef = material->constantTable;
  while ( arg->type == 6 )
  {
    while ( constDef->nameHash != arg->u.nameHash )
    {
      ++constDef;
      assertx(constDef != &material->constantTable[material->constantCount], "material '%s' is missing a required named constant", material->info.name);
    }
    R_SetPixelShaderConstantFromLiteral(context->state, arg->dest, constDef->literal);
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }
  while ( arg->type == 7 )
  {
    R_SetPixelShaderConstantFromLiteral(context->state, arg->dest, arg->u.literalConst);
    ++arg;
    if ( !--argCount )
    {
      return;
    }
  }
  assertx(0, "unreachable");

}


void R_SetupPassCriticalPixelShaderArgs(GfxCmdBufContext context)
{
  MaterialPass *pass;

  pass = context.state->pass;
  if ( pass->stableArgCount )
  {
    R_SetPassPixelShaderStableArguments(&context, (uint8_t)pass->stableArgCount, &pass->args[(uint8_t)pass->perPrimArgCount + (uint8_t)pass->perObjArgCount]);
  }
}

void R_SetupPassPixelShaderArgs(GfxCmdBufContext context)
{
  MaterialPass *pass;

  pass = context.state->pass;
  if ( pass->stableArgCount )
  {
    R_SetPassPixelShaderStableArguments(&context, (uint8_t)pass->stableArgCount, &pass->args[(uint8_t)pass->perPrimArgCount + (uint8_t)pass->perObjArgCount]);
  }
}


void R_SetVertexShader(GfxCmdBufState *state, const MaterialVertexShader *vertexShader)
{
  if ( state->vertexShader != vertexShader )
  {
    assert(vertexShader);
    assertx(vertexShader->prog.vs, "(vertexShader->name) = %s", vertexShader->name);

    R_HW_SetVertexShader(state->prim.device, vertexShader);
    state->vertexShader = vertexShader;
  }
}

void R_UpdateVertexDecl(GfxCmdBufState *state)
{
  MaterialPass *pass;
  MaterialVertexShader *vertexShader;

  pass = state->pass;
  assert(pass->vertexDecl);

  vertexShader = pass->vertexShader;
  assert(vertexShader);

  R_SetVertexDecl(&state->prim, pass->vertexDecl);

  assert(pass->pixelShader);
  assert(pass->vertexDecl->routing.decl);

  if ( !pass->vertexDecl->routing.decl[state->prim.vertDeclType] )
  {
    Com_Error(ERR_FATAL, "Vertex type %i doesn't have the information used by shader %s in material %s\n", state->prim.vertDeclType, pass->vertexShader->name, state->material->info.name);
  }
  R_SetVertexShader(state, vertexShader);
}

void R_SetPixelShader(GfxCmdBufState *state, const MaterialPixelShader *pixelShader)
{
  assert(pixelShader);
  assertx(pixelShader->prog.ps, "(pixelShader->name) = %s", pixelShader->name);

  if ( state->pixelShader != pixelShader )
  {
    R_HW_SetPixelShader(state->prim.device, pixelShader);
    state->pixelShader = pixelShader;
  }
}

int R_ReserveIndexData(GfxCmdBufPrimState *state, int triCount)
{
  signed int index;
  int indexCount;

  indexCount = 3 * triCount;

  assert(indexCount <= gfxBuf.dynamicIndexBuffer->total);

  if ( indexCount + gfxBuf.dynamicIndexBuffer->used > gfxBuf.dynamicIndexBuffer->total )
  {
    gfxBuf.dynamicIndexBuffer->used = 0;
  }
  if ( !gfxBuf.dynamicIndexBuffer->used )
  {
    index = gfxBuf.dynamicIndexBuffer - gfxBuf.dynamicIndexBufferPool;
    if ( index < 0 )
    {
      index = 0;
    }
    gfxBuf.dynamicIndexBuffer = &gfxBuf.dynamicIndexBufferPool[index];
  }
  return gfxBuf.dynamicIndexBuffer->used;
}

int R_SetIndexData(GfxCmdBufPrimState *state, const uint16_t *indices, int triCount)
{
  int baseIndex;
  int indexDataSize;
  D3DIndexBuffer *ib;
  uint16_t *bufferData;

  baseIndex = R_ReserveIndexData(state, triCount);
  indexDataSize = 6 * triCount;
  ib = gfxBuf.dynamicIndexBuffer->buffer;
  assert(ib);

  if ( gfxBuf.dynamicIndexBuffer->used )
  {
    bufferData = (uint16_t*)R_LockIndexBuffer(ib, 2 * gfxBuf.dynamicIndexBuffer->used, indexDataSize, 4096);
  }
  else
  {
    bufferData = (uint16_t*)R_LockIndexBuffer(ib, 2 * gfxBuf.dynamicIndexBuffer->used, indexDataSize, 8192);
  }
  if ( bufferData )
  {
    memcpy(bufferData, indices, indexDataSize);
  }
  R_UnlockIndexBuffer(ib);
  if ( state->indexBuffer != ib )
  {
    R_ChangeIndices(state, ib);
  }
  if ( bufferData )
  {
    gfxBuf.dynamicIndexBuffer->used += 3 * triCount;
  }
  return baseIndex;
}

int R_SetVertexData(GfxCmdBufState *state, const void *data, int vertexCount, int stride)
{
  int vertexOffset;
  D3DVertexBuffer *vb;
  void *bufferData;
  int totalSize;

  assert(vertexCount > 0);

  totalSize = stride * vertexCount;

  assert(totalSize <= gfxBuf.dynamicVertexBuffer->total);
  assert(gfxBuf.dynamicVertexBuffer->used + totalSize <= gfxBuf.dynamicVertexBuffer->total);

  vb = gfxBuf.dynamicVertexBuffer->buffer;

  assert(vb);

  bufferData = R_LockVertexBuffer(vb, gfxBuf.dynamicVertexBuffer->used, totalSize, gfxBuf.dynamicVertexBuffer->used != 0 ? 0x1000 : 0x2000);

  assert(bufferData);

  if ( bufferData )
  {
    memcpy(bufferData, data, totalSize);
  }
  R_UnlockVertexBuffer(vb);
  vertexOffset = gfxBuf.dynamicVertexBuffer->used;
  gfxBuf.dynamicVertexBuffer->used += totalSize;
  return vertexOffset;
}
