#include <V3d/Scene/VDefaultRenderAlgorithm.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>

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
	vint count = 0;
	
	VRangeIterator<graphics::VModelMesh> iter = in_Objects.Meshes();
	while( iter.HasNext() )
	{
		RenderMesh(in_RenderTarget, *iter);

		++iter;
		++count;
	}
	
	static int lastCount = -1;
	
	if( count != lastCount )
	{	
		vout << "rendered " << count << " meshes" << vendl;
		lastCount = count;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
