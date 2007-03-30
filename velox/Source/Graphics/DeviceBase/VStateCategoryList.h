/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSTATECATEGORYLIST_H
#define V3D_VSTATECATEGORYLIST_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/VEffectDescription.h>

#include <V3d/Graphics/IVStateCategory.h>

#include "VMaterial.h"

#include <set>
#include <memory>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class CategorySmaller
{
public:
	vbool operator()(const IVStateCategory* left, const IVStateCategory* right)
	{
		V3D_ASSERT(left != 0);
		V3D_ASSERT(right != 0);

		return left->GetPriority() < right->GetPriority();
	}
};

class VStateCategoryList
{
public:
	typedef VRenderStateList::RenderStateList RenderStateList;

	void RegisterCategory(IVStateCategory& in_Category);

	std::vector<VRenderStateList*> CreateMaterialList(
		const VEffectDescription& in_Effect);

	std::list<const IVRenderState*> CreateDefaultStates() const;

	const VRenderStateList& GetDefaultMaterial();

private:
	typedef std::set<IVStateCategory*, CategorySmaller> CategoryContainer;

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

