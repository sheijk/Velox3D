#ifndef V3D_IVXMLCOMMENT_08_31_04_H
#define V3D_IVXMLCOMMENT_08_31_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include "IVXMLNode.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------
/**
 * The XML Comment interface
 * @author insane/acrylsword/sheijk
 * @version 2.0
 */
class IVXMLComment : public IVXMLNode
{
public:
	/** Returns the Comment */
	virtual VStringRetVal GetComment() const = 0;
	virtual void SetComment(VStringParam in_strComment) = 0;

	virtual	IVXMLElement* ToElement() { return 0; }
	virtual IVXMLComment* ToComment() { return this; }
	virtual IVXMLText* ToText() { return 0; }
};
//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLCOMMENT_08_31_04_H
