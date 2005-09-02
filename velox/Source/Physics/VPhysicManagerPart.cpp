#include <v3dLib/Physics/VPhysicManagerPart.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace  physics {
//-----------------------------------------------------------------------------
using namespace v3d;

VPhysicManagerPart::VPhysicManagerPart()
{
}

VPhysicManagerPart::~VPhysicManagerPart()
{
	m_PhysicWorld.Destroy();
}

void VPhysicManagerPart::Activate()
{

}

void VPhysicManagerPart::Deactivate()
{
}

void VPhysicManagerPart::Update()
{
	m_PhysicWorld.Update();
}

VPhysicWorld& VPhysicManagerPart::GetPhysicWorld()
{
	return m_PhysicWorld;
}

std::string VPhysicManagerPart::GetDefaultId()
{
	return "physicManager";
}


//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------
