#include "VWindowWin32.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/VIOStream.h>

#include "../Graphics/OpenGL/VOpenGLDevice.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
using namespace v3d::graphics;
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	switch(iMsg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
//-----------------------------------------------------------------------------

VWindowWin32::VWindowWin32()
{
	hInstance = NULL;
	hWnd = NULL;
	IVUpdateable::Register();
}
//-----------------------------------------------------------------------------

VWindowWin32::~VWindowWin32()
{
}
//-----------------------------------------------------------------------------

void VWindowWin32::Register()
{
	vout << "Registering window..." << vendl;
	hInstance = GetModuleHandle(NULL);

	WNDCLASS Register;
	Register.style =         CS_DBLCLKS | CS_OWNDC |
			                 CS_HREDRAW | CS_VREDRAW;

	Register.lpfnWndProc =   (WNDPROC)WindowProc;
	Register.cbClsExtra =    0;
	Register.cbWndExtra =    0;
	Register.hInstance =     NULL; //hinstance
	Register.hIcon =         LoadIcon(NULL, IDI_WINLOGO);
	Register.hCursor =       LoadCursor(NULL, IDC_ARROW);
	Register.hbrBackground = NULL;
	Register.lpszMenuName =  NULL;
	Register.lpszClassName = m_Name.c_str();

	if(!RegisterClass(&Register))
	{
		// TODO: fix
		vout << "registering window failed\n" << vendl;
	}
}
//-----------------------------------------------------------------------------

void VWindowWin32::Unregister()
{
	vout << "Unregistering window..." << vendl;
	if(hWnd && !DestroyWindow(hWnd))
	{
		vout << "destroying window failed\n" << vendl;
	}

	hWnd = NULL;

	if (!UnregisterClass(m_Name.c_str(), hInstance))
	{
		vout << "unregistering window failed\n" << vendl;
	}

	hInstance = NULL;
}
//-----------------------------------------------------------------------------

void VWindowWin32::Destroy()
{
	if(m_DisplaySettings.m_bFullscreen)
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);
	}

	Unregister();
}
//-----------------------------------------------------------------------------

void VWindowWin32::CreateWindow()
{
	RECT WindowRect;

	WindowRect.left		= 0;
	WindowRect.top		= 0;
	WindowRect.right	= m_DisplaySettings.m_iWidth;
	WindowRect.bottom	= m_DisplaySettings.m_iHeight;

	if(m_DisplaySettings.m_bFullscreen)
	{
		AdjustWindowRectEx(&WindowRect, WS_POPUP, FALSE, WS_EX_APPWINDOW);

		hWnd = CreateWindowEx(WS_EX_APPWINDOW,
									m_Name.c_str(),
									m_Name.c_str(),
									WS_POPUP |
									WS_CLIPSIBLINGS |
									WS_CLIPCHILDREN,
									0,
									0,
									WindowRect.right-WindowRect.left,
									WindowRect.bottom-WindowRect.top,
									NULL,
									NULL,
									hInstance,
								    NULL);

			ShowCursor(FALSE);
	}

	else
	{
		AdjustWindowRectEx(&WindowRect, WS_OVERLAPPEDWINDOW, TRUE,
							WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

		hWnd = CreateWindowEx(WS_EX_APPWINDOW |
								WS_EX_WINDOWEDGE,
								m_Name.c_str(),
								m_Name.c_str(),
								//WS_OVERLAPPEDWINDOW |
								WS_CLIPSIBLINGS |
								WS_CLIPCHILDREN,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								NULL,
								NULL,
								hInstance,
								NULL);

		ShowCursor(TRUE);
	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
}
//-----------------------------------------------------------------------------

void VWindowWin32::Create(VStringParam in_pName)
{
	m_Name = in_pName;
	//TODO: error service fuer sowas benutzen (sheijk)
	vout << "Creating window: \"" << in_pName << "\"" << vendl;
	Register();
	CreateWindow();

	QueryGraphicsDevice();
}
//-----------------------------------------------------------------------------

void VWindowWin32::ChangeDisplay(graphics::VDisplaySettings* in_pInfo)
{

	m_DisplaySettings.Assign(in_pInfo);
	vout << "Changing display settings..." << vendl;
	Destroy();
	Create(m_Name.c_str());
}
//-----------------------------------------------------------------------------

void VWindowWin32::Update(vfloat32 in_fSeconds)
{
	MSG msg;

	while(PeekMessage(&msg, hWnd, 0, 0, PM_NOREMOVE)) {


		if (!(GetMessage(&msg, hWnd, 0, 0)))
			return;

		if(msg.message == WM_CLOSE)
		{
			PostQuitMessage(0);
		}


		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
//-----------------------------------------------------------------------------

IVDevice& VWindowWin32::QueryGraphicsDevice()
{
	vout << "Query graphics device..." << vendl;
	if(m_Device)
		return *m_Device;

	/**
	 * Insert API dependant device implementation here
	 */

	//REMINDER: in einen system abhaengigen factory service auslagern (sheijk)

	if(m_DisplaySettings.m_sAPIType == "OpenGL")
	{
		vout << "Using OpenGL API..." << vendl;
		m_Device = new VOpenGLDevice(&m_DisplaySettings, hWnd);
	}

	else if(m_DisplaySettings.m_sAPIType == "Direct3D")
	{
		m_Device = NULL;
	}

	return *m_Device;
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
