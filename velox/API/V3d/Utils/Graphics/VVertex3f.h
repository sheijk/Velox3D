#ifndef V3D_VVERTEX3F_H
#define V3D_VVERTEX3F_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

//TODO: frage: wie konvertierung zu VVector<float, 3>? oder alternative
// um cross, etc fkten zu implementiern?
struct VVertex3f
{
	vfloat32 v[3];

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
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEX3F_H
