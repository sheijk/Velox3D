#include "VDIInputManager.h"
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/Wrappers/VSTLIteratorPol.h>
#include <v3d/Input/VInputException.h>

//#include "Memory/mmgr.h"

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
	
	m_pDI = 0;
	m_pDIStandardKeyboard = 0;
	m_pDIStandardMouse = 0;

	Create();
}

VDIInputManager::~VDIInputManager()
{
	Release();
}


void VDIInputManager::Create()
{
    // Create DirectInput interface
	vout << "Init DirectInput..." << vendl;
	if ( DI_OK != DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL) )
	{
		vout << "DI: could not create DI8 interface" << vendl;
		V3D_THROW( VCreationException, "Could not create DirectInput8" );
	}

	vout << "Create standard keyboard and mouse acess" << vendl;
	// Create standard keyboard and mouse device
	if ( !InitStandardKeyboardDevice() )
		V3D_THROW( VCreationException, "Could not create standard keyboard device");

	if ( !InitStandardMouseDevice() )
		V3D_THROW( VCreationException, "Could not create standard mouse device" );

	IVUpdateable::Register();

	// enumerate devices
	if ( !EnumerateDevices() )
		V3D_THROW( VCreationException, "Could not enumerate devices");
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

VStringRetVal VDIInputManager::GetKeyboardButtonName( vlong in_Index )
{
	DIDEVICEOBJECTINSTANCE DeviceObject;
	
	ZeroMemory( &DeviceObject, sizeof( DIDEVICEOBJECTINSTANCE) );
	DeviceObject.dwSize = sizeof(DIDEVICEOBJECTINSTANCE);

	if ( DI_OK != m_pDIStandardKeyboard->GetObjectInfo(&DeviceObject, in_Index, DIPH_BYOFFSET) )
		V3D_THROW( VInputException, "Cannot get keyboard button names");
	
	return DeviceObject.tszName;
}

vbool VDIInputManager::InitStandardMouseDevice()
{
	// create standard mouse device
	vout << "DI: Init standard mouse...";

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
	VDIInputDevice *Temp = 0;

	try
	{
        switch ( GET_DIDEVICE_TYPE( in_pdiDeviceInstance->dwDevType ) )
		{
            case DI8DEVTYPE_JOYSTICK:	
            case DI8DEVTYPE_GAMEPAD:	
            case DI8DEVTYPE_KEYBOARD:	
            case DI8DEVTYPE_MOUSE:	Temp = new VDIInputDevice( *in_pdiDeviceInstance, m_pDI, m_hWnd );
									break;
		}
	}
	catch(VException e)
	{
		delete Temp;
		return true;
	}

	if (Temp)
        m_DeviceList.push_back( *Temp );

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
	switch ( in_myKey )
	{
        case Escape:		return m_StandardKeys[Escape];
		case Enter:			return m_StandardKeys[Enter];
		case Space:			return m_StandardKeys[Space];
		case CursorLeft:	return m_StandardKeys[CursorLeft];
		case CursorRight:	return m_StandardKeys[CursorRight];
		case CursorUp:		return m_StandardKeys[CursorUp];
		case CursorDown:	return m_StandardKeys[CursorDown];
		default:			V3D_THROW( VIllegalKeyIdentifierException, "Illegal key identifier");
	}
}

IVButton& VDIInputManager::GetMouseButton(vuint in_iButton)
{
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

		m_DeviceList.clear();

		m_pDI->Release();
		m_pDI = NULL;
	}
}

// from IVUpdateable
void VDIInputManager::Update(vfloat32 in_fSeconds)
{

	HRESULT hr;
	// update standard devices
	hr = m_pDIStandardKeyboard->GetDeviceState( sizeof(m_KeyboardBuffer),
												(LPVOID)&m_KeyboardBuffer);
	if ( hr != DI_OK )
	{
		vout << "Error" << hr;
		if ( hr == DIERR_NOTACQUIRED )
		{
			m_pDIStandardKeyboard->Acquire();
			m_pDIStandardKeyboard->GetDeviceState( sizeof(m_KeyboardBuffer),
												   (LPVOID)&m_KeyboardBuffer);
			if ( hr != DI_OK )
				V3D_THROW(VUpdateException, "Input update error");
		}
	}

    hr = m_pDIStandardMouse->GetDeviceState( sizeof(DIMOUSESTATE),
											 (LPVOID) &m_MouseState );
		if ( hr != DI_OK )
			if ( hr == DIERR_NOTACQUIRED )
			{
				m_pDIStandardMouse->Acquire();
				m_pDIStandardMouse->GetDeviceState( sizeof(DIMOUSESTATE),
													(LPVOID) &m_MouseState );
				if ( hr != DI_OK )
					V3D_THROW(VUpdateException, "Input update error");
			}

	std::list<VDIInputDevice>::iterator Iter;

	for ( Iter = m_DeviceList.begin(); Iter != m_DeviceList.end(); Iter++ )
	{
		(*Iter).Update();
	}
}

void VDIInputManager::Activate()
{
}

void VDIInputManager::Deactivate()
{
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
	return ((VDIInputManager*) pvRef)->EnumDevicesCallback(lpddi);
}

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
