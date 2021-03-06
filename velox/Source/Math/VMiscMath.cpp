/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Math/VQuaternionOps.h>
//-----------------------------------------------------------------------------
#include <V3d/Math/VMatrixOps.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

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

std::ostream& operator<<(std::ostream& str, const VMatrix44f& matrix)
{
	for(vuint row = 0; row < 4; ++row)
		for(vuint column = 0; column < 4; ++column)
		{
			str << matrix.Get(row, column) << " ";
		}

		return str;
}

std::istream& operator>>(std::istream& str, VMatrix44f& matrix)
{
	for(vuint row = 0; row < 4; ++row)
		for(vuint column = 0; column < 4; ++column)
		{
			vfloat32 val;
			str >> val;
			matrix.Set(row, column, val);
		}

		return str;
}

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------

