#include <V3dLib/Graphics/Misc/VKeyboardCamera.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VKeyboardCamera::VKeyboardCamera(input::IVInputManager& in_InputDevice)
{
	QueryButtons(in_InputDevice);
}

void VKeyboardCamera::QueryButtons(input::IVInputManager& in_InputManager)
{
	m_pEscapeButton		= &in_InputManager.GetStandardKey(input::IVInputManager::Escape);
	m_pUpButton			= &in_InputManager.GetStandardKey(input::IVInputManager::CursorUp);
	m_pDownButton		= &in_InputManager.GetStandardKey(input::IVInputManager::CursorDown);
	m_pLeftButton		= &in_InputManager.GetStandardKey(input::IVInputManager::CursorLeft);
	m_pRightButton		= &in_InputManager.GetStandardKey(input::IVInputManager::CursorRight);

	m_pLeftMouseButton	= &in_InputManager.GetMouseButton(1);
	m_pRightMouseButton	= &in_InputManager.GetMouseButton(0);
	m_pMouseXAxis		= &in_InputManager.GetMouseXAxis();
	m_pMouseYAxis		= &in_InputManager.GetMouseYAxis();
}

void VKeyboardCamera::Move(vfloat32 in_fSeconds)
{
	if(m_pUpButton->IsDown() == true)
		m_Camera.MoveForward(5.0f * in_fSeconds);

	if(m_pDownButton->IsDown() == true)
		m_Camera.MoveForward(-5.0f * in_fSeconds);

	if(m_pLeftButton->IsDown() == true)
		m_Camera.Strafe(-5 * in_fSeconds);

	if(m_pRightButton->IsDown() == true)
		m_Camera.Strafe(5 * in_fSeconds);

	if(m_pRightMouseButton->IsDown() == true)
		m_Camera.RotateZ(-25 * in_fSeconds);

	if(m_pLeftMouseButton->IsDown() == true)
		m_Camera.RotateZ(25 * in_fSeconds);

	m_Camera.RotateX(- m_pMouseYAxis->GetLastMovement() * 5 * in_fSeconds);
	m_Camera.RotateY(m_pMouseXAxis->GetLastMovement() * 5 * in_fSeconds);
}

const VMatrix44f& VKeyboardCamera::GetTransform()
{
	return * m_Camera.GetMatrix();
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
