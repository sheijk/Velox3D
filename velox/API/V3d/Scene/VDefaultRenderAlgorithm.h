//TODO: add file creation date to file guard
#ifndef V3D_VDEFAULTRENDERALGORITHM_2005_05_22_H
#define V3D_VDEFAULTRENDERALGORITHM_2005_05_22_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Scene/IVRenderAlgorithm.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VDefaultRenderAlgorithm : public IVRenderAlgorithm
{
public:
	void Render(graphics::IVDevice& in_RenderTarget, IVRenderList& in_Objects);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VDEFAULTRENDERALGORITHM_2005_05_22_H
