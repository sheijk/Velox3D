#include "VPBufferWindowContext.h"

#include <V3d/Core/VIOStream.h>
#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent
using namespace v3d;

VPBufferWindowContext::VPBufferWindowContext(const graphics::VDisplaySettings* in_pDisplaySettings) : 
	m_DisplaySettings(*in_pDisplaySettings),
	m_RenderTexture()
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

void VPBufferWindowContext::BindTexture()
{
	m_RenderTexture.EnableTextureTarget();
	m_RenderTexture.Bind();
}

void VPBufferWindowContext::UnbindTexture()
{
	m_RenderTexture.DisableTextureTarget();
}

VDisplaySettings* VPBufferWindowContext::GetDisplaySettings()
{
	return &m_DisplaySettings;
}

IVRenderContext* VPBufferWindowContext::CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings)
{
	return new VPBufferWindowContext(in_pDisplaySettings);
}
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------