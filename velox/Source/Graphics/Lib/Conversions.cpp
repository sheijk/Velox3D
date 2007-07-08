/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/Geometry/Conversions.h>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------

namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

VVector3f ToVector3f(const VColor4f& in_Color)
{
	VVector3f vec;
	vec[0] = in_Color.red;
	vec[1] = in_Color.green;
	vec[2] = in_Color.blue;

	return vec;
}

VVector4f ToVector4f(const VColor4f& in_Color)
{
	VVector4f vec;
	vec[0] = in_Color.red;
	vec[1] = in_Color.green;
	vec[2] = in_Color.blue;
	vec[3] = in_Color.alpha;

	return vec;
}

VColor4f ToColor4f(const VVector4f& in_Vec)
{
	VColor4f color;
	color.red = in_Vec[0];
	color.green = in_Vec[1];
	color.blue = in_Vec[2];
	color.alpha = in_Vec[3];
	return color;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

