#ifndef V3D_VPHYSICSPHEREMASSSTATE_16_11_04_H
#define V3D_VPHYSICSPHEREMASSSTATE_16_11_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Physics/VPhysicMass.h>
#include <V3dLib/Physics/VPhysicState.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a sphere mass state
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VPhysicSphereMassState : public VPhysicMass, public VPhysicState
{
public:
	
	VPhysicSphereMassState();
	virtual ~VPhysicSphereMassState();

	/**
	 * Sets the radius of this spherical mass abstraction
	 */
	void SetRadius(vfloat32 in_fRadius);

	/**
	 * Returns the assigned mass of this object
	 */
	vfloat32 GetRadius();

private:

	virtual void Apply();

	vfloat32 m_fRadius;
	
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICSPHEREMASSSTATE_16_11_04_H
