#ifndef V3D_IVXMLELEMNT_H
#define V3D_IVXMLELEMNT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypes.h>
#include <V3d/XML/IVXMLAttribute.h>
#include <V3d/Core/Wrappers/VIterator.h>
#include <V3d/Core/VException.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

	typedef VException VXMLException;

/**
 * The XML Element interface
 * @author insane
 * @version 1.0
 */

class IVXMLElement
{
public:
typedef VBirectionalIterator<IVXMLAttribute> AttributeIter;

	virtual VStringRetVal GetName() = 0;
	virtual IVXMLAttribute* GetFirstAttribute() = 0;
	virtual IVXMLAttribute* NextAttribute() = 0;
	virtual IVXMLAttribute* GetAttribute(VStringParam Name) = 0;
	virtual AttributeIter AttributeBegin() = 0;
	virtual AttributeIter AttributeEnd() = 0;


};

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLELEMNT_H
