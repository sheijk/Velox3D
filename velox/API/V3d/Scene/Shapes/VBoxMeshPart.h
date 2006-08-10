#ifndef V3D_VBOXMESHPART_2006_02_23_H
#define V3D_VBOXMESHPART_2006_02_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Scene/VMeshPartBase.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <V3d/Math/VBoundingBox.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Renders a bounding box mesh
 * @author ins
 */
class VBoxMeshPart : public VMeshPartBase
{
public:
	VBoxMeshPart();
	VBoxMeshPart(const graphics::VColor4f& in_Color);
	VBoxMeshPart(const math::VBoundingBox& in_BoundingBox);
	VBoxMeshPart(
		const math::VBoundingBox& in_BoundingBox,
		const graphics::VColor4f& in_Color);

	void SetColor(const graphics::VColor4f& in_Color);
	void SetBoundingBox(const math::VBoundingBox& in_BoungingBox);
	
	void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:

	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	graphics::VColor4f m_Color;
	math::VBoundingBox m_BoundingBox;
	vbool m_bWireFrame;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VBoxMeshPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VBOXMESHPART_2006_02_23_H
