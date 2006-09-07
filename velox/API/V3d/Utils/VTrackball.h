/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTRACKBALL_2005_10_15_H
#define V3D_VTRACKBALL_2005_10_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VRBTransform.h>
#include <V3d/Math/VVector.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VTrackball
{
public:
	VTrackball();

	math::VRBTransform GetTransform();

	math::VVector3f GetViewPoint() const;

	math::VVector3f GetUpVector() const;

	void RecalculateTransform();

	vfloat32 GetAltitudeAngle() const;
	void SetAltitudeAngle(vfloat32 in_AltitudeAngle);

	vfloat32 GetDirectionAngle() const;
	void SetDirectionAngle(vfloat32 in_DirectionAngle);

	vfloat32 GetDistance() const;
	void SetDistance(vfloat32 in_fDistance);

	math::VVector3f GetCenter() const;
	void SetCenter(const math::VVector3f& in_Center);

private:
	vfloat32 m_fAltitudeAngle;
	vfloat32 m_fDirectionAngle;
	vfloat32 m_fDistance;
	math::VVector3f m_Center;

	math::VRBTransform m_Transform;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VTRACKBALL_2005_10_15_H

