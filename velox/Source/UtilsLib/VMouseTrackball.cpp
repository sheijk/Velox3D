#include <V3d/Utils/VMouseTrackball.h>
//-----------------------------------------------------------------------------
#include <V3d/Math/VVectorOps.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

VMouseTrackball::VMouseTrackball(input::IVMouseDevice* in_pMouse)
{
	m_pRotationAxis = &in_pMouse->GetXAxis();
	m_pAltitudeAxis = &in_pMouse->GetYAxis();
	m_pDistanceAxis = &in_pMouse->GetWheel();
	m_pMovementModifier = &in_pMouse->GetLeftButton();
	m_pResetButton = &in_pMouse->GetRightButton();

	m_fRotationSpeed = 1.0f;
	m_fAltitudeSpeed = 1.0f;
	m_fDistanceSpeed = 1.0f / 120.0f;

	m_fLinearDistance = .0f;
}

namespace {
	vfloat32 Sign(vfloat32 value)
	{
		return value >= .0f ? 1.0f : -1.0f;
	}
}

void VMouseTrackball::Update(vfloat32 in_fSeconds)
{
	if( m_pMovementModifier->IsDown() == false )
	{
		vfloat32 deltaAltitude = 0;
		vfloat32 deltaDirection = 0;

		if( m_pRotationAxis != 0 )
			deltaDirection = - m_pRotationAxis->GetLastMovement();

		if( m_pAltitudeAxis != 0 )
			deltaAltitude = m_pAltitudeAxis->GetLastMovement();

		if( abs(deltaAltitude) > abs(deltaDirection) )
			SetAltitudeAngle(GetAltitudeAngle() + deltaAltitude * m_fAltitudeSpeed);
		else
			SetDirectionAngle(GetDirectionAngle() + deltaDirection * m_fRotationSpeed);

		if( m_pDistanceAxis != 0 ) 
		{
			m_fLinearDistance += m_pDistanceAxis->GetLastMovement() * m_fDistanceSpeed;
			SetDistance(m_fLinearDistance * m_fLinearDistance * Sign(m_fLinearDistance));
			//SetDistance(
			//	GetDistance() -
			//	m_pDistanceAxis->GetLastMovement() * m_fDistanceSpeed);
		}
	}
	else
	{
		const vfloat32 movementSpeed = .2f;

		vfloat32 deltax = m_pRotationAxis->GetLastMovement();
		vfloat32 deltay = - m_pAltitudeAxis->GetLastMovement();
		vfloat32 deltaz = - m_pDistanceAxis->GetLastMovement();

        SetCenter(GetCenter() + (ToVector3f(deltax, deltay, deltaz) * movementSpeed));
	}

	if( m_pResetButton->IsDown() )
	{
		SetCenter(ToVector3f(0, 0, 0));
		SetDirectionAngle(0);
		SetAltitudeAngle(0);
		m_fLinearDistance = 1.0f;
		SetDistance(1.0f);
	}

	RecalculateTransform();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
