/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSHADERCATEGORY_2005_11_26_H
#define V3D_VSHADERCATEGORY_2005_11_26_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVStateCategory.h>
#include "GLSL/VGLSLShader.h"
#include "VShaderState.h"

#include <vector>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VShaderCategory : public IVStateCategory
{
public:
	VShaderCategory();
	virtual ~VShaderCategory();

	virtual VShaderState* CreateState(const VRenderPass& in_Pass);

	static vbool CanCreateStateFrom(const VRenderPass& in_Pass);

	void SetPriority(vuint in_nPriority) { IVStateCategory::SetPriority(in_nPriority); }

	static std::vector<std::string> GetResourceDependencies(const VRenderPass& in_Pass);
private:
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VSHADERCATEGORY_2005_11_26_H

