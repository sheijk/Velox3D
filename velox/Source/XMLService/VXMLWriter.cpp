#include "VXMLWriter.h"

namespace v3d{
namespace xml{



VXMLWriter::VXMLWriter(void)
{
	XmlFile = NULL;
	m_bIsOpen = false;
	m_bElementOpen =  false;
	m_bOpenTwice = false;

}

void VXMLWriter::WriteDeclaration(VStringParam FileName)
{
	XmlFile = fopen (FileName, "w");
	if(XmlFile != NULL)
		m_bIsOpen = true;

	fprintf(XmlFile, "<?");
	fprintf(XmlFile, "xml version=\"1.0\"");
	fprintf(XmlFile, "?>");

		
}

void VXMLWriter::AddComment(VStringParam text)
{
	m_bOpenTwice = false;

	if(m_bIsOpen)
		fprintf(XmlFile, "<!--%s-->",text);
}

void VXMLWriter::Close()
{
	m_bOpenTwice = false;

	fclose(XmlFile);
	m_bIsOpen = false;
}

void VXMLWriter::OpenElement(VStringParam name)
{
	if(m_bIsOpen)
	{
		if(m_bOpenTwice)
			fprintf(XmlFile,">");

		fprintf(XmlFile,"<%s", name);
		m_bElementOpen = true;
	}
	m_bOpenTwice = true;
}

void VXMLWriter::CloseElement(VStringParam name)
{
	m_bOpenTwice = false;

	if(m_bIsOpen)
	{
		if(m_bElementOpen)
			fprintf(XmlFile,"/>");
		else
            fprintf(XmlFile,"</%s>", name);
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
	{
		fprintf(XmlFile," %s", name);
		fprintf(XmlFile,"=\"%s", m_Buffer);
		fprintf(XmlFile,"\"");
	}
}


}
}
