#include "VXMLService.h"

namespace v3d
{
namespace xml
{

VXMLService::VXMLService(void) : IVXMLService("XmlService", 0)
{
	m_Vistor = NULL;
}

VXMLService::~VXMLService(void)
{
}

IVXMLWriter* VXMLService::CreateXMLWriter()
{
	VXMLWriter* Writer = new VXMLWriter();
	return Writer;

}

/*IVXMLWriter* VXMLService::CreateXMLWriter(IVStream* in_pStream)
{
	return NULL;
}*/

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

void VXMLService::TraversalNodes(TiXmlNode* node)
{
	
	TiXmlNode* child = 0;

	for(child = node->FirstChild(); child; child = child->NextSibling())
	{
		if(child->Type() == TiXmlNode::ELEMENT)
		{
			VXMLElement *NewElement;
			TiXmlElement *ele;
		
			ele = child->ToElement();
			NewElement = TraversalAttributes(ele);
			m_Vistor->OnElementOpen(NewElement);
			m_Vistor->OnElementClose(NewElement);
			delete NewElement;
		
		}

		TraversalNodes(child);
	}

}

void VXMLService::ParseXMLFile(VStringParam in_pcName, IVXMLVisitor* in_pVisitor)
{
	if(in_pVisitor)
        m_Vistor = in_pVisitor;
	else
		return; //TODO: [ins] exception throw

	TiXmlDocument Doc(in_pcName);
	Doc.LoadFile();

	if( Doc.Error())
		return;	//TODO: [ins]- Exception should be thrown

	TiXmlNode* node;

	node = Doc.FirstChild();
	node = node->NextSibling();

	if(node->Type() == TiXmlNode::ELEMENT)
	{
		TiXmlElement *ele;
		VXMLElement *NewElement;

		ele = node->ToElement();
		NewElement = TraversalAttributes(ele);

		m_Vistor->OnElementOpen(NewElement);
		m_Vistor->OnElementClose(NewElement);
		delete NewElement;

	}


	for(node = Doc.FirstChild(); node; node = node->NextSibling())
		TraversalNodes(node);

	m_Vistor->OnFileEnd();

}

/*void VXMLService::ParseXMLFile(IVStream* in_pStream, IVXMLVisitor* in_pVisitor)
{
}

*/







}
}