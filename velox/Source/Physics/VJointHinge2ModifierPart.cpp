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
	m_pButton = 0;
	m_pButton2 = 0;
	m_pButton3 = 0;
	m_pButton4 = 0;
	m_pButton5 = 0;
	m_fSpeed = 0.0f;
	m_fSteering = 0.0f;
	m_fSpeedFactor = 5.0f;
	m_fSteerFactor = 0.2f;
	m_fAccel = 0;
	m_fMaxAccel = 1000.0f;
	m_fMaxSteer = 0.5f;
	m_fMaxSpeed = 1000.0f;
}

void VJointHinge2ModifierPart::Activate()
{
	if( m_pPhysicManagerPart.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part phyic manager");
	if( m_pInputManager.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part VInputPart");

	if(m_pInputManager->GetInputManager())
	{
		m_pButton = &m_pInputManager->GetInputManager()->GetStandardKey(KeyUp);
		m_pButton2 = &m_pInputManager->GetInputManager()->GetStandardKey(KeyDown);
		m_pButton3 = &m_pInputManager->GetInputManager()->GetStandardKey(KeyLeft);
		m_pButton4 = &m_pInputManager->GetInputManager()->GetStandardKey(KeyRight);
		m_pButton5 = &m_pInputManager->GetInputManager()->GetStandardKey(KeySpace);
		m_pButton6 = &m_pInputManager->GetInputManager()->GetStandardKey(KeyA);
		m_pButton7 = &m_pInputManager->GetInputManager()->GetStandardKey(KeyZ);
	}
	
	m_pUpdateManager->Register(this);
}

void VJointHinge2ModifierPart::Deactivate()
{
	m_pUpdateManager->Unregister(this);
}

bool VJointHinge2ModifierPart::GetButtons()
{
  bool pushed = false;
 if(m_pButton2)
 {
 	if(m_pButton2->IsDown())
 	{
	  m_fSpeed = m_fMaxSpeed;
	  m_fAccel = m_fMaxAccel;
	  pushed = true;
  	}
	if( ! pushed )
	{
	  m_fAccel = 0;
	  m_fSpeed = 0;
	}
  }

  if(m_pButton)
  {
  	if(m_pButton->IsDown())
  	{
	  m_fSpeed = m_fMaxSpeed;
	  m_fAccel = -m_fMaxAccel;
	  pushed = true;
   	}
	if( ! pushed )
	{
	  m_fSpeed = 0;
	  m_fAccel = 0;
	}
  }
  bool bIsSteered = false;

  if(m_pButton3)
  {
  	if(m_pButton3->IsDown())
  	{
	  bIsSteered = true;
  		m_fSteering -= m_fSteerFactor;
		if(m_fSteering < -m_fMaxSteer )
		  m_fSteering = - m_fMaxSteer;
   	}
  }

  if(m_pButton4)
  {
	if(m_pButton4->IsDown())
  	{
	  bIsSteered = true;
  		m_fSteering += m_fSteerFactor;
		if(m_fSteering > m_fMaxSteer )
		  m_fSteering =  m_fMaxSteer;
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

  /*if(m_pButton6)
  {
	if(m_pButton6->IsDown())
	{
	  if(m_fAccel > 0)
	  {
		m_fAccel = 0;
	  }
	  m_fAccel -=m_fSpeedFactor;
	}
  }
  if(m_pButton7)
  {
	if(m_pButton7->IsDown())
	{
	  if(m_fAccel < 0)
	  {
		m_fAccel = 0;
	  }
	  m_fAccel +=m_fSpeedFactor;
	}
  }*/

  return bIsSteered;
}

void VJointHinge2ModifierPart::Update(vfloat32 in_fSeconds)
{
  //get the joints we are looking for
  for(vuint i = 0; i < 4 ; i++)
  {
	m_pJoint[i] = m_pPhysicManagerPart->GetPhysicManager()->GetJointByName(m_sJointName[i]);
  }
  
  if( ! GetButtons() )
  {
	//get the wheels back to 0
	if( m_fSteering > 0)
	{
	  if(m_fSteering < 0.1)
		m_fSteering = 0;
	  else
	  {
    	  m_fSteering -= in_fSeconds;
	  }
	}
	else
	{
	  if(m_fSteering > -.1)
	  {
		m_fSteering = 0;
	  }
	  else
	  {
	  	  m_fSteering +=in_fSeconds;
	  }
	}

	/*if(m_fAccel > 0)
	{
	  m_fAccel-= in_fSeconds*10;
	  if(m_fAccel < 0)
		m_fAccel = 0;
	}
	else
	{
	  m_fAccel += in_fSeconds*10;
	  if(m_fAccel > 0)
		m_fAccel = 0;
	}*/

  }
  
  if(m_pJoint[0] && m_pJoint[1])
  {
	Accel(m_fSpeed, m_fAccel);
	Steer(m_fSteering);
	//vout << "Speed: " << m_fSpeed << "Accel: " << m_fAccel << "Steer: " << m_fSteering << vendl;
  }
  else
  {
	//vout << "physics modifier: could not find requested joints" << vendl;
  }
	//TODO: ugly test code; clean up

	
}

void VJointHinge2ModifierPart::Steer(float in_fSteer)
{
  //float leftAdjust = (in_fSpeed > 0 ? in_fSpeed : in_fSpeed * 1.2);
  //float rightAdjust = (in_fSpeed < 0 ? in_fSpeed : in_fSpeed * 1.2);

  float v[2];
  v[0] = (in_fSteer > 0 ? in_fSteer : in_fSteer * 1.2f);
  v[1] = (in_fSteer < 0 ? in_fSteer : in_fSteer * 1.2f);
  
  for(vuint i = 0; i < 2; i++)
  {
	m_pJoint[i]->SetLowStop(v[i]);
	m_pJoint[i]->SetLowStop(v[i]); // do this twice; ode may have trouble
	m_pJoint[i]->SetHighStop(v[i]);
	//m_pJoint[i]->SetVelocity(v[i]);
	float s = in_fSteer - m_pJoint[i]->GetAnchorAngle1();
	m_pJoint[i]->SetVelocity(s);
	m_pJoint[i+1]->SetVelocity(s);
	m_pJoint[i+2]->SetVelocity(s);
	//m_pJoint[i]->SetFudgeFactor(0.1f);
	//m_pJoint[i]->SetMaxForce(10.0);
  }
  //float s = in_fSteer - dJointGetHinge2Angle1 (joint[0]);

  //vfloat32 v1 = in_fSteer - pJoint1->GetAnchorAngle1();
  //if (v1 > 0.1) v1 = 0.1;
  //if (v1 < -0.1) v1 = -0.1;
  //v1 *= 10.0;
  //pJoint1->SetVelocity(v1);
  /*pJoint1->SetLowStop(-0.65f);
  pJoint1->SetHighStop(0.65f);
  pJoint1->SetMaxForce(10.5f);*/
  //vfloat32 v2 = in_fSteer - pJoint2->GetAnchorAngle1();
  //if (v2 > 0.1) v2 = 0.1;
  //if (v2 < -0.1) v2 = -0.1;
  //v2 *= 10.0;
  
  //pJoint2->SetVelocity(v2);
  /*pJoint2->SetLowStop(-0.65f);
  pJoint2->SetHighStop(0.65f);
  pJoint2->SetMaxForce(10.5f);*/
}

void VJointHinge2ModifierPart::Accel(float in_fSpeed, float in_fAccel)
{
  for(vuint i = 0; i < 4; i++)
  {
	m_pJoint[i]->SetVelocity2(in_fAccel);
	m_pJoint[i]->SetMaxForce2(in_fSpeed);
  }

  /*m_pJoint[0]->SetVelocity2(in_fAccel);
  m_pJoint[1]->SetVelocity2(in_fAccel);
  m_pJoint[2]->SetVelocity2(in_fAccel);
  m_pJoint[3]->SetVelocity2(in_fAccel);*/

  //m_pJoint[0]->SetVelocity2(in_fSpeed);
  //m_pJoint[1]->SetVelocity2(in_fSpeed);
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
	  in_pAnswer->AddProperty("Speed", m_fSpeedFactor);
	  in_pAnswer->AddProperty("Steer", m_fSteerFactor);
	  in_pAnswer->AddProperty("MaxSpeed", m_fMaxSpeed);
	  in_pAnswer->AddProperty("Accel", m_fMaxAccel);
	  in_pAnswer->AddProperty("ControlJoint1", m_sJointName[0]);
	  in_pAnswer->AddProperty("ControlJoint2", m_sJointName[1]);
	  in_pAnswer->AddProperty("ControlJoint3", m_sJointName[2]);
	  in_pAnswer->AddProperty("ControlJoint4", m_sJointName[3]);
	}
  }
  else if( request == "update" )
  {
	const string name = in_Message.GetAs<string>("name");

	if( name == "Speed" )
	{
	  //update button event
	  vfloat32 speed = in_Message.GetAs<vfloat32>("value");
	//  m_fSpeedFactor = speed;
	}

	if( name == "Steer" )
	{
	  //update button event
	  vfloat32 steer = in_Message.GetAs<vfloat32>("value");
	  //m_fSteerFactor = steer;
	}

	if( name == "MaxSpeed" )
	{
	  //update button event
	  vfloat32 maxSpeed = in_Message.GetAs<vfloat32>("value");
	  m_fMaxSpeed = maxSpeed;
	}

	if( name == "Accel" )
	{
	  //update button event
	  vfloat32 acc = in_Message.GetAs<vfloat32>("value");
	  m_fMaxAccel = acc;
	}


	if( name == "ControlJoint1" )
	{
	  m_sJointName[0] = in_Message.GetAs<std::string>("value");
	}
	if( name == "ControlJoint2" )
	{
	  m_sJointName[1] = in_Message.GetAs<std::string>("value");
	}

	if( name == "ControlJoint3" )
	{
	  m_sJointName[2] = in_Message.GetAs<std::string>("value");
	}
	if(name == "ControlJoint4" )
	{
	  m_sJointName[3] = in_Message.GetAs<std::string>("value");
	}
  }
}

V3D_REGISTER_PART_PARSER(VJointHinge2ModifierPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------

