#ifndef V3D_VBLENDINGSTATE_05_26_04_H
#define V3D_VBLENDINGSTATE_05_26_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VMaterialDescription.h>

#include "IVOpenGLRenderState.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------

/**
 *  adds blending to opengl
 *	@author: ins
 */

class VBlendingState : public IVOpenGLRenderState
{
public:

	VBlendingState(const VMaterialDescription& in_Mat);
		
	virtual void Apply() const;

private:

	typedef VMaterialDescription::BlendFactor BlendMode;

	vuint m_SourceFactor;
	vuint m_DestFactor;
	vbool m_bIsEnabled;

	static vuint GetGLModeNum(BlendMode in_Mode);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBLENDINGSTATE_05_26_04_H