#include <v3dLib/Physics/VPhysicJointHinge2State.h>
#include <v3dLib/Physics/VPhysicBody.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VPhysicJointHinge2State::VPhysicJointHinge2State()
{
	m_pBody1 = 0;
	m_pBody2 = 0;

	m_fMaxForce2 = 0.0f;
}

VPhysicJointHinge2State::~VPhysicJointHinge2State()
{
}

void VPhysicJointHinge2State::Apply()
{
	SetParameters();
}

void VPhysicJointHinge2State::Create(VPhysicWorld* in_PhysicWorld)
{

	AddWorld(in_PhysicWorld);

	// check if a joint group is specified, if not use defult group 0
	if(!m_pJointGroup)
	{
		m_JointID = dJointCreateHinge2(
			*m_pPhysicWorld->GetWorld(),
			0);
	}
	else
	{
		m_JointID = dJointCreateHinge2(
			*m_pPhysicWorld->GetWorld(),
			*m_pJointGroup->GetJointGroupID());
	}

	SetAxis1(1,0,0);
	SetAxis2(0,1,0);
	SetAnchor(0,0,1);
}

void VPhysicJointHinge2State::AddBody(VPhysicBody* in_pBody1, VPhysicBody* in_pBody2)
{
	m_pBody1 = in_pBody1;
	m_pBody2 = in_pBody2;

	V3D_ASSERT(m_JointID != 0);
	V3D_ASSERT(m_pBody1  != 0);
	V3D_ASSERT(m_pBody2  != 0);
	V3D_ASSERT(*m_pBody1->GetBodyID() != 0);
	V3D_ASSERT(*m_pBody2->GetBodyID() != 0);

	SetParameters();
	dJointAttach(m_JointID, *m_pBody1->GetBodyID(), *m_pBody2->GetBodyID());
}

void VPhysicJointHinge2State::SetAnchor(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Anchor.x = x;
	m_Anchor.y = y;
	m_Anchor.z = z;

	dJointSetHinge2Anchor(m_JointID, m_Anchor.x, m_Anchor.y, m_Anchor.z);
}

void VPhysicJointHinge2State::SetAnchor(graphics::VVertex3f in_Anchor)
{
	m_Anchor = in_Anchor;
	
	V3D_ASSERT(m_JointID != 0);
	dJointSetHinge2Anchor(m_JointID, m_Anchor.x, m_Anchor.y, m_Anchor.z);
}
void VPhysicJointHinge2State::SetAxis1(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Axis1.x = x;
	m_Axis1.y = y;
	m_Axis1.z = z;

	V3D_ASSERT(m_JointID != 0);
	dJointSetHinge2Axis1(m_JointID, m_Axis1.x, m_Axis1.y, m_Axis1.z);
}

void VPhysicJointHinge2State::SetAxis1(graphics::VVertex3f in_Axis)
{
	m_Axis1 = in_Axis;
	V3D_ASSERT(m_JointID != 0);
	dJointSetHinge2Axis1(m_JointID, m_Axis1.x, m_Axis1.y, m_Axis1.z);
}

void VPhysicJointHinge2State::SetAxis2(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Axis2.x = x;
	m_Axis2.y = y;
	m_Axis2.z = z;
	
	V3D_ASSERT(m_JointID != 0);
	dJointSetHinge2Axis2(m_JointID, m_Axis2.x, m_Axis2.y, m_Axis2.z);
}

void VPhysicJointHinge2State::SetAxis2(graphics::VVertex3f in_Axis)
{
	m_Axis2 = in_Axis;
	
	V3D_ASSERT(m_JointID != 0);
	dJointSetHinge2Axis2(m_JointID, m_Axis2.x, m_Axis2.y, m_Axis2.z);
}

graphics::VVertex3f VPhysicJointHinge2State::GetAnchor()
{
	return m_Anchor;
}

graphics::VVertex3f VPhysicJointHinge2State::GetAxis1()
{
	return m_Axis1;
}

graphics::VVertex3f VPhysicJointHinge2State::GetAxis2()
{
	return m_Axis2;
}

void VPhysicJointHinge2State::SetParameters()
{
	 dJointSetHinge2Param (m_JointID, dParamLoStop,m_fLowStop);
	 dJointSetHinge2Param (m_JointID, dParamHiStop,m_fHighStop);
	 dJointSetHinge2Param (m_JointID, dParamVel, m_fVelocity);
	 dJointSetHinge2Param (m_JointID, dParamFMax, m_fMaxForce);
	 dJointSetHinge2Param (m_JointID, dParamFudgeFactor, m_fFudgeFactor);
	 dJointSetHinge2Param (m_JointID, dParamBounce, m_fBounce);
	 dJointSetHinge2Param (m_JointID, dParamCFM, m_fCFM);
	 dJointSetHinge2Param (m_JointID, dParamStopERP, m_fStopERP);
	 dJointSetHinge2Param (m_JointID, dParamStopCFM, m_fStopCFM);
	 dJointSetHinge2Param (m_JointID, dParamSuspensionERP, m_fSuspensionERP);
	 dJointSetHinge2Param (m_JointID, dParamSuspensionCFM, m_fSuspensionCFM);
	 dJointSetHinge2Param (m_JointID, dParamVel2, m_fVelocity2);
	 dJointSetHinge2Param (m_JointID, dParamFMax2, m_fMaxForce2);
}

vfloat32 VPhysicJointHinge2State::GetAnchorAngle1()
{
	return dJointGetHinge2Angle1(m_JointID);
}

void VPhysicJointHinge2State::SetMaxForce2(vfloat32 in_fMaxForce2)
{
	m_fMaxForce2 = in_fMaxForce2;
}

vfloat32 VPhysicJointHinge2State::GetMaxForce2()
{
	return m_fMaxForce2;
}

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
