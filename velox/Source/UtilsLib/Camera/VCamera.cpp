#include <V3dLib/Graphics/Misc/VCamera.h>

#include <v3d/Math/VMatrixOps.h>

#include <V3d/Graphics/IVDevice.h>

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
	m_PositionVector.v[0] = x;
	m_PositionVector.v[1] = y;
	m_PositionVector.v[2] = z;

	m_UpVector.Set(0, 0);
	m_UpVector.Set(1, 1);
    m_UpVector.Set(2, 0);

	m_RightVector.Set(0, 1);
	m_RightVector.Set(1, 0);
	m_RightVector.Set(2, 0);

	m_RotationVector.Set(0,0);
	m_RotationVector.Set(1,0);
	m_RotationVector.Set(2,0);


	m_ViewVector.Set(0,0);
	m_ViewVector.Set(1,0);
	m_ViewVector.Set(2,-1);

	CalculateMatrix();
}

VCamera::VCamera()
		: m_fPiDiv180((vfloat32)3.141592654 / (vfloat32)180)
{

	m_UpVector.Set(0, 0);
	m_UpVector.Set(1, 1);
	m_UpVector.Set(2, 0);

	m_RightVector.Set(0, 1);
	m_RightVector.Set(1, 0);
	m_RightVector.Set(2, 0);

	m_RotationVector.Set(0,0);
	m_RotationVector.Set(1,0);
	m_RotationVector.Set(2,0);

	m_ViewVector.Set(0,0);
	m_ViewVector.Set(1,0);
	m_ViewVector.Set(2,-1);

	CalculateMatrix();
}

void VCamera::ApplyTo(IVDevice& in_Device) const
{
	in_Device.SetMatrix(IVDevice::ViewMatrix, m_ViewMatrix);
}

void VCamera::Move(vfloat32 in_fX, vfloat32 in_fY, vfloat32 in_fZ)
{
	m_PositionVector.v[0] = in_fX;
	m_PositionVector.v[1] = in_fY;
	m_PositionVector.v[2] = in_fZ;

	CalculateMatrix();
}

void VCamera::MoveForward(vfloat32 in_fUnits)
{
	m_PositionVector.v[0] = m_PositionVector.v[0] + (m_ViewVector.Get(0) * in_fUnits);
	m_PositionVector.v[1] = m_PositionVector.v[1] + (m_ViewVector.Get(1) * in_fUnits);
	m_PositionVector.v[2] = m_PositionVector.v[2] + (m_ViewVector.Get(2) * in_fUnits);

	CalculateMatrix();
}


void VCamera::MoveUp(vfloat32 in_fUnits)
{
	m_PositionVector.v[0] = m_PositionVector.v[0] + (m_UpVector.Get(0) * in_fUnits);
	m_PositionVector.v[1] = m_PositionVector.v[1] + (m_UpVector.Get(1) * in_fUnits);
	m_PositionVector.v[2] = m_PositionVector.v[2] + (m_UpVector.Get(2) * in_fUnits);

	CalculateMatrix();
}


void VCamera::Strafe(vfloat32 in_fUnits)
{
	m_PositionVector.v[0] = m_PositionVector.v[0]  + (m_RightVector.Get(0) * in_fUnits);
	m_PositionVector.v[1] = m_PositionVector.v[1]  + (m_RightVector.Get(1) * in_fUnits);
	m_PositionVector.v[2] = m_PositionVector.v[2]  + (m_RightVector.Get(2) * in_fUnits);

	CalculateMatrix();
}


void VCamera::RotateX(vfloat32 in_fAngle)
{
	// save our current rotation into the vector because we want to rotate over the
	// existing rotation value
	m_RotationVector.Set(0, m_RotationVector.Get(0) + in_fAngle);

	vfloat32 x,y,z;
	
	x = m_ViewVector.Get(0);
	y = m_ViewVector.Get(1);
	z = m_ViewVector.Get(2);
	
	x = x*cos(in_fAngle * m_fPiDiv180);
	y = y*cos(in_fAngle * m_fPiDiv180);
	z = z*cos(in_fAngle * m_fPiDiv180);

	x += m_UpVector.Get(0) * sin(in_fAngle * m_fPiDiv180);
	y += m_UpVector.Get(1) * sin(in_fAngle * m_fPiDiv180);
	z += m_UpVector.Get(2) * sin(in_fAngle * m_fPiDiv180);

	//store the value back

	m_ViewVector.Set(0,x);
	m_ViewVector.Set(1,y);
	m_ViewVector.Set(2,z);

	Normalize(m_ViewVector);

	//get the new up vector
	m_UpVector = Cross(m_ViewVector, m_RightVector);

	//negate it
	m_UpVector.Set(0, -m_UpVector.Get(0));
	m_UpVector.Set(1, -m_UpVector.Get(1));
	m_UpVector.Set(2, -m_UpVector.Get(2));


	CalculateMatrix();
}

void VCamera::RotateY(vfloat32 in_fAngle)
{
	// save our current rotation into the vector because we want to rotate over the
	// existing rotation value
	m_RotationVector.Set(1, m_RotationVector.Get(1) + in_fAngle);

	vfloat32 x,y,z;

	x = m_ViewVector.Get(0);
	y = m_ViewVector.Get(1);
	z = m_ViewVector.Get(2);

	x = x*cos(in_fAngle * m_fPiDiv180);
	y = y*cos(in_fAngle * m_fPiDiv180);
	z = z*cos(in_fAngle * m_fPiDiv180);

	x += m_RightVector.Get(0) * sin(in_fAngle * m_fPiDiv180);
	y += m_RightVector.Get(1) * sin(in_fAngle * m_fPiDiv180);
	z += m_RightVector.Get(2) * sin(in_fAngle * m_fPiDiv180);

	//store the value back

	m_ViewVector.Set(0,x);
	m_ViewVector.Set(1,y);
	m_ViewVector.Set(2,z);

	Normalize(m_ViewVector);

	//get the new right vector
	m_RightVector = Cross(m_ViewVector, m_UpVector);

	CalculateMatrix();
}

void VCamera::RotateZ(vfloat32 in_fAngle)
{
	// save our current rotation into the vector because we want to rotate over the
	// existing rotation value
	m_RotationVector.Set(2, m_RotationVector.Get(2) + in_fAngle);

	vfloat32 x,y,z;

	x = m_RightVector.Get(0);
	y = m_RightVector.Get(1);
	z = m_RightVector.Get(2);

	x = x*cos(in_fAngle * m_fPiDiv180);
	y = y*cos(in_fAngle * m_fPiDiv180);
	z = z*cos(in_fAngle * m_fPiDiv180);

	x += m_UpVector.Get(0) * sin(in_fAngle * m_fPiDiv180);
	y += m_UpVector.Get(1) * sin(in_fAngle * m_fPiDiv180);
	z += m_UpVector.Get(2) * sin(in_fAngle * m_fPiDiv180);

	//store the value back

	m_RightVector.Set(0,x);
	m_RightVector.Set(1,y);
	m_RightVector.Set(2,z);

	Normalize(m_RightVector);

	//get the new up vector
	m_UpVector = Cross(m_ViewVector, m_RightVector);

	CalculateMatrix();
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
	t.SetTransform(
		-m_PositionVector.v[0],
		-m_PositionVector.v[1],
		-m_PositionVector.v[2]);

	Matrix4f r;
	Identity(r);
	Mult(r, m, t);

	m_ViewMatrix = r;

	m_Transform.Set(m_ViewMatrix);
}

VRBTransform VCamera::GetTransform() const
{
	return VRBTransform(GetPosition(), m_ViewVector, m_UpVector);
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
	// warum auch immer m_PositionVector ein VVector3f ist... -> konvertieren
	VVector3f pos;
	pos.Set(0, m_PositionVector.x);
	pos.Set(1, m_PositionVector.y);
	pos.Set(2, m_PositionVector.z);

	return pos;
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
