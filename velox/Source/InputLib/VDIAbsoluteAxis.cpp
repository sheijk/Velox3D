#include "VDIAbsoluteAxis.h"
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
		VDIAbsoluteAxis::VDIAbsoluteAxis(DIDEVICEOBJECTINSTANCE in_diDeviceObject, LPDIRECTINPUTDEVICE8	in_pdiDevice )
		{
			m_diDeviceObject = in_diDeviceObject;
			m_pdiDevice = in_pdiDevice;
		}

		/**
		* Destructor
		*/
		VDIAbsoluteAxis::~VDIAbsoluteAxis()
		{
			m_pdiDevice = 0;
		}

		/**
		* Returns axis name
		* @return The name.
		*/
		VStringRetVal VDIAbsoluteAxis::GetName()
		{
			return m_diDeviceObject.tszName;
		}

		/**
		* Returns postion
		*/
		vfloat32 VDIAbsoluteAxis::GetPosition()
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
