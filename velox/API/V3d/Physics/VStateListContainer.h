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