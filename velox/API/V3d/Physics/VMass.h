/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMASS_27_10_04_H
#define V3D_VMASS_27_10_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypes.h>
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

class VMass
{
public:
	
	virtual ~VMass();
	
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

	void SetTotalMass(vfloat32 in_fTotalMass);
	vfloat32 GetTotalMass();
    
protected:

	VMass();

	dMass m_Mass;
	
	vfloat32 m_fDensity;
	vfloat32 m_fMass;
	vfloat32 m_fTotalMass;
	
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMASS_27_10_04_H

