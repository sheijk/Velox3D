#include <v3dLib/Physics/VPhysicBoxMassState.h>
#include <v3dLib/Physics/VPhysicBody.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VPhysicBoxMassState::VPhysicBoxMassState() : VPhysicMass()
{
	m_fHeight	= 1.0f;
	m_fWidth	= 1.0f;
	m_fLength	= 1.0f;
}

VPhysicBoxMassState::~VPhysicBoxMassState()
{
}

void VPhysicBoxMassState::Apply()
{
	dMassSetBox (&m_Mass, GetDensity(), m_fLength , m_fWidth ,m_fHeight);
	dMassAdjust (&m_Mass, GetMass());

	VPhysicBody* obj = static_cast<VPhysicBody*>(GetParent());

	V3D_ASSERT(obj != 0);

	dBodySetMass (*obj->GetBodyID(),&m_Mass);
}

void VPhysicBoxMassState::SetLength(vfloat32 in_fLength)
{
	m_fLength = in_fLength;
}

void VPhysicBoxMassState::SetWidth(vfloat32 in_fWidth)
{
	m_fWidth = in_fWidth;
	//UpdateState();
}

void VPhysicBoxMassState::SetHeigth(vfloat32 in_fHeight)
{
	m_fHeight = in_fHeight;
	//UpdateState();
}

vfloat32 VPhysicBoxMassState::GetHeight()
{
	return m_fHeight;
}

vfloat32 VPhysicBoxMassState::GetLength()
{
	return m_fLength;
}

vfloat32 VPhysicBoxMassState::GetWidth()
{
	return m_fWidth;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

