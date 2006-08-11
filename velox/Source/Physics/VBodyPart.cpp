#include <V3d/Physics/VBodyPart.h>
#include <V3d/Core.h>
#include <V3d/Physics/VBody.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/Physics/VPhysicManagerPart.h>
#include <V3d/Physics/Bounding/IVBoundingVolumePart.h>
#include <V3d/Math//VQuaternionOps.h>
#include <V3d/Math/VQuaternion.h>

#include <limits>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;
using namespace math;

VBodyPart::VBodyPart(BodyPtr in_pBody) : m_pRigidBodyPart(VPartDependency::Neighbour, RegisterTo()),
										 m_pPhysicManagerPart(VPartDependency::Ancestor, RegisterTo()),
										 m_pVolumePart(VPartDependency::Neighbour, RegisterTo()),
										 m_pUpdateManager(VPartDependency::Ancestor, RegisterTo())
{
	V3D_ASSERT(in_pBody.Get() != 0);
	m_fMass = 0.1f;
	m_pBody = in_pBody;
}

VBodyPart::VBodyPart() : m_pRigidBodyPart(VPartDependency::Neighbour, RegisterTo()),
						 m_pPhysicManagerPart(VPartDependency::Ancestor, RegisterTo()),
						 m_pVolumePart(VPartDependency::Neighbour, RegisterTo()),
						 m_pUpdateManager(VPartDependency::Ancestor, RegisterTo())
{
	m_pBody.Assign(0);
	m_fMass  = 0.1f;
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
	if( ! m_pBody.Get() || ! m_pBody.Get()->IsValid() )
	//if( ! m_pBody.Get())
	{
		m_pBody = m_pPhysicManagerPart->GetPhysicManager()->Create(m_pVolumePart.Get(), m_fMass);
		
		m_Position = m_pRigidBodyPart.Get()->GetPosition();
		m_pBody->Deactivate();

		m_pBody->SetPosition(
			graphics::VVertex3f(
			m_Position[0],
			m_Position[1],
			m_Position[2])
			);
		//TODO: set orientation
		m_pBody->Activate();
		m_fMass = m_pBody->GetMass();
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

	//hack!
	/*if(
		m_Position.GetX() - m_pRigidBodyPart.Get()->GetPosition().GetX() <= std::numeric_limits<float>::epsilon() &&
		m_Position.GetY() - m_pRigidBodyPart.Get()->GetPosition().GetY() <= std::numeric_limits<float>::epsilon() &&
		m_Position.GetZ() - m_pRigidBodyPart.Get()->GetPosition().GetZ() <= std::numeric_limits<float>::epsilon()
		) //makes all things oscillating
	*/
	//if(
	//	m_Position.GetX() == m_pRigidBodyPart.Get()->GetPosition().GetX() &&
	//	m_Position.GetY() == m_pRigidBodyPart.Get()->GetPosition().GetY() &&
	//	m_Position.GetZ() == m_pRigidBodyPart.Get()->GetPosition().GetZ())

	if(
		fabs( m_Position.GetX() - m_pRigidBodyPart.Get()->GetPosition().GetX() ) <= std::numeric_limits<vfloat32>::epsilon() &&
		fabs( m_Position.GetY() - m_pRigidBodyPart.Get()->GetPosition().GetY() ) <= std::numeric_limits<vfloat32>::epsilon() &&
		fabs( m_Position.GetZ() - m_pRigidBodyPart.Get()->GetPosition().GetZ() ) <= std::numeric_limits<vfloat32>::epsilon() )


	{
		//VVector3f x1,y1,z1;
		//VMatrix<vfloat32, 3, 3> axis;
		//VMatrix<vfloat32, 4, 4> trans; //TODO: rbtransform accessmethoden aendern

		//m_pRigidBodyPart->GetTransform().GetAxis(x1,y1,z1);

		//axis.Set(0,0, x1.Get(0)); 
		//axis.Set(1,0, x1.Get(1));
		//axis.Set(2,0, x1.Get(2));

		//axis.Set(0,1, y1.Get(0));
		//axis.Set(1,1, y1.Get(1));
		//axis.Set(2,1, y1.Get(2));

		//axis.Set(0,2, z1.Get(0));
		//axis.Set(1,2, z1.Get(1));
		//axis.Set(2,2, z1.Get(2));

		////MakeTranspose(axis);

		//Rotate(axis, m_pBody->GetOrientation().GetQuat());
		//graphics::VVertex3f pos = m_pBody->GetPositionState().GetPositon();
		//MakeTranspose(axis); //TODO: should be coorect but recheck!
		//m_Position = pos.AsVector();

		//trans.Set(0,0, axis.Get(0,0));
		//trans.Set(0,1, axis.Get(0,1));
		//trans.Set(0,2, axis.Get(0,2));
		//trans.Set(0,3, pos.x);

		//trans.Set(1,0, axis.Get(1,0));
		//trans.Set(1,1, axis.Get(1,1));
		//trans.Set(1,2, axis.Get(1,2));
		//trans.Set(1,3, pos.y);

		//trans.Set(2,0, axis.Get(2,0));
		//trans.Set(2,1, axis.Get(2,1));
		//trans.Set(2,2, axis.Get(2,2));
		//trans.Set(2,3, pos.z);

		//trans.Set(3,0, 0);
		//trans.Set(3,1, 0);
		//trans.Set(3,2, 0);
		//trans.Set(3,3, 1);

		//m_pRigidBodyPart->SetTransform(math::VRBTransform(trans));
		m_pRigidBodyPart->GetTransform().Rotate(m_pBody->GetOrientation().GetQuat());
 		m_pRigidBodyPart->SetPosition(m_pBody->GetPositionState().GetPositon().AsVector());
		m_Position = m_pBody->GetPositionState().GetPositon().AsVector();

	}
	else
	{
		//delete body

		VQuatf rigidQuat = m_pBody->GetOrientation().GetQuat();
		m_Position = m_pRigidBodyPart.Get()->GetPosition();
		m_pBody->Deactivate();

		//TODO will not take joints into account. coming with new physic manager design
		//restore the old values
		m_pBody->SetPosition(
			graphics::VVertex3f(
			m_Position[0],
			m_Position[1],
			m_Position[2])
			);
		//m_pBody->SetOrientation(rigidQuat);
		m_pBody->Activate();
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
			VVector4f quat;
			VVector4f axisAngleQuat;
			vbool isEnabled = false;
			if( m_pBody.Get() != 0)
			{
				quat = m_pBody->GetOrientation().GetAsVector();
				isEnabled = m_pBody->IsEnabled();
			}
				
			in_pAnswer->AddProperty("Mass", m_fMass);
			in_pAnswer->AddProperty("Position", m_Position);
			in_pAnswer->AddProperty("Address", m_pBody.Get());
			in_pAnswer->AddProperty("Quat", quat);
			in_pAnswer->AddProperty("QuatAxisAngle", axisAngleQuat);
			in_pAnswer->AddProperty("Enabled", isEnabled);
		}
	}
	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");

		if (name == "Mass" )
		{
			vfloat32 param = in_Message.GetAs<vfloat32>("value");
			if(m_pBody.Get())
			{
				m_pBody->SetMass(param);
				m_fMass = m_pBody->GetMass();
			}
		}

		if( name == "Position" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			
			if(m_pBody.Get())
			{
				m_pBody->SetPosition(graphics::VVertex3f(pos.GetX(),pos.GetY(),pos.GetZ()));
				vout << "Physics: pos set to " << pos << vendl;
			}
		}

		if( name == "Quat" )
		{
			VVector4f pos = in_Message.GetAs<VVector4f>("value");

			if(m_pBody.Get())
			{
				m_pBody->SetOrientation(pos);
			}
		}

		if( name == "QuatAxisAngle" )
		{
			VVector4f pos = in_Message.GetAs<VVector4f>("value");
			VVector3f axis;
			
			for(vuint i = 0; i < 3; i++)
			{
				axis.Set(i, pos[i]);
			}
			
			VQuatf quat = QuatFromAxisAngle(axis, pos[3]);
			//TODO: check if coharent with dQFromAxisAndAngle
			
			if(m_pBody.Get())
			{
				m_pBody->SetOrientation(quat);
			}
		}
	}
}

V3D_REGISTER_PART_PARSER(VBodyPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------
