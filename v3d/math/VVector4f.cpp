#include <Math/VVector4f.h>

VVector4f::VVector4f(void)
{
	m_pfVector[0] = 0.0f;
	m_pfVector[1] = 0.0f;
	m_pfVector[2] = 0.0f;
	m_pfVector[3] = 1.0f;
}

VVector4f::VVector4f(const vfloat32 in_fX, const vfloat32 in_fY, const vfloat32 in_fZ, const vfloat32 in_fW)
{
	m_pfVector[0] = in_fX;
	m_pfVector[1] = in_fY;
	m_pfVector[2] = in_fZ;
	m_pfVector[3] = in_fW;
}

VVector4f::VVector4f(const vfloat32 in_pfV[])
{
	m_pfVector[0] = in_pfV[0];
	m_pfVector[1] = in_pfV[1];
	m_pfVector[2] = in_pfV[2];
	m_pfVector[3] = in_pfV[3];
}

VVector4f::VVector4f(const VVector4f& in_rV)
{
	m_pfVector[0] = in_rV.m_pfVector[0];
	m_pfVector[1] = in_rV.m_pfVector[1];
	m_pfVector[2] = in_rV.m_pfVector[2];
	m_pfVector[3] = in_rV.m_pfVector[3];
}