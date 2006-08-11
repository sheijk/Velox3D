#ifndef V3D_VMATRIX_H
#define V3D_VMATRIX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
	class VMatrix
	{
	public:
		typedef gmtl::Matrix<Scalar, RowCount, ColumnCount> MatrixImpl;
		
		MatrixImpl m_Mat;
		/**
		 * treat this as if it where private.. had to be
		 * made public due to compiler problems 
		 */		
		VMatrix(const MatrixImpl& mat) : m_Mat(mat) {}
	public:

		VMatrix() {};
		VMatrix(const VMatrix& in_Source) : m_Mat(in_Source.m_Mat) {}
		
		void Set(vuint r, vuint c, Scalar val) 
		{
			m_Mat(r, c) = val;
		}

		Scalar Get(vuint r, vuint c) const
		{
			return m_Mat(r,c);
		}

		vuint GetRows() const
		{
			return RowCount;
		}

		vuint GetColumns() const
		{
			return ColumnCount;
		}

		VMatrix& operator=(const VMatrix& source)
		{
			m_Mat = source.m_Mat;
			return *this;
		}

		//TODO: move away from here

		void SetTransform(Scalar in_X, Scalar in_Y, Scalar in_Z)
		{
			Set(0,3, in_X);
			Set(1,3, in_Y);
			Set(2,3, in_Z);
		}
};

typedef VMatrix<vfloat32, 2, 2> VMatrix22f;
typedef VMatrix<vfloat32, 3, 3> VMatrix33f;
typedef VMatrix<vfloat32, 4, 4> VMatrix44f;

typedef VMatrix<vfloat64, 2, 2> VMatrix22d;
typedef VMatrix<vfloat64, 3, 3> VMatrix33d;
typedef VMatrix<vfloat64, 4, 4> VMatrix44d;


	
//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMATRIX_H

