#include "VPBufferTexture.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VPBufferTexture::VPBufferTexture(VPBufferWindowContext* in_pContext) : 
	m_pContext(in_pContext), m_iTextureID(0)
{
	vbyte* pPixelData = new vbyte[m_pContext->GetDisplaySettings()->GetWidth() * m_pContext->GetDisplaySettings()->GetHeight() * 3];

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_iTextureID);
	glBindTexture(GL_TEXTURE_2D, m_iTextureID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_pContext->GetDisplaySettings()->GetWidth(), 
		m_pContext->GetDisplaySettings()->GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, 
		pPixelData);

	if(pPixelData != 0)
	{
		delete[] pPixelData;
		pPixelData = 0;
	}
}

VPBufferTexture::~VPBufferTexture()
{
}

void VPBufferTexture::Bind()
{
	//bind Texture
	wglBindTexImageARB(m_pContext -> GetPixelBuffer(), WGL_FRONT_LEFT_ARB);
}

void VPBufferTexture::Unbind()
{
	//unbind Texture
	wglReleaseTexImageARB(m_pContext -> GetPixelBuffer(), WGL_FRONT_LEFT_ARB);
};
//-----------------------------------------------------------------------------
}}// namespace v3d::graphics
//-----------------------------------------------------------------------------