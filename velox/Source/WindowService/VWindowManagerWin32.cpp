#include <v3d/Window/IVWindow.h>
#include <v3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include "VWindowManagerWin32.h"
#include "VWindowWin32.h"
#include "../Graphics/OpenGL/VOpenGLDevice.h"

#include <stdlib.h>

//windows.h spackt rum
#undef CreateWindow
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

VWindowManagerWin32::VWindowManagerWin32()
{
	//m_iNumWindows = 0;
}

//-----------------------------------------------------------------------------

VWindowManagerWin32::~VWindowManagerWin32()
{
}

//-----------------------------------------------------------------------------

IVWindowManager::IVWindowPtr VWindowManagerWin32::QueryWindow(VStringParam in_pName)
{
	IVWindowManager::IVWindowPtr window;
	VWindowWin32* window32 = new VWindowWin32;

	vout << "Window manager creating window:" << vendl;
	window32->Create(in_pName);

	m_iNumWindows++;
	vout << "-------------------------------------------------------" << vendl;

	window.Assign(window32);
	return window;
}

IVWindowManager::GraphicsDevicePtr VWindowManagerWin32::CreateGraphicsDevice(
	const graphics::VDisplaySettings& in_Settings,
	PlatformWindowHandle in_Handle)
{
	HWND hwnd = HWND(in_Handle);

	GraphicsDevicePtr pDevice(new graphics::VOpenGLDevice(&in_Settings, hwnd));
	return pDevice;
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
