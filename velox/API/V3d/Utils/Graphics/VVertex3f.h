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
	float x;
	float y;
	float z;

	VVertex3f()
	{
		x = y = z = 0;
	}

	VVertex3f(float in_X, float in_Y, float in_Z)
	{
		x = in_X;
		y = in_Y;
		z = in_Z;
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEX3F_H
