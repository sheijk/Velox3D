#ifndef V3D_VMISCSTATECATEGORY_H
#define V3D_VMISCSTATECATEGORY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

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
		m_Default(VMaterialDescription())
	{
	}

	virtual vfloat32 GetPriority() const
	{
		return .1f;
	}

	virtual const IVRenderState& GetDefault() const
	{
		return m_Default;
	}

	VMiscState* CreateState(const VMaterialDescription& in_Mat)
	{
		VMiscState* pState = new VMiscState(in_Mat);
		return pState;
	}

	VMiscState* CreateState(const VRenderPass& in_Pass)
	{
		VMiscState* pState = new VMiscState(in_Pass);
		return pState;
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMISCSTATECATEGORY_H
