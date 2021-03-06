/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VDIRelativeAxis.h"
#include <windows.h>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
VDIRelativeAxis::VDIRelativeAxis()
{
}

/**
 * Constructor
 * @param in_strName Name of this axis
 */
VDIRelativeAxis::VDIRelativeAxis( VStringParam in_strName )
{
	m_strName = in_strName;
	m_fMovement = 666.0f;
}

/**
 * Destructor
 */
VDIRelativeAxis::~VDIRelativeAxis()
{
}


/**
 * Returns axis name
 * @return The name.
 */
VStringRetVal VDIRelativeAxis::GetName()
{
	return m_strName;
}


void VDIRelativeAxis::Set( vfloat32 in_fMovement )
{
	m_fMovement = in_fMovement;
}

/**
 * Returns relative change since last update
 * @return Last axis movement
 */
vfloat32 VDIRelativeAxis::GetLastMovement()
{
	return m_fMovement;
}

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
