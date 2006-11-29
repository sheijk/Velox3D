/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VGeometryCappedCylinder.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace  physics { 
//-----------------------------------------------------------------------------
using namespace v3d;

VGeometryCappedCylinder::VGeometryCappedCylinder(
  vfloat32 in_fLength /* = 1.0f */, vfloat32 in_fRadius /* = 1.0f */)
{
	m_fRadius = in_fRadius;
	m_fLength = in_fLength;
}

VGeometryCappedCylinder::~VGeometryCappedCylinder()
{
}

vfloat32 VGeometryCappedCylinder::GetLength()
{
  return m_fLength;
}

vfloat32 VGeometryCappedCylinder::GetRadius()
{
  return m_fRadius;
}

void VGeometryCappedCylinder::CreateCylinder(VSpace* in_pSpace)
{
  V3D_ASSERT(in_pSpace != 0);
  m_GeomID = dCreateCCylinder (*in_pSpace->GetSpaceID(), m_fRadius, m_fLength);
}

void VGeometryCappedCylinder::SetParams(vfloat32 in_fLength, vfloat32 in_fRadius)
{
  m_fLength = in_fLength;
  m_fRadius = in_fRadius;
  dGeomCCylinderSetParams(m_GeomID, m_fRadius, m_fLength);
}
//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------

