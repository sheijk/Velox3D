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
	m_pEscapeButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::Key_Escape);
	m_pUpButton			= &in_InputManager.GetStandardKeyboard().GetKey(input::Key_Up);
	m_pDownButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::Key_Down);
	m_pLeftButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::Key_Left);
	m_pRightButton		= &in_InputManager.GetStandardKeyboard().GetKey(input::Key_Right);

	m_pLeftMouseButton	= &in_InputManager.GetStandardMouse().GetLeftButton();
	m_pRightMouseButton	= &in_InputManager.GetStandardMouse().GetRightButton();
	m_pMouseXAxis		= &in_InputManager.GetStandardMouse().GetXAxis();
	m_pMouseYAxis		= &in_InputManager.GetStandardMouse().GetYAxis();
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
