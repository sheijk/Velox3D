#ifndef V3D_VCOLOR4F_H
#define V3D_VCOLOR4F_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A color consisting of 4 float values
 */
struct VColor4f
{
	float red;
	float green;
	float blue;
	float alpha;

	VColor4f()
	{
		red = green = blue = alpha = 0;
	}

	VColor4f(float in_Red, float in_Green, float in_Blue, float in_Alpha)
	{
		red = in_Red;
		green = in_Green;
		blue = in_Blue;
		alpha = in_Alpha;
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCOLOR4F_H

