//-----------------------------------------------------------------------------
#include <v3dLib/Physics/VPhysicObject.h>
#include <v3dLib/Physics/VPhysicState.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------

VPhysicObject::VPhysicObject()
{
}

VPhysicObject::~VPhysicObject()
{
}


void VPhysicObject::AddState(VPhysicState* in_State)
{
	//delete it if object is in static list
	m_StaticStateList.remove(in_State);

	in_State->SetParent(this);
	m_DynamicStateList.push_back(in_State);
	
	Apply();
}

void VPhysicObject::DeleteState(VPhysicState* in_State)
{
	// we don't know where state is currently listed thus remove it everywhere
	m_StaticStateList.remove(in_State);
	m_DynamicStateList.remove(in_State);

	Apply();
}

void VPhysicObject::Apply()
{
	typedef std::list<VPhysicState*>::iterator ListIter;

	ListIter itBegin = m_DynamicStateList.begin();
	ListIter itEnd = m_DynamicStateList.end();

	for(; itBegin != itEnd; ++itBegin)
	{
		(*itBegin)->Apply();
		
		//move to static container because its applied
		m_StaticStateList.push_back(*itBegin);
	}

	itBegin = m_DynamicStateList.begin();
    
    m_DynamicStateList.clear();
	

	
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
