#ifndef V3D_IVXMLTEXT_08_31_04_H
#define V3D_IVXMLTEXT_08_31_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/XML/IVXMLNode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------
/**
 * The XML Text interface
 * @author insane/acrylsword/sheijk
 * @version 2.0
 */
class IVXMLText : public IVXMLNode
{
public:
	/** Returns the text */
	virtual VStringRetVal GetText() = 0;
};

//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLTEXT_08_31_04_H