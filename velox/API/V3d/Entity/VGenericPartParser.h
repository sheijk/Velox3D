#ifndef V3D_VGENERICPARTPARSER_2005_10_20_H
#define V3D_VGENERICPARTPARSER_2005_10_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPartParser.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VGenericPartParser : public IVPartParser
{
public:
	VGenericPartParser(VStringParam in_strType);
	virtual ~VGenericPartParser();

	virtual std::string GetType() const;
	virtual VSharedPtr<IVPart> Parse(xml::IVXMLElement& in_Node);

protected:
	virtual VSharedPtr<IVPart> CreatePart() = 0;

private:
	const vchar* m_strType;
};

template<typename PartType>
class VPartParser : public VGenericPartParser
{
public:
	VPartParser(VStringParam in_strId) : VGenericPartParser(in_strId)
	{}

protected:
	virtual VSharedPtr<IVPart> CreatePart()
	{
		return SharedPtr(new PartType());
	}
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VGENERICPARTPARSER_2005_10_20_H
