#ifndef V3D_VMATRIXOPS_H
#define V3D_VMATRIXOPS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Math/VMatrix.h>
#include <v3d/Math/VVector.h>
#include <V3d/Math/VQuaternion.h>
#include <gmtl/gmtl.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
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
		result.m_Mat = gmtl::makeInverse(result.m_Mat);
	}

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
		void MakeTranspose(
		VMatrix<Scalar, RowCount, ColumnCount>& result
		)
	{
		result.m_Mat = gmtl::makeTranspose(result.m_Mat);
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

	template<typename Scalar, int RowCount, int ColumnCount, int Internal>
		void Mult(
		VMatrix<Scalar, RowCount, ColumnCount>& result,
		const VMatrix<Scalar, RowCount, Internal>& op1,
		const VMatrix<Scalar, Internal, ColumnCount>& op2
		)
	{
		gmtl::mult(result.m_Mat, op1.m_Mat, op2.m_Mat);
	}

	//template<typename Scalar, vuint RowCount, vuint ColumnCount>
	//	void Mult(
	//	VMatrix<Scalar, RowCount, ColumnCount>& result,
	//	const VMatrix<Scalar, RowCount, ColumnCount>& op1,
	//	const VMatrix<Scalar, RowCount, ColumnCount>& op2
	//	)
	//{
	//	gmtl::mult(result.m_Mat, op1.m_Mat, op2.m_Mat);
	//}

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
	void Mult(
		VVector<Scalar, ColumnCount>& result,
		const VMatrix<Scalar, RowCount, ColumnCount>& mat,
		const VVector<Scalar, ColumnCount>& vector
		)
	{
		//r = m * v;
		result = VVector<Scalar, ColumnCount>(
			gmtl::operator*(mat.m_Mat, vector.m_Vec));
	}

	// 3d vector / 4x4 matrix multiplication
	template<typename Scalar>
		void Mult(
		VVector<Scalar, 3>& result,
		const VMatrix<Scalar, 4, 4>& mat,
		const VVector<Scalar, 3>& vector
		)
	{
		//r = m * v;
		result = VVector<Scalar, 3>(
			gmtl::operator*(mat.m_Mat, vector.m_Vec));
	}

	/**
	 * matrix quaternion rotation, works only for 3x3 matrices
	 * @author: ins
	 */

	template<typename Scalar>
		void Rotate(VMatrix<Scalar, 3, 3>& in_Matrix,
		VQuaternion<Scalar>& in_Quat)
	{
		vfloat32 scale, xs,ys,zs, wx,wy,wz, xx,xy,xz, yy,yz, zz;
		vfloat32 qx,qy,qz,qw;

		in_Quat.Get(qx,qy,qz,qw);
		
		//scaling factor for non normalized quaternion rotation
		scale = 2.0f / Length(in_Quat);

		xs = scale * qx;
		ys = scale * qy;
		zs = scale * qz;

		wx = qw * xs;
		wy = qw * ys;
		wz = qw * zs;

		xx = qx * xs;
		xy = qx * ys;
		xz = qx * zs;

		yy = qy * ys;
		yz = qy * zs;
		
		zz = qz * zs;

		in_Matrix.Set(0,0, 1.0f - (yy + zz));
		in_Matrix.Set(0,1, xy - wz);
		in_Matrix.Set(0,2, xz + wy);

		in_Matrix.Set(1,0, xy + wz);
		in_Matrix.Set(1,1, 1.0f - (xx + zz));
		in_Matrix.Set(1,2, yz - wx);

		in_Matrix.Set(2,0, xz - wy);
		in_Matrix.Set(2,1, yz + wx);
		in_Matrix.Set(2,2, 1.0f - (xx + yy));
	}

	std::ostream& operator<<(std::ostream& str, const VMatrix44f& matrix);
	std::istream& operator>>(std::istream& str, VMatrix44f& matrix);

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMATRIXOPS_H
