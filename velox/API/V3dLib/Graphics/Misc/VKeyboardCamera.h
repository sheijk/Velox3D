#ifndef V3D_VKEYBOARDCAMERA_H
#define V3D_VKEYBOARDCAMERA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Input.h>
#include <v3d/Graphics.h>
#include <V3dLib/Graphics/Misc/VCamera.h>

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
public:
	VKeyboardCamera(input::IVInputManager& in_InputDevice);

	void Move(float in_fSeconds);

	graphics::VCamera& GetCamera();
	const graphics::VCamera& GetCamera() const;

	virtual const VMatrix44f& GetTransform() const;

	void SetMovementSpeed(vfloat32 m_fMovementSpeed);
	vfloat32 GetMovementSpeed() const;
	void SetRotationSpeedX(vfloat32 in_fNewSpeedX);
	vfloat32 GetRotationSpeedX() const;
	void SetRotationSpeedY(vfloat32 in_fNewSpeedX);
	vfloat32 GetRotationSpeedY() const;
	void SetRotationSpeedZ(vfloat32 in_fNewSpeedX);
	vfloat32 GetRotationSpeedZ() const;

private:
	void QueryButtons(input::IVInputManager& in_pInputManager);

	vfloat32 m_fMovementSpeed;
	vfloat32 m_fRotationSpeedX;
	vfloat32 m_fRotationSpeedY;
	vfloat32 m_fRotationSpeedZ;
	vfloat32 m_fKeyRotationFactor;

	input::IVButton* m_pForwardButton;
	input::IVButton* m_pBackwardButton;
	input::IVButton* m_pLeftButton;
	input::IVButton* m_pRightButton;

	input::IVButton* m_pUpButton;
	input::IVButton* m_pDownButton;

	input::IVButton* m_pRotateLeftButton;
	input::IVButton* m_pRotateRightButton;
	input::IVButton* m_pRotateUpButton;
	input::IVButton* m_pRotateDownButton;

	input::IVButton* m_pFastTriggerButton;

	input::IVButton* m_pRollLeftButton;
	input::IVButton* m_pRollRightButton;
	input::IVButton* m_pRollLeftButton2;
	input::IVButton* m_pRollRightButton2;
	input::IVRelativeAxis* m_pMouseXAxis;
	input::IVRelativeAxis* m_pMouseYAxis;

	graphics::VCamera m_Camera;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VKEYBOARDCAMERA_H
