#include <V3d/Graphics/Misc/VCamera.h>
#include <V3d/Math/VMatrixOps.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Math/VQuaternionOps.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace math;

VCamera::VCamera(vfloat32 x, vfloat32 y, vfloat32 z)
		: m_fPiDiv180((vfloat32) 3.141592654 /(vfloat32) 180)
{
	m_Position = ToVector3f(x, y, z);

	m_UpVector = VVector3f(0, 1, 0);
	m_RightVector = VVector3f(1, 0, 0);
	m_ViewVector = VVector3f(0, 0, -1);

	CalculateMatrix();
}

VCamera::VCamera()
		: m_fPiDiv180((vfloat32)3.141592654 / (vfloat32)180)
{
	m_Position = VVector3f(0, 0, 0);

	m_UpVector = VVector3f(0, 1, 0);
	m_RightVector = VVector3f(1, 0, 0);
	m_ViewVector = VVector3f(0, 0, -1);

	CalculateMatrix();
}

void VCamera::ApplyTo(IVDevice& in_Device) const
{
	in_Device.SetMatrix(IVDevice::ViewMatrix, m_ViewMatrix);
}

void VCamera::Move(vfloat32 in_fX, vfloat32 in_fY, vfloat32 in_fZ)
{
	m_Position = ToVector3f(in_fX, in_fY, in_fZ);

	CalculateMatrix();
}

void VCamera::MoveForward(vfloat32 in_fUnits)
{
	m_Position += m_ViewVector * in_fUnits;

	CalculateMatrix();
}


void VCamera::MoveUp(vfloat32 in_fUnits)
{
	m_Position += m_UpVector * in_fUnits;

	CalculateMatrix();
}


void VCamera::Strafe(vfloat32 in_fUnits)
{
	m_Position += m_RightVector * in_fUnits;

	CalculateMatrix();
}

void VCamera::RotateAround(const VVector3f& in_Axis, vfloat32 in_fAngle)
{
	VQuatf rot = QuatFromAxisAngle(in_Axis, in_fAngle);
	Rotate(m_ViewVector, rot);
	Rotate(m_UpVector, rot);
	Rotate(m_RightVector, rot);

	CalculateMatrix();
}

void VCamera::RotateX(vfloat32 in_fAngle)
{
	RotateAround(m_RightVector, in_fAngle);
	//RotateAround(VVector3f(1, 0, 0), in_fAngle);
}

void VCamera::RotateY(vfloat32 in_fAngle)
{
	RotateAround(m_UpVector, in_fAngle);
	//RotateAround(VVector3f(0, 1, 0), in_fAngle);
}

void VCamera::RotateZ(vfloat32 in_fAngle)
{
	RotateAround(m_ViewVector, in_fAngle);
	//RotateAround(VVector3f(0, 0, 1), in_fAngle);
}

void VCamera::CalculateMatrix() const
{
	VVector3f f = m_ViewVector;
	Normalize(f);

	VVector3f up = m_UpVector;
	Normalize(up);

	VVector3f s;

	s = Cross(f,up);

	VVector3f u;

	u = Cross(s,f);

	Matrix4f m;
	Identity(m);
	m.Set(0, 0, s.Get(0));
	m.Set(0, 1, s.Get(1));
	m.Set(0, 2, s.Get(2));
	
	m.Set(1, 0, u.Get(0));
	m.Set(1, 1, u.Get(1));
	m.Set(1, 2, u.Get(2));

	m.Set(2, 0, -f.Get(0));
	m.Set(2, 1, -f.Get(1));
	m.Set(2, 2, -f.Get(2));

	Matrix4f t;
	Identity(t);
	t.SetTransform(-m_Position[0], -m_Position[1], -m_Position[2]);

	Matrix4f r;
	Identity(r);
	Mult(r, m, t);

	m_ViewMatrix = r;

	//m_Transform.Set(m_ViewMatrix);
	m_Transform.SetPosition(m_Position);
	m_Transform.SetDirection(m_ViewVector, m_UpVector);
}

VRBTransform VCamera::GetTransform() const
{
	return m_Transform;
}

void VCamera::SetTransform(const VRBTransform& transform)
{
	Move(transform.GetPosition().GetX(), transform.GetPosition().GetY(), transform.GetPosition().GetZ());
	m_ViewVector = transform.GetZAxis() * -1;
	m_UpVector = transform.GetYAxis();

	CalculateMatrix();
}

const VMatrix44f& VCamera::ViewMatrix() const
{
	return m_ViewMatrix;
}

const math::VRBTransform& VCamera::Transform() const
{
	return m_Transform;
}

VVector3f VCamera::GetPosition() const
{
	return m_Position;
}

VVector3f VCamera::GetViewDirection() const
{
	return m_ViewVector;
}

VVector3f VCamera::GetUpVector() const
{
	return m_UpVector;
}

VCamera ca;
//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
