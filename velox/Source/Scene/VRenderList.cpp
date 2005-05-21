#include <V3d/Scene/VRenderList.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter/VSTLAccessorRangePolicy.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VRenderList::VRenderList()
{
	m_nNextFreeId = 1;
}

IVRenderList::Id VRenderList::Add(const graphics::VModelMesh& in_Model)
{
	Id id = m_nNextFreeId;
	++m_nNextFreeId;

	m_Models.push_back(ModelMeshAndId(id, in_Model));

	return id;
}

IVRenderList::Id VRenderList::Add(const graphics::VModel& in_Model)
{
	Id id = m_nNextFreeId;
	++m_nNextFreeId;

	for(vuint partnum = 0; partnum < in_Model.GetPartCount(); ++partnum)
	{
		m_Models.push_back(ModelMeshAndId(id, in_Model.GetPart(partnum)));
	}

	return id;
}

void VRenderList::Remove(Id in_ModelId)
{
	ModelList::iterator iter = m_Models.begin();

	while( iter != m_Models.end() )
	{
		if( iter->first == in_ModelId )
		{
			iter = m_Models.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

VRangeIterator<graphics::VModelMesh> VRenderList::Meshes()
{
	return CreateAccesssorIterator<VPair2ndAccessor, graphics::VModelMesh>(
		m_Models.begin(), m_Models.end());
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
