#include <v3dlib/Math/VRBTransform.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VRBTransform::Type VRBTransform::defaultType = VRBTransform::LeftHanded;

VRBTransform::VRBTransform()
{
	m_XAxis = VVector3f(1.0f, 0.0f, 0.0f);
	m_YAxis = VVector3f(0.0f, 1.0f, 0.0f);
	m_ZAxis = VVector3f(0.0f, 0.0f, 1.0f);
	m_Position = VVector3f(0.0f, 0.0f, 0.0f);
}

//////////////////////////////////////////////////////////////////////////

VRBTransform::VRBTransform(const VVector3f& in_Position,
						   const VVector3f& in_Direction,
						   const VVector3f& in_Up,
						   const Type in_Type)
{
	V3D_ASSERT( Length(in_Up) != 0.0f );

	SetLookAt(in_Position, in_Direction, in_Up, in_Type);
}

VRBTransform::VRBTransform(VMatrix44f in_Matrix)
{
	Set(in_Matrix);
}

//////////////////////////////////////////////////////////////////////////

void VRBTransform::SetLookAt(const VVector3f& in_Position,
							 const VVector3f& in_Direction,
							 const VVector3f& in_Up,
							 const Type in_Type)
{
	V3D_ASSERT( Length(in_Up) != 0.0f );

	m_Position = in_Position;
	SetLookAt( in_Direction, in_Up, in_Type);
}

//////////////////////////////////////////////////////////////////////////

void VRBTransform::SetLookAt(const VVector3f& in_Direction,
							 const VVector3f& in_Up,
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

VVector3f VRBTransform::GetXAxis() const
{
	return m_XAxis;
}

//////////////////////////////////////////////////////////////////////////

VVector3f VRBTransform::GetYAxis() const
{
	return m_YAxis;
}

//////////////////////////////////////////////////////////////////////////

VVector3f VRBTransform::GetZAxis() const
{
	return m_ZAxis;
}

//////////////////////////////////////////////////////////////////////////

void VRBTransform::SetPosition(const VVector3f& in_Position)
{
	m_Position = in_Position;
}

//////////////////////////////////////////////////////////////////////////

VVector3f VRBTransform::GetPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

VMatrix44f VRBTransform::GetAsMatrix() const
{
	//TODO: funktion duerfte bei "unregulaeren" matrizen komische
	//ergebnisse haben, sowas sollte abgefangen, oder zumindest dokumentiert
	//werden --sheijk
	
	VMatrix44f ret;

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

void VRBTransform::Set(VMatrix44f in_Matrix)
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
	VMatrix44f temp = in_A.GetAsMatrix()*in_B.GetAsMatrix();
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

