#include <V3d/Physics/VJointHinge2LinkAncestorBodyPart.h>
#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;

VJointHinge2LinkAncestorBodyPart::VJointHinge2LinkAncestorBodyPart() : 
	m_pJointHinge2(VPartDependency::Neighbour, RegisterTo()),
	m_pBodyPart(VPartDependency::Ancestor, RegisterTo())
{
}

void VJointHinge2LinkAncestorBodyPart::Activate()
{
	if( m_pJointHinge2.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part JointHinge2 'data'");

	if( m_pBodyPart.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part body 'data'");

	m_pJointHinge2.Get()->RegisterBody(m_pBodyPart.Get()->GetBody().Get());
	
}

void VJointHinge2LinkAncestorBodyPart::Deactivate()
{
	m_pJointHinge2.Get()->UnregisterBody(m_pBodyPart.Get()->GetBody().Get());
}

void VJointHinge2LinkAncestorBodyPart::OnMessage(
							   const messaging::VMessage& in_Message,
							   messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;
}

V3D_REGISTER_PART_PARSER(VJointHinge2LinkAncestorBodyPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------
