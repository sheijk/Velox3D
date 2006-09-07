/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VXMLCOMMENT_09_11_2004_H
#define V3D_VXMLCOMMENT_09_11_2004_H
//-----------------------------------------------------------------------------
#include <V3d/XML/IVXMLComment.h>
#include <V3d/Core/Wrappers/VString.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------
/**
 * The IVXMLComment implementation
 * @author AcrylSword
 * @version 1.0
 */
class VXMLComment : public IVXMLComment
{
private:
	VString m_strComment;

	VXMLComment();

public:
	VXMLComment(VStringParam in_strComment);

	virtual VStringRetVal GetComment() const;
	virtual void SetComment(VStringParam in_strComment);

	virtual void Visit(IVXMLVisitor& in_Visitor);
	virtual NodeType GetType();
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLCOMMENT_09_11_2004_H
