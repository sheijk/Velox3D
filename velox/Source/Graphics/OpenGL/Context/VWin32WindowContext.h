#ifndef V3D_VWIN32WINDOWCONTEXT_H
#define V3D_VWIN32WINDOWCONTEXT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>
#include <v3d/Core/VIOStream.h>
#include <v3d/Graphics/VDisplaySettings.h>
#include <v3d/Graphics/IVRenderContext.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VWin32WindowContext : public IVRenderContext
{
public:

	VWin32WindowContext(HWND in_hwnd = 0, const graphics::VDisplaySettings* in_pdisplaysettings = 0);
	virtual ~VWin32WindowContext();

	void MakeCurrent();

private:

	graphics::VDisplaySettings m_displaysettings;
	HDC                        m_devicecontext;
	HGLRC                      m_rendercontext;
	HWND                       m_handle;
	PIXELFORMATDESCRIPTOR      m_pixelformat;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

#endif //V3D_VWIN32WINDOWCONTEXT_H