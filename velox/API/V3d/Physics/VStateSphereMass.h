/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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

