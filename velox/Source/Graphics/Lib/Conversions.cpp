#include <V3dLib/Graphics/Geometry/Conversions.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VVector4f ToVector4f(const VVector3f& in_Vec, vfloat32 in_fW)
{
	VVector4f vec;
	vec[0] = in_Vec[0];
	vec[1] = in_Vec[1];
	vec[2] = in_Vec[2];
	vec[3] = in_fW;

	return vec;
}

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

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
