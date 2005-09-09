#ifndef V3D_IVXMLATTRIBUTE_09_15_2004_H
#define V3D_IVXMLATTRIBUTE_09_15_2004_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypes.h>
#include <V3dlib/Utils/VStringValue.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------
/**
 * The XML Attribute interface
 * @author insane/acrylsword/sheijk
 * @version 2.0
 */
class IVXMLAttribute
{
public:
	/** Returns the name of the xml attribute*/
    virtual VStringRetVal GetName() const = 0;

	/** Returns the value of this xml attribute */
	virtual v3d::utils::VStringValue GetValue() const = 0;

	/** Change the attribute's value */
	virtual void SetValue(const v3d::utils::VStringValue& in_NewValue) = 0;
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLATTRIBUTE_H
