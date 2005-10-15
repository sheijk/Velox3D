#ifndef V3D_VORIENTATIONGRIDPART_2005_10_15_H
#define V3D_VORIENTATIONGRIDPART_2005_10_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/VMeshPartBase.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VOrientationGridPart : public scene::VMeshPartBase
{
public:
	VOrientationGridPart();

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;

private:
	void SendParallelLineVertices(int min, int max, float distance) const;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VORIENTATIONGRIDPART_2005_10_15_H
