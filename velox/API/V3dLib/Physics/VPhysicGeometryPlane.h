#ifndef V3D_VPHYSICGEOMETRYPLANE_2004_11_07_H
#define V3D_VPHYSICGEOMETRYPLANE_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3dLib/Physics/VPhysicGeometry.h>
#include <v3dLib//Graphics/Geometry/VVertex3f.h>
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
	void SetPlane(graphics::VVertex3f in_Normal, vfloat32 in_fDistance);
	vfloat32 GetPlaneDistance();
	graphics::VVertex3f GetPlaneNormal();

private:

	VPhysicGeometryPlane(const VPhysicGeometryPlane&);
	VPhysicGeometryPlane& operator=(const VPhysicGeometryPlane&);
	
	graphics::VVertex3f m_Normal;
	vfloat32 m_fDistance;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICGEOMETRYPLANE_2004_11_07_H
