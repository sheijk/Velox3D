#include "VDIButton.h"
#include <v3d/Core/VAssert.h>
#include <windows.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/* Constructor. Initializes to a DIDEVICEOBJECTINSTANCE instance
 * @param in_DeviceObject "physical" part of a device.
 */
VDIButton::VDIButton(DIDEVICEOBJECTINSTANCE in_diDeviceObject, LPDIRECTINPUTDEVICE8 in_pdiDevice)
{
	m_diDeviceObject = in_diDeviceObject;
	m_pdiDevice = in_pdiDevice;
}

/**
 * Destructor. Sets m_pDeviceObject to NULL
 */
VDIButton::~VDIButton()
{
	m_pdiDevice = 0;
}

/* Returns the button's name
 * @return VStringRetVal containing the button's name
 */
VStringRetVal VDIButton::GetName()
{
	return m_diDeviceObject.tszName;
}

/*
 * Returns the button's state
 * @return TRUE if button ist down, FALSE  else
 */
vbool VDIButton::IsDown()
{
	DIDEVICEOBJECTINSTANCE ObjectInstance;
	ZeroMemory(&ObjectInstance, sizeof(ObjectInstance));
	ObjectInstance.dwSize = sizeof(ObjectInstance);

	m_pdiDevice->GetObjectInfo( &ObjectInstance, m_diDeviceObject.dwType, DIPH_BYID);

	return (ObjectInstance.dwOfs & 0x80);
}



//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
