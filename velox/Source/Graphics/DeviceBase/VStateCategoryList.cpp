#include "VStateCategoryList.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

void VStateCategoryList::RegisterCategory(IVStateCategory& in_Category)
{
	m_Categories.insert(&in_Category);
}

//VRenderStateList* VStateCategoryList::CreateRenderStateList(
//	const VMaterialDescription& in_Mat)
//{
//	CategoryContainer::iterator cat = m_Categories.begin();
//
//	RenderStateList states;
//	IVRenderState* pState;
//
//	for( ; cat != m_Categories.end(); ++cat)
//	{
//		pState = (*cat)->CreateState(in_Mat);
//		states.push_back(pState);
//	}
//
//	return new VRenderStateList(states);
//}

VRenderStateList* VStateCategoryList::CreateMaterialForPass(
	const VRenderPass& in_Pass)
{
	// for each state category
	CategoryContainer::iterator cat = m_Categories.begin();
	RenderStateList states;

	for( ; cat != m_Categories.end(); ++cat)
	{
		// create state
		IVRenderState* pState = (*cat)->CreateState(in_Pass);
		if( pState != 0 )
			states.push_back(pState);
		else
		{
			//TODO:
			// release all states
			return 0;
		}
	}

	return new VRenderStateList(states);
}

std::vector<VRenderStateList*> VStateCategoryList::CreateMaterialsForPath(
	const VShaderPath& in_Path)
{
	std::vector<VRenderStateList*> materialList;
	materialList.resize(in_Path.GetRenderPassCount());

	// for each pass
	for(vuint passid = 0; passid < in_Path.GetRenderPassCount(); ++passid)
	{
		// create material
		VRenderStateList* pMaterial = 
			CreateMaterialForPass(in_Path.RenderPass(passid));

		if( pMaterial != 0 )
			materialList[passid] = pMaterial;
		else
		{
			//TODO
			// release all created materials			
			return std::vector<VRenderStateList*>();
		}			
	}

	return materialList;
}

std::vector<VRenderStateList*> VStateCategoryList::CreateMaterialList(
	const VEffectDescription& in_Effect)
{
	// for each path
	for(vuint pathid = 0; pathid < in_Effect.GetShaderPathCount(); ++pathid)
	{
		// try to build materials for path
		std::vector<VRenderStateList*> materials = 
			CreateMaterialsForPath(in_Effect.ShaderPath(pathid));

		if( materials.size() > 0 )
			return materials;

	}

	return std::vector<VRenderStateList*>();
}

const VRenderStateList& VStateCategoryList::GetDefaultMaterial()
{
	if( m_pDefaultMaterial.get() == 0 )
	{
		VRenderPass pass;

		m_pDefaultMaterial.reset(CreateMaterialForPass(pass));
	}

	return *m_pDefaultMaterial;
}

std::list<const IVRenderState*> VStateCategoryList::CreateDefaultStates() const
{
    VEffectDescription defaultEffect;
	VRenderPass& pass(defaultEffect.AddShaderPath().AddRenderPass());

	std::list<const IVRenderState*> states;

	for( CategoryContainer::const_iterator cat = m_Categories.begin();
		cat != m_Categories.end(); ++cat)
	{
		states.push_back((*cat)->CreateState(pass));
	}

	return states;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
