#ifndef V3D_IVRENDERSTATE_H
#define V3D_IVRENDERSTATE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/VRangeIterator.h>
#include <V3d/Graphics/IVParameter.h>
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

	virtual VRangeIterator<IVParameter> Parameters() = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVRENDERSTATE_H
