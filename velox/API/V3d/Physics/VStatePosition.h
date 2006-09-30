/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSTATEPOSITION_27_10_04_H
#define V3D_VSTATEPOSITION_27_10_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Physics/VState.h>
#include <V3d/Math/VVector.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a position state and
 * encapsulates ODE function calls
 *
 * author: ins
 */

class VStatePosition : public VState
{
public:
	VStatePosition(VState::Parent in_pParent);	
	virtual ~VStatePosition();

	void SetPosition(vfloat32 x, vfloat32 y, vfloat32 z);
	void SetPosition(math::VVector3f in_Position);
	math::VVector3f GetPositon();

	virtual void Apply();

private:

	
	math::VVector3f m_Position;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTATEPOSITION_27_10_04_H

