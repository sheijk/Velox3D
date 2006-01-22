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

IVStateCategory* VMiscState::m_pStateCategory = 0;

VMiscState::VMiscState(const VRenderPass& in_Pass)
{
	// init with default values
	m_nFrontPolygonMode = GL_FILL;
	m_nBackPolygonMode = GL_FILL;

	//m_DefaultColor = VColor4f(0, 0, 0, 1);

	m_ColorMask.writeRed = true;
	m_ColorMask.writeGreen = true;
	m_ColorMask.writeBlue = true;
	m_ColorMask.writeAlpha = true;

	m_SourceFactor = GetGLModeNum(BlendSourceAlpha);
	m_DestFactor = GetGLModeNum(BlendOneMinusSourceAlpha);
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
	m_DepthState.Parse(in_Pass);

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
		std::string matrix;
		texmatState->GetParameter("matrix", matrix);

		m_TextureMatrix.Connect(matrix);

		std::string coordGen = GetTexGenModeInfo().GetName(TexGenNone);
		texmatState->GetParameter("genCoords", coordGen);
		m_TextureGenerationMode = GetTexGenModeInfo().GetMode(coordGen);
	}

	m_bEnableLighting = true;
	const VState* lightingState = in_Pass.GetStateByName("lighting");
    if( lightingState != 0 )
	{
        lightingState->GetParameter("enabled", m_bEnableLighting);		
	}

	ReadColor(in_Pass);
	//m_DefaultColor = GetColor(in_Pass);
}

void VMiscState::Apply() const
{
	glPolygonMode(GL_FRONT, m_nFrontPolygonMode);
	glPolygonMode(GL_BACK, m_nBackPolygonMode);

	m_DepthState.Apply();

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

	if( m_bEnableLighting )
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	SetGLMatrix(GL_TEXTURE, m_TextureMatrix.Get());

	if( m_TextureGenerationMode == TexGenEyeSpace )
	{
		//const GLenum texGenMode = GL_EYE_LINEAR;
		//const GLenum texPlane = GL_EYE_PLANE;

		//glEnable(GL_TEXTURE_GEN_S);
		//glEnable(GL_TEXTURE_GEN_T);
		//glEnable(GL_TEXTURE_GEN_R);
		//glEnable(GL_TEXTURE_GEN_Q);

		//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, texGenMode);
		//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, texGenMode);
		//glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, texGenMode);
		//glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, texGenMode);

		//float sfact[4] = { 1, 0, 0, 0 };
		//float tfact[4] = { 0, 1, 0, 0 };
		//float rfact[4] = { 0, 0, 1, 0 };
		//float qfact[4] = { 0, 0, 0, 1 };
		//glTexGenfv(GL_S, texPlane, sfact);
		//glTexGenfv(GL_T, texPlane, tfact);
		//glTexGenfv(GL_R, texPlane, rfact);
		//glTexGenfv(GL_Q, texPlane, qfact);
	}
	else
	{
		//glDisable(GL_TEXTURE_GEN_S);
		//glDisable(GL_TEXTURE_GEN_T);
		//glDisable(GL_TEXTURE_GEN_R);
		//glDisable(GL_TEXTURE_GEN_Q);
	}
}

vuint VMiscState::GetGLModeNum(const PolygonMode in_Mode)
{
	switch(in_Mode)
	{
	case PMPoint:	return GL_POINT;
	case PMFilled:	return GL_FILL;
	case PMLine:	return GL_LINE;
	}

	V3D_THROW(VException, "illegal polygon mode");
}

vuint VMiscState::GetGLModeNum(const DepthTest in_Test)
{
	switch(in_Test)
	{
	case DepthAlways:			return GL_ALWAYS;
	case DepthOnLess:			return GL_LESS;
	case DepthOnLessEqual:	return GL_LEQUAL;
	case DepthOnGreater:		return GL_GREATER;
	case DepthOnGreaterEqual: return GL_GEQUAL;
	case DepthNever:			return GL_NEVER;
	case DepthOnEqual:		return GL_EQUAL;
	case DepthOnNotEqual:		return GL_NOTEQUAL;
	}

	V3D_THROW(VException, "illegal depth test operation");
}

vuint VMiscState::GetGLModeNum(BlendMode in_Mode)
{
	switch(in_Mode)
	{
	case BlendZero:
		return GL_ZERO;
	case BlendOne:
		return GL_ONE;
	case BlendSourceColor:
		return GL_SRC_COLOR;
	case BlendOneMinusSourceColor:
		return GL_ONE_MINUS_SRC_COLOR;
	case BlendDestColor:
		return GL_DST_COLOR;
	case BlendOneMinusDestColor:
		return GL_ONE_MINUS_DST_COLOR;
	case BlendSourceAlpha:
		return GL_SRC_ALPHA;
	case BlendOneMinusSourceAlpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	case BlendDestAlpha:
		return GL_DST_ALPHA;
	case BlendOneMinusDestAlpha:
		return GL_ONE_MINUS_DST_ALPHA;
	case BlendSourceAlphaSaturate:
		return GL_SRC_ALPHA_SATURATE;
	}

	V3D_THROW(VException, "illegal mode for blending state");
}

void VMiscState::SetCategory(IVStateCategory* in_pCategory)
{
	m_pStateCategory = in_pCategory;
}

const IVStateCategory* VMiscState::GetCategory() const
{
	V3D_ASSERT(m_pStateCategory != 0);

	return m_pStateCategory;
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

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
