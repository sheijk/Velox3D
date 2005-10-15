#include <V3dLib/Utils/VMouseTrackball.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VMouseTrackball::VMouseTrackball(input::IVMouseDevice* in_pMouse)
{
	m_pRotationAxis = &in_pMouse->GetXAxis();
	m_pAltitudeAxis = &in_pMouse->GetYAxis();
	m_pDistanceAxis = &in_pMouse->GetWheel();

	m_fRotationSpeed = 1.0f;
	m_fAltitudeSpeed = 1.0f;
	m_fDistanceSpeed = 1.0f / 120.0f;
}

void VMouseTrackball::Update(vfloat32 in_fSeconds)
{
	vfloat32 deltaAltitude = 0;
	vfloat32 deltaDirection = 0;

	if( m_pRotationAxis != 0 )
		deltaDirection = m_pRotationAxis->GetLastMovement();

	if( m_pAltitudeAxis != 0 )
		deltaAltitude = m_pAltitudeAxis->GetLastMovement();

	if( abs(deltaAltitude) > abs(deltaDirection) )
		SetAltitudeAngle(GetAltitudeAngle() + deltaAltitude * m_fAltitudeSpeed);
	else
		SetDirectionAngle(GetDirectionAngle() + deltaDirection * m_fRotationSpeed);

	if( m_pDistanceAxis != 0 )
		SetDistance(GetDistance() + 
		m_pDistanceAxis->GetLastMovement() * m_fDistanceSpeed);

	RecalculateTransform();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
