#include "VDIMouseButton.h"
#include <v3d/Core/VAssert.h>
#include <windows.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/* Constructor. Initializes pointer to DIMouseState2 structure in VDIMouseDevice
 * and names the mousebutton.
 * @param in_pButtonByte Pointer to one button element of the DIMOUSESTATE2 structure.
 * @param in_strName Name of the button.
 */
VDIMouseButton::VDIMouseButton( VStringParam in_strName, vbyte* in_pPointer )
{
	// sowas sollten wir oefter machen, gut -- sheijk
	V3D_ASSERT( in_pPointer != NULL);
	m_pPointer = in_pPointer;
	m_strName = in_strName;
}

/**
 * Destructor. Sets m_pButtonByte to NULL
 */
VDIMouseButton::~VDIMouseButton()
{
	m_pPointer = NULL;
}

/* Returns the button's name
 * @return VStringRetVal containing the button's name
 */
VStringRetVal VDIMouseButton::GetName()
{
	return m_strName;
}

/*
 *	Returns the button's state
 * @return TRUE if button ist down, FALSE  else
 */
vbool VDIMouseButton::IsDown()
{
	return (*m_pPointer & 0x80);
}



//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------