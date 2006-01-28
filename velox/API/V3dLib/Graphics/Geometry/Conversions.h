#ifndef V3D_CONVERSIONS_2005_08_27_H
#define V3D_CONVERSIONS_2005_08_27_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VVectorOps.h>

#include <V3dLib/Graphics/Geometry/VColor4f.h>
#include <iostream>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/** Returns in_Vec[0-2]/in_Vec[3] */
VVector3f DeHomogenize(const VVector4f& in_Vec);

VVector4f ToVector4f(const VVector3f& in_Vec, vfloat32 in_fW);

VVector3f ToVector3f(const VColor4f& in_Color);
VVector4f ToVector4f(const VColor4f& in_Color);

VColor4f ToColor4f(const VVector4f& in_Vec);


inline std::ostream& operator<<(std::ostream& str, const graphics::VColor4f& color)
{
	VVector4f vec = ToVector4f(color);
	str << vec;
	return str;
}

inline std::istream& operator>>(std::istream& str, graphics::VColor4f& color)
{
	VVector4f vec;
	str >> vec;
	color = ToColor4f(vec);
	return str;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_CONVERSIONS_2005_08_27_H

