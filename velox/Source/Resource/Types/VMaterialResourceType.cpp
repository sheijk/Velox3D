#include "VMaterialResourceType.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVMaterial.h>
#include <V3d/Graphics/VEffectDescription.h>
#include <../Source/Graphics/DeviceBase/VMaterial.h>

#include "../../Graphics/OpenGL/Materials/VFixedFunctionPass.h"
#include "../../Graphics/OpenGL/Materials/VCGFXMaterial.h"
#include "../../Graphics/OpenGL/glsl/VGLSLPass.h"
#include <V3d/Resource/Types/VFileName.h>

#include <V3d/Vfs.h>
#include <V3dLib/Utils/VStreamReader.h>
#include <V3d/Core/RangeIter.h>
#include <V3d/Resource/Types/VTextFile.h>

#include <V3dLib/Graphics/Importer/VEffectLoader.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using resource::VFileName;
using namespace resource;

/**
 * standard c'tor
 */
VMaterialResourceType::VMaterialResourceType()
{
	m_ManagedTypes.push_back(GetTypeInfo<IVMaterial>());

	// priorities must be asssigned before registering the categories to
	// the category registry
	int prio = 0;
	m_CGFXCategory.SetPriority(prio); ++prio;
	m_ShaderCategory.SetPriority(prio); ++prio;
	m_TextureStateCategory.SetPriority(prio); ++prio;
	m_MiscStateCategory.SetPriority(prio); ++prio;

	//register all states
	m_StateCategories.RegisterCategory(m_CGFXCategory);
	m_StateCategories.RegisterCategory(m_ShaderCategory);
	m_StateCategories.RegisterCategory(m_TextureStateCategory);
	m_StateCategories.RegisterCategory(m_MiscStateCategory);

	VFixedFunctionPass::SetCategories(
		&m_TextureStateCategory,
		&m_MiscStateCategory);
	VGLSLPass::SetCategories(
		&m_ShaderCategory
		);
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

VRangeIterator<VTypeInfo> VMaterialResourceType::ManagedTypes()
{
	static VTypeInfo cgfxmatType = GetTypeInfo<VCGFXMaterial>();

	return CreateSingleValueIterator(&cgfxmatType, 1);
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
	if( VGLSLPass::CanRealize(in_Pass) )
	{
		VRenderStateList::RenderStateList defaultStates = 
			m_StateCategories.CreateDefaultStates();

		return new VGLSLPass(defaultStates, in_Pass);
	}
	else if( VFixedFunctionPass::CanRealize(in_Pass) )
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

vbool IsEffectFile(const std::string& fileName)
{
	std::string ext = fileName.substr(fileName.find_last_of("."), fileName.length());

	return ext == ".v3dmat";
}

vbool VMaterialResourceType::IsCGFXFile(const std::string& in_strFileName) const
{
	const int len = static_cast<int>(in_strFileName.length());

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

	if( in_pResource->ContainsData(in_Type) )
		return true;

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
	else if( IsEffectFile( in_pResource->GetData<VFileName>()->AsString() ) )
	{
		VEffectLoader loader;
		loader.LoadEffect(in_pResource->GetData<VFileName>()->AsString().c_str(),
			in_pResource);

		Generate(in_pResource, in_Type);

		return true;
	}
	else //if( IsCGFXFile( in_pResource->GetData<VFileName>()->AsString() ) )
	{
		using namespace ::v3d::vfs;

		std::string fileContent;

		if( in_pResource->ContainsData<VTextFile>() ) 
		{
			VResourceDataPtr<const VTextFile> pTextFile = 
				in_pResource->GetData<VTextFile>();

			fileContent = pTextFile->GetContent();
		}
		else if( IsCGFXFile( in_pResource->GetData<VFileName>()->AsString() ) )
		{
			// load source into string
			VFileName fileName = *in_pResource->GetData<VFileName>();

			IVFileSystem::FileStreamPtr pFileStream = VFileSystemPtr()->OpenFile(
				fileName.AsString().c_str(), VReadAccess);
			utils::VStreamReader reader(&*pFileStream);

			reader.CopyToString(&fileContent);
		}

		// create material
		VRenderStateList::RenderStateList defaultStates =
			m_StateCategories.CreateDefaultStates();

		VCGFXMaterial* pMaterial = new VCGFXMaterial(defaultStates, fileContent.c_str());
		in_pResource->AddData(pMaterial);

		return true;
		//TODO: fehlerbehandlung
	}

	return false;
}

vbool VMaterialResourceType::AllowMutableAccess(
	const VTypeInfo& in_TypeInfo, const VResource* in_Resource) const
{
	return true;
	//return in_Resource->ContainsData<VCGFXMaterial>();
}

void VMaterialResourceType::NotifyChange(
	const VTypeInfo& in_Type, VResource* in_pResource)
{
	if( in_pResource->ContainsData<VCGFXMaterial>() )
	{
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
