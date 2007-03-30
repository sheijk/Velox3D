/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VJointGroup.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VJointGroup::VJointGroup()
{
	m_JointGroupID = dJointGroupCreate(0);
}

VJointGroup::~VJointGroup()
{
//	Destroy();
}

void VJointGroup::Destroy()
{
	dJointGroupDestroy(m_JointGroupID);
}

void VJointGroup::Empty()
{
	dJointGroupEmpty(m_JointGroupID);
}

dJointGroupID* VJointGroup::GetJointGroupID()
{
	return &m_JointGroupID;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------


