#include "VDIMouseAxis.h"
#include <v3d/Core/VAssert.h>
#include <windows.h>
//-----------------------------------------------------------------------------
namespace v3d {
	namespace input {
		//-----------------------------------------------------------------------------

		/**
		* Constructor
		* @param in_pAxis Points to a member of DIMOUSESTATE
		* @param in_strName Name of this axis
		*/
		VDIMouseAxis::VDIMouseAxis( VStringParam in_strName, vlong* in_pPointer )
		{
			m_pPointer = in_pPointer;
			m_strName = in_strName;
		}

		/**
		* Destructor
		*/
		VDIMouseAxis::~VDIMouseAxis()
		{
			m_pPointer = 0;
		}

		/**
		* Returns axis name
		* @return The name.
		*/
		VStringRetVal VDIMouseAxis::GetName()
		{
			return m_strName;
		}

		/**
		* Returns relative change since last update
		*/
		vfloat32 VDIMouseAxis::GetLastMovement()
		{
			return *m_pPointer;
		}

		//-----------------------------------------------------------------------------
	} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
