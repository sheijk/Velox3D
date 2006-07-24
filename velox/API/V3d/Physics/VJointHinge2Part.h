#ifndef V3D_VJOINTHINGE2PART_2006_05_05_H
#define V3D_VJOINTHINGE2PART_2006_05_05_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Physics/VJointHinge2.h>
#include <V3d/Physics/VBodyPart.h>
#include <V3d/Entity.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------

/**
 * This part is used for joints
 * author: ins
 */

class VPhysicManagerPart;
class VBody;

class VJointHinge2Part : public entity::VPartBase
{
public:
	
	VJointHinge2Part();
	
	// IVPart derived
	void Activate();
	void Deactivate();
	
	void RegisterBody(VBody* in_pAddress);
	void UnregisterBody(VBody* in_pAddress);
	
	VJointHinge2& GetJointHinge2();

	static std::string GetDefaultId();

	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

private:

	void Create();

	virtual void OnMessage(
		const messaging::VMessage& in_Message,
		messaging::VMessage* in_pAnswer);
	entity::VPartConnection<physics::VPhysicManagerPart> m_pPhysicManagerPart;
	
	VJointHinge2 m_Joint;
	vbool m_bIsLinkedByBodyOne;
	vbool m_bIsLinkedByBodyTwo;
	VBody* m_pBodyAddressOne;
	VBody* m_pBodyAddressTwo;

	vbool m_bIsActive;
	vbool m_bIsReady;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
V3D_TYPEINFO_WITHPARENT(v3d::physics::VJointHinge2Part, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif //V3D_VJOINTHINGE2PART_2006_05_05_H
