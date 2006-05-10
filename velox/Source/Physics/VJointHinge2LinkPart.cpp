#include <V3d/Physics/VJointHinge2LinkPart.h>
#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;

VJointHinge2LinkPart::VJointHinge2LinkPart() : 
	m_pJointHinge2(VPartDependency::Ancestor, RegisterTo()),
	m_pBodyPart(VPartDependency::Neighbour, RegisterTo())
{
}

void VJointHinge2LinkPart::Activate()
{
	if( m_pJointHinge2.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part JointHinge2 'data'");
	
	if( m_pBodyPart.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part body 'data'");

	m_pJointHinge2.Get()->RegisterBody(m_pBodyPart.Get()->GetBody().Get());
	
}

void VJointHinge2LinkPart::Deactivate()
{
	m_pJointHinge2.Get()->UnregisterBody(m_pBodyPart.Get()->GetBody().Get());
}

void VJointHinge2LinkPart::OnMessage(
							   const messaging::VMessage& in_Message,
							   messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;
}

namespace {
	entity::VPartParser<VJointHinge2LinkPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------
