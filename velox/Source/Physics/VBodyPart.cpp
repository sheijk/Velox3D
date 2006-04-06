#include <V3d/Physics/VBodyPart.h>
#include <V3d/Core.h>
#include <V3d/Core/MemManager.h>
#include <V3d/Physics/VBody.h>
#include <V3dLib/Graphics/Geometry/VVertex3f.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;

VBodyPart::VBodyPart(BodyPtr in_pBody) : m_pRigidBodyPart(VPartDependency::Neighbour, RegisterTo())
{
	V3D_ASSERT(in_pBody.Get() != 0);

	m_pBody = in_pBody;
}

VBodyPart::~VBodyPart()
{
}

std::string VBodyPart::GetDefaultId()
{
	return "physicPart";
}

void VBodyPart::Activate()
{
	if( m_pRigidBodyPart.Get() == 0 )
		V3D_THROW(entity::VMissingPartException, "missing part 'data'");
	else
	{
		m_pBody->SetPosition(graphics::VVertex3f(m_pRigidBodyPart->GetPosition().GetX(), 
				m_pRigidBodyPart->GetPosition().GetY(), 
				m_pRigidBodyPart->GetPosition().GetZ())); 
	}
}

void VBodyPart::Deactivate() 
{
	vout << "deactivating setter part" << vendl;
}

VBodyPart::BodyPtr VBodyPart::GetBody()
{
	return m_pBody;
}

void VBodyPart::Update()
{
	m_pBody->Update();

	VVector3f x1,y1,z1;
	VMatrix<vfloat32, 3, 3> axis;
	VMatrix<vfloat32, 4, 4> trans; //TODO: rbtransform accessmethoden aendern

	m_pRigidBodyPart->GetTransform().GetAxis(x1,y1,z1);

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

	Rotate(axis, m_pBody->GetOrientation().GetQuat());
	graphics::VVertex3f pos = m_pBody->GetPositionState().GetPositon();
	MakeTranspose(axis); //TODO: should be coorect but recheck!

	trans.Set(0,0, axis.Get(0,0));
	trans.Set(0,1, axis.Get(0,1));
	trans.Set(0,2, axis.Get(0,2));
	trans.Set(0,3, pos.x);

	trans.Set(1,0, axis.Get(1,0));
	trans.Set(1,1, axis.Get(1,1));
	trans.Set(1,2, axis.Get(1,2));
	trans.Set(1,3, pos.y);

	trans.Set(2,0, axis.Get(2,0));
	trans.Set(2,1, axis.Get(2,1));
	trans.Set(2,2, axis.Get(2,2));
	trans.Set(2,3, pos.z);

	trans.Set(3,0, 0);
	trans.Set(3,1, 0);
	trans.Set(3,2, 0);
	trans.Set(3,3, 1);

	m_pRigidBodyPart->SetTransform(math::VRBTransform(trans));
}
//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------
