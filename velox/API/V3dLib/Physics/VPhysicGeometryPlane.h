#ifndef V3D_VPHYSICGEOMETRYPLANE_2004_11_07_H
#define V3D_VPHYSICGEOMETRYPLANE_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3dLib/Physics/VPhysicGeometry.h>
#include <V3dLib/Graphics/Geometry/VVector3f.h>
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

class VPhysicSpace;

class VPhysicGeometryPlane : public VPhysicGeometry
{
public:

	VPhysicGeometryPlane();
	virtual ~VPhysicGeometryPlane();

	void CreatePlane(VPhysicSpace* in_SpaceState);
	void SetPlane(graphics::VVector3f in_Normal, vfloat32 in_fDistance);
	vfloat32 GetPlaneDistance();
	graphics::VVector3f GetPlaneNormal();

private:

	VPhysicGeometryPlane(const VPhysicGeometryPlane&);
	VPhysicGeometryPlane& operator=(const VPhysicGeometryPlane&);
	
	graphics::VVector3f m_Normal;
	vfloat32 m_fDistance;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICGEOMETRYPLANE_2004_11_07_H
