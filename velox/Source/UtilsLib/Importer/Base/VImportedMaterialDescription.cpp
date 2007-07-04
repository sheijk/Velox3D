/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/Importer/Base/VImportedMaterialDescription.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics.h>
#include <V3d/Graphics.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::graphics;

VImportedMaterialDescription::VImportedMaterialDescription( 
	VStringParam sName,
	VStringParam sTextureImageName)
{
	m_sMaterialName = sName;
	m_sTextureImageName = sTextureImageName;
	m_sResourcePath = "/system";
	m_sResourceParentName = "/graphics";

	Initialize();
}

VImportedMaterialDescription::VImportedMaterialDescription( 
	VStringParam sName,
	VStringParam sTextureImageName,
	VStringParam sResourcePath)			
{
	m_sMaterialName = sName;
	m_sTextureImageName = sTextureImageName;
	m_sResourcePath = sResourcePath;
	m_sResourceParentName = "/textures";
	
	Initialize();
}

VImportedMaterialDescription::VImportedMaterialDescription(
	VStringParam sResourcePath)
{
	m_sMaterialName = "none";
	m_sTextureImageName = "";
	m_sResourcePath = sResourcePath;
	m_sResourceParentName = "/textures";
	
	Initialize();
}

void VImportedMaterialDescription::Initialize()
{
	//make it white by default
	m_fTransparency = 0.0f;
	m_Ambient.red = 1.0f;
	m_Ambient.green = 1.0f;
	m_Ambient.blue = 1.0f;
}

VImportedMaterialDescription::~VImportedMaterialDescription()
{
}

VStringRetVal VImportedMaterialDescription::GetMaterialName()
{
	return m_sMaterialName.c_str();
}

VStringRetVal VImportedMaterialDescription::GetTextureImageName()
{
	return m_sTextureImageName.c_str();
}

void VImportedMaterialDescription::SetMaterialName(VStringParam sName)
{
	m_sMaterialName = sName;
}

void VImportedMaterialDescription::SetTextureImageName(
	VStringParam sTextureImageName)
{
	m_sTextureImageName = sTextureImageName;
}

VStringRetVal VImportedMaterialDescription::GetResourceName()
{
	std::string ret = m_sResourcePath;
	ret.append(m_sResourceParentName.c_str());
	ret.append("/");
	ret.append(m_sMaterialName);

	return ret.c_str();
}

resource::VResourceId VImportedMaterialDescription::CreateResource()
{
	bool isDefault = false;
	std::string FilenamePath;
	resource::VResourceManagerPtr pResourceManager;
	std::string name;
	if(m_sMaterialName == "defaultMaterial")
	{
		name = "/edit/mat/white-lit.v3dmat";
		isDefault = true;
	}
	else
	{
	  name = m_sResourcePath;
	  name.append("/textures");
	}


	//look if we have already created a texture sub resource
	try
	{
		resource::VResourceId texResource = pResourceManager->GetResourceByName(name.c_str());
	}
	catch(resource::VResourceNotFoundException e)
	{
		//create it
		resource::VResourceId newResource = pResourceManager->GetResourceByName(m_sResourcePath.c_str());
		newResource->AddSubResource("textures");
	}

	resource::VResourceId m_Resource = pResourceManager->GetResourceByName(name.c_str());
	if( !isDefault )
	{
	  resource::VResourceId result = m_Resource->AddSubResource(m_sMaterialName.c_str());
    
	  if(m_sTextureImageName.size())
	  {
		  FilenamePath = m_sResourcePath;
		  FilenamePath.append("/");
		  FilenamePath.append(m_sTextureImageName.c_str());
  		
		  std::string test = "/data/";
		  test.append(m_sTextureImageName);
		  result->AddData(
			  //new resource::VFileName(FilenamePath.c_str())
			  new resource::VFileName(test.c_str())
			  );
	  }

	  result->AddData(new graphics::VEffectDescription(
		  CreateEffectDescription()));

	  return result;
	}
	else
	  return m_Resource;
}

graphics::VEffectDescription
	VImportedMaterialDescription::CreateEffectDescription()
{
	graphics::VEffectDescription pED;

	VRenderPass& pass(pED.AddShaderPath().AddRenderPass());
	
	pass.AddState(DefaultColorState(VColor4f(
		m_Ambient.red, m_Ambient.green, m_Ambient.blue, m_fTransparency)
		));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));

	//if we have texture file add it
	if(m_sTextureImageName.size())
	{
		VState textureState = TextureState(
			GetResourceName(),
			FilterLinear, FilterLinear,
			TextureRepeat, TextureRepeat);
		
		pass.AddState(textureState);
	}

	return pED;
}

void VImportedMaterialDescription::SetColorAmbient(VColor4f in_Ambient)
{
	m_Ambient = in_Ambient;
}

void VImportedMaterialDescription::SetColorDiffuse(VColor4f in_Diffuse)
{
	m_Diffuse = in_Diffuse;
}

void VImportedMaterialDescription::SetColorSpecular(VColor4f in_Specular)
{
	m_Specular = in_Specular;
}

void VImportedMaterialDescription::SetTransparency(vfloat32 in_fValue)
{
	m_fTransparency = in_fValue;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------

