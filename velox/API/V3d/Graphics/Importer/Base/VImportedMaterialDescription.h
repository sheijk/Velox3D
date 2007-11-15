/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VIMPORTEDMATERIALDESCRIPTION_2005_05_17_H
#define V3D_VIMPORTEDMATERIALDESCRIPTION_2005_05_17_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/Wrappers/VString.h>
#include <V3d/Resource.h>
#include <V3d/Graphics/VEffectDescription.h>
#include <V3d/Graphics/Geometry/VColor4f.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * represents a common utitlity for imported materials
 */

class VImportedMaterialDescription
{
public:
		
	/*
	 * first param is material name
	 * second is texture file name
	 */
	VImportedMaterialDescription(
		VStringParam sName,
		VStringParam sTextureImageName);

	/*
	 * additional resource path to search for the texture file
	 */
	VImportedMaterialDescription(
		VStringParam sName,
		VStringParam sTextureImageName,
		VStringParam sResourcePath);

	VImportedMaterialDescription(VStringParam sResourcePath);


	virtual ~VImportedMaterialDescription();

	VStringRetVal GetMaterialName();
	VStringRetVal GetTextureImageName();
	void SetMaterialName(VStringParam sName);
	void SetTextureImageName(VStringParam sTextureImageName);

	void SetColorAmbient(graphics::VColor4f in_Ambient);
	void SetColorDiffuse(graphics::VColor4f in_Diffuse);
	void SetColorSpecular(graphics::VColor4f in_Specular);
	void SetTransparency(vfloat32 in_fValue);
	
	
	/*
	 * returns the resource name which was used to create the
	 * resource
	 * @note: complete path is returned
	 */
	VStringRetVal GetResourceName();
	
	/*
	 * returns the created resource id.
	 * creates the material and inserts itself to a resource
	 */
	resource::VResourceId CreateResource();
	
protected:

	graphics::VEffectDescription CreateEffectDescription();

	void Initialize();
    
	std::string m_sMaterialName;
	std::string m_sTextureImageName;
	std::string m_sResourcePath;
	std::string m_sResourceParentName;

	graphics::VColor4f m_Ambient;
	graphics::VColor4f m_Diffuse;
	graphics::VColor4f m_Specular;
	vfloat32 m_fTransparency;
	
	//resource::VResourceId m_pResourceId;
	resource::VResourceManagerPtr pResourceManager;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VIMPORTEDMATERIALDESCRIPTION_2005_05_17_H

