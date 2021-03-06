/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VNORMAL3F_2005_02_26_H
#define V3D_VNORMAL3F_2005_02_26_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VVector.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

struct VNormal3f
{
	union
	{
		vfloat32 v[3];
		struct 
		{
			vfloat32 x, y, z;
		};
	};

	VNormal3f()
	{
		v[0] = v[1] = v[2] = 0;
	}

	VNormal3f(float in_X, float in_Y, float in_Z)
	{
		Set(in_X, in_Y, in_Z);
	}

	explicit VNormal3f(const math:: VVector3f& vec)
	{
		v[0] = vec[0];
		v[1] = vec[1];
		v[2] = vec[2];
	}

	void Set(float in_X, float in_Y, float in_Z)
	{
		v[0] = in_X;
		v[1] = in_Y;
		v[2] = in_Z;
	}

	math::VVector3f AsVector() const
	{
		return math::VVector3f(x, y, z);
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VNORMAL3F_2005_02_26_H

