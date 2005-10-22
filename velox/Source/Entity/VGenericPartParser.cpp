#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------

#include <V3d/Messaging/VMessage.h>

#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VGenericPartParser::VGenericPartParser(VStringParam in_strType)
{
	m_strType = in_strType;
}

/**
 * d'tor
 */
VGenericPartParser::~VGenericPartParser()
{
}

std::string VGenericPartParser::GetType() const
{
	return m_strType;
}

VSharedPtr<IVPart> VGenericPartParser::Parse(xml::IVXMLElement& in_Node)
{
	using namespace xml;
	using std::string;

	VSharedPtr<IVPart> pPart = CreatePart();

	vout << "Creating part of type " << GetType() << vendl;

	IVXMLElement::AttributeIter attrib = in_Node.AttributeBegin();
	while( attrib.HasNext() )
	{
		string name = attrib->GetName();
		string value = attrib->GetValue().Get<string>();

		vout << "\t " << name << "=" << value << vendl;

		if( name != "type" )
		{
			messaging::VMessage message;
			message.AddProperty("type", "update");
			message.AddProperty("name", name);
			message.AddProperty("value", value);

			pPart->Send(message);
		}

		++attrib;
	}

	return pPart;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
