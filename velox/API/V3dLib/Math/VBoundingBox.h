#ifndef V3D_VBOUNDINGBOX_H
#define V3D_VBOUNDINGBOX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Bounding Box class for Entitys
 *
 * @author lars
*/
class VBoundingBox
{
public:

	VBoundingBox()
	{
		m_MinPoint = VVector3f(0.0f, 0.0f, 0.0f);
		m_MaxPoint = VVector3f(1.0f, 1.0f, 1.0f);
	}

	VBoundingBox(VVector3f in_MinPoint, VVector3f in_MaxPoint) :
		m_MinPoint(in_MinPoint), m_MaxPoint(in_MaxPoint)
	{
	}

	/** Sets the Position from the Bounding Sphere */
	void SetMinPoint(VVector3f in_MinPoint)
	{
		m_Position = in_Position;
	}

	/** Sets the Radius from the Bounding Sphere */
	void SetMaxPoint(VVector3f in_MaxPoint)
	{
		m_fRadius = in_Radius;
	}

	/** Returned the Position from the Bounding Sphere */
	VVector3f GetMinPoint() const
	{
		return m_MinPoint;
	}

	/** Returned the Radius from the Bounding Sphere */
	VVector3f GetMaxPoint() const
	{
		return m_MaxPoint;
	}

private:

	VVector3f m_MinPoint;
	VVector3f m_MaxPoint;
};

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBOUNDINGBOX_H