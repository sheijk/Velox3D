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
	virtual IVXMLAttribute* GetFirstAttribute();
	virtual IVXMLAttribute* NextAttribute();
	virtual IVXMLAttribute* GetAttribute(VStringParam Name);
	virtual AttributeIter AttributeBegin();
	virtual AttributeIter AttributeEnd();

	void AddAttribute(VXMLAttribute* p_Attribute);
	void SetName(VStringParam Name);

	void AddChild(IVXMLNode* in_pChild);
	virtual NodeIter ChildBegin();
	virtual NodeIter ChildEnd();

    virtual void Visit(IVXMLVisitor& in_Visitor);
	virtual void VisitChildren(IVXMLVisitor& in_Visitor);


	virtual NodeType GetType();

private:

	VString m_strName;
	std::vector <VXMLAttribute*> m_AttributeList;
	std::list<IVXMLNode*> m_Childs;
	vuint m_iPos;
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLELEMNT_H