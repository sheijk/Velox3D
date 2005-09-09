#include "VPBufferWindowContext.h"

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VPBufferWindowContext::VPBufferWindowContext(HDC in_DeviceContext, const graphics::VDisplaySettings* in_pDisplaySettings) : 
	m_PBufferDeviceContext(0), 
	m_WindowDeviceContext(in_DeviceContext),
	m_PBufferRenderContext(0), 
	m_DisplaySettings(*in_pDisplaySettings)
{
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

	vuint Count;
	vint Pixelformat;
	
	//select Pixel Buffer Format
//	Pixelformat = ChoosePixelFormat(in_DeviceContext, Format);
	wglChoosePixelFormatARB(in_DeviceContext, Format, 0, 1, &Pixelformat, &Count);

	int Attribute[] = 
	{
		WGL_TEXTURE_FORMAT_ARB, WGL_TEXTURE_RGB_ARB,
		WGL_TEXTURE_TARGET_ARB, WGL_TEXTURE_2D_ARB,
        0
	};

	//create Pixel Buffer
	m_PixelBuffer = wglCreatePbufferARB(in_DeviceContext, Pixelformat, m_DisplaySettings.GetWidth(), m_DisplaySettings.GetHeight(), Attribute);

	if(m_PixelBuffer == 0)
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Pixel Buffer wasn't created!");
	}
	else
	{
		vout << "OpenGL Pixel Buffer was created!" << vendl;
	}

	//get Pixel Buffer Device Context
	m_PBufferDeviceContext = wglGetPbufferDCARB(m_PixelBuffer);

	if(m_PBufferDeviceContext == 0)
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Pixel Buffer Device Context wasn't created!");
	}
	else
	{
		vout << "OpenGL Pixel Buffer Device Context was created!" << vendl;
	}

	//get Pixel Buffer Render Context
	m_PBufferRenderContext = wglCreateContext(m_PBufferDeviceContext);

	if(m_PBufferRenderContext == 0)
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Pixel Buffer Render Context wasn't created!");
	}
	else
	{
		vout << "OpenGL Pixel Buffer Render Context was created!" << vendl;
	}
}

VPBufferWindowContext::~VPBufferWindowContext()
{
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
}

void VPBufferWindowContext::SwapBuffers()
{
	//Dummy
}

IVRenderContext* VPBufferWindowContext::CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings)
{
	return new VPBufferWindowContext(m_WindowDeviceContext, in_pDisplaySettings);
}
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------