/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VLIGHTPART_2006_01_21_H
#define V3D_VLIGHTPART_2006_01_21_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Scene/IVLightManager.h>
#include <V3d/Graphics/VLight.h>
#include <V3d/Entity/VUpdateablePart.h>
#include <V3d/Entity/VRigidBodyPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * An entity part which holds a light. Will register itself to it's ancestor
 * IVLightManager.
 *
 * @author sheijk
 */
class VLightPart : public entity::VPartBaseAdapter<entity::IVUpdateablePart>
{
public:
	VLightPart();

	graphics::VLight& Light();

	virtual void Update(vfloat32 in_Seconds);

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual void OnActivate();
	virtual void OnDeactivate();

	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

private:
	graphics::VLight m_Light;
	entity::VPartConnection<IVLightManager> m_LightManager;
	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBody;
	entity::VPartConnection<entity::VUpdateManagerPart> m_pUpdateManager;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VLightPart, v3d::entity::IVUpdateablePart);
//-----------------------------------------------------------------------------
#endif // V3D_VLIGHTPART_2006_01_21_H

