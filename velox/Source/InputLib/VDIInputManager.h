#ifndef V3D_VDIINPUTMANAGER_H
#define V3D_VDIINPUTMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Input/IVInputManager.h>
#include <windows.h>
#include <dinput.h>

#include <list>

#include "VDIInputDevice.h"
#include "VDIKeyboardButton.h"
#include "VDIMouseButton.h"
#include "VDIMouseAxis.h"


//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/** VDIInputManager manages all DirectInput related stuff such as constructing, 
  * destructing und updating the single input devices
  * @author AcrylSword
  * @version 1.0
  */

class VDIInputManager : public IVInputManager
{
protected:
	//VDIInputManager();

	std::list<VDIInputDevice>  m_DeviceList;

	HWND					m_hWnd;
		
	LPDIRECTINPUT8			m_pDI; 
	LPDIRECTINPUTDEVICE8	m_pDIStandardKeyboard;
	LPDIRECTINPUTDEVICE8	m_pDIStandardMouse;

	char				    m_KeyboardBuffer[256];
	VDIKeyboardButton		m_StandardKeys[7];

	DIMOUSESTATE			m_MouseState;
	VDIMouseButton			m_MouseButtons[4];
	VDIMouseAxis			m_MouseXAxis;
	VDIMouseAxis			m_MouseYAxis;

	vbool					InitStandardKeyboardDevice();
	vbool					InitStandardMouseDevice();

	vbool			EnumDevicesCallback( const DIDEVICEINSTANCE* in_pdiDeviceInstance);
	vbool					EnumerateDevices();

public:
							VDIInputManager();
							VDIInputManager( HWND in_hWnd );				
	virtual					~VDIInputManager();

	virtual vbool			Create();
	virtual void			Release();
	void					Update(vfloat32 in_fSeconds);

	virtual IVButton&		GetStandardKey( KeyCode in_myKey );

	virtual IVButton&		GetMouseButton(vuint in_iButton);
	virtual IVRelativeAxis& GetMouseXAxis();
	virtual IVRelativeAxis&	GetMouseYAxis();

	virtual DeviceIterator	DeviceBegin();
	virtual DeviceIterator	DeviceEnd();

	virtual void			Activate() {;};
	virtual void			Deactivate() {;};

private:
	static BOOL CALLBACK	EnumDevicesStaticCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef );
	
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VDIINPUTMANAGER_H
