#include "VDIMouseDevice.h"
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/VAssert.h>
#include <v3d/Input/VInputExceptions.h>
#include <v3d/Input/IVInputDevice.h>
#include <v3d/Core/MemManager.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
 * This constructor shouldn't ever be used
 * @author AcrylSword
 */
VDIMouseDevice::VDIMouseDevice()
{
	m_pDevice=0;
}

/**
* This constructor creates a mouse device 
* 
* @author AcrylSword
*/
VDIMouseDevice::VDIMouseDevice( const DIDEVICEINSTANCE in_DeviceInstance,
							    const LPDIRECTINPUT8 in_pDI,
								const HWND in_hWnd ) 
	: m_DeviceInstance(in_DeviceInstance)
{
	V3D_ASSERT(in_pDI != 0);
	V3D_ASSERT(in_hWnd != 0);
	
	CreateDevice(in_pDI, in_hWnd);
	CreateDeviceObjects();
}

VDIMouseDevice::~VDIMouseDevice()
{
	m_InputHelper.Release();

	m_pDevice->Unacquire();
	m_pDevice->Release();
	m_pDevice = 0;
}

/**
 * Create the IDirectInput8 object
 *
 * 
 * @param in_pDI	A valid IDirectInput8 object that is used to create the mouse 
 *					device
 * @param in_hWnd	The window handle that is associated with the input manager
 * @return			What do you guess?
 *
 * @author			AcrylSword
 */
vbool VDIMouseDevice::CreateDevice(const LPDIRECTINPUT8 in_pDI,
								   const HWND in_hWnd )
{
	HRESULT hr;

	if ( DI_OK != ( hr = in_pDI->CreateDevice(m_DeviceInstance.guidInstance, &m_pDevice, NULL) ) )
	{
		vout << "failed: IDirectInput8::CreateDevice() says:" << hr << vendl;
		return false;
	}

	if ( DI_OK != ( hr = m_pDevice->SetDataFormat(&c_dfDIMouse2)) )
	{
		vout << "failed: IDirectInputDevice8::SetDataFormat() says: " <<hr << vendl;
		return false;
	}

	if ( DI_OK != (hr = m_pDevice->SetCooperativeLevel( in_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)) )
	{
		vout << "failed: IDirectInputDevice8::SetCooperativeLevel() says: " << hr << vendl;
		return false;
	}

	if ( DI_OK != (hr = m_pDevice->Acquire()) )
	{
		vout << "failed: IDirectInputDevice8::Acquire() says: " << hr << vendl;
		return false;
	}

	ZeroMemory(&m_DevCaps, sizeof(m_DevCaps));
	m_DevCaps.dwSize = sizeof(m_DevCaps);

	if ( DI_OK != (hr = m_pDevice->GetCapabilities(&m_DevCaps)) )
	{
		vout << "failed: IDirectInputDevice8::GetCapabilities() says: " << hr << vendl;
		return false;
	}

	return true;
}

/**
 * Create objects for the DIMouseState2 structure.
 * Maybe this can be done more correct with object enumeration
 * but I don't see a way.
 *
 * @author AcrylSword
 */
vbool VDIMouseDevice::CreateDeviceObjects()
{
	m_LeftButton = new VDIButton("Left Button");
	m_RightButton = new VDIButton("RightButton");

	m_XAxis = new VDIRelativeAxis("X-Axis");
	m_YAxis = new VDIRelativeAxis("Y-Axis");
	m_Wheel = new VDIRelativeAxis("Mouse Wheel");

	m_InputHelper.m_ButtonList.push_back(m_LeftButton);
	m_InputHelper.m_ButtonList.push_back(m_RightButton);

	m_InputHelper.m_RelativeAxisList.push_back(m_XAxis);
	m_InputHelper.m_RelativeAxisList.push_back(m_YAxis);
	m_InputHelper.m_RelativeAxisList.push_back(m_Wheel);

	return true;
}

/**
 * Returns the number of mouse buttons
 *
 * @return The number of buttons this mouse device has
 * @author AcrylSword
 */
vuint VDIMouseDevice::GetButtonCount()
{
	return m_InputHelper.m_ButtonList.size();
}

/**
* Returns a reference to the desired mouse button
*
* @return Reference to the mouse button
* @author AcrylSword
* @todo maybe implemement a map<vuint, IVButton*>?
*/
IVButton& VDIMouseDevice::GetButton(const vuint in_Number)
{
	V3D_ASSERT( in_Number < GetButtonCount());

	IVInputDevice::ButtonIterator Iter = ButtonBegin();
	for( vuint i(0); i<in_Number; ++i, ++Iter);
    
	return *Iter;
}

/**
 * Returns a reference to the left mouse button
 *
 * @return A reference to the left mouse button
 * @author AcrylSword
 */
IVButton& VDIMouseDevice::GetLeftButton()
{
	return *m_LeftButton;
}
/**
* Returns a reference to the right mouse button
*
* @return A reference to the right mouse button
* @author AcrylSword
*/
IVButton& VDIMouseDevice::GetRightButton()
{
	return *m_RightButton;
}

/**
 * Returns a reference to the mouse x axis
 *
 * @return A reference to the X axis
 * @author AcrylSword
 */
IVRelativeAxis& VDIMouseDevice::GetXAxis()
{
	return *m_XAxis;
}

/**
* Returns a reference to the mouse y axis
*
* @return A reference to the Y axis
* @author AcrylSword
*/
IVRelativeAxis& VDIMouseDevice::GetYAxis()
{
	return *m_YAxis;
}

/**
* Returns a reference to the mouse wheel
*
* @return A reference to the wheel
* @author AcrylSword
*/
IVRelativeAxis& VDIMouseDevice::GetWheel()
{
	return *m_Wheel;
}

/**
* 
*
* @author AcrylSword
*/
void VDIMouseDevice::Update()
{
	HRESULT hr;
	DIMOUSESTATE2 mouseState;

	ZeroMemory(&mouseState, sizeof(mouseState));

	hr = m_pDevice->GetDeviceState( sizeof(DIMOUSESTATE2),
		(LPVOID) &mouseState );

	if ( hr != DI_OK )
		if ( hr == DIERR_NOTACQUIRED )
		{
			m_pDevice->Acquire();
			m_pDevice->GetDeviceState( sizeof(DIMOUSESTATE2),
				(LPVOID) &mouseState );

			if ( hr != DI_OK )
				V3D_THROW(VUpdateException, "Input update error");
		}

	m_LeftButton->Set( mouseState.rgbButtons[0] & 0x80 );
	m_RightButton->Set( mouseState.rgbButtons[1] & 0x80 );

	//vout << mouseState.lX << vendl;
	
	m_XAxis->Set( mouseState.lX );
	m_YAxis->Set( mouseState.lY );
	m_Wheel->Set( mouseState.lZ );
}

/**
 * 
 *
 * @author AcrylSword
 */
VStringRetVal VDIMouseDevice::GetName()
{
	return m_DeviceInstance.tszInstanceName;
}

/**
 * Delegates method call to VInputDevice::GetType()
 *
 * @author AcrylSword
 */
IVInputDevice::DeviceType VDIMouseDevice::GetType()
{
	return IVInputDevice::Mouse;
}

/**
 * Delegates method call to VInputDeviceHelper::ButtonBegin()
 *
 * @author AcrylSword
 */
IVInputDevice::ButtonIterator VDIMouseDevice::ButtonBegin()
{
	return m_InputHelper.ButtonBegin();
}
/**
 * Delegates method call to VInputDeviceHelper::ButtonEnd()
 *
 * @author AcrylSword
 */
IVInputDevice::ButtonIterator VDIMouseDevice::ButtonEnd()
{
	return m_InputHelper.ButtonEnd();
}

/**
 * Delegates method call to VInputDeviceHelper::AbsoluteAxisBegin() 
 *
 * @author AcrylSword
 */
IVInputDevice::AbsoluteAxisIterator VDIMouseDevice::AbsoluteAxisBegin()
{
	return m_InputHelper.AbsoluteAxisBegin();
}
/**
 * Delegates method call to VInputDeviceHelper::AbsoluteAxisEnd()
 *
 * @author AcrylSword
 */
IVInputDevice::AbsoluteAxisIterator	VDIMouseDevice::AbsoluteAxisEnd()
{
	return m_InputHelper.AbsoluteAxisEnd();
}

/**
 * Delegates method call to VInputDeviceHelper::RelativeAxisBegin()
 *
 * @author AcrylSword
 */
IVInputDevice::RelativeAxisIterator	VDIMouseDevice::RelativeAxisBegin()
{
	IVInputDevice::RelativeAxisIterator temp = m_InputHelper.RelativeAxisBegin();
	IVRelativeAxis* temp2 = &(*temp);
	
	return temp;
}

/**
 * Delegates method call to VInputDeviceHelper::RelativeAxisEnd()
 *
 * @author AcrylSword
 */
IVInputDevice::RelativeAxisIterator	VDIMouseDevice::RelativeAxisEnd()
{
	return m_InputHelper.RelativeAxisEnd();
}

//-----------------------------------------------------------------------------
} // namespace input	
} // namespace v3d
//-----------------------------------------------------------------------------