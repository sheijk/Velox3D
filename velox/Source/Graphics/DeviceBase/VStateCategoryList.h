#ifndef V3D_VSTATECATEGORYLIST_H
#define V3D_VSTATECATEGORYLIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/VMaterialDescription.h>
#include <v3d/Graphics/IVStateCategory.h>

#include "VRenderStateList.h"

#include <set>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VStateCategoryList
{
public:
	typedef VRenderStateList::RenderStateList RenderStateList;

private:
	typedef std::set<IVStateCategory*> CategoryContainer;

	CategoryContainer m_Categories;
	RenderStateList m_DefaultStates;

	void BuildDefaultList()
	{
		//CategoryContainer::iterator catIter = m_Categories.begin();
		//for( ;
	}
public:

	void RegisterCategory(IVStateCategory& in_Category)
	{
		m_Categories.insert(&in_Category);
	}

	VRenderStateList* CreateRenderStateList(const VMaterialDescription& in_Mat)
	{
		CategoryContainer::iterator cat = m_Categories.begin();

		RenderStateList states;
		IVRenderState* pState;

		for( ; cat != m_Categories.end(); ++cat)
		{
			pState = (*cat)->CreateState(in_Mat);
			states.push_back(pState);
		}

		return new VRenderStateList(states);
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTATECATEGORYLIST_H
