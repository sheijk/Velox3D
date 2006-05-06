#include "VGLSLParameter.h"
//-----------------------------------------------------------------------------

#include <V3d/Math/VVector.h>

#include <V3d/Resource.h>

#include "../Textures/VTexture2D.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

GLfloat VGLSLParameter::m_fTempBuffer[16];
GLint VGLSLParameter::m_iTempBuffer[16];

VGLSLParameter::VGLSLParameter(
	GLhandleARB in_hProgram, VStringParam in_strName, Type in_Type)
{
	m_hProgram = in_hProgram;
	m_Location = glGetUniformLocationARB(in_hProgram, in_strName);
	m_strName = in_strName;
	m_Type = in_Type;
}

VGLSLParameter::~VGLSLParameter()
{
}

std::string VGLSLParameter::GetName() const
{
	return m_strName;
}

IVParameter::Type VGLSLParameter::GetType() const
{
	return m_Type;
}

GLint VGLSLParameter::GetLocation() const
{
	return m_Location;
}

GLhandleARB VGLSLParameter::GetProgram() const
{
	return m_hProgram;
}

void VGLSLParameter::Apply(vfloat32 in_fNewValue) const
{
	glUniform1fARB(m_Location, in_fNewValue);
}

vfloat32 VGLSLParameter::AsFloat() const
{
	glGetUniformfv(m_hProgram, m_Location, &m_fTempBuffer[0]);
	return m_fTempBuffer[0];
}

void VGLSLParameter::Apply(const VVector2f& in_NewValue) const
{
	glUniform2fARB(m_Location, in_NewValue[0], in_NewValue[1]);
}

VVector2f VGLSLParameter::AsFloat2() const
{
	glGetUniformfv(m_hProgram, m_Location, &m_fTempBuffer[0]);
	return ToVector2f(m_fTempBuffer[0], m_fTempBuffer[1]);
}

void VGLSLParameter::Apply(const VVector4f& in_NewValue) const
{
	glUniform4fARB(m_Location, 
		in_NewValue[0], 
		in_NewValue[1], 
		in_NewValue[2],
		in_NewValue[3]);
}

VVector4f VGLSLParameter::AsFloat4() const
{
	glGetUniformfvARB(m_hProgram, m_Location, &m_fTempBuffer[0]);
	
	return ToVector4f(m_fTempBuffer[0], m_fTempBuffer[1], 
		m_fTempBuffer[2], m_fTempBuffer[3]);
}

namespace {
	VMatrix44f ToMatrix44f(vfloat32* in_pArray16)
	{
		VMatrix44f mat;

		vuint index = 0;
		for(vuint column = 0; column < 4; ++column)
		for(vuint row = 0; row < 4; ++row)
		{
			mat.Set(row, column, in_pArray16[index]);
			++index;
		}

		return mat;
	}

	void Fill(const VMatrix44f& matrix, vfloat32* out_pArray)
	{
		vuint index = 0;
		for(vuint column = 0; column < 4; ++column)
		for(vuint row = 0; row < 4; ++row)
		{
			out_pArray[index] = matrix.Get(row, column);
			++index;
		}
	}

	V3D_DECLARE_EXCEPTION(VOpenGLException, VException);

	void ThrowGLExceptionOnError()
	{
		GLenum error = glGetError();

		if( error != GL_NO_ERROR )
		{
			std::string errorMessage = (char*) gluErrorString(error);

			V3D_THROWMSG(VOpenGLException, "OpenGL Error occured: " << errorMessage);
		}
	}
}

VMatrix44f VGLSLParameter::AsFloat44() const
{
	glGetUniformfvARB(m_hProgram, m_Location, &m_fTempBuffer[0]);

	return ToMatrix44f(m_fTempBuffer);
}

void VGLSLParameter::Apply(const VMatrix44f& in_NewValue) const
{
	Fill(in_NewValue, &m_fTempBuffer[0]);

	glUniformMatrix4fvARB(m_Location, 1, false, &m_fTempBuffer[0]);
}

void VGLSLParameter::Apply(vint in_nNewValue) const
{
	glUniform1iARB(m_Location, in_nNewValue);
}

vint VGLSLParameter::AsInt() const
{
	glGetUniformivARB(m_hProgram, m_Location, &m_iTempBuffer[0]);

	return m_iTempBuffer[0];
}


void VGLSLParameter::Apply(vbool in_bNewValue) const
{
	glUniform1iARB(m_Location, in_bNewValue);
}

vbool VGLSLParameter::AsBool() const
{
	glGetUniformivARB(m_hProgram, m_Location, &m_iTempBuffer[0]);
	return m_iTempBuffer[0] != 0;
}

void VGLSLParameter::ApplyTexture(VStringParam in_strResourceName) const
{
	return;

	//using namespace resource;

	//// get resource
	//VResourceDataPtr<const VTexture2D> pTex = 
	//	GetResourceData<VTexture2D>(in_strResourceName);

	//// set texture id as int
	////glUniform1iARB(m_Location, pTex->GetTextureId());
	//glUniform1iARB(m_Location, 0);
}

std::string VGLSLParameter::TextureResource() const
{
	return "";
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
