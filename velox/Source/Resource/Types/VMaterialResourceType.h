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
#include "../source/Graphics/OpenGL/Materials/VCGFXState.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
* Automatically loads materials
*
* @author: ins
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
	VRenderStateList* CreatePass(const VRenderPass& in_Pass) const;
	VMaterial* CreateMaterial(const VShaderPath& in_Technique) const;

	vbool IsCGFXFile(const std::string& in_strFileName) const;

	VCGFXStateCategory m_CGFXCategory;
	VStateCategoryList m_StateCategories;
	VTextureStateCategory m_TextureStateCategory;
	VMiscStateCategory m_MiscStateCategory;
	VVertexShaderCategory m_VertexShaderCategory;
	VPixelShaderCategory m_PixelShaderCategory;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::image
//-----------------------------------------------------------------------------
#endif // V3D_VMATERIALRESOURCETYPE_H
