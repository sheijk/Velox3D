/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VBOUNDINGSPHERE_H
#define V3D_VBOUNDINGSPHERE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Bounding Sphere class for Entitys
 *
 * @author lars
*/
class VBoundingSphere
{
public:

	VBoundingSphere()
	{
		m_Position = VVector3f(0.0f, 0.0f, 0.0f);
		m_fRadius = 1.0f;
	}

	VBoundingSphere(VVector3f in_Position, vfloat32 in_Radius) :
		m_Position(in_Position), m_fRadius(in_Radius)
	{
	}

	/** Sets the Position from the Bounding Sphere */
	void SetPosition(VVector3f in_Position)
	{
		m_Position = in_Position;
	}

	/** Sets the Radius from the Bounding Sphere */
	void SetRadius(vfloat32 in_Radius)
	{
		m_fRadius = in_Radius;
	}

	/** Returned the Position from the Bounding Sphere */
	VVector3f GetPosition() const
	{
		return m_Position;
	}

	/** Returned the Radius from the Bounding Sphere */
	vfloat32 GetRadius() const
	{
		return m_fRadius;
	}

private:

	VVector3f m_Position;
	vfloat32  m_fRadius;
};

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBOUNDINGSPHERE_H
