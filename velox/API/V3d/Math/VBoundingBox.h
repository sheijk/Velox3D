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
 * @author lars
*/
class VBoundingBox
{
public:

	VBoundingBox()
	{
		m_MinPoint = VVector3f(0.0f, 0.0f, 0.0f);
		m_MaxPoint = VVector3f(1.0f, 1.0f, 1.0f);
		m_Size = VVector3f(0.0f, 0.0f, 0.0f);
	}

	VBoundingBox(VVector3f in_MinPoint, VVector3f in_MaxPoint, VVector3f in_Size) :
		m_MinPoint(in_MinPoint), m_MaxPoint(in_MaxPoint), m_Size(in_Size)
	{
	}

	/** Sets the Min Point for the Bounding Box */
	void SetMinPoint(VVector3f in_MinPoint)
	{
		m_MinPoint = in_MinPoint;
	}

	/** Sets the Max Point for the Bounding Box */
	void SetMaxPoint(VVector3f in_MaxPoint)
	{
		m_MaxPoint = in_MaxPoint;
	}

	/** Sets the Size for the Bounding Box */
	void SetSize(VVector3f in_Size)
	{
		m_Size = in_Size;
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

	/** Returned the Size from the Bounding Box*/
	VVector3f GetSize() const
	{
		return m_Size;
	}

private:

	VVector3f m_MinPoint;
	VVector3f m_MaxPoint;
	VVector3f m_Size;
};

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBOUNDINGBOX_H