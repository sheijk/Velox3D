/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VStateBoxMass.h>
#include <V3d/Physics/VBody.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VStateBoxMass::VStateBoxMass(VState::Parent in_pParent) : VState(in_pParent)
{
	m_fHeight	= 1.0f;
	m_fWidth	= 1.0f;
	m_fLength	= 1.0f;
}

VStateBoxMass::~VStateBoxMass()
{
}

void VStateBoxMass::Apply()
{
	dMassSetBox (&m_Mass, GetDensity(), m_fLength , m_fWidth ,m_fHeight);
	dMassAdjust (&m_Mass, GetMass());

	VState::Parent parent = GetParent();

	V3D_ASSERT(parent != 0);

	dBodySetMass (parent->GetBodyID(), &m_Mass);
}

void VStateBoxMass::SetLength(vfloat32 in_fLength)
{
	m_fLength = in_fLength;
}

void VStateBoxMass::SetWidth(vfloat32 in_fWidth)
{
	m_fWidth = in_fWidth;
	//UpdateState();
}

void VStateBoxMass::SetHeight(vfloat32 in_fHeight)
{
	m_fHeight = in_fHeight;
	//UpdateState();
}

vfloat32 VStateBoxMass::GetHeight()
{
	return m_fHeight;
}

vfloat32 VStateBoxMass::GetLength()
{
	return m_fLength;
}

vfloat32 VStateBoxMass::GetWidth()
{
	return m_fWidth;
}

void VStateBoxMass::SetTotalMass()
{
	
	//VState::Parent parent = static_cast<VState::Parent>(GetParent());
	
	dMassSetBoxTotal(
		&m_Mass,
		GetTotalMass(),
		m_fWidth,
		m_fHeight,
		m_fLength
		); 
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------


