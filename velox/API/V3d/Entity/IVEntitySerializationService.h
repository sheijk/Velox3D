#ifndef V3D_IVENTITYSERIALIZATIONSERVICE_2005_07_18_H
#define V3D_IVENTITYSERIALIZATIONSERVICE_2005_07_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Entity/VEntityExceptions.h>
#include <V3d/Entity/IVPart.h>
#include <V3d/Entity/IVPartParser.h>
#include <V3d/XML/IVXMLElement.h>

#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Can parse an xml file containing an entity scene and will create entities
 * and parts for it
 *
 * @author sheijk
 */
class IVEntitySerializationService : public VNamedObject
{
public:
	IVEntitySerializationService(VStringParam in_strName) 
		: VNamedObject(in_strName, 0) 
	{};

	virtual ~IVEntitySerializationService() {}

	/** 
	 * Looks up the "type" attribute and let's the registered parser for the
	 * type create a part from the xml node
	 *
	 * @throws VNoParserForTypeException if no parser for the given type has
	 * been registered
	 */
	virtual VSharedPtr<IVPart> ParsePart(xml::IVXMLElement& in_Node) = 0;

	/** 
	 * Will add the given part parse to the part parser list and will use the
	 * part parser for parts of in_pPartParser.GetType(). Only one part parser
	 * for the same type may be registered
	 *
	 * @throws VTypeAlreadyRegisteredException if a parser for the given type
	 * already has been registered before
	 */
	virtual void Register(IVPartParser* in_pPartParser) = 0;

	/**
	 * Will remove the registered part parser for the given type. If no parser
	 * for the type exists nothing will happen
	 */
	virtual void Unregister(IVPartParser* in_pPartParser) = 0;

	virtual void DumpInfo() = 0;
};

typedef VServicePtr<IVEntitySerializationService> VEntitySerializationServicePtr;
//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
template<>
inline v3d::entity::IVEntitySerializationService* 
v3d::QueryService<v3d::entity::IVEntitySerializationService>()
{
	return QueryObject<v3d::entity::IVEntitySerializationService>(
		"entity.serialization");
}
//-----------------------------------------------------------------------------
#endif // V3D_IVENTITYSERIALIZATIONSERVICE_2005_07_18_H
