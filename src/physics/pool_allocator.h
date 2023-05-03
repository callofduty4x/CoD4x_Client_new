
#ifndef __POOL_ALLOCATOR_H__
#define __POOL_ALLOCATOR_H__

struct pooldata_t
{
  void *firstFree;
  int activeCount;
};

void ** Pool_Alloc(pooldata_t *pooldata);
void Pool_Init(void *pool, pooldata_t *pooldata, unsigned int itemSize, unsigned int itemCount);
void Pool_Free(void *data, pooldata_t *pooldata);

#endif