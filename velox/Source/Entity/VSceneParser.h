//TODO: add file creation date to file guard
#ifndef V3D_VSCENEPARSER_2005_07_18_H
#define V3D_VSCENEPARSER_2005_07_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVSceneParser.h>

#include <map>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VSceneParser : public IVSceneParser
{
public:
	VSceneParser();
	virtual ~VSceneParser();

	virtual void Register(IVPartParser* in_pPartParser);
	virtual void Unregister(utils::VFourCC in_Type);
	virtual VSharedPtr<IVPart> ParsePart(xml::IVXMLElement& in_Node);

private:
	typedef std::map<utils::VFourCC, IVPartParser*> ParserMap;

	ParserMap m_Parsers;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VSCENEPARSER_2005_07_18_H
