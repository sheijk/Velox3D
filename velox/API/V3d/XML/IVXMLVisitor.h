///////////////////////////////////////////////////////////
//
//  IVXMLVisitor.h
//  Implementation of the Interface IVXMLVisitor
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////

#ifndef IVXMLVISITOR_H
#define IVXMLVISITOR_H

/**
* An interface used by IVXMLDocument.
* Use a class implementing this interface for parsing XML files. IVXMLDocument
* does not store the data for you. Instead use IVXMLVisitor to generate the data
* you need.
* @version 1.0
* @generator Enterprise Architect
* @created 18-Jun-2003 01:33:08
*/

#include <V3d/XML/IVXMLAttribute.h>
#include <V3d/XML/IVXMLElement.h>

namespace v3d
{
namespace xml
{


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

}
}

#endif
