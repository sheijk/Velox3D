#include <v3dLib/Physics/VPhysicGeometry.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VPhysicGeometry::VPhysicGeometry()
{
	m_GeomID = 0;
	m_bIsEnabled = true;
	m_CategoryGroup = 0;
	m_CollisionGroup = 0;
}

VPhysicGeometry::~VPhysicGeometry()
{
}

void VPhysicGeometry::Destroy()
{
	dGeomDestroy(m_GeomID);
}

dGeomID* VPhysicGeometry::GetGeomID()
{
	return &m_GeomID;
}

void VPhysicGeometry::Enable()
{
	dGeomEnable(m_GeomID);
	m_bIsEnabled = true;
}

void VPhysicGeometry::Disable()
{
	dGeomDisable(m_GeomID);
	m_bIsEnabled = false;
}

vbool VPhysicGeometry::IsEnabled()
{
	return m_bIsEnabled;
}

void VPhysicGeometry::SetCategoryGroup(Group in_CategoryGroup)
{
    m_CategoryGroup = in_CategoryGroup;

	dGeomSetCategoryBits(m_GeomID,m_CategoryGroup);
}

void VPhysicGeometry::SetCollisionGroup(Group in_CollisionGroup)
{
	m_CollisionGroup = in_CollisionGroup;
	dGeomSetCollideBits (m_GeomID,m_CollisionGroup);
}

vint VPhysicGeometry::GetCategoryGroup()
{
	m_CategoryGroup =  dGeomGetCategoryBits(m_GeomID);	
	return m_CategoryGroup;
}

vint VPhysicGeometry::GetCollisionGroup()
{
	m_CollisionGroup =  dGeomGetCollideBits(m_GeomID);
	return m_CollisionGroup;
}

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
