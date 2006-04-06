#ifndef V3D_VJOINTGROUP_2004_11_07_H
#define V3D_VJOINTGROUP_2004_11_07_H
//-----------------------------------------------------------------------------
#include <ode/ode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a joint group needed for collisions
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VJointGroup
{
public:

	VJointGroup();
	virtual ~VJointGroup();
	
	/**
	 * Destroys this group
	 */
	void Destroy();
	/**
	 * Just empties the group without destroying it
	 * @note: call this EACH FRAME for correct physic simulation
	 */
	void Empty();

	dJointGroupID* GetJointGroupID();


private:

	VJointGroup(const VJointGroup&);
	VJointGroup& operator=(const VJointGroup&);

	dJointGroupID m_JointGroupID;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VJOINTGROUP_2004_11_07_H
