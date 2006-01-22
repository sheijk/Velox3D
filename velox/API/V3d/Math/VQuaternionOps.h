#ifndef V3D_VQUATERNIONOPS_01_09_05_H
#define V3D_VQUATERNIONOPS_01_09_05_H
//-----------------------------------------------------------------------------
#include <v3d/Math/VVector.h>
#include <V3d/Math/VQuaternion.h>
#include <V3d/Math/Numerics.h>
#include <gmtl/QuatOps.h>
//-----------------------------------------------------------------------------
namespace v3d{
//-----------------------------------------------------------------------------
/**
 * Quaternion operations templates
 * @author: ins
 * @note: recheck implementation, it's 5 am....
 */

template<typename Scalar>
	VQuaternion<Scalar> Mult(VQuaternion<Scalar>& result,
		const VQuaternion<Scalar> q1,
		const VQuaternion<Scalar> q2
		)
{
	return gmtl::mult(result.m_Data, q1.m_Data, q2.m_Data);
}

template<typename Scalar>
VQuaternion<Scalar> Negate(VQuaternion<Scalar>& result)
{
	return gmtl::negate(result.m_Data);
}

template<typename Scalar>
	VQuaternion<Scalar> Mult(VQuaternion<Scalar>& result,
	const VQuaternion<Scalar>& q1, const Scalar s)
{
	return gmtl::mult(result.m_Data, q1.m_Data, s);
}
template<typename Scalar>
	VQuaternion<Scalar> Div(VQuaternion<Scalar>& result,
	const VQuaternion<Scalar>& q1, const VQuaternion<Scalar>& q2)
{
	return gmtl::div(result.m_Data, q1.m_Data, q2.m_Data);
}

template<typename Scalar>
	VQuaternion<Scalar> Div(VQuaternion<Scalar>& result,
	const VQuaternion<Scalar>& q1, const Scalar s)
{
	return gmtl::div(result.m_Data, q1.m_Data, s);
}

template<typename Scalar>
	VQuaternion<Scalar> Add(VQuaternion<Scalar>& result,
	const VQuaternion<Scalar>& q1, const VQuaternion<Scalar>& q2)
{
	return gmtl::add(result.m_Data, q1.m_Data, q2.m_Data);
}

template<typename Scalar>
	VQuaternion<Scalar> Sub(VQuaternion<Scalar>& result,
	const VQuaternion<Scalar>& q1, const VQuaternion<Scalar>& q2)
{
	return gmtl::sub(result.m_Data, q1.m_Data, q2.m_Data);
}

template<typename Scalar>
	Scalar Dot(const VQuaternion<Scalar>& q1, const VQuaternion<Scalar>& q2)
{
	return gmtl::dot(q1.m_Data, q2.m_Data);
}

template<typename Scalar>
	Scalar LengthSquared(const VQuaternion<Scalar>& q1)
{
	return gmtl::lengthSquared(q1.m_Data);
}

template<typename Scalar>
	Scalar Length(const VQuaternion<Scalar>& q1)
{
	return gmtl::length(q1.m_Data);
}

template<typename Scalar>
	VQuaternion<Scalar> Normalize(VQuaternion<Scalar>& result)
{
	VQuaternion<Scalar> resultVal = gmtl::normalize(result.m_Data);
	return resultVal;
}

template<typename Scalar>
	vbool IsNormalized(const VQuaternion<Scalar>& q1)
{
	return gmtl::isNormalized(q1.m_Data);
}

template<typename Scalar>
	VQuaternion<Scalar> Conj( VQuaternion<Scalar>& result)
{
	result = gmtl::conj(result.m_Data);
	return result;
}

template<typename Scalar>
	VQuaternion<Scalar> Invert(VQuaternion<Scalar>& result)
{
	result = gmtl::invert(result.m_Data);
	return result;
}

template<typename Scalar>
	VQuaternion<Scalar> Exp(VQuaternion<Scalar>& result)
{
	result = gmtl::exp(result.m_Data);
	return result;
}

template<typename Scalar>
	VQuaternion<Scalar> Log(VQuaternion<Scalar>& result)
{
	result = gmtl::log(result.m_Data);
	return result;
}

template<typename Scalar>
	VQuaternion<Scalar> Slerp(VQuaternion<Scalar>& result, const Scalar t,
	const VQuaternion<Scalar>& from, const VQuaternion<Scalar>& to,
	bool adjustSign=true)
{
	VQuaternion<Scalar> retVal = gmtl::slerp(result.m_Data, t, from.m_Data,
		to.m_Data, adjustSign);

	return retVal;
}

template<typename Scalar>
VQuaternion<Scalar> Lerp(VQuaternion<Scalar>& result, const Scalar t,
						  const VQuaternion<Scalar>& from,
						  const VQuaternion<Scalar>& to)
{
	VQuaternion<Scalar> retVal = gmtl::lerp(result.m_Data, t, from.m_Data,
		to.m_Data);

	return retVal;
}

template<typename Scalar>
	VQuaternion<Scalar> operator-(const VQuaternion<Scalar>& q1,
	const VQuaternion<Scalar>& q2)
{
	VQuaternion<Scalar> result = gmtl::sub(result.m_Data, q1.m_Data,q2.m_Data);
	return result;
}

template<typename Scalar>
	VQuaternion<Scalar> operator+(const VQuaternion<Scalar>& q1,
	const VQuaternion<Scalar>& q2)
{
	VQuaternion<Scalar> result = gmtl::add(result.m_Data, q1.m_Data, q2.m_Data);
	return result;
}

template<typename Scalar>
	VQuaternion<Scalar> operator+=(const VQuaternion<Scalar>& q1,
	const VQuaternion<Scalar>& q2)
{
	VQuaternion<Scalar> result = gmtl::add(result.m_Data,
		result.m_Data, q1.m_Data
		);

	return result;
}

template<typename Scalar>
	VQuaternion<Scalar> operator-=(const VQuaternion<Scalar>& q1,
	const VQuaternion<Scalar>& q2)
{
	VQuaternion<Scalar> result = gmtl::sub(result.m_Data,
		q1.m_Data,
		q2.m_Data);
	
	return result;
}

template<typename Scalar>
VQuaternion<Scalar> operator-(VQuaternion<Scalar> q1)
{
	return gmtl::negate(q1.m_Data);
}

template<typename Scalar>
	VQuaternion<Scalar> operator*(const VQuaternion<Scalar>& q1,
	const VQuaternion<Scalar>& q2)
{
	VQuaternion<Scalar> result;
	result = gmtl::mult( result.m_Data, q1.m_Data,q2.m_Data);
	return result;
}

template<typename Scalar> 
	VQuaternion<Scalar> operator*(const VQuaternion<Scalar>& q1,
	const Scalar s)
{
	VQuaternion<Scalar> result;
	result = gmtl::mult( result.m_Data, q1.m_Data, s);
	return result;
}

template<typename Scalar>
	VQuaternion<Scalar> operator/(const VQuaternion<Scalar>& q1,
	const Scalar s)
{
	VQuaternion<Scalar> result = gmtl::div(result.m_Data, q1.m_Data, s);
	return result;
}


template<typename Scalar>
	VQuaternion<Scalar> operator*=(VQuaternion<Scalar> result,
	const VQuaternion<Scalar>& q1)
{
	return gmtl::mult(result.m_Data, result.m_Data, q1.m_Data);
}
template<typename Scalar>
	VQuaternion<Scalar> operator*=(VQuaternion<Scalar>& q1,
	const Scalar s)
{
	return gmtl::mult(q1.m_Data, q1.m_Data, s);
}

template<typename Scalar>
	VQuaternion<Scalar> operator/=(VQuaternion<Scalar>& q1,
	const Scalar s)
{
    return gmtl::div(q1.m_Data, q1.m_Data, s);
}

template<typename Scalar>
	vbool operator==(const VQuaternion<Scalar>& q1,
	const VQuaternion<Scalar>& q2)
{
	return gmtl::operator==(q1.m_Data, q2.m_Data);
}

template<typename Scalar>
vbool operator!=(const VQuaternion<Scalar>& q1,
				 const VQuaternion<Scalar>& q2)
{
	return !gmtl::operator==(q1.m_Data, q2.m_Data);
}

template<typename Scalar>
	vbool IsEqual(const VQuaternion<Scalar>& q1,
	const VQuaternion<Scalar>& q2, Scalar delta=0.0)
{
	return gmtl::isEqual(q1.m_Data, q2.m_Data, delta);
}

template<typename Scalar>
	vbool IsEquiv(const VQuaternion<Scalar>& q1,
	const VQuaternion<Scalar>& q2, Scalar delta=0.0)

{
	return gmtl::isEquiv(q1.m_Data, q2.m_Data, delta);
}

/**
 * Construct a quaternion from an axis and angle
 */
template<typename Scalar>
VQuaternion<Scalar> QuatFromAxisAngle(
	const VVector<Scalar, 3>& in_Axis, Scalar in_AngleDegree)
{
	Scalar sinx = sin(math::DegreeToRadian(in_AngleDegree) / 2);
	Scalar cosy = cos(math::DegreeToRadian(in_AngleDegree) / 2);

	Scalar x,y,z,w;

	x = in_Axis.Get(0) * sinx;
	y = in_Axis.Get(1) * sinx;
	z = in_Axis.Get(2) * sinx;
	w = cosy;

	return VQuaternion<Scalar>(x,y,z,w);
}

void Rotate(VVector3f& io_Vector, const VQuatf& in_Rotation);

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VQUATERNIONOPS_01_09_05_H
