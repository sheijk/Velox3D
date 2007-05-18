/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//-----------------------------------------------------------------------------
#include <V3d/Physics/VBody.h>
//#include <V3dLib/Physics/VPhysicWorld.h>
//#include <V3dLib/Physics/VPhysicPositionState.h>
//#include <V3dLib/Physics/VPhysicGeometry.h>
//#include <V3d/Math/VRBTransform.h>
#include <V3d/Core.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
using namespace math;
VBody::VBody(VBody::SpOdeBody in_pOdeBody, std::string in_sName) : m_PositionState(in_pOdeBody), m_OrientationState(in_pOdeBody)
{
	m_CollisionMesh.Assign(0);
	V3D_ASSERT( in_pOdeBody != 0 );
	m_Body = in_pOdeBody;
	m_PositionState.Apply();
	m_OrientationState.Apply();
	m_sName = in_sName;
}

VBody::~VBody()
{
  ;
}

std::string VBody::GetName()
{
	return m_sName;
}
VBody::SpOdeBody VBody::GetOdeBody()
{
	return m_Body;
}

VBody::SpGeom VBody::GetCollisionMesh()
{
	return m_CollisionMesh;
}

void VBody::Update()
{
	const dReal* p = dBodyGetPosition(m_Body->GetBodyID());
	const dReal* q = dBodyGetQuaternion(m_Body->GetBodyID());

	m_PositionState.SetPosition(p[0],p[1],p[2]);
	m_OrientationState.GetQuat().Set(q[1], q[2], q[3],q[0]); //convert to x,y,z,w format
}

VStatePosition& VBody::GetPositionState()
{
	return m_PositionState;
}

VStateOrientation& VBody::GetOrientation()
{
	return m_OrientationState;
}

void VBody::Add(VState* in_pState)
{
	m_StateListContainer.RegisterForUpdate(in_pState);
}

void VBody::Delete(VState* in_pState)
{
	m_StateListContainer.UnregisterForUpdate(in_pState);
}
void VBody::SetCollisionMesh(VSharedPtr<VGeometry> in_Geometry)
{
	V3D_ASSERT(in_Geometry != 0);
	m_CollisionMesh = in_Geometry;
	dGeomSetBody(*in_Geometry->GetGeomID(), m_Body->GetBodyID());
	m_PositionState.Apply();
	m_OrientationState.Apply();
}

void VBody::SetPosition(math::VVector3f in_Position)
{
	m_PositionState.SetPosition(in_Position);
	m_PositionState.Apply();
}

void VBody::SetOrientation(math::VQuatf in_Orientation)
{
	m_OrientationState.GetQuat().Set(
		in_Orientation[0],
		in_Orientation[1],
		in_Orientation[2],
		in_Orientation[3]);

	m_OrientationState.Apply();
}

void VBody::SetOrientation(VVector4f in_Orientation)
{
	//ode quaternion representation w,x,y,z but recheck
	m_OrientationState.GetQuat().Set(
		in_Orientation[0],
		in_Orientation[1],
		in_Orientation[2],
		in_Orientation[3]);

	m_OrientationState.Apply();
}

void VBody::Destroy()
{
	//TODO unregister name!!!
	//m_Body->Destroy();
	m_Body.Release();
	m_Body.Assign(0);
}

bool VBody::IsValid()
{
	if(m_Body.Get())
		return true;
	return false;
}
void VBody::Deactivate()
{
	if( m_Body.Get() )
		dBodyDisable(m_Body->GetBodyID());
}

void VBody::Activate()
{
	if ( m_Body.Get() )
	{
		dBodyEnable(m_Body->GetBodyID());
		dBodySetLinearVel  (m_Body->GetBodyID(), 0,0,0);
		dBodySetAngularVel (m_Body->GetBodyID(), 0,0,0);
	}
}

vbool VBody::IsEnabled()
{
	if( m_Body.Get() )
	{
		if(dBodyIsEnabled(m_Body->GetBodyID()))
			return true;
	}

	return false;
}

void VBody::SetMass(vfloat32 in_fMass)
{
	if( m_Body.Get() )
	{
		dMass mass;
		dBodyGetMass(m_Body->GetBodyID(), &mass);
		mass.adjust(in_fMass);
		dBodySetMass(m_Body->GetBodyID(), &mass);
	}
}

vfloat32 VBody::GetMass()
{
	if( m_Body.Get() )
	{
		dMass mass;
		dBodyGetMass(m_Body->GetBodyID(), &mass);
		return mass.mass;
	}
	else
		return 0;
}
void VBody::SetName(std::string in_sName)
{
	m_sName = in_sName;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

