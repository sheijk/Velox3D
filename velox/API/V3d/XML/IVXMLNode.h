#ifndef V3D_IVXMLNODE_08_31_04_H
#define V3D_IVXMLNODE_08_31_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/XML/IVXMLVisitor.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------

class IVXMLElement;
class IVXMLComment;
class IVXMLText;

/**
 * The XML Node interface
 * @author insane/acrylsword/sheijk
 * @version 2.0
 */
class IVXMLNode
{
public:

	enum NodeType
	{
		Comment,
		Text,
		Element
	};
	
	/** Visit this node */
	virtual void Visit(IVXMLVisitor& in_Visitor) = 0;

	virtual	IVXMLElement* ToElement() = 0;
	virtual IVXMLComment* ToComment() = 0;
	virtual IVXMLText* ToText() = 0;

	/** Returns the node type */
	virtual NodeType GetType() = 0;
};
//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLNODE_08_31_04_H
