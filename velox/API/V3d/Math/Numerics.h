#ifndef V3D_NUMERICS_2004_04_09_H
#define V3D_NUMERICS_2004_04_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d;

inline vfloat32 RadianToDegree(vfloat32 radian);
inline vfloat32 DegreeToRadian(vfloat32 degree);

inline vfloat32 Pi();
inline float PseudoRandom(vuint x);

/**
 * Returns the interpolation between the two values
 * 0 means returning a, 1 means returning b, .5 means a/2 + b/2, etc
 */
template<typename T>
T Interpolate(T a, T b, vfloat32 factor);

//-----------------------------------------------------------------------------
//TODO: move to .inl

inline vfloat32 DegreeToRadian(vfloat32 degree)
{
	return degree / 180.0f * Pi();
}

inline vfloat32 RadianToDegree(vfloat32 radian)
{
	return radian * 180.0f / Pi();
}

inline vfloat32 Pi()
{
	return 3.1415f;
}

template<typename T>
T Interpolate(T a, T b, vfloat32 factor)
{
	return ((1 - factor) * a) + (factor * b);
}

inline float PseudoRandom(vuint x)
{
	x = (x<<13) ^ x;
    return ( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_NUMERICS_2004_04_09_H
