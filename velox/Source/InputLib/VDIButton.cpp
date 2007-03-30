/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VDIButton.h"
#include <V3d/Core/MemManager.h>
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

void VDIButton::SetDown(vbool in_bState)
{
    m_bState = in_bState;
}
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------

