/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VODEBODY_2006_02_13_H
#define V3D_VODEBODY_2006_02_13_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <ode/ode.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; 

/**
 * Ode body implementation
 */

class VWorld;
class VOdeBody
{
public:

	VOdeBody();
	virtual ~VOdeBody();

	dBodyID* GetBodyID();
	void Create(VWorld* in_pWorld);
	void Destroy();
	vbool IsAlive();

private:

	vbool m_bIsAlive;
	dBodyID m_Body;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------
#endif // V3D_VODEBODY_2006_02_13_H

