#ifndef V3D_VHALFRAY_H
#define V3D_VHALFRAY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Ray class for the Picking from Entitys
 *
 * @author lars
 */
class VHalfRay
{
public:

	VHalfRay()
	{
		m_StartPoint = VVector3f(0.0f, 0.0f, 0.0f);
		m_Direction = VVector3f(0.0f, 0.0f, 0.0f);
	}

	VHalfRay(VVector3f in_StartPoint, VVector3f in_Direction) :
		m_StartPoint(in_StartPoint), m_Direction(in_Direction)
	{
	}

	/** Sets the Start Point from the Ray */
	void SetStartPoint(VVector3f in_StartPoint)
	{
		m_StartPoint = in_StartPoint;
	}

	/** Sets the Start Point from the Ray */
	void SetDirection(VVector3f in_Direction)
	{
		m_Direction = in_Direction;
	}

	/** Returned the Start Point from the Ray */
	VVector3f GetStartPoint() const
	{
		return m_StartPoint;
	}

	/** Returned the Direction from the Ray */
	VVector3f GetDirection() const
	{
		return m_Direction;
	}

private:

	VVector3f m_StartPoint;
	VVector3f m_Direction;
};

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VHALFRAY_H