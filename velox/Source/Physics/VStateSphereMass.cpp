/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VStateSphereMass.h>
#include <V3d/Physics/VBody.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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
	VState::Parent pParent = GetParent();

	dMassSetSphere (&m_Mass, GetDensity(), m_fRadius);
	dMassAdjust (&m_Mass, GetMass());
	dBodySetMass (pParent->GetBodyID(),&m_Mass);
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


