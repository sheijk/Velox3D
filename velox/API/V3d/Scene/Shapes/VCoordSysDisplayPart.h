#ifndef V3D_VCOORDSYSDISPLAYPART_2005_10_15_H
#define V3D_VCOORDSYSDISPLAYPART_2005_10_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/VMeshPartBase.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Displays three lines showing the x,y,z axis using lines with length 1
 * x - red, y - green, z - blue
 *
 * @author sheijk
 */
class VCoordSysDisplayPart : public scene::VMeshPartBase
{
public:
	VCoordSysDisplayPart();

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VCoordSysDisplayPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VCOORDSYSDISPLAYPART_2005_10_15_H
