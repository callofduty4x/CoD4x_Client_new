#include "../q_shared.h"

/*
=================
AnglesToAxis
=================
*/

void AnglesToAxis(const vec3_t angles, vec3_t axis[3])
{
  float cy;
  float angle;
  float sr;
  float sp;
  float cr;
  float cp;
  float sy;

  angle = angles[1] * 0.017453292;
  sincosf(angle, &sy, &cy);
  angle = angles[0] * 0.017453292;
  sincosf(angle, &sp, &cp);
  angle = angles[2] * 0.017453292;
  sincosf(angle, &sr, &cr);

  axis[0][0] = cp * cy;
  axis[0][1] = cp * sy;
  axis[0][2] = -sp;
  axis[1][0] = sr * sp * cy - sy * cr;
  axis[1][1] = sr * sp * sy + cr * cy;
  axis[1][2] = sr * cp;
  axis[2][0] = cr * sp * cy + (-sr) * (-sy);
  axis[2][1] = cr * sp * sy - sr * cy;
  axis[2][2] = cr * cp;
}

void AxisToQuat(const vec3_t mat[3], float *out)
{
  float invLength;
  float test[4][4];
  int best;
  float testSizeSq;

  test[0][0] = mat[1][2] - mat[2][1];
  test[0][1] = mat[2][0] - mat[0][2];
  test[0][2] = mat[0][1] - mat[1][0];
  test[0][3] = mat[0][0] + mat[1][1] + mat[2][2] + 1.0;
  testSizeSq = Vec4LengthSq(test[0]);
  if ( testSizeSq < 1.0 )
  {
    test[1][0] = mat[2][0] + mat[0][2];
    test[1][1] = mat[2][1] + mat[1][2];
    test[1][2] = mat[2][2] - mat[1][1] - mat[0][0] + 1.0;
    test[1][3] = test[0][2];
    testSizeSq = Vec4LengthSq(test[1]);
    if ( testSizeSq < 1.0 )
    {
      test[2][0] = mat[0][0] - mat[1][1] - mat[2][2] + 1.0;
      test[2][1] = mat[1][0] + mat[0][1];
      test[2][2] = test[0][0];
      test[2][3] = test[1][0];
      testSizeSq = Vec4LengthSq(test[2]);
      if ( testSizeSq < 1.0 )
      {
        test[3][0] = test[2][1];
        test[3][1] = mat[1][1] - mat[0][0] - mat[2][2] + 1.0;
        test[3][2] = test[0][1];
        test[3][3] = test[1][1];
        testSizeSq = Vec4LengthSq(test[3]);
        assertx(testSizeSq >= 1.0f, "(testSizeSq) = %g", testSizeSq);
        best = 3;
      }
      else
      {
        best = 2;
      }
    }
    else
    {
      best = 1;
    }
  }
  else
  {
    best = 0;
  }

  assert(testSizeSq);

  invLength = 1.0 / sqrt(testSizeSq);

  VectorScale4(test[best], invLength, out);

}

void AnglesToQuat(const float *angles, float *quat)
{
  vec3_t axis[3];

  AnglesToAxis(angles, axis);
  AxisToQuat(axis, quat);
}
