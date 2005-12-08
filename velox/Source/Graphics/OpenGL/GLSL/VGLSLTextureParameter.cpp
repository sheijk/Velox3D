#include "VGLSLTextureParameter.h"
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VGLSLTextureParameter::VGLSLTextureParameter(
	GLhandleARB in_hProgram, VStringParam in_strName, vuint in_nTextureUnit)
	: VGLSLParameter(in_hProgram, in_strName)
{
	m_nTextureUnit = in_nTextureUnit;
}

/**
 * d'tor
 */
VGLSLTextureParameter::~VGLSLTextureParameter()
{
}

void VGLSLTextureParameter::ApplyTexture(VStringParam in_strResourceName)
{
	using namespace resource;

	// get resource
	m_pTexture = GetMutableResourceData<VTexture2D>(in_strResourceName);

	// set texture id as int
	//glUniform1iARB(m_Location, pTex->GetTextureId());
	glUniform1iARB(GetLocation(), m_nTextureUnit);
}

void VGLSLTextureParameter::BindTexture()
{	
	if( &*m_pTexture != 0 )
		m_pTexture->Bind(m_nTextureUnit);
}

void VGLSLTextureParameter::UnbindTexture()
{
	if( &*m_pTexture != 0 )
		m_pTexture->Unbind();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
