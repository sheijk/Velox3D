#include <v3dlib/EntityParts/VRigidBodyPart.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VRigidBodyPart::VRigidBodyPart()
{

}

void VRigidBodyPart::Activate()
{
}

void VRigidBodyPart::Deactivate()
{
}											 

VVector3f VRigidBodyPart::GetPosition() const
{
	return m_Transformation.GetPosition();
}

void VRigidBodyPart::SetPosition(const VVector3f& in_Position)
{
	m_Transformation.SetPosition(in_Position);
}

void VRigidBodyPart::SetTransform(const VRBTransform& in_Trans)
{
	m_Transformation = in_Trans;
}

VRBTransform VRigidBodyPart::GetTransform()
{
	return m_Transformation;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
