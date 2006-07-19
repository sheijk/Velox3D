#include <v3d/Physics/VPhysicManagerPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace  physics {
//-----------------------------------------------------------------------------
using namespace v3d;

VPhysicManagerPart::VPhysicManagerPart() : 
m_pUpdateManager(entity::VPartDependency::Neighbour, RegisterTo())
{
	m_pPhysicManager.Assign(new VPhysicManager());
}

VPhysicManagerPart::~VPhysicManagerPart()
{
	;
}

void VPhysicManagerPart::Activate()
{
	//m_pPhysicManager->RegisterToUpdater();
	m_pUpdateManager->Register(this);
}

void VPhysicManagerPart::Deactivate()
{
	m_pUpdateManager->Unregister(this);
	//m_pPhysicManager->UnregisterToUpdater();
}

void VPhysicManagerPart::Update(vfloat32 in_fSeconds)
{
	if(in_fSeconds == 0) //no step plz
		return;
	m_pPhysicManager->Update(in_fSeconds);
}

std::string VPhysicManagerPart::GetDefaultId()
{
	return "physicManagerPart";
}

VPhysicManagerPtr VPhysicManagerPart::GetPhysicManager()
{
	return m_pPhysicManager;
}

void VPhysicManagerPart::OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer != 0 )
		{
			in_pAnswer->AddProperty("Gravity", m_pPhysicManager->GetWorld()->GetGravity());
			in_pAnswer->AddProperty("ObjectCount", m_pPhysicManager->GetPhysicObjectCount());
			in_pAnswer->AddProperty("UpdateStep", m_pPhysicManager->GetWorld()->GetWorldStep());
			in_pAnswer->AddProperty("MaxContacts", m_pPhysicManager->GetWorld()->GetSpace()->GetMaxNumContacts());
			in_pAnswer->AddProperty("ContactMode", m_pPhysicManager->GetWorld()->GetSpace()->GetContactMode());
			in_pAnswer->AddProperty("SurfaceMu", m_pPhysicManager->GetWorld()->GetSpace()->GetSurfaceMu());
			in_pAnswer->AddProperty("SurfaceMu2", m_pPhysicManager->GetWorld()->GetSpace()->GetSurfaceMu2());
			in_pAnswer->AddProperty("Slip1", m_pPhysicManager->GetWorld()->GetSpace()->GetSlip1());
			in_pAnswer->AddProperty("Slip2", m_pPhysicManager->GetWorld()->GetSpace()->GetSlip2());
			in_pAnswer->AddProperty("SoftERP", m_pPhysicManager->GetWorld()->GetSpace()->GetSoftERP());
			in_pAnswer->AddProperty("SoftCFM", m_pPhysicManager->GetWorld()->GetSpace()->GetSoftCFM());
			in_pAnswer->AddProperty("SurfaceBounce", m_pPhysicManager->GetWorld()->GetSpace()->GetSurfaceBounce());
			in_pAnswer->AddProperty("SurfaceBounceVelocity", m_pPhysicManager->GetWorld()->GetSpace()->GetSurfaceBounceVelocity());
			in_pAnswer->AddProperty("SurfaceMotion1", m_pPhysicManager->GetWorld()->GetSpace()->GetSurfaceMotion1());
			in_pAnswer->AddProperty("SurfaceMotion2", m_pPhysicManager->GetWorld()->GetSpace()->GetSurfaceMotion2());
		}
	}
	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");
		//const string val = in_pAnswer->GetAs<string>("value");

		if( name == "Gravity" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			m_pPhysicManager->GetWorld()->SetGravity(pos.GetX(), pos.GetY(), pos.GetZ());

			vout << "Physics: gravity set to " << pos << vendl;
		}

		if( name == "UpdateStep" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			//m_pPhysicManager->GetWorld()->SetWorldStep(pos);

			//vout << "Physics: world update step size set to " << pos << vendl;
		}

		if( name == "SurfaceMu" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_pPhysicManager->GetWorld()->GetSpace()->SetSurfaceMu(pos);

			vout << "Physics: space surface mu size set to " << pos << vendl;
		}

		if( name == "SurfaceMu2" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_pPhysicManager->GetWorld()->GetSpace()->SetSurfaceMu2(pos);

			vout << "Physics: space surface mu2 size set to " << pos << vendl;
		}

		if( name == "Slip1" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_pPhysicManager->GetWorld()->GetSpace()->SetSlip1(pos);

			vout << "Physics: space slip1 size set to " << pos << vendl;
		}

		if( name == "Slip2" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_pPhysicManager->GetWorld()->GetSpace()->SetSlip2(pos);

			vout << "Physics: space slip2 size set to " << pos << vendl;
		}

		if( name == "SoftERP" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_pPhysicManager->GetWorld()->GetSpace()->SetSoftERP(pos);

			vout << "Physics: space softERP size set to " << pos << vendl;
		}

		if( name == "SoftCFM" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_pPhysicManager->GetWorld()->GetSpace()->SetSoftCFM(pos);

			vout << "Physics: space softCFM size set to " << pos << vendl;
		}

		if( name == "SurfaceBounce" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_pPhysicManager->GetWorld()->GetSpace()->SetSurfaceBounce(pos);

			vout << "Physics: space surface bounce size set to " << pos << vendl;
		}

		if( name == "SurfaceBounceVelocity" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_pPhysicManager->GetWorld()->GetSpace()->SetSurfaceBounceVelocity(pos);

			vout << "Physics: space surface bounce velocity size set to " << pos << vendl;
		}

		if( name == "SurfaceMotion1" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_pPhysicManager->GetWorld()->GetSpace()->SetSurfaceMotion1(pos);

			vout << "Physics: space surface motion 1 set to " << pos << vendl;
		}

		if( name == "SurfaceMotion2" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_pPhysicManager->GetWorld()->GetSpace()->SetSurfaceMotion2(pos);

			vout << "Physics: space surface motion 2 set to " << pos << vendl;
		}
	}
}


namespace {
	entity::VPartParser<VPhysicManagerPart> parser;
}


//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------
