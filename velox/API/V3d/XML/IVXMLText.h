#ifndef V3D_IVXMLTEXT_H
#define V3D_IVXMLTEXT_H
//-----------------------------------------------------------------------------
#include <V3d/XML/IVXMLNode.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------

/** 
 * Text within an xml file. <element>ThisIsATextNode</element> (the element
 * tag is an IVXMLElement
 */
class IVXMLText : public IVXMLNode
{
public:
};

//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLTEXT_H
