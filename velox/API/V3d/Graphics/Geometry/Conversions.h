/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_CONVERSIONS_2005_08_27_H
#define V3D_CONVERSIONS_2005_08_27_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Math/VVectorOps.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <iostream>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

math::VVector3f ToVector3f(const VColor4f& in_Color);
math::VVector4f ToVector4f(const VColor4f& in_Color);

VColor4f ToColor4f(const math::VVector4f& in_Vec);


inline std::ostream& operator<<(std::ostream& str, const graphics::VColor4f& color)
{
	math::VVector4f vec = ToVector4f(color);
	str << vec;
	return str;
}

inline std::istream& operator>>(std::istream& str, graphics::VColor4f& color)
{
	math::VVector4f vec;
	str >> vec;
	color = ToColor4f(vec);
	return str;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_CONVERSIONS_2005_08_27_H


