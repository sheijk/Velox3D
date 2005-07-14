#include "VBaseTexture.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VBaseTexture::VBaseTexture()
{
	//Dummy
}

VBaseTexture::VBaseTexture(const image::VImage& in_Image, GLenum in_TextureTarget) : m_iTextureTarget(in_TextureTarget)
{
}

VBaseTexture::~VBaseTexture()
{
}

void VBaseTexture::Bind()
{
	glBindTexture(m_iTextureTarget, m_iTextureID);
}

void VBaseTexture::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VTexture2D::VTexture2D(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_2D)
{
	m_iTextureID = in_TextureID;
}

VTexture2D::~VTexture2D()
{
	glDeleteTextures(1, &m_iTextureID);
}

void VTexture2D::Bind()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_iTextureID);
}

void VTexture2D::Unbind()
{
	glDisable(GL_TEXTURE_2D);
}

VUntextured::VUntextured()
{
	//Dummy
}

VUntextured::VUntextured(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, 0)
{
	m_iTextureID = in_TextureID;
}

VUntextured::~VUntextured()
{
}

void VUntextured::Bind()
{
}

void VUntextured::Unbind()
{
}


VCubemapPosX::VCubemapPosX(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_POSITIVE_X)
{
	m_iTextureID = in_TextureID;
}

VCubemapPosX::~VCubemapPosX()
{
}

void VCubemapPosX::Bind()
{
	glEnable(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X, m_iTextureID);
}

void VCubemapPosX::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VCubemapNegX::VCubemapNegX(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_NEGATIVE_X)
{
	m_iTextureID = in_TextureID;
}

VCubemapNegX::~VCubemapNegX()
{
}

void VCubemapNegX::Bind()
{
	glEnable(GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, m_iTextureID);
}

void VCubemapNegX::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VCubemapPosY::VCubemapPosY(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_POSITIVE_Y)
{
	m_iTextureID = in_TextureID;
}

VCubemapPosY::~VCubemapPosY()
{
}

void VCubemapPosY::Bind()
{
	glEnable(GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, m_iTextureID);
}

void VCubemapPosY::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VCubemapNegY::VCubemapNegY(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y)
{
	m_iTextureID = in_TextureID;
}

VCubemapNegY::~VCubemapNegY()
{
}

void VCubemapNegY::Bind()
{
	glEnable(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, m_iTextureID);
}

void VCubemapNegY::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VCubemapPosZ::VCubemapPosZ(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_POSITIVE_Z)
{
	m_iTextureID = in_TextureID;
}

VCubemapPosZ::~VCubemapPosZ()
{
}

void VCubemapPosZ::Bind()
{
	glEnable(GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, m_iTextureID);
}

void VCubemapPosZ::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VCubemapNegZ::VCubemapNegZ(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
{
	m_iTextureID = in_TextureID;
}

VCubemapNegZ::~VCubemapNegZ()
{
}

void VCubemapNegZ::Bind()
{
	glEnable(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, m_iTextureID);
}

void VCubemapNegZ::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VPBufferTexture::VPBufferTexture(const image::VImage& in_Image, int in_TextureID) : m_pContext(0), VBaseTexture(in_Image, GL_TEXTURE_2D)
{
	//create Pixel Buffer
	graphics::VDisplaySettings Settings;
	Settings.SetWidth(in_Image.GetWidth());
	Settings.SetHeight(in_Image.GetHeight());
	m_pContext = new VPBufferWindowContext(&Settings);
}

VPBufferTexture::~VPBufferTexture()
{
	if(m_pContext != 0)
	{
		delete m_pContext;
		m_pContext = 0;
	}
}

void VPBufferTexture::Bind()
{
	//make Pixel Buffer actived
	m_pContext -> MakeCurrent();

	//bind Texture
	glBindTexture(GL_TEXTURE_2D, m_iTextureID);
	wglBindTexImageARB(m_pContext -> GetPixelBuffer(), WGL_FRONT_LEFT_ARB);
}

void VPBufferTexture::Unbind()
{
	//unbind Texture
	wglReleaseTexImageARB(m_pContext -> GetPixelBuffer(), WGL_FRONT_LEFT_ARB);
};

/*VFramebufferTexture::VFramebufferTexture(const image::VImage& in_Image, int in_TextureID) : m_pContext(0), VBaseTexture(in_Image, GL_TEXTURE_2D)
{
	//TODO: check Framebuffer Support

	//create Frame Buffer and the Render Buffer
	glGenFramebuffersEXT(1, &m_iFramebuffer);
	glGenRenderbuffersEXT(1, &m_iRenderbuffer);

	//bind the Buffers
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_iRenderbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, in_Image.GetWidth(), in_Image.GetHeight());
	
	//TODO: Framebuffer States einbauen

	//clear Framebuffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, in_Image.GetWidth(), in_Image.GetHeight());
}

VFramebufferTexture::~VFramebufferTexture()
{
}

void VFramebufferTexture::Bind()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_iFramebuffer);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_iTextureID, 0);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_iRenderbuffer);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}

void VFramebufferTexture::Unbind()
{
	//unbind Framebuffer and Render Buffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
};*/
//-----------------------------------------------------------------------------
}}// namespace v3d::graphics
//-----------------------------------------------------------------------------