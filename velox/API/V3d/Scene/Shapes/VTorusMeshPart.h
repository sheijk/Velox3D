#ifndef V3D_VTORUSMESHPART_2006_01_20_H
#define V3D_VTORUSMESHPART_2006_01_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Scene/VMeshPartBase.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Renders a cylinder mesh
 * @author: ins
 */
class VTorusMeshPart : public VMeshPartBase
{
public:
	VTorusMeshPart();
	VTorusMeshPart(const graphics::VColor4f& in_Color);
	VTorusMeshPart(
		vfloat32 in_fTopRadius,
		vfloat32 in_fButtonRadius,
		vfloat32 in_fHeight,
		int in_iSlices,
		int in_iStacks);

	void SetColor(const graphics::VColor4f& in_Color);
	void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:
	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	graphics::VColor4f m_Color;

	static void sendCircleVertices(vfloat32 z1);

	static void sendCircleVertices(vfloat32 z1, vfloat32 z2, bool normals);

	vfloat32 m_fTopRadius;
	vfloat32 m_fButtonRadius;
	vfloat32 m_fHeight;
	int m_iSlices;
	int m_iStacks;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VTorusMeshPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VTORUSMESHPART_2005_10_15_H
