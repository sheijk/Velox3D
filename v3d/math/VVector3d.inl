inline vfloat64& VVector3d::operator [] (const vint in_iIndex) const
{
	return ((vfloat64*)this)[in_iIndex];
}

inline VVector3d& VVector3d::Set(const vfloat64 in_dX, const vfloat64 in_dY, const vfloat64 in_dZ)
{
	m_pdVector[0] = in_dX;
	m_pdVector[1] = in_dY;
	m_pdVector[2] = in_dZ;

	return *this;
}

inline VVector3d& VVector3d::operator = (const vfloat64 in_pdV[])
{
	m_pdVector[0] = in_pdV[0];
	m_pdVector[1] = in_pdV[1];
	m_pdVector[2] = in_pdV[2];

	return *this;
}

inline VVector3d& VVector3d::operator = (const VVector3d& in_rV)
{
	m_pdVector[0] = in_rV.m_pdVector[0];
	m_pdVector[1] = in_rV.m_pdVector[1];
	m_pdVector[2] = in_rV.m_pdVector[2];

	return *this;
}

inline vbool VVector3d::operator == (const vfloat64 in_pdV[]) const
{
	return (m_pdVector[0] == in_pdV[0] &&
			m_pdVector[1] == in_pdV[1] &&
			m_pdVector[2] == in_pdV[2]);
}

inline vbool VVector3d::operator == (const VVector3d& in_rV) const
{
	return (m_pdVector[0] == in_rV.m_pdVector[0] &&
			m_pdVector[1] == in_rV.m_pdVector[1] &&
			m_pdVector[2] == in_rV.m_pdVector[2]);
}

inline vbool VVector3d::operator != (const vfloat64 in_pdV[]) const
{
	return (m_pdVector[0] != in_pdV[0] ||
			m_pdVector[1] != in_pdV[1] ||
			m_pdVector[2] != in_pdV[2]);
}

inline vbool VVector3d::operator != (const VVector3d& in_rV) const
{
	return (m_pdVector[0] != in_rV.m_pdVector[0] ||
			m_pdVector[1] != in_rV.m_pdVector[1] ||
			m_pdVector[2] != in_rV.m_pdVector[2]);
}

inline VVector3d& VVector3d::Add(const VVector3d& in_rV, const vfloat64 in_dS)
{
	m_pdVector[0] = in_rV.m_pdVector[0] + in_dS;
	m_pdVector[1] = in_rV.m_pdVector[1] + in_dS;
	m_pdVector[2] = in_rV.m_pdVector[2] + in_dS;

	return *this;
}

inline VVector3d& VVector3d::Subtract(const VVector3d& in_rV, const vfloat64 in_dS)
{
	m_pdVector[0] = in_rV.m_pdVector[0] - in_dS;
	m_pdVector[1] = in_rV.m_pdVector[1] - in_dS;
	m_pdVector[2] = in_rV.m_pdVector[2] - in_dS;

	return *this;
}

inline VVector3d& VVector3d::Multiply(const VVector3d& in_rV, const vfloat64 in_dS)
{
	m_pdVector[0] = in_rV.m_pdVector[0] * in_dS;
	m_pdVector[1] = in_rV.m_pdVector[1] * in_dS;
	m_pdVector[2] = in_rV.m_pdVector[2] * in_dS;

	return *this;
}

inline VVector3d& VVector3d::Divide(const VVector3d& in_rV, const vfloat64 in_dS)
{
	m_pdVector[0] = in_rV.m_pdVector[0] / in_dS;
	m_pdVector[1] = in_rV.m_pdVector[1] / in_dS;
	m_pdVector[2] = in_rV.m_pdVector[2] / in_dS;

	return *this;
}

inline VVector3d& VVector3d::Add(const VVector3d& in_rA, const VVector3d& in_rB)
{
	m_pdVector[0] = in_rA.m_pdVector[0] + in_rB.m_pdVector[0];
	m_pdVector[1] = in_rA.m_pdVector[1] + in_rB.m_pdVector[1];
	m_pdVector[2] = in_rA.m_pdVector[2] + in_rB.m_pdVector[2];

	return *this;
}

inline VVector3d& VVector3d::Subtract(const VVector3d& in_rA, const VVector3d& in_rB)
{
	m_pdVector[0] = in_rA.m_pdVector[0] - in_rB.m_pdVector[0];
	m_pdVector[1] = in_rA.m_pdVector[1] - in_rB.m_pdVector[1];
	m_pdVector[2] = in_rA.m_pdVector[2] - in_rB.m_pdVector[2];

	return *this;
}

inline VVector3d VVector3d::operator + (const vfloat64 in_dS) const
{
	return VVector3d(m_pdVector[0] + in_dS,
					 m_pdVector[1] + in_dS,
					 m_pdVector[2] + in_dS);
}

inline VVector3d VVector3d::operator + (const vfloat64 in_pdV[]) const
{
	return VVector3d(m_pdVector[0] + in_pdV[0],
					 m_pdVector[1] + in_pdV[1],
					 m_pdVector[2] + in_pdV[2]);
}

inline VVector3d VVector3d::operator + (const VVector3d& in_rV) const
{
	return VVector3d(m_pdVector[0] + in_rV.m_pdVector[0],
					 m_pdVector[1] + in_rV.m_pdVector[1],
					 m_pdVector[2] + in_rV.m_pdVector[2]);
}

inline VVector3d VVector3d::operator - (const vfloat64 in_dS) const
{
	return VVector3d(m_pdVector[0] - in_dS,
					 m_pdVector[1] - in_dS,
					 m_pdVector[2] - in_dS);
}

inline VVector3d VVector3d::operator - (const vfloat64 in_pdV[]) const
{
	return VVector3d(m_pdVector[0] - in_pdV[0],
					 m_pdVector[1] - in_pdV[1],
					 m_pdVector[2] - in_pdV[2]);
}

inline VVector3d VVector3d::operator - (const VVector3d& in_rV) const
{
	return VVector3d(m_pdVector[0] - in_rV.m_pdVector[0],
					 m_pdVector[1] - in_rV.m_pdVector[1],
					 m_pdVector[2] - in_rV.m_pdVector[2]);
}

inline VVector3d VVector3d::operator * (const vfloat64 in_dS) const
{
	return VVector3d(m_pdVector[0] * in_dS,
					 m_pdVector[1] * in_dS,
					 m_pdVector[2] * in_dS);
}

inline VVector3d VVector3d::operator * (const vfloat64 in_pdV[]) const
{
	return VVector3d(m_pdVector[0] * in_pdV[0],
					 m_pdVector[1] * in_pdV[1],
					 m_pdVector[2] * in_pdV[2]);
}

inline VVector3d VVector3d::operator * (const VVector3d& in_rV) const
{
	return VVector3d(m_pdVector[0] * in_rV.m_pdVector[0],
					 m_pdVector[1] * in_rV.m_pdVector[1],
					 m_pdVector[2] * in_rV.m_pdVector[2]);
}

inline VVector3d VVector3d::operator / (const vfloat64 in_dS) const
{
	return VVector3d(m_pdVector[0] / in_dS,
					 m_pdVector[1] / in_dS,
					 m_pdVector[2] / in_dS);
}

inline VVector3d VVector3d::operator / (const vfloat64 in_pdV[]) const
{
	return VVector3d(m_pdVector[0] / in_pdV[0],
					 m_pdVector[1] / in_pdV[1],
					 m_pdVector[2] / in_pdV[2]);
}

inline VVector3d VVector3d::operator / (const VVector3d& in_rV) const
{
	return VVector3d(m_pdVector[0] / in_rV.m_pdVector[0],
					 m_pdVector[1] / in_rV.m_pdVector[1],
					 m_pdVector[2] / in_rV.m_pdVector[2]);
}

inline VVector3d& VVector3d::operator += (const vfloat64 in_dS)
{
	m_pdVector[0] += in_dS;
	m_pdVector[1] += in_dS;
	m_pdVector[2] += in_dS;

	return *this;
}

inline VVector3d& VVector3d::operator += (const vfloat64 in_pdV[])
{
	m_pdVector[0] += in_pdV[0];
	m_pdVector[1] += in_pdV[1];
	m_pdVector[2] += in_pdV[2];

	return *this;
}

inline VVector3d& VVector3d::operator += (const VVector3d& in_rV)
{
	m_pdVector[0] += in_rV.m_pdVector[0];
	m_pdVector[1] += in_rV.m_pdVector[1];
	m_pdVector[2] += in_rV.m_pdVector[2];

	return *this;
}

inline VVector3d& VVector3d::operator -= (const vfloat64 in_dS)
{
	m_pdVector[0] -= in_dS;
	m_pdVector[1] -= in_dS;
	m_pdVector[2] -= in_dS;

	return *this;
}

inline VVector3d& VVector3d::operator -= (const vfloat64 in_pdV[])
{
	m_pdVector[0] -= in_pdV[0];
	m_pdVector[1] -= in_pdV[1];
	m_pdVector[2] -= in_pdV[2];

	return *this;
}

inline VVector3d& VVector3d::operator -= (const VVector3d& in_rV)
{
	m_pdVector[0] -= in_rV.m_pdVector[0];
	m_pdVector[1] -= in_rV.m_pdVector[1];
	m_pdVector[2] -= in_rV.m_pdVector[2];

	return *this;
}

inline VVector3d& VVector3d::operator *= (const vfloat64 in_dS)
{
	m_pdVector[0] *= in_dS;
	m_pdVector[1] *= in_dS;
	m_pdVector[2] *= in_dS;

	return *this;
}

inline VVector3d& VVector3d::operator *= (const vfloat64 in_pdV[])
{
	m_pdVector[0] *= in_pdV[0];
	m_pdVector[1] *= in_pdV[1];
	m_pdVector[2] *= in_pdV[2];

	return *this;
}

inline VVector3d& VVector3d::operator *= (const VVector3d& in_rV)
{
	m_pdVector[0] *= in_rV.m_pdVector[0];
	m_pdVector[1] *= in_rV.m_pdVector[1];
	m_pdVector[2] *= in_rV.m_pdVector[2];

	return *this;
}

inline VVector3d& VVector3d::operator /= (const vfloat64 in_dS)
{
	m_pdVector[0] /= in_dS;
	m_pdVector[1] /= in_dS;
	m_pdVector[2] /= in_dS;

	return *this;
}

inline VVector3d& VVector3d::operator /= (const vfloat64 in_pdV[])
{
	m_pdVector[0] /= in_pdV[0];
	m_pdVector[1] /= in_pdV[1];
	m_pdVector[2] /= in_pdV[2];

	return *this;
}

inline VVector3d& VVector3d::operator /= (const VVector3d& in_rV)
{
	m_pdVector[0] /= in_rV.m_pdVector[0];
	m_pdVector[1] /= in_rV.m_pdVector[1];
	m_pdVector[2] /= in_rV.m_pdVector[2];

	return *this;
}

inline vfloat64 VVector3d::Magnitude(void) const 
{
	return sqrt(m_pdVector[0] * m_pdVector[0] + 
				m_pdVector[1] * m_pdVector[1] + 
				m_pdVector[2] * m_pdVector[2]); 
}

inline vfloat64 VVector3d::MagnitudeSquared(void) const 
{
	return (m_pdVector[0] * m_pdVector[0] + 
			m_pdVector[1] * m_pdVector[1] + 
			m_pdVector[2] * m_pdVector[2]);
}

inline VVector3d& VVector3d::Normalize(void)
{ 
	return *this /= Magnitude(); 
}
	
inline VVector3d& VVector3d::Normalize(const VVector3d& in_rV) 
{ 
	return Divide(in_rV, in_rV.Magnitude());
}

inline vfloat64 VVector3d::Dot(const VVector3d& in_rV) const
{
	return (m_pdVector[0] * in_rV.m_pdVector[0] +
			m_pdVector[1] * in_rV.m_pdVector[1] + 
			m_pdVector[2] * in_rV.m_pdVector[2]);
}

inline VVector3d VVector3d::Cross(const VVector3d& in_rV) const
{
	return VVector3d(m_pdVector[1] * in_rV.m_pdVector[2] - m_pdVector[2] * in_rV.m_pdVector[1],
					 m_pdVector[2] * in_rV.m_pdVector[0] - m_pdVector[0] * in_rV.m_pdVector[2],
					 m_pdVector[0] * in_rV.m_pdVector[1] - m_pdVector[1] * in_rV.m_pdVector[0]);
}

inline VVector3d& VVector3d::Cross(const VVector3d& in_rA, const VVector3d& in_rB)
{
	m_pdVector[0] = in_rA.m_pdVector[1] * in_rB.m_pdVector[2] - in_rA.m_pdVector[2] * in_rB.m_pdVector[1];
	m_pdVector[1] = in_rA.m_pdVector[2] * in_rB.m_pdVector[0] - in_rA.m_pdVector[0] * in_rB.m_pdVector[2];
	m_pdVector[2] = in_rA.m_pdVector[0] * in_rB.m_pdVector[1] - in_rA.m_pdVector[1] * in_rB.m_pdVector[0];

	return *this;
}

inline void VVector3d::Random(void)
{
    m_pdVector[2] = VMath::Rand(-1.0f, 1.0f);
    vfloat64 dA = VMath::Rand(0.0f, 6.283185307179586476925286766559f);

    vfloat64 dR = sqrt(1.0 - m_pdVector[2] * m_pdVector[2]);

    m_pdVector[0] = dR * cos(dA);
    m_pdVector[1] = dR * sin(dA);
}