#ifndef V3D_VMATRIX_H
#define V3D_VMATRIX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

	template<typename Scalar, vuint RowCount, vuint ColumnCount>
	class VMatrix
	{
	public:
		typedef gmtl::Matrix<Scalar, RowCount, ColumnCount> MatrixImpl;

		MatrixImpl m_Mat;
		
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

		//friend Add(VMatrix&, const VMatrix&, const VMatrix&);
		//friend Sub(VMatrix&, const VMatrix&, const VMatrix&);
		//friend Mult(VMatrix&, const VMatrix&, const VMatrix&);
		//friend Identity(VMatrix&);
		//friend MakeInverse(VMatrix&);
		//friend MakeTranspose(VMatrix&);
	};
	
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMATRIX_H
