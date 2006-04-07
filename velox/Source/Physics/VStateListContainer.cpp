//-----------------------------------------------------------------------------
#include <V3d/Physics/VStateListContainer.h>
#include <V3d/Physics/VState.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------

VStateListContainer::VStateListContainer()
{
	typedef StateList::iterator ListIter;

	ListIter itBegin = m_StateList.begin();
	ListIter itEnd = m_StateList.end();

	for(; itBegin != itEnd; ++itBegin)
	{
		delete (*itBegin);
	}
}

VStateListContainer::~VStateListContainer()
{
}


void VStateListContainer::RegisterForUpdate(VState* in_pState)
{
	m_StateList.push_back(in_pState);
	Update();
}

void VStateListContainer::UnregisterForUpdate(VState* in_pState)
{
	m_StateList.remove(in_pState);
	Update();
}

void VStateListContainer::Update()
{
	typedef StateList::iterator ListIter;

	ListIter itBegin = m_StateList.begin();
	ListIter itEnd = m_StateList.end();

	for(; itBegin != itEnd; ++itBegin)
	{
		(*itBegin)->Apply();
	}
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
