#ifndef V3D_VGEOMETRYPLANE_2004_11_07_H
#define V3D_VGEOMETRYPLANE_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3d/Physics/VGeometry.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a geometrical plane for ode
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VSpace;

class VGeometryPlane : public VGeometry
{
public:

	VGeometryPlane();
	virtual ~VGeometryPlane();

	void CreatePlane(VSpace* in_SpaceState);
	void SetPlane(graphics::VVertex3f in_Normal, vfloat32 in_fDistance);
	vfloat32 GetPlaneDistance();
	graphics::VVertex3f GetPlaneNormal();

private:

	VGeometryPlane(const VGeometryPlane&);
	VGeometryPlane& operator=(const VGeometryPlane&);
	
	graphics::VVertex3f m_Normal;
	vfloat32 m_fDistance;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGEOMETRYPLANE_2004_11_07_H
