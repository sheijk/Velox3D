//
// *** VWindow ***
//
// Synopsis:
//    - Window implementation for win32 platform
//
// Description:
//    - 
//
// See also:
//    - 
//
#ifndef V3D_VWINDOW_H
#define V3D_VWINDOW_H

#include <Core/IVWindow.h>
#include <utils/VDisplayProperty.h>

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


class VWindow : public VIWindow
{
	friend LRESULT CALLBACK ::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	HWND m_hWnd;

public:

	VWindow();

	VRESULT Initialize(HINSTANCE hInstanceHandle, vint iWidth, vint iHeight,
							  	vint iBitsPerPixel, vbool bFullscreen);
    VRESULT Shutdown();

	HWND GetWindowHandle();

	void SetWindowName(const string& Name);
	
	vint HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	
	
};



#endif