#include "VDIKeyboardDevice.h"
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/VAssert.h>
#include <v3d/Input/VInputException.h>
#include <v3d/Core/Wrappers/VSTLDerefIteratorPol.h> 
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
	vout << "VDIInputDevice::~VDIINPUTDEVICE" << vendl;

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

	return true;
}


vbool VDIKeyboardDevice::CreateDeviceObjects()
{
	m_KeyMap[Key_Escape] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_ESCAPE), &m_KeyState[DIK_ESCAPE]);
	m_KeyMap[Key_Return] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RETURN), &m_KeyState[DIK_RETURN]);
	m_KeyMap[Key_BackSpace] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_BACK), &m_KeyState[DIK_BACK]);
	m_KeyMap[Key_Tab] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_TAB), &m_KeyState[DIK_TAB]);
	m_KeyMap[Key_LeftControl] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_LCONTROL), &m_KeyState[DIK_LCONTROL]);
	m_KeyMap[Key_RightControl] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RCONTROL), &m_KeyState[DIK_RCONTROL]);
	m_KeyMap[Key_LeftAlt] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_LALT), &m_KeyState[DIK_LALT]);
	m_KeyMap[Key_RightAlt] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RALT), &m_KeyState[DIK_RALT]);
    m_KeyMap[Key_LeftShift] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_LSHIFT), &m_KeyState[DIK_LSHIFT]);
	m_KeyMap[Key_RightShift] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RSHIFT), &m_KeyState[DIK_RSHIFT]);
	m_KeyMap[Key_Up] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_UP), &m_KeyState[DIK_UP]);
	m_KeyMap[Key_Left] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_LEFT), &m_KeyState[DIK_LEFT]);
	m_KeyMap[Key_Right] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RIGHT), &m_KeyState[DIK_RIGHT]);
	m_KeyMap[Key_Down] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_DOWN), &m_KeyState[DIK_DOWN]);
	m_KeyMap[Key_Home] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_HOME), &m_KeyState[DIK_HOME]);
	m_KeyMap[Key_End] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_END), &m_KeyState[DIK_END]);
	m_KeyMap[Key_PageUp] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_PRIOR), &m_KeyState[DIK_PRIOR]);
	m_KeyMap[Key_PageDown] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_NEXT), &m_KeyState[DIK_NEXT]);
	m_KeyMap[Key_Insert] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_INSERT), &m_KeyState[DIK_INSERT]);
	m_KeyMap[Key_Delete] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_DELETE), &m_KeyState[DIK_DELETE]);
	m_KeyMap[Key_BackSlash] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_BACKSLASH), &m_KeyState[DIK_BACKSLASH]);
	m_KeyMap[Key_Minus] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_MINUS), &m_KeyState[DIK_MINUS]);
	m_KeyMap[Key_Equals] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_EQUALS), &m_KeyState[DIK_EQUALS]);
	m_KeyMap[Key_LeftBracket] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_LBRACKET), &m_KeyState[DIK_LBRACKET]);
	m_KeyMap[Key_RightBracket] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_RBRACKET), &m_KeyState[DIK_RBRACKET]);
	m_KeyMap[Key_Semicolon] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_SEMICOLON), &m_KeyState[DIK_SEMICOLON]);
	m_KeyMap[Key_Apostrophe] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_APOSTROPHE), &m_KeyState[DIK_APOSTROPHE]);
	m_KeyMap[Key_Grave] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_GRAVE), &m_KeyState[DIK_GRAVE]);
	m_KeyMap[Key_Comma] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_COMMA), &m_KeyState[DIK_COMMA]);
	m_KeyMap[Key_Period] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_PERIOD), &m_KeyState[DIK_PERIOD]);
	m_KeyMap[Key_Slash] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_SLASH), &m_KeyState[DIK_SLASH]);
	m_KeyMap[Key_Multiply] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_MULTIPLY), &m_KeyState[DIK_MULTIPLY]);
	m_KeyMap[Key_NumLock] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_NUMLOCK), &m_KeyState[DIK_NUMLOCK]);
	m_KeyMap[Key_ScrollLock] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_SCROLL), &m_KeyState[DIK_SCROLL]);
	m_KeyMap[Key_SYSRQ] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_SYSRQ), &m_KeyState[DIK_SYSRQ]);
	m_KeyMap[Key_Space] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_SPACE), &m_KeyState[DIK_SPACE]);
	m_KeyMap[Key_Capital] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_CAPITAL), &m_KeyState[DIK_CAPITAL]);
	m_KeyMap[Key_1] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_1), &m_KeyState[DIK_1]);
	m_KeyMap[Key_2] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_2), &m_KeyState[DIK_2]);
	m_KeyMap[Key_3] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_3), &m_KeyState[DIK_3]);
	m_KeyMap[Key_4] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_4), &m_KeyState[DIK_4]);
	m_KeyMap[Key_5] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_5), &m_KeyState[DIK_5]);
	m_KeyMap[Key_6] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_6), &m_KeyState[DIK_6]);
	m_KeyMap[Key_7] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_7), &m_KeyState[DIK_7]);
	m_KeyMap[Key_8] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_8), &m_KeyState[DIK_8]);
	m_KeyMap[Key_9] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_9), &m_KeyState[DIK_9]);
	m_KeyMap[Key_0] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_0), &m_KeyState[DIK_0]);
	m_KeyMap[Key_A] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_A), &m_KeyState[DIK_A]);
	m_KeyMap[Key_B] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_B), &m_KeyState[DIK_B]);
	m_KeyMap[Key_C] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_C), &m_KeyState[DIK_C]);
	m_KeyMap[Key_D] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_D), &m_KeyState[DIK_D]);
	m_KeyMap[Key_E] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_E), &m_KeyState[DIK_E]);
	m_KeyMap[Key_F] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F), &m_KeyState[DIK_F]);
	m_KeyMap[Key_G] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_G), &m_KeyState[DIK_G]);
	m_KeyMap[Key_H] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_H), &m_KeyState[DIK_H]);
	m_KeyMap[Key_I] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_I), &m_KeyState[DIK_I]);
	m_KeyMap[Key_J] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_J), &m_KeyState[DIK_J]);
	m_KeyMap[Key_K] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_K), &m_KeyState[DIK_K]);
	m_KeyMap[Key_L] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_L), &m_KeyState[DIK_L]);
	m_KeyMap[Key_M] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_M), &m_KeyState[DIK_M]);
	m_KeyMap[Key_N] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_N), &m_KeyState[DIK_N]);
	m_KeyMap[Key_O] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_O), &m_KeyState[DIK_O]);
	m_KeyMap[Key_P] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_P), &m_KeyState[DIK_P]);
	m_KeyMap[Key_Q] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_Q), &m_KeyState[DIK_Q]);
	m_KeyMap[Key_R] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_R), &m_KeyState[DIK_R]);
	m_KeyMap[Key_S] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_S), &m_KeyState[DIK_S]);
	m_KeyMap[Key_T] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_T), &m_KeyState[DIK_T]);
	m_KeyMap[Key_U] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_U), &m_KeyState[DIK_U]);
	m_KeyMap[Key_V] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_V), &m_KeyState[DIK_V]);
	m_KeyMap[Key_W] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_W), &m_KeyState[DIK_W]);
	m_KeyMap[Key_X] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_X), &m_KeyState[DIK_X]);
	m_KeyMap[Key_Y] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_Y), &m_KeyState[DIK_Y]);
	m_KeyMap[Key_Z] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_Z), &m_KeyState[DIK_Z]);
	m_KeyMap[Key_F1] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F1), &m_KeyState[DIK_F1]);
	m_KeyMap[Key_F2] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F2), &m_KeyState[DIK_F2]);
	m_KeyMap[Key_F3] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F3), &m_KeyState[DIK_F3]);
	m_KeyMap[Key_F4] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F4), &m_KeyState[DIK_F4]);
	m_KeyMap[Key_F5] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F5), &m_KeyState[DIK_F5]);
	m_KeyMap[Key_F6] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F6), &m_KeyState[DIK_F6]);
	m_KeyMap[Key_F7] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F7), &m_KeyState[DIK_F7]);
	m_KeyMap[Key_F8] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F8), &m_KeyState[DIK_F8]);
	m_KeyMap[Key_F9] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F9), &m_KeyState[DIK_F9]);
	m_KeyMap[Key_F10] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F10), &m_KeyState[DIK_F10]);
	m_KeyMap[Key_F11] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F11), &m_KeyState[DIK_F11]);
	m_KeyMap[Key_F12] = new VDIKeyboardButton( GetKeyboardButtonName(DIK_F11), &m_KeyState[DIK_F12]);

	for ( std::map<KeyCodes, VDIKeyboardButton*>::iterator iter = m_KeyMap.begin();
		  iter != m_KeyMap.end();
		  ++iter )
	{
        m_ButtonList.push_back(iter->second);
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
IVButton& VDIKeyboardDevice::GetKey(const KeyCodes in_KeyCode)
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
	typedef VSTLDerefIteratorPol<std::list<VDIKeyboardButton*>::iterator, IVButton> ButtonIterPol;
	return IVInputDevice::ButtonIterator( new ButtonIterPol(m_ButtonList.begin()) );
}
/**
 * Returns a VForwardIterator which points to the beginning of the button list
 *
 * @author AcrylSword
 */
IVInputDevice::ButtonIterator VDIKeyboardDevice::ButtonEnd()
{
	typedef VSTLDerefIteratorPol<std::list<VDIKeyboardButton*>::iterator, IVButton> ButtonIterPol;
	return IVInputDevice::ButtonIterator( new ButtonIterPol(m_ButtonList.end()) );
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
	typedef VSTLDerefIteratorPol<std::list<VDIAbsoluteAxis*>::iterator,	IVAbsoluteAxis> AbsoluteAxisIterPol;
	return IVInputDevice::AbsoluteAxisIterator( new AbsoluteAxisIterPol(m_AbsoluteAxisList.begin()));
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
	typedef VSTLDerefIteratorPol<std::list<VDIAbsoluteAxis*>::iterator,	IVAbsoluteAxis> AbsoluteAxisIterPol;
	return IVInputDevice::AbsoluteAxisIterator( new AbsoluteAxisIterPol(m_AbsoluteAxisList.end()));
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
	typedef VSTLDerefIteratorPol<std::list<VDIRelativeAxis*>::iterator,	IVRelativeAxis> RelativeAxisIterPol;
	return IVInputDevice::RelativeAxisIterator( new RelativeAxisIterPol(m_RelativeAxisList.begin()));
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
	typedef VSTLDerefIteratorPol<std::list<VDIRelativeAxis*>::iterator, IVRelativeAxis> RelativeAxisIterPol;
	return IVInputDevice::RelativeAxisIterator( new RelativeAxisIterPol(m_RelativeAxisList.end()));
}

//-----------------------------------------------------------------------------
} // namespace input	
} // namespace v3d
//-----------------------------------------------------------------------------