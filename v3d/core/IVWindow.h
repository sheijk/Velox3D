

#ifndef V3D_VIWINDOW_H
#define V3D_VIWINDOW_H

#include <windows.h>
#include <string>
#include <Core/VTypes.h>
#include <utils/VDisplayProperty.h>

using std::string;

class VIWindow
{
public:
	
	virtual VRESULT Initialize(HINSTANCE InstanceHandle, vint iWidth, vint iHeight,
							  	vint iBitsPerPixel, vbool bFullscreen) = 0;
	
	virtual void SetWindowName(const string& Name) = 0;

    virtual VRESULT Shutdown() = 0;

	virtual HWND GetWindowHandle() = 0;

	
	VDisplayProperty m_Display;
	string m_sName;
	HINSTANCE m_hInstance;
};

#endif

