#include <Math/VVector3d.h>

VVector3d::VVector3d(void)
{
	m_pdVector[0] = 0.0;
	m_pdVector[1] = 0.0;
	m_pdVector[2] = 0.0;
}

VVector3d::VVector3d(const vfloat64 in_dX, const vfloat64 in_dY, const vfloat64 in_dZ)
{
	m_pdVector[0] = in_dX;
	m_pdVector[1] = in_dY;
	m_pdVector[2] = in_dZ;
}

VVector3d::VVector3d(const vfloat64* in_pdVector)
{
	m_pdVector[0] = in_pdVector[0];
	m_pdVector[1] = in_pdVector[1];
	m_pdVector[2] = in_pdVector[2];
}

VVector3d::VVector3d(const VVector3d& in_rVector)
{
	m_pdVector[0] = in_rVector.m_pdVector[0];
	m_pdVector[1] = in_rVector.m_pdVector[1];
	m_pdVector[2] = in_rVector.m_pdVector[2];
}