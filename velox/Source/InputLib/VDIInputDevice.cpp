#include "VDIInputDevice.h"
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/VAssert.h>
#include <v3d/Core/Wrappers/VSTLIteratorPol.h>

//#include "Memory/mmgr.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {

VDIInputDevice::~VDIInputDevice()
{
	m_ButtonList.clear();
	m_RelativeAxisList.clear();
	m_AbsoluteAxisList.clear();

	if (m_pdiDevice)
	{
		m_pdiDevice->Unacquire();
        m_pdiDevice->Release();
        m_pdiDevice = 0;
	}
}

VDIInputDevice::VDIInputDevice()
{
	m_pdiDevice = 0;
}

VDIInputDevice::VDIInputDevice( DIDEVICEINSTANCE in_diDeviceInstance, LPDIRECTINPUT8 in_pDI, HWND in_hWnd )
{
	m_pdiDevice = 0;
	V3D_ASSERT( in_pDI != NULL );

	//init DI structures
	//ZeroMemory(&m_diDeviceInstance, sizeof(m_diDeviceInstance));
	//m_diDeviceInstance.dwSize = sizeof(m_diDeviceInstance);

	ZeroMemory(&m_diDevCaps, sizeof(m_diDevCaps));
	m_diDevCaps.dwSize = sizeof(m_diDevCaps);

	m_diDeviceInstance = in_diDeviceInstance;
	
	// lets create a device
	if ( !Create( in_pDI, in_hWnd) )
		V3D_THROW(VException, "Could not create DI device");

    EnumerateDeviceObjects();
}

vbool VDIInputDevice::Create(LPDIRECTINPUT8 in_pDI, HWND in_hWnd)
{

	vout << "Init input device: " << m_diDeviceInstance.tszInstanceName << "...";

	HRESULT hr;

	if ( DI_OK != in_pDI->CreateDevice(m_diDeviceInstance.guidInstance, &m_pdiDevice, NULL)  )
	{
		vout << "DI: Cannot create device" << vendl;
		return false;
	}

	switch ( GET_DIDEVICE_TYPE( m_diDeviceInstance.dwDevType ) )
	{
		case DI8DEVTYPE_JOYSTICK:	hr = m_pdiDevice->SetDataFormat(&c_dfDIJoystick2);
									break;
		case DI8DEVTYPE_GAMEPAD:	hr = m_pdiDevice->SetDataFormat(&c_dfDIJoystick2);
									break;
		case DI8DEVTYPE_KEYBOARD:	hr = m_pdiDevice->SetDataFormat(&c_dfDIKeyboard);
									break;
		case DI8DEVTYPE_MOUSE:		hr = m_pdiDevice->SetDataFormat(&c_dfDIMouse2);
									break;
	}

	if ( DI_OK != hr )
	{
		vout << "DI: ::SetDataFormat failed" << vendl;
		return false;
	}

	if ( DI_OK != m_pdiDevice->SetCooperativeLevel( in_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) )
	{
		vout << "DI: ::SetCooperativeLevel failed" << vendl;
		return false;
	}

	// Set device properties
	DIPROPDWORD Properties = {0};
	Properties.diph.dwSize = sizeof(DIPROPDWORD);
	Properties.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	Properties.diph.dwHow = DIPH_DEVICE;
	Properties.dwData = 16;

	// Allocate a buffer for input events
	if ( DI_OK != m_pdiDevice->SetProperty( DIPROP_BUFFERSIZE, &Properties.diph ) )
	{
		vout << "DI: ::SetProperty failed" << vendl;
	}

	if ( DI_OK != m_pdiDevice->Acquire() )
	{
		vout << " DI: Cannot acquire device" << vendl;
		return false;
	}

	m_pdiDevice->GetCapabilities(&m_diDevCaps);

	vout << " sucessful" << vendl;

	return true;
}

void VDIInputDevice::EnumerateDeviceObjects()
{
	HRESULT hr;

	hr = m_pdiDevice->EnumObjects(&StaticDIEnumDeviceObjectsCallback, this, DIDFT_ALL);
}

vbool VDIInputDevice::EnumDeviceObjectCallback(const DIDEVICEOBJECTINSTANCE* in_pdiDOI)
{
	if ( in_pdiDOI->dwType & DIDFT_ABSAXIS )
	{
	    m_AbsoluteAxisList.push_back( VDIAbsoluteAxis(in_pdiDOI->tszName) );
		return true;
	}
	
	if ( in_pdiDOI->dwType & DIDFT_RELAXIS )
	{
		m_RelativeAxisList.push_back( VDIRelativeAxis(in_pdiDOI->tszName) );
		return true;
	}
	
	if ( in_pdiDOI->dwType & DIDFT_BUTTON )
    {
        m_ButtonList.push_back( VDIButton(in_pdiDOI->tszName) );
        //vout << "Added button: " << in_pdiDOI->tszName << vendl;
		return true;
    }
	
    vout << "Found some unkown device objects: " << in_pdiDOI->tszName << vendl;
	
    return true;
}


VStringRetVal VDIInputDevice::GetName()
{
	return m_diDeviceInstance.tszInstanceName;
}

void VDIInputDevice::Update()
{
	
	DIDEVICEOBJECTDATA DeviceData[16];
	DWORD   Items = 16;
	HRESULT hr;

	m_pdiDevice->Acquire();  
	m_pdiDevice->Poll();
	m_pdiDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), DeviceData, &Items, 0 );



	for ( DWORD i=0; i<Items; i++ )
	{
		VString Name;
		DIDEVICEOBJECTINSTANCE ObjectInstance = {0};
		ObjectInstance.dwSize = sizeof(DIDEVICEOBJECTINSTANCE);

		m_pdiDevice->GetObjectInfo( &ObjectInstance, DeviceData[i].dwOfs, DIPH_BYOFFSET );
		Name = ObjectInstance.tszName;

		if (ObjectInstance.dwType & DIDFT_ABSAXIS)
		{
			std::list<VDIAbsoluteAxis>::iterator Iter;
			
			for ( Iter = m_AbsoluteAxisList.begin(); Iter != m_AbsoluteAxisList.end(); Iter++ )
				if ( (*Iter).GetName() == Name )
					(*Iter).Set( static_cast<vfloat32>(DeviceData[i].dwData) );
		}

		if (ObjectInstance.dwType & DIDFT_RELAXIS)
		{

			std::list<VDIRelativeAxis>::iterator Iter;
			
			for ( Iter = m_RelativeAxisList.begin(); Iter != m_RelativeAxisList.end(); Iter++ )
				if ( (*Iter).GetName() == Name )
					//vout << DeviceData[i].dwData << vendl;
					(*Iter).Set( DeviceData[i].dwData );
				//else
				//	(*Iter).Set(0.0f);
		}

		if ( ObjectInstance.dwType & DIDFT_BUTTON )
		{
			std::list<VDIButton>::iterator Iter;

			for ( Iter = m_ButtonList.begin(); Iter != m_ButtonList.end(); Iter++ )
				if ( (*Iter).GetName() == Name )
					(*Iter).Set( static_cast<vbool>(DeviceData[i].dwData & 0x80) );
		}
	}
	
}

BOOL VDIInputDevice::StaticDIEnumDeviceObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	return ((VDIInputDevice*) pvRef)->EnumDeviceObjectCallback(lpddoi);
}

IVInputDevice::ButtonIterator VDIInputDevice::ButtonBegin()
{
	typedef VSTLIteratorPol<std::list<VDIButton>::iterator, IVButton> ButtonIterPol;

	return ButtonIterator( new ButtonIterPol(m_ButtonList.begin()) );
}

IVInputDevice::ButtonIterator VDIInputDevice::ButtonEnd()
{
	typedef VSTLIteratorPol<std::list<VDIButton>::iterator, IVButton> ButtonIterPol;

	return ButtonIterator( new ButtonIterPol(m_ButtonList.end()) );
}

IVInputDevice::AbsoluteAxisIterator VDIInputDevice::AbsoluteAxisBegin()
{
	typedef VSTLIteratorPol<std::list<VDIAbsoluteAxis>::iterator, IVAbsoluteAxis> AbsoluteAxisIterPol;

	return AbsoluteAxisIterator( new AbsoluteAxisIterPol(m_AbsoluteAxisList.begin()));
}

IVInputDevice::AbsoluteAxisIterator VDIInputDevice::AbsoluteAxisEnd()
{
	typedef VSTLIteratorPol<std::list<VDIAbsoluteAxis>::iterator, IVAbsoluteAxis> AbsoluteAxisIterPol;

	return AbsoluteAxisIterator( new AbsoluteAxisIterPol(m_AbsoluteAxisList.end()));
}

IVInputDevice::RelativeAxisIterator VDIInputDevice::RelativeAxisBegin()
{
	typedef VSTLIteratorPol<std::list<VDIRelativeAxis>::iterator, IVRelativeAxis> RelativeAxisIterPol;

	return RelativeAxisIterator( new RelativeAxisIterPol(m_RelativeAxisList.begin() ));
}


IVInputDevice::RelativeAxisIterator VDIInputDevice::RelativeAxisEnd()
{
	typedef VSTLIteratorPol<std::list<VDIRelativeAxis>::iterator, IVRelativeAxis> RelativeAxisIterPol;

	return RelativeAxisIterator( new RelativeAxisIterPol(m_RelativeAxisList.end()));
}


}
}
/*
switch (hr)
{
case DIERR_INPUTLOST:		vout << "InputLost" << vendl; break;
case DIERR_INVALIDPARAM:	vout << "Invalid Param" << vendl; break;
case DIERR_NOTACQUIRED:		vout << "Not acquired" << vendl; break;
case DIERR_NOTBUFFERED:		vout << "Not bufferd" << vendl; break;
case DIERR_NOTINITIALIZED: vout << "Not init" << vendl; break;
}
*/