/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDIINPUTDEVICE_2004_08_09_H
#define V3D_VDIINPUTDEVICE_2004_08_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Input/IVInputDevice.h>
#include "VInputDeviceHelper.h"

#include <windows.h>
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/**
 * VDIInputDevice is the DirectInput8 implementation of the 
 * IVInputDevice interface. 
 * It is basicly a wrapper for the IDirectInputDevice8 COM-object.
 * The DIDEVICEINSTANCE structure ( received during enumeration in
 * the manager) contains all information about an input device and
 * is used to create the DirectInput device. 
 * After the device was created, the device objects are enumerated 
 * and put in the appropriate std::list. 
 * The lists for buttons and axis and access functionality comes from 
 * VInputDevice.
 * 
 * @author AcrylSword
 * @see IVInputDevice
 * @see VInputDevice
 * @see DirectInput8 documentation
 */
class VDIInputDevice : public IVInputDevice
{
	friend class VDIMouseDevice;
	friend class VDIKeyboardDevice;

protected:
	VInputDeviceHelper		m_InputHelper;

	DeviceType				m_DeviceType;

	LPDIRECTINPUTDEVICE8	m_pDevice;
	DIDEVICEINSTANCE		m_DeviceInstance;
	DIDEVCAPS				m_DevCaps;

							VDIInputDevice();
	void					EnumerateDeviceObjects();
	virtual vbool			EnumDeviceObjectCallback(const DIDEVICEOBJECTINSTANCE* in_pDOI);
	static BOOL CALLBACK	StaticDIEnumDeviceObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi,
															  LPVOID pvRef);
public:
							VDIInputDevice( const DIDEVICEINSTANCE in_DeviceStructure,
											const LPDIRECTINPUT8 in_pDI,
											const HWND in_hWnd,
											const DeviceType in_DeviceType);
	virtual					~VDIInputDevice();

	void					Update();
	virtual vbool			Create(const LPDIRECTINPUT8 in_pDI, const HWND in_hWnd);

	virtual VStringRetVal			GetName();
	virtual DeviceType				GetType();

	virtual ButtonIterator			ButtonBegin();
	virtual ButtonIterator			ButtonEnd();

	virtual AbsoluteAxisIterator	AbsoluteAxisBegin();
	virtual AbsoluteAxisIterator	AbsoluteAxisEnd();

	virtual RelativeAxisIterator	RelativeAxisBegin();
	virtual RelativeAxisIterator	RelativeAxisEnd();
};
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VDIINPUTDEVICE_2004_08_09_H

