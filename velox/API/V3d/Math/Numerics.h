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

/** Returns a pseudo random number between -1 and 1. Same x same result */
inline float PseudoRandom(vuint x);

/**
 * Returns the interpolation between the two values
 * 0 means returning a, 1 means returning b, .5 means a/2 + b/2, etc
 */
template<typename T>
T Interpolate(T a, T b, vfloat32 factor);

//-----------------------------------------------------------------------------
#include "Numerics.inl"
//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_NUMERICS_2004_04_09_H
