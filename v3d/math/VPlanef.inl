inline vfloat32 VPlanef::GetDistance(void) const
{
	return m_fDistance;
}

inline VVector3f& VPlanef::GetNormal(void)
{
	return m_Normal;
}

inline void VPlanef::GetNormal(VVector3f& in_rNormal) const
{
	in_rNormal = m_Normal;
}

inline void VPlanef::SetDistance(const vfloat32 in_fDistance)
{
	m_fDistance = in_fDistance;
}

inline void VPlanef::SetNormal(const VVector3f& in_rNormal)
{
	m_Normal = in_rNormal;
}