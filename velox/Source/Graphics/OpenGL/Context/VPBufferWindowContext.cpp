#include "VPBufferWindowContext.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VPBufferWindowContext::VPBufferWindowContext(const VDisplaySettings* in_pDisplaySettings) : m_devicecontext(0), m_rendercontext(0), m_pbufferdevicecontext(0), m_pbufferrendercontext(0), m_DisplaySettings(*in_pDisplaySettings)
{
	m_devicecontext = wglGetCurrentDC();
	m_rendercontext = wglGetCurrentContext();

	const int Format[] = {
	    WGL_SUPPORT_OPENGL_ARB, true,
        WGL_DRAW_TO_PBUFFER_ARB, true,
        WGL_RED_BITS_ARB, 16,
        WGL_GREEN_BITS_ARB, 16,
        WGL_BLUE_BITS_ARB, 16,
        WGL_ALPHA_BITS_ARB, 16,
		WGL_DEPTH_BITS_ARB, m_DisplaySettings.GetDepthBits(),
		WGL_STENCIL_BITS_ARB, m_DisplaySettings.GetStencilBits(),
        WGL_DOUBLE_BUFFER_ARB, true,
		0
	};

	vuint count = 0;
	vint pixelformat = 0;
	
	//select Pixel Buffer Format
	wglChoosePixelFormatARB(m_devicecontext, reinterpret_cast<const int*>(&Format), 0, 1, &pixelformat, &count);

	int Attribute[] = 
	{
		WGL_PBUFFER_LARGEST_ARB, true,
        0, 0 
	};

	//create Pixel Buffer
	m_pixelbuffer = wglCreatePbufferARB(m_devicecontext, pixelformat, m_DisplaySettings.GetWidth(), m_DisplaySettings.GetHeight(), Attribute);

	if(m_pixelbuffer == 0)
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Pixel Buffer wasn't created!");
	}
	else
	{
		vout << "OpenGL Pixel Buffer was created!" << vendl;
	}

	//get Pixel Buffer Device Context
	m_pbufferdevicecontext = wglGetPbufferDCARB(m_pixelbuffer);

	if(m_pbufferdevicecontext == 0)
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Pixel Buffer Device Context wasn't created!");
	}
	else
	{
		vout << "OpenGL Pixel Buffer Device Context was created!" << vendl;
	}

	//get Pixel Buffer Render Context
	m_pbufferrendercontext = wglCreateContext(m_pbufferdevicecontext);

	if(m_pbufferrendercontext == 0)
	{
		V3D_THROW(VGraphicException, "Error: OpenGL Pixel Buffer Render Context wasn't created!");
	}
	else
	{
		vout << "OpenGL Pixel Buffer Render Context was created!" << vendl;
	}

	wglShareLists(m_rendercontext, m_pbufferrendercontext);
}

VPBufferWindowContext::~VPBufferWindowContext()
{
/*	wglDeleteContext(m_pbufferrendercontext);
    wglReleasePbufferDCARB(m_pixelbuffer, m_pbufferdevicecontext);
    wglDestroyPbufferARB(m_pixelbuffer); 
*/}

void VPBufferWindowContext::MakeCurrent()
{
	vint flag = 0;
	wglQueryPbufferARB(m_pixelbuffer, WGL_PBUFFER_LOST_ARB, &flag);

	if(flag)
	{
	}

	wglMakeCurrent(m_pbufferdevicecontext, m_pbufferrendercontext);

	glViewport(m_DisplaySettings.GetX(), m_DisplaySettings.GetY(), m_DisplaySettings.GetWidth(), m_DisplaySettings.GetHeight());

    glDrawBuffer(GL_FRONT);
    glReadBuffer(GL_FRONT); 
}
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------