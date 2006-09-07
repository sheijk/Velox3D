/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VKEYBOARDCAMERA_H
#define V3D_VKEYBOARDCAMERA_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Input.h>
#include <V3d/Graphics.h>
#include <V3d/Graphics/Misc/IVCamera.h>
#include <V3d/Graphics/Misc/VCamera.h>

#include <string>
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
class VKeyboardCamera : public IVCamera
{
public:
	VKeyboardCamera(input::IVInputManager& in_InputDevice);
	virtual ~VKeyboardCamera();

	void Move(float in_fSeconds);

	graphics::VCamera& GetCamera();
	const graphics::VCamera& GetCamera() const;

	virtual V3D_DEPRECATED const math::VMatrix44f& GetTransform() const;
	virtual const math::VMatrix44f& ViewMatrix() const;
	virtual const math::VRBTransform& Transform() const;

	virtual void ApplyTo(IVDevice& in_Device) const;

	virtual math::VVector3f GetPosition() const;
	virtual math::VVector3f GetViewDirection() const;
	virtual math::VVector3f GetUpVector() const;

	void SetMovementSpeed(vfloat32 m_fMovementSpeed);
	vfloat32 GetMovementSpeed() const;
	void SetRotationSpeedX(vfloat32 in_fNewSpeedX);
	vfloat32 GetRotationSpeedX() const;
	void SetRotationSpeedY(vfloat32 in_fNewSpeedX);
	vfloat32 GetRotationSpeedY() const;
	void SetRotationSpeedZ(vfloat32 in_fNewSpeedX);
	vfloat32 GetRotationSpeedZ() const;

	void SetIgnoreMouse(vbool in_bMouseIgnored);
	vbool IsMouseIgnored() const;

private:
	void QueryButtons(input::IVInputManager& in_pInputManager);
	void LoadCameraPositions(const std::string& in_strFileName);
	void SaveCameraPositions(const std::string& in_strFileName);

	vbool m_bIgnoreMouse;

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

	std::vector<input::IVButton*> m_GotoButtons;
	input::IVButton* m_pSavePosModifierButton;

	typedef std::map<vuint, math::VRBTransform> SavedOrientationMap;
	SavedOrientationMap m_SavedOrientations;

	graphics::VCamera m_Camera;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VKEYBOARDCAMERA_H

