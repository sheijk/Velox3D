/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VEntitySerializationService.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
#include <V3d/Core/RangeIter/VSTLAccessorRangePolicy.h>
#include <V3d/Tags/VTagRegistry.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace xml;

/**
 * standard c'tor
 */
VEntitySerializationService::VEntitySerializationService() :
	IVEntitySerializationService("entity.serialization")
{
}

/**
 * d'tor
 */
VEntitySerializationService::~VEntitySerializationService()
{
}

void VEntitySerializationService::Register(IVPartParser* in_pPartParser)
{
	if( m_Parsers.find(in_pPartParser->GetType()) == m_Parsers.end() )
	{
		//vout << "part parser for type <" << in_pPartParser->GetType()
			//<< "> registered" << vendl;

		m_Parsers[in_pPartParser->GetType()] = in_pPartParser;
	}
	else
	{
		V3D_THROWMSG(VTypeAlreadyRegisteredException,
			"Can't register PartParser for type '" 
			<< in_pPartParser->GetType().c_str()
			<< "' because there is already a parser registered for it");
	}
}

void VEntitySerializationService::Unregister(IVPartParser* in_pParser)
{
	m_Parsers.erase(in_pParser->GetType());
}

//namespace {
//	vbool IsEditorOnlyPartType(const std::string& in_strPartType)
//	{
//		return in_strPartType == "shooting";
//	}
//}

VSharedPtr<IVPart> VEntitySerializationService::ParsePart(xml::IVXMLElement& in_Node)
{
	const std::string type( in_Node.GetAttributeValue<std::string>("type") );

	ParserMap::iterator parserIter = m_Parsers.find(type);

	if( parserIter != m_Parsers.end() )
	{
		IVPartParser* parser = parserIter->second;

		VSharedPtr<IVPart> part = parser->Create();
		part->FromXML( in_Node );

		return part;
	}
	else
	{
		V3D_THROWMSG(VNoParserForTypeException,
			"Could not parse part with type \"" << type.c_str()
			<< "\" because no part parser for the type exists");
	}
}

//VSharedPtr<IVPart> VEntitySerializationService::ParsePart(xml::IVXMLElement& in_Node)
//{
//	std::string type(in_Node.GetAttributeValue<std::string>("type"));
//
//	if( IsEditorOnlyPartType(type) )
//		return VSharedPtr<IVPart>(0);
//
//	ParserMap::iterator parserIter = m_Parsers.find(type);
//
//	if( parserIter != m_Parsers.end() )
//	{
//		IVPartParser* parser = parserIter->second;
//
//		return parser->Create();
//	}
//	else
//	{
//		V3D_THROWMSG(VNoParserForTypeException,
//			"Could not parse part with type \"" << type.c_str()
//			<< "\" because no part parser for the type exists");
//	}
//}

VSharedPtr<VEntity> VEntitySerializationService::Parse(xml::IVXMLElement& in_Node)
{
	VSharedPtr<VEntity> pEntity(new VEntity());

	IVXMLAttribute* attrib = in_Node.GetAttribute("name");
	std::string name;
	if( attrib != NULL )
	{
		name = attrib->GetValue().Get<std::string>();
		pEntity->SetName(name);
	}

	VRangeIterator<IVXMLNode> childNode = in_Node.ChildBegin();
	while( childNode.HasNext() )
	{
		IVXMLElement* element = childNode->ToElement();
		if( element != NULL )
		{
			if( element->GetName() == "part" )
				pEntity->AddPart(ParsePart(*element));
			else if( element->GetName() == "entity" )
				pEntity->AddChild(Parse(*element));
		}

		++childNode;
	}

	return pEntity;		
}

void ApplySettings(xml::IVXMLElement& in_Node, IVPart& in_Part)
{
	using namespace xml;
	using std::string;

	const std::string xmlTypeName = in_Node.GetAttributeValue<std::string>("type");
	const std::string partTypeName = in_Part.GetTypeInfo().GetName();

	if( xmlTypeName == partTypeName )
	{
		in_Part.FromXML( in_Node );
	}
	else
	{
		// this is the wrong part, continue

		//V3D_THROWMSG(VException, 
		//	"Error while applying settings to scene: expected '"
		//	<< partTypeName << "' but found xml node for '"
		//	<< xmlTypeName << "'");
	}
}

void ApplySettings(xml::IVXMLElement& in_Node, VEntity& in_Entity)
{
	try
	{
		IVXMLAttribute* attrib = in_Node.GetAttribute("name");

		VRangeIterator<IVXMLNode> childNode = in_Node.ChildBegin();
		while( childNode.HasNext() )
		{
			IVXMLElement* element = childNode->ToElement();
			if( element != NULL )
			{
				if( element->GetName() == "part" )
				{
					VRangeIterator<IVPart> partIter = in_Entity.PartIterator();
					while( partIter.HasNext() )
					{
						ApplySettings(*element, *partIter);
						++partIter;
					}
				}
				else if( element->GetName() == "entity" )
				{
					std::string entityName = element->GetAttributeValue<std::string>("name");
					VSharedPtr<VEntity> pChild = in_Entity.GetChildWithName(entityName);

					if( pChild != 0 )
						ApplySettings(*element, *pChild);
				}
			}

			++childNode;
		}
	}
	catch(VException& e)
	{
		vout << "Catched exception while parsing scene: " << e.ToString();
	}
}

VSharedPtr<VEntity> VEntitySerializationService::ParseScene(xml::IVXMLElement& in_Node)
{
	VSharedPtr<VEntity> pEntity = Parse(in_Node);

	//if( pEntity != 0 )
	//{
	//	//TODO: find a nice solution..
	//	// we don't know in which order settings of a part will be loaded
	//	// at least "material" needs to be set before any "mat.*" parameters
	//	// are set
	//	// thus we apply them twice
	//	ApplySettings(in_Node, *pEntity);
	//	ApplySettings(in_Node, *pEntity);
	//}

	return pEntity;
}

void VEntitySerializationService::DumpInfo()
{
	ParserMap::iterator parser = m_Parsers.begin();
	for( ; parser != m_Parsers.end(); ++parser )
	{
		vout << parser->first << vendl;
	}
}

VRangeIterator<IVPartParser> VEntitySerializationService::PartParsers()
{
	return CreateAccesssorIterator<VPair2ndDerefAccessor, IVPartParser>(
		m_Parsers.begin(), m_Parsers.end());
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------


