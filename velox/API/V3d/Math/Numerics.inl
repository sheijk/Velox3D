inline vfloat32 DegreeToRadian(vfloat32 degree)
{
	return degree / 180.0f * Pi();
}

inline vfloat32 RadianToDegree(vfloat32 radian)
{
	return radian * 180.0f / Pi();
}

inline vfloat32 Pi()
{
	return 3.1415f;
}

template<typename T>
T Interpolate(T a, T b, vfloat32 factor)
{
	return ((1 - factor) * a) + (factor * b);
}

inline float PseudoRandom(vuint x)
{
	x = (x<<13) ^ x;
    return vfloat32( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

inline float PseudoRandom(vuint x, vfloat32 in_fMin, vfloat32 in_fMax)
{
	vfloat32 rnd = PseudoRandom(x);

	rnd += 1;
	rnd *= (in_fMax - in_fMin)/2;
	rnd += in_fMin;

	return rnd;
}

template<typename T>
T Clamp(T value, T minValue, T maxValue)
{
	if( value >= maxValue )
		return maxValue;
	else if( value <= minValue)
		return minValue;
	else
		return value;
}
