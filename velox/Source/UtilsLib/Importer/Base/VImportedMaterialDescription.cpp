#include <v3dLib/Graphics/Importer/Base/VImportedMaterialDescription.h>
//-----------------------------------------------------------------------------
#include <v3d/Graphics.h>
#include <v3dLib/Graphics.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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
	m_sResourcePath = "/data/";
	m_sResourceParentName = "/textures";

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
	std::string ret = m_sResourceParentName;
	ret.append("/");
	ret.append(m_sMaterialName);

	return ret.c_str();
}

resource::VResourceId VImportedMaterialDescription::CreateResource()
{
	std::string FilenamePath;
	resource::VResourceManagerPtr pResourceManager;

	resource::VResourceId m_pResourceParent = pResourceManager->CreateResource(
		m_sResourceParentName.c_str());

	resource::VResourceId retVal = m_pResourceParent->AddSubResource(
		m_sMaterialName.c_str());


	if(m_sTextureImageName.size())
	{
		FilenamePath = m_sResourcePath;
		FilenamePath.append(m_sTextureImageName.c_str());

		retVal->AddData(
			new resource::VFileName(FilenamePath.c_str())
			);
	}

	retVal->AddData(new graphics::VEffectDescription(
		CreateEffectDescription()));

	return retVal;
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
