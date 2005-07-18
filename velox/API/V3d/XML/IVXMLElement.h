#ifndef V3D_IVXMLELEMENT_09_11_2004_H
#define V3D_IVXMLELEMENT_09_11_2004_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypes.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>
#include <V3d/XML/IVXMLAttribute.h>
#include <V3d/XML/IVXMLNode.h>
#include <V3d/XML/VXMLExceptions.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------
	
/**
 * The XML Element interface
 *
 * Example of an xml element: <element />
 *
 * @author ins/acrylsword/sheijk
 * @version 2.0
 */
class IVXMLElement : public IVXMLNode
{
public:
	typedef VRangeIterator<IVXMLAttribute> AttributeIter;
	typedef VRangeIterator<IVXMLNode> NodeIter;

	/** Returns the name od the xml element */
	virtual VStringRetVal GetName() = 0;

	/** Sets the element's name */
	virtual void SetName(VStringParam in_strName) = 0;

	/** Returns the attribute with the given name. if not exisitng returning NULL */
	virtual IVXMLAttribute* GetAttribute(VStringParam Name) const = 0;

	/**
	 * Returns the value of the given attribute. If it does not exists or
	 * if it can not be converted to type T, an exception of type VException
	 * or VStringValueException will be thrown
	 */
	template<typename T>
	T GetAttributeValue(VStringParam in_strName);

	/** Adds an attribute */
	virtual void AddAttribute(
		VStringParam in_strName, const v3d::utils::VStringValue& in_Name) = 0;

	/** Remove an attribute by it's name */
	virtual void RemoveAttribute(VStringParam in_strName) = 0;

	/** Returns an iterator at first position through all attributes on this element */
	virtual AttributeIter AttributeBegin() = 0;

	/** Returns an iterator to the last position in all attributes on this element */
	virtual AttributeIter AttributeEnd() = 0;

	/** Adds a child node */
	virtual IVXMLElement* AddElement(VStringParam in_strName) = 0;

	/** Removes a child node */
	virtual void RemoveChild(NodeIter in_Node) = 0;

	/** Returns an iterator to the first node element of the child tree */
	virtual NodeIter ChildBegin() = 0;

	/** Returns an iterator to the last node element of the child tree */ 
	virtual NodeIter ChildEnd() = 0;

	/** Call Visit from all child nodes */
	virtual void VisitChildren(IVXMLVisitor& in_Visitor) = 0;

	virtual	IVXMLElement* ToElement() { return this; }
	virtual IVXMLComment* ToComment() { return 0; }
	virtual IVXMLText* ToText() { return 0; }
};
//-----------------------------------------------------------------------------

template<typename T>
T IVXMLElement::GetAttributeValue(VStringParam in_strName)
{
	IVXMLAttribute* pAttrib = GetAttribute(in_strName);

	V3D_ASSERT(pAttrib != 0);

	return pAttrib->GetValue().Get<T>();
}

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLELEMENT_09_11_2004_H