#ifndef V3D_IVXMLELEMENT_09_11_2004_H
#define V3D_IVXMLELEMENT_09_11_2004_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypes.h>
#include <V3d/Core/Wrappers/VIterator.h>
#include <V3d/XML/IVXMLAttribute.h>
#include <V3d/XML/IVXMLNode.h>
#include <V3d/XML/VXMLExceptions.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The XML Element interface
 * @author ins
 * @version 2.0
 */
class IVXMLElement : public IVXMLNode
{
public:
	typedef VBidirectionalIterator<IVXMLAttribute> AttributeIter;
	typedef VBidirectionalIterator<IVXMLNode> NodeIter;

	/* Returns the name od the xml element */
	virtual VStringRetVal GetName() = 0;

	/* Returns the first attribute in the element */
	virtual IVXMLAttribute* GetFirstAttribute() = 0;

	/* Returns the next attribute in the elemenet */
	virtual IVXMLAttribute* NextAttribute() = 0;

	/* Returns the attribute with the given name. if not exisitng returning NULL */
	virtual IVXMLAttribute* GetAttribute(VStringParam Name) = 0;

	/* Returns an iterator at first position through all attributes on this element */
	virtual AttributeIter AttributeBegin() = 0;

	/* Returns an iterator to the last position in all attributes on this element */
	virtual AttributeIter AttributeEnd() = 0;

	/* Returns an iterator to the first node element of the child tree */
	virtual NodeIter ChildBegin() = 0;

	/* Returns an iterator to the last node element of the child tree */ 
	virtual NodeIter ChildEnd() = 0;

	/* Call Visit from all child nodes */
	void VisitChildren(IVXMLVisitor& in_Visitor);
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLELEMENT_09_11_2004_H