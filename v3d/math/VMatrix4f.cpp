#include <Math/VMatrix4f.h>

VMatrix4f::VMatrix4f(void)
{
	m_pfMatrix[0][0] = 1.0f; m_pfMatrix[0][1] = 0.0f; m_pfMatrix[0][2] = 0.0f; m_pfMatrix[0][3] = 0.0f;
	m_pfMatrix[1][0] = 0.0f; m_pfMatrix[1][1] = 1.0f; m_pfMatrix[1][2] = 0.0f; m_pfMatrix[1][3] = 0.0f;
	m_pfMatrix[2][0] = 0.0f; m_pfMatrix[2][1] = 0.0f; m_pfMatrix[2][2] = 1.0f; m_pfMatrix[2][3] = 0.0f;
	m_pfMatrix[3][0] = 0.0f; m_pfMatrix[3][1] = 0.0f; m_pfMatrix[3][2] = 0.0f; m_pfMatrix[3][3] = 1.0f;
}

VMatrix4f::VMatrix4f(const vfloat32 in_fM11, const vfloat32 in_fM12, const vfloat32 in_fM13, const vfloat32 in_fM14,
					 const vfloat32 in_fM21, const vfloat32 in_fM22, const vfloat32 in_fM23, const vfloat32 in_fM24,
					 const vfloat32 in_fM31, const vfloat32 in_fM32, const vfloat32 in_fM33, const vfloat32 in_fM34,
					 const vfloat32 in_fM41, const vfloat32 in_fM42, const vfloat32 in_fM43, const vfloat32 in_fM44)
{
	m_pfMatrix[0][0] = in_fM11;
	m_pfMatrix[0][1] = in_fM12;
	m_pfMatrix[0][2] = in_fM13;
	m_pfMatrix[0][3] = in_fM14;
	m_pfMatrix[1][0] = in_fM21;
	m_pfMatrix[1][1] = in_fM22;
	m_pfMatrix[1][2] = in_fM23;
	m_pfMatrix[1][3] = in_fM24;
	m_pfMatrix[2][0] = in_fM31;
	m_pfMatrix[2][1] = in_fM32;
	m_pfMatrix[2][2] = in_fM33;
	m_pfMatrix[2][3] = in_fM34;
	m_pfMatrix[3][0] = in_fM41;
	m_pfMatrix[3][1] = in_fM42;
	m_pfMatrix[3][2] = in_fM43;
	m_pfMatrix[3][3] = in_fM44;
}

VMatrix4f::VMatrix4f(const vfloat32 in_pfMatrix[])
{
	m_pfMatrix[0][0] = in_pfMatrix[ 0];
	m_pfMatrix[0][1] = in_pfMatrix[ 1];
	m_pfMatrix[0][2] = in_pfMatrix[ 2];
	m_pfMatrix[0][3] = in_pfMatrix[ 3];
	m_pfMatrix[1][0] = in_pfMatrix[ 4];
	m_pfMatrix[1][1] = in_pfMatrix[ 5];
	m_pfMatrix[1][2] = in_pfMatrix[ 6];
	m_pfMatrix[1][3] = in_pfMatrix[ 7];
	m_pfMatrix[2][0] = in_pfMatrix[ 8];
	m_pfMatrix[2][1] = in_pfMatrix[ 9];
	m_pfMatrix[2][2] = in_pfMatrix[10];
	m_pfMatrix[2][3] = in_pfMatrix[11];
	m_pfMatrix[3][0] = in_pfMatrix[12];
	m_pfMatrix[3][1] = in_pfMatrix[13];
	m_pfMatrix[3][2] = in_pfMatrix[14];
	m_pfMatrix[3][3] = in_pfMatrix[15];
}

VMatrix4f::VMatrix4f(const VMatrix4f& in_rMatrix)
{
	m_pfMatrix[0][0] = in_rMatrix.m_pfMatrix[0][0];
	m_pfMatrix[0][1] = in_rMatrix.m_pfMatrix[0][1];
	m_pfMatrix[0][2] = in_rMatrix.m_pfMatrix[0][2];
	m_pfMatrix[0][3] = in_rMatrix.m_pfMatrix[0][3];
	m_pfMatrix[1][0] = in_rMatrix.m_pfMatrix[1][0];
	m_pfMatrix[1][1] = in_rMatrix.m_pfMatrix[1][1];
	m_pfMatrix[1][2] = in_rMatrix.m_pfMatrix[1][2];
	m_pfMatrix[1][3] = in_rMatrix.m_pfMatrix[1][3];
	m_pfMatrix[2][0] = in_rMatrix.m_pfMatrix[2][0];
	m_pfMatrix[2][1] = in_rMatrix.m_pfMatrix[2][1];
	m_pfMatrix[2][2] = in_rMatrix.m_pfMatrix[2][2];
	m_pfMatrix[2][3] = in_rMatrix.m_pfMatrix[2][3];
	m_pfMatrix[3][0] = in_rMatrix.m_pfMatrix[3][0];
	m_pfMatrix[3][1] = in_rMatrix.m_pfMatrix[3][1];
	m_pfMatrix[3][2] = in_rMatrix.m_pfMatrix[3][2];
	m_pfMatrix[3][3] = in_rMatrix.m_pfMatrix[3][3];
}