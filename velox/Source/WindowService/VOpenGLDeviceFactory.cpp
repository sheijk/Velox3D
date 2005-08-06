#include "VOpenGLDeviceFactory.h"
#include "../Graphics/OpenGL/VOpenGLDevice.h"

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------
using namespace graphics;

VOpenGLDeviceFactory::VOpenGLDeviceFactory(
	const graphics::VDisplaySettings* in_pDisplaySettings,
	const HWND hWnd) : m_pContext(0)
{
	m_hWnd = hWnd;
	m_pDisplaySettings = in_pDisplaySettings;

}

VOpenGLDeviceFactory::~VOpenGLDeviceFactory()
{
	m_hWnd = 0;
	delete m_pContext;
	m_pContext = 0;
}

graphics::IVDevice* VOpenGLDeviceFactory::CreateDevice()
{
	// create context
	VWin32WindowContext* pContext(new VWin32WindowContext(
		m_hWnd, m_pDisplaySettings));

	// create device
	return new graphics::VOpenGLDevice(*m_pDisplaySettings, pContext);
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
