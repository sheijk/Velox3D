#include "VOpenGLDeviceFactory.h"
#include "../Graphics/OpenGL/VOpenGLDevice.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------


VOpenGLDeviceFactory::VOpenGLDeviceFactory(
	const graphics::VDisplaySettings* in_pDisplaySettings,
	const HWND hWnd)
{
	m_hWnd = hWnd;
	m_pDisplaySettings = in_pDisplaySettings;

}

VOpenGLDeviceFactory::~VOpenGLDeviceFactory()
{
	m_hWnd = 0;
}

graphics::IVDevice* VOpenGLDeviceFactory::CreateDevice()
{
	return new graphics::VOpenGLDevice(m_pDisplaySettings, m_hWnd);
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
