/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSTATECCYLINDERMASS_16_11_04_H
#define V3D_VSTATECCYLINDERMASS_16_11_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Physics/VMass.h>
#include <V3d/Physics/VState.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a capped cylinder mass state
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VStateCCylinderMass : public VMass, public VState
{
public:
	
	VStateCCylinderMass(VState::Parent in_pParent);
	virtual ~VStateCCylinderMass();

	/**
	 * Sets the radius of this spherical mass abstraction
	 */
	void SetRadius(vfloat32 in_fRadius);
	void SetLength(vfloat32 in_fLength);
	void SetDirection(vuint in_iDirection);

	/**
	 * Returns the assigned mass of this object
	 */
	vfloat32 GetRadius();
	vfloat32 GetLength();
	vuint GetDirection();
	virtual void Apply();

private:
	vfloat32 m_fRadius;
	vfloat32 m_fLength;
	/**
	 * The cylinder's long axis is oriented along the body's x, y or z axis
	 * according to the value of direction (1=x, 2=y, 3=z)
	 */
	vuint m_iDirection; 
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTATECCYLINDERMASS_16_11_04_H