/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VGENERICPARTPARSER_2005_10_20_H
#define V3D_VGENERICPARTPARSER_2005_10_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPartParser.h>
#include <V3d/Core/VTypeInfo.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

void RegisterPartParser(IVPartParser* parser);

template<typename PartType>
class VGenericPartParser : public IVPartParser
{
public:
	VGenericPartParser()
	{
		RegisterPartParser(this);
	}

protected:
	virtual VSharedPtr<IVPart> Create()
	{
		VSharedPtr<IVPart> part = SharedPtr(new PartType());

		if( part != 0 && part->GetTypeInfo().GetName() != GetType() )
		{
			V3D_THROWMSG(VException, "Created part is of unexpected type."
				<< " Maybe you forgot to override GetTypeInfo()?."
				<< " Expected: " << GetType()
				<< " but found: " << part->GetTypeInfo().GetName() << "\n");
		}

		return part;
	}

	virtual std::string GetType() const
	{
		return GetTypeInfo<PartType>().GetName();
	}
};

/**
 * declares parser for the given class and adds a workaround for a "bug" in
 * msvc which will remove global variables from .libs if they are not referenced
 *
 * You will need to add a call to AssurePartClassExists() to make the protect
 * the parser from being stripped by the MSVC linker (-> PartParsers.cpp)
 */
#define V3D_REGISTER_PART_PARSER(PartClass) \
	namespace {\
		entity::VGenericPartParser<PartClass> parser##PartClass;\
	}\
	void* Assure##PartClass##Exists()\
	{\
	return &parser##PartClass;\
	}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VGENERICPARTPARSER_2005_10_20_H

