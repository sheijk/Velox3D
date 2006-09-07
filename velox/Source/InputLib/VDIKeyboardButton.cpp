/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VDIKeyboardButton.h"
#include <v3d/Core/VAssert.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
VDIKeyboardButton::VDIKeyboardButton( VStringParam in_strName, vchar* in_pPointer)
{
	V3D_ASSERT( in_pPointer != 0);
	m_strName = in_strName;
	m_pButton = in_pPointer;
}

VDIKeyboardButton::~VDIKeyboardButton()
{
	m_pButton = 0;
}

VStringRetVal VDIKeyboardButton::GetName()
{
	return m_strName;
}

vbool VDIKeyboardButton::IsDown()
{
	return (*m_pButton & 0x80) != 0;
}

void VDIKeyboardButton::SetDown(vbool down)
{
	*m_pButton = down ? 0x80 : 0x00;
}

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------

