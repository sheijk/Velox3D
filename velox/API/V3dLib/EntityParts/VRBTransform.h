#ifndef V3D_VRBTRANSFORM_2004_11_10_H
#define V3D_VRBTRANSFORM_2004_11_10_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Math.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

//TODO: in die mathlib verschieben --sheijk

/**
 * A rigid body transformation represented as an orthogonal coordinate system.
 * There are orthogonal normalized vectors forming a coordinate system plus a
 * translation vector.
 * The advantage over a matrix is that is is more imaginable and it avoids 
 * transformations witch alter angles or length of the transformed geometry 
 * which would corrupt the normals.
 */
class VRBTransform
{
public:

	enum Type { LeftHanded, RightHanded };
	//TODO: muss defaultType heissen, da public member --sheijk
	static Type m_sDefaultType;

	typedef math::VVector<vfloat32, 3> Vector;
	
	/**
	 * Initialize the orthogonal coordinate system to
	 * X-Axis = (1.0f, 0.0f, 0.0f)
	 * Y-Axis = (0.0f, 1.0f, 0.0f)
	 * Z-Axis = (0.0f, 0.0f, 1.0f)
	 * Position = (0.0f, 0.0f, 0.0f);
	 */
	VRBTransform();

	/**
	 * Initialize the orthogonal coordinate system with
	 * position, direction an up vectors.
	 *
	 * @param in_Position  The position
	 * @param in_Direction The direction part of the orientation
	 * @param in_Up        The up part of the orientation
	 * @param in_Type	   Left- or RightHanded? 
	 *                     (default: m_sDefaultType)
	 */
	VRBTransform(const Vector& in_Position,
	             const Vector& in_Direction,
			     const Vector& in_Up,
				 const Type in_Type = m_sDefaultType);

	/**
	 * Initialize the orthogonal coordinate system with a given
	 * matrix. If <code>in_Matrix</cod> does not describe a rigid
	 * body transformation, the rigid body transformation is calculated.
	 * TOD:: Bessere Doku - acryl
	 *
	 */
	VRBTransform(VMatrix<vfloat32, 4, 4>& in_Matrix);

	/**
	 * D'tor
	 */
	virtual ~VRBTransform();

	/**
	* Sets the position (origin) of the orthogonal coordinate
	* system.
	*
	* @param in_Position The new position (origin) of the coordinate 
	*                    system
	*/
	void SetPosition(const Vector& in_Position);

	/**
	* Gets the position (origin) of the orthogonal coordinate
	* system
	*
	* @return The position (origin) of the coordinate system
	*/
	Vector GetPosition() const;

	/**
	 * Sets the orientation using a look-at and up vector
	 *
	 * @param in_Direction The direction part of the orientation
	 * @param in_Up        The up part of the orientation
	 * @param in_Type	   Left- or RightHanded? 
	 *                     (default: m_sDefaultType)
	 */
	void SetLookAt(const Vector& in_Direction,
		           const Vector& in_Up,
				   const Type in_Type = m_sDefaultType);

	/**
	 * Sets the position and orientation using a position,
	 * look-at and up vector.
	 *
	 * @param in_Position  The position
	 * @param in_Direction The direction part of the orientation
	 * @param in_Up        The up part of the orientation
	 * @param in_Type	   Left- or RightHanded? 
	 *                     (default: m_sDefaultType)
	 *
	 */
	void SetLookAt(const Vector& in_Position,
		           const Vector& in_Direction,
				   const Vector& in_Up,
				   const Type in_Type = m_sDefaultType);
//
//	/**
//	 * Sets the orientation using euler angles
//	 * 
//	 * @param in_XAngle 
//	 * @param in_YAngle
//	 * @param in_ZAngles
//	 * @param in_Type	   Left- or RightHanded? 
//	 *                     (default: m_sDefaultType)
//	 *
//	 */
//	void SetEulerAngles(const vfloat32 in_XAngle,
//		                const vfloat32 in_YAngle,
//						const vfloat32 in_ZAngle,
//						const Type in_Type = m_sDefaultType);
//
//	/**
//	* Sets the position and orientation using euler angles
//	* position vector.
//	* 
//	* @param in_Position  The position
//	* @param in_XAngle 
//	* @param in_YAngle
//	* @param in_ZAngles
//	* @param in_Type	   Left- or RightHanded? 
//	*                     (default: m_sDefaultType)
//	*
//	*/
//	void SetEulerAngles(const Vector& in_Position,
//		                const vfloat32 in_XAngle,
//		                const vfloat32 in_YAngle,
//		                const vfloat32 in_ZAngle,
//		                const Type in_Type = m_sDefaultType);
//

//
//	/**
//	 * Sets the x-axis of the orthogonal coordinate system.
//	 * The vector <code>in_Vec</code> will be normalized.
//	 *
//	 * @param in_Vec	The cordinate system's new x-axis
//	 */
//	void SetXAxis(const Vector& in_Vec);
//
//	/**
//	 * Sets the y-axis of the orthogonal coordinate system.
//	 * The vector <code>in_Vec</code> will be normalized.
//	 *
//	 * @param in_Vec	The cordinate system's new y-axis
//	 */
//	void SetYAxis(const Vector& in_Vec);	
//

	/**
	 * Gets the x-axis of the orthogonal coordinate system.
	 *
	 * @return The cordinate system's x-axis
	 */
	Vector GetXAxis() const ;

	/**
	 * Gets the y-axis of the orthogonal coordinate system.
	 *
	 * @return The cordinate system's y-axis
	 */
	Vector GetYAxis() const;

	/**
	* Gets the z-axis of the orthogonal coordinate system.
	*
	* @return The cordinate system's z-axis
	*/
	Vector GetZAxis() const;

	/**
	 * Returns the transformation as a matrix
	 *	
	 * @return A transformation matrix
	 */
	math::VMatrix<vfloat32, 4, 4> GetAsMatrix() const;

	/**
	 *
	 *
	 *
	 */
	void Set(VMatrix<vfloat32, 4, 4> in_Matrix);

private:
	Vector	m_XAxis;
	Vector	m_YAxis;
	Vector  m_ZAxis;
	Vector	m_Position;
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