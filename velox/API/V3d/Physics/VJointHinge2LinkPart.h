#ifndef V3D_VJOINTHINGE2LINKPART_2006_06_05_H
#define V3D_VJOINTHINGE2LINKPART_2006_06_05_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Physics/VJointHinge2Part.h>
#include <V3d/Entity.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------

class VJointHinge2LinkPart : public entity::VPartBase
{
public:
	
	VJointHinge2LinkPart();
	
	// IVPart derived
	void Activate();
	void Deactivate();
	
	static std::string GetDefaultId();

	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

private:

	virtual void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer);
	entity::VPartConnection<physics::VJointHinge2Part> m_pJointHinge2;
	entity::VPartConnection<physics::VBodyPart> m_pBodyPart;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
V3D_TYPEINFO_WITHPARENT(v3d::physics::VJointHinge2LinkPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif //V3D_VJOINTHINGE2LINKPART_2006_06_05_H