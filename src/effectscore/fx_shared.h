
struct FxEffectDef;
FxEffectDef* FX_Register(const char *name);
unsigned int FX_SpawnOrientedEffect(int localClientNum, const FxEffectDef *def, int msecBegin, const float *origin, const float (*axis)[3], unsigned int markEntnum);