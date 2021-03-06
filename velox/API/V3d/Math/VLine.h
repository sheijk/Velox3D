/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VLINE_H
#define V3D_VLINE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
* Line Class
*
* @author lars
*/
class VLine
{
public:

	VLine()
	{
		m_Origin = VVector3f(0.0f, 0.0f, 0.0f);
		m_Direction = VVector3f(0.0f, 0.0f, 0.0f);
	}

	VLine(VVector3f in_Origin, VVector3f in_Direction) :
		m_Origin(in_Origin), m_Direction(in_Direction)
	{
	}

	/** Sets the Origin for the Bounding Box */
	void SetOrigin(VVector3f in_Origin)
	{
		m_Origin = in_Origin;
	}

	/** Sets the Direction for the Bounding Box */
	void SetDirection(VVector3f in_Direction)
	{
		m_Direction = in_Direction;
	}


	/** Returned the Origin from the Bounding Box */
	VVector3f GetOrigin() const
	{
		return m_Origin;
	}

	/** Returned the Direction from the Bounding Box */
	VVector3f GetDirection() const
	{
		return m_Direction;
	}

private:

	VVector3f m_Origin;
	VVector3f m_Direction;
};

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VLINE_H
