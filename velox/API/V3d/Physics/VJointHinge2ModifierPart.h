/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VJOINTHINGE2MODIFIERPART_2006_06_05_H
#define V3D_VJOINTHINGE2MODIFIERPART_2006_06_05_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Physics/VJointHinge2Part.h>
#include <V3d/Input/VKeyCode.h>
#include <V3d/Input/IVButton.h>
#include <V3d/Utils/VInputPart.h>
#include <V3d/Entity.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------

class VJointHinge2ModifierPart : public entity::IVUpdateablePart
{
public:
	
	VJointHinge2ModifierPart();
	
	void Update(vfloat32 in_fSeconds);
	
	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

private:
	virtual void OnActivate();
	virtual void OnDeactivate();

	virtual void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer);

	entity::VNodeConnection<physics::VPhysicManagerPart> m_pPhysicManagerPart;
	entity::VNodeConnection<utils::VInputPart> m_pInputManager;
	entity::VNodeConnection<entity::VUpdateManagerPart> m_pUpdateManager;

	void Steer(float in_fSteer);
	bool GetButtons(vfloat32 in_fSeconds);
	void Accel(float in_fSpeed, float in_fAccel);
	vbool AreValidJoints();
	input::IVButton* m_pButton;
	input::IVButton* m_pButton2;
	input::IVButton* m_pButton3;
	input::IVButton* m_pButton4;
	input::IVButton* m_pButton5;
	input::IVButton* m_pButton6;
	input::IVButton* m_pButton7;

	vfloat32 m_fSpeedFactor;
	vfloat32 m_fSteerFactor;

	vfloat32 m_fSteering;
	vfloat32 m_fSpeed;
	vfloat32 m_fMaxSpeed;
	vfloat32 m_fAccel;
	vfloat32 m_fMaxSteer;
	vfloat32 m_fMaxAccel;
	std::string m_sJointName[4];
	VJointHinge2* m_pJoint[4];
};

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
V3D_TYPEINFO_WITHPARENT(v3d::physics::VJointHinge2ModifierPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif //V3D_VJOINTHINGE2MODIFIERPART_2006_06_05_H
