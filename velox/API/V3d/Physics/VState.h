#ifndef V3D_VSTATE_27_10_04_H
#define V3D_VSTATE_27_10_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Physics/VOdeBody.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a physic state
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VBody;

class VState
{
public:
	typedef VOdeBody* Parent;
	
	VState(Parent in_pParent);
	virtual ~VState();

	/**
	 * Returns the Parent container of this state
	 * Returns 0 if no Parent is set
	 */
    Parent GetParent();
	//void SetParent(StateListContainerPtr in_Parent);




	/**
	 * Override this method to add functionality
	 */
    virtual void Apply() = 0;

	///**
	//* notifies the VStateListContainer to update all
	//* elements
	//*/

	//virtual void Update();

protected:

	Parent m_Parent;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTATE_27_10_04_H
