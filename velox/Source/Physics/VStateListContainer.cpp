/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
}

VStateListContainer::~VStateListContainer()
{
  ClearStates();
}
void VStateListContainer::ClearStates()
{
  typedef StateList::iterator ListIter;

  ListIter itBegin = m_StateList.begin();
  ListIter itEnd = m_StateList.end();

  for(; itBegin != itEnd; ++itBegin)
  {
	delete (*itBegin);
  }
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

