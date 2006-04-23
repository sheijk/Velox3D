//-----------------------------------------------------------------------------
#include <v3d/Physics/VBody.h>
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

VBody::VBody(VOdeBody* in_pOdeBody) : m_PositionState(in_pOdeBody), m_OrientationState(in_pOdeBody)
{
	m_CollisionMesh = 0;
	m_Body = in_pOdeBody;
	//m_StateListContainer.RegisterForUpdate(&m_PositionState);
	//m_StateListContainer.RegisterForUpdate(&m_OrientationState);
}

VBody::~VBody()
{
	if(m_Body)
	{
		m_Body->Destroy(); //todo tell the manager abou this
		delete m_Body;
	}
	if(m_CollisionMesh)
	{
		//delete m_CollisionMesh;
	}
}
VOdeBody* VBody::GetOdeBody()
{
	return m_Body;
}

VGeometry* VBody::GetCollisionMesh()
{
	return m_CollisionMesh;
}

void VBody::Update()
{

	const dReal* p = dBodyGetPosition(*m_Body->GetBodyID());
	const dReal* q = dBodyGetQuaternion(*m_Body->GetBodyID());

	m_PositionState.SetPosition(p[0],p[1],p[2]);
	m_OrientationState.GetQuat().Set(q[1], q[2], q[3],q[0]); //convert to x,y,z,w format
	
	/*m_OrientationState.Apply();
	m_PositionState.Apply();
	*///m_StateListContainer.RegisterForUpdate(&m_PositionState);
	//m_StateListContainer.RegisterForUpdate(&m_OrientationState);

	//m_StateListContainer.Update();
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
void VBody::SetCollisionMesh(VGeometry* in_Geometry)
{
	V3D_ASSERT(in_Geometry != 0);

	m_CollisionMesh = in_Geometry;
	dGeomSetBody(*in_Geometry->GetGeomID(), *m_Body->GetBodyID());
}

void VBody::SetPosition(graphics::VVertex3f in_Position)
{
	m_PositionState.SetPosition(in_Position);
	m_PositionState.Apply();
}

void VBody::SetOrientation(math::VQuatf in_Orientation)
{
	m_OrientationState.GetQuat().Set(in_Orientation[0], in_Orientation[1], in_Orientation[2], in_Orientation[3]);
	m_OrientationState.Apply();

}

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
