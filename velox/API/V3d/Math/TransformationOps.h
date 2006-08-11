#ifndef V3D_TRANSFORMATIONOPS_2004_04_09_H
#define V3D_TRANSFORMATIONOPS_2004_04_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Math/VMatrix.h>
#include <V3d/Math/VVector.h>
#include <V3d/Math/VQuaternion.h>
#include <V3d/Core/SmartPtr/VGuards.h>
#include <V3d/Math/VRBTransform.h>

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
* @author: lars
*/
template<typename Scalar, vuint RowCount, vuint ColumnCount>
void SetRotationAxis(VMatrix<Scalar, RowCount, ColumnCount>& result, VVector<Scalar, 3> in_Axis, Scalar in_RotAngle)
{
	Identity(result);

	Normalize(in_Axis);

	Scalar sinus   = sin(in_RotAngle);
	Scalar cosinus = cos(in_RotAngle);

	result.Set(0,0, in_Axis.GetX() * in_Axis.GetX() * (1-cosinus) + cosinus);
	result.Set(1,0, in_Axis.GetX() * in_Axis.GetY() * (1-cosinus) - (in_Axis.GetZ() * sinus));
	result.Set(2,0, in_Axis.GetX() * in_Axis.GetZ() * (1-cosinus) + (in_Axis.GetY() * sinus));

	result.Set(0,1, in_Axis.GetY() * in_Axis.GetX() * (1-cosinus) + (in_Axis.GetZ() * sinus));
	result.Set(1,1, in_Axis.GetY() * in_Axis.GetY() * (1-cosinus) + cosinus);
	result.Set(2,1, in_Axis.GetY() * in_Axis.GetZ() * (1-cosinus) - (in_Axis.GetX() * sinus));

	result.Set(0,2, in_Axis.GetZ() * in_Axis.GetX() * (1-cosinus) - (in_Axis.GetY() * sinus));
	result.Set(1,2, in_Axis.GetZ() * in_Axis.GetY() * (1-cosinus) + (in_Axis.GetX() * sinus));
	result.Set(2,2, in_Axis.GetZ() * in_Axis.GetZ() * (1-cosinus) + cosinus);
}

///**
//* @author: lars
//*/
//template<typename Scalar>
//void SetQuaternionRotation(VVector<Scalar, 3> io_Vector, VQuaternion<Scalar>& in_Rotation)
//{
//	Scalar x1; 
//	Scalar y1;
//	Scalar z1; 
//	Scalar w1;
//	Scalar x2; 
//	Scalar y2;
//	Scalar z2; 
//	Scalar w2;
//	in_Rotation.Get(x1, y1, z1, w1);
//
//	VQuaternion<Scalar> Quat(io_Vector.GetX() * w1 + io_Vector.GetZ() * y1 - io_Vector.GetY() * z1,
//		io_Vector.GetY() * w1 + io_Vector.GetX() * z1 - io_Vector.GetZ() * x1,
//		io_Vector.GetZ() * w1 + io_Vector.GetY() * x1 - io_Vector.GetX() * y1,
//		io_Vector.GetX() * x1 + io_Vector.GetY() * y1 + io_Vector.GetZ() * z1);
//
//	Quat.Get(x2, y2, z2, w2);
//
//	io_Vector = VVector<Scalar, 3>(w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2,
//		w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2,
//		w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2);
//}

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
 * Turns the given matrix into a scaling matrix
 *
 * @author sheijk
 */
template<typename Scalar, vuint Dimension>
void SetScale(
	  VMatrix<Scalar, Dimension, Dimension>& out_ScaleMatrix,
	  const VVector<Scalar, Dimension>& in_ScaleComponents)
{
	Identity(out_ScaleMatrix);

	for(int dim = 0; dim < Dimension; ++dim)
		out_ScaleMatrix.Set(dim, dim, in_ScaleComponents[dim]);
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
* @author: lars
*/
void RotateAxis(VMatrix44f& matrix, VVector3f axis, float angle);

///**
//* @author: lars
//*/
//void Rotate(VVector3f rotate, VQuatf quaternion);



/**
 * @author: sheijk
 */
void Scale(VMatrix44f& matrix, float factor);

void Scale(VMatrix44f& io_Matrix, vfloat32 sx, vfloat32 sy, vfloat32 sz);

template<typename Scalar, vuint Dimension>
void Scale(VMatrix<Scalar, Dimension, Dimension>& io_Matrix,
	const VVector<Scalar, Dimension>& in_ScaleComponents)
{
	VMatrix<Scalar, Dimension, Dimension> scaleMatrix;
	SetScale(scaleMatrix, in_ScaleComponents);
	Mult(io_Matrix, io_Matrix, scaleMatrix);
}

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
VMatrix44f ScaleMatrix(vfloat32 sx);

/**
 * @author sheijk
 */
VPointer<VMatrix44f>::SharedPtr IdentityPtr();

void ApplyRow(VMatrix44f* io_pMatrix, vuint in_nRow, const VVector3f& in_Vector);
void ApplyColumn(
	VMatrix44f* io_pMatrix, vuint in_nColumn, const VVector3f& in_Vector);

void MakeTextureProjectionMatrix(
	VMatrix44f* out_pMatrix, const math::VRBTransform& in_Transform);

void MakeProjectionMatrix(VMatrix44f* out_pMatrix, 
	vfloat32 fovy, vfloat32 aspect, vfloat32 znear, vfloat32 zfar);

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_TRANSFORMATIONOPS_2004_04_09_H
