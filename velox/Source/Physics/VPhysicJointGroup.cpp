#include <v3dLib/Physics/VPhysicJointGroup.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VPhysicJointGroup::VPhysicJointGroup()
{
	m_JointGroupID = dJointGroupCreate(0);
}

VPhysicJointGroup::~VPhysicJointGroup()
{
//	Destroy();
}

void VPhysicJointGroup::Destroy()
{
	dJointGroupDestroy(m_JointGroupID);
}

void VPhysicJointGroup::Empty()
{
	dJointGroupEmpty(m_JointGroupID);
}

dJointGroupID* VPhysicJointGroup::GetJointGroupID()
{
	return &m_JointGroupID;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

