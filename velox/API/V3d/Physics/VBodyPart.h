#ifndef V3D_VBODYPART_2006_02_18_H
#define V3D_VBODYPART_2006_02_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Entity.h>
#include <V3dLib/EntityParts/VRigidBodyPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------

/**
 * a body part connecting VBody to the entity system
 */
class VBody;

class VBodyPart : public entity::VPartBase
{
public:
	typedef VSharedPtr<VBody> BodyPtr;
	VBodyPart(BodyPtr in_pBody);
	virtual ~VBodyPart();
	BodyPtr GetBody();

	// IVPart derived
	void Activate();
	void Deactivate();
	void Update();

	static std::string GetDefaultId();

	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

private:

	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBodyPart;	
	BodyPtr m_pBody;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
V3D_TYPEINFO_WITHPARENT(v3d::physics::VBodyPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VBODYPART_2006_02_18_H
