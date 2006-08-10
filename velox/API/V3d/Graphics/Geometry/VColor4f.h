#ifndef V3D_VCOLOR4F_H
#define V3D_VCOLOR4F_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Math/VVector.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A color consisting of 4 float values
 */
struct VColor4f
{
	vfloat32 red;
	vfloat32 green;
	vfloat32 blue;
	vfloat32 alpha;

	VColor4f()
	{
		red = green = blue = alpha = 0;
	}

	VColor4f(vfloat32 in_Red, vfloat32 in_Green, vfloat32 in_Blue, vfloat32 in_Alpha)
	{
		red = in_Red;
		green = in_Green;
		blue = in_Blue;
		alpha = in_Alpha;
	}

	VColor4f(vfloat32 in_Red, vfloat32 in_Green, vfloat32 in_Blue)
	{
		red = in_Red;
		green = in_Green;
		blue = in_Blue;
		alpha = 1.0f;
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCOLOR4F_H

