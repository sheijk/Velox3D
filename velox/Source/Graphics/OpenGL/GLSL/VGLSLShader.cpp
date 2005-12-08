#include "VGLSLShader.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter/VEmptyPolicy.h>

#include "VGLSLTextureParameter.h"

#include <sstream>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace std;

VGLSLShader::VGLSLShader(
			const std::string& in_strVertexSource, 
			const std::string& in_strFragmentSource)
{
	m_nTextureCount = 0;

	if( ! IsGLSLSupported() )
		V3D_THROW(VGLSLException, "GLSL is not supported");

	std::string errorMessage;

	m_hProgram = glCreateProgramObjectARB();
	m_hVertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	m_hFragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	GLint vertexSize = GLint(in_strVertexSource.size());
	GLint fragmentSize = GLint(in_strFragmentSource.size());
	const GLchar* vertexSource = in_strVertexSource.c_str();
	const GLchar* fragmentSource = in_strFragmentSource.c_str();
	glShaderSourceARB(m_hVertexShader, 1, &vertexSource, &vertexSize);
	glShaderSourceARB(m_hFragmentShader, 1, &fragmentSource, &fragmentSize);

	glCompileShaderARB(m_hVertexShader);
	if( ErrorOccured(m_hVertexShader, &errorMessage) )
		V3D_THROWMSG(VGLSLException, "Could not compile vertex shader: " << errorMessage);

	glCompileShaderARB(m_hFragmentShader);
	if( ErrorOccured(m_hFragmentShader, &errorMessage) )
		V3D_THROWMSG(VGLSLException, "Could not compile fragment shader: " << errorMessage);

	glAttachObjectARB(m_hProgram, m_hVertexShader);
	glAttachObjectARB(m_hProgram, m_hFragmentShader);

	glDeleteObjectARB(m_hVertexShader);
	glDeleteObjectARB(m_hFragmentShader);

	glLinkProgramARB(m_hProgram);
	if( ErrorOccured(m_hProgram, &errorMessage) )
		V3D_THROWMSG(VGLSLException, "Could not link glsl program: " << errorMessage);

	glUseProgramObjectARB(m_hProgram);

	GLint uniformCount[10] = { 99 };
	glGetIntegerv(GL_ACTIVE_UNIFORMS, uniformCount);
	GLint maxUniforms[10] = { 99 };
	glGetIntegerv(GL_ACTIVE_UNIFORM_MAX_LENGTH, maxUniforms);

	vuint paramNum = 0;
	IVParameter* param = 0;
	while( (param = GetActiveUniformParameter(paramNum)) != 0 )
	{
		m_Parameters.push_back(SharedPtr(param));
		++paramNum;
	}
}

VGLSLShader::~VGLSLShader()
{
	glDetachObjectARB(m_hProgram, m_hVertexShader);
	glDetachObjectARB(m_hProgram, m_hFragmentShader);

	glDeleteObjectARB(m_hVertexShader);
	glDeleteObjectARB(m_hFragmentShader);

	glDeleteObjectARB(m_hProgram);
}

void VGLSLShader::Bind()
{
	glUseProgramObjectARB(m_hProgram);

	for(vuint texNum = 0; texNum < m_Textures.size(); ++texNum)
		m_Textures[texNum]->BindTexture();
}

void VGLSLShader::Unbind()
{
	for(vuint texNum = 0; texNum < m_Textures.size(); ++texNum)
		m_Textures[texNum]->UnbindTexture();

	glUseProgramObjectARB(0);
}

vbool VGLSLShader::IsGLSLSupported()
{
	return GLEW_ARB_shader_objects &&
		GLEW_ARB_vertex_shader &&
		GLEW_ARB_fragment_shader &&
		GLEW_ARB_shading_language_100;
}

VSharedPtr<IVParameter> VGLSLShader::GetParameter(VStringParam in_strName)
{
	return SharedPtr(new VGLSLParameter(m_hProgram, in_strName));
}

vbool VGLSLShader::ErrorOccured(GLhandleARB in_hProgram, std::string* in_pstrErrorMesssage)
{
	GLint length = 0;
	glGetObjectParameterivARB(in_hProgram, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);

	if( length > 1 )
	{
		char* message = new char[length];
		in_pstrErrorMesssage->resize(length);
		glGetInfoLogARB(in_hProgram, length, &length, message);
		*in_pstrErrorMesssage = message;
		delete message;
		return true;
	}
	else
	{
		return false;
	}
}

VRangeIterator<IVParameter> VGLSLShader::Parameters()
{
	return CreateDerefBeginIterator<IVParameter>(m_Parameters);
}

IVParameter* VGLSLShader::GetActiveUniformParameter(vuint in_nIndex)
{
	GLsizei size;
	GLsizei length;
	GLenum type = 0;
	GLchar name[100];
	glGetActiveUniformARB(m_hProgram, in_nIndex, 100, &length, &size, &type, name);

	if( type == GL_SAMPLER_2D )
	{
		VGLSLTextureParameter* pTexParam = new VGLSLTextureParameter(
			m_hProgram, name, m_nTextureCount);
		
		++m_nTextureCount;
        
		m_Textures.push_back(pTexParam);
		
		return pTexParam;
	}
	else if( type != 0 )
	{
		return new VGLSLParameter(m_hProgram, name);
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
