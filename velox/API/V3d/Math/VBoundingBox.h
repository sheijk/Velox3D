#ifndef V3D_VBOUNDINGBOX_H
#define V3D_VBOUNDINGBOX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Math.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Bounding Box class for Entitys
 *
 * @author lars / ins
*/
class VBoundingBox
{
public:

	VBoundingBox()
	{
		m_MinPoint = VVector3f(0.0f, 0.0f, 0.0f);
		m_MaxPoint = VVector3f(1.0f, 1.0f, 1.0f);
		CalcLength();
	}

	VBoundingBox(VVector3f in_MinPoint, VVector3f in_MaxPoint) :
		m_MinPoint(in_MinPoint), m_MaxPoint(in_MaxPoint)
	{
		CalcLength();
	}

	/** Sets the Min Point for the Bounding Box */
	void SetMinPoint(VVector3f in_MinPoint)
	{
		m_MinPoint = in_MinPoint;
		CalcLength();
	}

	/** Sets the Max Point for the Bounding Box */
	void SetMaxPoint(VVector3f in_MaxPoint)
	{
		m_MaxPoint = in_MaxPoint;
		CalcLength();
	}
	
	/** Returned the Min Point from the Bounding Box */
	VVector3f GetMinPoint() const
	{
		return m_MinPoint;
	}

	/** Returned the Max Point from the Bounding Box */
	VVector3f GetMaxPoint() const
	{
		return m_MaxPoint;
	}

	void CalcLength()
	{
		m_Length = VVector3f(m_MaxPoint.GetX() - m_MinPoint.GetX(),
			m_MaxPoint.GetY() - m_MinPoint.GetY(),
			m_MaxPoint.GetZ() - m_MinPoint.GetZ());
	}

	/** Returned the Size from the Bounding Box*/
	//TODO: was ist die size einer box? --ins
	VVector3f GetLength() const
	{
		return m_Length;
	}

private:

	VVector3f m_MinPoint;
	VVector3f m_MaxPoint;
	VVector3f m_Length;
};

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBOUNDINGBOX_H