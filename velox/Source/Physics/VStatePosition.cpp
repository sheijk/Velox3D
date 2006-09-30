/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Physics/VStatePosition.h>
#include <v3d/Core.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VStatePosition::VStatePosition(VState::Parent in_pParent) : VState(in_pParent)
{
	m_Position[0] = 0.0f;
	m_Position[1] = 0.0f;
	m_Position[2] = 0.0f;
}

VStatePosition::~VStatePosition()
{
}

void VStatePosition::SetPosition(math::VVector3f in_Position)
{
	m_Position = in_Position;
}

void VStatePosition::SetPosition(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Position[0] = x;
	m_Position[1] = y;
	m_Position[2] = z;
}

math::VVector3f VStatePosition::GetPositon()
{
	return m_Position;
}

void VStatePosition::Apply()
{
	VState::Parent pParent = static_cast<VState::Parent>(GetParent());
    dBodySetPosition(*(pParent->GetBodyID()),m_Position[0], m_Position[1], m_Position[2]);
}

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

