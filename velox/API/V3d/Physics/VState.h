/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSTATE_27_10_04_H
#define V3D_VSTATE_27_10_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/SmartPtr/VSharedPtr.h>
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
	typedef VSharedPtr<VOdeBody> Parent;
	
	VState(Parent in_pParent);
	virtual ~VState();

	/**
	 * Returns the Parent container of this state
	 * Returns 0 if no Parent is set
	 */
    Parent GetParent();
	
	/**
	 * Override this method to add functionality
	 */
    virtual void Apply() = 0;
protected:

	Parent m_Parent;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTATE_27_10_04_H

