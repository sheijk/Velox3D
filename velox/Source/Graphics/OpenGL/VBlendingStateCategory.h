#ifndef V3D_VBLENDINGSTATE_2004_06_06_H
#define V3D_VBLENDINGSTATE_2004_06_06_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include "VBlendingState.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * @author: ins
 */

class VBlendingStateCategory : public IVStateCategory
{
	VBlendingState m_Default;

public:
	VBlendingStateCategory() :
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

		VBlendingState* CreateState(const VMaterialDescription& in_Mat)
		{
			VBlendingState* pState = new VBlendingState(in_Mat);
			return pState;
		}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBLENDINGSTATE_2004_06_06_H
