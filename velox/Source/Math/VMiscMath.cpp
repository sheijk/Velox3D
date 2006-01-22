#include <V3d/Math/VQuaternionOps.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

void Rotate(VVector3f& io_Vector, const VQuatf& in_Rotation)
{
	VQuatf v(io_Vector[0], io_Vector[1], io_Vector[2], 1.0f);
	VQuatf neg(in_Rotation);
	Invert(neg);

	VQuatf res = in_Rotation * v * neg;

	io_Vector[0] = res[0];
	io_Vector[1] = res[1];
	io_Vector[2] = res[2];
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
