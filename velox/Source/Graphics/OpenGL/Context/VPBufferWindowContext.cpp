/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VPBufferWindowContext.h"

#include <V3d/Core/VIOStream.h>
#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent
using namespace v3d;

VPBufferWindowContext::VPBufferWindowContext(
	const graphics::VDisplaySettings& in_DisplaySettings,
	IVRenderContext* in_pParentContext        
	) :
	VOffscreenContextBase(in_DisplaySettings, in_pParentContext),
	//m_RenderTexture()
	m_RenderTexture("rgb depth tex2D rtt")
{
	m_RenderTexture.Initialize();
	V3D_ASSERT(m_RenderTexture.Initialize(
		(int) m_DisplaySettings.GetWidth(),
		(int) m_DisplaySettings.GetHeight(),
		true, false));

	vout << "pbuffer: (" << m_RenderTexture.GetMaxS() << ", "
		<< m_RenderTexture.GetMaxT() << ")" << vendl;
}

VPBufferWindowContext::~VPBufferWindowContext()
{
}

void VPBufferWindowContext::MakeCurrent()
{
	m_RenderTexture.BeginCapture();
}

void VPBufferWindowContext::SwapBuffers()
{
	m_RenderTexture.EndCapture();
}

void VPBufferWindowContext::BindAsTexture(vuint in_nTextureUnit)
{
	V3D_ASSERT(in_nTextureUnit == 0);

	m_RenderTexture.EnableTextureTarget();
	m_RenderTexture.Bind();
}

void VPBufferWindowContext::UnbindTexture()
{
	m_RenderTexture.DisableTextureTarget();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

