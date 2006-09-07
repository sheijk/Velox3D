/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Physics/VWorld.h>
#include <v3d/Physics/VBody.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
using namespace math;

VWorld::VWorld()
{
	m_Gravity.x = 0;
	m_Gravity.y = -0.5f;
	m_Gravity.z = 0;
	m_fWorldStep = 0.05f;

	m_WorldID = dWorldCreate();
	
	m_Space.SetWorld(this);
	m_Space.SetJointGroup(&m_JointGroup);
	SetGravity(m_Gravity);
}

VWorld::~VWorld()
{
	Destroy();
}

void VWorld::SetGravity(graphics::VVertex3f in_Gravity)
{
	m_Gravity = in_Gravity;
	dWorldSetGravity(m_WorldID, m_Gravity.x, m_Gravity.y, m_Gravity.z);
}

void VWorld::SetGravity(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Gravity.x = x;
	m_Gravity.y = y;
	m_Gravity.z = z;

	dWorldSetGravity(m_WorldID ,m_Gravity.x,m_Gravity.y,m_Gravity.z);
}

dWorldID* VWorld::GetWorld()
{
	return &m_WorldID;
}

void VWorld::SetWorldStep(vfloat32 in_fStep)
{
	m_fWorldStep = in_fStep;
}

vfloat32 VWorld::GetWorldStep()
{
	return m_fWorldStep;
}

VSpace* VWorld::GetSpace()
{
	return &m_Space;
}

VJointGroup* VWorld::GetJointGroup()
{
	return &m_JointGroup;
}
void VWorld::Update()
{
	m_Space.Collide();
	dWorldQuickStep(m_WorldID, m_fWorldStep); 
	m_JointGroup.Empty();
}

void VWorld::Destroy()
{
	m_JointGroup.Destroy();
	m_Space.Destroy();
	dWorldDestroy(m_WorldID);
}

void VWorld::RemoveCollisionMesh(dGeomID in_GeomId)
{
	dSpaceRemove(*m_Space.GetSpaceID(), in_GeomId);
}

VVector3f VWorld::GetGravity()
{
	return VVector3f(m_Gravity.x, m_Gravity.y, m_Gravity.z);
}

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

