#ifndef V3D_VMATRIXROTATIONOPS_H
#define V3D_VMATRIXROTATIONOPS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Math/VMatrix.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
/**
 * Rotation utility function
 * @author: ins
 */
template<typename Scalar, vuint RowCount, vuint ColumnCount>
void SetRotationX(VMatrix<Scalar, RowCount, ColumnCount>& result, Scalar in_RotAngle)
{
	Identity(result);
	
	Scalar sinus   = sin(in_RotAngle);
	Scalar cosinus = cos(in_RotAngle);

	result.Set(1,2, sinus);	
	result.Set(1,1, cosinus);
	result.Set(2,1, -sinus);
	result.Set(2,2, cosinus);

}

template<typename Scalar, vuint RowCount, vuint ColumnCount>
void SetRotationY(VMatrix<Scalar, RowCount, ColumnCount>& result, Scalar in_RotAngle)
{
	Identity(result);

	Scalar sinus   = sin(in_RotAngle);
	Scalar cosinus = cos(in_RotAngle);

	result.Set(0,0, cosinus);
	result.Set(0,2, -sinus);
	result.Set(2,0, sinus);
	result.Set(2,2, cosinus);

}

template<typename Scalar, vuint RowCount, vuint ColumnCount>
void SetRotationZ(VMatrix<Scalar, RowCount, ColumnCount>& result, Scalar in_RotAngle)
{
	Identity(result);

	Scalar sinus   = sin(in_RotAngle);
	Scalar cosinus = cos(in_RotAngle);

	result.Set(0,0, cosinus);
	result.Set(0,1, sinus);
	result.Set(1,0, -sinus);
	result.Set(1,1, cosinus);
}

template<typename Scalar, vuint RowCount, vuint ColumnCount>
void SetTranslate(
	VMatrix<Scalar, RowCount, ColumnCount>& result,
	Scalar x, Scalar y, Scalar z
	)
{
	Identity(result);

    result.Set(0, 3, x);
	result.Set(1, 3, y);
	result.Set(2, 3, z);
}

template<typename Scalar, vuint RowColumnCount>
void SetScale(
	VMatrix<Scalar, RowColumnCount, RowColumnCount>& mat,
	vfloat32 factor
	)
{
	Identity(mat);

	for(int i = 0; i < RowColumnCount - 1; ++i)
	{
		mat.Set(i, i, factor);
	}
}


//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMATRIXROTATIONOPS_H
