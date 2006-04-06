#include <v3d/Physics/VJointGroup.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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

