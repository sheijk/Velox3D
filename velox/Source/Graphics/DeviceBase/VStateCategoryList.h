#ifndef V3D_VSTATECATEGORYLIST_H
#define V3D_VSTATECATEGORYLIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/VMaterialDescription.h>
#include <v3d/Graphics/VEffectDescription.h>

#include <v3d/Graphics/IVStateCategory.h>

#include "VRenderStateList.h"

#include <set>
#include <memory>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VStateCategoryList
{
public:
	typedef VRenderStateList::RenderStateList RenderStateList;

	void RegisterCategory(IVStateCategory& in_Category);

	std::vector<VRenderStateList*> CreateMaterialList(
		const VEffectDescription& in_Effect);

	const VRenderStateList& GetDefaultMaterial();

private:
	typedef std::set<IVStateCategory*> CategoryContainer;

	CategoryContainer m_Categories;
	//RenderStateList m_DefaultStates;
	std::auto_ptr<VRenderStateList> m_pDefaultMaterial;

	VRenderStateList* CreateMaterialForPass(const VRenderPass& in_Pass);
	std::vector<VRenderStateList*> CreateMaterialsForPath(
		const VShaderPath& in_Path);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTATECATEGORYLIST_H
