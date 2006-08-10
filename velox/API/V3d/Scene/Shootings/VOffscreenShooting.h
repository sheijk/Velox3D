#ifndef V3D_VOFFSCREENSHOOTING_2006_05_12_H
#define V3D_VOFFSCREENSHOOTING_2006_05_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Scene/VSimpleShooting.h>
#include <V3d/Graphics/Misc/VCamera.h>
#include <V3d/Entity/VRigidBodyPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Renders to a texture from the rigid body part's position
 *
 * @author sheijk
 */
class VOffscreenShooting : public VShootingBase
{
public:
	VOffscreenShooting();
	virtual ~VOffscreenShooting();

	void SetRenderTargetResource(const std::string& in_strResource);

	virtual void UpdateAndCull();

	void Activate();
	void Deactivate();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
protected:
	virtual graphics::IVDevice* GetRenderTarget();
	virtual graphics::IVCamera* GetCamera();
	virtual scene::IVGraphicsPart* GetScene();

private:
	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	resource::VResourceDataPtr<graphics::IVDevice> m_pRenderTarget;

	entity::VPartConnection<VSimpleShooting> m_pMainShooting;
	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBodyPart;
	graphics::VCamera m_Camera;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VOffscreenShooting, v3d::scene::VShootingBase);
//-----------------------------------------------------------------------------
#endif // V3D_VOFFSCREENSHOOTING_2006_05_12_H
