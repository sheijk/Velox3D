/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

%ignore v3d::math::VVector::m_Vec;
%ignore v3d::math::VVector::operator[];
%ignore v3d::math::VVector::operator=;
%include "../../API/V3d/Math/VVector.h"
%include "../../API/V3d/Math/VVectorOps.h"
%include "../../API/V3d/Math/VQuaternion.h"
%include "../../API/V3d/Math/VQuaternionOps.h"
%extend v3d::math::VVector {
	void Assign(const VVector& o) { *self = o; }
	
	void Add(const VVector& o) { *self += o; }
	void Sub(const VVector& o) { *self -= o; }
	VVector Plus(const VVector& o) { return *self + o; }
	VVector Minus(const VVector& o) { return *self - o; }
	
	Scalar Dot(const VVector& o) { return Dot(*self, o); }
	
	void Scale(float factor) { Mult(*self, factor); }
	void Scale(int factor) { Mult(*self, factor); }
	VVector Times(float factor) { return *self * factor; }
	VVector Times(int factor) { return *self * factor; }
	
	void Normalize() { Normalize(*self); }
	VVector Normalized() { return Normalized(*self); }
	
	float Length() { return Length(*self); }
	float LengthSquared() { return LengthSquared(*self); }
};
%template(VVector4f) v3d::math::VVector<vfloat32, 4>;
%template(VVector3f) v3d::math::VVector<vfloat32, 3>;
%extend v3d::math::VVector<vfloat32, 3> {
	VVector<vfloat32, 3>(float x, float y, float z) {
		return new math::VVector3f(x, y, z);
	}
	
	void SetX(float x) { self->SetX(x); }
	void SetY(float y) { self->SetY(y); }
	void SetZ(float z) { self->SetZ(z); }
	
	float GetX() { return self->GetX(); }
	float GetY() { return self->GetY(); }
	float GetZ() { return self->GetZ(); }
	
	void Set(float x, float y, float z) {
		self->SetX(x); self->SetY(y); self->SetZ(z);
	}
	
	void ApplyCross(const math::VVector3f& left, const math::VVector3f& right) {
		ApplyCross(*self, left, right);
	}
	math::VVector3f Cross(const math::VVector3f& right) {
		return Cross(*self, right);
	}
	
	void RotateAround(float angleRad, const math::VVector3f& axis) {
		v3d::math::VQuatf quat = math::QuatFromAxisAngle(axis, RadianToDegree(angleRad));
		v3d::math::Rotate(*self, quat);
	}
}

%rename(Assign) v3d::math::VMatrix::operator=;
%include "../../API/V3d/Math/VMatrix.h"
%include "../../API/V3d/Math/VMatrixOps.h"
%extend v3d::math::VMatrix {
	void Add(const VMatrix& other) { *self += other; }
	void Sub(const VMatrix& other) { *self -= other; }
	
	void MakeIdentity() { v3d::math::Identity(*self); }
	void MakeInverse() { v3d::math::MakeInverse(*self); }
	void MakeTranspose() { v3d::math::MakeTranspose(*self); }
	
	void SetToMult(const VMatrix& left, const VMatrix& right) {
		Mult(*self, left, right);
	}
	
	void MakeTranslation(float x, float y, float z) { SetTranslate(*self, x, y, z); }
	void MakeRotationX(float angle) { SetRotationX(*self, angle); }
	void MakeRotationY(float angle) { SetRotationY(*self, angle); }
	void MakeRotationZ(float angle) { SetRotationZ(*self, angle); }
	
	void MakeScale(float scale) { SetScale(*self, scale); }
	
	void MakeOrtho(float left, float right, float top, float bottom, float nearWindows_H_SUCKS, float farWindows_H_SUCKS) {
		SetOrtho(*self, left, right, top, bottom, nearWindows_H_SUCKS, farWindows_H_SUCKS);
	}
	
	void RotateX(float angle) { RotateX(*self, angle); }
	void RotateY(float angle) { RotateY(*self, angle); }
	void RotateZ(float angle) { RotateZ(*self, angle); }
};
%template(VMatrix44f) v3d::math::VMatrix<vfloat32, 4, 4>;
%extend v3d::math::VMatrix<vfloat32, 4, 4> {
	static math::VMatrix44f Identity() { return math::IdentityMatrix(); }
	static math::VMatrix44f Translation(float x, float y, float z) {
		return math::TranslationMatrix(x, y, z);
	}
	static math::VMatrix44f Scaling(float x, float y, float z) {
		math::VMatrix44f mat;
		SetScale(mat, ToVector4f(x, y, z, 1.0f));
		return mat;
	}
	static math::VMatrix44f Scaling(float factor) {
		return math::ScaleMatrix(factor);
	}
	static math::VMatrix44f RotationX(float angleRadians) {
		return math::RotationXMatrix(angleRadians);
	}
	static math::VMatrix44f RotationY(float angleRadians) {
		return math::RotationYMatrix(angleRadians);
	}
	static math::VMatrix44f RotationZ(float angleRadians) {
		return math::RotationZMatrix(angleRadians);
	}
	
	void ApplyRow(unsigned int rowNum, const math::VVector3f& vector) {
		ApplyRow(self, rowNum, vector);
	}
	void ApplyColumn(unsigned int columnNum, const math::VVector3f& vector) {
		ApplyColumn(self, columnNum, vector);
	}
};
%include "../../API/V3d/Math/VRBTransform.h"


