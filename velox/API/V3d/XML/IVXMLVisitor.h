/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVXMLVISITOR_H
#define V3D_IVXMLVISITOR_H
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------

class IVXMLElement;
/**
 * The interface for a XML visitor
 * @author insane
 * @version 1.0
 */
class IVXMLVisitor
{
public:
	//TODO: Text parsing
	virtual ~IVXMLVisitor(){};

	/** Will be called on an element closing event */
	virtual void OnElementClose(IVXMLElement* pElement) = 0;

	/** Will be called on an element opening event*/
	virtual void OnElementOpen(IVXMLElement* pElement) = 0;

	/** Will be called when file end is reached  */
	virtual void OnFileEnd() = 0;

	/** Will be called bz parsing a comment on the xml file */
	virtual void OnComment(VStringParam pText) = 0;

	/** Will be called on a text passaged included on the xml file */
	virtual void OnText(VStringParam pText) = 0;
};
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLVISITOR_H
