#ifndef V3D_VPHYSICGEOMETRYSPHERE_2004_11_07_H
#define V3D_VPHYSICGEOMETRYSPHERE_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3dLib/Physics/VPhysicGeometry.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
class VPhysicSpace;

class VPhysicGeometrySphere : public VPhysicGeometry
{
public:

	VPhysicGeometrySphere();
	virtual ~VPhysicGeometrySphere();

	void CreateSphere(VPhysicSpace* in_SpaceState);
	void SetSphereRadius(vfloat32 in_fRadius);
	vfloat32 GetSphereRadius();
	
private:

	VPhysicGeometrySphere(const VPhysicGeometrySphere&);
	VPhysicGeometrySphere& operator=(const VPhysicGeometrySphere&);
    
	vfloat32 m_fRadius;
};


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICGEOMETRYSPHERE_2004_11_07_H
