/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VJointHinge2.h>
#include <V3d/Physics/VBody.h>
#include <V3d/Core.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
using namespace v3d::math;

VJointHinge2::VJointHinge2()
{
	m_pBody1 = 0;
	m_pBody2 = 0;
	m_fMaxForce2 = 0.0f;
	SetAxis1(1,0,0);
	SetAxis2(0,1,0);
	SetAnchor(0,0,0);
	m_sName = "";
}

VJointHinge2::~VJointHinge2()
{
}

void VJointHinge2::Apply()
{
	if(m_JointID != 0)
	{	
		SetParameters();
		SetAxisAndAnchor();
	}
}

void VJointHinge2::Create(VWorld* in_PhysicWorld)
{
	V3D_ASSERT(in_PhysicWorld != 0);
	AddWorld(in_PhysicWorld);

	// check if a joint group is specified, if not use default group 0
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
	m_bIsActive = true;
}
std::string VJointHinge2::GetName()
{
  return m_sName;
}

void VJointHinge2::SetName(std::string in_sName)
{
  m_sName = in_sName;
}
void VJointHinge2::AddBody(VBody* in_pBody1, VBody* in_pBody2)
{
	m_pBody1 = in_pBody1;
	m_pBody2 = in_pBody2;

	V3D_ASSERT(m_JointID != 0);
	V3D_ASSERT(m_pBody1  != 0);
	V3D_ASSERT(m_pBody2  != 0);
	V3D_ASSERT(*m_pBody1->GetOdeBody()->GetBodyID() != 0);
	V3D_ASSERT(*m_pBody2->GetOdeBody()->GetBodyID() != 0);

	//SetParameters();
	vout << "Joint: attaching body: " << "Body1: "<< m_pBody1->GetPositionState().GetPositon() << " Body2: " << m_pBody2->GetPositionState().GetPositon() << vendl;
	dJointAttach(
		m_JointID,
		*m_pBody1->GetOdeBody()->GetBodyID(),
		*m_pBody2->GetOdeBody()->GetBodyID()
		);
	Apply(); //ode wiki tells to attach joint before applying settings
}

void VJointHinge2::SetAnchor(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Anchor.Set(0,x);
	m_Anchor.Set(1,y);
	m_Anchor.Set(2,z);
	
	Apply();

	/*V3D_ASSERT(m_JointID != 0);*/
//	dJointSetHinge2Anchor(m_JointID, m_Anchor[0], m_Anchor[1], m_Anchor[2]);
}

void VJointHinge2::SetAnchor(VVector3f in_Anchor)
{
	m_Anchor = in_Anchor;
	
	Apply();
	
	/*V3D_ASSERT(m_JointID != 0);*/
//	dJointSetHinge2Anchor(m_JointID, m_Anchor[0], m_Anchor[1], m_Anchor[2]);
}
void VJointHinge2::SetAxis1(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Axis1.Set(0,x);
	m_Axis1.Set(1,y);
	m_Axis1.Set(2,z);

	Apply();

	/*V3D_ASSERT(m_JointID != 0);*/
	
//	dJointSetHinge2Axis1(m_JointID, m_Axis1[0], m_Axis1[1], m_Axis1[2]);
}

void VJointHinge2::SetAxis1(VVector3f in_Axis)
{
	m_Axis1 = in_Axis;

	Apply();
	/*V3D_ASSERT(m_JointID != 0);*/
//	dJointSetHinge2Axis1(m_JointID, m_Axis1[0], m_Axis1[1], m_Axis1[2]);
}

void VJointHinge2::SetAxis2(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Axis2.Set(0,x);
	m_Axis2.Set(1,y);
	m_Axis2.Set(2,z);

	Apply();
	
	/*V3D_ASSERT(m_JointID != 0);*/
//	dJointSetHinge2Axis2(m_JointID, m_Axis2[0], m_Axis2[1], m_Axis2[2]);
}

void VJointHinge2::SetAxis2(VVector3f in_Axis)
{
	m_Axis2 = in_Axis;

	Apply();
	
	//V3D_ASSERT(m_JointID != 0);*/
//	dJointSetHinge2Axis2(m_JointID, m_Axis2[0], m_Axis2[1], m_Axis2[2]);
}

VVector3f VJointHinge2::GetAnchor()
{
//	VVector3f anchor;
//	dVector3 result;
	/*if(m_JointID)
	{
		dJointGetHinge2Anchor (m_JointID, result);
		anchor.Set(result[0],result[1], result[2]);
		return anchor;
	}
	else*/
		return m_Anchor;
}

VVector3f VJointHinge2::GetOwnAnchor()
{
	return m_Anchor;
}

VVector3f VJointHinge2::GetAxis1()
{
	return m_Axis1;
}

VVector3f VJointHinge2::GetAxis2()
{
	return m_Axis2;
}

void VJointHinge2::SetParameters()
{
	V3D_ASSERT(m_JointID != 0);

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

vfloat32 VJointHinge2::GetAnchorAngle1()
{
	return dJointGetHinge2Angle1(m_JointID);
}

void VJointHinge2::SetMaxForce2(vfloat32 in_fMaxForce2)
{
	m_fMaxForce2 = in_fMaxForce2;
	if(m_JointID)
	  dJointSetHinge2Param (m_JointID, dParamFMax2, m_fMaxForce2);
}

vfloat32 VJointHinge2::GetMaxForce2()
{
	return m_fMaxForce2;
}

VBody* VJointHinge2::GetBody1()
{
	return m_pBody1;
}

VBody* VJointHinge2::GetBody2()
{
	return m_pBody2;
}

void VJointHinge2::SetAxisAndAnchor()
{
	if(m_pBody1 && m_pBody2)
	{
		V3D_ASSERT(m_JointID != 0);
		dJointSetHinge2Anchor(m_JointID, m_Anchor[0], m_Anchor[1], m_Anchor[2]);
		dJointSetHinge2Axis1(m_JointID, m_Axis1[0], m_Axis1[1], m_Axis1[2]);
		dJointSetHinge2Axis2(m_JointID, m_Axis2[0], m_Axis2[1], m_Axis2[2]);

		dJointSetHinge2Anchor(m_JointID, m_Anchor[0], m_Anchor[1], m_Anchor[2]);
		dJointSetHinge2Axis1(m_JointID, m_Axis1[0], m_Axis1[1], m_Axis1[2]);
		dJointSetHinge2Axis2(m_JointID, m_Axis2[0], m_Axis2[1], m_Axis2[2]);
		//debug purpose
		GetAnchor();
	}
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
