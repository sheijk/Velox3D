#include "VImported3dsResourceType.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/VModel.h>
#include <V3d/Graphics/Importer/3DS/VImported3DS.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
* standard c'tor
*/
VImported3DSResourceType::VImported3DSResourceType()
{
	m_ManagedTypes.push_back(GetTypeInfo<graphics::VModel>());
}

/**
* d'tor
*/
VImported3DSResourceType::~VImported3DSResourceType()
{
}

VRangeIterator<VTypeInfo> VImported3DSResourceType::CreatedTypes()
{
	return CreateBeginIterator< std::vector<VTypeInfo> >(m_ManagedTypes);
}

vbool VImported3DSResourceType::Generate(
	resource::VResource* in_pResource,
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<graphics::VModel>() == in_Type);
	
	//get filename
	const resource::VFileName* pFileName =
		&*in_pResource->GetData<resource::VFileName>();
		
	if( pFileName )
	{
		graphics::VModel* pModel = new graphics::VModel();
		utils::VImported3DS* pImporter = new utils::VImported3DS();

		if(pImporter->CreateModel(pModel,
			pFileName->AsString().c_str()))
		{
			delete pImporter;
			in_pResource->AddData(pModel);
			return true;
		}
		else
		{
			delete pImporter;
			return false;
		}
	}

	else
		return false;
}

void VImported3DSResourceType::NotifyChange(
	const VTypeInfo& in_Type, resource::VResource* in_pResource)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
