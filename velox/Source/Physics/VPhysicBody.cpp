//-----------------------------------------------------------------------------
#include <v3dLib/Physics/VPhysicBody.h>
#include <V3dLib/Physics/VPhysicWorld.h>
#include <V3dLib/Physics/VPhysicPositionState.h>
#include <V3dLib/Physics/VPhysicGeometry.h>
#include <V3dLib/Math/VRBTransform.h>
#include <V3d/Core.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
using namespace entity;

VPhysicBody::VPhysicBody() : 
	pBodyPart(VPartDependency::Neighbour, RegisterTo())
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
	SetTransformation();
}

void VPhysicBody::Activate()
{
	if( pBodyPart.Get() == 0 )
		V3D_THROW(entity::VMissingPartException, "missing part 'data'");
}

void VPhysicBody::Deactivate() 
{
	vout << "deactivating setter part" << vendl;
}

void VPhysicBody::SetPosition(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_PositionState.SetPosition(x,y,z);
	AddState(&m_PositionState);
}

void VPhysicBody::SetTransformation()
{
	
	//TODO: andere koennen VRigidBody aendern
	const dReal* p = dBodyGetPosition(m_BodyID);
	const dReal* q = dBodyGetQuaternion(m_BodyID);

	m_PositionState.SetPosition(p[0],p[1],p[2]);
	m_Quaternion.Set(q[0], q[1], q[2],q[3]);
	AddState(&m_PositionState);
		
	//Quaternion calc's
	VVector3f x1,y1,z1;
	VMatrix<vfloat32, 3, 3> axis;
	VMatrix<vfloat32, 4, 4> trans; //TODO: rbtransform accessmethoden aendern

	pBodyPart->GetTransform().GetAxis(x1,y1,z1);
    
	axis.Set(0,0, x1.Get(0)); 
	axis.Set(1,0, x1.Get(1));
	axis.Set(2,0, x1.Get(2));

	axis.Set(0,1, y1.Get(0));
	axis.Set(1,1, y1.Get(1));
	axis.Set(2,1, y1.Get(2));

	axis.Set(0,2, z1.Get(0));
	axis.Set(1,2, z1.Get(1));
	axis.Set(2,2, z1.Get(2));
	
	//MakeTranspose(axis);
	
	Rotate(axis, m_Quaternion);
	MakeTranspose(axis); //TODO: should be coorect but recheck!

	trans.Set(0,0, axis.Get(0,0));
	trans.Set(0,1, axis.Get(0,1));
	trans.Set(0,2, axis.Get(0,2));
	trans.Set(0,3, p[0]);
	
	trans.Set(1,0, axis.Get(1,0));
	trans.Set(1,1, axis.Get(1,1));
	trans.Set(1,2, axis.Get(1,2));
	trans.Set(1,3, p[1]);

	trans.Set(2,0, axis.Get(2,0));
	trans.Set(2,1, axis.Get(2,1));
	trans.Set(2,2, axis.Get(2,2));
	trans.Set(2,3, p[2]);

	trans.Set(3,0, 0);
	trans.Set(3,1, 0);
	trans.Set(3,2, 0);
	trans.Set(3,3, 1);
	
	pBodyPart->SetTransform(math::VRBTransform(trans));
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

graphics::VVertex3f VPhysicBody::GetPosition()
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

std::string VPhysicBody::GetDefaultId()
{
	return "physic";
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
