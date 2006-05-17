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
	m_bWasFineLastTime = true;
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

	m_pTexture = VResourceDataPtr<IVTexture>();

	try
	{
		if( in_strResourceName != 0 && in_strResourceName[0] != '\0' )
		{
			m_pTexture = GetMutableResourceData<IVTexture>(in_strResourceName);
			m_bWasFineLastTime = true;
		}
	}
	catch(VException& e)
	{
		//if( m_bWasFineLastTime )
		//{
		//	V3D_LOGLN("Could not apply texture " << in_strResourceName
		//		<< ":" << e.GetErrorString());
		//}

		m_bWasFineLastTime = false;
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
