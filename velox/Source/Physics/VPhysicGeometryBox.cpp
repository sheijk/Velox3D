#include <v3dLib/Physics/VPhysicGeometryBox.h>
#include <v3dLib/Physics/VPhysicSpace.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VPhysicGeometryBox::VPhysicGeometryBox()
{
	m_fLength	= 1.0f;
	m_fWidth	= 1.0f;
	m_fHeight	= 1.0f;
}

VPhysicGeometryBox::~VPhysicGeometryBox()
{
}

void VPhysicGeometryBox::CreateBox(VPhysicSpace* in_SpaceState)
{
	m_GeomID = dCreateBox (*in_SpaceState->GetSpaceID(), m_fLength,
							m_fWidth, m_fHeight);
}

void VPhysicGeometryBox::SetWidth(vfloat32 in_fWidth)
{
	m_fWidth = in_fWidth;
}

void VPhysicGeometryBox::SetLength(vfloat32 in_fLength)
{
	m_fLength = in_fLength;
}

void VPhysicGeometryBox::SetHeight(vfloat32 in_fHeight)
{
	m_fHeight = in_fHeight;
}

vfloat32 VPhysicGeometryBox::GetWidth()
{
	return m_fWidth;
}

vfloat32 VPhysicGeometryBox::GetLength()
{
	return m_fLength;
}

vfloat32 VPhysicGeometryBox::GetHeight()
{
	return m_fHeight;
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
