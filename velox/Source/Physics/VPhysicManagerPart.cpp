#include <v3dLib/Physics/VPhysicManagerPart.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace  physics {
//-----------------------------------------------------------------------------
using namespace v3d;

VPhysicManagerPart::VPhysicManagerPart(
	VPhysicManagerPart::PhysicWorld in_pPhysicWorld)
{
	V3D_ASSERT(in_pPhysicWorld != 0);
	m_pPhysicWorld = in_pPhysicWorld;
}

VPhysicManagerPart::~VPhysicManagerPart()
{
	;//m_PhysicWorld.Destroy();
}

void VPhysicManagerPart::Activate()
{

}

void VPhysicManagerPart::Deactivate()
{
}

void VPhysicManagerPart::Update()
{
}

VPhysicManagerPart::PhysicWorld VPhysicManagerPart::GetPhysicWorld()
{
	return m_pPhysicWorld;
}

std::string VPhysicManagerPart::GetDefaultId()
{
	return "physicManagerPart";
}


//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------
