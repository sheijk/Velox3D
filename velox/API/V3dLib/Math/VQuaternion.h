#ifndef V3D_VQUATERNION_01_8_04_H
#define V3D_VQUATERNION_01_8_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <gmtl/Quat.h>
//-----------------------------------------------------------------------------
namespace v3d{
//-----------------------------------------------------------------------------
/**
 * Wrapps a quaternion representation out of gmtl
 * @author: ins
 */

template <typename Scalar>
class VQuaternion
{
	typedef gmtl::Quat<Scalar> QuatImpl;

public:
	QuatImpl m_Data;

	void Set(Scalar x, Scalar y, Scalar z, Scalar w)
	{
		m_Data.set(x,y,z,w);
	}
	
	void Get(Scalar& x, Scalar& y, Scalar& z, Scalar& w)
	{
		m_Data.get(x,y,z,w);
	}

	Scalar& operator[] (const vuint8 index)
	{
		return m_Data.mData[index]; //gmtl throws exception here
	}

	VQuaternion()
	{
	}

	VQuaternion(const VQuaternion& in_Quaternion)
	{
		m_Data = in_Quaternion.m_Data;
	}
	
	//vc seems not iso compailent - took 15 mins...
	VQuaternion(const QuatImpl& quat) : m_Data(quat)
	{
	}
	

	VQuaternion& operator=(const VQuaternion& in_Quaternion)
	{
		this->m_Data = in_Quaternion.m_Data;
		return *this;
	}
};

typedef VQuaternion<vfloat32> VQuatf;
typedef VQuaternion<vfloat64> VQuatd;
//-----------------------------------------------------------------------------
} //namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VQUATERNION_01_8_04_H




