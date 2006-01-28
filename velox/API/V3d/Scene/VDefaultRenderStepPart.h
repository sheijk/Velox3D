#ifndef V3D_VDEFAULTRENDERSTEPPART_2005_10_19_H
#define V3D_VDEFAULTRENDERSTEPPART_2005_10_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVRenderStepPart.h>
#include <V3dLib/Graphics/Geometry/VColor4f.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VDefaultRenderStepPart : public IVRenderStepPart
{
public:
	VDefaultRenderStepPart();
	virtual ~VDefaultRenderStepPart();

	virtual void Render(IVGraphicsPart* in_pScene);
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	graphics::VColor4f m_BackgroundColor;

	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VDefaultRenderStepPart, v3d::scene::IVRenderStepPart);
//-----------------------------------------------------------------------------
#endif // V3D_VDEFAULTRENDERSTEPPART_2005_10_19_H
