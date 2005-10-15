#ifndef V3D_VARROWMESHPART_2005_10_15_H
#define V3D_VARROWMESHPART_2005_10_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/VMeshPartBase.h>
#include <V3dLib/Graphics/Geometry/VColor4f.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Renders an arrow oriented along the z-axis with it's tip at z=1.
 * Can be used to show the orientation of a VRBTransform, will point along
 * view direction
 *
 * @author sheijk
 */
class VArrowMeshPart : public VMeshPartBase
{
public:
	VArrowMeshPart(const graphics::VColor4f& in_Color);

	void SetColor(const graphics::VColor4f& in_Color);
	void SendGeometry(graphics::IVDevice& in_Device) const;

private:
	graphics::VColor4f m_Color;

	static void sendCircleVertices(vfloat32 z1);

	static void sendCircleVertices(vfloat32 z1, vfloat32 z2);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VARROWMESHPART_2005_10_15_H
