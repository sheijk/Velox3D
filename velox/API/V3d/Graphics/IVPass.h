#ifndef V3D_IVPASS_2005_08_18_H
#define V3D_IVPASS_2005_08_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVRenderState;

class IVPass
{
public:
	virtual ~IVPass() {};
	virtual vuint StateCount() const = 0;
	virtual const IVRenderState& GetState(vuint in_nPriority) const = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_IVPASS_2005_08_18_H
