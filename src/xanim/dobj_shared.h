struct DObj_s;
struct DObjModel_s;
struct XAnimTree_s;

void DObjShutdown();
void Com_SafeServerDObjFree(int handle);
DObj_s * Com_ServerDObjCreate(DObjModel_s *dobjModels, uint16_t numModels, XAnimTree_s *tree, int handle);
void DObjSetHidePartBits(DObj_s *obj, const unsigned int *partBits);
void DObjInit();
