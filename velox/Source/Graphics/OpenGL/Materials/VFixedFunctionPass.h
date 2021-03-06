/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VFIXEDFUNCTIONPASS_2005_08_17_H
#define V3D_VFIXEDFUNCTIONPASS_2005_08_17_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "../../DeviceBase/VRenderStateList.h"
#include <string>
#include "../VTextureStateCategory.h"
#include "../VMiscStateCategory.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VFixedFunctionPass : public VRenderStateList
{
public:
	VFixedFunctionPass(
		RenderStateList in_DefaultStates, const VRenderPass& in_Pass);
	virtual ~VFixedFunctionPass();

	static vbool CanRealize(const VRenderPass& in_Pass);

	static void SetCategories(
		VTextureStateCategory* in_pTextureStateCategory,
		VMiscStateCategory* in_pMiscStateCategory);

	virtual VRangeIterator<IVParameter> Parameters();
private:
	static vbool StateTypeKnown(const std::string& in_Type);

	static VTextureStateCategory* m_pTextureStateCategory;
	static VMiscStateCategory* m_pMiscStateCategory;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VFIXEDFUNCTIONPASS_2005_08_17_H

