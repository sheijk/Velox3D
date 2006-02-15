#include "VWin32WindowContext.h"

#include "VCopyPixelsContext.h"
#include "VFrameBufferObjectContext.h"

#include <V3dLib/Property.h>

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

namespace {
	const std::string OFFSCREEN_METHOD_PROPNAME = "v3d.graphics.offscreen-method";
	const std::string OFFSCREEN_FBO = "fbo";
	const std::string OFFSCREEN_COPY = "copy";

	/**
	 * Provide information about the capabilities of a graphics device (it's
	 * underlying opengl context
	 */
	struct VDeviceCaps
	{
		/** number of texture units */
		GLint maxTextures;

		/** supports opengl shading language */
		vbool supportsGLSL;
		/** GL_EXT_FRAMEBUFFER_OBJECT support */
		vbool supportsFBO;

		//vbool isAccelerated;

		VDeviceCaps();

		/** Gathers the infos from the currently active opengl context */
		void GatherInfoFromCurrentContext();

		/** prints all infos to vout */
		void PrintInfo() const;
	};

	VDeviceCaps::VDeviceCaps()
	{
		maxTextures = 0;
		supportsGLSL = false;
		supportsFBO = false;
	}

	void VDeviceCaps::GatherInfoFromCurrentContext()
	{
		glGetIntegerv(GL_MAX_TEXTURE_UNITS, &maxTextures);

		supportsGLSL = GLEW_ARB_fragment_program;
		supportsFBO = GLEW_EXT_framebuffer_object;
	}

	void VDeviceCaps::PrintInfo() const
	{
		vout << "OpenGL Device capabilities:\n";
		vout << "Texture units: " << maxTextures << "\n";
		vout << "Supports GLSL: " << supportsGLSL << "\n";
		vout << "Supports FBO:  " << supportsFBO << "\n";
		vout << vendl;
	}

}

VWin32WindowContext::VWin32WindowContext(HWND in_hwnd, const VDisplaySettings* in_pDisplaySettings) : 
	m_DeviceContext(0), m_RenderContext(0), m_Handle(in_hwnd),
	m_DisplaySettings(*in_pDisplaySettings)
{
	//create a OpenGL Device Context
	m_DeviceContext = GetDC(m_Handle);

	if(m_DeviceContext == 0)
	{
		V3D_THROW(VGraphicException, "Error: Device Context wasn't created!");
	}
	else
	{
		vout << "Device Context was created!" << vendl;
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
		V3D_THROW(VGraphicException, "Error: Pixel Format wasn't selected!");
	}
	else
	{
		vout << "Pixel Format was selected!" << vendl;
	}

	//create a OpenGL Render Context
	m_RenderContext = wglCreateContext(m_DeviceContext);

	if(m_RenderContext == 0)
	{
		V3D_THROW(VGraphicException, "Error: Render Context wasn't created!");
	}
	else
	{
		vout << "Render Context was created!" << vendl;
	}

	GLenum result = glewInit();
	if( result != GLEW_OK )
	{
		vout << "glew init failed: " << glewGetErrorString(result) << vendl;
	}

	VDeviceCaps caps;
	caps.GatherInfoFromCurrentContext();
	caps.PrintInfo();

	if( ! property::ExistsProperty(OFFSCREEN_METHOD_PROPNAME.c_str()) )
	{
		property::SetProperty(OFFSCREEN_METHOD_PROPNAME.c_str(), OFFSCREEN_FBO);
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

	//return new VPBufferWindowContext(*in_pDisplaySettings, this);
	//return new VCopyPixelsContext(*in_pDisplaySettings, this);
	if( property::GetProperty<std::string>(OFFSCREEN_METHOD_PROPNAME.c_str()) == OFFSCREEN_FBO )
	{
		return new VFrameBufferObjectContext(*in_pDisplaySettings, this);
	}
	else
	{
		return new VCopyPixelsContext(*in_pDisplaySettings, this);
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
