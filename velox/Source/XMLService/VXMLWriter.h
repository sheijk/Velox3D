#ifndef V3D_VXMLWRITER_H
#define V3D_VXMLWRITER_H
//-----------------------------------------------------------------------------
#include <v3d/XML/IVXMLWriter.h>
#include <v3d/XML/IVXMLService.h>
#include <v3d/Core/Wrappers/VString.h>
#include <V3d/VFS/IVStream.h>
#include <v3d/Core/VObjectRegistry.h>
#include <V3d/VFS/VStreamOps.h>
#include "VFileStream.h"
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <stack>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
using namespace vfs;
//-----------------------------------------------------------------------------

/**
 * The XML writer implementation
 * @author insane
 * @version 1.0
 */
class VXMLWriter :	public IVXMLWriter
{
public:
	typedef IVXMLService::IVStreamPtr IVStreamPtr;

	VXMLWriter(VStringParam Filename);
	VXMLWriter(IVStreamPtr pStream);
	virtual ~VXMLWriter();
	
	/*
	* Creates a new xml element (<Name)
	*/
	virtual void OpenElement(VStringParam Name);
	/*
	* Closes the last opened element. (/> or </Name>)
	*/
	virtual void CloseElement();
	/*
	* Adds an attribute to the current element. May only be called directly after
	* OpenElement
	*/
	virtual void AddAttribute(VStringParam Name, VStringParam Value, ...);
	/*
	* Adds a comment
	*/
	virtual void AddComment(VStringParam Text);
	/*
	* Adds a text
	*/
	virtual void AddText(VStringParam Text);


private:

	void WriteDeclaration();

	vbool m_bIsOpen;
	vbool m_bElementOpen;
	vbool m_bOpenTwice;
	vchar m_Buffer[256];
	std::string m_Filename;
	IVStream* m_pStreamInterface;
	
	IVStreamPtr m_pSmartPtr;
	std::stack<std::string> m_ElementOpenStack;
};

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
#endif V3D_VXMLWRITER_H