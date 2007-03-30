/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VVERTEXSHADERCATEGORY_2005_03_23_H
#define V3D_VVERTEXSHADERCATEGORY_2005_03_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVStateCategory.h>
#include "VCGVertexShaderState.h"
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VCGShaderCategory : public IVStateCategory
{
public:
	void SetPriority(vuint n) { IVStateCategory::SetPriority(n); }

protected:
	IVRenderState* CreateShaderState(
		const VState* in_pState, 
		VCGVertexShaderState::ShaderMode in_DisableMode);
};

/**
 * @author sheijk
 */
class VVertexShaderCategory : public VCGShaderCategory
{
public:
	virtual IVRenderState* CreateState(const VRenderPass& in_Pass);
};

class VPixelShaderCategory : public VCGShaderCategory
{
public:
	virtual IVRenderState* CreateState(const VRenderPass& in_Pass);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEXSHADERCATEGORY_2005_03_23_H

