/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual void OnActivate();
	virtual void OnDeactivate();

	virtual graphics::IVDevice* GetRenderTarget();
	virtual graphics::IVCamera* GetCamera();
	virtual scene::IVGraphicsPart* GetScene();

	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

private:
	std::string GetRenderTargetResource() const;

	resource::VResourceDataPtr<graphics::IVDevice> m_pRenderTarget;

	entity::VNodeConnection<VSimpleShooting> m_pMainShooting;
	entity::VNodeConnection<entity::VRigidBodyPart> m_pRigidBodyPart;
	graphics::VCamera m_Camera;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VOffscreenShooting, v3d::scene::VShootingBase);
//-----------------------------------------------------------------------------
#endif // V3D_VOFFSCREENSHOOTING_2006_05_12_H

