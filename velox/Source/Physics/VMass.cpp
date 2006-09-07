/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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


