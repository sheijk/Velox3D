/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VXMLWriter.h"

#include <v3d/VFS/IVFileSystem.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

VXMLWriter::VXMLWriter(VStringParam in_strFileName)
{
	m_bIsOpen = false;
	m_bElementOpen = false;
	m_bOpenTwice = false;
	m_Filename = in_strFileName;
	
	//TODO: zu datei erzeugung umwandeln
	vfs::IVFileSystem::FileStreamPtr ptr = 
		QueryObject<vfs::IVFileSystem>("vfs.fs")->OpenFile(in_strFileName,
															vfs::VWriteAccess);
	m_pSmartPtr = ptr;

	m_pStreamInterface = m_pSmartPtr.Get();
	
	WriteDeclaration();
}

VXMLWriter::VXMLWriter(IVStreamPtr pStream)
{
	m_bIsOpen = false;
	m_bElementOpen =  false;
	m_bOpenTwice = false;
	m_Filename = "";
	m_pStreamInterface = pStream.Get();
	m_pSmartPtr = pStream;
	
	WriteDeclaration();
}

VXMLWriter::~VXMLWriter()
{
	vuint i;
	vuint j = (vuint)m_ElementOpenStack.size();
	for(i = 0; i < j; i++)
		CloseElement();
		
	m_pSmartPtr.Release();
}

void VXMLWriter::WriteDeclaration()
{
	*m_pStreamInterface << "<?" << "xml version=\"1.0\"?>" <<"\n";
	m_bIsOpen = true;
}

void VXMLWriter::AddComment(VStringParam text)
{
	m_bOpenTwice = false;
	if(m_bElementOpen)
	{
		*m_pStreamInterface << ">";
		m_bElementOpen = false;
	}
		
	*m_pStreamInterface << "<!--" <<text<<"-->" <<"\n";
}

void VXMLWriter::OpenElement(VStringParam name)
{
	if(m_bIsOpen)
	{
		if(m_bOpenTwice)
			*m_pStreamInterface << ">\n";

		*m_pStreamInterface << "<" << name;
		m_bElementOpen = true;
	}
	m_bOpenTwice = true;
	m_ElementOpenStack.push(name);
}

void VXMLWriter::CloseElement()
{
	m_bOpenTwice = false;

	if(m_bIsOpen)
	{
		if(m_bElementOpen)
		{
			*m_pStreamInterface << "/>\n";
			if(!m_ElementOpenStack.empty())
				m_ElementOpenStack.pop();
		}
		else
		{
			*m_pStreamInterface << "</" << m_ElementOpenStack.top().c_str() <<">\n";

			if(!m_ElementOpenStack.empty())
				m_ElementOpenStack.pop();
		}
	}
	m_bElementOpen = false;
}

void VXMLWriter::AddAttribute(VStringParam name, VStringParam value, ...)
{
	memset( m_Buffer, 0, 256 );
	va_list	arguments;

	if (value == NULL)
		return;

	va_start(arguments, value);
	vsprintf(m_Buffer, value, arguments);
	va_end(arguments);

	m_bOpenTwice = false;
	
	if(m_bIsOpen && m_bElementOpen)
		*m_pStreamInterface << " " << name << "=\"" << m_Buffer << "\"";
}

void VXMLWriter::AddText(VStringParam Text)
{
	*m_pStreamInterface << Text;
}
//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------
