#ifndef V3D_VPLANE3F_H
#define V3D_VPLANE3F_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Utils/Graphics/VVector3f.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A plane consisting of a vertex and distance to coordinate system
 * @author ins
 */

struct VPlane3f
{
	VVector3f m_Normal;
	vfloat32 m_fDistance;

	VPlane3f()
	{
		m_fDistance = 0;
	}

	VPlane3f(vfloat32 in_X, vfloat32 in_Y, vfloat32 in_Z, vfloat32 in_Distance)
	{
		m_Normal.v[0] = in_X;
		m_Normal.v[1] = in_Y;
		m_Normal.v[2] = in_Z;

		m_fDistance = in_Distance;
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPLANE3F_H

