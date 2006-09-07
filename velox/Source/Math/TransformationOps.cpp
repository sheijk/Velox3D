/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Math.h>

// for MakeProjectionMatrix, 
//TODO: replace by implementation not depending on opengl!
#include <V3d/OpenGL.h>
#include <V3d/Graphics/OpenGLUtils.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace math {
//-----------------------------------------------------------------------------

void Translate(VMatrix44f& matrix, float x, float y, float z)
{
	VMatrix44f transl;
	SetTranslate(transl, x, y, z);
	Mult(matrix, matrix, transl);
}

void RotateX(VMatrix44f& matrix, float angle)
{
	VMatrix44f rot;
	SetRotationX(rot, angle);
	Mult(matrix, matrix, rot);
}

void RotateY(VMatrix44f& matrix, float angle)
{
	VMatrix44f rot;
	SetRotationY(rot, angle);
	Mult(matrix, matrix, rot);
}

void RotateZ(VMatrix44f& matrix, float angle)
{
	VMatrix44f rot;
	SetRotationZ(rot, angle);
	Mult(matrix, matrix, rot);
}

void RotateAxis(VMatrix44f& matrix, VVector3f axis, float angle)
{
	VMatrix44f rot;
	SetRotationAxis(rot, axis, angle);
	Mult(matrix, matrix, rot);
}

//void Rotate(VVector3f rotate, VQuatf quaternion)
//{
//	SetQuaternionRotation(rotate, quaternion);
//}

void Scale(VMatrix44f& matrix, float factor)
{
	VMatrix44f scale;
	SetScale(scale, factor);
	Mult(matrix, matrix, scale);
}

void Scale(VMatrix44f& io_Matrix, vfloat32 sx, vfloat32 sy, vfloat32 sz)
{
	VMatrix44f scaleMat;
	SetScale(scaleMat, ToVector4f(sx, sy, sz, 1.0f));
	Mult(io_Matrix, io_Matrix, scaleMat);
}

VMatrix44f IdentityMatrix()
{
	VMatrix44f identity;
	Identity(identity);
	return identity;
}

VMatrix44f TranslationMatrix(float x, float y, float z)
{
	VMatrix44f transl;
	SetTranslate(transl, x, y, z);
	return transl;
}

VMatrix44f RotationXMatrix(float angle)
{
	VMatrix44f rot;
	SetRotationX(rot, angle);
	return rot;
}

VMatrix44f RotationYMatrix(float angle)
{
	VMatrix44f rot;
	SetRotationY(rot, angle);
	return rot;
}

VMatrix44f RotationZMatrix(float angle)
{
	VMatrix44f rot;
	SetRotationZ(rot, angle);
	return rot;
}

VMatrix44f ScaleMatrix(vfloat32 sx)
{
	VMatrix44f scale;
	SetScale(scale, sx);
	return scale;
}

VPointer<VMatrix44f>::SharedPtr IdentityPtr()
{
	VPointer<VMatrix44f>::SharedPtr pMatrix(new VMatrix44f());
	Identity(*pMatrix);

	return pMatrix;
}

void ApplyRow(VMatrix44f* io_pMatrix, vuint in_nRow, const VVector3f& in_Vector)
{
	for(vuint column = 0; column < in_Vector.GetDimension(); ++column)
		io_pMatrix->Set(in_nRow, column, in_Vector.Get(column));
}

void ApplyColumn(VMatrix44f* io_pMatrix, vuint in_nColumn, const VVector3f& in_Vector)
{
	for(vuint row = 0; row < in_Vector.GetDimension(); ++row)
		io_pMatrix->Set(row, in_nColumn, in_Vector.Get(row));
}

void MakeTextureProjectionMatrix(
	VMatrix44f* out_pMatrix, const math::VRBTransform& in_Transform)
{
	Identity(*out_pMatrix);

	VVector3f xaxis = in_Transform.GetXAxis();
	VVector3f yaxis = in_Transform.GetYAxis();
	VVector3f zaxis = in_Transform.GetZAxis();
	yaxis.SetY(- yaxis.GetY());

	ApplyRow(out_pMatrix, 0, xaxis);
	ApplyRow(out_pMatrix, 1, yaxis);
	ApplyRow(out_pMatrix, 2, zaxis);

	VVector3f pos = in_Transform.GetPosition();
	Translate(*out_pMatrix, pos.GetX(), -pos.GetY(), pos.GetZ());
}

void MakeProjectionMatrix(VMatrix44f* out_pMatrix, 
	vfloat32 fovy, vfloat32 aspect, vfloat32 znear, vfloat32 zfar)
{
	vfloat32 origProj[16];
	glGetFloatv(GL_PROJECTION_MATRIX, origProj);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, znear, zfar);

	graphics::GetGLMatrix(GL_PROJECTION_MATRIX, out_pMatrix);

	glLoadMatrixf(origProj);
}

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------

