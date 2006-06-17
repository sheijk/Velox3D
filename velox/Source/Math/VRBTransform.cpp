#include <V3d/Math/VRBTransform.h>
//-----------------------------------------------------------------------------
#include <V3d/Math/VVectorOps.h>
#include <V3d/Math/VMatrixOps.h>
#include <V3d/Math/TransformationOps.h>
#include <V3d/Math/VVectorBase.h>
#include <V3d/Math/VQuaternionOps.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d;

VRBTransform::VRBTransform()
{
	m_XAxis = VVector3f(1.0f, 0.0f, 0.0f);
	m_YAxis = VVector3f(0.0f, 1.0f, 0.0f);
	m_ZAxis = VVector3f(0.0f, 0.0f, 1.0f);
	m_Position = VVector3f(0.0f, 0.0f, 0.0f);
}

VRBTransform::VRBTransform(
	const VVector3f& in_Position,
	const VVector3f& in_LookAt,
	const VVector3f& in_Up)
{
	SetLookAt(in_Position, in_LookAt, in_Up);
}

VRBTransform::VRBTransform(VMatrix44f in_Matrix)
{
	Set(in_Matrix); 
}

VRBTransform::~VRBTransform()
{
}

void VRBTransform::SetLookAt(const VVector3f& in_Position,
							 const VVector3f& in_LookAt,
							 const VVector3f& in_Up)
{
	//V3D_ASSERT(Length(in_Up) != 0.0f);
	//V3D_ASSERT(in_Position != in_LookAt);

	m_Position = in_Position;

	VVector3f direction = in_LookAt - in_Position;
	SetDirection(direction, in_Up);
}

void VRBTransform::SetLookAt(
	vfloat32 m_fPosX, vfloat32 m_fPosY, vfloat32 m_fPosZ,
	vfloat32 m_fLookAtX, vfloat32 m_fLookAtY, vfloat32 m_fLookAtZ,
	vfloat32 m_fUpX, vfloat32 m_fUpY, vfloat32 m_fUpZ)
{
	SetLookAt(VVector3f(m_fPosX, m_fPosY, m_fPosZ),
		VVector3f(m_fLookAtX, m_fLookAtY, m_fLookAtZ),
		VVector3f(m_fUpX, m_fUpY, m_fUpZ));
}

void VRBTransform::SetDirection(
	const VVector3f& in_Direction, const VVector3f& in_Up)
{
	//V3D_ASSERT( Length(in_Up) != 0.0f );

	SetZAxis(-in_Direction);
	SetXAxis(Cross(in_Direction, in_Up));
	SetYAxis(in_Up);
	Normalize(m_XAxis);
	Normalize(m_YAxis);
	Normalize(m_ZAxis);
	//SetZAxis(Normalized(-in_Direction));
	//SetXAxis(Normalized(Cross(in_Direction, in_Up)));
	//SetYAxis(Normalized(Cross(GetXAxis(), in_Direction)));
	//VVectorBase3f::Orthogonalize(&m_XAxis, &m_YAxis, &m_ZAxis);

//#ifdef V3D_DEBUG
//	VVectorBase3f base(GetXAxis(), GetYAxis(), GetZAxis());
//	V3D_ASSERT(base.IsRightHanded());
//	V3D_ASSERT(base.IsOrthogonal());
//	V3D_ASSERT(base.IsNormalized());
//#endif
}

VVector3f VRBTransform::GetXAxis() const
{
	return m_XAxis;
}

VVector3f VRBTransform::GetYAxis() const
{
	return m_YAxis;
}

VVector3f VRBTransform::GetZAxis() const
{
	return m_ZAxis;
}

void VRBTransform::SetXAxis(const VVector3f& in_XAxis)
{
	//m_CoordSysFrame.SetI(in_XAxis);
	m_XAxis = in_XAxis;
}

void VRBTransform::SetYAxis(const VVector3f& in_YAxis)
{
	//m_CoordSysFrame.SetJ(in_YAxis);
	m_YAxis = in_YAxis;
}

void VRBTransform::SetZAxis(const VVector3f& in_ZAxis)
{
	//m_CoordSysFrame.SetK(in_ZAxis);
	m_ZAxis = in_ZAxis;
}

void VRBTransform::SetPosition(const VVector3f& in_Position)
{
	m_Position = in_Position;
}

VVector3f VRBTransform::GetPosition() const
{
	return m_Position;
}

VMatrix44f VRBTransform::AsMatrix() const
{
	VMatrix44f ret;

	//set position
	math::SetTranslate(ret, m_Position[0], m_Position[1], m_Position[2]);

	//set first axis
	ret.Set(0,0, m_XAxis[0]);
	ret.Set(1,0, m_XAxis[1]);
	ret.Set(2,0, m_XAxis[2]);

	//set second axis
	ret.Set(0,1, m_YAxis[0]);
	ret.Set(1,1, m_YAxis[1]);
	ret.Set(2,1, m_YAxis[2]);

	//set third axis
	ret.Set(0,2, m_ZAxis[0]);
	ret.Set(1,2, m_ZAxis[1]);
	ret.Set(2,2, m_ZAxis[2]);

	return ret;
}

void VRBTransform::Set(VMatrix44f in_Matrix)
{
	//TODO: matrix validieren(?)

	m_Position[0] = in_Matrix.Get(0,3);
	m_Position[1] = in_Matrix.Get(1,3);
	m_Position[2] = in_Matrix.Get(2,3);

	m_XAxis[0] = in_Matrix.Get(0,0);
	m_XAxis[1] = in_Matrix.Get(1,0);
	m_XAxis[2] = in_Matrix.Get(2,0);

	m_YAxis[0] = in_Matrix.Get(0,1);
	m_YAxis[1] = in_Matrix.Get(1,1);
	m_YAxis[2] = in_Matrix.Get(2,1);

	m_ZAxis[0] = in_Matrix.Get(0,2);
	m_ZAxis[1] = in_Matrix.Get(1,2);
	m_ZAxis[2] = in_Matrix.Get(2,2);

	Normalize(m_XAxis);
	Normalize(m_YAxis);
	Normalize(m_ZAxis);
}

void Concatenate(VRBTransform& in_Result,
	 			 const VRBTransform& in_A,
				 const VRBTransform& in_B )
{
	VMatrix44f temp = in_A.AsMatrix()*in_B.AsMatrix();
    in_Result.Set(temp);
}



VRBTransform operator*( const VRBTransform& in_A,
  					    const VRBTransform& in_B )
{
	VRBTransform ret;
	Concatenate(ret, in_A, in_B);
	return ret;
}

void VRBTransform::GetAxis(
						   VVector3f& out_XAxis,
						   VVector3f& out_YAxis,
						   VVector3f& out_ZAxis
						   ) const
{
	out_XAxis = m_XAxis;
	out_YAxis = m_YAxis;
	out_ZAxis = m_ZAxis;
}

void VRBTransform::Invert()
{
	m_XAxis = - m_XAxis;
	m_YAxis = - m_YAxis;
	m_ZAxis = - m_ZAxis;
	m_Position = - m_Position;
}

void VRBTransform::Rotate(vfloat32 in_fAngleDegree, const VVector3f& axis)
{
	VQuatf quat = QuatFromAxisAngle(axis, in_fAngleDegree);
	v3d::Rotate(m_XAxis, quat);
	v3d::Rotate(m_YAxis, quat);
	v3d::Rotate(m_ZAxis, quat);
}

//-----------------------------------------------------------------------------
} //namespace math
} //namespace v3d
//-----------------------------------------------------------------------------
