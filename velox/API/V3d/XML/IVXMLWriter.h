/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVXMLWRITER_H
#define V3D_IVXMLWRITER_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypes.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The XML writer interface
 * @author insane
 * @version 1.0
 */

class IVXMLWriter
{

public:

	virtual ~IVXMLWriter(){};

	/*
	* Creates a new xml element (<Name)
	*/
	virtual void OpenElement(VStringParam Name) =0;

	/** Closes the last opened element. (/> or </Name>)*/
	virtual void CloseElement() =0;
	
	/** Adds an attribute to the current element.
	* May only be called directly after OpenElement	*/
	virtual void AddAttribute(VStringParam Name, VStringParam Value,...) =0;
	
	/** Adds a comment */
	virtual void AddComment(VStringParam Comment) =0;

	/**	Adds a text	*/ 
	virtual void AddText(VStringParam Text) =0;
	
};

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLWRITER_H

