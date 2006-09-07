/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Window/IVWindow.h>
#include <v3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include "VWindowManagerWin32.h"
#include "VWindowWin32.h"
#include "../Graphics/OpenGL/VOpenGLDevice.h"
#include "../Graphics/OpenGL/Context/VWin32WindowContext.h"

#include <stdlib.h>
#undef CreateWindow

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

VWindowManagerWin32::VWindowManagerWin32()
{
}

//-----------------------------------------------------------------------------

VWindowManagerWin32::~VWindowManagerWin32()
{
}

//-----------------------------------------------------------------------------

IVWindowManager::IVWindowPtr VWindowManagerWin32::QueryWindow(
	VStringParam in_pName
	)
{
	IVWindowManager::IVWindowPtr window;
	VWindowWin32* window32 = new VWindowWin32;

	//vout << "Window manager creating window:" << vendl;
	window32->Create(in_pName);

	m_iNumWindows++;
	//vout << "-------------------------------------------------------" << vendl;

	window.Assign(window32);
	return window;
}

//-----------------------------------------------------------------------------

IVWindowManager::IVWindowPtr VWindowManagerWin32::QueryWindow(
    VStringParam in_pName,
	const graphics::VDisplaySettings* in_pDisplaySettings
	)
{
	IVWindowManager::IVWindowPtr window;
	VWindowWin32* window32 = new VWindowWin32;

	//vout << "Window manager creating window:" << vendl;
	window32->SetDisplaySettings(in_pDisplaySettings);
	window32->Create(in_pName);

	m_iNumWindows++;
	//vout << "-------------------------------------------------------" << vendl;

	window.Assign(window32);
	return window;
}

IVWindowManager::GraphicsDevicePtr VWindowManagerWin32::CreateGraphicsDevice(
	const graphics::VDisplaySettings& in_Settings,
	PlatformWindowHandle in_Handle)
{
	using graphics::VWin32WindowContext;
	using graphics::VOpenGLDevice;

	HWND hwnd = HWND(in_Handle);

//	GraphicsDevicePtr pDevice(new graphics::VOpenGLDevice(&in_Settings, hwnd));
	VWin32WindowContext* pContext(new VWin32WindowContext(
		hwnd, &in_Settings));

	// create device
	GraphicsDevicePtr pDevice(new VOpenGLDevice(in_Settings, pContext));

	return pDevice;
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------

