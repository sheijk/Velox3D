#ifndef V3D_VVECTOR3F_H
#define V3D_VVECTOR3F_H

#include <Math/VMath.h>

#include <math.h>
#include <stdlib.h>

//
// *** VVector3f ***
//
// Synopsis:
//    - This class is used to encapsulate operations for three-dimensional vectors
//		with single precision.
//
// See also:
//    - VVector3d
//
class VVector3f
{
private :

	vfloat32 m_pfVector[3];

public :
	
	//
	// *** VVector3f ***
	//
	// Synopsis:
	//    - The object's standard constructor initializing all members by zero.
	//
	// Example: 
	//    - VVector3f v1;
	//
	VVector3f(void);

	//
	// *** VVector3f ***
	//
	// Synopsis:
	//    - A constructor which can be used to directly initialize the elements of
	//		the object with floating point values.
	//
	// Inputs:
	//    - const vfloat32 in_fX: The x-value the vector will be initialized with.
	//	  - const vfloat32 in_fY: The y-value the vector will be initialized with.
	//	  - const vfloat32 in_fZ: The z-value the vector will be initialized with.
	//
	// Example: 
	//    - VVector3f v1(1.0f, 1.0f, 1.0f);
	//
	VVector3f(const vfloat32 in_fX, const vfloat32 in_fY, const vfloat32 in_fZ);

	//
	// *** VVector3f ***
	//
	// Synopsis:
	//    - A constructor which can be used to directly initialized the elements of
	//		the object with values from an existent float-array.
	//
	// Inputs:
	//    - const vfloat32 in_pfV[]: The array containg the values with which the
	//				elements of the vector shall be initialized.
	//
	// Example: 
	//    - vfloat32[] pfValues = { 1.0f, 1.0f, 1.0f };
	//		VVector3f v(pfValues);
	//
	VVector3f(const vfloat32 fV[]);

	//
	// *** VVector3f ***
	//
	// Synopsis:
	//    - The copy constructor of VVector3f.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The input vector with whose elements the current
	//		vector will be filled.
	//
	// Example: 
	//    - VVector3f v1(1.0f, 1.0f, 1.0f);
	//		VVector3f v2(v1);
	//
	VVector3f(const VVector3f& in_rV);

	//
	// *** operator [] ***
	//
	// Synopsis:
	//    - Use this operator to gain direct read-write access to members of the
	//		vector.
	//
	// Inputs:
	//    - const vint in_iIndex: The index of the element one wants to get access
	//				to. Use "0" for the x-component, "1" for the y-component and
	//				"2" for access to the z-component.
	//
	// Returns:
	//    - vfloat32&: A reference to the chosen member of the vector.
	//
	// Example: 
	//    - VVector3f v(1.0f, 1.0f, 1.0f);
	//		vfloat32 fVal = v[0] + v[1] + v[2];
	//
	inline vfloat32& operator [] (const vint in_iIndex) const;

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
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector object whose elements were
	//				modified by this function.
	//
	// Notes:
	//    - For assigning new values from an already existing vector, better use the
	//		overloaded operator "=".
	//
	// Example: 
	//    - VVector3f v;
	//		v.Set(1.0f, 1.0f, 1.0f);
	//
	inline VVector3f& Set(const vfloat32 in_fX, const vfloat32 in_fY, const vfloat32 in_fZ);

	//
	// *** operator = ***
	//
	// Synopsis:
	//    - Assign some new values from a floating point array to the elements of
	//		the current object.
	//
	// Inputs:
	//    - const vfloat32 in_pfV[]: The float array from which the new values of
	//				the vector object are being read.
	//
	// Returns:
	//    - VVector3f&: A reference to the current newly initialized vector.
	//
	// Example: 
	//    - vfloat32 pfValues[] = { 1.0f, 2.0f, 3.0f };
	//		VVector3f v = pfValues;
	//
	inline VVector3f& operator = (const vfloat32 in_pfV[]);

	//
	// *** operator = ***
	//
	// Synopsis:
	//    - Assign the elements of an existing vector to the ones of the currently
	//		selected object.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The vector whose element's values are being
	//				assigned to the one in the current vector.
	//
	// Returns:
	//    - VVector3f&: A reference to the newly initialized vector.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		VVector3f v2 = v1;
	//
	inline VVector3f& operator = (const VVector3f& in_rV);

	//
	// *** operator == ***
	//
	// Synopsis:
	//    - Performs a check if two vectors are equal.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The vector to perform the test with.
	//
	// Returns:
	//    - VVector3f: Returns "true" if the two vectors are equal and "false" if
	//				this is not the case.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		VVector3f v2(1.0f, 2.0f, 3.0f);
	//		if (v1 == v2)
	//		{
	//			DoSomething();
	//		}
	//
	inline vbool operator == (const VVector3f& in_rV) const;

	//
	// *** operator != ***
	//
	// Synopsis:
	//    - Performs a check if two vectors are not equal.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The vector to perform the test with.
	//
	// Returns:
	//    - VVector3f: Returns "false" if the two vectors are equal and "true" if
	//				this is not the case.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		VVector3f v2(1.0f, 2.0f, 3.0f);
	//		if (v1 != v2)
	//		{
	//			DoSomething();
	//		}
	//
	inline vbool operator != (const VVector3f& in_rV) const;

	//
	// *** Add ***
	//
	// Synopsis:
	//    - Use this function to add a float to each element of a vector and store
	//		the result in the current object.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The input vector to whose elements the value
	//				will be added.
	//	  - const vfloat32 in_fS: The scalar value which is being added to the
	//				elements of the input vector.
	//
	// Returns:
	//    - VVector3f&: A reference to the current object.
	//
	// See also:
	//    - VVector3f::Subtract()
	//	  - VVector3f::Multiply()
	//	  - VVector3f::Divide()
	//
	// Example: 
	//    - VVector3f v(1.0f, 0.0f, 0.0f);
	//		v.Add(v, 1.0f);
	//
	inline VVector3f& Add(const VVector3f& in_rV, const vfloat32 in_fS);

	//
	// *** Subtract ***
	//
	// Synopsis:
	//    - Subtract a scalar from each element of a specified vector and store the
	//		result in the current object.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The vector from whose elements the scalar shall
	//				be subtracted.
	//	  - const vfloat32 in_fS: The scalar value which will be subtracted from
	//				each element of the input vector.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector.
	//
	// See also:
	//    - VVector3f::Add()
	//	  - VVector3f::Multiply()
	//	  - VVector3f::Divide()
	//
	// Example: 
	//    - VVector3f v(1.0f, 2.0f, 1.0f);
	//		v.Subtract(v, 1.0f);
	//
	inline VVector3f& Subtract(const VVector3f& in_rV, const vfloat32 in_fS);

	//
	// *** Multiply ***
	//
	// Synopsis:
	//    - Multiply each element of a specified vector with a scalar.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The vector whose elements will be multiplied
	//				with the scalar value.
	//	  - const vfloat32 in_fS: The scalar value with which all members of the
	//				input vector will be multiplied.
	//
	// Returns:
	//    - VVector3f&: A reference to the modified vector object.
	//
	// See also:
	//    - VVector3f::Add()
	//	  - VVector3f::Subtract()
	//	  - VVector3f::Divide()
	//
	// Example: 
	//    - VVector3f v(1.0f, 1.0f, 1.0f);
	//		v.Multiply(v, 2.0f);
	//
	inline VVector3f& Multiply(const VVector3f& in_rV, const vfloat32 in_fS);

	//
	// *** Divide ***
	//
	// Synopsis:
	//    - Use this function to divide each element of a vector by a specified
	//		scalar value and store the result in the current object.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The input vector whose elements will be divided
	//				by the input scalar.
	//	  - const vfloat32 in_fS: The scalar with which the elements of the input
	//				vector shall be divided.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector object.
	//
	// See also:
	//    - VVector3f::Add()
	//	  - VVector3f::Multiply()
	//	  - VVector3f::Subtract()
	//
	// Example: 
	//    - VVector3f v(1.0f, 2.0f, 3.0f);
	//		v.Divide(v, 2.0f);
	//
	inline VVector3f& Divide(const VVector3f& in_rV, const vfloat32 in_fS);

	//
	// *** Add ***
	//
	// Synopsis:
	//    - Add the elements of the second input vector to the ones of the first and
	//		store the result in the current vector object.
	//
	// Inputs:
	//    - const VVector3f& in_rA: The first input vector to the whose elements the
	//				elements of the second on whill be added.
	//	  - const VVector3f& in_rB: The second input vector which elements will be
	//				added to the ones of the first input vector.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector.
	//
	// See also:
	//    - VVector3f::Divide()
	//	  - VVector3f::Multiply()
	//	  - VVector3f::Subtract()
	//
	// Example: 
	//    - VVector3f v;
	//		v.Add(VVector3f(1.0f, 0.0f, 1.0f), VVector3f(0.0f, 1.0f, 0.0f));
	//
	inline VVector3f& Add(const VVector3f& in_rA, const VVector3f& in_rB);

	//
	// *** Subtract ***
	//
	// Synopsis:
	//    - Subtract the elements of the second input vector from the ones of the
	//		first input vector and store the result in the current vector object.
	//
	// Inputs:
	//    - const VVector3f& in_rA: The vector from whose elements the elements of
	//				the second vector will be subtracted.
	//	  - const VVector3f& in_rB: The vector whose elements are subtracted from
	//				the elements of the first input vector.
	//
	// Returns:
	//    - VVector3f&: A reference to the modified vector object.
	//
	// See also:
	//    - VVector3f::Add()
	//	  - VVector3f::Divide()
	//	  - VVector3f::Multiply()
	//
	// Example: 
	//    - VVector3f v;
	//		v.Subtract(VVector3f(2.0f, 2.0f, 2.0f), VVector3f(1.0f, 1.0f, 1.0f));
	//
	inline VVector3f& Subtract(const VVector3f& in_rA, const VVector3f& in_rB);

	//
	// *** operator + ***
	//
	// Synopsis:
	//    - Add a floating point value to the elements of an existing vector and
	//		return the newly initialized vector.
	//
	// Inputs:
	//    - const vfloat32 in_fS: The scalar which is being added to all elements of
	//				the current vector to compute the resulting vector.
	//
	// Returns:
	//    - VVector3f: The newly initialized vector.
	//
	// Example: 
	//    - VVector3f v1(1.0f, 1.0f, 1.0f);
	//		VVector3f v2 = v1 + 2.0f;
	//
	inline VVector3f operator + (const vfloat32 in_fS) const;

	//
	// *** operator - ***
	//
	// Synopsis:
	//    - Subtract a floating point value from the elements of an existing vector
	//		and return the newly initialized vector.
	//
	// Inputs:
	//    - const vfloat32 in_fS: The scalar which is being subtracted from all
	//				elements of the current vector to compute the resulting vector.
	//
	// Returns:
	//    - VVector3f: The newly initialized vector.
	//
	// Example: 
	//    - VVector3f v1(1.0f, 1.0f, 1.0f);
	//		VVector3f v2 = v1 - 2.0f;
	//
	inline VVector3f operator - (const vfloat32 in_fS) const;

	//
	// *** operator * ***
	//
	// Synopsis:
	//    - Multiply all elements of an existing vector with a scalar and return the
	//		newly initialized vector.
	//
	// Inputs:
	//    - const vfloat32 in_fS: The scalar with which all elements of the current
	//				vector are being initialized to get the returned vector.
	//
	// Returns:
	//    - VVector3f: The newly initialized vector.
	//
	// Example: 
	//    - VVector3f v1(1.0f, 2.0f, 1.0f);
	//		VVector3f v2 = v1 * 2.0f;
	//
	inline VVector3f operator * (const vfloat32 in_fS) const;

	//
	// *** operator / ***
	//
	// Synopsis:
	//    - Divide all elements of an vector by a floating point value and return a
	//		newly initialized vector object.
	//
	// Inputs:
	//    - const vfloat32 in_fS: The scalar by which all elements of the current
	//				vector are divided to get the new vector.
	//
	// Returns:
	//    - VVector3f: The newly initialized vector.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		VVector3f v2 = v1 / 2.0f;
	//
	inline VVector3f operator / (const vfloat32 in_fS) const;

	//
	// *** operator + ***
	//
	// Synopsis:
	//    - Add the elements of the input vector to the ones of the current vector
	//		and return a new vector initialized with the result of the operation.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The vector whose elements are being added to the
	//				ones of the current vector object.
	//
	// Returns:
	//    - VVector3f: The newly initialized vector.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		VVector3f v2(1.0f, 1.0f, 1.0f);
	//		VVector3f v3 = v1 + v2;
	//
	inline VVector3f operator + (const VVector3f& in_rV) const;

	//
	// *** operator - ***
	//
	// Synopsis:
	//    - Subtract the elements of the input vector from the ones of the current
	//		object and return a new vector initialized with these values.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The vector whose elements are being subtracted
	//				from the ones of the current vector object.
	//
	// Returns:
	//    - VVector3f: The newly initialized vector.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		VVector3f v2(1.0f, 1.0f, 1.0f);
	//		VVector3f v3 = v1 - v2;
	//
	inline VVector3f operator - (const VVector3f& in_rV) const;

	//
	// *** operator += ***
	//
	// Synopsis:
	//    - Add a scalar to each element of the current vector.
	//
	// Inputs:
	//    - const vfloat32 in_fS: The scalar value which is being added to all
	//				elements of the vector.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector object.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		v2 += 1.0f;
	//
	inline VVector3f& operator += (const vfloat32 in_fS);

	//
	// *** operator -= ***
	//
	// Synopsis:
	//    - Subtract a scalar from the elements of the current vector.
	//
	// Inputs:
	//    - const vfloat32 in_fS: The scalar which is being subtracted from the
	//				elements of the current vector object.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector object.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		v2 -= 1.0f;
	//
	inline VVector3f& operator -= (const vfloat32 in_fS);

	//
	// *** operator *= ***
	//
	// Synopsis:
	//    - Multiply all elements from the current vector with a scalar.
	//
	// Inputs:
	//    - const vfloat32 in_fS: The scalar with which all elements of the current
	//				vector are being multiplied.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector object.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		v2 *= 2.0f;
	//
	inline VVector3f& operator *= (const vfloat32 in_fS);

	//
	// *** operator /= ***
	//
	// Synopsis:
	//    - Divide all elements of the current vector by a scalar
	//
	// Inputs:
	//    - const vfloat32 in_fS: The scalar by which all elements of the current
	//				vector are being divided.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector object.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		v2 /= 2.0f;
	//
	inline VVector3f& operator /= (const vfloat32 in_fS);
	
	//
	// *** operator += ***
	//
	// Synopsis:
	//    - Add the elements of the input vector to the ones of the current vector.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The vector whose elements are being added to the
	//		ones of the current vector object.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector object.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		VVector3f v2(1.0f, 1.0f, 1.0f);
	//		v2 += v1;
	//
	inline VVector3f& operator += (const VVector3f &V);

	//
	// *** operator -= ***
	//
	// Synopsis:
	//    - Subtract the elements of the input vector from the ones of the currently
	//		selected vector.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The vector whose elements are being subtracted
	//				from the ones of the current vector object.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector object.
	//
	// Example: 
	//    - VVector3f v1(2.0f, 2.0f, 2.0f);
	//		VVector3f v2(1.0f, 1.0f, 1.0f);
	//		v2 -= v1;
	//
	inline VVector3f& operator -= (const VVector3f &V);

	//
	// *** Magnitude ***
	//
	// Synopsis:
	//    - Returns the length of the vector.
	//
	// Description:
	//    - Use this function to compute the magnitude of a vector using the formula
	//		l = sqrt(x² + y² + z²).
	//
	// Returns:
	//    - vfloat32: The length of the vector.
	//
	// See also:
	//    - VVector3f::MagnitudeSquared()
	//
	// Example: 
	//    - VVector3f v(1.0f, 0.0f, 0.0f);
	//		vfloat32 fLen = v.Magnitude();
	//
	inline vfloat32 Magnitude(void) const;

	//
	// *** MagnitudeSquared ***
	//
	// Synopsis:
	//    - Returns the squared length of the vector.
	//
	// Description:
	//    - Use this function to compute the squared magnitude of a vector using the formula
	//		l = x² + y² + z².
	//
	// Returns:
	//    - vfloat32: The length of the vector.
	//
	// See also:
	//    - VVector3f::Magnitude()
	//
	// Example: 
	//    - VVector3f v(1.0f, 0.0f, 0.0f);
	//		vfloat32 fLenSquared = v.MagnitudeSquared();
	//
	inline vfloat32 MagnitudeSquared(void) const;

	//
	// *** Normalize ***
	//
	// Synopsis:
	//    - Normalize the magnitude of the current vector object.
	//
	// Returns:
	//    - VVector3f&: A reference to the modified vector object.
	//
	// Example: 
	//    - VVector3f v(2.0f, 2.0f, 2.0f);
	//		v.Normalize();
	//
	inline VVector3f& Normalize(void);

	//
	// *** Normalize ***
	//
	// Synopsis:
	//    - Normalize the magnitude of an input vector and store the result in the
	//		current object.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The input vector whose magnitude will be
	//				normalized.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector in which the normalized
	//				vector has been stored.
	//
	// Example: 
	//    - VVector3f v;
	//		v.Normalize(VVector3f(1.0f, 2.0f, 3.0f));
	//
	inline VVector3f& Normalize(const VVector3f& in_rV);

	//
	// *** Dot ***
	//
	// Synopsis:
	//    - Computes the dotproduct of the current vector with the input vector.
	//
	// Description:
	//	  - The dotproduct is necessary for angle computations between to vectors
	//		and such stuff. It is being computed using the formula
	//		d = x1 * x2 + y1 * y1 + z1 * z2.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The second vector with which the dotproduct
	//				shall be computed.
	//
	// Returns:
	//    - VVector3f&: The scalar value resulting from the dotproduct of the two
	//				vectors.
	//
	// Example: 
	//    - VVector3f v(1.0f, 1.0f, 1.0f);
	//		vfloat32 fDot = v.Dot(VVector3f(2.0f, 3.0f, 2.0f));
	//
	inline vfloat32 Dot(const VVector3f& in_rV) const;
	
	//
	// *** Cross ***
	//
	// Synopsis:
	//    - Use this function to compute the normal vector of the plane spanned up
	//		by the current vector and the input vector.
	//
	// Description:
	//	  - The crossproduct is used to compute a normal vector of the plane spanned
	//		up by two vectors. Note that this operation is not commutative and thus
	//		the order of the vectors is important. The crossproduct itself is based
	//		on the formula :
	//			nx = y1 * z2 - y2 * z1
	//			ny = z1 * x2 - z2 * x1
	//			nz = x1 * y2 - x2 * y1
	//		Note that the resulting vector is not normalized.
	//
	// Inputs:
	//    - const VVector3f& in_rV: The input vector with which the crossproduct
	//				will be computed.
	//
	// Returns:
	//    - VVector3f: The resulting normal vector.
	//
	// Example: 
	//    - VVector3f v1(1.0f, 1.0f, 1.0f);
	//		VVector3f v2(2.0f, 2.0f, 2.0f);
	//		VVector3f vNormal = v1.Cross(v2);
	//
	inline VVector3f Cross(const VVector3f& in_rV);

	//
	// *** Cross ***
	//
	// Synopsis:
	//    - Use this function to compute the normal vector of the plane spanned up
	//		by the two input vectors and store it in the current vector object.
	//
	// Description:
	//	  - The crossproduct is used to compute a normal vector of the plane spanned
	//		up by two vectors. Note that this operation is not commutative and thus
	//		the order of the vectors is important. The crossproduct itself is based
	//		on the formula :
	//			nx = y1 * z2 - y2 * z1
	//			ny = z1 * x2 - z2 * x1
	//			nz = x1 * y2 - x2 * y1
	//		Note that the resulting vector is not normalized.
	//
	// Inputs:
	//    - const VVector3f& in_rA: The first input vector which is used for the
	//				crossproduct.
	//		const VVector3f& in_rB: The second vector needed for the crossproduct.
	//
	// Returns:
	//    - VVector3f&: A reference to the current vector i.e. the resulting normal
	//		vector.
	//
	// Example: 
	//    - VVector3f v1(1.0f, 1.0f, 1.0f);
	//		VVector3f v2(2.0f, 2.0f, 2.0f);
	//		VVector3f v3;
	//		v3.Cross(v1, v2);
	//
	inline VVector3f& Cross(const VVector3f& in_rA, const VVector3f& in_rB);

	//
	// *** Random ***
	//
	// Synopsis:
	//    - Fills all elements of the vector with random values.
	//
	// Example: 
	//    - VVector3f v;
	//		v.Random();
	//
	inline void Random(void);
};

#include <Math/VVector3f.inl>

#endif