#include "VMiscState.h"
//-----------------------------------------------------------------------------
#include <v3d/Graphics/GraphicsExceptions.h>

#include <V3dLib/Graphics/Materials/VModeTypeInfo.h>

#include "VOpenGLUtils.h"

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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
	m_bDepthTestEnabled = true;

	//m_DefaultColor = in_Mat.defaultColor;
	m_Red.Set(in_Mat.defaultColor.red);
	m_Green.Set(in_Mat.defaultColor.green);
	m_Blue.Set(in_Mat.defaultColor.blue);
	m_Alpha.Set(in_Mat.defaultColor.alpha);

	m_ColorMask = in_Mat.colorMask;

	m_SourceFactor		= GetGLModeNum(in_Mat.sourceBlendFactor);
	m_DestFactor		= GetGLModeNum(in_Mat.destBlendFactor);
	m_bBlendingEnabled	= in_Mat.enableBlending;

	VMatrix44f identity;
	Identity(identity);
	m_TextureMatrix.Set(identity);
}

void VMiscState::ReadColor(const VRenderPass& in_Pass)
{
	VState const* pColorState(in_Pass.GetStateByName("color"));

	if( pColorState != 0 )
	{
		std::string value;
		value = "1";

		pColorState->GetParameter("red", value);
		m_Red.Connect(value);

		value = "1";
		pColorState->GetParameter("green", value);
		m_Green.Connect(value);

		value = "1";
		pColorState->GetParameter("blue", value);
		m_Blue.Connect(value);

		value = "1";
		pColorState->GetParameter("alpha", value);
		m_Alpha.Connect(value);

		//pColorState->GetParameter<vfloat32>("red", color.red);
		//pColorState->GetParameter<vfloat32>("green", color.green);
		//pColorState->GetParameter("blue", color.blue);
		//pColorState->GetParameter("alpha", color.alpha);
	}
}

vuint VMiscState::GetPolygonMode(const std::string& in_strMode)
{
	return GetPolygonModeInfo().GetGLEnum(in_strMode);
}

vuint VMiscState::GetDepthFunction(const std::string& in_strFunc)
{
	return GetDepthTestInfo().GetGLEnum(in_strFunc);
}

vuint VMiscState::GetBlendFunction(const std::string& in_strFunc)
{
	return GetBlendFactorInfo().GetGLEnum(in_strFunc);
}

VMiscState::VMiscState(const VRenderPass& in_Pass)
{
	// init with default values
	m_nFrontPolygonMode = GL_FILL;
	m_nBackPolygonMode = GL_FILL;

	m_DepthFunction = GL_LESS;
	m_bDepthWrite = true;
	m_bDepthTestEnabled = true;

	//m_DefaultColor = VColor4f(0, 0, 0, 1);

	m_ColorMask.writeRed = true;
	m_ColorMask.writeGreen = true;
	m_ColorMask.writeBlue = true;
	m_ColorMask.writeAlpha = true;

	m_SourceFactor = GetGLModeNum(VMaterialDescription::BlendSourceAlpha);
	m_DestFactor = GetGLModeNum(VMaterialDescription::BlendOneMinusSourceAlpha);
	m_bBlendingEnabled = false;

	VMatrix44f identity;
	Identity(identity);
	m_TextureMatrix.Set(identity);

	// overwrite with options from render pass

	// read polygon mode
	VState const* polyState = in_Pass.GetStateByName("polygonmode");
	if( polyState != 0 )
	{
		std::string frontmode = "fill";
		std::string backmode = "fill";
		polyState->GetParameter("front", frontmode);
		polyState->GetParameter("back", backmode);

		m_nFrontPolygonMode = GetPolygonMode(frontmode);
		m_nBackPolygonMode = GetPolygonMode(backmode);
	}

	// get z buffer modes
	VState const* depthState = in_Pass.GetStateByName("depth");
	if( depthState != 0 )
	{
		std::string depthTest = "onless";
		vbool depthWrite = true;
		vbool enable = true;

		depthState->GetParameter("function", depthTest);
		depthState->GetParameter("write", depthWrite);
		depthState->GetParameter("enable", enable);

		m_DepthFunction = GetDepthFunction(depthTest);
		m_bDepthWrite = depthWrite;
		m_bDepthTestEnabled = enable;
	}

	VState const* colorMask = in_Pass.GetStateByName("colormask");
	if( colorMask != 0 )
	{
		colorMask->GetParameter("red", m_ColorMask.writeRed);
		colorMask->GetParameter("green", m_ColorMask.writeGreen);
		colorMask->GetParameter("blue", m_ColorMask.writeBlue);
		colorMask->GetParameter("alpha", m_ColorMask.writeAlpha);
	}

	VState const* blendState = in_Pass.GetStateByName("blending");
	if( blendState != 0 )
	{
		blendState->GetParameter("enable", m_bBlendingEnabled);

		std::string blendSource = "source.alpha";
		blendState->GetParameter("source", blendSource);
		m_SourceFactor = GetBlendFunction(blendSource);

		std::string blendDest = "one.minus.source.alpha";
		blendState->GetParameter("dest", blendDest);
		m_DestFactor = GetBlendFunction(blendDest);
	}

	const VState* texmatState = in_Pass.GetStateByName("texture");
	if( texmatState != 0 )
	{
		std::string value;
		texmatState->GetParameter("matrix", value);

		m_TextureMatrix.Connect(value);
	}

	ReadColor(in_Pass);
	//m_DefaultColor = GetColor(in_Pass);
}

void VMiscState::Apply() const
{
	glPolygonMode(GL_FRONT, m_nFrontPolygonMode);
	glPolygonMode(GL_BACK, m_nBackPolygonMode);

	if( m_bDepthTestEnabled )
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
	glDepthFunc(m_DepthFunction);
	glDepthMask(m_bDepthWrite);

	glColor4f(m_Red.Get(), m_Green.Get(), m_Blue.Get(), m_Alpha.Get());
		//m_DefaultColor.red,
		//m_DefaultColor.green,
		//m_DefaultColor.blue,
		//m_DefaultColor.alpha);

	glColorMask(
		m_ColorMask.writeRed,
		m_ColorMask.writeGreen,
		m_ColorMask.writeBlue,
		m_ColorMask.writeAlpha
		);

	if(m_bBlendingEnabled)
	{
		glEnable(GL_BLEND);

		glBlendFunc(m_SourceFactor, m_DestFactor);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	SetGLMatrix(GL_TEXTURE, m_TextureMatrix.Get());
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

vuint VMiscState::GetGLModeNum(BlendMode in_Mode)
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
