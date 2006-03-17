#ifndef V3D_VENTITYSERIALIZATIONSERVICE_2005_07_18_H
#define V3D_VENTITYSERIALIZATIONSERVICE_2005_07_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVEntitySerializationService.h>

#include <map>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VEntitySerializationService : public IVEntitySerializationService
{
public:
	VEntitySerializationService();
	virtual ~VEntitySerializationService();

	virtual void Register(IVPartParser* in_pPartParser);
	virtual void Unregister(IVPartParser* in_pPartParser);
	virtual VSharedPtr<IVPart> ParsePart(xml::IVXMLElement& in_Node);
	virtual VSharedPtr<VEntity> ParseScene(xml::IVXMLElement& in_Node);

	virtual VRangeIterator<IVPartParser> PartParsers();
	virtual void DumpInfo();
private:
	typedef std::map<std::string, IVPartParser*> ParserMap;

	ParserMap m_Parsers;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VENTITYSERIALIZATIONSERVICE_2005_07_18_H