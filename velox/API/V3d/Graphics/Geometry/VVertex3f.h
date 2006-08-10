#ifndef V3D_VVERTEX3F_H
#define V3D_VVERTEX3F_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Math/VVector.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

//TODO: frage: wie konvertierung zu VVector<float, 3>? oder alternative
// um cross, etc fkten zu implementiern?
struct VVertex3f
{
	union
	{
		vfloat32 v[3];
		struct 
		{
			vfloat32 x, y, z;
		};
	};

	VVertex3f()
	{
		v[0] = v[1] = v[2] = 0;
	}

	VVertex3f(float in_X, float in_Y, float in_Z)
	{
		v[0] = in_X;
		v[1] = in_Y;
		v[2] = in_Z;
	}

	VVector3f AsVector() const
	{
		return VVector3f(x, y, z);
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEX3F_H