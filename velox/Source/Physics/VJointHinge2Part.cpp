#include <V3d/Physics/VJointHinge2Part.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/Physics/VPhysicManagerPart.h>
#include <V3d/Physics/VBody.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::entity;

VJointHinge2Part::VJointHinge2Part() : 
	m_pPhysicManagerPart(entity::VPartDependency::Ancestor, RegisterTo())
{
	m_bIsLinkedByBodyOne = false;
	m_bIsLinkedByBodyTwo = false;
	m_bIsActive = false;
	m_bIsReady = false;
	
	m_pBodyAddressOne = 0;
	m_pBodyAddressTwo = 0;
}

void VJointHinge2Part::RegisterBody(VBody* in_pAddress)
{
	if(in_pAddress != 0)
	{
		if( (m_pBodyAddressOne != in_pAddress) && (m_pBodyAddressTwo != in_pAddress))
		{
			if (m_pBodyAddressOne == 0)
			{
				m_pBodyAddressOne = in_pAddress;
				m_bIsLinkedByBodyOne = true;
				Create();
			}
			else
			{
				m_pBodyAddressTwo = in_pAddress;
				m_bIsLinkedByBodyTwo = true;
				Create();
			}
		}
		else
		{
			V3D_THROW(VException, "body address does not match. Something smells");
		}
	}
}

void VJointHinge2Part::UnregisterBody(VBody* in_pAddress)
{
	if( in_pAddress != 0)
	{
		if( in_pAddress == m_pBodyAddressOne )
		{
			m_pBodyAddressOne = 0;
			m_bIsLinkedByBodyOne = false;
		}

		if( in_pAddress == m_pBodyAddressTwo )
		{
			m_pBodyAddressTwo = 0;
			m_bIsLinkedByBodyTwo = false;
		}

		else
		{
			V3D_THROW(VException, "invalid address to pointer specified!");
		}
	}
}

void VJointHinge2Part::Activate()
{
	if( m_pPhysicManagerPart.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part physic manager 'data'");

	if( !m_bIsActive)
	{
		m_Joint.Create(m_pPhysicManagerPart.Get()->GetPhysicManager().Get()->GetWorld());
		m_bIsActive = true;
		//create the link of the 2 bodies
		Create();
	}
	
	//ode seems to forget the anchor location
	m_Joint.SetAnchor(m_Joint.GetOwnAnchor());
	m_Joint.Apply();
}

void VJointHinge2Part::Create()
{
	if( m_bIsLinkedByBodyTwo && m_bIsLinkedByBodyOne )
	{
		m_Joint.AddBody(m_pBodyAddressOne, m_pBodyAddressTwo);
		m_Joint.Apply();
	}
}

void VJointHinge2Part::Deactivate()
{
	m_bIsActive = false;
	m_Joint.Destroy(); //not sure if this is a good idea
}

void VJointHinge2Part::OnMessage(
							   const messaging::VMessage& in_Message,
							   messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer != 0 )
		{
			in_pAnswer->AddProperty("LinkedByBodyOne", m_bIsLinkedByBodyOne);
			in_pAnswer->AddProperty("LinkedByBodyTwo", m_bIsLinkedByBodyTwo);
			in_pAnswer->AddProperty("Anchor", m_Joint.GetAnchor());
			
			/* somehow a bug...
			 * this seems to be the solution I searched one month for..
			 * cannot explain it but entity systems seems to do some mess up
			 * with ode...never seen this kind of strange behavior
			 */
			m_Joint.SetAnchor(m_Joint.GetAnchor());
			m_Joint.Apply();
			
			in_pAnswer->AddProperty("Axis1", m_Joint.GetAxis1());
			in_pAnswer->AddProperty("Axis2", m_Joint.GetAxis2());
			in_pAnswer->AddProperty("LowStop", m_Joint.GetLowStop());
			in_pAnswer->AddProperty("HighStop", m_Joint.GetHighStop());
			in_pAnswer->AddProperty("Velocity", m_Joint.GetVelocity());
			in_pAnswer->AddProperty("MaxForce", m_Joint.GetMaxForce());
			in_pAnswer->AddProperty("FudgeFactor", m_Joint.GetFudgeFactor());
			in_pAnswer->AddProperty("Bounce", m_Joint.GetBounce());
			in_pAnswer->AddProperty("CFM", m_Joint.GetCFM());
			in_pAnswer->AddProperty("StopERP", m_Joint.GetStopERP());
			in_pAnswer->AddProperty("StopCFM", m_Joint.GetStopCFM());
			in_pAnswer->AddProperty("SuspensionERP", m_Joint.GetSuspensionERP());
			in_pAnswer->AddProperty("SuspensionCFM", m_Joint.GetSuspensionCFM());
			in_pAnswer->AddProperty("Velocity2", m_Joint.GetVelocity2());
			in_pAnswer->AddProperty("MaxForce2", m_Joint.GetMaxForce2());
			in_pAnswer->AddProperty("Body1", m_pBodyAddressOne);
			in_pAnswer->AddProperty("Body2", m_pBodyAddressTwo);
		}
	}

	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");

		if( name == "Anchor" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			m_Joint.SetAnchor(pos);
			m_Joint.Apply();
		}

		if( name == "Axis1" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			m_Joint.SetAxis1(pos);
			m_Joint.Apply();
		}

		if( name == "Axis2" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			m_Joint.SetAxis2(pos);
			m_Joint.Apply();
		}

		if( name == "LowStop" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetLowStop(pos);
			m_Joint.Apply();
		}

		if ( name == "HighStop")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetHighStop(pos);
			m_Joint.Apply();
		}

		if ( name == "Velocity")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetVelocity(pos);
			m_Joint.Apply();
		}

		if ( name == "MaxForce")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetMaxForce(pos);
			m_Joint.Apply();
		}

		if ( name == "FudgeFactor")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetFudgeFactor(pos);
			m_Joint.Apply();
		}

		if ( name == "Bounce")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetBounce(pos);
			m_Joint.Apply();
		}

		if ( name == "CFM")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetCFM(pos);
			m_Joint.Apply();
		}

		if ( name == "StopERP")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetStopERP(pos);
			m_Joint.Apply();
		}

		if ( name == "StopCFM")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetStopCFM(pos);
			m_Joint.Apply();
		}

		if ( name == "SuspensionERP")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetSuspensionERP(pos);
			m_Joint.Apply();
		}

		if ( name == "SuspensionCFM")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetSuspensionCFM(pos);
			m_Joint.Apply();
		}

		if ( name == "Velocity2")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetVelocity2(pos);
			m_Joint.Apply();
		}

		if ( name == "MaxForce2")
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Joint.SetMaxForce2(pos);
			m_Joint.Apply();
		}
	}
}

VJointHinge2& VJointHinge2Part::GetJointHinge2()
{
	return m_Joint;
}

V3D_REGISTER_PART_PARSER(VJointHinge2Part);
//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------
