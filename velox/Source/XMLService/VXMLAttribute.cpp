#include "VXmlAttribute.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

VXMLAttribute::VXMLAttribute(void)
{
}

VXMLAttribute::VXMLAttribute(VStringParam Name, VStringParam Value)
{
	m_Name = Name;
	m_Value = Value;
}

VStringRetVal VXMLAttribute::GetName()
{
	return m_Name.c_str();
}

VStringRetVal VXMLAttribute::GetValue()
{
	return m_Value.c_str();
}

void VXMLAttribute::SetName(VStringParam Name)
{
	m_Name = Name;
}

void VXMLAttribute::SetValue(VStringParam Value)
{
	m_Value = Value;
}

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------


