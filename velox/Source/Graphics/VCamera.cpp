//-----------------------------------------------------------------------------
#include <v3d/Graphics/VCamera.h>
#include <v3d/Math/VMatrixOps.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d::utils::graphics;

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
	
}
//-----------------------------------------------------------------------------
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

}
//-----------------------------------------------------------------------------

void VCamera::Move(vfloat32 in_fX, vfloat32 in_fY, vfloat32 in_fZ)
{
	m_PositionVector.v[0] = in_fX;
	m_PositionVector.v[1] = in_fY;
	m_PositionVector.v[2] = in_fZ;
}
//-----------------------------------------------------------------------------

VCamera::Matrix4f* VCamera::GetMatrix()
{
	CalculateMatrix();
	return &m_ViewMatrix;
}
//-----------------------------------------------------------------------------

void VCamera::MoveForward(vfloat32 in_fUnits)
{
	m_PositionVector.v[0] = m_PositionVector.v[0] + (m_ViewVector.Get(0) *- in_fUnits);
	m_PositionVector.v[1] = m_PositionVector.v[1] + (m_ViewVector.Get(1) *- in_fUnits);
	m_PositionVector.v[2] = m_PositionVector.v[2] + (m_ViewVector.Get(2) *- in_fUnits);
}
//-----------------------------------------------------------------------------

void VCamera::MoveUp(vfloat32 in_fUnits)
{
	m_PositionVector.v[0] = m_PositionVector.v[0] + (m_UpVector.Get(0) * in_fUnits);
	m_PositionVector.v[1] = m_PositionVector.v[1] + (m_UpVector.Get(1) * in_fUnits);
	m_PositionVector.v[2] = m_PositionVector.v[2] + (m_UpVector.Get(2) * in_fUnits);
}
//-----------------------------------------------------------------------------

void VCamera::Strafe(vfloat32 in_fUnits)
{
	m_PositionVector.v[0] = m_PositionVector.v[0]  + (m_RightVector.Get(0) * in_fUnits);
	m_PositionVector.v[1] = m_PositionVector.v[1]  + (m_RightVector.Get(1) * in_fUnits);
	m_PositionVector.v[2] = m_PositionVector.v[2]  + (m_RightVector.Get(2) * in_fUnits);
}
//-----------------------------------------------------------------------------

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

}
//-----------------------------------------------------------------------------

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
}
//-----------------------------------------------------------------------------

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
}
//-----------------------------------------------------------------------------

void VCamera::CalculateMatrix()
{
	Vector f = m_ViewVector;
	Normalize(f);

	Vector up = m_UpVector;
	Normalize(up);

	Vector s;

	s = Cross(f,up);

	Vector u;

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

}

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------