#include "VRigidBodyPart.h"
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

VRigidBodyPart::Vector VRigidBodyPart::GetPosition() const
{
	return m_Transformation.GetPosition();
}

void VRigidBodyPart::SetPosition(const Vector& in_Position)
{
	m_Transformation.SetPosition(in_Position);
}

void VRigidBodyPart::SetTransform(const VRBTransform& in_Trans)
{
	m_Transformation = in_Trans;
}

VRBTransform VRigidBodyPart::GetTransform() const
{
	return m_Transformation;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::racer
//-----------------------------------------------------------------------------
