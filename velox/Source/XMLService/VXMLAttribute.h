#ifndef V3D_VXMLATTRIBUTE_H
#define V3D_VXMLATTRIBUTE_H
//-----------------------------------------------------------------------------
#include <string>
#include <V3d/XML/IVXMLAttribute.h>
#include <V3d/Core/Wrappers/VString.h>
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The XML attribute implementation
 * @author insane
 * @version 1.0
 */

class VXMLAttribute : public IVXMLAttribute
{
public:

	VXMLAttribute();
	VXMLAttribute(VStringParam Name, VStringParam Value);


	virtual VStringRetVal GetName();
	virtual VStringRetVal GetValue();
	
	void SetName(VStringParam Name);
	void SetValue(VStringParam Value);

private:

	std::string m_Name;
	std::string m_Value;

};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_VXMLATTRIBUTE_H
