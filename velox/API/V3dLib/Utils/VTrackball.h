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

	VVector3f GetViewPoint() const;

	VVector3f GetUpVector() const;

	void RecalculateTransform();

	vfloat32 GetAltitudeAngle() const;
	void SetAltitudeAngle(vfloat32 in_AltitudeAngle);

	vfloat32 GetDirectionAngle() const;
	void SetDirectionAngle(vfloat32 in_DirectionAngle);

	vfloat32 GetDistance() const;
	void SetDistance(vfloat32 in_fDistance);

	VVector3f GetCenter() const;
	void SetCenter(const VVector3f& in_Center);

private:
	vfloat32 m_fAltitudeAngle;
	vfloat32 m_fDirectionAngle;
	vfloat32 m_fDistance;
	VVector3f m_Center;

	math::VRBTransform m_Transform;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VTRACKBALL_2005_10_15_H
