#include "VMaterialResourceType.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVMaterial.h>
#include <V3d/Graphics/VEffectDescription.h>
#include <../Source/Graphics/DeviceBase/VMaterial.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
* standard c'tor
*/
VMaterialResourceType::VMaterialResourceType()
{
	m_ManagedTypes.push_back(GetTypeInfo<IVMaterial>());

	//register all states
	m_StateCategories.RegisterCategory(m_TextureStateCategory);
	m_StateCategories.RegisterCategory(m_MiscStateCategory);
	m_StateCategories.RegisterCategory(m_VertexShaderCategory);
	m_StateCategories.RegisterCategory(m_PixelShaderCategory);
}

/**
* d'tor
*/
VMaterialResourceType::~VMaterialResourceType()
{
}

VRangeIterator<VTypeInfo> VMaterialResourceType::CreatedTypes()
{
	return CreateBeginIterator< std::vector<VTypeInfo> >(m_ManagedTypes);
}

vbool VMaterialResourceType::Generate(
	resource::VResource* in_pResource,
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<IVMaterial>() == in_Type);

	resource::VResourceDataPtr<const VEffectDescription> in_pEffectDescription
		= in_pResource->GetData<VEffectDescription>();

	// create materials
	std::vector<VRenderStateList*> statelists
		= m_StateCategories.CreateMaterialList(*in_pEffectDescription);

	std::vector<VRenderStateList> sl;

	for(vuint i = 0; i < statelists.size(); ++i)
	{
		sl.push_back(VRenderStateList(*statelists[i]));
		delete statelists[i];
		statelists[i] = 0;
	}

	VMaterial* pMaterial = new VMaterial(sl);

	if( statelists.size() > 0 )
	{
		in_pResource->AddData<IVMaterial>(pMaterial);
		return true;
	}
	else
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
