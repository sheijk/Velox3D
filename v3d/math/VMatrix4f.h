#ifndef V3D_VMATRIX4F_H
#define V3D_VMATRIX4F_H

#include <Math/VMath.h>
#include <Math/VVector3f.h>

class VMatrix4f
{

public :
	
	vfloat32 m_pfMatrix[4][4];



	//
	// *** VMatrix4f ***
	//
	// Synopsis:
	//    - Standard constructor of VMatrix4f which is directly initializing the
	//		member values with an identity matrix.
	//
	// Example: 
	//    - VMatrix4f* pMatrix = new VMatrix4f;
	//
	VMatrix4f(void);

	//
	// *** VMatrix4f ***
	//
	// Synopsis:
	//    - Constructor of VMatrix4f which is used for directly initializing the
	//		matrix with 16 floating point values.
	//
	// Inputs:
	//    - const vfloat32 in_fM11 ... const vfloat32 in_fM44: All elements of the
	//				matrix as single floating point values.
	//
	// Example: 
	//    - VMatrix4f m(1.0f, 0.0f, 0.0f, 0.0f,
	//					0.0f, 1.0f, 0.0f, 0.0f,
	//					0.0f, 0.0f, 1.0f, 0.0f,
	//					0.0f, 0.0f, 0.0f, 1.0f);
	//
	VMatrix4f(const vfloat32 in_fM11, const vfloat32 in_fM12, const vfloat32 in_fM13, const vfloat32 in_fM14,
			  const vfloat32 in_fM21, const vfloat32 in_fM22, const vfloat32 in_fM23, const vfloat32 in_fM24,
			  const vfloat32 in_fM31, const vfloat32 in_fM32, const vfloat32 in_fM33, const vfloat32 in_fM34,
			  const vfloat32 in_fM41, const vfloat32 in_fM42, const vfloat32 in_fM43, const vfloat32 in_fM44);

	//
	// *** VMatrix4f ***
	//
	// Synopsis:
	//    - Constructor of VMatrix4f accepting floating point values from an array
	//		to initialize the member data with.
	//
	// Inputs:
	//    - const vfloat32 in_pfMatrix[]: An one-dimensional array containing 16
	//				values with which the member data of the matrix is being
	//				initialized.
	//
	// Example: 
	//    - vfloat32 pfM[] = { 1.0f, 0.0f, 0.0f, 0.0f,
	//						   0.0f, 1.0f, 0.0f, 0.0f,
	//						   0.0f, 0.0f, 1.0f, 0.0f,
	//						   0.0f, 0.0f, 0.0f, 1.0f };
	//		VMatrix4f m(pfM);
	//
	VMatrix4f(const vfloat32 in_pfMatrix[]);

	//
	// *** VMatrix4f ***
	//
	// Synopsis:
	//    - Copy constructor of VMatrix4f.
	//
	// Inputs:
	//    - const VMatrix4f& in_rMatrix: The input matrix from which the member data
	//				is being copied to the current object.
	//
	// Example: 
	//    - VMatrix m1(1.0f, 0.0f, 0.0f, 0.0f,
	//				   0.0f, 1.0f, 0.0f, 0.0f,
	//				   0.0f, 0.0f, 1.0f, 0.0f,
	//				   0.0f, 0.0f, 0.0f, 1.0f);
	//		VMatrix m2(m1);
	//
	VMatrix4f(const VMatrix4f& in_rMatrix);

	//
	// *** operator = ***
	//
	// Synopsis:
	//    - This overloaded operator is used to assign new values from an existent
	//		matrix to the current object.
	//
	// Inputs:
	//    - const VMatrix4f& in_rMatrix: The input matrix from which the member data
	//				is being copied.
	//
	// Example: 
	//    - VMatrix m1(1.0f, 0.0f, 0.0f, 0.0f,
	//				   0.0f, 1.0f, 0.0f, 0.0f,
	//				   0.0f, 0.0f, 1.0f, 0.0f,
	//				   0.0f, 0.0f, 0.0f, 1.0f);
	//		VMatrix m2 = m1;
	//
	inline VMatrix4f& operator = (const VMatrix4f& in_rMatrix);

	//
	// *** operator == ***
	//
	// Synopsis:
	//    - Overloaded operator which is being used for comparing two matrices.
	//		Returns "true" if they are equal and "false" if this is not the case.
	//
	// Inputs:
	//    - const VMatrix4f& in_rMatrix: The input matrix with which the current
	//				object's member data is being compared.
	//
	// Returns:
	//    - vbool: Returns "true" if the two matrices are equal, otherwise "false".
	//
	// Example: 
	//    - VMatrix m1(1.0f, 0.0f, 0.0f, 0.0f,
	//				   0.0f, 1.0f, 0.0f, 0.0f,
	//				   0.0f, 0.0f, 1.0f, 0.0f,
	//				   0.0f, 0.0f, 0.0f, 1.0f);
	//		VMatrix m2(1.0f, 0.0f, 0.0f, 0.0f,
	//				   0.0f, 1.0f, 0.0f, 0.0f,
	//				   0.0f, 0.0f, 1.0f, 0.0f,
	//				   0.0f, 0.0f, 0.0f, 1.0f);
	//		if (m1 == m2)
	//		{
	//			DoSomething();
	//		}
	//
	inline vbool operator == (const VMatrix4f& in_rMatrix);

	//
	// *** operator != ***
	//
	// Synopsis:
	//    - Operator which tests if two matrices are not equal.
	//
	// Inputs:
	//    - const VMatrix4f& in_rMatrix: The input matrix with which the current
	//				object's member data is being compared.
	//
	// Returns:
	//    - vbool: Returns "false" if the two matrices are equal, otherwise "true".
	//
	// Example: 
	//    - VMatrix m1(1.0f, 0.0f, 0.0f, 0.0f,
	//				   0.0f, 1.0f, 0.0f, 0.0f,
	//				   0.0f, 0.0f, 1.0f, 0.0f,
	//				   0.0f, 0.0f, 0.0f, 1.0f);
	//		VMatrix m2(1.0f, 0.0f, 0.0f, 0.0f,
	//				   0.0f, 1.0f, 0.0f, 0.0f,
	//				   0.0f, 0.0f, 1.0f, 0.0f,
	//				   0.0f, 0.0f, 0.0f, 1.0f);
	//		if (m1 != m2)
	//		{
	//			DoSomething();
	//		}
	//
	inline vbool operator != (const VMatrix4f& in_rMatrix);

	inline vfloat32 Det(void) const;

	//
	// *** Identity ***
	//
	// Synopsis:
	//    - Call this function to reset the 4x4 matrix to identity values.
	//
	// Description:
	//	  - The 4x4 matrix wrapped by this object is reset to the following values
	//		which make the matrix do nothing at all:
	//			[1][0][0][0]
	//			[0][1][0][0]
	//			[0][0][1][0]
	//			[0][0][0][1]
	//
	// Example: 
	//    - VMatrix m;
	//		...
	//		m.Identity();
	//
	inline void Identity(void);

	//
	// *** Set ***
	//
	// Synopsis:
	//    - Assigns the values of an existing matrix to the members of the current
	//		matrix object.
	//
	// Inputs:
	//    - const VMatrix4f& in_rMatrix: The input matrix whose values are being
	//				assigned to the current object.
	//
	// Example: 
	//    - VMatrix m1;
	//		VMatrix m2;
	//		...
	//		m2.Set(m1);
	//
	inline void Set(const VMatrix4f& in_rMatrix);

	//
	// *** Translate ***
	//
	// Synopsis:
	//    - Translate the matrix encapsulated by this object by the input vector.
	//
	// Description:
	//	  - Translating a matrix is being performed by adding the translation values
	//		to the first three members of the last row:
	//			[1][0][0][0]
	//			[0][1][0][0]
	//			[0][0][1][0]
	//			[x][y][z][0]
	//
	// Inputs:
	//    - const VVector3f& in_rV: The input vector by which the matrix is being
	//				translated.
	//
	// Example: 
	//    - VMatrix m;
	//		VVector3f v(1.0f, 0.0f, 3.0f);
	//		m.Translate(v);
	//
	inline void Translate(const VVector3f& in_rV);
	inline void RotateX(const vfloat32& fX);
	inline void RotateY(const vfloat32& fY);
	inline void RotateZ(const vfloat32& fZ);
	inline void Multiply(const VMatrix4f& in_rMatrix, const VMatrix4f& in_rMatrix2);
};

#include <Math/VMatrix4f.inl>

#endif