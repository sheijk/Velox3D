#include "VDIInputDevice.h"
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/VAssert.h>
#include <v3d/Core/Wrappers/VSTLIteratorPol.h>

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
	ZeroMemory(&m_diDeviceInstance, sizeof(m_diDeviceInstance));
	m_diDeviceInstance.dwSize = sizeof(m_diDeviceInstance);

	ZeroMemory(&m_diDevCaps, sizeof(m_diDevCaps));
	m_diDevCaps.dwSize = sizeof(m_diDevCaps);

	m_diDeviceInstance = in_diDeviceInstance;
	
	// lets create a device
	vout << "Init input device: " << m_diDeviceInstance.tszInstanceName;
	Create( in_pDI, in_hWnd);
//	if ( !Create( in_pDI, in_hWnd) )
//		V3D_THROW(VException, "Could not create DI device");
	
	//TODO: das sollte glaub ich wieder entkommentiert werden... -- sheijk
//    EnumerateDeviceObjects();
}

vbool VDIInputDevice::Create(LPDIRECTINPUT8 in_pDI, HWND in_hWnd)
{
	if ( DI_OK != in_pDI->CreateDevice(m_diDeviceInstance.guidInstance, &m_pdiDevice, NULL)  )
	{
		vout << "DI: Cannot create device" << vendl;
		return false;
	}

	if ( DI_OK != m_pdiDevice->SetDataFormat(&c_dfDIMouse2) )
	{
		vout << "DI: ::SetDataFormat failed" << vendl;
		return false;
	}

	if ( DI_OK != m_pdiDevice->SetCooperativeLevel( in_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND) )
	{
		vout << "DI: ::SetCooperativeLevel failed" << vendl;
		return false;
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
	//TODO: das sollte lesbarer formatiert werden... -- sheijk
	switch (in_pdiDOI->dwType)
	{
	case DIDFT_ABSAXIS:			m_AbsoluteAxisList.push_back( VDIAbsoluteAxis(*in_pdiDOI, m_pdiDevice) );
								break;

	case DIDFT_RELAXIS:			m_RelativeAxisList.push_back( VDIRelativeAxis(*in_pdiDOI, m_pdiDevice) );
								break;

	case DIDFT_BUTTON:			m_ButtonList.push_back( VDIButton(*in_pdiDOI, m_pdiDevice) );
								break;

	default:					vout << "Found some unkown device objects" << vendl;
	}

    return true;
}


VStringRetVal VDIInputDevice::GetName()
{
	return m_diDeviceInstance.tszInstanceName;
}

void VDIInputDevice::Update()
{
	/*
	HRESULT hr;
	hr = m_pdiDevice->GetDeviceState( sizeof(DIMOUSESTATE2), (LPVOID) &m_diMouseState );
	if ( hr != DI_OK )
		if ( hr == DIERR_NOTACQUIRED )
		{
			m_pdiDevice->Acquire();
			m_pdiDevice->GetDeviceState( sizeof(DIMOUSESTATE2), (LPVOID) &m_diMouseState );
			if ( hr != DI_OK )
				V3D_THROW(VException, "Input update error");
		}
	*/
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
;

IVInputDevice::RelativeAxisIterator VDIInputDevice::RelativeAxisEnd()
{
	typedef VSTLIteratorPol<std::list<VDIRelativeAxis>::iterator, IVRelativeAxis> RelativeAxisIterPol;

	return RelativeAxisIterator( new RelativeAxisIterPol(m_RelativeAxisList.end()));
}


}
}
