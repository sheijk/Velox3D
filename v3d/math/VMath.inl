inline vfloat32 VMath::Rand(const vfloat32 in_fMin, const vfloat32 in_fMax)
{
    return (in_fMin + (in_fMax - in_fMin) * rand() / (vfloat32)RAND_MAX);
}

inline vuint VMath::Log2(vuint in_uiVal)
{
	vuint uiRet = 0;
	while (in_uiVal>>=1) 
	{
		uiRet++;
	}
	return uiRet;
}

inline vfloat32 VMath::ToDegrees(const vfloat32 in_fAngle)
{
	return (in_fAngle * (180.0f / PI));
}

inline vfloat32 VMath::ToRadians(const vfloat32 in_fAngle)
{
	return (in_fAngle * (PI / 180.0f));
}