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

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_NUMERICS_2004_04_09_H
