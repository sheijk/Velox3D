#include <V3d/Physics/VCollisionPart.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/Physics/VPhysicManagerPart.h>
#include <V3d/Physics/Bounding/IVBoundingVolumePart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;

VCollisionPart::VCollisionPart() : 
	m_pVolumePart(entity::VPartDependency::Neighbour, RegisterTo()),
	m_pPhysicManagerPart(entity::VPartDependency::Ancestor, RegisterTo())
{
	m_pGeometry.Assign(0);
	m_bActive = false;
}

void VCollisionPart::Activate()
{
	if( m_pVolumePart.Get() == 0 )
		V3D_THROW(entity::VMissingPartException, "missing part volume part 'data'");
	if( m_pPhysicManagerPart.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part physic manager 'data'");

	if( !m_bActive )
		Create();
}

void VCollisionPart::Deactivate()
{
	m_bActive = false;
	m_pGeometry->Destroy();
	m_pGeometry.Release();
}

void VCollisionPart::Create()
{
	m_pGeometry = m_pPhysicManagerPart->GetPhysicManager()->CreateGeom(m_pVolumePart.Get());
	m_bActive = true;
}

void VCollisionPart::OnMessage(
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
			in_pAnswer->AddProperty("Active", m_bActive);
		}
	}
}

namespace {
	entity::VPartParser<VCollisionPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------
