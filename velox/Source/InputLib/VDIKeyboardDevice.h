#ifndef V3D_VDIKEYBOARDDEVICE_2004_08_09_H
#define V3D_VDIKEYBOARDDEVICE_2004_08_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Input/IVKeyboardDevice.h>
#include "VDIInputDevice.h"
#include "VDIKeyboardButton.h"

#include <windows.h>
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include <map>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/**
 * DirectInput implementation of a keyboard device
 */
class VDIKeyboardDevice : public IVKeyboardDevice
{
protected:
							VDIKeyboardDevice();
	
	LPDIRECTINPUTDEVICE8	m_pDevice;
	DIDEVICEINSTANCE		m_DeviceInstance;
	DIDEVCAPS				m_DevCaps;
	vchar					m_KeyState[256];

	std::list<VDIKeyboardButton*>	m_ButtonList;
	std::list<VDIRelativeAxis*>		m_RelativeAxisList;
	std::list<VDIAbsoluteAxis*>		m_AbsoluteAxisList;

	std::map<VKeyCode, VDIKeyboardButton*> m_KeyMap;

	vbool					CreateDevice(const LPDIRECTINPUT8 in_pDI,
										 const HWND in_hWnd );
	vbool					CreateDeviceObjects();
	VStringRetVal			GetKeyboardButtonName( vlong in_Index );
public:
							VDIKeyboardDevice( const DIDEVICEINSTANCE in_DeviceStructure, 
											   const LPDIRECTINPUT8 in_pDI,
											   const HWND in_hWnd );
	virtual					~VDIKeyboardDevice();

	void					Update();

	IVButton&				GetKey(const VKeyCode in_KeyCode);

	VStringRetVal			GetName();
	DeviceType				GetType();

	ButtonIterator			ButtonBegin();
	ButtonIterator			ButtonEnd();

	AbsoluteAxisIterator	AbsoluteAxisBegin();
	AbsoluteAxisIterator	AbsoluteAxisEnd();

	RelativeAxisIterator	RelativeAxisBegin();
	RelativeAxisIterator	RelativeAxisEnd();
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIKEYBOARDDEVICE_2004_08_09_H