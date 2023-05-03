
enum XAssetType
{
  ASSET_TYPE_XMODELPIECES,
  ASSET_TYPE_PHYSPRESET,
  ASSET_TYPE_XANIMPARTS,
  ASSET_TYPE_XMODEL,
  ASSET_TYPE_MATERIAL,
  ASSET_TYPE_TECHNIQUE_SET,
  ASSET_TYPE_IMAGE,
  ASSET_TYPE_SOUND,
  ASSET_TYPE_SOUND_CURVE,
  ASSET_TYPE_LOADED_SOUND,
  ASSET_TYPE_CLIPMAP,
  ASSET_TYPE_CLIPMAP_PVS,
  ASSET_TYPE_COMWORLD,
  ASSET_TYPE_GAMEWORLD_SP,
  ASSET_TYPE_GAMEWORLD_MP,
  ASSET_TYPE_MAP_ENTS,
  ASSET_TYPE_GFXWORLD,
  ASSET_TYPE_LIGHT_DEF,
  ASSET_TYPE_UI_MAP,
  ASSET_TYPE_FONT,
  ASSET_TYPE_MENULIST,
  ASSET_TYPE_MENU,
  ASSET_TYPE_LOCALIZE_ENTRY,
  ASSET_TYPE_WEAPON,
  ASSET_TYPE_SNDDRIVER_GLOBALS,
  ASSET_TYPE_FX,
  ASSET_TYPE_IMPACT_FX,
  ASSET_TYPE_AITYPE,
  ASSET_TYPE_MPTYPE,
  ASSET_TYPE_CHARACTER,
  ASSET_TYPE_XMODELALIAS,
  ASSET_TYPE_RAWFILE,
  ASSET_TYPE_STRINGTABLE,
  ASSET_TYPE_COUNT
};

union XAssetHeader
{
  struct XModelPieces *xmodelPieces;
  struct PhysPreset *physPreset;
  struct XAnimParts *parts;
  struct XModel *model;
  struct Material *material;
  struct MaterialPixelShader *pixelShader;
  struct MaterialVertexShader *vertexShader;
  struct MaterialTechniqueSet *techniqueSet;
  struct GfxImage *image;
  struct snd_alias_list_t *sound;
  struct SndCurve *sndCurve;
  struct LoadedSound_s* loadedsound;
  struct clipMap_s *clipMap;
  struct ComWorld *comWorld;
  struct GameWorldSp *gameWorldSp;
  struct GameWorldMp *gameWorldMp;
  struct MapEnts *mapEnts;
  struct GfxWorld *gfxWorld;
  struct GfxLightDef *lightDef;
  struct Font_s *font;
  struct MenuList *menuList;
  struct menuDef_t *menu;
  struct LocalizeEntry *localize;
  struct WeaponDef *weapon;
  struct SndDriverGlobals *sndDriverGlobals;
  struct FxEffectDef *fx;
  struct FxImpactTable *impactFx;
  struct RawFile *rawfile;
  struct StringTable *stringTable;
  void *data;
};

typedef struct
{
  const char *name;
  int allocFlags;
  int freeFlags;
}XZoneInfo;

//Raw file asset defined here as it is so simple and used everywhere
struct RawFile
{
  const char *name;
  int len;
  const char *buffer;
};


void DB_GetVertexBufferAndOffset(unsigned char, void*, void*, int*);
void DB_GetIndexBufferAndBase(unsigned char, void*, void*, int*);
void DB_LoadedExternalData(int size);
void DB_LoadXAssets(XZoneInfo *zoneInfo, unsigned int zonecount, int sync);
void DB_SyncXAssets();
void DB_ShutdownXAssets();
void DB_BeginRecoverLostDevice();
void DB_EndRecoverLostDevice();
XAssetHeader DB_FindXAssetHeader(XAssetType assettype, char const* assetname);
XAssetHeader DB_FindXAssetHeader(XAssetType type, const char *name, bool errorIfMissing, int waitTime);


