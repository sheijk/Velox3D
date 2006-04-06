#include <v3d/Physics/VGeometryBox.h>
#include <v3d/Physics/VSpace.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VGeometryBox::VGeometryBox()
{
	m_fLength	= 1.0f;
	m_fWidth	= 1.0f;
	m_fHeight	= 1.0f;
}

VGeometryBox::~VGeometryBox()
{
}

void VGeometryBox::CreateBox(VSpace* in_SpaceState)
{
	m_GeomID = dCreateBox (*in_SpaceState->GetSpaceID(), m_fLength,
							m_fWidth, m_fHeight);
}

void VGeometryBox::SetWidth(vfloat32 in_fWidth)
{
	m_fWidth = in_fWidth;
}

void VGeometryBox::SetLength(vfloat32 in_fLength)
{
	m_fLength = in_fLength;
}

void VGeometryBox::SetHeight(vfloat32 in_fHeight)
{
	m_fHeight = in_fHeight;
}

vfloat32 VGeometryBox::GetWidth()
{
	return m_fWidth;
}

vfloat32 VGeometryBox::GetLength()
{
	return m_fLength;
}

vfloat32 VGeometryBox::GetHeight()
{
	return m_fHeight;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
