#include "VDIButton.h"
#include <v3d/Core/VAssert.h>
#include <v3d/Core/VIOStream.h>
#include <windows.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/* Constructor. Initializes the name and buttons state
 * @param in_strName Button's name.
 */
VDIButton::VDIButton(VStringParam in_strName)
{
	m_strName = in_strName;
	m_bState = false;
}

/**
 * Destructor. 
 */
VDIButton::~VDIButton()
{
}

/* Returns the button's name
 * @return VStringRetVal containing the button's name
 */
VStringRetVal VDIButton::GetName()
{
	return m_strName;
}

/*
 * Returns the button's state
 * @return TRUE if button ist down, FALSE  else
 */
vbool VDIButton::IsDown()
{
	return m_bState;
}

void VDIButton::Set( vbool in_bState )
{
    m_bState = in_bState;
}


//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
