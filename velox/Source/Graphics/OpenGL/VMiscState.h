#ifndef V3D_VMISCSTATE_H
#define V3D_VMISCSTATE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/VMaterialDescription.h>
#include <V3dLib/Graphics/Geometry/VColor4f.h>

#include "IVOpenGLRenderState.h"

#include <Windows.h>
#include <gl/GL.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VMiscState : public IVOpenGLRenderState
{
public:
	typedef VMaterialDescription::PolygonMode PolygonMode;

	VMiscState(const VMaterialDescription& in_Mat);

	virtual void Apply() const;

private:
	int m_nFrontPolygonMode;
	int m_nBackPolygonMode;
	v3d::graphics::VColor4f m_DefaultColor;

	vuint GetGLModeNum(const PolygonMode in_Mode);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMISCSTATE_H
