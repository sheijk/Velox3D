#include "VRBTransform.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

//TODO: alle .cpp files nach velox/Source/... --sheijk

VRBTransform::Type VRBTransform::m_sDefaultType = VRBTransform::LeftHanded;

VRBTransform::VRBTransform()
{
	m_XAxis = Vector(1.0f, 0.0f, 0.0f);
	m_YAxis = Vector(0.0f, 1.0f, 0.0f);
	m_ZAxis = Vector(0.0f, 0.0f, 1.0f);
	m_Position = Vector(0.0f, 0.0f, 0.0f);
}

//////////////////////////////////////////////////////////////////////////

VRBTransform::VRBTransform(const Vector& in_Position,
						   const Vector& in_Direction,
						   const Vector& in_Up,
						   const Type in_Type)
{
	V3D_ASSERT( Length(in_Up) != 0.0f );

	SetLookAt(in_Position, in_Direction, in_Up, in_Type);
}

VRBTransform::VRBTransform(VMatrix<vfloat32, 4, 4>& in_Matrix)
{
	Set(in_Matrix);
}

//////////////////////////////////////////////////////////////////////////

void VRBTransform::SetLookAt(const Vector& in_Position,
							 const Vector& in_Direction,
							 const Vector& in_Up,
							 const Type in_Type)
{
	V3D_ASSERT( Length(in_Up) != 0.0f );

	m_Position = in_Position;
	SetLookAt( in_Direction, in_Up, in_Type);
}

//////////////////////////////////////////////////////////////////////////

void VRBTransform::SetLookAt(const Vector& in_Direction,
							 const Vector& in_Up,
							 const Type in_Type)
{
	V3D_ASSERT( Length(in_Up) != 0.0f );

	//TODO: sollen wirklich beide zweige das gleiche tun? --sheijk
    if (in_Type == LeftHanded)
	{
		m_XAxis = Normalized(Cross(in_Direction, in_Up));
		m_YAxis = Normalized(in_Direction);
		m_ZAxis = Normalized(Cross(m_XAxis, in_Up));
	}
	else
	{
		m_XAxis = Normalized(Cross(in_Direction, in_Up));
		m_YAxis = Normalized(in_Direction);
		m_ZAxis = Normalized(Cross(m_XAxis, in_Up));
	}
}

//
//void VRBTransform::SetXAxis(const Vector& in_Vec)
//{
//	V3D_ASSERT( Length(in_Vec) != 0.0f );
//
//	m_XAxis = Normalized(in_Vec);
//}
//
//void VRBTransform::SetYAxis(const Vector& in_Vec)
//{
//	V3D_ASSERT( Length(in_Vec) != 0.0f );
//
//	m_YAxis = Normalized(in_Vec);
//}
//

VRBTransform::Vector VRBTransform::GetXAxis() const
{
	return m_XAxis;
}

//////////////////////////////////////////////////////////////////////////

VRBTransform::Vector VRBTransform::GetYAxis() const
{
	return m_YAxis;
}

//////////////////////////////////////////////////////////////////////////

VRBTransform::Vector VRBTransform::GetZAxis() const
{
	return m_ZAxis;
}

//////////////////////////////////////////////////////////////////////////

void VRBTransform::SetPosition(const Vector& in_Position)
{
	m_Position = in_Position;
}

//////////////////////////////////////////////////////////////////////////

VRBTransform::Vector VRBTransform::GetPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

math::VMatrix<vfloat32, 4, 4> VRBTransform::GetAsMatrix() const
{
	//TODO: funktion duerfte bei "unregulaeren" matrizen komische
	//ergebnisse haben, sowas sollte abgefangen, oder zumindest dokumentiert
	//werden --sheijk
	
	VMatrix<vfloat32, 4, 4> ret;

	//set position
	math::SetTranslate(ret, m_Position[0], m_Position[1], m_Position[3]);

	//set first axis
	ret.Set(0,0, m_XAxis[0]);
	ret.Set(0,1, m_XAxis[1]);
	ret.Set(0,2, m_XAxis[2]);

	//set second axis
	ret.Set(1,0, m_YAxis[0]);
	ret.Set(1,1, m_YAxis[1]);
	ret.Set(1,2, m_YAxis[2]);

	//set third axis
	ret.Set(2,0, m_ZAxis[0]);
	ret.Set(2,1, m_ZAxis[1]);
	ret.Set(2,2, m_ZAxis[2]);

	return ret;
}

//////////////////////////////////////////////////////////////////////////

void VRBTransform::Set(VMatrix<vfloat32, 4, 4> in_Matrix)
{
	m_Position[0] = in_Matrix.Get(0,3);
	m_Position[1] = in_Matrix.Get(1,3);
	m_Position[2] = in_Matrix.Get(2,3);

	m_XAxis[0] = in_Matrix.Get(0,0);
	m_XAxis[1] = in_Matrix.Get(0,1);
	m_XAxis[2] = in_Matrix.Get(0,2);

	m_YAxis[0] = in_Matrix.Get(1,0);
	m_YAxis[1] = in_Matrix.Get(1,1);
	m_YAxis[2] = in_Matrix.Get(1,2);

	m_ZAxis = Cross(m_XAxis, m_ZAxis);

	Normalize(m_Position);
	Normalize(m_XAxis);
	Normalize(m_YAxis);
	Normalize(m_ZAxis);
}

void Concatenate(VRBTransform& in_Result,
	 			 const VRBTransform& in_A,
				 const VRBTransform& in_B )
{
	math::VMatrix<vfloat32, 4, 4> temp = in_A.GetAsMatrix()*in_B.GetAsMatrix();
    in_Result.Set(temp);
}

//////////////////////////////////////////////////////////////////////////

VRBTransform operator*( const VRBTransform& in_A,
					   const VRBTransform& in_B )
{
	VRBTransform ret;
	Concatenate(ret, in_A, in_B);
	return ret;
}


}} //namespace v3d::entity

