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
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
	m_Position.z = 0.0f;
}

VStatePosition::~VStatePosition()
{
}

void VStatePosition::SetPosition(graphics::VVertex3f in_Position)
{
	m_Position = in_Position;
}

void VStatePosition::SetPosition(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

graphics::VVertex3f VStatePosition::GetPositon()
{
	return m_Position;
}

void VStatePosition::Apply()
{
	VState::Parent pParent = static_cast<VState::Parent>(GetParent());
    dBodySetPosition(*(pParent->GetBodyID()),m_Position.x, m_Position.y, m_Position.z);
}

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

