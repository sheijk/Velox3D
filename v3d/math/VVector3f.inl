inline vfloat32& VVector3f::operator [] (const vint in_iIndex) const
{
	return ((vfloat32*)this)[in_iIndex];
}

inline VVector3f& VVector3f::operator = (const vfloat32 in_pfV[]) 
{ 
	m_pfVector[0] = in_pfV[0]; 
	m_pfVector[1] = in_pfV[1]; 
	m_pfVector[2] = in_pfV[2]; 
	
	return *this; 
}

inline VVector3f& VVector3f::operator = (const VVector3f& in_rV)
{ 
	m_pfVector[0] = in_rV.m_pfVector[0]; 
	m_pfVector[1] = in_rV.m_pfVector[1]; 
	m_pfVector[2] = in_rV.m_pfVector[2]; 
	
	return *this;
}

inline bool VVector3f::operator == (const VVector3f& in_rV) const 
{ 
	return (m_pfVector[0] == in_rV.m_pfVector[0] && 
			m_pfVector[1] == in_rV.m_pfVector[1] &&
			m_pfVector[2] == in_rV.m_pfVector[2]);
}

inline bool VVector3f::operator != (const VVector3f& in_rV) const 
{ 
	return (m_pfVector[0] != in_rV.m_pfVector[0] || 
			m_pfVector[1] != in_rV.m_pfVector[1] ||
			m_pfVector[2] != in_rV.m_pfVector[2]);
}

inline VVector3f VVector3f::operator + (const VVector3f& in_rV) const 
{ 
	return VVector3f(m_pfVector[0] + in_rV.m_pfVector[0], 
					 m_pfVector[1] + in_rV.m_pfVector[1], 
					 m_pfVector[2] + in_rV.m_pfVector[2]); 
}

inline VVector3f VVector3f::operator - (const VVector3f& in_rV) const
{
	return VVector3f(m_pfVector[0] - in_rV.m_pfVector[0],
					 m_pfVector[1] - in_rV.m_pfVector[1], 
					 m_pfVector[2] - in_rV.m_pfVector[2]);
}

inline VVector3f VVector3f::operator + (const vfloat32 in_fS) const 
{
	return VVector3f(m_pfVector[0] + in_fS, 
					 m_pfVector[1] + in_fS, 
					 m_pfVector[2] + in_fS); 
}
	
inline VVector3f VVector3f::operator - (const vfloat32 in_fS) const
{
	return VVector3f(m_pfVector[0] - in_fS, 
					 m_pfVector[1] - in_fS, 
					 m_pfVector[2] - in_fS); 
}

inline VVector3f& VVector3f::operator += (const vfloat32 in_fS) 
{ 
	m_pfVector[0] += in_fS;
	m_pfVector[1] += in_fS; 
	m_pfVector[2] += in_fS; 

	return *this;
}

inline VVector3f& VVector3f::operator -= (const vfloat32 in_fS) 
{ 
	m_pfVector[0] -= in_fS; 
	m_pfVector[1] -= in_fS; 
	m_pfVector[2] -= in_fS; 

	return *this; 
}

inline VVector3f& VVector3f::operator *= (const vfloat32 in_fS) 
{ 
	m_pfVector[0] *= in_fS; 
	m_pfVector[1] *= in_fS; 
	m_pfVector[2] *= in_fS;
	
	return *this; 
}

inline VVector3f& VVector3f::operator /= (const vfloat32 in_fS) 
{ 
	m_pfVector[0] /= in_fS; 
	m_pfVector[1] /= in_fS; 
	m_pfVector[2] /= in_fS; 
	
	return *this; 
}

inline VVector3f& VVector3f::operator += (const VVector3f& in_rV)
{ 
	m_pfVector[0] += in_rV.m_pfVector[0]; 
	m_pfVector[1] += in_rV.m_pfVector[1]; 
	m_pfVector[2] += in_rV.m_pfVector[2]; 
	
	return *this; 
}

inline VVector3f& VVector3f::operator -= (const VVector3f& in_rV) 
{ 
	m_pfVector[0] -= in_rV.m_pfVector[0]; 
	m_pfVector[1] -= in_rV.m_pfVector[1]; 
	m_pfVector[2] -= in_rV.m_pfVector[2]; 
	
	return *this; 
}

inline VVector3f VVector3f::operator * (const vfloat32 in_fS) const 
{ 
	return VVector3f(m_pfVector[0] * in_fS, 
					 m_pfVector[1] * in_fS, 
					 m_pfVector[2] * in_fS);
}

inline VVector3f VVector3f::operator / (const vfloat32 in_fS) const 
{ 
	return VVector3f(m_pfVector[0] / in_fS, 
					 m_pfVector[1] / in_fS, 
					 m_pfVector[2] / in_fS);
}

inline vfloat32 VVector3f::Magnitude(void) const 
{
	return sqrtf(m_pfVector[0] * m_pfVector[0] + 
				 m_pfVector[1] * m_pfVector[1] + 
				 m_pfVector[2] * m_pfVector[2]); 
}

inline vfloat32 VVector3f::MagnitudeSquared(void) const 
{
	return (m_pfVector[0] * m_pfVector[0] + 
			m_pfVector[1] * m_pfVector[1] + 
			m_pfVector[2] * m_pfVector[2]);
}

inline VVector3f& VVector3f::Normalize(void)
{ 
	return *this /= Magnitude(); 
}
	
inline VVector3f& VVector3f::Normalize(const VVector3f& in_rV) 
{ 
	return Divide(in_rV, in_rV.Magnitude());
}

inline vfloat32 VVector3f::Dot(const VVector3f& in_rV) const 
{ 
	return (m_pfVector[0] * in_rV.m_pfVector[0] + 
			m_pfVector[1] * in_rV.m_pfVector[1] + 
			m_pfVector[2] * in_rV.m_pfVector[2]); 
}

inline VVector3f& VVector3f::Set(const vfloat32 in_fX, const vfloat32 in_fY, const vfloat32 in_fZ) 
{ 
	m_pfVector[0] = in_fX; 
	m_pfVector[1] = in_fY; 
	m_pfVector[2] = in_fZ; 
	
	return *this; 
}

inline VVector3f& VVector3f::Add(const VVector3f& in_rV, const vfloat32 in_fS)
{ 
	m_pfVector[0] = in_rV.m_pfVector[0] + in_fS; 
	m_pfVector[1] = in_rV.m_pfVector[1] + in_fS; 
	m_pfVector[2] = in_rV.m_pfVector[2] + in_fS; 
	
	return *this; 
}

inline VVector3f& VVector3f::Subtract(const VVector3f& in_rV, const vfloat32 in_fS) 
{ 
	m_pfVector[0] = in_rV.m_pfVector[0] - in_fS; 
	m_pfVector[1] = in_rV.m_pfVector[1] - in_fS; 
	m_pfVector[2] = in_rV.m_pfVector[2] - in_fS; 
	
	return *this; 
}

inline VVector3f& VVector3f::Multiply(const VVector3f& in_rV, const vfloat32 in_fS) 
{ 
	m_pfVector[0] = in_rV.m_pfVector[0] * in_fS; 
	m_pfVector[1] = in_rV.m_pfVector[1] * in_fS; 
	m_pfVector[2] = in_rV.m_pfVector[2] * in_fS; 
	
	return *this; 
}

inline VVector3f& VVector3f::Divide(const VVector3f& in_rV, const vfloat32 in_fS) 
{ 
	m_pfVector[0] = in_rV.m_pfVector[0] / in_fS; 
	m_pfVector[1] = in_rV.m_pfVector[1] / in_fS; 
	m_pfVector[2] = in_rV.m_pfVector[2] / in_fS; 
	
	return *this; 
}

inline VVector3f& VVector3f::Add(const VVector3f& in_rA, const VVector3f& in_rB)
{
	m_pfVector[0] = in_rA.m_pfVector[0] + in_rB.m_pfVector[0];
	m_pfVector[1] = in_rA.m_pfVector[1] + in_rB.m_pfVector[1];
	m_pfVector[2] = in_rA.m_pfVector[2] + in_rB.m_pfVector[2];

	return *this;
}

inline VVector3f& VVector3f::Subtract(const VVector3f& in_rA, const VVector3f& in_rB)
{
	m_pfVector[0] = in_rA.m_pfVector[0] - in_rB.m_pfVector[0];
	m_pfVector[1] = in_rA.m_pfVector[1] - in_rB.m_pfVector[1];
	m_pfVector[2] = in_rA.m_pfVector[2] - in_rB.m_pfVector[2];

	return *this;
}

inline VVector3f VVector3f::Cross(const VVector3f &in_rV) 
{ 
	VVector3f A; 
	
	A.m_pfVector[0] = m_pfVector[1] * in_rV.m_pfVector[2] - m_pfVector[2] * in_rV.m_pfVector[1]; 
	A.m_pfVector[1] = m_pfVector[2] * in_rV.m_pfVector[0] - m_pfVector[0] * in_rV.m_pfVector[2]; 
	A.m_pfVector[2] = m_pfVector[0] * in_rV.m_pfVector[1] - m_pfVector[1] * in_rV.m_pfVector[0]; 
	
	return A; 
}

inline VVector3f& VVector3f::Cross(const VVector3f& in_rA, const VVector3f& in_rB) 
{ 
	m_pfVector[0] = in_rA.m_pfVector[1] * in_rB.m_pfVector[2] - in_rA.m_pfVector[2] * in_rB.m_pfVector[1]; 
	m_pfVector[1] = in_rA.m_pfVector[2] * in_rB.m_pfVector[0] - in_rA.m_pfVector[0] * in_rB.m_pfVector[2]; 
	m_pfVector[2] = in_rA.m_pfVector[0] * in_rB.m_pfVector[1] - in_rA.m_pfVector[1] * in_rB.m_pfVector[0]; 
	
	return *this; 
}

inline void VVector3f::Random(void)
{
    m_pfVector[2] = VMath::Rand(-1.0f, 1.0f);
    vfloat32 fA = VMath::Rand(0.0f, 6.283185307179586476925286766559f);

    vfloat32 fR = sqrtf(1.0f - m_pfVector[2] * m_pfVector[2]);

    m_pfVector[0] = fR * cosf(fA);
    m_pfVector[1] = fR * sinf(fA);
}