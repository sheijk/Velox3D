#include "VDIKeyboardButton.h"

namespace v3d {
namespace input {

VDIKeyboardButton::VDIKeyboardButton( VStringParam in_strName, vchar* in_pPointer)
{
	m_strName = in_strName;
	m_pButton = in_pPointer;
}

VDIKeyboardButton::~VDIKeyboardButton()
{
	//TODO:: ???
	//m_pButton = NULL;
}

VStringRetVal VDIKeyboardButton::GetName()
{
	return m_strName;
}

vbool VDIKeyboardButton::IsDown()
{
	return (*m_pButton & 0x80);
}

}
}