#include "VPBufferWindowContext.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VPBufferWindowContext::VPBufferWindowContext(const VDisplaySettings* in_pdisplaysettings) : m_devicecontext(0), m_rendercontext(0), m_pbufferdevicecontext(0), m_pbufferrendercontext(0), m_displaysettings(*in_pdisplaysettings)
{
	m_devicecontext = wglGetCurrentDC();
	m_rendercontext = wglGetCurrentContext();

	const int Attribute[] = {
	    WGL_SUPPORT_OPENGL_ARB, true,
        WGL_DRAW_TO_PBUFFER_ARB, true,
        WGL_RED_BITS_ARB, 16,
        WGL_GREEN_BITS_ARB, 16,
        WGL_BLUE_BITS_ARB, 16,
        WGL_ALPHA_BITS_ARB, 16,
		WGL_DEPTH_BITS_ARB, m_displaysettings.GetDepthBits(),
        WGL_DOUBLE_BUFFER_ARB, false,
		0
	};

	vuint count = 0;
	vint pixelformat = 0;
	wglChoosePixelFormatARB(m_devicecontext, reinterpret_cast<const int*>(&Attribute), 0, 1, &pixelformat, &count);
}

VPBufferWindowContext::~VPBufferWindowContext()
{
	wglDeleteContext(m_pbufferrendercontext);
    wglReleasePbufferDCARB(m_pixelbuffer, m_pbufferdevicecontext);
    wglDestroyPbufferARB(m_pixelbuffer); 
}

void VPBufferWindowContext::MakeCurrent()
{
}
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------