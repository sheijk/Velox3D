#include "VMaterialResourceType.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVMaterial.h>
#include <V3d/Graphics/VEffectDescription.h>
#include <../Source/Graphics/DeviceBase/VMaterial.h>

#include "../../Graphics/OpenGL/Materials/VFixedFunctionPass.h"
#include "../../Graphics/OpenGL/Materials/VCGFXMaterial.h"
#include <V3d/Resource/Types/VFileName.h>

#include <V3d/Vfs.h>
#include <V3dLib/Utils/VStreamReader.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using resource::VFileName;

/**
 * standard c'tor
 */
VMaterialResourceType::VMaterialResourceType()
{
	m_ManagedTypes.push_back(GetTypeInfo<IVMaterial>());

	//register all states
	m_StateCategories.RegisterCategory(m_CGFXCategory);
	m_StateCategories.RegisterCategory(m_TextureStateCategory);
	m_StateCategories.RegisterCategory(m_MiscStateCategory);
	m_StateCategories.RegisterCategory(m_VertexShaderCategory);
	m_StateCategories.RegisterCategory(m_PixelShaderCategory);

	int prio = 0;
	m_CGFXCategory.SetPriority(prio); ++prio;
	m_PixelShaderCategory.SetPriority(prio); ++prio;
	m_VertexShaderCategory.SetPriority(prio); ++prio;
	m_TextureStateCategory.SetPriority(prio); ++prio;
	m_MiscStateCategory.SetPriority(prio); ++prio;

	VFixedFunctionPass::SetCategories(
		&m_TextureStateCategory,
		&m_MiscStateCategory);
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

VMaterial* VMaterialResourceType::CreateMaterial(const VShaderPath& in_Technique) const
{
	VMaterial::PassList passes;
	passes.resize(in_Technique.GetRenderPassCount());
	
	for(vuint passNum = 0; passNum < in_Technique.GetRenderPassCount(); ++passNum)
	{
        VRenderStateList* pPass = CreatePass(in_Technique.RenderPass(passNum));

		if( pPass != 0 )
		{
            passes[passNum].Assign(pPass);
		}
		else
		{
			return 0;
		}
	}

	return new VMaterial(passes);
}

VRenderStateList* VMaterialResourceType::CreatePass(const VRenderPass& in_Pass) const
{
	// decide which material type to use
	if( VFixedFunctionPass::CanRealize(in_Pass) )
	{
		// create default states
		VRenderStateList::RenderStateList defaultStates =
			m_StateCategories.CreateDefaultStates();

		// create pass
		return new VFixedFunctionPass(defaultStates, in_Pass);
	}
	else
	{
		return 0;
	}
}

vbool VMaterialResourceType::IsCGFXFile(const std::string& in_strFileName) const
{
	const int len = in_strFileName.length();

	if( len > 2 && in_strFileName[len-2] == 'f' && in_strFileName[len-1] == 'x' )
		return true;
	else
		return false;
}

vbool VMaterialResourceType::Generate(
	resource::VResource* in_pResource,
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<IVMaterial>() == in_Type);

	if( in_pResource->ContainsData<VEffectDescription>() )
	{
		resource::VResourceDataPtr<const VEffectDescription> pEffectDescr
			= in_pResource->GetData<VEffectDescription>();

		VMaterial* pMaterial = 0;
		vuint techniqueNum = 0;

		// try to create a material for a technique, if best failes try
		// fallback techniques (aka shader paths)
		while( pMaterial == 0 && techniqueNum < pEffectDescr->GetShaderPathCount() )
		{
			pMaterial = CreateMaterial(pEffectDescr->ShaderPath(techniqueNum));

			// try next technique
			++techniqueNum;
		}

		if( pMaterial != 0 )
		{
			in_pResource->AddData<IVMaterial>(pMaterial);

			return true;
		}
		else
		{
			return false;
		}
	}
	else if( IsCGFXFile( in_pResource->GetData<VFileName>()->AsString() ) )
	{
		using namespace ::v3d::vfs;

		// load source into string
		VFileName fileName = *in_pResource->GetData<VFileName>();

		IVFileSystem::FileStreamPtr pFileStream = VFileSystemPtr()->OpenFile(
			fileName.AsString().c_str(), VReadAccess);
		utils::VStreamReader reader(&*pFileStream);
		std::string fileContent;
		reader.CopyToString(&fileContent);

		// create material
		VRenderStateList::RenderStateList defaultStates =
			m_StateCategories.CreateDefaultStates();

		VCGFXMaterial* pMaterial = new VCGFXMaterial(defaultStates, fileContent.c_str());
		in_pResource->AddData(pMaterial);

		return true;
		//TODO: fehlerbehandlung
	}

	return false;

	//std::vector<VRenderStateList*> passes;

	//// for each technique
	//for(vuint pathNum = 0; pathNum < pEffectDescr->GetShaderPathCount(); ++pathNum)
	//{
	//	VShaderPath& path(pEffectDescr->ShaderPath(pathNum);

	//	// decide type of render pass
	//	if( VFixedFunctionPass::CanRealize(passDescription) )
	//	{
	//		// create it and replace default states
	//	}
	//	// can't create tech
	//	else
	//	{
	//		////TODO: return error material
	//		//V3D_THROWMSG(VGraphicException, "Could not create render pass nr. "
	//		//	<< pathNum << " for effect in resource " <<
	//		//	in_pResource->GetQualifiedName());
	//	}
	//}

	// create and return material

	/*
// old implementation
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
	*/
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
