#ifndef V3D_VMATH_H
#define V3D_VMATH_H

#include <Core/VTypes.h>

#include <math.h>
#include <stdlib.h>

class VMath
{
public :
	
	static inline vfloat32 Rand(const vfloat32 in_fMin, const vfloat32 in_fMax);
	static inline vuint Log2(const vuint in_uiVal);

	//
	// *** ToDegrees ***
	//
	// Synopsis:
	//    - Converts a value from radians to degrees.
	//
	// Inputs:
	//    - const vfloat32 in_fAgle: The angle which shall be converted to degrees.
	//
	// Returns:
	//    - vfloat32: The converted value.
	//
	// Notes:
	//    - 
	//
	// See also:
	//    - VMath::ToRadians
	//
	// Example: 
	//    - vfloat32 fRad = VMath::PI / 2.0f;
	//		vfloat32 fDeg = VMath::ToDegrees(fRad);
	//
	static inline vfloat32 ToDegrees(const vfloat32 in_fAngle);
	static inline vfloat32 ToRadians(const vfloat32 in_fAngle);

	static const vfloat32 EPSILON;
	static const vfloat32 PI;
};

#include <Math/VMath.inl>

#endif