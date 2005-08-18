#include "VCGFXMaterial.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>

#include <string>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace std;

CGcontext VCGFXMaterial::s_Context = cgCreateContext();

#define V3D_CHECK_CG_ERROR()\
{\
	CGerror error = cgGetError();\
	if( CG_NO_ERROR != error )\
{\
	const char* message = cgGetErrorString(error);\
	V3D_THROW(VException, message);\
}\
}

VCGFXMaterial::VCGFXMaterial(VRenderStateList::RenderStateList in_DefaultStates, const std::string& in_strSource)
{
	cgGLRegisterStates(s_Context);

	// initialize
	m_Effect = cgCreateEffect(s_Context, in_strSource.c_str(), 0);
	V3D_CHECK_CG_ERROR();
	//m_Effect = cgCreateEffectFromFile(s_Context, in_strSource.c_str(), 0);
	V3D_ASSERT(m_Effect != 0);

	// get a suitable technique
	m_Technique = cgGetFirstTechnique(m_Effect);

	while( m_Technique )
	{
		cgValidateTechnique(m_Technique);
		m_Technique = cgGetNextTechnique(m_Technique);
	}

	// find a vaild technique
	m_Technique = cgGetFirstTechnique(m_Effect);
	while( m_Technique != 0 && !cgIsTechniqueValidated(m_Technique) )
		m_Technique = cgGetNextTechnique(m_Technique);

	V3D_ASSERT(m_Technique != 0);

	vout << "Effect using technique " << cgGetTechniqueName(m_Technique) << vendl;

	// get first pass TODO: use all passes (or specific pass)
	CGpass pass = cgGetFirstPass(m_Technique);

	while( pass != 0 )
	{
		VCGFXPass* pPass = new VCGFXPass(in_DefaultStates, pass, m_Effect, m_Technique, this);
		m_Passes.push_back(VSharedPtr<VCGFXPass>(pPass));

		vout << "\tpass " << cgGetPassName(pass) << vendl;

		pass = cgGetNextPass(pass);
	}

	//TODO: get parameters
	CGparameter param = cgGetFirstEffectParameter(m_Effect);

	vout << "parameters:" << vendl;

	while( param != 0 )
	{
		CGtype paramType = cgGetParameterType(param);

		vout << "\t" << cgGetParameterName(param) << " : " 
			<< cgGetTypeString(paramType);
			//<< " as " << cgGetParameterSemantic(param)
			//<< vendl;

		const string semantic(cgGetParameterSemantic(param));

		if( semantic == "MODELVIEWPROJECTION" )
		{
			AutoParameter autoParam;
			autoParam.param = param;
			autoParam.type = APModelViewProjectionMatrix;

			m_AutoParameters.push_back(autoParam);

			vout << " as " << semantic;
		}

		vout << vendl;

		param = cgGetNextParameter(param);
	}
}

vuint VCGFXMaterial::PassCount() const
{
	return m_Passes.size();
}

const IVPass& VCGFXMaterial::GetPass(vuint in_nNum) const
{
	V3D_ASSERT(in_nNum < m_Passes.size());

	return *m_Passes[in_nNum];
}

void VCGFXMaterial::ApplyAutoParameters()
{
	for(vuint num = 0; num < m_AutoParameters.size(); ++num) 
	{
		AutoParameter& ap(m_AutoParameters[num]);

		switch(ap.type)
		{
		case APModelViewProjectionMatrix: {
			cgGLSetStateMatrixParameter(ap.param, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
										  } break;
		}
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
