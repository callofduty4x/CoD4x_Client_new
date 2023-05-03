#ifndef __R_SHARED_H__
#define __R_SHARED_H__

#include "../common/cvar.h"

struct Material;
struct GfxLightDef;

struct vidConfig_t
{
  unsigned int sceneWidth;
  unsigned int sceneHeight;
  unsigned int displayWidth;
  unsigned int displayHeight;
  int displayFrequency;
  int isFullscreen;
  float aspectRatioWindow;
  float aspectRatioScenePixel;
  float aspectRatioDisplayPixel;
  unsigned int maxTextureSize;
  unsigned int maxTextureMaps;
  byte deviceSupportsGamma;
  byte pad0[3];
};

struct GfxLight
{
  char type;
  char canUseShadowMap;
  char unused[2];
  float color[3];
  float dir[3];
  vec3_t origin;
  float radius;
  float cosHalfFovOuter;
  float cosHalfFovInner;
  int exponent;
  unsigned int spotShadowIndex;
  GfxLightDef *def;
};

#pragma pack(push, 4)
struct GfxGlow
{
  bool8 enabled;
  float bloomCutoff;
  float bloomDesaturation;
  float bloomIntensity;
  float radius;
};
#pragma pack(pop)


#pragma pack(push, 4)
struct GfxFilm
{
  bool8 enabled;
  float brightness;
  float contrast;
  float desaturation;
  bool8 invert;
  float tintDark[3];
  float tintLight[3];
};
#pragma pack(pop)

struct GfxDepthOfField
{
  float viewModelStart;
  float viewModelEnd;
  float nearStart;
  float nearEnd;
  float farStart;
  float farEnd;
  float nearBlur;
  float farBlur;
};


struct GfxViewport
{
  int x;
  int y;
  int width;
  int height;
};

struct refdef_s
{
  unsigned int x;
  unsigned int y;
  unsigned int width;
  unsigned int height;
  float tanHalfFovX;
  float tanHalfFovY;
  float vieworg[3];
  float viewaxis[3][3];
  float viewOffset[3];
  int time;
  float zNear;
  float blurRadius;
  GfxDepthOfField dof;
  GfxFilm film;
  GfxGlow glow;
  GfxLight primaryLights[255];
  GfxViewport scissorViewport;
  bool useScissorViewport;
  int localClientNum;
};



void R_SyncRenderThread();
void R_WaitWorkerCmds();
extern cvar_t* r_reflectionProbeGenerate;
extern cvar_t* r_fullscreen;
extern cvar_t* vid_xpos;
extern cvar_t* vid_ypos;


void R_EndRemoteScreenUpdate(void (*pumpfunc)());
void R_BeginRemoteScreenUpdate();
bool R_CheckLostDevice();

/************************
Fonts, texts
*************************/
struct Font_s;

int     R_TextWidth(const char *text, int maxChars, Font_s *font);
void    R_AddCmdDrawText(const char *text, int maxChars, Font_s *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style);
void    R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, Material *material);
void    R_AddCmdDrawConsoleText(const char *textPool, int poolSize, int firstChar, int charCount, Font_s *font, float x, float y, float xScale, float yScale, const float *color, int style);
int     R_TextHeight(Font_s *font);
#endif