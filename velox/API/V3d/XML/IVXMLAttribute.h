#ifndef V3D_IVXMLATTRIBUTE_H
#define V3D_IVXMLATTRIBUTE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypes.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The XML Attribute interface
 * @author insane
 * @version 1.0
 */

class IVXMLAttribute
{
public:

	/* Returns the name of the xml attribute*/
    virtual VStringRetVal GetName() = 0;
	
	/* Returns the value of this xml attribute */
	virtual VStringRetVal GetValue() = 0;

};

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLATTRIBUTE_H
