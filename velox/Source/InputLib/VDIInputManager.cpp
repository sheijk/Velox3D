#include "VDIInputManager.h"
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/Wrappers/VSTLIteratorPol.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
VDIInputManager::VDIInputManager()
{

}

VDIInputManager::VDIInputManager( HWND in_hWnd )
{
	m_hWnd = in_hWnd;
	
	m_pDI = NULL;
	m_pDIStandardKeyboard = NULL;
	m_pDIStandardMouse = NULL;
}

VDIInputManager::~VDIInputManager()
{
	Release();
}


vbool VDIInputManager::Create()
{
	//FIXME: bitte exceptions statt rueckgabewerte fuer fehler signalisierung
	// verwenden, wie im rest von velox. rueckgabewerte werden zu leicht
	// vergessen zu ueberpruefen - sheijk

    // Create DirectInput interface
	vout << "Init DirectInput..." << vendl;
	if ( DI_OK != DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL) )
	{
		vout << "DI: could not create DI8 interface" << vendl;
		return false;
	}

	vout << "Create standard keyboard and mouse acess" << vendl;
	// Create standard keyboard and mouse device
	if ( !InitStandardKeyboardDevice() )
		return false;

	if ( !InitStandardMouseDevice() )
		return false;

	IVUpdateable::Register();
/*
	// enumerate devices
	if ( !EnumerateDevices() )
		return false;
*/
	return true;
}

vbool VDIInputManager::InitStandardKeyboardDevice()
{
	// create standard keyboard device
	vout << "DI: Init standard keyboard..." ;

	if ( DI_OK != m_pDI->CreateDevice(GUID_SysKeyboard, &m_pDIStandardKeyboard, NULL) )
	{
		vout << "failed" << vendl;
		return false;
	}

	if ( DI_OK != m_pDIStandardKeyboard->SetDataFormat(&c_dfDIKeyboard) )
	{
		vout << "failed" << vendl;
		return false;
	}

	if ( DI_OK != m_pDIStandardKeyboard->SetCooperativeLevel(m_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)  )
	{
		vout << "failed" << vendl;
		return false;
	}

	if ( DI_OK != m_pDIStandardKeyboard->Acquire() )
	{ 
		vout << "failed" << vendl;
		return false;
	} 

	vout << "sucessful" << vendl;

	//REMINDER: evtl key namen von DInput holen, fuer lokalisierte texte
	// und konsistenz mit den enumerierten devices -- sheijk

	// name keys
	m_StandardKeys[0] = VDIKeyboardButton( "Escape", &m_KeyboardBuffer[DIK_ESCAPE] );
    m_StandardKeys[1] = VDIKeyboardButton( "Enter", &m_KeyboardBuffer[DIK_RETURN] );
	m_StandardKeys[2] = VDIKeyboardButton( "Space", &m_KeyboardBuffer[DIK_SPACE] );
	m_StandardKeys[3] = VDIKeyboardButton( "Cursor Left", &m_KeyboardBuffer[DIK_LEFT] );
	m_StandardKeys[4] = VDIKeyboardButton( "Cursor Right", &m_KeyboardBuffer[DIK_RIGHT] );
	m_StandardKeys[5] = VDIKeyboardButton( "Cursor Up", &m_KeyboardBuffer[DIK_UP] );
	m_StandardKeys[6] = VDIKeyboardButton( "Cursor Down", &m_KeyboardBuffer[DIK_DOWN] );

	return true;
}

vbool VDIInputManager::InitStandardMouseDevice()
{
	// create standard mouse device
	vout << "DI: Init standard mouse...";

//	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
//	m_MouseState.dwSize = sizeof(m_MouseState);

	if ( DI_OK != m_pDI->CreateDevice(GUID_SysMouse, &m_pDIStandardMouse, NULL) )
	{
		vout << "failed" << vendl;
		return false;
	}

	if ( DI_OK != m_pDIStandardMouse->SetDataFormat(&c_dfDIMouse) )
	{
		vout << "failed" << vendl;
		return false;
	}

	if ( DI_OK != m_pDIStandardMouse->SetCooperativeLevel( m_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) )
	{
		vout << "failed" << vendl;
		return false;
	}

	if ( DI_OK != m_pDIStandardMouse->Acquire() )
	{ 
		vout << "failed" << vendl;
		return false;
	} 

	vout << "sucessful" << vendl;

	//REMINDER: das sollte spaeter mal die wirkliche button anzahl
	// beruecksichtigen -- sheijk
	m_MouseButtons[0] = VDIMouseButton( "Mousebutton 0", &m_MouseState.rgbButtons[0] );
	m_MouseButtons[1] = VDIMouseButton( "Mousebutton 1", &m_MouseState.rgbButtons[1] );
	m_MouseButtons[2] = VDIMouseButton( "Mousebutton 2", &m_MouseState.rgbButtons[2] );
	m_MouseButtons[3] = VDIMouseButton( "Mousebutton 3", &m_MouseState.rgbButtons[3] );

	m_MouseXAxis = VDIMouseAxis("Mouse X-Axis", &m_MouseState.lX);
	m_MouseYAxis = VDIMouseAxis("Mouse Y-Axis", &m_MouseState.lY);

	return true; 
}



vbool VDIInputManager::EnumDevicesCallback(const DIDEVICEINSTANCE* in_pdiDeviceInstance)
{
	//vout << "Enumeration Device" << in_pdiDeviceInstance->tszInstanceName << vendl;

	VDIInputDevice Temp( *in_pdiDeviceInstance, m_pDI, m_hWnd );
/*
	try
	{
		switch (in_pdiDeviceInstance->dwDevType)
        {
            case DIDFT_GETTYPE(DI8DEVTYPE_KEYBOARD):	vout << "Keyboard" << vendl;
            case DI8DEVTYPE_MOUSE: 		
            case DI8DEVTYPE_GAMEPAD:	
            case DI8DEVTYPE_JOYSTICK:	Temp = VDIInputDevice(*in_pdiDeviceInstance, m_pDI, m_hWnd); 
										break;

			default:					break;
        }
	}
	catch(VException e)
	{
		vout << e.GetErrorString() << vendl;
        return false;
	}
*/	
	m_DeviceList.push_back( Temp );

	return true;
}

vbool VDIInputManager::EnumerateDevices()
{
	// enumerate all devices with 
	if ( DI_OK != m_pDI->EnumDevices( DI8DEVCLASS_ALL,
		EnumDevicesStaticCallback,
		(LPVOID) this,
		DIEDFL_ATTACHEDONLY ) )
	{
		vout << "DI: devices enumeration failed" << vendl;
		return false;
	}

	return true;
}
										   
IVButton& VDIInputManager::GetStandardKey( KeyCode in_myKey )
{
	//TODO: dumme frage: warum nicht einfach
	// if( in_myKey >= Escape && in_myKey <= CursorDown )
	//		return m_StandardKeys[in_myKey];
	// else
	//		V3D_THROW(VIllegalKeyIdentifyer, "illegal key id");
	// oder sowas? -- sheijk

	switch ( in_myKey )
	{
        case Escape:		return m_StandardKeys[Escape];
		case Enter:			return m_StandardKeys[Enter];
		case Space:			return m_StandardKeys[Space];
		case CursorLeft:	return m_StandardKeys[CursorLeft];
		case CursorRight:	return m_StandardKeys[CursorRight];
		case CursorUp:		return m_StandardKeys[CursorUp];
		case CursorDown:	return m_StandardKeys[CursorDown];
		default:			return m_StandardKeys[Escape];
	}
}

IVButton& VDIInputManager::GetMouseButton(vuint in_iButton)
{
	//REMINDER: auch hier sollte lieber die echte button anzahl
	// beruecksichtigt werden -- sheijk
	if ( in_iButton > 3 )
		V3D_THROW( VException, "VDIInputManager::GetMouseButton(): in_iButton out of range" );

	return m_MouseButtons[in_iButton];
}

IVRelativeAxis& VDIInputManager::GetMouseXAxis()
{
	return m_MouseXAxis;
}

IVRelativeAxis&	VDIInputManager::GetMouseYAxis()
{
	return m_MouseYAxis;
}


void VDIInputManager::Release()
{
	if (m_pDI)
	{
		if (m_pDIStandardMouse)
		{
			m_pDIStandardMouse->Release();
			m_pDIStandardMouse = 0;
		}

		if (m_pDIStandardKeyboard)
		{
			m_pDIStandardKeyboard->Release();
			m_pDIStandardKeyboard = 0;
		}

		//TODO: muessend die devices hier nicht freigegeben werden? -- sheijk
		m_DeviceList.clear();

		m_pDI->Release();
		m_pDI = NULL;
	}
}

// from IVUpdateable
void VDIInputManager::Update(vfloat32 in_fSeconds)
{
	//TODO: line break nach 80 zeilen beachten (->coding style guide) -- sheijk

	HRESULT hr;
	// update standard devices
	hr = m_pDIStandardKeyboard->GetDeviceState( sizeof(m_KeyboardBuffer),(LPVOID)&m_KeyboardBuffer);
	if ( hr != DI_OK )
	{
		vout << "Error" << hr;
		if ( hr == DIERR_NOTACQUIRED )
		{
			m_pDIStandardKeyboard->Acquire();
			m_pDIStandardKeyboard->GetDeviceState( sizeof(m_KeyboardBuffer),(LPVOID)&m_KeyboardBuffer);
			if ( hr != DI_OK )
				V3D_THROW(VException, "Input update error");
		}
	}

    hr = m_pDIStandardMouse->GetDeviceState( sizeof(DIMOUSESTATE), (LPVOID) &m_MouseState );
		if ( hr != DI_OK )
			if ( hr == DIERR_NOTACQUIRED )
			{
				m_pDIStandardMouse->Acquire();
				m_pDIStandardMouse->GetDeviceState( sizeof(DIMOUSESTATE), (LPVOID) &m_MouseState );
				if ( hr != DI_OK )
					V3D_THROW(VException, "Input update error");
			}

//	vout << m_MouseState.lX;
}

IVInputManager::DeviceIterator VDIInputManager::DeviceBegin()
{
	typedef VSTLIteratorPol<std::list<VDIInputDevice>::iterator, IVInputDevice> DeviceIterPol;

	return IVInputManager::DeviceIterator( new DeviceIterPol(m_DeviceList.begin()));
}

IVInputManager::DeviceIterator VDIInputManager::DeviceEnd()
{
	typedef VSTLIteratorPol<std::list<VDIInputDevice>::iterator, IVInputDevice> DeviceIterPol;

	return DeviceIterator( new DeviceIterPol(m_DeviceList.end()));
}

BOOL CALLBACK VDIInputManager::EnumDevicesStaticCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef )
{
	// ieh, ist directx mal wieder eklig ;) -- sheijk
	return ((VDIInputManager*) pvRef)->EnumDevicesCallback(lpddi);
}

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------