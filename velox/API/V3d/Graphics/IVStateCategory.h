#ifndef V3D_IVSTATECATEGORY_H
#define V3D_IVSTATECATEGORY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/IVRenderState.h>
#include <v3d/Graphics/VEffectDescription.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
class IVRenderState;

class IVStateCategory
{
public:
	virtual IVRenderState* CreateState(const VRenderPass& in_Pass) = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVSTATECATEGORY_H
