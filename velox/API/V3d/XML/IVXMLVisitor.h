#ifndef V3D_IVXMLVISITOR_H
#define V3D_IVXMLVISITOR_H
//-----------------------------------------------------------------------------
#include <V3d/XML/IVXMLAttribute.h>
#include <V3d/XML/IVXMLElement.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The interface for a XML visitor
 * @author insane
 * @version 1.0
 */

class IVXMLVisitor
{
public:
	//TODO Text parsing
	virtual void OnElementClose(IVXMLElement* pElement) = 0;
	virtual void OnElementOpen(IVXMLElement* pElement) = 0;
	virtual void OnFileEnd() = 0;
	virtual void OnComment(VStringParam pText) = 0;
	
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLVISITOR_H
