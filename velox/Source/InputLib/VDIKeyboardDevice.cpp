#include "VDIKeyboardDevice.h"
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/VAssert.h>
#include <v3d/Input/VInputExceptions.h>
#include <v3d/Core/MemManager.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
 * This constructor shouldn't ever be used
 * @author AcrylSword
 */
VDIKeyboardDevice::VDIKeyboardDevice()
{
	m_pDevice = 0;
}

/**
 * 
 * @author AcrylSword
 */
VDIKeyboardDevice::VDIKeyboardDevice( const DIDEVICEINSTANCE in_DeviceInstance,
						     		  const LPDIRECTINPUT8 in_pDI,
									  const HWND in_hWnd ) 
	: m_pDevice(0), m_DeviceInstance(in_DeviceInstance)
{
	V3D_ASSERT(in_pDI != 0);
	V3D_ASSERT(in_hWnd != 0);

	if ( !CreateDevice(in_pDI, in_hWnd))
		V3D_THROW(VCreationException, "Could not create input device");

	CreateDeviceObjects();	
}

template<class Iter> void deleteAll(Iter begin, Iter end)
{ 
	for( ; begin != end; ++begin)
	{
		delete *begin;
		*begin = 0;
	}
}


VDIKeyboardDevice::~VDIKeyboardDevice()
{
	m_KeyMap.clear();
	deleteAll(m_ButtonList.begin(), m_ButtonList.end());
	deleteAll(m_RelativeAxisList.begin(), m_RelativeAxisList.end());
	deleteAll(m_AbsoluteAxisList.begin(), m_AbsoluteAxisList.end());

	m_pDevice->Unacquire();
	m_pDevice->Release();
	m_pDevice = 0;
}

/**
* Creates the IDirectInput8 object
*
* 
* @param in_pDI		A valid IDirectInput8 object that is used to create the 
*					keyboard device
* @param in_hWnd	The window handle that is associated with the input manager
* @return			What do you guess?
*
* @author			AcrylSword
*/
vbool VDIKeyboardDevice::CreateDevice(const LPDIRECTINPUT8 in_pDI,
									  const HWND in_hWnd )
{
	HRESULT hr;

	if ( DI_OK != ( hr = in_pDI->CreateDevice(m_DeviceInstance.guidInstance, &m_pDevice, NULL) ) )
	{
		vout << "failed: IDirectInput8::CreateDevice() says:" << hr << vendl;
		return false;
	}

	if ( DI_OK != ( hr = m_pDevice->SetDataFormat(&c_dfDIKeyboard)) )
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

	ZeroMemory(&m_KeyState, 256*sizeof(vchar));

	return true;
}


vbool VDIKeyboardDevice::CreateDeviceObjects()
{
	m_KeyMap[KeyEscape] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_ESCAPE), &m_KeyState[DIK_ESCAPE]);
	m_KeyMap[KeyReturn] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RETURN), &m_KeyState[DIK_RETURN]);
	m_KeyMap[KeyBackSpace] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_BACK), &m_KeyState[DIK_BACK]);
	m_KeyMap[KeyTab] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_TAB), &m_KeyState[DIK_TAB]);
	m_KeyMap[KeyLeftControl] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_LCONTROL), &m_KeyState[DIK_LCONTROL]);
	m_KeyMap[KeyRightControl] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RCONTROL), &m_KeyState[DIK_RCONTROL]);
	m_KeyMap[KeyLeftAlt] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_LALT), &m_KeyState[DIK_LALT]);
	m_KeyMap[KeyRightAlt] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RALT), &m_KeyState[DIK_RALT]);
    m_KeyMap[KeyLeftShift] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_LSHIFT), &m_KeyState[DIK_LSHIFT]);
	m_KeyMap[KeyRightShift] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RSHIFT), &m_KeyState[DIK_RSHIFT]);
	m_KeyMap[KeyUp] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_UP), &m_KeyState[DIK_UP]);
	m_KeyMap[KeyLeft] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_LEFT), &m_KeyState[DIK_LEFT]);
	m_KeyMap[KeyRight] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RIGHT), &m_KeyState[DIK_RIGHT]);
	m_KeyMap[KeyDown] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_DOWN), &m_KeyState[DIK_DOWN]);
	m_KeyMap[KeyHome] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_HOME), &m_KeyState[DIK_HOME]);
	m_KeyMap[KeyEnd] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_END), &m_KeyState[DIK_END]);
	m_KeyMap[KeyPageUp] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_PRIOR), &m_KeyState[DIK_PRIOR]);
	m_KeyMap[KeyPageDown] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_NEXT), &m_KeyState[DIK_NEXT]);
	m_KeyMap[KeyInsert] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_INSERT), &m_KeyState[DIK_INSERT]);
	m_KeyMap[KeyDelete] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_DELETE), &m_KeyState[DIK_DELETE]);
	m_KeyMap[KeyBackSlash] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_BACKSLASH), &m_KeyState[DIK_BACKSLASH]);
	m_KeyMap[KeyMinus] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_MINUS), &m_KeyState[DIK_MINUS]);
	m_KeyMap[KeyEquals] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_EQUALS), &m_KeyState[DIK_EQUALS]);
	m_KeyMap[KeyLeftBracket] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_LBRACKET), &m_KeyState[DIK_LBRACKET]);
	m_KeyMap[KeyRightBracket] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RBRACKET), &m_KeyState[DIK_RBRACKET]);
	m_KeyMap[KeySemicolon] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_SEMICOLON), &m_KeyState[DIK_SEMICOLON]);
	m_KeyMap[KeyApostrophe] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_APOSTROPHE), &m_KeyState[DIK_APOSTROPHE]);
	m_KeyMap[KeyGrave] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_GRAVE), &m_KeyState[DIK_GRAVE]);
	m_KeyMap[KeyComma] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_COMMA), &m_KeyState[DIK_COMMA]);
	m_KeyMap[KeyPeriod] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_PERIOD), &m_KeyState[DIK_PERIOD]);
	m_KeyMap[KeySlash] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_SLASH), &m_KeyState[DIK_SLASH]);
	m_KeyMap[KeyMultiply] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_MULTIPLY), &m_KeyState[DIK_MULTIPLY]);
	m_KeyMap[KeyNumLock] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_NUMLOCK), &m_KeyState[DIK_NUMLOCK]);
	m_KeyMap[KeyScrollLock] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_SCROLL), &m_KeyState[DIK_SCROLL]);
	m_KeyMap[KeySYSRQ] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_SYSRQ), &m_KeyState[DIK_SYSRQ]);
	m_KeyMap[KeySpace] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_SPACE), &m_KeyState[DIK_SPACE]);
	m_KeyMap[KeyCapital] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_CAPITAL), &m_KeyState[DIK_CAPITAL]);
	m_KeyMap[Key1] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_1), &m_KeyState[DIK_1]);
	m_KeyMap[Key2] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_2), &m_KeyState[DIK_2]);
	m_KeyMap[Key3] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_3), &m_KeyState[DIK_3]);
	m_KeyMap[Key4] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_4), &m_KeyState[DIK_4]);
	m_KeyMap[Key5] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_5), &m_KeyState[DIK_5]);
	m_KeyMap[Key6] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_6), &m_KeyState[DIK_6]);
	m_KeyMap[Key7] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_7), &m_KeyState[DIK_7]);
	m_KeyMap[Key8] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_8), &m_KeyState[DIK_8]);
	m_KeyMap[Key9] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_9), &m_KeyState[DIK_9]);
	m_KeyMap[Key0] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_0), &m_KeyState[DIK_0]);
	m_KeyMap[KeyA] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_A), &m_KeyState[DIK_A]);
	m_KeyMap[KeyB] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_B), &m_KeyState[DIK_B]);
	m_KeyMap[KeyC] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_C), &m_KeyState[DIK_C]);
	m_KeyMap[KeyD] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_D), &m_KeyState[DIK_D]);
	m_KeyMap[KeyE] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_E), &m_KeyState[DIK_E]);
	m_KeyMap[KeyF] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F), &m_KeyState[DIK_F]);
	m_KeyMap[KeyG] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_G), &m_KeyState[DIK_G]);
	m_KeyMap[KeyH] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_H), &m_KeyState[DIK_H]);
	m_KeyMap[KeyI] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_I), &m_KeyState[DIK_I]);
	m_KeyMap[KeyJ] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_J), &m_KeyState[DIK_J]);
	m_KeyMap[KeyK] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_K), &m_KeyState[DIK_K]);
	m_KeyMap[KeyL] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_L), &m_KeyState[DIK_L]);
	m_KeyMap[KeyM] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_M), &m_KeyState[DIK_M]);
	m_KeyMap[KeyN] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_N), &m_KeyState[DIK_N]);
	m_KeyMap[KeyO] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_O), &m_KeyState[DIK_O]);
	m_KeyMap[KeyP] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_P), &m_KeyState[DIK_P]);
	m_KeyMap[KeyQ] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_Q), &m_KeyState[DIK_Q]);
	m_KeyMap[KeyR] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_R), &m_KeyState[DIK_R]);
	m_KeyMap[KeyS] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_S), &m_KeyState[DIK_S]);
	m_KeyMap[KeyT] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_T), &m_KeyState[DIK_T]);
	m_KeyMap[KeyU] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_U), &m_KeyState[DIK_U]);
	m_KeyMap[KeyV] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_V), &m_KeyState[DIK_V]);
	m_KeyMap[KeyW] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_W), &m_KeyState[DIK_W]);
	m_KeyMap[KeyX] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_X), &m_KeyState[DIK_X]);
	m_KeyMap[KeyY] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_Y), &m_KeyState[DIK_Y]);
	m_KeyMap[KeyZ] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_Z), &m_KeyState[DIK_Z]);
	m_KeyMap[KeyF1] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F1), &m_KeyState[DIK_F1]);
	m_KeyMap[KeyF2] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F2), &m_KeyState[DIK_F2]);
	m_KeyMap[KeyF3] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F3), &m_KeyState[DIK_F3]);
	m_KeyMap[KeyF4] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F4), &m_KeyState[DIK_F4]);
	m_KeyMap[KeyF5] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F5), &m_KeyState[DIK_F5]);
	m_KeyMap[KeyF6] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F6), &m_KeyState[DIK_F6]);
	m_KeyMap[KeyF7] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F7), &m_KeyState[DIK_F7]);
	m_KeyMap[KeyF8] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F8), &m_KeyState[DIK_F8]);
	m_KeyMap[KeyF9] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F9), &m_KeyState[DIK_F9]);
	m_KeyMap[KeyF10] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F10), &m_KeyState[DIK_F10]);
	m_KeyMap[KeyF11] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F11), &m_KeyState[DIK_F11]);
	m_KeyMap[KeyF12] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F12), &m_KeyState[DIK_F12]);

	for ( std::map<VKeyCode, VDIKeyboardButton*>::iterator iter = m_KeyMap.begin();
		  iter != m_KeyMap.end();
		  ++iter )
	{
        m_ButtonList.push_back(&(*iter->second));
	}

	return true;
}

VStringRetVal VDIKeyboardDevice::GetKeyboardButtonName( vlong in_Index )
{
	DIDEVICEOBJECTINSTANCE DeviceObject;
	
	ZeroMemory( &DeviceObject, sizeof( DIDEVICEOBJECTINSTANCE) );
	DeviceObject.dwSize = sizeof(DIDEVICEOBJECTINSTANCE);

	if ( DI_OK != m_pDevice->GetObjectInfo(&DeviceObject, in_Index, DIPH_BYOFFSET) )
		V3D_THROW( VInputException, "Cannot get keyboard button names");
	
	return DeviceObject.tszName;
}

/**
 * Returns a reference to the desired key
 *
 * @return Reference to the key
 * @author AcrylSword
 */
IVButton& VDIKeyboardDevice::GetKey(const VKeyCode in_KeyCode)
{
	return *m_KeyMap[in_KeyCode];
}
/**
* Updates the keyboard state
* @todo: haha
* @author AcrylSword
*/
void VDIKeyboardDevice::Update()
{
	HRESULT hr;
	
	hr = m_pDevice->GetDeviceState( sizeof(m_KeyState),
		(LPVOID) &m_KeyState );

	if ( hr != DI_OK )
		if ( hr == DIERR_NOTACQUIRED )
		{
			m_pDevice->Acquire();
			hr = m_pDevice->GetDeviceState( sizeof(m_KeyState),
				(LPVOID) &m_KeyState );

			if ( hr != DI_OK )
				V3D_THROW(VUpdateException, "Input update error");
		}
}

/**
 * Returns the name of this keyboard device
 *
 * @return The name of this device
 * @author AcrylSword
 */
VStringRetVal VDIKeyboardDevice::GetName()
{
	return m_DeviceInstance.tszInstanceName;
}

/**
 * Returns the type of this device. Since this is a implementation of the
 * IVKeyboardDevice interface, this function always returns 
 * IVInputDevice::Keyboard.
 *
 * @return IVInputDevice::Keyboard
 * @see IVInputDevice::DeviceType
 * @author AcrylSword
 */
IVInputDevice::DeviceType VDIKeyboardDevice::GetType()
{
	return IVInputDevice::Keyboard;
}

/**
 * Returns a VForwardIterator which points to the end of the button list
 *
 * @author AcrylSword
 */
IVInputDevice::ButtonIterator VDIKeyboardDevice::ButtonBegin()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIKeyboardButton*>::iterator, IVButton> ButtonIterPol;
	//return IVInputDevice::ButtonIterator( new ButtonIterPol(m_ButtonList.begin()) );
	return CreateDerefBeginIterator<IVButton>(m_ButtonList);
}

/**
 * Returns a VForwardIterator which points to the beginning of the button list
 *
 * @author AcrylSword
 */
IVInputDevice::ButtonIterator VDIKeyboardDevice::ButtonEnd()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIKeyboardButton*>::iterator, IVButton> ButtonIterPol;
	//return IVInputDevice::ButtonIterator( new ButtonIterPol(m_ButtonList.end()) );
	return CreateDerefEndIterator<IVButton>(m_ButtonList);
}

/**
* Returns a VForwardIterator pointing to the beginning of the absolute
* axis list.
*
* @return An iterator pointing to the beginning of the absolute axis list
* @author AcrylSword
*/
IVInputDevice::AbsoluteAxisIterator VDIKeyboardDevice::AbsoluteAxisBegin()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIAbsoluteAxis*>::iterator,	IVAbsoluteAxis> AbsoluteAxisIterPol;
	//return IVInputDevice::AbsoluteAxisIterator( new AbsoluteAxisIterPol(m_AbsoluteAxisList.begin()));
	return CreateDerefBeginIterator<IVAbsoluteAxis>(m_AbsoluteAxisList);
}

/**
* Returns a VForwardIterator pointing to the end of the absolute
* axis list.
*
* @return An iterator pointing to the end of the absolute axis list
* @author AcrylSword
*/
IVInputDevice::AbsoluteAxisIterator	VDIKeyboardDevice::AbsoluteAxisEnd()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIAbsoluteAxis*>::iterator,	IVAbsoluteAxis> AbsoluteAxisIterPol;
	//return IVInputDevice::AbsoluteAxisIterator( new AbsoluteAxisIterPol(m_AbsoluteAxisList.end()));
	return CreateDerefEndIterator<IVAbsoluteAxis>(m_AbsoluteAxisList);
}

/**
* Returns a VForwardIterator pointing to the beginning of the relative
* axis list.
*
* @return An iterator pointing to the beginning of the relative axis list
* @author AcrylSword
*/
IVInputDevice::RelativeAxisIterator	VDIKeyboardDevice::RelativeAxisBegin()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIRelativeAxis*>::iterator,	IVRelativeAxis> RelativeAxisIterPol;
	//return IVInputDevice::RelativeAxisIterator( new RelativeAxisIterPol(m_RelativeAxisList.begin()));
	return CreateDerefBeginIterator<IVRelativeAxis>(m_RelativeAxisList);
}

/**
 * Returns a VForwardIterator pointing to the end of the relative
 * axis list.
 *
 * @return An iterator pointing to the end of the relative axis list
 * @author AcrylSword
 */
IVInputDevice::RelativeAxisIterator	VDIKeyboardDevice::RelativeAxisEnd()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIRelativeAxis*>::iterator, IVRelativeAxis> RelativeAxisIterPol;
	//return IVInputDevice::RelativeAxisIterator( new RelativeAxisIterPol(m_RelativeAxisList.end()));
	return CreateDerefEndIterator<IVRelativeAxis>(m_RelativeAxisList);
}

//-----------------------------------------------------------------------------
} // namespace input	
} // namespace v3d
//-----------------------------------------------------------------------------