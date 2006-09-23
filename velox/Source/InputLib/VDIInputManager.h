/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDIINPUTMANAGER_H
#define V3D_VDIINPUTMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Input/IVInputManager.h>
#include <windows.h>
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include <list>

#include "VDIInputDevice.h"
#include "VDIKeyboardDevice.h"
#include "VDIMouseDevice.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/** VDIInputManager manages all DirectInput related stuff such as constructing, 
  * destructing und updating the single input devices
  * It encapsulates a IDirectInput8 object that is used to enumerate and create 
  * all installed input devices. 
  * This input devices are stored in m_DeviceList and can be 
  * acessed through DeviceBegin() and DeviceEnd().
  * There are three other lists that store input devices. This is for easier 
  * device update
  * VDIInputManager also provides acess to the standard keyboard and mouse 
  * device through  GetStandardKeyboard/Mouse()
  *
  * @author AcrylSword / ins
  * @version 1.0
  * @see IVInputManger
  * @see VInputManager
  */
class VDIInputManager : public IVInputManager
{
protected:
	HWND							m_hWnd;
	LPDIRECTINPUT8					m_pDI; 
	VDIMouseDevice*					m_pStandardMouse;
	VDIKeyboardDevice*				m_pStandardKeyboard;

	std::list<IVInputDevice*>		m_DeviceList;
	std::list<VDIMouseDevice*>		m_MouseList;
	std::list<VDIKeyboardDevice*>	m_KeyboardList;
	std::list<VDIInputDevice*>		m_InputDeviceList;

	vbool							EnumDevicesCallback( const DIDEVICEINSTANCE* in_pdiDeviceInstance);
	vbool							EnumerateDevices();
	vbool							InitStandardKeyboardDevice();
	vbool							InitStandardMouseDevice();
	
	virtual void					Create();

public:
									VDIInputManager( HWND in_hWnd );				
	virtual							~VDIInputManager();

	virtual IVKeyboardDevice&		GetStandardKeyboard();
	virtual IVMouseDevice&			GetStandardMouse();

	virtual IVButton&				GetStandardKey(VKeyCode in_Key);
	virtual IVRelativeAxis&			GetMouseXAxis();
	virtual IVRelativeAxis&			GetMouseYAxis();
	virtual IVButton&				GetLeftMouseButton();
	virtual IVButton&				GetRightMouseButton();

	virtual DeviceIterator			DeviceBegin();
	virtual DeviceIterator			DeviceEnd();

	virtual void					Update(vfloat32 in_fSeconds);
	virtual void					Activate();
	virtual void					Deactivate();
	virtual void					SetActive(vbool in_bStatus);

private:
	void							ClearInputData();
	static BOOL CALLBACK			StaticDIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi,
																LPVOID pvRef );
	vbool							m_bRegistered;
	vbool m_bActive;
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VDIINPUTMANAGER_H

