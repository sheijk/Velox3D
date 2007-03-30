/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDIMOUSEDEVICE_2004_08_09_H
#define V3D_VDIMOUSEDEVICE_2004_08_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Input/IVMouseDevice.h>
#include "VDIInputDevice.h"
#include "VInputDeviceHelper.h"

#include <windows.h>
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>


//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/**
 * DirectInput implementation of a mouse device
 */
class VDIMouseDevice : public IVMouseDevice
{
protected:
							VDIMouseDevice();
	LPDIRECTINPUTDEVICE8	m_pDevice;
	DIDEVICEINSTANCE		m_DeviceInstance;
	DIDEVCAPS				m_DevCaps;
	
	VInputDeviceHelper		m_InputHelper;

	VDIButton*				m_LeftButton;
	VDIButton*				m_RightButton;
	VDIRelativeAxis*		m_XAxis;
	VDIRelativeAxis*		m_YAxis;
	VDIRelativeAxis*		m_Wheel;
    
	vbool					CreateDevice(const LPDIRECTINPUT8 in_pDI,
										 const HWND in_hWnd );
	vbool					CreateDeviceObjects();
public:
							VDIMouseDevice( const DIDEVICEINSTANCE in_DeviceStructure, 
											const LPDIRECTINPUT8 in_pDI,
											const HWND in_hWnd );
	virtual					~VDIMouseDevice();

	void					Update();

	virtual vuint			GetButtonCount();
	virtual IVButton&		GetButton(const vuint in_Number);
	virtual IVButton&		GetLeftButton();
	virtual IVButton&		GetRightButton();

	virtual IVRelativeAxis& GetXAxis();
	virtual IVRelativeAxis& GetYAxis();
	virtual IVRelativeAxis& GetWheel();

	VStringRetVal			GetName();
	DeviceType				GetType();

	ButtonIterator			ButtonBegin();
	ButtonIterator			ButtonEnd();

	AbsoluteAxisIterator	AbsoluteAxisBegin();
	AbsoluteAxisIterator	AbsoluteAxisEnd();

	RelativeAxisIterator	RelativeAxisBegin();
	RelativeAxisIterator	RelativeAxisEnd();

	void ClearInputData();
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIMOUSEDEVICE_2004_08_09_H
