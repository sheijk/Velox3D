#ifndef V3D_IVXMLTEXT_08_31_04_H
#define V3D_IVXMLTEXT_08_31_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/XML/IVXMLNode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------
class IVXMLText : public IVXMLNode
{
public:
	virtual VStringRetVal GetText() = 0;
};

//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLTEXT_08_31_04_H
