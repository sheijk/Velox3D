#include "VRigidBodyPart.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace racer {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VRigidBodyPart::VRigidBodyPart()
{
	m_Position.Set(0, 0.0f);
	m_Position.Set(1, 0.0f);
	m_Position.Set(2, 0.0f);
}

void VRigidBodyPart::Activate()
{
}

void VRigidBodyPart::Deactivate()
{
}											 

VRigidBodyPart::PositionVector VRigidBodyPart::GetPosition() const
{
	return m_Position;
}

void VRigidBodyPart::SetPosition(const PositionVector& in_NewPos)
{
	m_Position = in_NewPos;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::racer
//-----------------------------------------------------------------------------
