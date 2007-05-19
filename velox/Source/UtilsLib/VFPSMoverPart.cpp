/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Utils/VFPSMoverPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Math/VQuaternionOps.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Messaging/VMessageInterpreter.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::input;

/**
 * standard c'tor
 */
VFPSMoverPart::VFPSMoverPart() :
	m_pRigidBody(entity::VPartDependency::Neighbour, RegisterTo()),
	m_pUpdateManager(entity::VPartDependency::Ancestor, RegisterTo()),
	m_pInputPart(entity::VPartDependency::Ancestor, RegisterTo())
{
	m_bIgnoreMouse = false;

	m_fMovementSpeed = 2.0f;
	m_fRotationSpeedX = 1.0f;
	m_fRotationSpeedY = 1.0f;
	m_fRotationSpeedZ = -10.0f;
	m_fKeyRotationFactor = 50.0f;
}

/**
 * d'tor
 */
VFPSMoverPart::~VFPSMoverPart()
{
}

void VFPSMoverPart::Update(vfloat32 in_fSeconds)
{
	if( m_pFastTriggerButton->IsDown() == true )
		in_fSeconds *= 4;

	// strafing
	if(m_pForwardButton->IsDown() == true)
		 MoveForward(m_fMovementSpeed * in_fSeconds);

	if(m_pBackwardButton->IsDown() == true)
		 MoveForward(-m_fMovementSpeed* in_fSeconds);

	if(m_pLeftButton->IsDown() == true)
		 StrafeRight(-m_fMovementSpeed * in_fSeconds);

	if(m_pRightButton->IsDown() == true)
		 StrafeRight(m_fMovementSpeed * in_fSeconds);

	if(m_pUpButton->IsDown() == true)
		 MoveUp(m_fMovementSpeed * in_fSeconds);

	if(m_pDownButton->IsDown() == true)
		 MoveUp(-m_fMovementSpeed * in_fSeconds);

	// keyboard rotation
	if( m_pRotateLeftButton->IsDown() == true )
		 RotateY(-m_fRotationSpeedY * m_fKeyRotationFactor  * in_fSeconds);

	if( m_pRotateRightButton->IsDown() == true )
		 RotateY(m_fRotationSpeedY * m_fKeyRotationFactor * in_fSeconds);

	if( m_pRotateUpButton->IsDown() == true )
		 RotateX(-m_fRotationSpeedX * m_fKeyRotationFactor  * in_fSeconds);

	if( m_pRotateDownButton->IsDown() == true )
		 RotateX(m_fRotationSpeedX * m_fKeyRotationFactor  * in_fSeconds);

	vbool rollRight = false;
	vbool rollLeft = false;

	if( ! m_bIgnoreMouse )
	{
		if( m_pRollRightButton->IsDown() )
			rollRight = true;
		if( m_pRollLeftButton->IsDown() )
			rollLeft = true;

		 RotateX(- m_pMouseYAxis->GetLastMovement() * m_fRotationSpeedX * in_fSeconds);
		 RotateY(m_pMouseXAxis->GetLastMovement() * m_fRotationSpeedY * in_fSeconds);
	}

	if( m_pRollRightButton2->IsDown() )
		rollRight = true;
	if( m_pRollLeftButton2->IsDown() )
		rollLeft = true;

	if( rollRight )
		 RotateZ(-m_fRotationSpeedZ * in_fSeconds);

	if( rollLeft )
		 RotateZ(m_fRotationSpeedZ * in_fSeconds);
}

void VFPSMoverPart::OnActivate()
{
	if( m_pInputPart->GetInputManager() != 0 )
	{
		m_pUpdateManager->Register(this);
		QueryButtons(*m_pInputPart->GetInputManager());
	}
}

void VFPSMoverPart::OnDeactivate()
{
	m_pUpdateManager->Unregister(this);
}

void VFPSMoverPart::MoveBy(const math::VVector3f& in_Distance)
{
	m_pRigidBody->SetPosition(m_pRigidBody->GetPosition() + in_Distance);
}

void VFPSMoverPart::MoveForward(vfloat32 in_fDistance)
{
	math::VVector3f movement = m_pRigidBody->GetTransform().GetZAxis() * (- in_fDistance);
	MoveBy(movement);
}

void VFPSMoverPart::StrafeRight(vfloat32 in_fDistance)
{
	math::VVector3f movement = m_pRigidBody->GetTransform().GetXAxis() * in_fDistance;
	MoveBy(movement);
}

void VFPSMoverPart::MoveUp(vfloat32 in_fDistance)
{
	math::VVector3f movement = m_pRigidBody->GetTransform().GetYAxis() * in_fDistance;
	MoveBy(movement);
}

void VFPSMoverPart::RotateAround(const math::VVector3f& in_Axis, vfloat32 in_fAngle)
{
	math::VRBTransform transform = m_pRigidBody->GetTransform();
	math::VVector3f view = - transform.GetZAxis();
	math::VVector3f up = transform.GetYAxis();

	math::VQuatf rot = QuatFromAxisAngle(in_Axis, in_fAngle);
	math::Rotate(view, rot);
	math::Rotate(up, rot);

	transform.SetDirection(view, up);

	m_pRigidBody->SetTransform(transform);
}

void VFPSMoverPart::RotateX(vfloat32 in_fAngleDegree)
{
	RotateAround(m_pRigidBody->GetTransform().GetXAxis(), in_fAngleDegree);
}

void VFPSMoverPart::RotateY(vfloat32 in_fAngleDegree)
{
	RotateAround(m_pRigidBody->GetTransform().GetYAxis(), in_fAngleDegree);
}

void VFPSMoverPart::RotateZ(vfloat32 in_fAngleDegree)
{
	RotateAround(m_pRigidBody->GetTransform().GetZAxis(), in_fAngleDegree);
}

void VFPSMoverPart::QueryButtons(IVInputManager& in_InputManager)
{
	m_pForwardButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyW);
	m_pBackwardButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyS);
	m_pLeftButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyA);
	m_pRightButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyD);
	m_pUpButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyR);
	m_pDownButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyF);

	m_pRotateLeftButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyLeft);
	m_pRotateRightButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyRight);
	m_pRotateUpButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyUp);
	m_pRotateDownButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyDown);

	m_pRollLeftButton2 = &in_InputManager.GetStandardKeyboard().GetKey(KeyQ);
	m_pRollRightButton2 = &in_InputManager.GetStandardKeyboard().GetKey(KeyE);

	m_pRollLeftButton = &in_InputManager.GetStandardMouse().GetLeftButton();
	m_pRollRightButton = &in_InputManager.GetStandardMouse().GetRightButton();
	m_pMouseXAxis = &in_InputManager.GetStandardMouse().GetXAxis();
	m_pMouseYAxis = &in_InputManager.GetStandardMouse().GetYAxis();

	m_pFastTriggerButton = &in_InputManager.GetStandardKeyboard().GetKey(KeyLeftShift);
}

void VFPSMoverPart::OnMessage(
  const messaging::VMessage& in_Message, 
  messaging::VMessage* in_pAnswer)
{
	using namespace messaging;

	static VMessageInterpreter interpreter;

	if( ! interpreter.IsInitialized() )
	{
		interpreter.SetInitialized(true);
		interpreter.AddMemberOption("ignore-mouse", this, &m_bIgnoreMouse);
	}

	interpreter.HandleMessage(this, in_Message, in_pAnswer);
}


V3D_REGISTER_PART_PARSER(VFPSMoverPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------

