/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
#include <V3d/Utils/VStreamReader.h>
#include <V3d/Core/RangeIter.h>
#include <V3d/Resource/Types/VTextFile.h>
#include <V3d/Graphics/Materials/EffectUtils.h>
#include <V3d/Core/DebugUtils.h>
#include <V3d/Graphics/Importer/VEffectLoader.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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


VMaterial* VMaterialResourceType::CreateMaterial(
	const VShaderPath& in_Technique, std::string in_ResourceName)
{
	//try
	//{
		VMaterial::PassList passes;
		passes.resize(in_Technique.GetRenderPassCount());
		
		for(vuint passNum = 0; passNum < in_Technique.GetRenderPassCount(); ++passNum)
		{
			VRenderStateList* pPass = CreatePass(
				in_Technique.RenderPass(passNum), in_ResourceName);

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
	//}
	//catch(VException& e)
	//{
	//	return 0;
	//}
}

VRenderStateList* VMaterialResourceType::CreatePass(
	const VRenderPass& in_Pass, std::string in_ResourceName)
{
	// decide which material type to use
	if( VGLSLPass::CanRealize(in_Pass) )
	{
		VRenderStateList::RenderStateList defaultStates = 
			m_StateCategories.CreateDefaultStates();

		// store resource dependencies (if a shader is changed, also recreate
		// materials which use it
		std::vector<std::string> dependantResources =
			VShaderCategory::GetResourceDependencies(in_Pass);

		for(std::vector<std::string>::iterator dep = dependantResources.begin();
			dep != dependantResources.end();
			++dep)
		{
			m_DependantResources.insert(make_pair(*dep, in_ResourceName));
		}

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
	std::string ext;

	if( fileName.length() > 1 )
		ext = fileName.substr(fileName.find_last_of("."), fileName.length());
	else
		ext = "";

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

VMaterialResourceType::CreatedMaterial 
	VMaterialResourceType::CreateMaterial(VResource* in_pResource)
{
	CreatedMaterial result;

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
			pMaterial = CreateMaterial(
				pEffectDescr->ShaderPath(techniqueNum), 
				in_pResource->GetQualifiedName());

			// try next technique
			++techniqueNum;
		}

		// no material could be created
		if( pMaterial == 0 )
		{
			VShaderPath path;
			VRenderPass& pass(path.AddRenderPass());
			// red to indicate an error
			pass.AddState(DefaultColorState(1, 0, 0, 1));
			pass.AddState(LightingState(true));
			pMaterial = CreateMaterial(path, in_pResource->GetQualifiedName());

			V3D_ASSERT(pMaterial != 0);
		}

		result.pMaterial = pMaterial;
		result.typeInfo = GetTypeInfo<IVMaterial>();
	}
	else if( IsEffectFile( in_pResource->GetData<VFileName>()->AsString() ) )
	{
		//TODO: move to resource type for VEffectDescription
		VEffectLoader loader;
		loader.LoadEffect(in_pResource->GetData<VFileName>()->AsString().c_str(),
			in_pResource);

		//Generate(in_pResource, in_Type);
		result = CreateMaterial(in_pResource);
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

		result.pMaterial = pMaterial;
		result.typeInfo = GetTypeInfo<VCGFXMaterial>();
		//in_pResource->AddData(pMaterial);

		//return true;
		//TODO: fehlerbehandlung
	}

	return result;
}

vbool VMaterialResourceType::Generate(
	resource::VResource* in_pResource,
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<IVMaterial>() == in_Type);

	static VThreadId lastThreadId = -1;
	VThreadId threadId = IdOfCurrentThread();

	if( threadId != lastThreadId )
	{
		lastThreadId = threadId;
		V3D_LOGLN("generating material from thread " << threadId);
	}

	if( in_pResource->ContainsData(in_Type) )
		return true;

	CreatedMaterial result = CreateMaterial(in_pResource);

	if( result.pMaterial != 0 )
	{
		//in_pResource->AddData(result.typeInfo, SharedPtr(result.pMaterial));
		in_pResource->AddData(result.pMaterial);
		return true;
	}
	else
	{
		return false;
	}
}

vbool VMaterialResourceType::AllowMutableAccess(
	const VTypeInfo& in_TypeInfo, const VResource* in_Resource) const
{
	return true;
	//return in_Resource->ContainsData<VCGFXMaterial>();
}

void VMaterialResourceType::UpdateMaterial(VResource* in_pResource)
{
	VEffectLoader loader;
	VEffectDescription effect = 
		loader.LoadEffect(in_pResource->GetQualifiedName().c_str());
	in_pResource->ReplaceData<VEffectDescription>(CopyPtr(effect));

	CreatedMaterial result = CreateMaterial(in_pResource);

	vout << "Updating material in resource " 
		<< in_pResource->GetQualifiedName() << " ... ";

	if( result.pMaterial != 0 )
	{
		in_pResource->ReplaceData<IVMaterial>(result.pMaterial);

		vout << "successful" << vendl;
	}
	else
	{
		vout << "failed" << vendl;
	}
}

void VMaterialResourceType::NotifyChange(
	const VTypeInfo& in_Type, VResource* in_pResource)
{
	V3D_LOGLN("changing material from thread " << IdOfCurrentThread());
	
	// if the effect description changed, update the material
	if( in_Type == GetCompileTimeTypeInfo<VEffectDescription>(0) )
	{
		UpdateMaterial(in_pResource);
	}
	//TODO: update _all_ materials instead of only one
	else if( m_DependantResources.find(in_pResource->GetQualifiedName())
		!= m_DependantResources.end() )
	{
		VResourceId matres(m_DependantResources[in_pResource->GetQualifiedName()].c_str());
		UpdateMaterial(&*matres);
	}
}

VMaterialResourceType::CreatedMaterial::CreatedMaterial()
{
	pMaterial = 0;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

