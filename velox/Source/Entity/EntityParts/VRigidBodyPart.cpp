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
	m_Transformation.GetXAxis() = VVector3f(1.0f, 0.0f, 0.0f);
	m_Transformation.GetYAxis() = VVector3f(0.0f, 1.0f, 0.0f);
	m_Transformation.GetZAxis() = VVector3f(0.0f, 0.0f, 1.0f);
	m_Transformation.SetPosition(VVector3f(0.0f, 0.0f, 0.0f));
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

void VRigidBodyPart::SetTransform(const math::VRBTransform& in_Trans)
{
	m_Transformation = in_Trans;
}


math::VRBTransform VRigidBodyPart::GetTransform()
{
	return m_Transformation;
}

utils::VFourCC VRigidBodyPart::GetDefaultId()
{
	return utils::VFourCC("body");
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
