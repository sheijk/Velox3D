#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------

#include <V3d/Messaging/VMessage.h>

#include <V3d/Core/VIOStream.h>
#include <V3dLib/Utils/VRegisterGuard.h>
#include <V3d/Entity/IVEntitySerializationService.h>

#include <V3d/Tags/VTagRegistry.h>

#include <sstream>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

namespace {
	/**
	 * A minimalistic list which does not call new. Use this for some cases
	 * where a list is needed before the memory manager has been set up
	 */
	template<typename T>
	struct VSimpleMallocList
	{
		enum CheckEnum { AlreadyInitialized = 0xCAFEBABE };

		void Append(T* newObj)
		{
			if( initChecker != AlreadyInitialized )
			{
				obj = 0;
				next = 0;
				initChecker = AlreadyInitialized;
			}

			VSimpleMallocList<T>* newList = 
				(VSimpleMallocList*)malloc(sizeof(VSimpleMallocList));

			newList->obj = newObj;

			newList->next = next;
			next = newList;
		}

		T* obj;
		VSimpleMallocList<T>* next;
		CheckEnum initChecker;
	};

	static VSimpleMallocList<VGenericPartParser> g_Parsers;

	class Registerer : public utils::VRegisterGuardBase
	{
	public:
		Registerer()
		{
			utils::VRegisterGuardBase::Register(this);
		}

		~Registerer()
		{
			utils::VRegisterGuardBase::Unregister(this);
		}

		void Register()
		{
			VEntitySerializationServicePtr pSerialService;

			VSimpleMallocList<VGenericPartParser>* x = &g_Parsers;

			VSimpleMallocList<VGenericPartParser>* parser = g_Parsers.next;
			while( parser ) 
			{
				pSerialService->Register(parser->obj);
				parser = parser->next;
			}
		}

		void Unregister()
		{
			VEntitySerializationServicePtr pSerialService;

			VSimpleMallocList<VGenericPartParser>* parser = g_Parsers.next;
			while( parser ) 
			{
				pSerialService->Unregister(parser->obj);
				parser = parser->next;
			}
		}
	};

	Registerer g_Registerer;
};

/**
 * standard c'tor
 */
VGenericPartParser::VGenericPartParser()
{
	g_Parsers.Append(this);
}

/**
 * d'tor
 */
VGenericPartParser::~VGenericPartParser()
{
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

		if( name != "type" && name != "tags" )
		{
			messaging::VMessage message;
			message.AddProperty("type", "update");
			message.AddProperty("name", name);
			message.AddProperty("value", value);

			pPart->Send(message);
		}
		else if( name == "tags" )
		{
			tags::VTagRegistryPtr pTagRegistry;

			std::stringstream tags(value);
			std::string tagName;

			while( ! tags.eof() )
			{
				tags >> tagName;
				pPart->AttachTag(pTagRegistry->GetTagWithName(tagName));
			}
		}

		++attrib;
	}

	return pPart;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
