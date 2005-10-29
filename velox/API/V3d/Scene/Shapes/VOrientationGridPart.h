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

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:
	void SendParallelLineVertices(int min, int max, float distance) const;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VOrientationGridPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VORIENTATIONGRIDPART_2005_10_15_H
