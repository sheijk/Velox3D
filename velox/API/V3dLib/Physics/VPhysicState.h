#ifndef V3D_VPHYSICSTATE_27_10_04_H
#define V3D_VPHYSICSTATE_27_10_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <ode/ode.h>
#include "VPhysicObject.h"
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
class VPhysicState
{
public:

	VPhysicState();
	
	virtual ~VPhysicState();

	/**
	 * Returns the parent object of this state
	 * Returns 0 if no parent is set
	 */
    VPhysicObject* GetParent();
	void SetParent(VPhysicObject* in_Parent);


	/**
	 * This method has to be overwritten for each state.
	 * This wraps the ODE calls
	 */
    virtual void Apply() = 0;

	/**
	* Sets the parent of this state where it has to
	* be applied
	*/


protected:

	virtual void UpdateState();

	//TODO: declars as friend of object. client must not set this data!

	

	VPhysicObject* m_Parent;


};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICSTATE_27_10_04_H
