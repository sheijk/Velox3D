#ifndef V3D_IVRENDERLIST_2005_05_20_H
#define V3D_IVRENDERLIST_2005_05_20_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Graphics/VModel.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class IVRenderList
{
public:
	typedef vuint Id;
	static Id GetInvalidId() { return 0; }

	virtual ~IVRenderList() {}

	virtual Id Add(const graphics::VModelMesh& in_Model) = 0;
	virtual void Remove(Id in_Model) = 0;

	virtual VRangeIterator<graphics::VModelMesh> Meshes() = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_IVRENDERLIST_2005_05_20_H
