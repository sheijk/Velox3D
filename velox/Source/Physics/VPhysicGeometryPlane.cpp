#include <v3dLib/Physics/VPhysicGeometryPlane.h>
#include <v3dLib/Physics/VPhysicSpace.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VPhysicGeometryPlane::VPhysicGeometryPlane()
{
	m_fDistance = 0;
}

VPhysicGeometryPlane::~VPhysicGeometryPlane()
{
}

void VPhysicGeometryPlane::CreatePlane(VPhysicSpace* in_SpaceState)
{
	m_GeomID = dCreatePlane (*in_SpaceState->GetSpaceID(), m_Normal.x, m_Normal.y, m_Normal.z, m_fDistance);
}

void VPhysicGeometryPlane::SetPlane(graphics::VVertex3f in_Normal,
								   vfloat32 in_fDistance)
{
	m_Normal = in_Normal;
	m_fDistance = in_fDistance;
}

vfloat32 VPhysicGeometryPlane::GetPlaneDistance()
{
	return m_fDistance;
}

graphics::VVertex3f VPhysicGeometryPlane::GetPlaneNormal()
{
	return m_Normal;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
