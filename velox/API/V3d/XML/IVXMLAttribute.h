#ifndef V3D_IVXMLATTRIBUTE_H
#define V3D_IVXMLATTRIBUTE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------

class IVXMLAttribute
{
public:
	virtual void GetName() = 0;
	virtual void GetValue() = 0;
	virtual vint GetValueAsNum() = 0;
	virtual v3d::vfloat32 GetValueAsFloat() = 0;
};

//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVXMLATTRIBUTE_H
