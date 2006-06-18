#include <v3dlib/EntityParts/VRigidBodyPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VRigidBodyPart::VRigidBodyPart()
{
	//m_Transformation.GetXAxis() = VVector3f(1.0f, 0.0f, 0.0f);
	//m_Transformation.GetYAxis() = VVector3f(0.0f, 1.0f, 0.0f);
	//m_Transformation.GetZAxis() = VVector3f(0.0f, 0.0f, 1.0f);
	m_Transformation.SetPosition(VVector3f(0.0f, 0.0f, 0.0f));
}

void VRigidBodyPart::Activate()
{
}

void VRigidBodyPart::Deactivate()
{
}											 

VVector3f VRigidBodyPart::GetPosition() const
{
	return m_Transformation.GetPosition();
}

void VRigidBodyPart::SetPosition(const VVector3f& in_Position)
{
	m_Transformation.SetPosition(in_Position);
}

void VRigidBodyPart::SetTransform(const math::VRBTransform& in_Trans)
{
	m_Transformation = in_Trans;
}


math::VRBTransform& VRigidBodyPart::GetTransform()
{
	return m_Transformation;
}

std::string VRigidBodyPart::GetDefaultId()
{
	return "body";
}

void VRigidBodyPart::OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	using std::string;
	
	if( ! in_Message.HasProperty("type") )
		return;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer != 0 )
		{
			in_pAnswer->AddProperty("pos", m_Transformation.GetPosition());
			in_pAnswer->AddProperty("viewdir", -m_Transformation.GetZAxis());
			in_pAnswer->AddProperty("updir", m_Transformation.GetYAxis());
		}
	}
	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");
		//const string val = in_pAnswer->GetAs<string>("value");

		if( name == "pos" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			m_Transformation.SetPosition(pos);

			vout << "VRigidBodyPart: set position to " << pos << vendl;
		}
		else if( name == "direction" )
		{
			VVector3f lookAtPoint = in_Message.GetAs<VVector3f>("value");
			VVector3f direction = lookAtPoint - m_Transformation.GetPosition();
			VVector3f upDir = Cross(Cross(VVector3f(0, 1, 0), direction), direction);

			Normalize(direction);
			Normalize(upDir);

			if( Length(direction) != 0 && Length(upDir) != 0 )
				m_Transformation.SetLookAt(
					m_Transformation.GetPosition(),
					direction,
					upDir);

			vout << "VRigidBodyPart: looking to " << direction
				<< ", up = " << upDir << vendl;
			vout << "x-axis = " << m_Transformation.GetXAxis()
				<< ", y-axis = " << m_Transformation.GetYAxis()
				<< ", z-axis = " << m_Transformation.GetZAxis()
				<< vendl;
		}
		else if( name == "viewdir" )
		{
			VVector3f viewdir = in_Message.GetAs<VVector3f>("value");
			m_Transformation.SetZAxis(-viewdir);
		}
		else if( name == "updir" )
		{
			VVector3f updir = in_Message.GetAs<VVector3f>("value");
			m_Transformation.SetYAxis(updir);
		}
	}
}

namespace {
	VPartParser<VRigidBodyPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
