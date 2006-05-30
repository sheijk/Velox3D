#include "VXMLModelResourceType.h"
//-----------------------------------------------------------------------------

#include <V3dLib/Graphics/Importer/VModelLoader.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::resource;

/**
 * standard c'tor
 */
VXMLModelResourceType::VXMLModelResourceType()
{
}

/**
 * d'tor
 */
VXMLModelResourceType::~VXMLModelResourceType()
{
}

VRangeIterator<VTypeInfo> VXMLModelResourceType::CreatedTypes()
{
	static VTypeInfo modelTypeInfo = GetTypeInfo<VModel>();

	return CreateSingleValueIterator(&modelTypeInfo);
}

vbool VXMLModelResourceType::Generate(
									  resource::VResource* in_pResource, VTypeInfo in_Type)
{
	try
	{
		VResourceDataPtr<const VFileName> pFileName = in_pResource->GetData<VFileName>();
		VModelLoader loader;

		loader.LoadMesh(pFileName->AsString().c_str(), in_pResource);

		return in_pResource->ContainsData<VModel>();
	}
	catch(VException& e)
	{
		V3D_LOG("Could not load model from resource \""
			<< in_pResource->GetQualifiedName() << "\": "
			<< e.ToString());				

		return false;
	}
}

void VXMLModelResourceType::NotifyChange(
	const VTypeInfo& in_Type, resource::VResource* in_pResource)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
