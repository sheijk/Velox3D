#ifndef V3D_IVXMLNODE_08_31_04_H
#define V3D_IVXMLNODE_08_31_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/XML/IVXMLVisitor.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------
class IVXMLNode
{
public:

	enum NodeType
	{
		Comment,
		Text,
		Element
	};

	virtual void Visit(IVXMLVisitor& in_Visitor) = 0;
	virtual NodeType GetType() = 0;
};
//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLNODE_08_31_04_H