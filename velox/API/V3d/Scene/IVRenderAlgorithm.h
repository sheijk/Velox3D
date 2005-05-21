//TODO: add file creation date to file guard
#ifndef V3D_IVRENDERALGORITHM_2005_05_22_H
#define V3D_IVRENDERALGORITHM_2005_05_22_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVDevice.h>
#include <V3d/Scene/IVRenderList.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVRenderAlgorithm
{
public:
	virtual void Render(graphics::IVDevice& in_RenderTarget, IVRenderList& in_Objects) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_IVRENDERALGORITHM_2005_05_22_H
