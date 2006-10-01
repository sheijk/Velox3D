/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VFrameBufferObjectContext.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/GraphicsExceptions.h>

#include <V3d/OpenGL.h>
#include <GL/glfw.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/Scene/IVLightManager.h>
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
	if( ! IsFormatValid(in_DisplaySettings) )
		V3D_THROW(VException, "Cannot create FBO because display format is not supported");

	vout << "Creating FBO context from thread " << glfwGetThreadID() << vendl;

	in_pParentContext->MakeCurrent();

	const vuint width = in_DisplaySettings.GetWidth();
	const vuint height = in_DisplaySettings.GetHeight();

	// create texture
	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	vbyte* pixels = new vbyte[width*height*4];
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

VFrameBufferObjectContext::VFrameBufferObjectContext(
	const VDisplaySettings& in_DisplaySettings,
	IVRenderContext* in_pParentContext,
	NoInitMarker)
	:
	VOffscreenContextBase(in_DisplaySettings, in_pParentContext)
{
	m_TextureId = 0;
	m_FBOId = 0;
	m_DepthBufferId = 0;
	m_StencilBufferId = 0;
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

vbool VFrameBufferObjectContext::IsFormatValid(const VDisplaySettings& in_Settings)
{
	return true;
}

void VFrameBufferObjectContext::MakeCurrent()
{
	m_pParentContext->MakeCurrent();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_FBOId);
}

void VFrameBufferObjectContext::SwapBuffers()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glGenerateMipmapEXT(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void VFrameBufferObjectContext::BindAsTexture(vuint in_nTextureUnit)
{
	m_nTextureUnit = in_nTextureUnit;

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0 + in_nTextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void VFrameBufferObjectContext::UnbindTexture()
{
	glActiveTexture(GL_TEXTURE0 + m_nTextureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

