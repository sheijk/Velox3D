#ifndef V3D_VJOINTHINGE2MODIFIERPART_2006_06_05_H
#define V3D_VJOINTHINGE2MODIFIERPART_2006_06_05_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Physics/VJointHinge2Part.h>
#include <V3d/Input/VKeyCode.h>
#include <V3d/Input/IVButton.h>
#include <V3d/Utils/VInputPart.h>
#include <V3d/Entity.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------

class VJointHinge2ModifierPart : public entity::VPartBaseAdapter<entity::IVUpdateablePart>
{
public:
	
	VJointHinge2ModifierPart();
	
	// IVPart derived
	void Activate();
	void Deactivate();
	void Update(vfloat32 in_fSeconds);
	
	static std::string GetDefaultId();

	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

private:

	virtual void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer);
	entity::VPartConnection<physics::VJointHinge2Part> m_pJointHinge2;
	entity::VPartConnection<utils::VInputPart> m_pInputManager;
	entity::VPartConnection<entity::VUpdateManagerPart> m_pUpdateManager;

	input::VKeyCode m_ListeningEvent;
	input::VKeyCode m_ListeningEvent2;
	input::IVButton* m_pButton;
	input::IVButton* m_pButton2;
	input::IVButton* m_pButton3;
	input::IVButton* m_pButton4;
	input::IVButton* m_pButton5;

	vfloat32 m_fSpeedFactor;
	vfloat32 m_fSteerFactor;

	vfloat32 m_fSteering;
	vfloat32 m_fSpeed;
	vfloat32 m_fMaxSpeed;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
V3D_TYPEINFO_WITHPARENT(v3d::physics::VJointHinge2ModifierPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif //V3D_VJOINTHINGE2MODIFIERPART_2006_06_05_H