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
	m_nNextFreeId = 1;
}
//-----------------------------------------------------------------------------

VSimpleDrawList::~VSimpleDrawList()
{
	m_Models.clear();
}
//-----------------------------------------------------------------------------

IVDrawList::ModelMeshId VSimpleDrawList::Add(VModelMesh in_Model)
{
	ModelMeshId id = m_nNextFreeId;
	++m_nNextFreeId;

	m_Models.push_back(ModelMeshAndId(id, in_Model));

	return id;
}
//-----------------------------------------------------------------------------

void VSimpleDrawList::Remove(ModelMeshId in_ModelId)
{
	ModelList::iterator delCandidate = m_Models.begin();
	for( ; delCandidate != m_Models.end(); ++delCandidate)
	{
		if( delCandidate->first == in_ModelId )
		{
			m_Models.erase(delCandidate);
		}
	}

	//m_Models.remove(in_Model);
}
//-----------------------------------------------------------------------------

void VSimpleDrawList::Render()
{
	ModelList::iterator modelIter = m_Models.begin();

	for( ; modelIter != m_Models.end(); ++modelIter)
	{
		VModelMesh& model = modelIter->second;
		IVMesh* hMesh = model.GetMesh();
		IVMaterial* hMaterial = model.GetMaterial();
		VMatrix44f& transform(model.GetTransform());

		m_Device.SetMatrix(IVDevice::ModelMatrix, transform);

		for(vuint matid = 0; matid < hMaterial->PassCount(); ++matid)
		{
			const IVPass* hPass = &(hMaterial->GetPass(matid));
			ApplyMaterial(hPass);
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

void VSimpleDrawList::ApplyMaterial(const IVPass* in_pRenderStates)
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
