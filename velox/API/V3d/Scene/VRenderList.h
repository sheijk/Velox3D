//TODO: add file creation date to file guard
#ifndef V3D_VRENDERLIST_2005_05_22_H
#define V3D_VRENDERLIST_2005_05_22_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Scene/IVRenderList.h>
#include <V3d/Graphics/VModel.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>

#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VRenderList : public IVRenderList
{
public:
	VRenderList();

	virtual Id Add(const graphics::VModelMesh& in_Model);
	virtual Id Add(const graphics::VModel& in_Model);
	virtual void Remove(Id in_Model);

	vuint MeshCount() const;

	virtual VRangeIterator<graphics::VModelMesh> Meshes();

private:
	typedef std::pair<Id, graphics::VModelMesh> ModelMeshAndId;
	typedef std::list<ModelMeshAndId> ModelList;

	Id m_nNextFreeId;

	ModelList m_Models;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VRENDERLIST_2005_05_22_H
