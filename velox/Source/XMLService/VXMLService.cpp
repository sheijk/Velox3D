#include "VXMLService.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VIOStream.h>
#include <v3d/VFS/IVFileSystem.h>
#include "VXMLComment.h"
#include "VXMLText.h"
#include <v3d/Core/MemManager.h>

namespace v3d{
namespace xml{
//-----------------------------------------------------------------------------

/**
 * The constructor registers the service with unique string ID 
 * "xml.service". The attribute are initialized to a default
 * value.
 */
VXMLService::VXMLService() : IVXMLService("xml.service", 0)
{
	m_Vistor = NULL;
	m_bRecursionFirstCall = false;
}

/**
 * The destructor has nothing to do..
 */
VXMLService::~VXMLService()
{
}

/**
 * Creates the writer class that writes a xml file to a local data 
 * file with specified file name.
 * 
 * @param in_strFileName The name of the file.
 */
IVXMLService::IVXMLWriterPtr VXMLService::CreateXMLWriter(VStringParam in_strFileName)
{
	IVXMLWriterPtr pWriter;
	pWriter.Assign(new VXMLWriter(in_strFileName));
	
	return pWriter;
	
}
/**
* Creates the writer class that writes a xml file in the virtual file
* system.
* 
* @param in_pStream The stream to which the data is written ?!?! (muß besser werden :( )
*/
IVXMLService::IVXMLWriterPtr VXMLService::CreateXMLWriter(IVStreamPtr in_pStream)
{
	IVXMLWriterPtr pWriter;
	pWriter.Assign(new VXMLWriter(in_pStream));

	return pWriter;
}

bool VXMLService::Visit(IVXMLVisitor& in_Visitor, IVStream& in_Stream)
{
	GetRootElement(&in_Stream)->Visit(in_Visitor);

	return true;
}

bool VXMLService::Visit(IVXMLVisitor& in_Visitor, VStringParam in_strFile)
{
	GetRootElement(in_strFile)->Visit(in_Visitor);

	return true;
}

/**
 * Datei laden
 */
IVXMLService::IVXMLElementPtr VXMLService::GetRootElement(VStringParam in_pcName)
{
	TiXmlDocument Doc(in_pcName);
	Doc.LoadFile();

	if( Doc.Error())
	{
		std::string Error;
		Error.append("Document could not be parsed: ");
		Error.append(in_pcName);
		V3D_THROW(VXMLTinyXMLException, Error.c_str());
	}

	IVXMLElementPtr pElement;
	pElement.Assign(BeginTranslation(Doc));

	return pElement;    
}

/**
 * Stream in Buffer kopieren um tinyXML nitzen zu können.
 *
 * @author acrylsword
 */
IVXMLService::IVXMLElementPtr VXMLService::GetRootElement(IVStream* in_pStream)
{
	V3D_ASSERT(in_pStream != 0);

    TiXmlDocument Doc;
	
	//create a class to read from the stream
	VStreamReader Reader(in_pStream);
	
	Doc.Parse((char*)Reader.GetStreamBuffer());
	
	if( Doc.Error())
	{
//TODO:: in_pStream in die Fehlermeldung einbauen
		std::string Error;
		Error.append("Document could not be parsed: ");
		V3D_THROW(VXMLTinyXMLException, Error.c_str());
	}

	IVXMLElementPtr pElement;
	pElement.Assign(BeginTranslation(Doc));

	return pElement;    
}

VXMLElement* VXMLService::BeginTranslation(TiXmlDocument& in_Doc)
{
	VXMLElement* pReturn = TranslateElement(in_Doc.RootElement());

	TiXmlElement* pRootElement = in_Doc.RootElement();

	//skip the decleration
//	TiXmlNode* pNode = in_Doc.FirstChild();
/*		
	//add other node to our root element
	TiXmlNode* pChild = 0;
	while( pChild = pRootElement->IterateChildren(pChild) )
	{
		pReturn->AddChild(TranslateNode(pChild));
	}
*/
	return pReturn;
}

/**
 * Translate tiny xml node into the corresponding IVXMLNode
 *
 * @author acrlysword
 * @version 1.0
 * @todo Exception werfen statt 0 zurückzugeben
 */
IVXMLNode* VXMLService::TranslateNode(TiXmlNode* in_pNode)
{
    V3D_ASSERT(in_pNode != 0);
	
	if (in_pNode->Type() == TiXmlNode::ELEMENT)
	{
		return TranslateElement(in_pNode->ToElement());
	}

	if (in_pNode->Type() == TiXmlNode::COMMENT)
	{
	    return new VXMLComment(in_pNode->Value());
	}

	if (in_pNode->Type() == TiXmlNode::TEXT)
	{
		return new VXMLText(in_pNode->Value());
	}

	return 0;
}

/**
* Translates a TiXmlElement into a VXMLElement.
* @author acrylsword
* @version 1.0
*/
VXMLElement* VXMLService::TranslateElement(TiXmlElement* in_pElement)
{
	V3D_ASSERT(in_pElement != 0);
	

	VXMLElement *pReturn = new VXMLElement(in_pElement->Value());

	// Add attributes to VXMLElement
	TiXmlAttribute *pAttribute = in_pElement->FirstAttribute();
	while(pAttribute != 0) 
	{
		pReturn->AddAttribute(new VXMLAttribute(pAttribute->Name(),
			pAttribute->Value()));

		pAttribute = pAttribute->Next();
	}

	// Translate all children
	TiXmlNode* pChild = 0;
	while( pChild = in_pElement->IterateChildren(pChild))
	{
		pReturn->AddChild(TranslateNode(pChild));
	}

	return pReturn;
}

//-----------------------------------------------------------------------------
} //xml
} //v3d
//-----------------------------------------------------------------------------