struct DObj_s;
struct XModel;
struct XAnimTree_s;



enum itemType_t 
{
  IT_BAD = 0x0,
  IT_WEAPON = 0x1,
};

struct gitem_s
{
  itemType_t giType;
};


#pragma pack(push, 4)
struct weaponInfo_s
{
  DObj_s *viewModelDObj;
  XModel *handModel;
  XModel *gogglesModel;
  XModel *rocketModel;
  XModel *knifeModel;
  char weapModelIdx;
  char pad[3];
  int partBits[4];
  int iPrevAnim;
  XAnimTree_s *tree;
  int registered;
  gitem_s *item;
  const char *translatedDisplayName;
  const char *translatedModename;
  const char *translatedAIOverlayDescription;
};
#pragma pack(pop)

extern weaponInfo_s cg_weaponsArray[1][128];

int CG_WeaponDObjHandle(int localClientNum);
void CG_RegisterWeapon(int localClientNum, int index);

/*
extern WeaponDef *bg_weaponDefs[];
extern weaponInfo_t cg_weaponsArray[];
extern Material* weaponHudIcons[];
WeaponDef* BG_GetWeaponDef(int index);
int BG_PlayerWeaponCountPrimaryTypes(playerState_t *ps);
int BG_GetNumWeapons();
void ChangeViewmodelDObj(int localClientNum, int weaponNum, char weaponModel, XModel *newHands, XModel *newGoggles, XModel *newRocket, XModel *newKnife, byte updateClientInfo);
*/