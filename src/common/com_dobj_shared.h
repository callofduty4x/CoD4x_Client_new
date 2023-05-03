void Com_SafeClientDObjFree(int handle, int localClientNum);
void Com_ShutdownDObj();

#define DOBJ_MAX_SUBMODELS 32

/***************************************************************************
DObj types
****************************************************************************/
struct XModel;
struct XAnimTree_s;

/* 6916 */
struct DObjAnimMat
{
  float quat[4];
  float trans[3];
  float transWeight;
};

/* 7074 */
typedef struct 
{
  int anim[4];
  int control[4];
  int skel[4];
}DSkelPartBits;

/* 7075 */
struct DSkel
{
  DSkelPartBits partBits;
  int timeStamp;
  DObjAnimMat *mat;
};

/* 7076 */
#pragma pack(push, 2)
struct DObj_s
{
  XAnimTree_s *tree;
  uint16_t duplicateParts;
  uint16_t entnum;
  char duplicatePartsSize;
  char numModels;
  char numBones;
  byte pad;
  unsigned int ignoreCollision;
  volatile int locked;
  DSkel skel;
  float radius;
  int hidePartBits[4];
  XModel **models;
};
#pragma pack(pop)

#pragma pack(push, 2)
struct DObjModel_s
{
  XModel *model;
  uint16_t boneName;
  byte ignoreCollision;
  byte pad;
};
#pragma pack(pop)

