#ifndef V3D_VRECT3D_2005_12_27_H
#define V3D_VRECT3D_2005_12_27_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VVectorOps.h>
#include <V3d/Math/VPlane.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace math {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

struct VRect3D
{
	VVector3f right;
	VVector3f up;
	vfloat32 distance;

	VVector3f GetNormal() const { return Normalized(Cross(right, up)); }
	VVector3f GetPosition() const { return GetNormal() * distance; }
	VPlane GetPlane() const { return VPlane(GetNormal(), distance); }
};

//-----------------------------------------------------------------------------
}} // namespace v3d::math
//-----------------------------------------------------------------------------
#endif // V3D_VRECT3D_2005_12_27_H
