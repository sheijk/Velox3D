/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VJointHinge2ModifierPart.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Input/IVInputManager.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;
using namespace v3d::input;

VJointHinge2ModifierPart::VJointHinge2ModifierPart() : 
	m_pJointHinge2(VPartDependency::Neighbour, RegisterTo()),
	m_pInputManager(VPartDependency::Ancestor, RegisterTo()),
	m_pUpdateManager(VPartDependency::Ancestor, RegisterTo())
{
	m_ListeningEvent = KeyUp;
	m_ListeningEvent2 = KeyDown;

	m_pButton = 0;
	m_pButton2 = 0;
	m_pButton3 = 0;
	m_pButton4 = 0;
	m_pButton5 = 0;
	m_fSpeed = 0.0f;
	m_fSteering = 0.0f;
	m_fSpeedFactor = 0.5f;
	m_fSteerFactor = 0.5f;
	m_fMaxSpeed = 200;
		
}

void VJointHinge2ModifierPart::Activate()
{
	if( m_pJointHinge2.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part VJointHinge2");
	if( m_pInputManager.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part VInputPart");

	if(m_pInputManager->GetInputManager())
	{
		m_pButton = &m_pInputManager->GetInputManager()->GetStandardKey(m_ListeningEvent);
		m_pButton2 = &m_pInputManager->GetInputManager()->GetStandardKey(m_ListeningEvent2);
		m_pButton3 = &m_pInputManager->GetInputManager()->GetStandardKey(KeyLeft);
		m_pButton4 = &m_pInputManager->GetInputManager()->GetStandardKey(KeyRight);
		m_pButton5 = &m_pInputManager->GetInputManager()->GetStandardKey(KeySpace);
	}
	
	m_pUpdateManager->Register(this);
}

void VJointHinge2ModifierPart::Deactivate()
{
	m_pUpdateManager->Unregister(this);
}

void VJointHinge2ModifierPart::OnMessage(
							   const messaging::VMessage& in_Message,
							   messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer != 0 )
		{
			in_pAnswer->AddProperty("KeyEvent", m_ListeningEvent);
			in_pAnswer->AddProperty("Speed", m_fSpeedFactor);
			in_pAnswer->AddProperty("Steer", m_fSteerFactor);
			in_pAnswer->AddProperty("MaxSpeed", m_fMaxSpeed);

		}
	}
	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");

		if( name == "Speed" )
		{
			//update button event
			vfloat32 speed = in_Message.GetAs<vfloat32>("value");
			m_fSpeedFactor = speed;
		}

		if( name == "Steer" )
		{
			//update button event
			vfloat32 steer = in_Message.GetAs<vfloat32>("value");
			m_fSteerFactor = steer;
		}

		if( name == "MaxSpeed" )
		{
			//update button event
			vfloat32 maxSpeed = in_Message.GetAs<vfloat32>("value");
			m_fMaxSpeed = maxSpeed;
		}

		//type cast crashes
		//if( name == "KeyEvent" )
		//{
		//	//update button event
		//	vuint number = in_Message.GetAs<vuint>("value");
		//	m_ListeningEvent = static_cast<VKeyCode>(number);
		//	
		//	m_pButton = &m_pInputManager->GetInputManager()->GetStandardKey(m_ListeningEvent);
		//}
	}
}

void VJointHinge2ModifierPart::Update(vfloat32 in_fSeconds)
{
	//TODO: ugly test code; clean up

	bool test = false;
	if(m_pButton)
	{
		if(m_pButton->IsDown())
		{
			m_fSpeed += m_fSpeedFactor;
			test = true;
		}
	}
	if(m_pButton2)
	{
		if(m_pButton2->IsDown())
		{
			m_fSpeed -= m_fSpeedFactor;
			test = true;
		}
	}

	if(m_pButton3)
	{
		if(m_pButton3->IsDown())
		{
			m_fSteering += m_fSteerFactor;
			test = true;
		}
	}

	if(m_pButton4)
	{
		if(m_pButton4->IsDown())
		{
			m_fSteering -= m_fSteerFactor;
			test = true;
		}
	}
	
	if(m_pButton5)
	{
		if(m_pButton5->IsDown())
		{
			m_fSpeed = 0;
			m_fSteering = 0;
			test = true;
		}
	}

	VJointHinge2* pJoint = &m_pJointHinge2->GetJointHinge2();
	vfloat32 angle = pJoint->GetAnchorAngle1();
	vfloat32 v = m_fSteering - angle;

	if (v > 0.1) v = 0.1;
	if (v < -0.1) v = -0.1;
	v *= m_fMaxSpeed;
	
	//if(test)
	//{
		pJoint->SetVelocity2(-m_fSpeed);
		pJoint->SetVelocity(v);
		pJoint->SetMaxForce(10.2f);
		pJoint->SetMaxForce2(10.1f);
		pJoint->SetFudgeFactor(0.1);
		pJoint->SetLowStop(-.75f);
		pJoint->SetHighStop(0.75f);
		
		//pJoint->SetMaxForce(0.1f);
		//pJoint->Apply();
		
		pJoint->SetParameters();
//	}
}

V3D_REGISTER_PART_PARSER(VJointHinge2ModifierPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------

