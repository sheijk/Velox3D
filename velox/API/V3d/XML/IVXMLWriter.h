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
	virtual void WriteDeclaration(VStringParam FileName) =0;

	/*
	* Creates a new xml element (<Name)
	*/
	virtual void OpenElement(VStringParam name) =0;

	/** Closes the last opened element. (/> oder </Name>)*/
	virtual void CloseElement(VStringParam name) =0;
	
	/** Adds an attribute to the current element.
	* May only be called directly after OpenElement	*/
	virtual void AddAttribute(VStringParam name, VStringParam value,...) =0;
	
	/** Adds a comment */
	virtual void AddComment(VStringParam text) =0;

	/**	Adds a text	*/
	//virtual void AddText(char* text) =0; //TODO: warum ist die auskommentiert? (sheijk)
	
	/*
	* Finishes writing. Cache will be written to disk.
	*/
	virtual void Close() =0;

};

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif //V3D_IVXMLWRITER_H
