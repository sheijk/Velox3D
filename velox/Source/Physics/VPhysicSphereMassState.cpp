#include <v3dLib/Physics/VPhysicSphereMassState.h>
#include <v3dLib/Physics/VPhysicBody.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VPhysicSphereMassState::VPhysicSphereMassState() : VPhysicMass()
{
	m_fRadius	= 1.0f;
}

VPhysicSphereMassState::~VPhysicSphereMassState()
{
}

void VPhysicSphereMassState::Apply()
{
	dMassSetSphere (&m_Mass, GetDensity(), m_fRadius);
	dMassAdjust (&m_Mass, GetMass());

	VPhysicBody* obj = static_cast<VPhysicBody*>(GetParent());
	
	V3D_ASSERT(obj != 0);
	V3D_ASSERT(*obj->GetBodyID() != 0);

	dBodySetMass (*obj->GetBodyID(),&m_Mass);
}

vfloat32 VPhysicSphereMassState::GetRadius()
{
	return m_fRadius;
}

void VPhysicSphereMassState::SetRadius(vfloat32 in_fRadius)
{
	m_fRadius = in_fRadius;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

