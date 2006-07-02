#include <V3dLib/Utils/VCircleMoverPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Messaging/VMessageInterpreter.h>
#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VCircleMoverPart::VCircleMoverPart() :
	m_pRigidBody(entity::VPartDependency::Neighbour, RegisterTo()),
	m_pUpdateManager(entity::VPartDependency::Ancestor, RegisterTo())
{
	m_fSpeed = math::Pi() * 1;
	m_fAngle = .0f;
	m_fRadius = 10.0f;
}

void VCircleMoverPart::Update(vfloat32 in_fSeconds)
{
	m_fAngle += in_fSeconds * m_fSpeed;
	VVector3f newPos(sin(m_fAngle), 0, cos(m_fAngle));
	newPos *= m_fRadius;
	newPos += m_Center;
	VVector3f dir(newPos.GetZ(), 0.0f, -newPos.GetX());

	math::VRBTransform transform;
	transform.SetPosition(newPos);
	transform.SetDirection(dir, VVector3f(0.0f, 1.0f, 0.0f));

	m_pRigidBody->SetTransform(transform);
	//m_pRigidBody->SetPosition(newPos);
	//m_pRigidBody->
}

void VCircleMoverPart::Activate()
{
	m_pUpdateManager->Register(this);
}

void VCircleMoverPart::Deactivate()
{
	m_pUpdateManager->Unregister(this);
}

void VCircleMoverPart::OnMessage(
	const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	static messaging::VMessageInterpreter interpreter;
	if( ! interpreter.IsInitialized() )
	{
		interpreter.AddMemberOption("radius", this, &m_fRadius);
		interpreter.AddMemberOption("center", this, &m_Center);
		interpreter.AddMemberOption("speed", this, &m_fSpeed);
		interpreter.AddMemberOption("angle", this, &m_fAngle);
	}

	interpreter.HandleMessage(this, in_Message, in_pAnswer);
}

namespace {
	entity::VPartParser<VCircleMoverPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
