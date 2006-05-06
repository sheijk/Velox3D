#include "VGLSLTextureParameter.h"
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>
#include <V3d/Graphics/OpenGLUtils.h>
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
	: VGLSLParameter(in_hProgram, in_strName, IVParameter::Texture)
{
	m_nTextureUnit = in_nTextureUnit;
}

/**
 * d'tor
 */
VGLSLTextureParameter::~VGLSLTextureParameter()
{
}

void VGLSLTextureParameter::ApplyTexture(VStringParam in_strResourceName) const
{
	using namespace resource;

	// get resource
	try
	{
		m_pTexture = GetMutableResourceData<IVTexture>(in_strResourceName);
	}
	catch(VException&)
	{
	}

	// set texture id as int
	//glUniform1iARB(m_Location, pTex->GetTextureId());
	V3D_GLCHECK( glUniform1iARB(GetLocation(), m_nTextureUnit) );	
}

std::string VGLSLTextureParameter::TextureResource() const
{
	if( m_pTexture != 0 && m_pTexture.GetEnclosingResource() != 0 )
		return m_pTexture.GetEnclosingResource()->GetQualifiedName();
	else
		return "";
}

void VGLSLTextureParameter::BindTexture()
{	
	if( &*m_pTexture != 0 )
	{
		V3D_GLCHECK( m_pTexture->Bind(m_nTextureUnit) );
	}
}

void VGLSLTextureParameter::UnbindTexture()
{
	if( &*m_pTexture != 0 )
	{
		V3D_GLCHECK( m_pTexture->Unbind() );
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
