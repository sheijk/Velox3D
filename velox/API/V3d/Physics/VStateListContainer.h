/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_PHYSICOBJECT_05_11_04_H
#define V3D_PHYSICOBJECT_05_11_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
class VState;

/**
 * Container that contains only states
 * that will be traversed and applied
 *
 * note: The container takes no ownership of
 *		 the pointers. Thus they will not be
 *		 deallocated.
 *
 * author: ins
 */
class VStateListContainer
{
public:


	VStateListContainer();
	virtual ~VStateListContainer();

	void RegisterForUpdate(VState* in_pState);
	void UnregisterForUpdate(VState* in_pState);
	void ClearStates();
	virtual void Update();

protected:
	typedef std::list<VState*> StateList;

	StateList m_StateList;
};


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_PHYSICOBJECT_05_11_04_H

