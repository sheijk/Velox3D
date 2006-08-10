#ifndef V3D_VTEXCOORD2F_H
#define V3D_VTEXCOORD2F_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

struct VTexCoord2f
{
	float u, v;

	VTexCoord2f()
	{
		u = v = 0;
	}

	VTexCoord2f(float inU, float inV)
	{
		u = inU;
		v = inV;
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTEXCOORD2F_H