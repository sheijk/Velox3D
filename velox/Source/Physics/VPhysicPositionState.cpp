#include <v3dLib/Physics/VPhysicBody.h>
#include <v3dLib/Physics/VPhysicPositionState.h>
#include <v3d/Core.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VPhysicPositionState::VPhysicPositionState()
{
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
	m_Position.z = 0.0f;
}

VPhysicPositionState::~VPhysicPositionState()
{
}

void VPhysicPositionState::SetPosition(graphics::VVector3f in_Position)
{
	m_Position = in_Position;
	//UpdateState();
}

void VPhysicPositionState::SetPosition(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;

	//UpdateState();
}

void VPhysicPositionState::Apply()
{
	VPhysicBody* obj = static_cast<VPhysicBody*>(GetParent());
    dBodySetPosition(*(obj->GetBodyID()),m_Position.x, m_Position.y, m_Position.z);
}

graphics::VVector3f VPhysicPositionState::GetPositon()
{
	return m_Position;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
