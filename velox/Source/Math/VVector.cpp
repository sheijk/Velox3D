#include <V3d/Math/VVector.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

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

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
