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
		/**
		 * treat this as if it where private.. had to be
		 * made public due to compiler problems 
		 */		
		VMatrix(const MatrixImpl& mat) : m_Mat(mat) {}
	public:

		enum RotationAxis
		{
			X_AXIS,
			Y_AXIS,
			Z_AXIS

		};

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

		/*void SetRotate(RotationAxis in_Axis, Scalar in_RotAngle)
		{
			SetIdentity();

			Scalar sinus   = sin(in_RotAngle);
			Scalar cosinus = cos(in_RotAngle);


			switch(in_Axis)
			{
				case X_AXIS:
				{
			
					Set(1,2, sinus);	
					Set(1,1, cosinus);
					Set(2,1, -sinus);
					Set(2,2, cosinus);
					break;
				}
				case Y_AXIS:
				{
					Set(0,0, cosinus);
					Set(0,2, -sinus);
					Set(2,0, sinus);
					Set(2,2, cosinus);
					break;
				}
				case Z_AXIS:
				{
					
					Set(0,0, cosinus);
					Set(0,1, sinus);
					Set(1,0, -sinus);
					Set(1,1, cosinus);
					break;
				}
			}
		}*/

};
typedef VMatrix<float, 4, 4> VMatrix44f;


	
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMATRIX_H

