#ifndef V3D_VFPSMOVERPART_2006_01_22_H
#define V3D_VFPSMOVERPART_2006_01_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Input.h>
#include <V3d/Graphics.h>
#include <V3d/Graphics/Misc/IVCamera.h>
#include <V3d/Graphics/Misc/VCamera.h>
#include <V3d/Entity/VUpdateablePart.h>
#include <V3d/Entity/VRigidBodyPart.h>
#include <V3d/Utils/VInputPart.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VFPSMoverPart : public entity::VPartBaseAdapter<entity::IVUpdateablePart>
{
public:
	VFPSMoverPart();
	virtual ~VFPSMoverPart();

	virtual void Update(vfloat32 in_fSeconds);

	virtual void Activate();
	virtual void Deactivate();
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

	void QueryButtons(input::IVInputManager& in_pInputManager);
private:
	void MoveForward(vfloat32 in_fDistance);
	void StrafeRight(vfloat32 in_fDistance);
	void MoveUp(vfloat32 in_fDistance);

	void RotateX(vfloat32 in_fAngleDegree);
	void RotateY(vfloat32 in_fAngleDegree);
	void RotateZ(vfloat32 in_fAngelDegree);

	void MoveBy(const math::VVector3f& in_Distance);
	void RotateAround(const math::VVector3f& in_Axis, vfloat32 in_fAngle);

	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBody;
	entity::VPartConnection<entity::VUpdateManagerPart> m_pUpdateManager;
	entity::VPartConnection<utils::VInputPart> m_pInputPart;

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
	input::IVRelativeAxis* m_pMouseYAxis;};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils

V3D_TYPEINFO_WITHPARENT(v3d::utils::VFPSMoverPart, v3d::entity::IVUpdateablePart);
//-----------------------------------------------------------------------------
#endif // V3D_VFPSMOVERPART_2006_01_22_H
