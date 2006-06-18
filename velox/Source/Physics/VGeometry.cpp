#include <v3d/Physics/VGeometry.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VGeometry::VGeometry()
{
	m_GeomID = 0;
	m_bIsEnabled = true;
	m_CategoryGroup = 0;
	m_CollisionGroup = 0;
}

//VGeometry::~VGeometry()
//{
//}

void VGeometry::Destroy()
{
	dGeomDestroy(m_GeomID);
}

dGeomID* VGeometry::GetGeomID()
{
	return &m_GeomID;
}

void VGeometry::Enable()
{
	dGeomEnable(m_GeomID);
	m_bIsEnabled = true;
}

void VGeometry::Disable()
{
	dGeomDisable(m_GeomID);
	m_bIsEnabled = false;
}

vbool VGeometry::IsEnabled()
{
	return m_bIsEnabled;
}

void VGeometry::SetCategoryGroup(Group in_CategoryGroup)
{
    m_CategoryGroup = in_CategoryGroup;

	dGeomSetCategoryBits(m_GeomID,m_CategoryGroup);
}

void VGeometry::SetCollisionGroup(Group in_CollisionGroup)
{
	m_CollisionGroup = in_CollisionGroup;
	dGeomSetCollideBits (m_GeomID,m_CollisionGroup);
}

vint VGeometry::GetCategoryGroup()
{
	m_CategoryGroup =  dGeomGetCategoryBits(m_GeomID);	
	return m_CategoryGroup;
}

vint VGeometry::GetCollisionGroup()
{
	m_CollisionGroup =  dGeomGetCollideBits(m_GeomID);
	return m_CollisionGroup;
}

void VGeometry::SetPosition(VVector3f in_Position)
{
	dGeomSetPosition(
		m_GeomID,
		in_Position[0],
		in_Position[1],
		in_Position[2]
	);
}

void VGeometry::SetOrientation(VQuatf in_Quatf)
{
	dQuaternion quat;
	
	for(vuint i=0; i<4; i++)
		quat[i] = in_Quatf[i];

	dGeomSetQuaternion(
		m_GeomID, quat);
}


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
