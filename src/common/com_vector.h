#include "../q_shared.h"

static inline void Vec3Cross(const float *v0, const float *v1, float *cross)
{
    assert(v0 != cross);
    assert(v1 != cross);

    cross[0] = v0[1] * v1[2] - v0[2] * v1[1];
    cross[1] = v0[2] * v1[0] - v0[0] * v1[2];
    cross[2] = v0[0] * v1[1] - v0[1] * v1[0];
}

static inline vec_t VectorLengthSquared( const vec3_t v )
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}
