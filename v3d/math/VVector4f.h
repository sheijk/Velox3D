#ifndef V3D_VVECTOR4F_H
#define V3D_VVECTOR4F_H

#include <Math/VMath.h>

//
// *** VVector4f ***
//
// Synopsis:
//    - Use instances of this class to encapsulate operations with four dimensional
//		vectors (not quaternions).
//
// See also:
//    - VVector4d
//
class VVector4f 
{
private :
	
	vfloat32 m_pfVector[4];

public :

	//
	// *** VVector4f ***
	//
	// Synopsis:
	//    - The object's standard constructor initializing the x-, y- and
	//		z-component by 0 and the w-component by 1.
	//
	// Example: 
	//    - VVector4f v1;
	//
	VVector4f(void);

	//
	// *** VVector4f ***
	//
	// Synopsis:
	//    - A constructor using which the member data can be initilialized directly
	//		with some floating point values.
	//
	// Inputs:
	//    - const vfloat32 in_fX: The x-component of the vector.
	//	  - const vfloat32 in_fY: The y-component of the vector.
	//	  - const vfloat32 in_fZ: The z-component of the vector.
	//	  - const vfloat32 in_fW: The w-component of the vector.
	//
	// Example: 
	//    - VVector4f v1(0.0f, 0.0f, 0.0f, 1.0f);
	//
	VVector4f(const vfloat32 in_fX, const vfloat32 in_fY, const vfloat32 in_fZ, const vfloat32 in_fW);

	//
	// *** VVector4f ***
	//
	// Synopsis:
	//    - A constructor accepting an one-dimensional array of floats with which
	//		the member data is being initialized.
	//
	// Inputs:
	//    - const vfloat32 in_pfV[]: The array containing the values with which the
	//				object is being initialized.
	//
	// Example: 
	//    - vfloat32 pfV[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//		VVector4f v1(pfV);
	//
	VVector4f(const vfloat32 in_pfV[]);

	//
	// *** VVector4f ***
	//
	// Synopsis:
	//    - Copy constructor.
	//
	// Inputs:
	//    - const VVector4f& in_rV: A reference to the input vector whose members
	//				values shall be copied to this object.
	//
	// Example: 
	//    - VVector4f v1(2.0f, 2.0f, 2.0f, 1.0f);
	//		VVector4f v2(v1);
	//
	VVector4f(const VVector4f& in_rV);

	//
	// *** Set ***
	//
	// Synopsis:
	//    - Assign new values to the elements of the vector.
	//
	// Inputs:
	//    - const vfloat32 in_fX: The new x-component of the vector.
	//	  - const vfloat32 in_fY: The new y-component of the vector.
	//	  - const vfloat32 in_fZ: The new z-component of the vector.
	//	  - const vfloat32 in_fW: The new w-component of the vector.
	//
	// Returns:
	//    - VVector4f&: A reference to the current vector object whose elements were
	//				modified by this function.
	//
	// Notes:
	//    - For assigning new values from an already existing vector or an array of
	//		values, better use the overloaded "=" operator.
	//
	// Example: 
	//    - VVector4f v;
	//		v.Set(0.0f, 0.0f, 0.0f, 1.0f);
	//
	inline VVector4f& Set(const vfloat32 in_fX, const vfloat32 in_fY, const vfloat32 in_fZ, const vfloat32 in_fW);
	inline VVector4f& operator = (const vfloat32 in_pfV[]);
	inline VVector4f& operator = (const VVector4f& in_rV);

	inline VVector4f& operator += (const vfloat32 in_fS);
	inline VVector4f& operator += (const vfloat32 in_pfV[]);
	inline VVector4f& operator += (const VVector4f& in_rV);
	inline VVector4f& operator -= (const vfloat32 in_fS);
	inline VVector4f& operator -= (const vfloat32 in_pfV[]);
	inline VVector4f& operator -= (const VVector4f& in_rV);
	inline VVector4f& operator *= (const vfloat32 in_fS);
	inline VVector4f& operator *= (const vfloat32 in_pfV[]);
	inline VVector4f& operator *= (const VVector4f& in_rV);
	inline VVector4f& operator /= (const vfloat32 in_fS);
	inline VVector4f& operator /= (const vfloat32 in_pfV[]);
	inline VVector4f& operator /= (const VVector4f& in_rV);

	inline VVector4f operator + (const vfloat32 in_fS) const;
	inline VVector4f operator + (const vfloat32 in_pfV[]) const;
	inline VVector4f operator + (const VVector4f& in_rV) const;
	inline VVector4f operator - (const vfloat32 in_fS) const;
	inline VVector4f operator - (const vfloat32 in_pfV[]) const;
	inline VVector4f operator - (const VVector4f& in_rV) const;
	inline VVector4f operator * (const vfloat32 in_fS) const;
	inline VVector4f operator * (const vfloat32 in_pfV[]) const;
	inline VVector4f operator * (const VVector4f& in_rV) const;
	inline VVector4f operator / (const vfloat32 in_fS) const;
	inline VVector4f operator / (const vfloat32 in_pfV[]) const;
	inline VVector4f operator / (const VVector4f& in_rV) const;

	inline vfloat32 Dot(const VVector4f& in_rV) const;
};

#include <Math/VVector4f.inl>

#endif