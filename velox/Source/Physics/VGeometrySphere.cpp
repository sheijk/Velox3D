#include <v3d/Physics/VGeometrySphere.h>
#include <v3d/Physics/VSpace.h>
#include <V3d/Core.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VGeometrySphere::VGeometrySphere()
{
}

VGeometrySphere::~VGeometrySphere()
{
}

void VGeometrySphere::CreateSphere(VSpace* in_SpaceState)
{
	V3D_ASSERT(in_SpaceState != 0);
	m_GeomID = dCreateSphere (*in_SpaceState->GetSpaceID(), m_fRadius);
}

void VGeometrySphere::SetSphereRadius(vfloat32 in_fRadius)
{
	m_fRadius = in_fRadius;
}

vfloat32 VGeometrySphere::GetSphereRadius()
{
	return m_fRadius;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
