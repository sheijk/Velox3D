#include "VSimpleDrawList.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
namespace drawlist {
//-----------------------------------------------------------------------------

VSimpleDrawList::VSimpleDrawList(IVDevice& in_Device) : m_Device(in_Device)
{
}
//-----------------------------------------------------------------------------

VSimpleDrawList::~VSimpleDrawList()
{
	m_Models.clear();
}
//-----------------------------------------------------------------------------

void VSimpleDrawList::Add(VModel* in_pModel)
{
	m_Models.push_back(in_pModel);
}
//-----------------------------------------------------------------------------

void VSimpleDrawList::Remove(VModel* in_pModel)
{
	m_Models.remove(in_pModel);
}
//-----------------------------------------------------------------------------

void VSimpleDrawList::Render()
{
	ModelList::iterator modelIter = m_Models.begin();

	for( ; modelIter != m_Models.end(); ++modelIter)
	{
		MaterialHandle hMaterial = (*modelIter)->hMaterial;
		MeshHandle hMesh = (*modelIter)->hMesh;

		ApplyMaterial(hMaterial);
		m_Device.RenderMesh(hMesh);
	}
}
//-----------------------------------------------------------------------------

void VSimpleDrawList::ApplyMaterial(IVMaterial* in_pRenderStates)
{
	for(vuint prio = 0; prio < in_pRenderStates->StateCount(); ++prio)
	{
		m_Device.ApplyState(in_pRenderStates->GetState(prio));
	}
}


//-----------------------------------------------------------------------------
} // namespace drawlist
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
