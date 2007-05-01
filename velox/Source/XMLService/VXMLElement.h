/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VXMLELEMNT_H
#define V3D_VXMLELEMNT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/Wrappers/VString.h>
#include <V3d/XML/IVXMLElement.h>
#include <vector>
#include <list>
//-----------------------------------------------------------------------------
#include "VXMLAttribute.h"
//class VXMLAttribute;
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------
/**
 * The IVXMLElement implementation
 * @author insane
 * @version 1.0
 */
class VXMLElement : public IVXMLElement
{
public:
	VXMLElement();
	VXMLElement(VStringParam in_strName);
	~VXMLElement();
	virtual VStringRetVal GetName();
	virtual void SetName(VStringParam in_strName);
	//virtual IVXMLAttribute* GetFirstAttribute();
	//virtual IVXMLAttribute* NextAttribute();
	virtual IVXMLAttribute* GetAttribute(VStringParam Name) const;
	virtual AttributeIter AttributeBegin();
	virtual AttributeIter AttributeEnd();
	virtual VRangeIterator<const IVXMLAttribute> AttributeBegin() const;

	void AddAttribute(VXMLAttribute* p_Attribute);

	virtual void AddAttribute(
		VStringParam in_strName, const v3d::utils::VStringValue& in_Name);
	virtual void RemoveAttribute(VStringParam in_strName);

	void AddChild(IVXMLNode* in_pChild);

	virtual IVXMLElement* AddElement(VStringParam in_strName);
	virtual void RemoveChild(NodeIter in_Node);

	virtual NodeIter ChildBegin();
	virtual NodeIter ChildEnd();

    virtual void Visit(IVXMLVisitor& in_Visitor);
	virtual void VisitChildren(IVXMLVisitor& in_Visitor);


	virtual NodeType GetType();

private:

	VString m_strName;
	std::list<IVXMLAttribute*> m_AttributeList;
	std::list<IVXMLNode*> m_Childs;
	//vuint m_iPos;
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLELEMNT_H
