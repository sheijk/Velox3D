#ifndef V3D_TRANSFORMATIONOPS_2004_04_09_H
#define V3D_TRANSFORMATIONOPS_2004_04_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Math/VMatrix.h>
#include <v3d/Core/SmartPtr/VGuards.h>

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

/**
 * @author: ins
 */
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

/**
 * @author: ins
 */
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

/**
* @author: ins
*/
template<typename Scalar, vuint RowCount, vuint ColumnCount>
void SetOrtho(VMatrix<Scalar, RowCount, ColumnCount>& result,
			  Scalar left, Scalar right, Scalar top, Scalar bottom,
			  Scalar near, Scalar far)
{
	Identity(result);

	

    result.Set(0,0, 2/(right-left));
	result.Set(1,1, 2/(top-bottom));
	result.Set(2,2, -2/(far-near));
	
	Scalar tx = (right+left)/(right-left);
	Scalar ty = (top+bottom)/(top-bottom);
	Scalar tz = (far+near)/(far-near);

	result.Set(0,3, tx);
	result.Set(1,3, ty);
	result.Set(2,3, tz);
	result.Set(3,3, -1);
}


/**
 * @author: sheijk
 */
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

/**
 * Makes the given matrix a scaling matrix
 *
 * Example:
 * To create a matrix which will scale to half of the original size
 *
 * VMatrix44f scaleMatrix;
 * SetScale(scaleMatrix, .5f);
 *
 * @author: sheijk
 */
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

/**
 * @author: sheijk
 */
void Translate(VMatrix44f& matrix, float x, float y, float z);

/**
 * @author: sheijk
 */
void RotateX(VMatrix44f& matrix, float angle);

/**
 * @author: sheijk
 */
void RotateY(VMatrix44f& matrix, float angle);

/**
 * @author: sheijk
 */
void RotateZ(VMatrix44f& matrix, float angle);

/**
 * @author: sheijk
 */
void Scale(VMatrix44f& matrix, float factor);

/**
 * @author: sheijk
 */
VMatrix44f IdentityMatrix();

/**
 * @author: sheijk
 */
VMatrix44f TranslationMatrix(float x, float y, float z);

/**
 * @author: sheijk
 */
VMatrix44f RotationXMatrix(float angle);

/**
 * @author: sheijk
 */
VMatrix44f RotationYMatrix(float angle);

/**
 * @author: sheijk
 */
VMatrix44f RotationZMatrix(float angle);

/**
 * @author sheijk
 */
VPointer<VMatrix44f>::SharedPtr IdentityPtr();

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_TRANSFORMATIONOPS_2004_04_09_H
