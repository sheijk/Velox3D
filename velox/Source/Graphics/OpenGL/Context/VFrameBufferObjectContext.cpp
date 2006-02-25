#include "VFrameBufferObjectContext.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/GraphicsExceptions.h>

#include <V3d/OpenGL.h>
#include <GL/glfw.h>
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VFrameBufferObjectContext::VFrameBufferObjectContext(
	const VDisplaySettings& in_DisplaySettings,
	IVRenderContext* in_pParentContext)
	:
	VOffscreenContextBase(in_DisplaySettings, in_pParentContext)
{
	vout << "Creating FBO context from thread " << glfwGetThreadID() << vendl;

	in_pParentContext->MakeCurrent();

	const vuint width = in_DisplaySettings.GetWidth();
	const vuint height = in_DisplaySettings.GetHeight();

	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	vbyte* pixels = new vbyte[width*height*4];
	for(vuint32* pix = (vuint32*)pixels; pix < (vuint*)(pixels)+(width*height); ++pix)
	{
		*pix = 0xFF0000FF;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glGenFramebuffersEXT(1, &m_FBOId);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_FBOId);

	glGenRenderbuffersEXT(1, &m_DepthBufferId);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_DepthBufferId);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_DepthBufferId);

	//glGenRenderbuffersEXT(1, &m_StencilBufferId);
	//glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_StencilBufferId);
	//glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_STENCIL_INDEX, width, height);
	//glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_StencilBufferId);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_TextureId, 0);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

/**
 * d'tor
 */
VFrameBufferObjectContext::~VFrameBufferObjectContext()
{
	glDeleteRenderbuffersEXT(1, &m_DepthBufferId);
	glDeleteFramebuffersEXT(1, &m_FBOId);

	glDeleteTextures(1, &m_TextureId);
}

void VFrameBufferObjectContext::MakeCurrent()
{
	m_pParentContext->MakeCurrent();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_FBOId);
	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_TextureId, 0);
}

void VFrameBufferObjectContext::SwapBuffers()
{
	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, 0, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void VFrameBufferObjectContext::BindAsTexture(vuint in_nTextureUnit)
{
	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_TextureId, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void VFrameBufferObjectContext::UnbindTexture()
{
	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, 0, 0);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
