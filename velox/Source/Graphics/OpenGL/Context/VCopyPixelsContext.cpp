#include "VCopyPixelsContext.h"
//-----------------------------------------------------------------------------

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

vuint NextPowerOf2(vuint num)
{
	vuint pow2 = 1;

	while( pow2 < num )
	{
		pow2 *= 2;
	}

	return pow2;
};

/**
 * standard c'tor
 */
VCopyPixelsContext::VCopyPixelsContext(
	const VDisplaySettings& in_DisplaySettings,
	IVRenderContext* in_pParentContext)
	: 
	VOffscreenContextBase(in_DisplaySettings, in_pParentContext)
{
	//in_pParentContext->MakeCurrent();

	glGenTextures(1, &m_TextureId);

	m_nTextureWidth = NextPowerOf2(in_DisplaySettings.GetWidth());
	m_nTextureHeight = NextPowerOf2(in_DisplaySettings.GetHeight());

	glBindTexture(GL_TEXTURE_2D, m_TextureId);

	//const vuint imageSize = m_nTextureWidth*m_nTextureHeight*4;
	//vbyte* data = new vbyte[imageSize];
	//memset(data, 128, imageSize);

	//gluBuild2DMipmaps(GL_TEXTURE_2D,
	//	GL_RGBA,
	//	m_nTextureWidth, m_nTextureHeight,
	//	GL_RGBA,
	//	GL_UNSIGNED_BYTE,
	//	data);

	//glTexImage2D(
	//	GL_TEXTURE_2D, 
	//	0, 
	//	GL_RGBA, 
	//	m_nTextureWidth, 
	//	m_nTextureHeight, 
	//	0, 
	//	GL_RGBA, 
	//	GL_UNSIGNED_BYTE, 
	//	0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	vuint size = m_nTextureWidth;
	vuint level = 0;
	vbyte color = 255;
	while(size > 0)
	{
        vbyte* data = new vbyte[size*size*4];
		memset(data, color, size*size*4);

		glTexImage2D(
			GL_TEXTURE_2D,
			level,
			GL_RGBA,
			size, size,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			data);

		delete[] data;

		size /= 2;
		++level;
		color /= 2;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * d'tor
 */
VCopyPixelsContext::~VCopyPixelsContext()
{
}

void VCopyPixelsContext::MakeCurrent()
{
	m_pParentContext->MakeCurrent();
}

void VCopyPixelsContext::SwapBuffers()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);

	glReadBuffer(GL_BACK);

	glCopyTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		0, 0,
		0, 0,
		m_nTextureWidth, m_nTextureHeight);

	//glCopyTexImage2D(
	//	GL_TEXTURE_2D,
	//	0,
	//	GL_RGB,
	//	0, 0,
	//	m_nTextureWidth,
	//	m_nTextureHeight,
	//	0);

	//// build mipmaps
	//vuint width = m_nTextureWidth;
	//vuint height = m_nTextureHeight;
	//vuint level = 0;
	//while(width > 0 && height > 0)
	//{
	//	glCopyTexImage2D(
	//		GL_TEXTURE_2D,
	//		level,
	//		GL_RGB,
	//		0, 0,
	//		m_nTextureWidth,
	//		m_nTextureHeight,
	//		0);

 //       ++level;
	//	width /= 2;
	//	height /= 2;
	//}

//	V3D_ASSERT(glGetError() == GL_NO_ERROR);
}

void VCopyPixelsContext::BindAsTexture(vuint in_nTextureUnit)
{
	V3D_ASSERT(in_nTextureUnit == 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void VCopyPixelsContext::UnbindTexture()
{
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
