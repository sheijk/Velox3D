//
// *** VWindow ***
//
// Synopsis:
//    - Window implementation
//
// Description:
//    - 
//
// See also:
//    - 
//

#include <Core/VWindow.h>


VWindow::VWindow()
{
	m_hWnd	= NULL;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Get a pointer to the window class object.
	VWindow* pWindow;
	
	pWindow	= (VWindow*) GetWindowLong(hWnd, GWL_USERDATA);
	
	DWORD newError = GetLastError();
	
	
	switch (uMsg)
	{
		case WM_NCCREATE:

			pWindow = (VWindow*) ((CREATESTRUCT*)lParam)->lpCreateParams;

			pWindow->m_hWnd = hWnd;
			SetWindowLong(hWnd, GWL_USERDATA, (vlong)pWindow);
		
		break;
		
	
		case WM_DESTROY:
			
			SetWindowLong(hWnd, GWL_USERDATA, 0);
			break;
		
		default:
			break;
	}

	
	if (NULL != pWindow)
		return (pWindow->HandleEvent(uMsg, wParam, lParam));
	else
		return (::DefWindowProc(hWnd, uMsg, wParam, lParam));
}


vint VWindow::HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int iResult = 0;
    
    switch (uMsg)
    {
    case WM_SIZE:
		
	    break;

	case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}
    default:
        // Defer all messages NOT handled here to the Default Window Proc.
        iResult =(vint) ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
        break;
    }

    return iResult;
}

VRESULT VWindow::Initialize(HINSTANCE hInstanceHandle, vint iWidth, vint iHeight,
							 vint iBitsPerPixel, vbool bFullscreen)
{
	
	m_hInstance		= hInstanceHandle;
	
	m_Display.SetWidth(iWidth);
	m_Display.SetHeight(iHeight);
	m_Display.SetBitsPerPixel(iBitsPerPixel);
	m_Display.SetFullscreen(bFullscreen);


	WNDCLASS WndClass;
	
	WndClass.style =         CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	WndClass.lpfnWndProc =   WinProc;
	WndClass.cbClsExtra =    0;
	WndClass.cbWndExtra =    0;
	WndClass.hInstance =     hInstanceHandle;
	WndClass.hIcon =         NULL;
	WndClass.hCursor =       NULL;
	WndClass.hbrBackground = NULL;
	WndClass.lpszMenuName =  
	WndClass.lpszClassName = "Engine";
		
	if(!RegisterClass(&WndClass))
		return VERROR_WINDOW_REGISTRATION;
	
	RECT WindowRect;

	WindowRect.left		= 0;
	WindowRect.top		= 0;
	WindowRect.right	= m_Display.GetWidth();
	WindowRect.bottom	= m_Display.GetHeight();

	if(m_Display.GetFullscreen())
	{
		AdjustWindowRectEx(&WindowRect, WS_POPUP, FALSE, WS_EX_APPWINDOW);
		
		m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		  						"Engine",
								m_sName.c_str(),
								WS_POPUP | 
								WS_CLIPSIBLINGS | 
								WS_CLIPCHILDREN,
 								0,
								0,
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								NULL,
								NULL,
								m_hInstance,
								this);
		
		ShowCursor(false);

		DEVMODE DisplayFormat;

		DisplayFormat.dmSize		= sizeof(DEVMODE);
		DisplayFormat.dmPelsWidth	= m_Display.GetWidth();
		DisplayFormat.dmPelsHeight	= m_Display.GetHeight();
		DisplayFormat.dmBitsPerPel	= m_Display.GetBitsPerPixel();
		DisplayFormat.dmFields	    = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		if (ChangeDisplaySettings(&DisplayFormat,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			//ASSERT("Requesting fullscreen mode failed");  //FIXME!!
			m_Display.SetFullscreen(false);
		}
	}

	
	else
	{
		AdjustWindowRectEx(&WindowRect, WS_OVERLAPPEDWINDOW, TRUE, 
						   WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

		m_hWnd = CreateWindowEx(WS_EX_APPWINDOW | 
								WS_EX_WINDOWEDGE,
								"Engine",
								m_sName.c_str(),
								WS_OVERLAPPEDWINDOW | 
								WS_CLIPSIBLINGS | 
								WS_CLIPCHILDREN,
								0,
								0,
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								NULL,
								NULL,
								m_hInstance,
								this);

		ShowCursor(true);
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow (m_hWnd) ;
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	return VOK;
}

VRESULT VWindow::Shutdown()
{
	if(m_Display.GetFullscreen())
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);
	}

	if(m_hWnd && !DestroyWindow(m_hWnd))
		return VERROR_WINDOW_DESTRUCTION;
		
	m_hWnd = NULL;

	if (!UnregisterClass("Engine", m_hInstance))
		return VERROR_WINDOW_UNREGISTRATION;
		
	return VOK;
}

HWND VWindow::GetWindowHandle()
{
	return m_hWnd;
}

void VWindow::SetWindowName(const string& Name)
{
	m_sName = Name;
}

