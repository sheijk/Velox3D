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

