#include "VEntitySerializationService.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
#include <V3d/Core/RangeIter/VSTLAccessorRangePolicy.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

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

VSharedPtr<IVPart> VEntitySerializationService::ParsePart(xml::IVXMLElement& in_Node)
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
		return VSharedPtr<IVPart>(0);
		//V3D_THROWMSG(VNoParserForTypeException,
		//	"Could not parse part with type " << type.c_str()
		//	<< " because no part parser for the type exists");
	}
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
