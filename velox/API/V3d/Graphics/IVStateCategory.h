#ifndef V3D_IVSTATECATEGORY_H
#define V3D_IVSTATECATEGORY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
class IVRenderState;

class IVStateCategory
{
public:
	virtual IVRenderState* CreateState(const VMaterialDescription& in_Mat) = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVSTATECATEGORY_H
