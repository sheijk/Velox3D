/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VDIInputDevice.h"
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/VAssert.h>
#include <v3d/Input/VInputExceptions.h>
#include "VDIButton.h"
#include "VDIRelativeAxis.h"
#include "VDIAbsoluteAxis.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
 * Standard constructor. Justs sets the device pointer to 0;
 * This constructor is protected, so it doesn't make any sense.
 * @author AcrylSword
 */
VDIInputDevice::VDIInputDevice()
{
	m_pDevice = 0;
}

/**
 * This constructor create the DirectInputDevice8 object that is 
 * described by the DIDEVICEINSTANCE structure and starts enumeration
 * of all device objects. A VCreationException is thrown if an error 
 * occures during device creation.
 *
 * @param in_DeviceInstance Describtion of the DirectInput device that 
 *                          is to be created.
 * @param in_pDI			Pointer to a valid IDirectInput8 object. 
 *                          Cannot be 0;
 * @param in_hWnd			Pointer to the windows that is associated
 *                          with the input manager. Cannot be 0
 *
 * @execption VCreationException VCreationException is thrown on an 
 *                               error during device creation.                        
 * @author AcrylSword
 */
VDIInputDevice::VDIInputDevice( const DIDEVICEINSTANCE in_DeviceInstance,
								const LPDIRECTINPUT8 in_pDI,
								const HWND in_hWnd,
								DeviceType in_DeviceType = Undefined )
								: m_DeviceInstance(in_DeviceInstance),
								  m_pDevice(0),
								  m_DeviceType(in_DeviceType)
{
	V3D_ASSERT( in_pDI != 0 );
	V3D_ASSERT( in_hWnd != 0);

	//init DI structures
	ZeroMemory(&m_DevCaps, sizeof(m_DevCaps));
	m_DevCaps.dwSize = sizeof(m_DevCaps);

	// lets create a device
	vout << "Init input device: " << m_DeviceInstance.tszInstanceName << "...";

	if ( !Create( in_pDI, in_hWnd) )
		V3D_THROW(VCreationException, "Could not create DI device");

	EnumerateDeviceObjects();

	vout << " sucessful" << vendl;
}

/**
 * The destructor deletes all device objects in the lists, sets its pointers
 * to zero, clears the list and finaly releases the IDirectInputDevice8 object
 *
 * @author AcrylSword
 */
VDIInputDevice::~VDIInputDevice()
{	
	m_InputHelper.Release();

	m_pDevice->Unacquire();
	m_pDevice->Release();
	m_pDevice = 0;
}

/**
 * This method creates the DirectInput device, sets the appropriate
 * data format and cooperative level. After that the device is pre-
 * pared for retrivial of buffered data.
 * 
 * @param in_DI	Pointer to a valid IDirectInput8 object
 * @param in_hWnd Pointer to the windows that is associated
 *                          with the input manager. 
 *
 * @name AcrylSword
 */
vbool VDIInputDevice::Create(LPDIRECTINPUT8 in_pDI, HWND in_hWnd)
{
	HRESULT hr;

	if ( DI_OK != ( hr = in_pDI->CreateDevice(m_DeviceInstance.guidInstance, &m_pDevice, NULL) ) )
	{
		vout << "failed: IDirectInput8::CreateDevice() says:" << hr << vendl;
		return false;
	}

	switch ( GET_DIDEVICE_TYPE( m_DeviceInstance.dwDevType ) )
	{
		case DI8DEVTYPE_JOYSTICK:	hr = m_pDevice->SetDataFormat(&c_dfDIJoystick2);
									//m_DeviceType = IVInputDevice::Joystick;
									break;
		case DI8DEVTYPE_GAMEPAD:	hr = m_pDevice->SetDataFormat(&c_dfDIJoystick2);
									//m_DeviceType = IVInputDevice::Joystick;
									break;
		case DI8DEVTYPE_KEYBOARD:	hr = m_pDevice->SetDataFormat(&c_dfDIKeyboard);
									//m_DeviceType = IVInputDevice::Keyboard;
									break;
		case DI8DEVTYPE_MOUSE:		hr = m_pDevice->SetDataFormat(&c_dfDIMouse2);
									//m_DeviceType = IVInputDevice::Mouse;
									break;
		default:					hr = DIERR_INVALIDPARAM;
									break;
	}

	if ( DI_OK != hr )
	{
		vout << "failed: IDirectInputDevice8::SetDataFormat() says: " <<hr << vendl;
		return false;
	}

	if ( DI_OK != (hr = m_pDevice->SetCooperativeLevel( in_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)) )
	{
		vout << "failed: IDirectInputDevice8::SetCooperativeLevel() says: " << hr << vendl;
		return false;
	}

	// Set device properties
	DIPROPDWORD Properties = {0};
	Properties.diph.dwSize = sizeof(DIPROPDWORD);
	Properties.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	Properties.diph.dwHow = DIPH_DEVICE;
	Properties.dwData = 16;

	// Allocate a buffer for input events
	if ( DI_OK != (hr=m_pDevice->SetProperty( DIPROP_BUFFERSIZE, &Properties.diph)) )
	{
		vout << "failed: IDirectInputDevice8::SetProperty() says: " << hr << vendl;
	}

	if ( DI_OK != (hr = m_pDevice->Acquire()) )
	{
		vout << "failed: IDirectInputDevice8::Acquire() says: " << hr << vendl;
		return false;
	}

	m_pDevice->GetCapabilities(&m_DevCaps);
	return true;
}

/**
 * The method starts the DirectInput enumeration of device objects.
 * For each device object the EnumDeviceObjectCallback method is 
 * called. For more detailed information about the callback see
 * StaticDIEnumDeviceObjectsCallback().
 *
 * @author AcrylSword
 */
void VDIInputDevice::EnumerateDeviceObjects()
{
	HRESULT hr;

	hr = m_pDevice->EnumObjects(&StaticDIEnumDeviceObjectsCallback, this, DIDFT_ALL);
}

/**
 * This method examines a device objects, creates the matching velox 
 * device object (IVButton, IVRelativeAxis or IVAbsoluteAxis) and 
 * puts them into the appropriate lists.
 *
 * @param in_pDOI The device object that is currently progressed.
 *
 * @author AcrylSword
 */
vbool VDIInputDevice::EnumDeviceObjectCallback(const DIDEVICEOBJECTINSTANCE* in_pDOI)
{
	if ( in_pDOI->dwType & DIDFT_ABSAXIS )
	{
	    m_InputHelper.m_AbsoluteAxisList.push_back( new VDIAbsoluteAxis(in_pDOI->tszName) );
		return true;
	}
	
	if ( in_pDOI->dwType & DIDFT_RELAXIS )
	{
		m_InputHelper.m_RelativeAxisList.push_back( new VDIRelativeAxis(in_pDOI->tszName) );
		return true;
	}
	
	if ( in_pDOI->dwType & DIDFT_BUTTON )
    {
        m_InputHelper.m_ButtonList.push_back( new VDIButton(in_pDOI->tszName) );
		return true;
    }
	
    vout << "Found a unkown device object: " << in_pDOI->tszName << vendl;
	
    return true;
}

/**
 * Returns the name of this device
 * 
 * @return The name of this device
 * @author AcrylSword
 */
VStringRetVal VDIInputDevice::GetName()
{
	return m_DeviceInstance.tszInstanceName;
}

/**
 * !!!THIS FUNCTION IS HIGHLY UNPERFORMANT!!!
 * 
 *
 * @author AcrylSword
 */
void VDIInputDevice::Update()
{
	
	DIDEVICEOBJECTDATA DeviceData[16];
	DWORD   Items = 16;

	m_pDevice->Acquire();  
	m_pDevice->Poll();
	m_pDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), DeviceData, &Items, 0 );

	for ( DWORD i=0; i<Items; i++ )
	{
		VString Name;
		DIDEVICEOBJECTINSTANCE ObjectInstance = {0};
		ObjectInstance.dwSize = sizeof(DIDEVICEOBJECTINSTANCE);

		m_pDevice->GetObjectInfo( &ObjectInstance, DeviceData[i].dwOfs, DIPH_BYOFFSET );
		Name = ObjectInstance.tszName;

		if (ObjectInstance.dwType & DIDFT_ABSAXIS)
		{
			VInputDeviceHelper::STLAbsoluteIter Iter;
			
			for ( Iter = m_InputHelper.m_AbsoluteAxisList.begin();
				  Iter != m_InputHelper.m_AbsoluteAxisList.end();
				  ++Iter )
				if ( (*Iter)->GetName() == Name )
					 (*Iter)->Set( static_cast<vfloat32>(DeviceData[i].dwData) );
		}

		if (ObjectInstance.dwType & DIDFT_RELAXIS)
		{
			VInputDeviceHelper::STLRelativeIter Iter;
			
			for ( Iter = m_InputHelper.m_RelativeAxisList.begin();
				  Iter != m_InputHelper.m_RelativeAxisList.end();
				  ++Iter )
				if ( (*Iter)->GetName() == Name )
					 (*Iter)->Set( static_cast<vfloat32>(DeviceData[i].dwData) );
		}

		if ( ObjectInstance.dwType & DIDFT_BUTTON )
		{
			VInputDeviceHelper::STLButtonIter Iter;

			for ( Iter = m_InputHelper.m_ButtonList.begin();
				  Iter != m_InputHelper.m_ButtonList.end();
				  ++Iter )
				if ( (*Iter)->GetName() == Name )
					 (*Iter)->SetDown( (DeviceData[i].dwData & 0x80) != 0 );
		}
	}
}

/**
 * Non-static callback methods does not work. This static callback
 * function redirects a method call to the EnumDeviceObjectCallback()
 * method.
 *
 * @param lpddoi The device object that is enumerated
 * @param pvRef	 Pointer to user data. In this case pvRef is the this
 *               pointer of the class that performs the enumeration
 * @author AcrylSword
 */
BOOL VDIInputDevice::StaticDIEnumDeviceObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	return ((VDIInputDevice*) pvRef)->EnumDeviceObjectCallback(lpddoi);
}

/**
* Returns the type of this device. 
* The default value is 'Undefined'
*
* @see IVInputDevice::DeviceType
* @return The device type
* @author AcrylSword
*/
IVInputDevice::DeviceType VDIInputDevice::GetType()
{
	return m_DeviceType;
}

/**
* Delegates method call to VInputDeviceHelper::ButtonBegin()
*
* @author AcrylSword
*/
IVInputDevice::ButtonIterator VDIInputDevice::ButtonBegin()
{
	return m_InputHelper.ButtonBegin();
}
/**
* Delegates method call to VInputDeviceHelper::ButtonEnd()
*
* @author AcrylSword
*/
IVInputDevice::ButtonIterator VDIInputDevice::ButtonEnd()
{
	return m_InputHelper.ButtonEnd();
}

/**
* Delegates method call to VInputDeviceHelper::AbsoluteAxisBegin() 
*
* @author AcrylSword
*/
IVInputDevice::AbsoluteAxisIterator VDIInputDevice::AbsoluteAxisBegin()
{
	return m_InputHelper.AbsoluteAxisBegin();
}
/**
* Delegates method call to VInputDeviceHelper::AbsoluteAxisEnd()
*
* @author AcrylSword
*/
IVInputDevice::AbsoluteAxisIterator	VDIInputDevice::AbsoluteAxisEnd()
{
	return m_InputHelper.AbsoluteAxisEnd();
}

/**
* Delegates method call to VInputDeviceHelper::RelativeAxisBegin()
*
* @author AcrylSword
*/
IVInputDevice::RelativeAxisIterator	VDIInputDevice::RelativeAxisBegin()
{
	return m_InputHelper.RelativeAxisBegin();
}

/**
* Delegates method call to VInputDeviceHelper::RelativeAxisEnd()
*
* @author AcrylSword
*/
IVInputDevice::RelativeAxisIterator	VDIInputDevice::RelativeAxisEnd()
{
	return m_InputHelper.RelativeAxisEnd();
}
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
