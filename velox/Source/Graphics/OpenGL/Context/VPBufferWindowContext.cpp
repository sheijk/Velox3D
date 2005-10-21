#include "VPBufferWindowContext.h"

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VPBufferWindowContext::VPBufferWindowContext(const graphics::VDisplaySettings* in_pDisplaySettings) : 
	m_PBufferDeviceContext(0), 
	m_WindowDeviceContext(0),
	m_PBufferRenderContext(0),
	m_DisplaySettings(*in_pDisplaySettings)
{
	m_WindowDeviceContext = wglGetCurrentDC();
	V3D_ASSERT(m_WindowDeviceContext != 0);

	const int Format[] = {
	    WGL_SUPPORT_OPENGL_ARB, true,
        WGL_DRAW_TO_PBUFFER_ARB, true,
		WGL_BIND_TO_TEXTURE_RGB_ARB, true,
        WGL_COLOR_BITS_ARB, m_DisplaySettings.GetBitsPerPixel(),
		WGL_DEPTH_BITS_ARB, m_DisplaySettings.GetDepthBits(),
		WGL_STENCIL_BITS_ARB, m_DisplaySettings.GetStencilBits(),
        WGL_DOUBLE_BUFFER_ARB, false,
		0
	};

	vuint Count = 0;
	vint Pixelformat;
	
	//select Pixel Buffer Format
	wglChoosePixelFormatARB(m_WindowDeviceContext, Format, 0, 1, &Pixelformat, &Count);

	int Attribute[] = 
	{
		WGL_TEXTURE_FORMAT_ARB, WGL_TEXTURE_RGB_ARB,
		WGL_TEXTURE_TARGET_ARB, WGL_TEXTURE_2D_ARB,
        0
	};

	//create Pixel Buffer
	m_PixelBuffer = wglCreatePbufferARB(m_WindowDeviceContext, Pixelformat, m_DisplaySettings.GetWidth(), m_DisplaySettings.GetHeight(), Attribute);

	if(m_PixelBuffer == 0)
	{
		V3D_THROW(VGraphicException, "Error: Pixel Buffer wasn't created!");
	}
	else
	{
		vout << "Pixel Buffer was created!" << vendl;
	}

	//get Pixel Buffer Device Context
	m_PBufferDeviceContext = wglGetPbufferDCARB(m_PixelBuffer);

	if(m_PBufferDeviceContext == 0)
	{
		V3D_THROW(VGraphicException, "Error: Pixel Buffer Device Context wasn't created!");
	}
	else
	{
		vout << "Pixel Buffer Device Context was created!" << vendl;
	}

	//get Pixel Buffer Render Context
	m_PBufferRenderContext = wglCreateContext(m_PBufferDeviceContext);

	if(m_PBufferRenderContext == 0)
	{
		V3D_THROW(VGraphicException, "Error: Pixel Buffer Render Context wasn't created!");
	}
	else
	{
		vout << "Pixel Buffer Render Context was created!" << vendl;
	}

	if(!wglShareLists(m_PBufferRenderContext, wglGetCurrentContext()))
	{
		V3D_THROW(VGraphicException, "Error: Pixel Buffer Context wasn't connected with the Window Context!");
	}
	else
	{
		vout << "Pixel Buffer Context was connected with the Window Context!" << vendl;
	}

	vint width = m_DisplaySettings.GetWidth();
	vint height = m_DisplaySettings.GetHeight();
	wglQueryPbufferARB(m_PixelBuffer, WGL_PBUFFER_WIDTH_ARB, &width);
	wglQueryPbufferARB(m_PixelBuffer, WGL_PBUFFER_HEIGHT_ARB, &height);
}

VPBufferWindowContext::~VPBufferWindowContext()
{
	glDrawBuffer(GL_BACK);
	glReadBuffer(GL_BACK);

	wglDeleteContext(m_PBufferRenderContext);
    wglReleasePbufferDCARB (m_PixelBuffer, m_PBufferDeviceContext);
    wglDestroyPbufferARB(m_PixelBuffer); 
}

void VPBufferWindowContext::MakeCurrent()
{
	vint flag = 0;
	wglQueryPbufferARB(m_PixelBuffer, WGL_PBUFFER_LOST_ARB, &flag);

	if(flag)
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Pixel Buffer Object is invalid!");
	}

	wglMakeCurrent(m_PBufferDeviceContext, m_PBufferRenderContext);

	glDrawBuffer(GL_FRONT);
	glReadBuffer(GL_FRONT);
	
	glViewport(m_DisplaySettings.GetX(), m_DisplaySettings.GetY(), m_DisplaySettings.GetWidth(), m_DisplaySettings.GetHeight());
}

void VPBufferWindowContext::SwapBuffers()
{
	//Dummy
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