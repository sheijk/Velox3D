#ifndef V3D_VKEYBOARDCAMERA_H
#define V3D_VKEYBOARDCAMERA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/input.h>
#include <v3d/graphics.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // ...

//TODO: die Buttons in eine Struct oder sowas tun, und durch den 
// benutzer aenderbar machen --sheijk
//REMINDER: kamera von aussen setzbar machen -- sheijk

/**
 * A keyboard controlled VCamera
 *
 * @sheijk
 */
class VKeyboardCamera
{
	input::IVButton* m_pEscapeButton;
	input::IVButton* m_pUpButton;
	input::IVButton* m_pDownButton;
	input::IVButton* m_pLeftButton;
	input::IVButton* m_pRightButton;

	input::IVButton* m_pLeftMouseButton;
	input::IVButton* m_pRightMouseButton;
	input::IVRelativeAxis* m_pMouseXAxis;
	input::IVRelativeAxis* m_pMouseYAxis;

	graphics::VCamera m_Camera;

	void QueryButtons(input::IVInputManager& in_pInputManager);
public:
	VKeyboardCamera(input::IVInputManager& in_InputDevice);

	void Move(float in_fSeconds);

	graphics::VCamera& GetCamera()
	{
		return m_Camera;
	}

	virtual const VMatrix44f& GetTransform();
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VKEYBOARDCAMERA_H
