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

	/* Will be called on an element closing event */
	virtual void OnElementClose(IVXMLElement* pElement) = 0;

	/* Will be called on an element opening event*/
	virtual void OnElementOpen(IVXMLElement* pElement) = 0;

	/* Will be called when file end is reached  */
	virtual void OnFileEnd() = 0;

	/* Will be called bz parsing a comment on the xml file */
	virtual void OnComment(VStringParam pText) = 0;

	/* Will be called on a text passaged included on the xml file */
	virtual void OnText(VStringParam pText) = 0;
	
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLVISITOR_H
