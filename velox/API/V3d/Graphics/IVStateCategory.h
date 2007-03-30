/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVSTATECATEGORY_H
#define V3D_IVSTATECATEGORY_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVRenderState.h>
#include <V3d/Graphics/VEffectDescription.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
class IVRenderState;

class IVStateCategory
{
public:
	virtual IVRenderState* CreateState(const VRenderPass& in_Pass) = 0;
	virtual vuint GetPriority() const { return m_nPriority; }

protected:
	void SetPriority(vuint in_nPriority) { m_nPriority = in_nPriority; }

private:
	vuint m_nPriority;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVSTATECATEGORY_H

