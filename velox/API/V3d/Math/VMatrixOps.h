#ifndef V3D_VMATRIXOPS_H
#define V3D_VMATRIXOPS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Math/VMatrix.h>
#include <v3d/Math/VVector.h>
#include <gmtl/gmtl.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

	// matrix factories:
	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		VMatrix<Scalar, RowCount, ColumnCount>
		Identity(VMatrix<Scalar, RowCount, ColumnCount>& result)
	{
		return gmtl::identity(result.m_Mat);
	}

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		void MakeInverse(
		VMatrix<Scalar, RowCount, ColumnCount>& result
		)
	{
		gmtl::makeInverse(result.m_Mat);
	}

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		void MakeTranspose(
		VMatrix<Scalar, RowCount, ColumnCount>& result
		)
	{
		gmtl::makeTranspose(result.m_Mat);
	}

	// matrix operations:
	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		void Add(
		VMatrix<Scalar, RowCount, ColumnCount>& result,
		const VMatrix<Scalar, RowCount, ColumnCount>& op1,
		const VMatrix<Scalar, RowCount, ColumnCount>& op2
		)
	{
		gmtl::add(result.m_Mat, op1.m_Mat, op2.m_Mat);
	}

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		void Sub(
		VMatrix<Scalar, RowCount, ColumnCount>& result,
		const VMatrix<Scalar, RowCount, ColumnCount>& op1,
		const VMatrix<Scalar, RowCount, ColumnCount>& op2
		)
	{
		gmtl::sub(result.m_Mat, op1.m_Mat, op2.m_Mat);
	}

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		void Mult(
		VMatrix<Scalar, RowCount, ColumnCount>& result,
		const VMatrix<Scalar, RowCount, ColumnCount>& op1,
		const VMatrix<Scalar, RowCount, ColumnCount>& op2
		)
	{
		gmtl::mult(result.m_Mat, op1.m_Mat, op2.m_Mat);
	}	

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		VMatrix<Scalar, RowCount, ColumnCount>
		operator+(
		const VMatrix<Scalar, RowCount, ColumnCount>& a,
		const VMatrix<Scalar, RowCount, ColumnCount>& b
		)
	{
		VMatrix<Scalar, RowCount, ColumnCount> res;
		Add(res, a, b);
		return res;		
	}

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		VMatrix<Scalar, RowCount, ColumnCount>
		operator-(
		const VMatrix<Scalar, RowCount, ColumnCount>& a,
		const VMatrix<Scalar, RowCount, ColumnCount>& b
		)
	{
		VMatrix<Scalar, RowCount, ColumnCount> res;
		Sub(res, a, b);
		return res;		
	}

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		VMatrix<Scalar, RowCount, ColumnCount>
		operator*(
		const VMatrix<Scalar, RowCount, ColumnCount>& a,
		const VMatrix<Scalar, RowCount, ColumnCount>& b
		)
	{
		VMatrix<Scalar, RowCount, ColumnCount> res;
		Mult(res, a, b);
		return res;		
	}

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		void operator+=(
		VMatrix<Scalar, RowCount, ColumnCount>& result,
		const VMatrix<Scalar, RowCount, ColumnCount>& addval
		)
	{
		Add(result, result, addval);
	}

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		void operator-=(
		VMatrix<Scalar, RowCount, ColumnCount>& result,
		const VMatrix<Scalar, RowCount, ColumnCount>& subval
		)
	{
		Sub(result, result, subval);
	}

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
	void operator*=(
		VMatrix<Scalar, RowCount, ColumnCount>& result,
		const VMatrix<Scalar, RowCount, ColumnCount>& multval
		)
	{
		Mult(result, result, multval);
	}

	// vector/matrix multiplication
	template<typename Scalar, vuint RowCount, vuint ColumnCount>
	VVector<Scalar, ColumnCount>
	Mult(
		const VMatrix<Scalar, RowCount, ColumnCount>& mat,
		const VVector<Scalar, ColumnCount>& vector
		)
	{
		//gmtl::Vec<Scalar, ColumnCount> r;
		//gmtl::Vec<Scalar, ColumnCount> v;
		//gmtl::Matrix<Scalar, ColumnCount, RowCount> m;

		//r = m * v;
		return VVector<Scalar, ColumnCount>(
			gmtl::operator*(mat.m_Mat, vector.m_Vec));
	}



//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMATRIXOPS_H
