#include "VXMLWriter.h"
#include <V3d/VFS/IVStreamFactory.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

VXMLWriter::VXMLWriter(VStringParam Filename)
{
	m_bIsOpen = false;
	m_bElementOpen = false; //TODO: remove this code
	m_bOpenTwice = false;
	m_Filename = Filename;
	m_pStreamInterface = NULL;
	
	m_pSmartPtr.Assign(new VFileStream(m_Filename.c_str(), VRWAccess, VCreateAlways));			m_pStreamInterface = m_pSmartPtr.Get();
	
	WriteDeclaration();
	
}

VXMLWriter::VXMLWriter(IVStream* pStream)
{
	m_bIsOpen = false;
	m_bElementOpen =  false;
	m_bOpenTwice = false;
	m_Filename = "";
	m_pStreamInterface = pStream;
	
	WriteDeclaration();

}
VXMLWriter::~VXMLWriter()
{
	vuint i;
	vuint j = m_ElementOpenStack.size();
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