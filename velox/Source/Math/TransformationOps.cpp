#include <V3dLib/Math.h>
//-----------------------------------------------------------------------------

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

void Scale(VMatrix44f& matrix, float factor)
{
	VMatrix44f scale;
	SetScale(scale, factor);
	Mult(matrix, matrix, scale);
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

VPointer<VMatrix44f>::SharedPtr IdentityPtr()
{
	VPointer<VMatrix44f>::SharedPtr pMatrix(new VMatrix44f());
	Identity(*pMatrix);

	return pMatrix;
}

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
