/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VDIAbsoluteAxis.h"
#include <V3d/Core/MemManager.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/**
 * Constructor
 * @param in_pAxis Points to a member of DIMOUSESTATE2 or DIJOYSTATE2
 * @param in_strName Name of this axis
 */
VDIAbsoluteAxis::VDIAbsoluteAxis( VStringParam in_strName )
{
    m_strName = in_strName;
	m_fPos = 0.0f;
}

/**
 * Destructor
 */
VDIAbsoluteAxis::~VDIAbsoluteAxis()
{
}

/**
 * Returns axis name
 * @return The name.
 */
VStringRetVal VDIAbsoluteAxis::GetName()
{
    return m_strName;
}

/**
 * Returns postion
 */
vfloat32 VDIAbsoluteAxis::GetPosition()
{
    return m_fPos;
}

void VDIAbsoluteAxis::Set( vfloat32 in_fPos )
{
    m_fPos = in_fPos;
}


//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------

