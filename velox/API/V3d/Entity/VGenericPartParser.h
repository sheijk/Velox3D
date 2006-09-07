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

/**
 */
class VGenericPartParser : public IVPartParser
{
public:
	VGenericPartParser();
	virtual ~VGenericPartParser();

	virtual std::string GetType() const = 0;
	virtual VSharedPtr<IVPart> Parse(xml::IVXMLElement& in_Node);

protected:
	virtual VSharedPtr<IVPart> CreatePart() = 0;
};

template<typename PartType>
class VPartParser : public VGenericPartParser
{
public:
	VPartParser() 
	{}
	//VPartParser(VStringParam in_strId) : VGenericPartParser(in_strId)
	//{}

protected:
	virtual VSharedPtr<IVPart> CreatePart()
	{
		return SharedPtr(new PartType());
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
		entity::VPartParser<PartClass> parser##PartClass;\
	}\
	void* Assure##PartClass##Exist()\
	{\
	return &parser##PartClass;\
	}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VGENERICPARTPARSER_2005_10_20_H

