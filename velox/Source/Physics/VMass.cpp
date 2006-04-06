#include <v3d/Physics/VMass.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VMass::VMass()
{
	m_fDensity = 1.0f;
	m_fMass = 1.0f;
	m_fTotalMass = 1.0f;
}
VMass::~VMass()
{
}

void VMass::SetDensity(vfloat32 in_fDensity)
{
	m_fDensity = in_fDensity;
}

vfloat32 VMass::GetDensity()
{
	return m_fDensity;
}

void VMass::SetMass(vfloat32 in_fMass)
{
	m_fMass = in_fMass;
}

vfloat32 VMass::GetMass()
{
	return m_fMass;
}

void VMass::SetTotalMass(vfloat32 in_fTotalMass)
{
	m_fTotalMass = in_fTotalMass;
}

vfloat32 VMass::GetTotalMass()
{
	return m_fTotalMass;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

