#include <v3dLib/Physics/VPhysicMass.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VPhysicMass::VPhysicMass()
{
	m_fDensity = 1.0f;
	m_fMass = 1.0f;
}
VPhysicMass::~VPhysicMass()
{
}

void VPhysicMass::SetDensity(vfloat32 in_fDensity)
{
	m_fDensity = in_fDensity;
}

vfloat32 VPhysicMass::GetDensity()
{
	return m_fDensity;
}

void VPhysicMass::SetMass(vfloat32 in_fMass)
{
	m_fMass = in_fMass;
}

vfloat32 VPhysicMass::GetMass()
{
	return m_fMass;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

