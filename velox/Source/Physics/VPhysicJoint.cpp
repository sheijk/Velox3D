#include <v3dLib/Physics/VPhysicJoint.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VPhysicJoint::VPhysicJoint()
{
	m_pPhysicWorld		= 0;
	m_pJointGroup		= 0;
	m_JointID			= 0;

	m_fLowStop			= -dInfinity;
	m_fHighStop			= dInfinity;
    m_fVelocity			= 0.0f;
	m_fVelocity2		= 0.0f;
	m_fMaxForce			= 0.0f;
	m_fFudgeFactor		= 1.0f;
	m_fBounce			= 0.0f;
	m_fCFM				= (vfloat32)1.0000000e-010;
	m_fStopERP			= 0.2f;
	m_fStopCFM			= (vfloat32)1.0000000e-010;
	m_fSuspensionCFM	= 1.0f;
	m_fSuspensionERP	= 1.0f;
}

VPhysicJoint::~VPhysicJoint()
{
}

void VPhysicJoint::Destroy()
{
	dJointDestroy(m_JointID);
}

void VPhysicJoint::AddWorld(VPhysicWorld* in_pPhysicWorld)
{
	V3D_ASSERT(in_pPhysicWorld != 0);

	m_pPhysicWorld = in_pPhysicWorld;
	m_pJointGroup  = 0;
}
void VPhysicJoint::AddJointGroup(VPhysicJointGroup* in_pJointGroup)
{
	m_pJointGroup = in_pJointGroup;
}

void VPhysicJoint::SetLowStop(vfloat32 in_fLowStop)
{
	m_fLowStop = in_fLowStop;
}

vfloat32 VPhysicJoint::GetLowStop()
{
	return m_fLowStop;
}

void VPhysicJoint::SetHighStop(vfloat32 in_fHighStop)
{
	m_fHighStop = in_fHighStop;
}

vfloat32 VPhysicJoint::GetHighStop()
{
	return m_fHighStop;
}

void VPhysicJoint::SetVelocity(vfloat32 in_fVelocity)
{
	m_fVelocity = in_fVelocity;
}

vfloat32 VPhysicJoint::GetVelocity()
{
	return m_fVelocity;
}

void VPhysicJoint::SetMaxForce(vfloat32 in_fMaxForce)
{
	m_fMaxForce = in_fMaxForce;
}

vfloat32 VPhysicJoint::GetMaxForce()
{
	return m_fMaxForce;
}

void VPhysicJoint::SetFudgeFactor(vfloat32 in_fFudgeFactor)
{
	m_fFudgeFactor = in_fFudgeFactor;
}

vfloat32 VPhysicJoint::GetFudgeFactor()
{
	return m_fFudgeFactor;
}

void VPhysicJoint::SetBounce(vfloat32 in_fBounce)
{
	m_fBounce = in_fBounce;
}

vfloat32 VPhysicJoint::GetBounce()
{
	return m_fBounce;
}

void VPhysicJoint::SetCFM(vfloat32 in_fCFM)
{
	m_fCFM = in_fCFM;
}

vfloat32 VPhysicJoint::GetCFM()
{
	return m_fCFM;
}

void VPhysicJoint::SetStopCFM(vfloat32 in_fStopCFM)
{
	m_fStopCFM = in_fStopCFM;
}

vfloat32 VPhysicJoint::GetStopCFM()
{
	return m_fStopCFM;
}

void VPhysicJoint::SetStopERP(vfloat32 in_fStopERP)
{
	m_fStopERP = in_fStopERP;
}

vfloat32 VPhysicJoint::GetStopERP()
{
	return m_fStopERP;
}

void VPhysicJoint::SetSuspensionERP(vfloat32 in_fSuspensionERP)
{
	m_fSuspensionERP = in_fSuspensionERP;
}

vfloat32 VPhysicJoint::GetSuspensionERP()
{
	return m_fSuspensionERP;
}

void VPhysicJoint::SetSuspensionCFM(vfloat32 in_fSuspensionCFM)
{
	m_fSuspensionCFM = in_fSuspensionCFM;
}
vfloat32 VPhysicJoint::GetSuspensionCFM()
{
	return m_fSuspensionCFM;
}

void VPhysicJoint::SetVelocity2(vfloat32 in_fVelocity2)
{
	m_fVelocity2 = in_fVelocity2;
}

vfloat32 VPhysicJoint::GetVelocity2()
{
	return m_fVelocity2;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

