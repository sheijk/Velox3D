#ifndef V3D_VMISCSTATE_H
#define V3D_VMISCSTATE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VMiscState : public IVOpenGLRenderState
{
public:
	typedef VMaterialDescription::PolygonMode PolygonMode;

	VMiscState(const VMaterialDescription& in_Mat)
	{
		m_nFrontPolygonMode = GetGLModeNum(in_Mat.frontPolyMode);
		m_nBackPolygonMode = GetGLModeNum(in_Mat.backPolyMode);
	}

	virtual void Apply() const
	{
		glPolygonMode(GL_FRONT, m_nFrontPolygonMode);
		glPolygonMode(GL_BACK, m_nBackPolygonMode);
	}

private:
	int m_nFrontPolygonMode;
	int m_nBackPolygonMode;

	int GetGLModeNum(PolygonMode in_Mode)
	{
		switch(in_Mode)
		{
		case VMaterialDescription::Point: return GL_POINT;
		case VMaterialDescription::Filled: return GL_FILL;
		case VMaterialDescription::Line: return GL_LINE;
		}

		V3D_THROW(VException, "illegal polygon mode");
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMISCSTATE_H
