#include <V3dLib/Graphics/Misc/VSimpleDrawList.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
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

void VSimpleDrawList::Add(VModel in_Model)
{
	m_Models.push_back(in_Model);
}
//-----------------------------------------------------------------------------

void VSimpleDrawList::Remove(VModel in_Model)
{
	m_Models.remove(in_Model);
}
//-----------------------------------------------------------------------------

void VSimpleDrawList::Render()
{
	ModelList::iterator modelIter = m_Models.begin();

	for( ; modelIter != m_Models.end(); ++modelIter)
	{
		VModel& model = *modelIter;
		MeshHandle hMesh = (*modelIter).hMesh;
		TransformMatrixPtr pTransform = model.pTransformation;

		m_Device.SetMatrix(IVDevice::ModelMatrix, *pTransform);

		for(vuint matid = 0; matid < hMesh->GetMaterialCount(); ++matid)
		{
			MaterialHandle hMaterial = &(hMesh->GetMaterial(matid));
			ApplyMaterial(hMaterial);
			m_Device.RenderMesh(hMesh);
		}
	}
}
//-----------------------------------------------------------------------------

IVDevice& VSimpleDrawList::GetDevice()
{
	return m_Device;
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
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
