/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VRBTRANSFORM_2004_11_10_H
#define V3D_VRBTRANSFORM_2004_11_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Math/VVector.h>
#include <V3d/Math/VMatrix.h>
#include <V3d/Math/VQuaternion.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d;
/**
 * A rigid body transform is transform that consists of concatenations of only
 * translations and rotations. This transform is length, angle and normal 
 * preserving and is normally used the change an object's position and
 * orientation.
 *
 * It consists of a position and the x,y,z axis of the local coordinate
 * system it defines
 *
 * The coordinate frame is always right handed (z is the inverse view dir)
 *
 * To concatenate two rigid body transforms use 
 *
 *    Concatenate(VRBTransform& in_Result,
 *                const VRBTransform& in_A,
 *                const VRBTransform& in_B );
 *
 * or result = a * b;
 *
 * @author sheijk
 */
class VRBTransform
{
public:
	/**
	 * Initialize the orthogonal coordinate system to
	 *
	 * X-Axis = (1.0f, 0.0f, 0.0f)
	 * Y-Axis = (0.0f, 1.0f, 0.0f)
	 * Z-Axis = (0.0f, 0.0f, 1.0f)
	 * Position = (0.0f, 0.0f, 0.0f);
	 */
	VRBTransform();

	/**
	 * Located at in_Position, z axis facing away from in_LookAt
	 * (we have a right handed coordinate system)
	 */
	VRBTransform(const VVector3f& in_Position,
	             const VVector3f& in_LookAt,
			     const VVector3f& in_Up);

	VRBTransform(vfloat32 m_fPosX, vfloat32 m_fPosY, vfloat32 m_fPosZ,
		vfloat32 m_fLookAtX, vfloat32 m_fLookAtY, vfloat32 m_fLookAtZ,
		vfloat32 m_fUpX, vfloat32 m_fUpY, vfloat32 m_fUpZ);

	/**
	 * Initialize the orthogonal coordinate system with a given
	 * matrix
	 */
	explicit VRBTransform(VMatrix44f in_Matrix);

	/** class is not designed for subclassing */
	~VRBTransform();

	void SetPosition(const VVector3f& in_Position);
	VVector3f GetPosition() const;

	void SetDirection(const VVector3f& in_Direction, const VVector3f& in_Up);

	void SetLookAt(const VVector3f& in_Position,
		           const VVector3f& in_LookAt,
				   const VVector3f& in_Up);
	void SetLookAt(vfloat32 m_fPosX, vfloat32 m_fPosY, vfloat32 m_fPosZ,
		vfloat32 m_fLookAtX, vfloat32 m_fLookAtY, vfloat32 m_fLookAtZ,
		vfloat32 m_fUpX, vfloat32 m_fUpY, vfloat32 m_fUpZ);

	VVector3f GetXAxis() const ;
	VVector3f GetYAxis() const;
	VVector3f GetZAxis() const;
	void GetAxis(VVector3f& out_XAxis, VVector3f& out_YAxis, VVector3f& out_ZAxis) const;

	// these methods may result in a non orthonormal basis! use with caution
	void SetXAxis(const VVector3f& in_XAxis);
	void SetYAxis(const VVector3f& in_YAxis);
	void SetZAxis(const VVector3f& in_ZAxis);

	/**
	 * Returns the transformation as a matrix
	 *	
	 * @return A transformation matrix
	 */
	VMatrix44f AsMatrix() const;

	/**
	 * Let's the transform represent the same transformation the given matrix
	 * represents. This is only possible if the matrix represents a rigid body
	 * transformation (= a concatenation of rotation and translation transforms)
	 */
	void Set(VMatrix44f in_Matrix);

	void Invert();

	void Rotate(vfloat32 in_fAngleDegree, const VVector3f& axis);
	void Rotate(VQuatf& in_Quatf);

private:
	VVector3f m_XAxis;
	VVector3f m_YAxis;
	VVector3f m_ZAxis;

	VVector3f m_Position;
};

/**
 * Concatenates two rigid body coordinate systems. 
 *
 * @param in_Result The result of this operation
 * @param in_A      First operand
 * @param in_B		Second operand
 *
 */
void Concatenate(VRBTransform& in_Result,
			     const VRBTransform& in_A,
				 const VRBTransform& in_B );

//////////////////////////////////////////////////////////////////////////

VRBTransform operator*( const VRBTransform& in_A,
					    const VRBTransform& in_B );

//-----------------------------------------------------------------------------
} // namespace entity
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VRBTRANSFORM_2004_11_10_H
