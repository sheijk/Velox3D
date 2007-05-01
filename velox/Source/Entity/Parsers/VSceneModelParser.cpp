/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VSceneModelParser.h"
//-----------------------------------------------------------------------------
#include <V3d/Scene/VModelPart.h>
#include <V3d/Resource.h>
#include <V3d/Utils/VRegisterGuard.h>
#include <V3d/Entity/IVEntitySerializationService.h>
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::scene;
using namespace v3d::resource;
using namespace v3d::graphics;

/**
 * standard c'tor
 */
VSceneModelParser::VSceneModelParser()
{
	//vout << "\n\n\n\n\nVSceneModelParser c'tor" << vendl;
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

VSharedPtr<IVPart> VSceneModelParser::Create()
{
	return SharedPtr( new VModelPart() );
}
//VSharedPtr<IVPart> VSceneModelParser::Parse(xml::IVXMLElement& in_Node)
//{
//	try
//	{
//		// read mesh and material resource
//		std::string meshResource = in_Node.GetAttributeValue<std::string>("mesh");
//		std::string materialResource = in_Node.GetAttributeValue<std::string>("material");
//
//		VModel model(VModelMesh(
//			GetResourceData<IVMesh>( meshResource.c_str() ),
//			GetResourceData<IVMaterial>( materialResource.c_str() )));
//
//		// create part
//		VSharedPtr<IVPart> pPart(new VModelPart(model));
//		return pPart;
//	}
//	catch(VException& e)
//	{
//		V3D_THROWMSG(VPartParseException,
//			"Could not parse part of type " << GetType().c_str()
//			<< " due to exception: \n"
//			<< e.ToString());
//	}
//}

//namespace {
//	//VSceneModelParser p;
//	utils::VRegisterGuard<VSceneModelParser, IVEntitySerializationService> g;
//}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

