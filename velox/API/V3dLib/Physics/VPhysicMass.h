#ifndef V3D_VPHYSICMASS_27_10_04_H
#define V3D_VPHYSICMASS_27_10_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
#include <ode/ode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a physical mass
 *
 * @author: ins
 */

class VPhysicMass
{
public:
	
	virtual ~VPhysicMass();
	
	/**
	 * Returns the density of the mass
	 */
	vfloat32 GetDensity();
	
	/**
	 * Set density parameter
	 */
	void SetDensity(vfloat32 in_fDensity);
	
	/**
	 * Set mass of this object
	 */
	void SetMass(vfloat32 in_fMass);
	
	/**
	 * Returns assigned mass of this object
	 */
	vfloat32 GetMass();
    
protected:

	VPhysicMass();

	dMass m_Mass;
	
	vfloat32 m_fDensity;
	vfloat32 m_fMass;									
	
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICMASS_27_10_04_H
