//-----------------------------------------------------------------------------
#include <v3dLib/Physics/VPhysicBody.h>
#include <V3dLib/Physics/VPhysicWorld.h>
#include <V3dLib/Physics/VPhysicPositionState.h>
#include <V3dLib/Physics/VPhysicGeometry.h>
#include <V3d/Core.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

VPhysicBody::VPhysicBody()
{
	m_BodyID = 0;
	m_pWorld = 0;
	m_PositionState.SetParent(this);
}

VPhysicBody::~VPhysicBody()
{
}

dBodyID* VPhysicBody::GetBodyID()
{
	return &m_BodyID;
}

void VPhysicBody::Create(VPhysicWorld* in_PhysicWorld)
{
	m_BodyID = dBodyCreate(*in_PhysicWorld->GetWorld());
	m_pWorld = in_PhysicWorld;
}

void VPhysicBody::Update()
{
	const dReal* p = dBodyGetPosition(m_BodyID);
	SetPosition((vfloat32)p[0], (vfloat32)p[1], (vfloat32)p[2]);
}

void VPhysicBody::Activate()
{
	if( pBodyPart == 0 )
		V3D_THROW(entity::VMissingPartException, "missing part 'data'");
}

void VPhysicBody::Deactivate() 
{
	vout << "deactivating setter part" << vendl;
}

void VPhysicBody::TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part)
{
	if( in_Part.IsOfType<racer::VRigidBodyPart>() )
		pBodyPart = in_Part.Convert<racer::VRigidBodyPart>();
}

void VPhysicBody::SetPosition(vfloat32 x, vfloat32 y, vfloat32 z)
{
	//vout << "x: " << x << "y: " << y << "z: " << z<< vendl;

	//TODO: andere koennen VRigidBody aendern
	m_PositionState.SetPosition(x,y,z);
	AddState(&m_PositionState);
	
	Position pos;
	pos.Set(0, x);
	pos.Set(1, y);
	pos.Set(2, z);
	
	pBodyPart->SetPosition(pos);
}

void VPhysicBody::SetCollisionBody(VPhysicGeometry* in_CollisionBodyState)
{
	dGeomSetBody(*in_CollisionBodyState->GetGeomID(), m_BodyID);
}

void VPhysicBody::UpdatePositionFromBody()
{
	vfloat64* pPos = (vfloat64*)dBodyGetPosition(m_BodyID);

//	m_PositionState.SetPosition(pPos[0], pPos[1], pPos[2]);
}

graphics::VVector3f VPhysicBody::GetPosition()
{
	return m_PositionState.GetPositon();
}

void VPhysicBody::SetQuaternion(const vfloat32 x, const  vfloat32 y,
								const vfloat32 z, const vfloat32 w)
{
	dQuaternion q;
	
	q[0]=x;
	q[1]=y;
	q[2]=z;
	q[3]=w;
	
	dBodySetQuaternion(m_BodyID, q);
	
	m_Quaternion.Set(x, y, z, w);
}

void VPhysicBody::SetQuaternion(const VQuatf in_Quat)
{
	m_Quaternion  = in_Quat;

	dQuaternion q;

	q[0]=m_Quaternion[0];
	q[1]=m_Quaternion[1];
	q[2]=m_Quaternion[2];
	q[3]=m_Quaternion[3];

	dBodySetQuaternion(m_BodyID, q);
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
