#ifndef VXMLWRITER_H
#define VXMLWRITER_H

#include <v3d/XML/IVXMLWriter.h>
#include <stdio.h>
#include <stdarg.h>

#include <v3d/Core/Wrappers/VString.h>

namespace v3d{
namespace xml{




class VXMLWriter :	public IVXMLWriter
{
public:
	VXMLWriter(void);
	
	virtual void WriteDeclaration(VStringParam FileName);
	/*
	* Creates a new xml element (<Name)
	*/
	virtual void OpenElement(VStringParam name);
	/*
	* Closes the last opened element. (/> oder </Name>)
	*/
	virtual void CloseElement(VStringParam name);
	/*
	* Adds an attribute to the current element. May only be called directly after
	* OpenElement
	*/
	virtual void AddAttribute(VStringParam name, VStringParam value, ...);
	/*
	* Adds a comment
	*/
	virtual void AddComment(VStringParam text);
	/*
	* Adds a text
	*/
	//virtual void AddText(char* text);
	/*
	* Finishes writing. Cache will be written to disk.
	*/
	virtual void Close();

	

private:

	bool m_bIsOpen;
	bool m_bElementOpen;
	bool m_bOpenTwice;
	char m_Buffer[256];
	FILE* XmlFile;

	
};


}
}

#endif