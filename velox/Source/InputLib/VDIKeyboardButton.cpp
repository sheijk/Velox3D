#include "VDIKeyboardButton.h"
#include <v3d/Core/VAssert.h>
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
	return (*m_pButton & 0x80);
}
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
