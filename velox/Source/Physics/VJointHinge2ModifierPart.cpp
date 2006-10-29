/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Core.h>
#include <V3d/Physics/VJointHinge2ModifierPart.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Input/IVInputManager.h>
#include <V3d/Physics/VPhysicManagerPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;
using namespace v3d::input;

VJointHinge2ModifierPart::VJointHinge2ModifierPart() : 
m_pPhysicManagerPart(VPartDependency::Ancestor, RegisterTo()),
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
	m_fSpeedFactor = 0.05f;
	m_fSteerFactor = 0.05f;
	m_sJoint1Identifer = "";
	m_sJoint2Identifer = "";
	m_fAccel = 30.0f;
		
}

void VJointHinge2ModifierPart::Activate()
{
	if( m_pPhysicManagerPart.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part phyic manager");
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
			in_pAnswer->AddProperty("ControlJoint1", m_sJoint1Identifer);
			in_pAnswer->AddProperty("ControlJoint2", m_sJoint2Identifer);
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
		if( name == "ControlJoint1" )
		{
		  m_sJoint1Identifer = in_Message.GetAs<std::string>("value");
		}
		if( name == "ControlJoint2" )
		{
		  m_sJoint2Identifer = in_Message.GetAs<std::string>("value");
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

void VJointHinge2ModifierPart::GetButtons()
{
 if(m_pButton)
 {
 	if(m_pButton->IsDown())
 	{
 		//m_fSpeed += m_fSpeedFactor;
	  m_fAccel+=m_fSpeedFactor;
  	}
  }
  if(m_pButton2)
  {
  	if(m_pButton2->IsDown())
  	{
  		//m_fSpeed -= m_fSpeedFactor;
		m_fAccel-=m_fSpeedFactor;
   	}
  }
  if(m_pButton3)
  {
  	if(m_pButton3->IsDown())
  	{
  		m_fSteering += m_fSteerFactor;
		//m_fSpeed -=1.0f;
   	}
  }

  if(m_pButton4)
  {
  	{
  		m_fSteering -= m_fSteerFactor;
		//m_fSpeed +=1.0f;
   	}
  }
  
  if(m_pButton5)
  {
  	if(m_pButton5->IsDown())
  	{
  		m_fSpeed = 0;
  		m_fSteering = 0;
		m_fAccel = 0;
   	}
  }
}

void VJointHinge2ModifierPart::Update(vfloat32 in_fSeconds)
{
  //get the joints we are looking for
  VJointHinge2* pJoint1 =  m_pPhysicManagerPart->GetPhysicManager()->GetJointByName(m_sJoint1Identifer);
  VJointHinge2* pJoint2 =  m_pPhysicManagerPart->GetPhysicManager()->GetJointByName(m_sJoint2Identifer);

  GetButtons();

  if(pJoint1 && pJoint2)
  {
	//Steer(m_fSteering, pJoint1, pJoint2);
	Accel(m_fMaxSpeed, m_fAccel, pJoint1, pJoint2);
	vout << "Speed: " << m_fMaxSpeed << "Accel: " << m_fAccel << vendl;
  }
  else
  {
	vout << "physics modifier: could not find requested joints" << vendl;
  }
	//TODO: ugly test code; clean up

	
}

void VJointHinge2ModifierPart::Steer(float in_fSpeed, VJointHinge2* pJoint1, VJointHinge2* pJoint2)
{
  float leftAdjust = (in_fSpeed > 0 ? in_fSpeed : in_fSpeed * 1.2);
  float rightAdjust = (in_fSpeed < 0 ? in_fSpeed : in_fSpeed * 1.2);

  pJoint1->SetLowStop(leftAdjust);
  pJoint1->SetHighStop(leftAdjust);
  //ode bug!? 
  pJoint1->SetLowStop(leftAdjust);
  pJoint1->SetHighStop(leftAdjust);

  pJoint2->SetLowStop(rightAdjust);
  pJoint2->SetHighStop(rightAdjust);
  //ode bug!? 
  pJoint2->SetLowStop(rightAdjust);
  pJoint2->SetHighStop(rightAdjust);

 /* pJoint1->Apply();
  pJoint2->Apply();*/
}

void VJointHinge2ModifierPart::Accel(float in_fSpeed, float in_fAccel, VJointHinge2* pJoint1, VJointHinge2* pJoint2 )
{
  /*if(in_fSpeed < 0 && m_fAccel > 0)
	m_fAccel *= -1;
  else
  {
	if(in_fSpeed > 0 && m_fAccel < 0)
	  m_fAccel *=-1;
  }*/
  
  pJoint1->SetMaxForce2(in_fSpeed);
  pJoint1->SetVelocity2(in_fAccel);
  pJoint2->SetVelocity2(in_fAccel);
  pJoint2->SetMaxForce2(in_fSpeed);


  //pJoint2->SetMaxForce(0.2);
  //pJoint2->SetMaxForce(0.2);



  /*dReal v = 0 - pJoint1->GetAnchorAngle1();
  if (v > 0.1) v = 0.1;
  if (v < -0.1) v = -0.1;
  v *= 10.0;*/

  //pJoint1->SetVelocity(v);
  //pJoint1->SetMaxForce(0.2);
  //pJoint1->SetFudgeFactor(0.1);
 
  //pJoint2->SetVelocity(v);
 // pJoint2->SetFudgeFactor(0.1);

 // dJointSetHinge2Param (joint[0],dParamVel,v);
 // dJointSetHinge2Param (joint[0],dParamFMax,0.2);
 // dJointSetHinge2Param (joint[0],dParamLoStop,-0.75);
//  dJointSetHinge2Param (joint[0],dParamHiStop,0.75);
  //dJointSetHinge2Param (joint[0],dParamFudgeFactor,0.1);
  
  /*pJoint1->Apply();
  pJoint2->Apply();*/
}

V3D_REGISTER_PART_PARSER(VJointHinge2ModifierPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------

