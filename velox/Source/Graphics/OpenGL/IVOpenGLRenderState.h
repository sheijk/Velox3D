/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVOPENGLRENDERSTATE_H
#define V3D_IVOPENGLRENDERSTATE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVRenderState.h>

#include <V3d/Core/RangeIter/VEmptyPolicy.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VOpenGLDevice;

class IVOpenGLRenderState : public IVRenderState
{
public:
	virtual void Apply(const VOpenGLDevice* in_pDevice) const
	{
		Apply();
	}


	virtual VRangeIterator<IVParameter> Parameters()
	{
		return CreateEmptyIterator<IVParameter>();
	}
protected:
	virtual void Apply() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVOPENGLRENDERSTATE_H

