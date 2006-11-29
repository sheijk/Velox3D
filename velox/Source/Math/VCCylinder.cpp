/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
#include <V3d/Math/VCCylinder.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace math {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VCCylinder::VCCylinder(vfloat32 in_fLength /* = 1.0f */,
					   vfloat32 in_fRadius /* = 1.0f */)
{
  m_fRadius = in_fRadius;
  m_fLength = in_fLength;
}

VCCylinder::~VCCylinder()
{
}

void VCCylinder::SetParams(v3d::vfloat32 in_fLength, v3d::vfloat32 in_fRadius)
{
  m_fLength = in_fLength;
  m_fRadius = in_fRadius;
}

vfloat32 VCCylinder::GetRadius()
{
  return m_fRadius;
}

vfloat32 VCCylinder::GetLength()
{
  return m_fLength;
}
//-----------------------------------------------------------------------------
}} // namespace v3d::math
//-----------------------------------------------------------------------------

