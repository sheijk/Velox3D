/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VXMLComment.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

VXMLComment::VXMLComment()
{
}

VXMLComment::VXMLComment(VStringParam in_strComment)
{
	m_strComment = in_strComment;
}

IVXMLNode::NodeType VXMLComment::GetType()
{
	return Comment;
}

VStringRetVal VXMLComment::GetComment() const
{
	return m_strComment;
};

void VXMLComment::SetComment(VStringParam in_strComment)
{
	m_strComment = in_strComment;
}

void VXMLComment::Visit(IVXMLVisitor& in_Visitor)
{
	in_Visitor.OnComment(m_strComment);
}

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
