/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Physics/VState.h>
#include <V3d/Physics/VBody.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VState::VState(Parent in_pParent)
{
	m_Parent = in_pParent;
}

VState::~VState()
{
}

//void VState::SetOwner(VState::Owner in_Object)
//{
//	m_Owner = in_Object;
//}

VState::Parent VState::GetParent()
{
	return m_Parent;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------


