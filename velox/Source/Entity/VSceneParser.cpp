#include "VSceneParser.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VSceneParser::VSceneParser()
{
}

/**
 * d'tor
 */
VSceneParser::~VSceneParser()
{
}

void VSceneParser::Register(IVPartParser* in_pPartParser)
{
	if( m_Parsers.find(in_pPartParser->GetType()) == m_Parsers.end() )
	{
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

void VSceneParser::Unregister(std::string in_Type)
{
	m_Parsers.erase(in_Type);	
}

VSharedPtr<IVPart> VSceneParser::ParsePart(xml::IVXMLElement& in_Node)
{
	std::string type(in_Node.GetAttributeValue<std::string>("type"));

	ParserMap::iterator parserIter = m_Parsers.find(type);

	if( parserIter != m_Parsers.end() )
	{
		IVPartParser* parser = parserIter->second;

		return parser->Parse(in_Node);
	}
	else
	{
		V3D_THROWMSG(VNoParserForTypeException,
			"Could not parse part with type " << type.c_str()
			<< " because no part parser for the type exists");
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
