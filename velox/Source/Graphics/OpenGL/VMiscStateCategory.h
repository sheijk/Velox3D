/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMISCSTATECATEGORY_H
#define V3D_VMISCSTATECATEGORY_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "VMiscState.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VMiscStateCategory : public IVStateCategory
{
	VMiscState m_Default;

public:
	VMiscStateCategory() :
		m_Default(VRenderPass())
	{
		VMiscState::SetCategory(this);
	}

	//virtual vfloat32 GetPriority() const
	//{
	//	return .1f;
	//}

	//virtual const IVRenderState& GetDefault() const
	//{
	//	return m_Default;
	//}

	VMiscState* CreateState(const VRenderPass& in_Pass)
	{
		VMiscState* pState = new VMiscState(in_Pass);
		return pState;
	}

	void SetPriority(vuint n) { IVStateCategory::SetPriority(n); }
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMISCSTATECATEGORY_H

