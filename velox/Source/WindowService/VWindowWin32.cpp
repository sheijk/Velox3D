#include "VWindowWin32.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VIOStream.h>
#include "../Graphics/OpenGL/VOpenGLDevice.h"
#include "../InputLib/VDIInputManager.h"

#include "VOpenGLDeviceFactory.h"

#include <v3d/Core/MemManager.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
using namespace graphics;
//-----------------------------------------------------------------------------
vbool VWindowWin32::bFocus;
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
		
		case WM_ACTIVATE:
		{
			switch(wParam)
			{
				case WA_ACTIVE:
				{
					VWindowWin32::bFocus = true;
					return 0;
				} 

				case WA_CLICKACTIVE:
				{
					VWindowWin32::bFocus = true;
					return 0;
				}

				case WA_INACTIVE:
				{
					VWindowWin32::bFocus = false;
					return 0;
				}
			}
		}
	}

return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
//-----------------------------------------------------------------------------

VWindowWin32::VWindowWin32()
{
	hInstance = 0;
	hWnd = 0;
	bFocus = false;
	IVUpdateable::Register();
}
//-----------------------------------------------------------------------------

VWindowWin32::~VWindowWin32()
{
	// release device
	delete m_Device;
	Unregister();
}
//-----------------------------------------------------------------------------
void VWindowWin32::SetActive()
{
	SetFocus(hWnd);
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
		V3D_THROW(VWin32Exception, "registering window failed!");
	}
}
//-----------------------------------------------------------------------------

void VWindowWin32::Unregister()
{
	vout << "Unregistering window..." << vendl;
	if(hWnd && !DestroyWindow(hWnd))
	{
		V3D_THROW(VWin32Exception, "destroying window failed!");
	}
	

	hWnd = 0;

	if (!UnregisterClass(m_Name.c_str(), hInstance))
	{
		V3D_THROW(VWin32Exception, "unregistering window failed!");
	}

	hInstance = 0;
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
		AdjustWindowRectEx(&WindowRect, WS_POPUP, FALSE, WS_EX_APPWINDOW);

		hWnd = CreateWindowEx(WS_EX_APPWINDOW |
								WS_EX_WINDOWEDGE,
								m_Name.c_str(),
								m_Name.c_str(),
								//WS_OVERLAPPEDWINDOW |
								//WS_CLIPSIBLINGS |
								//WS_CLIPCHILDREN,
								0,
								m_DisplaySettings.m_iWinCoordX,
								m_DisplaySettings.m_iWinCoordY,
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

	QueryInputManager();
	QueryGraphicsDevice();
}
//-----------------------------------------------------------------------------

void VWindowWin32::ChangeDisplay(graphics::VDisplaySettings* in_pInfo)
{

	m_DisplaySettings = *in_pInfo;
	vout << "Changing display settings..." << vendl;
	Destroy();
	Create(m_Name.c_str());
}
//-----------------------------------------------------------------------------

void VWindowWin32::Update(vfloat32 in_fSeconds)
{

	m_pInputManager->SetActive(bFocus);

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

	if(m_DisplaySettings.m_sAPIType == "OpenGL")
	{
		vout << "Using OpenGL API..." << vendl;
		m_pDeviceFactory = new VOpenGLDeviceFactory(&m_DisplaySettings, hWnd);
	}
	
	else
	{
		V3D_THROW(VWin32Exception, "only open gl support available");
	}

	m_Device = m_pDeviceFactory->CreateDevice();
	
	V3D_ASSERT(m_Device != 0);
	
	return *m_Device;
}

input::IVInputManager& VWindowWin32::QueryInputManager()
{
	vout << "---------------------------" << vendl;
	vout << "Query input manager..." << vendl;

	if (m_pInputManager)
		return *m_pInputManager;

	vout << "Using DirectInput..." << vendl;
	m_pInputManager = new input::VDIInputManager(hWnd);
	
	vout << "---------------------------" << vendl;

	V3D_ASSERT(m_pInputManager != 0);

	return *m_pInputManager;	
}
//-----------------------------------------------------------------------------

void VWindowWin32::SetTitle(VStringParam in_sName)
{
	SetWindowText(hWnd, in_sName);
}
//-----------------------------------------------------------------------------
void VWindowWin32::SetDisplaySettings(
	 const graphics::VDisplaySettings* in_pDisplaySettings)
{
	m_DisplaySettings = *in_pDisplaySettings;
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
