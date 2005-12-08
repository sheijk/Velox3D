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

VGLSLParameter::VGLSLParameter(GLhandleARB in_hProgram, VStringParam in_strName)
{
	m_hProgram = in_hProgram;
	m_Location = glGetUniformLocationARB(in_hProgram, in_strName);
	m_strName = in_strName;
}

VGLSLParameter::~VGLSLParameter()
{
}

std::string VGLSLParameter::GetName() const
{
	return m_strName;
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

void VGLSLParameter::ApplyTexture(VStringParam in_strResourceName)
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

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
