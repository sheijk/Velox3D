#include "VCGVertexShaderState.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/VException.h>

//#include <Cg/cgGL.h>
#include <sstream>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

namespace {
	vbool IsPixelShader(CGprofile in_Profile)
	{
		return in_Profile == CG_PROFILE_FP20 || in_Profile == CG_PROFILE_FP30;
	}

	vbool IsVertexShader(CGprofile in_Profile)
	{
		return in_Profile == CG_PROFILE_VP20 || in_Profile == CG_PROFILE_VP30;
	}

	vbool IsKnownProfile(CGprofile in_Profile)
	{
		return IsPixelShader(in_Profile) || IsVertexShader(in_Profile);
	}
}

CGcontext VCGVertexShaderState::m_Context = cgCreateContext();
CGprofile VCGVertexShaderState::s_LastPixelProfile;
CGprofile VCGVertexShaderState::s_LastVertexProfile;

#define V3D_CHECK_CG_ERROR()\
	{\
		CGerror error = cgGetError();\
		if( CG_NO_ERROR != error )\
		{\
			const char* message = cgGetErrorString(error);\
			V3D_THROW(VException, message);\
		}\
	}

VCGVertexShaderState::VCGVertexShaderState(ShaderMode in_Mode)
{
	m_Profile = CG_PROFILE_VP20;
	m_Program = NULL;
	m_DisableMode = in_Mode;
}

/**
 * standard c'tor
 */
VCGVertexShaderState::VCGVertexShaderState(
	VStringParam in_strFileName,
	CGprofile in_Profile
	)
{
	if( ! IsKnownProfile(in_Profile) )
	{
		V3D_THROWMSG(VException, "Could not create vertex shader '"
			<< in_strFileName << "': the profile " << in_Profile
			<< " is unknown");
	}

	try {
		m_Profile = in_Profile;
		m_Program = cgCreateProgramFromFile(
			m_Context, 
			CG_SOURCE, 
			in_strFileName,
			m_Profile, 
			NULL, 
			NULL);
	    
		V3D_CHECK_CG_ERROR();

		cgGLLoadProgram(m_Program);
		V3D_CHECK_CG_ERROR();

		m_ModelViewParam = cgGetNamedParameter(m_Program, "ModelViewMat");
		V3D_CHECK_CG_ERROR();
	}
	catch(VException& e)
	{
		std::stringstream msg;
		msg << "Error when loading '" << in_strFileName << ": ";
		msg << e.GetErrorString();
		V3D_THROW(VException, msg.str().c_str());
	}
}

/**
 * d'tor
 */
VCGVertexShaderState::~VCGVertexShaderState()
{
}

void VCGVertexShaderState::AddAutoVar(
	const std::string& in_strName, 
	AutoVariable in_Type)
{
	Autovar var;
	var.name = in_strName;
	var.variable = in_Type;

	m_AutoVariables.push_back(var);
}

void VCGVertexShaderState::SetAutoVariable(
	const std::string& name, AutoVariable type) const
{
    switch(type)
	{
	case AutoVarModelViewMatrix:
		cgGLSetStateMatrixParameter(
			m_ModelViewParam, 
			CG_GL_MODELVIEW_PROJECTION_MATRIX, 
			CG_GL_MATRIX_IDENTITY);
		V3D_CHECK_CG_ERROR();
		break;

	default:
		V3D_THROW(VException, "Invalid auto variable type");
	}
}

void VCGVertexShaderState::SetAutoVariables() const
{
	AutovarList::const_iterator iter = m_AutoVariables.begin();

	for( ; iter != m_AutoVariables.end(); ++iter)
	{
		AutoVariable type = iter->variable;
		const std::string& name = iter->name;

		SetAutoVariable(name, type);
	}
}

void VCGVertexShaderState::Apply() const
{
	if( m_Program != NULL )
	{
		cgGLBindProgram(m_Program);
		V3D_CHECK_CG_ERROR();

		SetAutoVariables();

		//if( ! IsPixelShader(m_Profile) )
		if( cgIsParameter(m_ModelViewParam) )
		{
			// set modelview matrix parameter
			//cgGLSetStateMatrixParameter(m_ModelViewParam, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
			//V3D_CHECK_CG_ERROR();
		}

		cgGLEnableProfile(m_Profile);
		V3D_CHECK_CG_ERROR();

		if( IsPixelShader(m_Profile) )
		{
			s_LastPixelProfile = m_Profile;
		}
		else
		{
			s_LastVertexProfile = m_Profile;
		}
	}
	else
	{
		CGprofile profile;

		if( m_DisableMode == DisableVertexShader )
			profile = s_LastVertexProfile;
		else
			profile = s_LastPixelProfile;

		if( IsKnownProfile(profile) )
		{
			cgGLUnbindProgram(profile);
			V3D_CHECK_CG_ERROR();
			cgGLDisableProfile(profile);
			V3D_CHECK_CG_ERROR();
		}
	}
}

std::istream& operator>>(std::istream& str, VCGVertexShaderState::AutoVariable& v)
{
	std::string name;
	str >> name;

	if( name == "$modelview.matrix" )
		v = VCGVertexShaderState::AutoVarModelViewMatrix;
	else
		V3D_THROW(VException, "Invalid name for CG Shader auto variable");
	//TODO: bessere info ausgeben

	return str;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
