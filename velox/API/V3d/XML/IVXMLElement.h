#ifndef V3D_IVXMLELEMNT_H
#define V3D_IVXMLELEMNT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypes.h>
#include <V3d/XML/IVXMLAttribute.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The XML Element interface
 * @author insane
 * @version 1.0
 */

class IVXMLElement
{
public:

	virtual VStringRetVal GetName() = 0;
	//TODO: warum keine iteratoren? was ist wenn man die elemente
	// 2x durchlaufen will? (sheijk)
	virtual IVXMLAttribute* GetFirstAttribute() = 0;
	virtual IVXMLAttribute* NextAttribute() = 0;
	virtual IVXMLAttribute* GetAttribute(VStringParam Name) = 0;


};

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLELEMNT_H
