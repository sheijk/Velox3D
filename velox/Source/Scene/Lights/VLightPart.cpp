#include <V3d/Scene/Lights/VLightPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

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
}

namespace {
	entity::VPartParser<VLightPart> g_LightPartParser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
