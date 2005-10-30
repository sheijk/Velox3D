#ifndef V3D_VPLANE_H
#define V3D_VPLANE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Math.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
* Plane Class
*
* @author lars
*/
class VPlane
{
public:

	VPlane()
	{
		m_Normal = VVector3f(0.0f, 0.0f, 0.0f);
		m_Distance = 0.0f;
	}

	VPlane(VVector3f in_Normal, vfloat32 in_Distance) :
		m_Normal(in_Normal), m_Distance(in_Distance)
	{
	}

	/** Sets the Normal for the Plane */
	void SetNormal(VVector3f in_Normal)
	{
		m_Normal = in_Normal;
	}

	/** Sets the Distance for the Plane */
	void SetDistance(vfloat32 in_Distance)
	{
		m_Distance = in_Distance;
	}

	/** Returned the Normal from the Ray */
	VVector3f GetNormal() const
	{
		return m_Normal;
	}

	/** Returned the Distance from the Ray */
	vfloat32 GetDistance() const
	{
		return m_Distance;
	}

private:

	VVector3f m_Normal;
	vfloat32  m_Distance;
};

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPLANE_H