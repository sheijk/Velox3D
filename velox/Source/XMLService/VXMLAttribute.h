#ifndef V3D_VXMLATTRIBUTE_09_15_2004_H
#define V3D_VXMLATTRIBUTE_09_15_2004_H
//-----------------------------------------------------------------------------
#include <V3d/XML/IVXMLAttribute.h>
#include <V3d/Core/Wrappers/VString.h>
#include <V3dlib/Utils/VStringValue.h>
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The XML attribute implementation
 * @author insane/acrylsword
 * @version 2.0
 */

class VXMLAttribute : public IVXMLAttribute
{
public:
	VXMLAttribute(VStringParam Name, VStringParam Value);

	virtual VStringRetVal GetName();
	virtual v3d::utils::VStringValue GetValue();
	
	void SetName(VStringParam Name);
	void SetValue(VStringParam Value);

private:
	VXMLAttribute();

	VString m_strName;
	v3d::utils::VStringValue m_Value;
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLATTRIBUTE_09_015_2004_H
