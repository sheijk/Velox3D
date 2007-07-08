/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Math/VVector.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

VVector2f ToVector2f(float x, float y)
{
	VVector2f vec;
	vec[0] = x;
	vec[1] = y;
	return vec;
}

VVector3f ToVector3f(float x, float y, float z)
{
	VVector3f vec;
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	return vec;
}

VVector4f ToVector4f(float x, float y, float z, float w)
{
	VVector4f vec;
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = w;
	return vec;
}

VVector3f XYZToVector3f(const VVector4f& vec4)
{
	VVector3f result;

	for(vint i = 2; i >= 0; --i)
		result[i] = vec4[i];

	return result;
}

VVector3f DeHomogenize(const VVector4f& vec4)
{
	VVector3f result;

	for(vint i = 2; i >= 0; --i)
		result[i] = vec4[i] / vec4[3];

	return result;
}

VVector4f ToVector4f(const VVector3f& vec3, float w)
{
	VVector4f result;

	for(vint i = 2; i >= 0; --i)
		result[i] = vec3[i];

	result[3] = w;

	return result;
}

//-----------------------------------------------------------------------------
} 
} // namespace v3d
//-----------------------------------------------------------------------------

