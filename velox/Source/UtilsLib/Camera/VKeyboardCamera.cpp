#include <V3dLib/Graphics/Misc/VKeyboardCamera.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VKeyboardCamera::VKeyboardCamera(input::IVInputManager& in_InputDevice)
{
	QueryButtons(in_InputDevice);

	m_fMovementSpeed = 2.0f;
	m_fRotationSpeedX = 1.0f;
	m_fRotationSpeedY = 1.0f;
	m_fRotationSpeedZ = 10.0f;
	m_fKeyRotationFactor = 50.0f;
}

void VKeyboardCamera::QueryButtons(input::IVInputManager& in_InputManager)
{
	//m_pUpButton			= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyUp);
	//m_pDownButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyDown);
	//m_pLeftButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyLeft);
	//m_pRightButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyRight);

	m_pForwardButton	= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyW);
	m_pBackwardButton	= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyS);
	m_pLeftButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyA);
	m_pRightButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyD);
	m_pUpButton			= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyR);
	m_pDownButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyF);

	m_pRotateLeftButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyLeft);
	m_pRotateRightButton	= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyRight);
	m_pRotateUpButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyUp);
	m_pRotateDownButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyDown);

	m_pRollLeftButton2	= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyQ);
	m_pRollRightButton2	= &in_InputManager.GetStandardKeyboard().GetKey(input::KeyE);

	m_pRollLeftButton	= &in_InputManager.GetStandardMouse().GetLeftButton();
	m_pRollRightButton	= &in_InputManager.GetStandardMouse().GetRightButton();
	m_pMouseXAxis		= &in_InputManager.GetStandardMouse().GetXAxis();
	m_pMouseYAxis		= &in_InputManager.GetStandardMouse().GetYAxis();

	m_pFastTriggerButton = &in_InputManager.GetStandardKeyboard().GetKey(input::KeyLeftShift);
}

graphics::VCamera& VKeyboardCamera::GetCamera()
{
	return m_Camera;
}

const graphics::VCamera& VKeyboardCamera::GetCamera() const
{
	return m_Camera;
}

void VKeyboardCamera::Move(vfloat32 in_fSeconds)
{
	if( m_pFastTriggerButton->IsDown() == true )
		in_fSeconds *= 4;

	// strafing
	if(m_pForwardButton->IsDown() == true)
		m_Camera.MoveForward(m_fMovementSpeed * in_fSeconds);

	if(m_pBackwardButton->IsDown() == true)
		m_Camera.MoveForward(-m_fMovementSpeed* in_fSeconds);

	if(m_pLeftButton->IsDown() == true)
		m_Camera.Strafe(-m_fMovementSpeed * in_fSeconds);

	if(m_pRightButton->IsDown() == true)
		m_Camera.Strafe(m_fMovementSpeed * in_fSeconds);

	if(m_pUpButton->IsDown() == true)
		m_Camera.MoveUp(m_fMovementSpeed * in_fSeconds);

	if(m_pDownButton->IsDown() == true)
		m_Camera.MoveUp(-m_fMovementSpeed * in_fSeconds);

	// keyboard rotation
	if( m_pRotateLeftButton->IsDown() == true )
		m_Camera.RotateY(-m_fRotationSpeedY * m_fKeyRotationFactor  * in_fSeconds);

	if( m_pRotateRightButton->IsDown() == true )
		m_Camera.RotateY(m_fRotationSpeedY * m_fKeyRotationFactor * in_fSeconds);

	if( m_pRotateUpButton->IsDown() == true )
		m_Camera.RotateX(m_fRotationSpeedX * m_fKeyRotationFactor  * in_fSeconds);

	if( m_pRotateDownButton->IsDown() == true )
		m_Camera.RotateX(-m_fRotationSpeedX * m_fKeyRotationFactor  * in_fSeconds);

	// mouse rotation
	if(m_pRollRightButton->IsDown() == true || m_pRollRightButton2->IsDown() == true)
		m_Camera.RotateZ(-m_fRotationSpeedZ * in_fSeconds);

	if(m_pRollLeftButton->IsDown() == true || m_pRollLeftButton2->IsDown() == true)
		m_Camera.RotateZ(m_fRotationSpeedZ * in_fSeconds);

	m_Camera.RotateX(- m_pMouseYAxis->GetLastMovement() * m_fRotationSpeedX * in_fSeconds);
	m_Camera.RotateY(m_pMouseXAxis->GetLastMovement() * m_fRotationSpeedY * in_fSeconds);
}

const VMatrix44f& VKeyboardCamera::GetTransform() const
{
	return m_Camera.TransformMatrix();
}

void VKeyboardCamera::SetMovementSpeed(vfloat32 in_fMovementSpeed)
{
	m_fMovementSpeed = in_fMovementSpeed;
}

vfloat32 VKeyboardCamera::GetMovementSpeed() const
{
	return m_fMovementSpeed;
}

void VKeyboardCamera::SetRotationSpeedX(vfloat32 in_fNewSpeedX)
{
	m_fRotationSpeedX = in_fNewSpeedX;
}

vfloat32 VKeyboardCamera::GetRotationSpeedX() const
{
	return m_fRotationSpeedX;
}

void VKeyboardCamera::SetRotationSpeedY(vfloat32 in_fNewSpeedY)
{
	m_fRotationSpeedY = in_fNewSpeedY;
}

vfloat32 VKeyboardCamera::GetRotationSpeedY() const
{
	return m_fRotationSpeedY;
}

void VKeyboardCamera::SetRotationSpeedZ(vfloat32 in_fNewSpeedZ)
{
	m_fRotationSpeedZ = in_fNewSpeedZ;
}

vfloat32 VKeyboardCamera::GetRotationSpeedZ() const
{
	return m_fRotationSpeedZ;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
