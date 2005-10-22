#ifndef V3D_VCAMERA_H
#define V3D_VCAMERA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
#include <v3d/Math/VMatrix.h>
#include <v3d/Math/VVector.h>
#include <V3d/Math/VRBTransform.h>
#include <V3d/Math/VVectorOps.h>
#include <v3dLib//Graphics/Geometry/VVertex3f.h>
#include <V3dLib/Graphics/Misc/IVCamera.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A first person camera implementation
 *
 * @author ins
 */
//TODO: vereinheitlichen.. + fkten eindeutige benennen 
// (Move->MoveTo, Strafe Left oder Right?)
class VCamera : public IVCamera
{
public:

	VCamera();
	VCamera(vfloat32 x, vfloat32 y, vfloat32 z);

	virtual ~VCamera() {};

	virtual void ApplyTo(IVDevice& in_Device) const;

	/** Move to absolute position */
	void Move(vfloat32 in_fX, vfloat32 in_fY, vfloat32 in_fZ);

	void MoveForward(vfloat32 in_fUnits);
	void MoveUp(vfloat32 in_fUnits);
	void Strafe(vfloat32 in_fUnits);
	void RotateX(vfloat32 in_fAngle);
	void RotateY(vfloat32 in_fAngle);
	void RotateZ(vfloat32 in_fAngle);

	// derived from IVCamera:
	virtual const VMatrix44f& ViewMatrix() const;
	virtual const math::VRBTransform& Transform() const;
	virtual VVector3f GetPosition() const;
	virtual VVector3f GetViewDirection() const;
	virtual VVector3f GetUpVector() const;

	math::VRBTransform GetTransform() const;
	void SetTransform(const math::VRBTransform& transform);

private:

	typedef VMatrix<vfloat32, 4,4> Matrix4f;

	void CalculateMatrix() const;

	const vfloat32 m_fPiDiv180;

	mutable Matrix4f m_ViewMatrix;
	mutable math::VRBTransform m_Transform;

	VVector3f m_UpVector;
	VVector3f m_RightVector;
	VVector3f m_RotationVector;
	VVector3f m_ViewVector;

	v3d::graphics::VVertex3f m_PositionVector;

};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCAMERA_H
