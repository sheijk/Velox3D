#ifndef V3D_VVECTOR_H
#define V3D_VVECTOR_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
	
	template<typename Scalar, vuint RowCount, vuint ColumnCount>
	class VMatrix;

	/**
	 * a simple 1-dimensional vector in the mathematical sense
	 */
	template<typename Scalar, vuint Dimension>
	class VVector
	{
	public:
		// do not use members and functions in this block as they are only
		// public because of some problem with friend declarations
		typedef gmtl::Vec<Scalar, Dimension> VecImpl;

		VecImpl m_Vec;
		
		VVector(const VecImpl& implv) : m_Vec(implv) {}
	public:
		VVector() {}
		~VVector() {}
		VVector(const VVector& source) : m_Vec(source.m_Vec) {}

		void Set(vuint in_Pos, Scalar in_Val)
		{
			m_Vec[in_Pos] = in_Val;
		}

		Scalar Get(vuint in_Pos)
		{
			return m_Vec[in_Pos];
		}

		Scalar& operator[](vuint in_Pos)
		{
			return m_Vec[in_Pos];
		}

		const Scalar& operator[](vuint in_Pos) const
		{
			return m_Vec[in_Pos];
		}

		vuint GetDimension()
		{
			return Dimension;
		}

		VVector& operator=(const VVector& source)
		{
			m_Vec = source.m_Vec;
			return *this;
		}

		//friend void Add(VVector&, const VVector&, const VVector&);
		//friend void Sub(VVector&, const VVector&, const VVector&);
		//friend void ApplyCross(VVector&, const VVector&, const VVector&);
		//friend VVector Cross(const VVector&, const VVector&);
		//friend Scalar Dot(const VVector&, const VVector&);
		//
		//template<typename Scalar, vuint Dimension, typename AssignType>
		//friend void Mult(VVector&, AssignType);

		//template<typename Scalar, vuint Dimension, typename AssignType>
		//friend VVector operator*(const VVector&, AssignType);

		//template<typename Scalar, vuint Dimension, typename AssignType>
		//friend VVector operator*(AssignType, const VVector&);

		//friend void Normalize(VVector&);
		//friend Scalar Length(const VVector&);
		//friend Scalar LengthSquared(const VVector&);

	};

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
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VVECTOR_H