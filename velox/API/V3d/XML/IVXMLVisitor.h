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
	//TODO: wo sind kommentare (<!-- -->), sowie einfacher Text etc.? (sheijk)
	// <text>dies ist ein text</text><!-- textfeld --> <- was passiert da?
	// text muss unbedingt noch rein, comments waeren gut
	virtual void OnElementClose(IVXMLElement* Element) =0;
	virtual void OnElementOpen(IVXMLElement* Element) =0;
	virtual void OnFileEnd() =0;
	
	
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLVISITOR_H
