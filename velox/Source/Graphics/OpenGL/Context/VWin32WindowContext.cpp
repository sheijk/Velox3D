#include "VWin32WindowContext.h"

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VWin32WindowContext::VWin32WindowContext(HWND in_hwnd, const VDisplaySettings* in_pDisplaySettings) : m_devicecontext(0), m_rendercontext(0), m_handle(in_hwnd), m_DisplaySettings(*in_pDisplaySettings)
{
	//create a OpenGL Device Context
	m_devicecontext = GetDC(m_handle);

	if(m_devicecontext == 0)
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Device Context wasn't created!");
	}
	else
	{
		vout << "OpenGL Device Context was created!" << vendl;
	}

	//create Pixel Format
	memset(&m_pixelformat, 0, sizeof(PIXELFORMATDESCRIPTOR));
	m_pixelformat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    m_pixelformat.nVersion = 1;
    m_pixelformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    m_pixelformat.iPixelType = PFD_TYPE_RGBA;
	m_pixelformat.cColorBits = m_DisplaySettings.GetBitsPerPixel();
	m_pixelformat.cDepthBits = m_DisplaySettings.GetDepthBits();
	m_pixelformat.cStencilBits = m_DisplaySettings.GetStencilBits();
    m_pixelformat.iLayerType = PFD_MAIN_PLANE;

	//create and set Pixel Format
	if(!(SetPixelFormat(m_devicecontext, ChoosePixelFormat(m_devicecontext, &m_pixelformat), &m_pixelformat)))
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Pixel Format wasn't selected!");
	}
	else
	{
		vout << "OpenGL Pixel Format was selected!" << vendl;
	}

	//create a OpenGL Render Context
	m_rendercontext = wglCreateContext(m_devicecontext);

	if(m_rendercontext == 0)
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
	if(m_rendercontext != 0)
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(m_rendercontext);
		m_rendercontext = 0;
	}
	if(m_devicecontext != 0)
	{
		ReleaseDC(0, m_devicecontext);
		m_devicecontext = 0;
	}
}

void VWin32WindowContext::MakeCurrent()
{
	wglMakeCurrent(m_devicecontext, m_rendercontext);
}

void VWin32WindowContext::SwapBuffers()
{
	::SwapBuffers(m_devicecontext);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
