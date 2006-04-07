#include <v3d/Physics/VStateSphereMass.h>
#include <v3d/Physics/VBody.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VStateSphereMass::VStateSphereMass(VState::Parent in_pParent) : VState(in_pParent)
{
	m_fRadius	= 1.0f;
}

VStateSphereMass::~VStateSphereMass()
{
}

void VStateSphereMass::Apply()
{
	VState::Parent pParent = static_cast<VState::Parent>(GetParent());

	dMassSetSphere (&m_Mass, GetDensity(), m_fRadius);
	dMassAdjust (&m_Mass, GetMass());
	dBodySetMass (*pParent->GetBodyID(),&m_Mass);
}

vfloat32 VStateSphereMass::GetRadius()
{
	return m_fRadius;
}

void VStateSphereMass::SetRadius(vfloat32 in_fRadius)
{
	m_fRadius = in_fRadius;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

