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

/**
 * @author sheijk
 */
class VMiscState : public IVOpenGLRenderState
{
public:
	VMiscState(const VMaterialDescription& in_Mat);

	virtual void Apply() const;

private:
	typedef VMaterialDescription::PolygonMode PolygonMode;
	typedef VMaterialDescription::DepthTest DepthTest;

	vuint m_nFrontPolygonMode;
	vuint m_nBackPolygonMode;

	vuint m_DepthFunction;
	vbool m_bDepthWrite;

	VMaterialDescription::ColorBufferMask m_ColorMask;

	v3d::graphics::VColor4f m_DefaultColor;

	static vuint GetGLModeNum(const DepthTest in_Test);
	static vuint GetGLModeNum(const PolygonMode in_Mode);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMISCSTATE_H
