#ifndef V3D_IVXMLNODE_H
#define V3D_IVXMLNODE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------

/**
 * Interface for a xml node. Nodes are everything which can be part of
 * a xml file, like comments, elements, etc.
 */
class IVXMLNode
{
public:
	virtual const vchar* GetName() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLNODE_H
