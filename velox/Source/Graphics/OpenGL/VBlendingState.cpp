#include "VBlendingState.h"

#include <Windows.h>
#include <gl/GL.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------

VBlendingState::VBlendingState(const VMaterialDescription& in_Mat)
{

	m_SourceFactor = GetGLModeNum(in_Mat.sourceBlendFactor);
	m_DestFactor   = GetGLModeNum(in_Mat.destBlendFactor);
	m_bIsEnabled   = in_Mat.enableBlending;
   
}

void VBlendingState::Apply() const
{
	
	if(m_bIsEnabled)
	{
		glEnable(GL_BLEND);
		glDisable ( GL_DEPTH_TEST );

		glBlendFunc(m_SourceFactor, m_DestFactor);
	}
	else
		glDisable(GL_BLEND);
		glEnable ( GL_DEPTH_TEST );
}

vuint VBlendingState::GetGLModeNum(BlendMode in_Mode)
{
	switch(in_Mode)
	{
	case VMaterialDescription::BlendZero:
		return GL_ZERO;
	case VMaterialDescription::BlendOne:
		return GL_ONE;
	case VMaterialDescription::BlendSourceColor:
		return GL_SRC_COLOR;
	case VMaterialDescription::BlendOneMinusSourceColor:
		return GL_ONE_MINUS_SRC_COLOR;
	case VMaterialDescription::BlendDestColor:
		return GL_DST_COLOR;
	case VMaterialDescription::BlendOneMinusDestColor:
		return GL_ONE_MINUS_DST_COLOR;
	case VMaterialDescription::BlendSourceAlpha:
		return GL_SRC_ALPHA;
	case VMaterialDescription::BlendOneMinusSourceAlpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	case VMaterialDescription::BlendDestAlpha:
		return GL_DST_ALPHA;
	case VMaterialDescription::BlendOneMinusDepthAlpha:
		return GL_ONE_MINUS_DST_ALPHA;
	case VMaterialDescription::BlendSourceAlphaSaturate:
		return GL_SRC_ALPHA_SATURATE;
	}

	V3D_THROW(VException, "illegal mode for blending state");
}
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
