#include <V3d/Scene/VDefaultRenderAlgorithm.h>
//-----------------------------------------------------------------------------

#include <V3dLib/Graphics/Misc/MiscUtils.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

void VDefaultRenderAlgorithm::Render(
	graphics::IVDevice& in_RenderTarget, IVRenderList& in_Objects)
{
	VRangeIterator<graphics::VModelMesh> iter = in_Objects.Meshes();
	while( iter.HasNext() )
	{
		RenderMesh(in_RenderTarget, *iter);

		++iter;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
