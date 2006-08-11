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
	m_LightManager(entity::VPartDependency::Ancestor, RegisterTo()),
	m_pRigidBody(entity::VPartDependency::Neighbour, RegisterTo()),
	m_pUpdateManager(entity::VPartDependency::Ancestor, RegisterTo())
{}

graphics::VLight& VLightPart::Light()
{
	return m_Light;
}

void VLightPart::Activate()
{
	if( m_LightManager.IsConnected() )
		m_LightManager->Add(this);

	m_pUpdateManager->Register(this);
}

void VLightPart::Deactivate()
{
	if( m_LightManager.IsConnected() )
		m_LightManager->Remove(this);

	m_pUpdateManager->Unregister(this);
}

void VLightPart::Update(vfloat32 in_fSeconds)
{
	m_Light.SetPosition(m_pRigidBody->GetPosition());

	if( m_Light.GetW() == .0f )
	{
		VVector3f pos = m_Light.GetPosition();
		VVector3f dir = Normalized(pos);
		m_Light.SetPosition(dir);
	}
}

void VLightPart::OnMessage(const messaging::VMessage& in_Message, 
	messaging::VMessage* in_pAnswer)
{
	static messaging::VMessageInterpreter interpreter;

	if( ! interpreter.IsInitialized() )
	{
        interpreter.AddMemberOption("ambientColor", this, &m_Light.ambientColor);
		interpreter.AddMemberOption("diffuseColor", this, &m_Light.diffuseColor);
		interpreter.AddMemberOption("specularColor", this, &m_Light.specularColor);
		interpreter.AddMemberOption("position", this, &m_Light.m_Position);
		interpreter.AddMemberOption("w", this, &m_Light.m_fW);

		interpreter.SetInitialized(true);
	}

	interpreter.HandleMessage(this, in_Message, in_pAnswer);
}

V3D_REGISTER_PART_PARSER(VLightPart);

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
