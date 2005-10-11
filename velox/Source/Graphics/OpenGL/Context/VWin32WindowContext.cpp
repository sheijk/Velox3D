#include "VWin32WindowContext.h"

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VWin32WindowContext::VWin32WindowContext(HWND in_hwnd, const VDisplaySettings* in_pDisplaySettings) : 
	m_DeviceContext(0), m_RenderContext(0), m_Handle(in_hwnd),
	m_DisplaySettings(*in_pDisplaySettings)
{
	//create a OpenGL Device Context
	m_DeviceContext = GetDC(m_Handle);

	if(m_DeviceContext == 0)
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Device Context wasn't created!");
	}
	else
	{
		vout << "OpenGL Device Context was created!" << vendl;
	}

	//create Pixel Format
	memset(&m_Pixelformat, 0, sizeof(PIXELFORMATDESCRIPTOR));
	m_Pixelformat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    m_Pixelformat.nVersion = 1;
    m_Pixelformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    m_Pixelformat.iPixelType = PFD_TYPE_RGBA;
	m_Pixelformat.cColorBits = m_DisplaySettings.GetBitsPerPixel();
	m_Pixelformat.cDepthBits = m_DisplaySettings.GetDepthBits();
	m_Pixelformat.cStencilBits = m_DisplaySettings.GetStencilBits();
    m_Pixelformat.iLayerType = PFD_MAIN_PLANE;

	//create and set Pixel Format
	if(!(SetPixelFormat(m_DeviceContext, ChoosePixelFormat(m_DeviceContext, &m_Pixelformat), &m_Pixelformat)))
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Pixel Format wasn't selected!");
	}
	else
	{
		vout << "OpenGL Pixel Format was selected!" << vendl;
	}

	//create a OpenGL Render Context
	m_RenderContext = wglCreateContext(m_DeviceContext);

	GLenum result = glewInit();
	if( result != GLEW_OK )
	{
		vout << "Warning. Could not initialize glew: "
			<< " (" << result << ") "
			<< glewGetErrorString(result);
	}

	if(m_RenderContext == 0)
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Render Context wasn't created!");
	}
	else
	{
		vout << "OpenGL Render Context was created!" << vendl;
	}
}

VWin32WindowContext::~VWin32WindowContext()
{
	if(m_RenderContext != 0)
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(m_RenderContext);
		m_RenderContext = 0;
	}
	if(m_DeviceContext != 0)
	{
		ReleaseDC(0, m_DeviceContext);
		m_DeviceContext = 0;
	}
}

void VWin32WindowContext::MakeCurrent()
{
	wglMakeCurrent(m_DeviceContext, m_RenderContext);
}

void VWin32WindowContext::SwapBuffers()
{
	::SwapBuffers(m_DeviceContext);
}

VDisplaySettings* VWin32WindowContext::GetDisplaySettings()
{
	return &m_DisplaySettings;
}

IVRenderContext* VWin32WindowContext::CreateOffscreenContext(const graphics::VDisplaySettings* in_pDisplaySettings)
{
	MakeCurrent();

	return new VPBufferWindowContext(m_Handle, in_pDisplaySettings);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
