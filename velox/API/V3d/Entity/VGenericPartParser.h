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

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VGENERICPARTPARSER_2005_10_20_H