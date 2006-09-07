/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Physics/VGeometryPlane.h>
#include <v3d/Physics/VSpace.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VGeometryPlane::VGeometryPlane()
{
	m_fDistance = 0;
}

VGeometryPlane::~VGeometryPlane()
{
}

void VGeometryPlane::CreatePlane(VSpace* in_SpaceState)
{
	m_GeomID = dCreatePlane (*in_SpaceState->GetSpaceID(), m_Normal.x, m_Normal.y, m_Normal.z, m_fDistance);
}

void VGeometryPlane::SetPlane(graphics::VVertex3f in_Normal,
								   vfloat32 in_fDistance)
{
	m_Normal = in_Normal;
	m_fDistance = -in_fDistance;
}

vfloat32 VGeometryPlane::GetPlaneDistance()
{
	return m_fDistance;
}

graphics::VVertex3f VGeometryPlane::GetPlaneNormal()
{
	return m_Normal;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

