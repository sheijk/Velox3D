#include "VDIRelativeAxis.h"
#include <v3d/Core/VAssert.h>
#include <windows.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/**
 * Constructor
 * @param in_pAxis Points to a member of DIMOUSESTATE2 or DIJOYSTATE2
 * @param in_strName Name of this axis
 */
VDIRelativeAxis::VDIRelativeAxis( DIDEVICEOBJECTINSTANCE in_diDeviceObject, LPDIRECTINPUTDEVICE8 in_lpdiDevice )
{
	m_diDeviceObject = in_diDeviceObject;
	m_pdiDevice = m_pdiDevice;
}

/**
 * Destructor
 */
VDIRelativeAxis::~VDIRelativeAxis()
{
	m_pdiDevice = 0;
}

/**
 * Returns axis name
 * @return The name.
 */
VStringRetVal VDIRelativeAxis::GetName()
{
	return m_diDeviceObject.tszName;
}

/**
 * Returns relative change since last update
 */
vfloat32 VDIRelativeAxis::GetLastMovement()
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
