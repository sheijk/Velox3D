/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/Misc/VSimpleDrawList.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace math;
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
			break;
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
		VModelMesh::MeshPtr hMesh = model.GetMesh();
		VModelMesh::MaterialPtr hMaterial = model.GetMaterial();
		VMatrix44f& transform(*model.GetTransform());

		m_Device.SetMatrix(IVDevice::ModelMatrix, transform);

		for(vuint matid = 0; matid < hMaterial->PassCount(); ++matid)
		{
			const IVPass* hPass = &(hMaterial->GetPass(matid));
			ApplyMaterial(hPass);
			m_Device.RenderMesh(&*hMesh);
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

