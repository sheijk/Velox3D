/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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

VStringRetVal VXMLText::GetText() const
{
	return m_strText;
}

void VXMLText::SetText(VStringParam in_strText)
{
	m_strText = in_strText;
}

void VXMLText::Visit(IVXMLVisitor& in_Visitor)
{
	in_Visitor.OnText(m_strText);
}

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
