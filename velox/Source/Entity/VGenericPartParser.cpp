/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Messaging/VMessage.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/Utils/VRegisterGuard.h>
#include <V3d/Entity/IVEntitySerializationService.h>
#include <V3d/Tags/VTagRegistry.h>

#include <sstream>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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

	static VSimpleMallocList<IVPartParser> g_Parsers;

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

			VSimpleMallocList<IVPartParser>* x = &g_Parsers;

			VSimpleMallocList<IVPartParser>* parser = g_Parsers.next;
			while( parser ) 
			{
				pSerialService->Register(parser->obj);
				parser = parser->next;
			}
		}

		void Unregister()
		{
			VEntitySerializationServicePtr pSerialService;

			VSimpleMallocList<IVPartParser>* parser = g_Parsers.next;
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
void RegisterPartParser(IVPartParser* parser)
{
	g_Parsers.Append( parser );
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

