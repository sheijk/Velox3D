#include "VMiscState.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // auto unindent

VMiscState::VMiscState(const VMaterialDescription& in_Mat)
{
	m_nFrontPolygonMode = GetGLModeNum(in_Mat.frontPolyMode);
	m_nBackPolygonMode = GetGLModeNum(in_Mat.backPolyMode);
	m_DefaultColor = in_Mat.defaultColor;
}

void VMiscState::Apply() const
{
	glPolygonMode(GL_FRONT, m_nFrontPolygonMode);
	glPolygonMode(GL_BACK, m_nBackPolygonMode);
	glColor4f(
		m_DefaultColor.red,
		m_DefaultColor.green,
		m_DefaultColor.blue,
		m_DefaultColor.alpha
		);
}

vuint VMiscState::GetGLModeNum(const PolygonMode in_Mode)
{
	switch(in_Mode)
	{
	case VMaterialDescription::Point: return GL_POINT;
	case VMaterialDescription::Filled: return GL_FILL;
	case VMaterialDescription::Line: return GL_LINE;
	}

	V3D_THROW(VException, "illegal polygon mode");
}


//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
