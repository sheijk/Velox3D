#ifndef V3D_VSTATESPHEREMASS_16_11_04_H
#define V3D_VSTATESPHEREMASS_16_11_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Physics/VMass.h>
#include <V3d/Physics/VState.h>
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

class VStateSphereMass : public VMass, public VState
{
public:
	
	VStateSphereMass(VState::Parent in_pParent);
	virtual ~VStateSphereMass();

	/**
	 * Sets the radius of this spherical mass abstraction
	 */
	void SetRadius(vfloat32 in_fRadius);

	/**
	 * Returns the assigned mass of this object
	 */
	vfloat32 GetRadius();
	virtual void Apply();

private:

	

	vfloat32 m_fRadius;
	
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTATESPHEREMASS_16_11_04_H
