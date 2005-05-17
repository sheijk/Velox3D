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

//TODO: doku
class VWin32WindowContext : public IVRenderContext
{
public:

	VWin32WindowContext(HWND in_hwnd = 0, const graphics::VDisplaySettings* in_pdisplaysettings = 0);
	virtual ~VWin32WindowContext();

	void MakeCurrent();

private:

	//TODO: aendern zu m_DisplaySettings,.. (->coding conventions)
	//TODO: nicht "huebsch" anordnen, das macht nur viel arbeit wenn eine
	// variable dazu kommt, weil man dann alles umformatiern muss. einfach
	// immer ein space zwischen typ und variablen name reicht
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