//-----------------------------------------------------------------------------
#include <v3d/Graphics/VCamera.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VCamera::VCamera(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_pPosition[0] = x;
	m_pPosition[1] = y;
	m_pPosition[2] = z;

	rotX = 0;
	rotY = 0;
}
//-----------------------------------------------------------------------------
VCamera::VCamera()
{
	m_pPosition[0] = 0;
	m_pPosition[1] = 0;
	m_pPosition[2] = 0;

	rotX = 0;
	rotY = 0;
}
//-----------------------------------------------------------------------------

vfloat32 VCamera::GetX()
{
	return m_pPosition[0];
}
//-----------------------------------------------------------------------------

vfloat32 VCamera::GetY()
{
	return m_pPosition[1];
}
//-----------------------------------------------------------------------------

vfloat32 VCamera::GetZ()
{
	return m_pPosition[2];
}

//-----------------------------------------------------------------------------
void VCamera::SetX(vfloat32 x)
{
	m_pPosition[0] = x;
}
//-----------------------------------------------------------------------------

void VCamera::SetY(vfloat32 y)
{
	m_pPosition[1] = y;

}
//-----------------------------------------------------------------------------

void VCamera::SetZ(vfloat32 z)
{
	m_pPosition[2] = z;
}

//-----------------------------------------------------------------------------
void VCamera::AddX(vfloat32 x)
{
	m_pPosition[0] += x;
}

//-----------------------------------------------------------------------------
void VCamera::AddY(vfloat32 y)
{
	m_pPosition[1] += y;
}

//-----------------------------------------------------------------------------

void VCamera::AddZ(vfloat32 z)
{
	m_pPosition[2] += z;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------