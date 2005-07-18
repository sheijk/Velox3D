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