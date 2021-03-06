/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Lights/VLightPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Messaging/VMessageInterpreter.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Graphics/Geometry/Conversions.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

VLightPart::VLightPart() : 
	m_LightManager( RegisterTo()),
	m_pRigidBody(RegisterTo()),
	m_pUpdateManager(RegisterTo())
{}

graphics::VLight& VLightPart::Light()
{
	return m_Light;
}

void VLightPart::OnActivate()
{
	if( m_LightManager.IsConnected() )
		m_LightManager->Add(this);

	m_pUpdateManager->Register(this);
}

void VLightPart::OnDeactivate()
{
	if( m_LightManager.IsConnected() )
		m_LightManager->Remove(this);

	m_pUpdateManager->Unregister(this);
}

void VLightPart::Update(vfloat32 in_fSeconds)
{
//	m_Light.SetPosition(m_pRigidBody->GetPosition());
	m_Light.SetTransform(m_pRigidBody->GetTransform());

	if( m_Light.GetW() == .0f )
	{
		VVector3f pos = m_Light.GetPosition();
		VVector3f dir = Normalized(pos);
		m_Light.SetPosition(dir);
	}
}

messaging::VMessageInterpreter* VLightPart::GetMessageInterpreterForClass()
{
	static messaging::VMessageInterpreter interpreter;

	return &interpreter;
}

void VLightPart::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddMemberOption("ambientColor", this, &m_Light.ambientColor);
	interpreter.AddMemberOption("diffuseColor", this, &m_Light.diffuseColor);
	interpreter.AddMemberOption("specularColor", this, &m_Light.specularColor);
	interpreter.AddMemberOption("w", this, &m_Light.m_fW);

	IVUpdateablePart::SetupProperties( interpreter );
}

//void VLightPart::OnMessage(const messaging::VMessage& in_Message, 
//	messaging::VMessage* in_pAnswer)
//{
//	static messaging::VMessageInterpreter interpreter;
//
//	if( ! interpreter.IsInitialized() )
//	{
//        interpreter.AddMemberOption("ambientColor", this, &m_Light.ambientColor);
//		interpreter.AddMemberOption("diffuseColor", this, &m_Light.diffuseColor);
//		interpreter.AddMemberOption("specularColor", this, &m_Light.specularColor);
//		interpreter.AddMemberOption("w", this, &m_Light.m_fW);
//
//		interpreter.SetInitialized(true);
//	}
//
//	interpreter.HandleMessage(this, in_Message, in_pAnswer);
//}

V3D_REGISTER_PART_PARSER(VLightPart);

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

