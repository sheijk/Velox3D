#include <Math/VVector3f.h>

VVector3f::VVector3f(void)
{
	m_pfVector[0] = 0.0f; 
	m_pfVector[1] = 0.0f;
	m_pfVector[2] = 0.0f;
}

VVector3f::VVector3f(const vfloat32 in_fX, const vfloat32 in_fY, const vfloat32 in_fZ)
{
	m_pfVector[0] = in_fX; 
	m_pfVector[1] = in_fY;
	m_pfVector[2] = in_fZ;
}

VVector3f::VVector3f(const vfloat32 in_pfV[])
{
	m_pfVector[0] = in_pfV[0]; 
	m_pfVector[1] = in_pfV[1]; 
	m_pfVector[2] = in_pfV[2];
}

VVector3f::VVector3f(const VVector3f& in_rV)
{
	m_pfVector[0] = in_rV.m_pfVector[0]; 
	m_pfVector[1] = in_rV.m_pfVector[1]; 
	m_pfVector[2] = in_rV.m_pfVector[2];
}