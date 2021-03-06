/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VGeometrySphere.h>
#include <V3d/Physics/VSpace.h>
#include <V3d/Core.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VGeometrySphere::VGeometrySphere()
{
}

VGeometrySphere::~VGeometrySphere()
{
}

void VGeometrySphere::CreateSphere(VSpace* in_SpaceState)
{
	V3D_ASSERT(in_SpaceState != 0);
	m_GeomID = dCreateSphere (*in_SpaceState->GetSpaceID(), m_fRadius);
}

void VGeometrySphere::SetSphereRadius(vfloat32 in_fRadius)
{
	m_fRadius = in_fRadius;
}

vfloat32 VGeometrySphere::GetSphereRadius()
{
	return m_fRadius;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

