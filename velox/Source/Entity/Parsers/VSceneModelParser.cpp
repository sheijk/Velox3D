#include "VSceneModelParser.h"
//-----------------------------------------------------------------------------

#include <V3d/Scene/VModelPart.h>
#include <V3d/Resource.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d::scene;
using namespace v3d::resource;
using namespace v3d::graphics;

/**
 * standard c'tor
 */
VSceneModelParser::VSceneModelParser()
{
}

/**
 * d'tor
 */
VSceneModelParser::~VSceneModelParser()
{
}

std::string VSceneModelParser::GetType() const
{
	return VModelPart::GetDefaultId();
}

VSharedPtr<IVPart> VSceneModelParser::Parse(xml::IVXMLElement& in_Node)
{
	try
	{
		// read mesh and material resource
		std::string meshResource = in_Node.GetAttributeValue<std::string>("mesh");
		std::string materialResource = in_Node.GetAttributeValue<std::string>("material");

		VModel model(VModelMesh(
			GetResourceData<IVMesh>( meshResource.c_str() ),
			GetResourceData<IVMaterial>( materialResource.c_str() )));

		// create part
		VSharedPtr<IVPart> pPart(new VModelPart(model));
		return pPart;
	}
	catch(VException& e)
	{
		V3D_THROWMSG(VPartParseException,
			"Could not parse part of type " << GetType().c_str()
			<< " due to exception: \n"
			<< e.ToString());
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
