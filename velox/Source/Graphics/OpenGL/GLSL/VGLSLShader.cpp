/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VGLSLShader.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter/VEmptyPolicy.h>

#include "VGLSLTextureParameter.h"

#include <V3d/Core/VIOStream.h>
#include <GL/glfw.h>
#include <V3d/Core/VLogging.h>
#include <V3d/Core/DebugUtils.h>

#include <sstream>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace std;

namespace {
	IVParameter::Type ParamTypeFromGLEnum(GLenum in_GLTypeEnum)
	{
		switch(in_GLTypeEnum)
		{
		case GL_FLOAT: return IVParameter::Float;
		case GL_FLOAT_VEC2: return IVParameter::Float2;
		case GL_FLOAT_VEC4: return IVParameter::Float4;
		case GL_FLOAT_MAT4: return IVParameter::Float44;

		case GL_INT: return IVParameter::Int;
		case GL_BOOL: return IVParameter::Bool;

		default:
			V3D_LOGONCE(unimplementedShaderParamDataType);

			return IVParameter::Unknown;
		}
	}
}

VGLSLShader::VGLSLShader(
			const std::string& in_strVertexSource, 
			const std::string& in_strFragmentSource)
{
	static VThreadId lastThreadId = -1;
	VThreadId threadId = IdOfCurrentThread();

	if( lastThreadId != threadId )
	{
		vout << "Creating GLSL Shader from thread " << threadId << vendl;
		lastThreadId = threadId;
	}

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
	if( CompileErrorOccured(m_hVertexShader, &errorMessage) )
		V3D_THROWMSG(VGLSLException, "Could not compile vertex shader: " << errorMessage);

	glCompileShaderARB(m_hFragmentShader);
	
	if( CompileErrorOccured(m_hFragmentShader, &errorMessage) )
		V3D_THROWMSG(VGLSLException, "Could not compile fragment shader: " << errorMessage);

	glAttachObjectARB(m_hProgram, m_hVertexShader);
	glAttachObjectARB(m_hProgram, m_hFragmentShader);

	/* TODO: right here?!? "Only shaders that are not attached can be deleted so this operation is not irrelevant." 
	 * see http://www.lighthouse3d.com/opengl/glsl/index.php?oglcleanup --ins
	 */
	glDeleteObjectARB(m_hVertexShader); 
	glDeleteObjectARB(m_hFragmentShader);

	glLinkProgramARB(m_hProgram);
	if( LinkErrorOccured(m_hProgram, &errorMessage) )
		V3D_THROWMSG(VGLSLException, "Could not link glsl program: " << errorMessage);

	glUseProgramObjectARB(m_hProgram);

	GLint uniformCount[10] = { 99 };
	// generates an opengl error..
	glGetIntegerv(GL_ACTIVE_UNIFORMS, uniformCount);
	GLint maxUniforms[10] = { 99 };
	// this one, too
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
	for(vuint paramNum = 0; paramNum < m_Parameters.size(); ++paramNum)
	{
		if( m_Parameters[paramNum]->GetName() == in_strName )
			return m_Parameters[paramNum];
	}

	return SharedPtr<IVParameter>(0);

	//return SharedPtr(new VGLSLParameter(m_hProgram, in_strName));
}

vbool VGLSLShader::CompileErrorOccured(GLhandleARB in_hProgram, std::string* in_pstrErrorMesssage)
{
	GLint length = 0;
	GLint compileError = 0;
	glGetObjectParameterivARB(in_hProgram, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
	glGetObjectParameterivARB(in_hProgram, GL_OBJECT_COMPILE_STATUS_ARB, &compileError);

	if( compileError != 1)
	{
		char* message = new char[length];
		in_pstrErrorMesssage->resize(length);
		glGetInfoLogARB(in_hProgram, length, &length, message);
		*in_pstrErrorMesssage = message;
		delete[] message;
		return true;
	}
	else
	{
		return false;
	}
}

vbool VGLSLShader::LinkErrorOccured(GLhandleARB in_hProgram, std::string* in_pstrErrorMesssage)
{
	GLint length;
	GLint linkError = 0;
	glGetObjectParameterivARB(in_hProgram, GL_OBJECT_INFO_LOG_LENGTH_ARB, &length);
	glGetObjectParameterivARB(in_hProgram, GL_OBJECT_LINK_STATUS_ARB, &linkError);

	if( linkError != 1)
	{
		char* message = new char[length];
		in_pstrErrorMesssage->resize(length);
		glGetInfoLogARB(in_hProgram, length, &length, message);
		*in_pstrErrorMesssage = message;
		delete[] message;
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
		return new VGLSLParameter(m_hProgram, name, ParamTypeFromGLEnum(type));
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

