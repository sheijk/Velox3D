#include "VXMLService.h"
//-----------------------------------------------------------------------------
#include <v3d/VFS/IVFileSystem.h>

namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * Register the service with strind ID "xml.service". 
 */

VXMLService::VXMLService(void) : IVXMLService("xml.service", 0)
{
	m_Vistor = NULL;
	m_bRecursionFirstCall = false;
	
}

VXMLService::~VXMLService(void)
{
}
/**
 * Creates the writer class with a filename
 */
IVXMLService::IVXMLWriterPtr VXMLService::CreateXMLWriter(VStringParam FileName)
{
	IVXMLWriterPtr pWriter;
	pWriter.Assign(new VXMLWriter(FileName));
	
	return pWriter;
	
}
/**
* Creates the writer class with a streaming device
*/
IVXMLService::IVXMLWriterPtr VXMLService::CreateXMLWriter(IVStreamPtr pStream)
{
	IVXMLWriterPtr pWriter;
	pWriter.Assign(new VXMLWriter(pStream));

	return pWriter;
}

/**
* Traversals the tinyxml tree and saves the attribute stats in a own format
*/

VXMLElement* VXMLService::TraversalAttributes(TiXmlElement* Element)
{
	TiXmlAttribute *att;
	VXMLAttribute attribute;
	VXMLElement* NewElement = new VXMLElement;


	NewElement->SetName(Element->Value());

	for(att = Element->FirstAttribute(); att; att = att->Next())
	{
		attribute.SetName(att->Name());
		attribute.SetValue(att->Value());

		NewElement->AddAttribute(&attribute);

	}

	return NewElement;
}

/**
 * Traversals the tinyxml tree by recursion
 */
void VXMLService::TraversalNodes(TiXmlNode* node)
{
	
	TiXmlNode* child = 0;
	vbool bCloseElement = false;

	if(m_bRecursionFirstCall)
	{
		
		if(node->Type() == TiXmlNode::ELEMENT)
		{
			TiXmlElement *ele;
			VXMLElement *NewElement;

			ele = node->ToElement();
			NewElement = TraversalAttributes(ele);

			m_Vistor->OnElementOpen(NewElement);
			std::string sName = NewElement->GetName();
			m_LastElementNameList.push(sName);
			bCloseElement = true;
			
			delete NewElement;
			m_bRecursionFirstCall = false;
		}

		if(node->Type() == TiXmlNode::COMMENT)
		{
			m_Vistor->OnComment(node->Value());
			m_bRecursionFirstCall = false;
		}

		if(node->Type() == TiXmlNode::TEXT)
				m_Vistor->OnText(node->Value());
	}

	for(child = node->FirstChild(); child; child = child->NextSibling())
	{
		vbool bElementOpen = false;

		if(child->Type() == TiXmlNode::ELEMENT)
		{
			VXMLElement *NewElement;
			TiXmlElement *ele;
		
			ele = child->ToElement();
			NewElement = TraversalAttributes(ele);
			m_Vistor->OnElementOpen(NewElement);
			std::string sName = NewElement->GetName();
			m_LastElementNameList.push(sName);
			bElementOpen = true;
			//m_Vistor->OnElementClose(NewElement);
			delete NewElement;
		
		}
		if(child->Type() == TiXmlNode::COMMENT)
 				m_Vistor->OnComment(child->Value());
		
		if(child->Type() == TiXmlNode::TEXT)
				m_Vistor->OnText(child->Value());
		
			
		TraversalNodes(child);
		
		if(bElementOpen)
		{
			VXMLElement ClosedElement;
			std::string sName = m_LastElementNameList.top();
			ClosedElement.SetName(sName.c_str());
			m_Vistor->OnElementClose(&ClosedElement);
			m_LastElementNameList.pop();
		}
	}
	if(bCloseElement)
	{
		VXMLElement ClosedElement;
		std::string sName = m_LastElementNameList.top();
		ClosedElement.SetName(sName.c_str());
		m_Vistor->OnElementClose(&ClosedElement);
		m_LastElementNameList.pop();
	}

}
/**
 * Call this mehtod to parse a xml file with an appro. visitor
 */
void VXMLService::ParseLocalXMLFile(
	VStringParam in_pcName, 
	IVXMLVisitor* in_pVisitor
	)
{
	if(in_pVisitor)
        m_Vistor = in_pVisitor;
	else
	{
		V3D_THROW(VXMLVistorException, "Vistor not vaild!");
		return;
	}

	TiXmlDocument Doc(in_pcName);
	Doc.LoadFile();

	if( Doc.Error())
		V3D_THROW(VXMLTinyXMLException, "Document could not be parsed!");

	TiXmlNode* node;

    //skip the decleration
	node = Doc.FirstChild();

	node = node->NextSibling();

	m_bRecursionFirstCall = true;
	
	for(node; node; node = node->NextSibling())
	{
		m_bRecursionFirstCall = true;
		TraversalNodes(node);
	}


	m_Vistor->OnFileEnd();

}

void VXMLService::ParseVfsXMLFile(
									VStringParam in_pcName, 
									IVXMLVisitor* in_pVisitor
									)
{
	// query vfs
	vfs::IVFileSystem& fileSys = *QueryObject<vfs::IVFileSystem>("vfs.fs");

	// open file
	vfs::IVFileSystem::FileStreamPtr fileStream = 
		fileSys.OpenFile(in_pcName, VReadAccess);
	
	// parse it
	this->ParseXMLFile(fileStream.Get(), in_pVisitor);
}

void VXMLService::ParseXMLFile(
	IVStream* in_pStream, 
	IVXMLVisitor* in_pVisitor
	)
{
	if(in_pVisitor)
		m_Vistor = in_pVisitor;
	else
	{
		V3D_THROW(VXMLVistorException, "Visitor not valid!");
		return;
	}

	TiXmlDocument Doc;
	
	//create a class to read from the stream
	VStreamReader Reader(in_pStream);
	
	Doc.Parse((char*)Reader.GetStreamBuffer());

	TiXmlNode* node;

	//skip the decleration
	node = Doc.FirstChild();
	node = node->NextSibling();

	m_bRecursionFirstCall = true;

	for(node ; node; node = node->NextSibling())
	{
		TraversalNodes(node);
		m_bRecursionFirstCall = true;
	}

	m_Vistor->OnFileEnd();
}

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------