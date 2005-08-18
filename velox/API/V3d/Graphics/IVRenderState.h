#ifndef V3D_IVRENDERSTATE_H
#define V3D_IVRENDERSTATE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
class IVStateCategory;

class IVRenderState
{
public:
	virtual const IVStateCategory* GetCategory() const = 0;

	virtual ~IVRenderState() {}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVRENDERSTATE_H
