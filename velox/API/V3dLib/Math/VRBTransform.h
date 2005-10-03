#ifndef V3D_VRBTRANSFORM_2004_11_10_H
#define V3D_VRBTRANSFORM_2004_11_10_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Math.h>
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
 *
 * The translation of the rigid body transform is stored in a 3D position
 * vector. Three 3D axis vectors forms an orthogonal carthesian coordinate
 * system representing the rotation.
 *
 *
 * There a varios way to describe a valid rigid body transform. So VRBTransform
 * provides serveral Get/Set-Methods to set or get the rigid body transform in
 * various ways.
 * Further information is in the documentation of the methods.
 *
 *
 * To concatenate two rigid body transforms use 
 *
 *    Concatenate(VRBTransform& in_Result,
 *                const VRBTransform& in_A,
 *                const VRBTransform& in_B );
 *
 * or the overloaded operator*.
 *
 * Fore more information about how two rigid body transforms are concatenated
 * see the commentary.
 *
 * @author sheijk, acrylsword
 */

class VRBTransform
{
public:

	enum Type { LeftHanded, RightHanded };

	static Type defaultType;
	
	/**
	 * Initialize the orthogonal coordinate system to
	 *
	 * X-Axis = (1.0f, 0.0f, 0.0f)
	 * Y-Axis = (0.0f, 1.0f, 0.0f)
	 * Z-Axis = (0.0f, 0.0f, 1.0f)
	 * Position = (0.0f, 0.0f, 0.0f);
	 *
	 */
	VRBTransform();

	VRBTransform(const VRBTransform& in_Source);
	void operator=(const VRBTransform& in_Source);

	/**
	 * Initialize the orthogonal coordinate system with
	 * position, direction an up vectors.
	 * 
	 *
	 * @param in_Position  The position
	 * @param in_Direction The direction part of the orientation
	 * @param in_Up        The up part of the orientation
	 * @param in_Type	   Left- or RightHanded? 
	 *                     (default: defaultType)
	 */
	VRBTransform(const VVector3f& in_Position,
	             const VVector3f& in_Direction,
			     const VVector3f& in_Up,
				 const Type in_Type = defaultType);

	/**
	 * Initialize the orthogonal coordinate system with a given
	 * matrix. If <code>in_Matrix</cod> does not describe a rigid
	 * body transformation, the rigid body transformation is calculated.
	 * TOD:: Bessere Doku - acryl
	 *
	 */
	explicit VRBTransform(VMatrix44f in_Matrix);

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
	void SetPosition(const VVector3f& in_Position);

	/**
	* Gets the position (origin) of the orthogonal coordinate
	* system
	*
	* @return The position (origin) of the coordinate system
	*/
	VVector3f GetPosition() const;

	/**
	 * Sets the orientation using a look-at and up vector
	 *
	 * @param in_Direction The direction part of the orientation
	 * @param in_Up        The up part of the orientation
	 * @param in_Type	   Left- or RightHanded? 
	 *                     (default: defaultType)
	 */
	void SetLookAt(const VVector3f& in_Direction,
		           const VVector3f& in_Up,
				   const Type in_Type = defaultType);

	/**
	 * Sets the position and orientation using a position,
	 * look-at and up vector.
	 *
	 * @param in_Position  The position
	 * @param in_Direction The direction part of the orientation
	 * @param in_Up        The up part of the orientation
	 * @param in_Type	   Left- or RightHanded? 
	 *                     (default: defaultType)
	 *
	 */
	void SetLookAt(const VVector3f& in_Position,
		           const VVector3f& in_Direction,
				   const VVector3f& in_Up,
				   const Type in_Type = defaultType);
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
	/**
	 * Gets the x-axis of the orthogonal coordinate system.
	 *
	 * @return The cordinate system's x-axis
	 */
	VVector3f GetXAxis() const ;

	/**
	 * Gets the y-axis of the orthogonal coordinate system.
	 *
	 * @return The cordinate system's y-axis
	 */
	VVector3f GetYAxis() const;

	/**
	* Gets the z-axis of the orthogonal coordinate system.
	*
	* @return The cordinate system's z-axis
	*/
	VVector3f GetZAxis() const;

	/**
	 * Get the three axis vectors
	 *
	 * @param out_XAxis The x-axis
	 * @param out_YAxis The y-axis
	 * @param out_ZAxis The z-axis
	 *
     */
	void GetAxis(VVector3f& out_XAxis, VVector3f& out_YAxis, VVector3f& out_ZAxis) const;

	/**
	 * Returns the transformation as a matrix
	 *	
	 * @return A transformation matrix
	 */
	VMatrix44f GetAsMatrix() const;

	/**
	 *
	 *
	 *
	 */
	void Set(VMatrix44f in_Matrix);

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