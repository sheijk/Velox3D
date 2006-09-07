/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCGFXSTATE_2005_08_17_H
#define V3D_VCGFXSTATE_2005_08_17_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "../IVOpenGLRenderState.h"
#include <V3d/Graphics/IVStateCategory.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VCGFXPass;

class VCGFXStateCategory : public IVStateCategory
{
public:
	VCGFXStateCategory();
	IVRenderState* CreateState(const VRenderPass& in_Pass);
	void SetPriority(vuint n) { IVStateCategory::SetPriority(n); }
};

/**
 */
class VCGFXState : public IVOpenGLRenderState
{
public:
	VCGFXState(VCGFXPass* in_pPass);
	virtual ~VCGFXState();

	virtual void Apply(const VOpenGLDevice* in_pDevice) const;
	virtual const IVStateCategory* GetCategory() const;

	static void SetStateCategory(IVStateCategory* in_pCategory);
private:
	virtual void Apply() const { V3D_ASSERT(false /* should never be called */); }

	static IVStateCategory* s_pCategory;

	static VCGFXPass* s_pLastPass;
	VCGFXPass* m_pPass;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VCGFXSTATE_2005_08_17_H

