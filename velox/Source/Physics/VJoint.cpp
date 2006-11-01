/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Physics/VJoint.h>
#include <limits>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VJoint::VJoint()
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
	m_fCFM				= (vfloat32)1.0000000e-05; //10^-10 for vfloat64
	//m_fCFM				= std::numeric_limits<float>::min();
	m_fStopERP			= 0.2f;
	m_fStopCFM			= (vfloat32)1.0000000e-05; //10^-10 for vfloat64
	//m_fStopCFM			= std::numeric_limits<float>::min();
	m_fSuspensionCFM	= 1.0f;
	m_fSuspensionERP	= 1.0f;
	m_bIsActive = false;
}

VJoint::~VJoint()
{
}

void VJoint::Destroy()
{
	dJointDestroy(m_JointID);
	m_bIsActive = false;
}
vbool VJoint::IsActive()
{
	return m_bIsActive;
}

void VJoint::AddWorld(VWorld* in_pPhysicWorld)
{
	V3D_ASSERT(in_pPhysicWorld != 0);

	m_pPhysicWorld = in_pPhysicWorld;
	m_pJointGroup  = 0;
}
void VJoint::AddJointGroup(VJointGroup* in_pJointGroup)
{
	m_pJointGroup = in_pJointGroup;
}

void VJoint::SetLowStop(vfloat32 in_fLowStop)
{
	m_fLowStop = in_fLowStop;
	if(m_JointID)
	  dJointSetHinge2Param( m_JointID, dParamLoStop, m_fLowStop);
}

vfloat32 VJoint::GetLowStop()
{
	return m_fLowStop;
}

void VJoint::SetHighStop(vfloat32 in_fHighStop)
{
	m_fHighStop = in_fHighStop;
	if(m_JointID)
	  dJointSetHinge2Param( m_JointID, dParamHiStop, m_fHighStop);
}

vfloat32 VJoint::GetHighStop()
{
	return m_fHighStop;
}

void VJoint::SetVelocity(vfloat32 in_fVelocity)
{
	m_fVelocity = in_fVelocity;
	if(m_JointID)
	  dJointSetHinge2Param (m_JointID, dParamVel, m_fVelocity);
}

vfloat32 VJoint::GetVelocity()
{
	return m_fVelocity;
}

void VJoint::SetMaxForce(vfloat32 in_fMaxForce)
{
  m_fMaxForce = in_fMaxForce;
  if(m_JointID) 
	dJointSetHinge2Param(m_JointID, dParamFMax, m_fMaxForce);
}
vfloat32 VJoint::GetMaxForce()
{
	return m_fMaxForce;
}

void VJoint::SetFudgeFactor(vfloat32 in_fFudgeFactor)
{
	m_fFudgeFactor = in_fFudgeFactor;
	if(m_JointID)
	  dJointSetHinge2Param(m_JointID, dParamFudgeFactor, m_fFudgeFactor);
}

vfloat32 VJoint::GetFudgeFactor()
{
	return m_fFudgeFactor;
}

void VJoint::SetBounce(vfloat32 in_fBounce)
{
	m_fBounce = in_fBounce;
	if(m_JointID)
	  dJointSetHinge2Param( m_JointID, dParamBounce, m_fBounce);
}

vfloat32 VJoint::GetBounce()
{
	return m_fBounce;
}

void VJoint::SetCFM(vfloat32 in_fCFM)
{
	m_fCFM = in_fCFM;
	if(m_JointID)
	  dJointSetHinge2Param( m_JointID, dParamCFM, m_fCFM);
}

vfloat32 VJoint::GetCFM()
{
	return m_fCFM;
}

void VJoint::SetStopCFM(vfloat32 in_fStopCFM)
{
	m_fStopCFM = in_fStopCFM;
}

vfloat32 VJoint::GetStopCFM()
{
	return m_fStopCFM;
}

void VJoint::SetStopERP(vfloat32 in_fStopERP)
{
	m_fStopERP = in_fStopERP;
}

vfloat32 VJoint::GetStopERP()
{
	return m_fStopERP;
}

void VJoint::SetSuspensionERP(vfloat32 in_fSuspensionERP)
{
	m_fSuspensionERP = in_fSuspensionERP;
}

vfloat32 VJoint::GetSuspensionERP()
{
	return m_fSuspensionERP;
}

void VJoint::SetSuspensionCFM(vfloat32 in_fSuspensionCFM)
{
	m_fSuspensionCFM = in_fSuspensionCFM;
	if(m_JointID)	  
	  dJointSetHinge2Param( m_JointID, dParamSuspensionCFM, m_fSuspensionCFM);
}
vfloat32 VJoint::GetSuspensionCFM()
{
	return m_fSuspensionCFM;
}

void VJoint::SetVelocity2(vfloat32 in_fVelocity2)
{
	m_fVelocity2 = in_fVelocity2;
	if(m_JointID)
	  dJointSetHinge2Param (m_JointID, dParamVel2, m_fVelocity2);
}

vfloat32 VJoint::GetVelocity2()
{
	return m_fVelocity2;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------


