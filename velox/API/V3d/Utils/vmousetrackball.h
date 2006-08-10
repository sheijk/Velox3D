#ifndef V3D_VMOUSETRACKBALL_2005_10_15_H
#define V3D_VMOUSETRACKBALL_2005_10_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Input/IVRelativeAxis.h>
#include <V3d/Input/IVMouseDevice.h>
#include <V3d/Utils/VTrackball.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VMouseTrackball : public VTrackball
{
public:
	VMouseTrackball(input::IVMouseDevice* in_pMouse);

	void Update(vfloat32 in_fSeconds);

private:
	input::IVRelativeAxis* m_pRotationAxis;
	input::IVRelativeAxis* m_pAltitudeAxis;
	input::IVRelativeAxis* m_pDistanceAxis;
	input::IVButton* m_pMovementModifier;
	input::IVButton* m_pResetButton;

	vfloat32 m_fRotationSpeed;
	vfloat32 m_fAltitudeSpeed;
	vfloat32 m_fDistanceSpeed;

	vfloat32 m_fLinearDistance;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VMOUSETRACKBALL_2005_10_15_H
