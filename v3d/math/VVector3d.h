#ifndef V3D_VVECTOR3D_H
#define V3D_VVECTOR3D_H

#include <Math/VMath.h>

class VVector3d
{
private :
	
	vfloat64 m_pdVector[3];

public :

	VVector3d(void);
	VVector3d(const vfloat64 in_dX, const vfloat64 in_dY, const vfloat64 in_dZ);
	VVector3d(const vfloat64* in_pdVector);
	VVector3d(const VVector3d& in_rVector);

	inline vfloat64& operator [] (const vint in_iIndex) const;

	inline VVector3d& Set(const vfloat64 in_dX, const vfloat64 in_dY, const vfloat64 in_dZ);
	
	inline VVector3d& operator = (const vfloat64 in_pdV[]);
	inline VVector3d& operator = (const VVector3d& in_rV);

	inline vbool operator == (const vfloat64 in_pdV[]) const;
	inline vbool operator == (const VVector3d& in_rV) const;
	inline vbool operator != (const vfloat64 in_pdV[]) const;
	inline vbool operator != (const VVector3d& in_rV) const;

	inline VVector3d& Add(const VVector3d& in_rV, const vfloat64 in_dS);
	inline VVector3d& Subtract(const VVector3d& in_rV, const vfloat64 in_dS);
	inline VVector3d& Multiply(const VVector3d& in_rV, const vfloat64 in_dS);
	inline VVector3d& Divide(const VVector3d& in_rV, const vfloat64 in_dS);
	inline VVector3d& Add(const VVector3d& in_rA, const VVector3d& in_rB);
	inline VVector3d& Subtract(const VVector3d& in_rA, const VVector3d& in_rB);

	inline VVector3d operator + (const vfloat64 in_dS) const;
	inline VVector3d operator + (const vfloat64 in_pdV[]) const;
	inline VVector3d operator + (const VVector3d& in_rV) const;
	inline VVector3d operator - (const vfloat64 in_dS) const;
	inline VVector3d operator - (const vfloat64 in_pdV[]) const;
	inline VVector3d operator - (const VVector3d& in_rV) const;
	inline VVector3d operator * (const vfloat64 in_dS) const;
	inline VVector3d operator * (const vfloat64 in_pdV[]) const;
	inline VVector3d operator * (const VVector3d& in_rV) const;
	inline VVector3d operator / (const vfloat64 in_dS) const;
	inline VVector3d operator / (const vfloat64 in_pdV[]) const;
	inline VVector3d operator / (const VVector3d& in_rV) const;

	inline VVector3d& operator += (const vfloat64 in_dS);
	inline VVector3d& operator += (const vfloat64 in_pdV[]);
	inline VVector3d& operator += (const VVector3d& in_rV);
	inline VVector3d& operator -= (const vfloat64 in_dS);
	inline VVector3d& operator -= (const vfloat64 in_pdV[]);
	inline VVector3d& operator -= (const VVector3d& in_rV);
	inline VVector3d& operator *= (const vfloat64 in_dS);
	inline VVector3d& operator *= (const vfloat64 in_pdV[]);
	inline VVector3d& operator *= (const VVector3d& in_rV);
	inline VVector3d& operator /= (const vfloat64 in_dS);
	inline VVector3d& operator /= (const vfloat64 in_pdV[]);
	inline VVector3d& operator /= (const VVector3d& in_rV);

	inline vfloat64 Magnitude(void) const;
	inline vfloat64 MagnitudeSquared(void) const;

	inline VVector3d& Normalize(void);
	inline VVector3d& Normalize(const VVector3d& in_rV);

	inline vfloat64 Dot(const VVector3d& in_rV) const;
	inline VVector3d Cross(const VVector3d& in_rV) const;
	inline VVector3d& Cross(const VVector3d& in_rA, const VVector3d& in_rB);
	inline void Random(void);
};

#include <Math/VVector3D.inl>

#endif