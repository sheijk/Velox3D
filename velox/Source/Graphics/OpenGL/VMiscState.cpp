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

	m_DepthFunction = GetGLModeNum(in_Mat.depthTestFunction);
	m_bDepthWrite = in_Mat.depthWriteMask == VMaterialDescription::DepthWrite;

	m_DefaultColor = in_Mat.defaultColor;

	m_ColorMask = in_Mat.colorMask;
}

void VMiscState::Apply() const
{
	glPolygonMode(GL_FRONT, m_nFrontPolygonMode);
	glPolygonMode(GL_BACK, m_nBackPolygonMode);

	glDepthFunc(m_DepthFunction);
	glDepthMask(m_bDepthWrite);

	glColor4f(
		m_DefaultColor.red,
		m_DefaultColor.green,
		m_DefaultColor.blue,
		m_DefaultColor.alpha
		);

	glColorMask(
		m_ColorMask.writeRed,
		m_ColorMask.writeGreen,
		m_ColorMask.writeBlue,
		m_ColorMask.writeAlpha
		);
}

vuint VMiscState::GetGLModeNum(const PolygonMode in_Mode)
{
	switch(in_Mode)
	{
	case VMaterialDescription::Point:	return GL_POINT;
	case VMaterialDescription::Filled:	return GL_FILL;
	case VMaterialDescription::Line:	return GL_LINE;
	}

	V3D_THROW(VException, "illegal polygon mode");
}

vuint VMiscState::GetGLModeNum(const DepthTest in_Test)
{
	switch(in_Test)
	{
	case VMaterialDescription::DepthAlways:			return GL_ALWAYS;
	case VMaterialDescription::DepthOnLess:			return GL_LESS;
	case VMaterialDescription::DepthOnLessEqual:	return GL_LEQUAL;
	case VMaterialDescription::DepthOnGreater:		return GL_GREATER;
	case VMaterialDescription::DepthOnGreaterEqual: return GL_GEQUAL;
	case VMaterialDescription::DepthNever:			return GL_NEVER;
	case VMaterialDescription::DepthOnEqual:		return GL_EQUAL;
	case VMaterialDescription::DepthOnNotEqual:		return GL_NOTEQUAL;
	}

	V3D_THROW(VException, "illegal depth test operation");
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
