/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMATERIALRESOURCETYPE_H
#define V3D_VMATERIALRESOURCETYPE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Resource/Types/VFileName.h>
#include <V3d/Resource.h>

#include "../Source/Graphics/DeviceBase/VStateCategoryList.h"
#include "../Source/Graphics/OpenGL/VTextureStateCategory.h"
#include "../Source/Graphics/OpenGL/VMiscStateCategory.h"
#include "../Source/Graphics/OpenGL/VVertexShaderCategory.h"
#include "../Source/Graphics/OpenGL/Materials/VCGFXState.h"
#include "../Source/Graphics/OpenGL/VShaderCategory.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Automatically loads materials
 *
 * @author: ins, sheijk
 */
class VMaterialResourceType : public resource::IVResourceType
{
	std::vector<VTypeInfo> m_ManagedTypes;
public:
	VMaterialResourceType();
	virtual ~VMaterialResourceType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();
	virtual VRangeIterator<VTypeInfo> ManagedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);

	virtual vbool AllowMutableAccess(
		const VTypeInfo& in_TypeInfo, 
		const resource::VResource* in_Resource) const;

	virtual void NotifyChange(
		const VTypeInfo& in_Type, 
		resource::VResource* in_pResource);
private:
	struct CreatedMaterial
	{
		CreatedMaterial();

		VTypeInfo typeInfo;
		IVMaterial* pMaterial;
	};

	CreatedMaterial CreateMaterial(resource::VResource* in_pResource);

	VRenderStateList* CreatePass(
		const VRenderPass& in_Pass, std::string in_ResourceName);
	VMaterial* CreateMaterial(
		const VShaderPath& in_Technique, std::string in_ResourceName);

	vbool IsCGFXFile(const std::string& in_strFileName) const;

	void UpdateMaterial(resource::VResource* in_pResource);

	VCGFXStateCategory m_CGFXCategory;
	VStateCategoryList m_StateCategories;
	VTextureStateCategory m_TextureStateCategory;
	VMiscStateCategory m_MiscStateCategory;
	VShaderCategory m_ShaderCategory;

	typedef std::map<std::string, std::string> StringMap;
	/** If resource key is changed, material in resource value must be rebuild
	 * (shaders of material changed, etc.)
	 */
	StringMap m_DependantResources;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::image
//-----------------------------------------------------------------------------
#endif // V3D_VMATERIALRESOURCETYPE_H

