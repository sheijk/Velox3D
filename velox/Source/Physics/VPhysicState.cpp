#include <v3dLib/Physics/VPhysicState.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VPhysicState::VPhysicState()
{
	m_Parent = 0;
}

VPhysicState::~VPhysicState()
{
}

void VPhysicState::SetParent(VPhysicObject* in_Object)
{
	m_Parent = in_Object;
}

VPhysicObject* VPhysicState::GetParent()
{
	return m_Parent;
}

void VPhysicState::UpdateState()
{
	VPhysicObject* objPtr = GetParent();

	V3D_ASSERT(objPtr != 0);
	
	if(objPtr)
        objPtr->AddState(this);
}


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

