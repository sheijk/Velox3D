inline VVector4f& VVector4f::Set(const vfloat32 in_fX, const vfloat32 in_fY, const vfloat32 in_fZ,
								 const vfloat32 in_fW)
{
	m_pfVector[0] = in_fX;
	m_pfVector[1] = in_fY;
	m_pfVector[2] = in_fZ;
	m_pfVector[3] = in_fW;

	return *this;
}

inline VVector4f& VVector4f::operator = (const vfloat32 in_pfV[])
{
	m_pfVector[0] = in_pfV[0];
	m_pfVector[1] = in_pfV[1];
	m_pfVector[2] = in_pfV[2];
	m_pfVector[3] = in_pfV[3];

	return *this;
}

inline VVector4f& VVector4f::operator = (const VVector4f& in_rV)
{
	m_pfVector[0] = in_rV.m_pfVector[0];
	m_pfVector[1] = in_rV.m_pfVector[1];
	m_pfVector[2] = in_rV.m_pfVector[2];
	m_pfVector[3] = in_rV.m_pfVector[3];
}

inline VVector4f& VVector4f::operator += (const vfloat32 in_fS)
{
	m_pfVector[0] += in_fS;
	m_pfVector[1] += in_fS;
	m_pfVector[2] += in_fS;
	m_pfVector[3] += in_fS;
	
	return *this;
}

inline VVector4f& VVector4f::operator += (const vfloat32 in_pfV[])
{
	m_pfVector[0] += in_pfV[0];
	m_pfVector[1] += in_pfV[1];
	m_pfVector[2] += in_pfV[2];
	m_pfVector[3] += in_pfV[3];

	return *this;
}

inline VVector4f& VVector4f::operator += (const VVector4f& in_rV)
{
	m_pfVector[0] += in_rV.m_pfVector[0];
	m_pfVector[1] += in_rV.m_pfVector[1];
	m_pfVector[2] += in_rV.m_pfVector[2];
	m_pfVector[3] += in_rV.m_pfVector[3];

	return *this;
}

inline VVector4f& VVector4f::operator -= (const vfloat32 in_fS)
{
	m_pfVector[0] -= in_fS;
	m_pfVector[1] -= in_fS;
	m_pfVector[2] -= in_fS;
	m_pfVector[3] -= in_fS;
	
	return *this;
}

inline VVector4f& VVector4f::operator -= (const vfloat32 in_pfV[])
{
	m_pfVector[0] -= in_pfV[0];
	m_pfVector[1] -= in_pfV[1];
	m_pfVector[2] -= in_pfV[2];
	m_pfVector[3] -= in_pfV[3];

	return *this;
}

inline VVector4f& VVector4f::operator -= (const VVector4f& in_rV)
{
	m_pfVector[0] -= in_rV.m_pfVector[0];
	m_pfVector[1] -= in_rV.m_pfVector[1];
	m_pfVector[2] -= in_rV.m_pfVector[2];
	m_pfVector[3] -= in_rV.m_pfVector[3];

	return *this;
}

inline VVector4f& VVector4f::operator *= (const vfloat32 in_fS)
{
	m_pfVector[0] *= in_fS;
	m_pfVector[1] *= in_fS;
	m_pfVector[2] *= in_fS;
	m_pfVector[3] *= in_fS;
	
	return *this;
}

inline VVector4f& VVector4f::operator *= (const vfloat32 in_pfV[])
{
	m_pfVector[0] *= in_pfV[0];
	m_pfVector[1] *= in_pfV[1];
	m_pfVector[2] *= in_pfV[2];
	m_pfVector[3] *= in_pfV[3];

	return *this;
}

inline VVector4f& VVector4f::operator *= (const VVector4f& in_rV)
{
	m_pfVector[0] *= in_rV.m_pfVector[0];
	m_pfVector[1] *= in_rV.m_pfVector[1];
	m_pfVector[2] *= in_rV.m_pfVector[2];
	m_pfVector[3] *= in_rV.m_pfVector[3];

	return *this;
}

inline VVector4f& VVector4f::operator /= (const vfloat32 in_fS)
{
	m_pfVector[0] /= in_fS;
	m_pfVector[1] /= in_fS;
	m_pfVector[2] /= in_fS;
	m_pfVector[3] /= in_fS;
	
	return *this;
}

inline VVector4f& VVector4f::operator /= (const vfloat32 in_pfV[])
{
	m_pfVector[0] /= in_pfV[0];
	m_pfVector[1] /= in_pfV[1];
	m_pfVector[2] /= in_pfV[2];
	m_pfVector[3] /= in_pfV[3];

	return *this;
}

inline VVector4f& VVector4f::operator /= (const VVector4f& in_rV)
{
	m_pfVector[0] /= in_rV.m_pfVector[0];
	m_pfVector[1] /= in_rV.m_pfVector[1];
	m_pfVector[2] /= in_rV.m_pfVector[2];
	m_pfVector[3] /= in_rV.m_pfVector[3];

	return *this;
}

inline VVector4f VVector4f::operator + (const vfloat32 in_fS) const
{
	return VVector4f(m_pfVector[0] + in_fS,
					 m_pfVector[1] + in_fS,
					 m_pfVector[2] + in_fS,
					 m_pfVector[3] + in_fS);
}

inline VVector4f VVector4f::operator + (const vfloat32 in_pfV[]) const
{
	return VVector4f(m_pfVector[0] + in_pfV[0],
					 m_pfVector[1] + in_pfV[1],
					 m_pfVector[2] + in_pfV[2],
					 m_pfVector[3] + in_pfV[3]);
}

inline VVector4f VVector4f::operator + (const VVector4f& in_rV) const
{
	return VVector4f(m_pfVector[0] + in_rV.m_pfVector[0],
					 m_pfVector[1] + in_rV.m_pfVector[1],
					 m_pfVector[2] + in_rV.m_pfVector[2],
					 m_pfVector[3] + in_rV.m_pfVector[3]);
}

inline VVector4f VVector4f::operator - (const vfloat32 in_fS) const
{
	return VVector4f(m_pfVector[0] - in_fS,
					 m_pfVector[1] - in_fS,
					 m_pfVector[2] - in_fS,
					 m_pfVector[3] - in_fS);
}

inline VVector4f VVector4f::operator - (const vfloat32 in_pfV[]) const
{
	return VVector4f(m_pfVector[0] - in_pfV[0],
					 m_pfVector[1] - in_pfV[1],
					 m_pfVector[2] - in_pfV[2],
					 m_pfVector[3] - in_pfV[3]);
}

inline VVector4f VVector4f::operator - (const VVector4f& in_rV) const
{
	return VVector4f(m_pfVector[0] - in_rV.m_pfVector[0],
					 m_pfVector[1] - in_rV.m_pfVector[1],
					 m_pfVector[2] - in_rV.m_pfVector[2],
					 m_pfVector[3] - in_rV.m_pfVector[3]);
}

inline VVector4f VVector4f::operator * (const vfloat32 in_fS) const
{
	return VVector4f(m_pfVector[0] * in_fS,
					 m_pfVector[1] * in_fS,
					 m_pfVector[2] * in_fS,
					 m_pfVector[3] * in_fS);
}

inline VVector4f VVector4f::operator * (const vfloat32 in_pfV[]) const
{
	return VVector4f(m_pfVector[0] * in_pfV[0],
					 m_pfVector[1] * in_pfV[1],
					 m_pfVector[2] * in_pfV[2],
					 m_pfVector[3] * in_pfV[3]);
}

inline VVector4f VVector4f::operator * (const VVector4f& in_rV) const
{
	return VVector4f(m_pfVector[0] * in_rV.m_pfVector[0],
					 m_pfVector[1] * in_rV.m_pfVector[1],
					 m_pfVector[2] * in_rV.m_pfVector[2],
					 m_pfVector[3] * in_rV.m_pfVector[3]);
}

inline VVector4f VVector4f::operator / (const vfloat32 in_fS) const
{
	return VVector4f(m_pfVector[0] / in_fS,
					 m_pfVector[1] / in_fS,
					 m_pfVector[2] / in_fS,
					 m_pfVector[3] / in_fS);
}

inline VVector4f VVector4f::operator / (const vfloat32 in_pfV[]) const
{
	return VVector4f(m_pfVector[0] / in_pfV[0],
					 m_pfVector[1] / in_pfV[1],
					 m_pfVector[2] / in_pfV[2],
					 m_pfVector[3] / in_pfV[3]);
}

inline VVector4f VVector4f::operator / (const VVector4f& in_rV) const
{
	return VVector4f(m_pfVector[0] / in_rV.m_pfVector[0],
					 m_pfVector[1] / in_rV.m_pfVector[1],
					 m_pfVector[2] / in_rV.m_pfVector[2],
					 m_pfVector[3] / in_rV.m_pfVector[3]);
}

inline vfloat32 VVector4f::Dot(const VVector4f& in_rV) const
{
	return (m_pfVector[0] * in_rV.m_pfVector[0] +
			m_pfVector[1] * in_rV.m_pfVector[1] +
			m_pfVector[2] * in_rV.m_pfVector[2] +
			m_pfVector[3] * in_rV.m_pfVector[3]);
}