#include <v3dLib/Physics/VPhysicGeometrySphere.h>
#include <v3dLib/Physics/VPhysicSpace.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VPhysicGeometrySphere::VPhysicGeometrySphere()
{
}

VPhysicGeometrySphere::~VPhysicGeometrySphere()
{
}

void VPhysicGeometrySphere::CreateSphere(VPhysicSpace* in_SpaceState)
{
	m_GeomID = dCreateSphere (*in_SpaceState->GetSpaceID(), m_fRadius);
}

void VPhysicGeometrySphere::SetSphereRadius(vfloat32 in_fRadius)
{
	m_fRadius = in_fRadius;
}

vfloat32 VPhysicGeometrySphere::GetSphereRadius()
{
	return m_fRadius;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
