#ifndef V3D_IVXMLCOMMENT_08_31_04_H
#define V3D_IVXMLCOMMENT_08_31_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include "IVXMLNode.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------
class IVXMLComment : public IVXMLNode
{
public:
	virtual VStringRetVal GetComment() = 0;
};
//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLCOMMENT_08_31_04_H
