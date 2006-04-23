#include <V3d/Physics/VBodyPart.h>
#include <V3d/Core.h>
#include <V3d/Physics/VBody.h>
#include <V3dLib/Graphics/Geometry/VVertex3f.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/Physics/VPhysicManagerPart.h>
#include <V3d/Physics/Bounding/IVBoundingVolumePart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;

VBodyPart::VBodyPart(BodyPtr in_pBody) : m_pRigidBodyPart(VPartDependency::Neighbour, RegisterTo()),
										 m_pPhysicManagerPart(VPartDependency::Ancestor, RegisterTo()),
										 m_pVolumePart(VPartDependency::Neighbour, RegisterTo()),
										 m_pUpdateManager(VPartDependency::Ancestor, RegisterTo())
{
	V3D_ASSERT(in_pBody.Get() != 0);
	m_fMass = 1;
	m_pBody = in_pBody;
}

VBodyPart::VBodyPart() : m_pRigidBodyPart(VPartDependency::Neighbour, RegisterTo()),
						 m_pPhysicManagerPart(VPartDependency::Ancestor, RegisterTo()),
						 m_pVolumePart(VPartDependency::Neighbour, RegisterTo()),
						 m_pUpdateManager(VPartDependency::Ancestor, RegisterTo())
{
	m_pBody.Assign(0);
	m_fMass  = 1;
}

VBodyPart::~VBodyPart()
{
}

std::string VBodyPart::GetDefaultId()
{
	return "physicPart";
}

void VBodyPart::Create()
{
	if( !m_pBody.Get())
	{
		m_pBody = m_pPhysicManagerPart->GetPhysicManager()->Create(m_pVolumePart.Get(), m_fMass);
	}
}

void VBodyPart::Activate()
{
	if( m_pUpdateManager.Get() == 0 )
		V3D_THROW(entity::VMissingPartException, "missing part updater 'data'");
	if( m_pVolumePart.Get() == 0 )
		V3D_THROW(entity::VMissingPartException, "missing part volume part 'data'");
	if( m_pPhysicManagerPart.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part physic manager 'data'");

	if( m_pRigidBodyPart.Get() == 0 )
		V3D_THROW(entity::VMissingPartException, "missing part 'data'");
	
	Create();
	m_pUpdateManager->Register(this);
}

void VBodyPart::Deactivate() 
{
	m_pUpdateManager->Unregister(this);
}

VBodyPart::BodyPtr VBodyPart::GetBody()
{
	return m_pBody;
}

void VBodyPart::Update(vfloat32 in_fSeconds)
{
	//m_pBody->Update(); //TODO: wird doppelt aufgerufen

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
	
	//hack!
	if(
		m_Position.GetX() == m_pRigidBodyPart.Get()->GetPosition().GetX() &&
		m_Position.GetY() == m_pRigidBodyPart.Get()->GetPosition().GetY() &&
		m_Position.GetZ() == m_pRigidBodyPart.Get()->GetPosition().GetZ()
		)
	{
	
		Rotate(axis, m_pBody->GetOrientation().GetQuat());
		graphics::VVertex3f pos = m_pBody->GetPositionState().GetPositon();
		MakeTranspose(axis); //TODO: should be coorect but recheck!
		m_Position = pos.AsVector();

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
	else
	{
		m_Position = m_pRigidBodyPart.Get()->GetPosition();
		m_pBody->SetPosition(
			graphics::VVertex3f(
			m_Position.GetX(),
			m_Position.GetY(),
			m_Position.GetZ())
			);
	}
}

void VBodyPart::OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer != 0 )
		{
			in_pAnswer->AddProperty("Mass", m_fMass);
			in_pAnswer->AddProperty("Position", m_Position);
		}
	}
	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");

		if( name == "Position" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			
			if(m_pBody.Get())
			{
				m_pBody->SetPosition(graphics::VVertex3f(pos.GetX(),pos.GetY(),pos.GetZ()));
				vout << "Physics: pos set to " << pos << vendl;
			}
		}
	}
}

namespace {
	entity::VPartParser<VBodyPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------
