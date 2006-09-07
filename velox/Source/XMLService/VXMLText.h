/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VXMLTEXT_09_11_2004_H
#define V3D_VXMLTEXT_09_11_2004_H
//-----------------------------------------------------------------------------
#include <V3d/XML/IVXMLText.h>
#include <V3d/Core/Wrappers/VString.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The IVXMLText implementation
 * @author AcrylSword
 * @version 1.0
 */
class VXMLText : public IVXMLText
{
private:
	VString m_strText;

	VXMLText();

public:
	VXMLText(VStringParam in_strText);

	virtual void Visit(IVXMLVisitor& in_Visitor);

	virtual VStringRetVal GetText() const;
	virtual void SetText(VStringParam in_strText);
	virtual NodeType GetType();
};

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLTEXT_09_11_2004_H
