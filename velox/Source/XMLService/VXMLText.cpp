#include "VXMLText.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

VXMLText::VXMLText()
{
}

VXMLText::VXMLText(VStringParam in_strText)
{
	m_strText = in_strText;
}

IVXMLNode::NodeType VXMLText::GetType()
{
	return Text;
}

VStringRetVal VXMLText::GetText()
{
	return m_strText;
}

void VXMLText::Visit(IVXMLVisitor& in_Visitor)
{
	in_Visitor.OnText(m_strText);
}

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------