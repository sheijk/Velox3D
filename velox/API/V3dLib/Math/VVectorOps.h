#ifndef V3D_VVECTOROPS_01_22_05_H
#define V3D_VVECTOROPS_01_22_05_H
//-----------------------------------------------------------------------------
#include <V3d/Math/VVector.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

template<typename Scalar, vuint Dimension>
	void Add(
	VVector<Scalar, Dimension>& res,
	const VVector<Scalar, Dimension>& a,
	const VVector<Scalar, Dimension>& b
	)
{
	res.m_Vec = a.m_Vec + b.m_Vec;
	//gmtl::add(res.m_Vec, a.m_Vec, b.m_Vec);
}

template<typename Scalar, vuint Dimension>
	void Sub(
	VVector<Scalar, Dimension>& res,
	const VVector<Scalar, Dimension>& a,
	const VVector<Scalar, Dimension>& b
	)
{
	res.m_Vec = a.m_Vec - b.m_Vec;
	//gmtl::sub(res.m_Vec, a.m_Vec, b.m_Vec);
}

template<typename Scalar, vuint Dimension>
	VVector<Scalar, Dimension>
	operator+(
	const VVector<Scalar, Dimension>& a,
	const VVector<Scalar, Dimension>& b
	)
{
	VVector<Scalar, Dimension> res;
	Add(res, a, b);
	return res;
}

template<typename Scalar, vuint Dimension>
	VVector<Scalar, Dimension>
	operator-(
	const VVector<Scalar, Dimension>& a,
	const VVector<Scalar, Dimension>& b
	)
{
	VVector<Scalar, Dimension> res;
	Sub(res, a, b);
	return res;
}

template<typename Scalar, vuint Dimension>
	void operator+=(
	VVector<Scalar, Dimension>& result,
	const VVector<Scalar, Dimension>& addval
	)
{
	Add(result, result, addval);
}

template<typename Scalar, vuint Dimension>
	void operator-=(
	VVector<Scalar, Dimension>& result,
	const VVector<Scalar, Dimension>& subval
	)
{
	Sub(result, result, subval);
}

template<typename Scalar, vuint Dimension>
	void ApplyCross(
	VVector<Scalar, Dimension>& result,
	const VVector<Scalar, Dimension>& a,
	const VVector<Scalar, Dimension>& b
	)
{
	gmtl::cross(result.m_Vec, a.m_Vec, b.m_Vec);
}

template<typename Scalar, vuint Dimension>
	VVector<Scalar, Dimension>
	Cross(
	const VVector<Scalar, Dimension>& a,
	const VVector<Scalar, Dimension>& b
	)
{
	return VVector<Scalar, Dimension>(gmtl::cross(a.m_Vec, b.m_Vec));
}

template<typename Scalar, vuint Dimension>
	Scalar Dot(
	const VVector<Scalar, Dimension>& a,
	const VVector<Scalar, Dimension>& b
	) 
{
	Scalar res;
	res = dot(a.m_Vec, b.m_Vec);
	return res;
	//return VVector<Scalar, Dimension>(gmtl::dot(a.m_Vec, b.m_Vec));
}

template<typename Scalar, vuint Dimension, typename AssignType>
	void Mult(
	VVector<Scalar, Dimension>& vec,
	AssignType fac
	)
{
	gmtl::operator*=(vec.m_Vec, fac);
}

template<typename Scalar, vuint Dimension, typename AssignType>
	void operator*=(
	VVector<Scalar, Dimension>& vec,
	AssignType fac
	)
{
	Mult(vec, fac);
}

template<typename Scalar, vuint Dimension, typename AssignType>
	VVector<Scalar, Dimension> 
	operator*(
	const VVector<Scalar, Dimension>& vec,
	AssignType fac
	)
{
	VVector<Scalar, Dimension> res(vec);
	Mult(res, fac);
	return res;		
}

template<typename Scalar, vuint Dimension, typename AssignType>
	VVector<Scalar, Dimension>
	operator*(
	AssignType fac,
	const VVector<Scalar, Dimension>& vec
	)
{
	return vec * fac;
}

template<typename Scalar, vuint Dimension>
	void Normalize(
	VVector<Scalar, Dimension>& vec
	)
{
	gmtl::normalize(vec.m_Vec);
}

template<typename Scalar, vuint Dimension>
	VVector<Scalar, Dimension> Normalized(
	const VVector<Scalar, Dimension>& vec
	)
{
	VVector<Scalar, Dimension> ret(vec);
	Normalize(ret);
	return ret;
}



template<typename Scalar, vuint Dimension>
	Scalar Length(
	const VVector<Scalar, Dimension>& vec
	)
{
	return gmtl::length(vec.m_Vec);
}

template<typename Scalar, vuint Dimension>
	inline Scalar LengthSquared(
	const VVector<Scalar, Dimension>& vec
	)
{
	return gmtl::lengthSquared(vec.m_Vec);
}

//-----------------------------------------------------------------------------

template<typename Scalar>
void Add(
		 VVector<Scalar, 3>& res,
		 const VVector<Scalar, 3>& a,
		 const VVector<Scalar, 3>& b
		 )
{
	res.m_Vec = a.m_Vec + b.m_Vec;
	//gmtl::add(res.m_Vec, a.m_Vec, b.m_Vec);
}

template<typename Scalar>
void Sub(
		 VVector<Scalar, 3>& res,
		 const VVector<Scalar, 3>& a,
		 const VVector<Scalar, 3>& b
		 )
{
	res.m_Vec = a.m_Vec - b.m_Vec;
	//gmtl::sub(res.m_Vec, a.m_Vec, b.m_Vec);
}

template<typename Scalar>
VVector<Scalar, 3>
operator+(
		  const VVector<Scalar, 3>& a,
		  const VVector<Scalar, 3>& b
		  )
{
	VVector<Scalar, 3> res;
	Add(res, a, b);
	return res;
}

template<typename Scalar>
VVector<Scalar, 3>
operator-(
		  const VVector<Scalar, 3>& a,
		  const VVector<Scalar, 3>& b
		  )
{
	VVector<Scalar, 3> res;
	Sub(res, a, b);
	return res;
}

template<typename Scalar>
void operator+=(
				VVector<Scalar, 3>& result,
				const VVector<Scalar, 3>& addval
				)
{
	Add(result, result, addval);
}

template<typename Scalar>
void operator-=(
				VVector<Scalar, 3>& result,
				const VVector<Scalar, 3>& subval
				)
{
	Sub(result, result, subval);
}

template<typename Scalar>
void ApplyCross(
				VVector<Scalar, 3>& result,
				const VVector<Scalar, 3>& a,
				const VVector<Scalar, 3>& b
				)
{
	gmtl::cross(result.m_Vec, a.m_Vec, b.m_Vec);
}

template<typename Scalar>
VVector<Scalar, 3>
Cross(
	  const VVector<Scalar, 3>& a,
	  const VVector<Scalar, 3>& b
	  )
{
	return VVector<Scalar, 3>(gmtl::cross(a.m_Vec, b.m_Vec));
}

template<typename Scalar>
vbool IsNormalized(const VVector<Scalar, 3>& a, Scalar eps = 0.0001)
{
	return gmtl::isNormalized(a.m_Vec, eps);
}

template<typename Scalar>
Scalar Dot(
		   const VVector<Scalar, 3>& a,
		   const VVector<Scalar, 3>& b
		   ) 
{
	Scalar res;
	res = dot(a.m_Vec, b.m_Vec);
	return res;
	//return VVector<Scalar, Dimension>(gmtl::dot(a.m_Vec, b.m_Vec));
}

template<typename Scalar, typename AssignType>
void Mult(
		  VVector<Scalar, 3>& vec,
		  AssignType fac
		  )
{
	gmtl::operator*=(vec.m_Vec, fac);
}

template<typename Scalar, typename AssignType>
void operator*=(
				VVector<Scalar, 3>& vec,
				AssignType fac
				)
{
	Mult(vec, fac);
}

template<typename Scalar, typename AssignType>
VVector<Scalar, 3> 
operator*(
		  const VVector<Scalar, 3>& vec,
		  AssignType fac
		  )
{
	VVector<Scalar, 3> res(vec);
	Mult(res, fac);
	return res;		
}

template<typename Scalar, typename AssignType>
VVector<Scalar, 3>operator*
(
		  AssignType fac,
		  const VVector<Scalar, 3>& vec
		  )
{
	return vec * fac;
}

//-----------------------------------------------------------------------------
} //namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VVECTOROPS_01_22_05_H

