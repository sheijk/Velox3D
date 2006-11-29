/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Physics/VStateCCylinderMass.h>
#include <v3d/Physics/VBody.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VStateCCylinderMass::VStateCCylinderMass(VState::Parent in_pParent) : VState(in_pParent)
{
	m_fRadius	= 1.0f;
	m_iDirection = 1;
}

VStateCCylinderMass::~VStateCCylinderMass()
{
}

void VStateCCylinderMass::Apply()
{
	VState::Parent pParent = static_cast<VState::Parent>(GetParent());

	dMassSetCappedCylinder(&m_Mass, GetDensity(), m_iDirection, m_fRadius, m_fLength);
	dMassAdjust (&m_Mass, GetMass());
	dBodySetMass (*pParent->GetBodyID(),&m_Mass);
}

vfloat32 VStateCCylinderMass::GetRadius()
{
	return m_fRadius;
}

vfloat32 VStateCCylinderMass::GetLength()
{
  return m_fLength;
}

vuint VStateCCylinderMass::GetDirection()
{
  return m_iDirection;
}

void VStateCCylinderMass::SetDirection(vuint in_iDirection)
{
  m_iDirection = in_iDirection;
}

void VStateCCylinderMass::SetRadius(vfloat32 in_fRadius)
{
	m_fRadius = in_fRadius;
}

void VStateCCylinderMass::SetLength(vfloat32 in_fLength)
{
  m_fLength = in_fLength;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------


