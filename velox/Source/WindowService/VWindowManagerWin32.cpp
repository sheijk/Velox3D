#include <v3d/Window/IVWindow.h>
#include <v3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include "VWindowManagerWin32.h"
#include "VWindowWin32.h"
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

IVWindowManager::IVWindowPtr VWindowManagerWin32::CreateWindow(VStringParam in_pName)
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


//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
