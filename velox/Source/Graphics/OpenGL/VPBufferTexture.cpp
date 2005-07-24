#include "VPBufferTexture.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VPBufferTexture::VPBufferTexture(VPBufferWindowContext* in_pContext) : 
	m_pContext(in_pContext), m_iTextureID(0)
{
	byte* pPixelData = new byte[m_pContext->GetWidth() * m_pContext->GetHeight() * 3];

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_iTextureID);
	glBindTexture(GL_TEXTURE_2D, m_iTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_pContext->GetWidth(), 
		m_pContext->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, pPixelData);

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