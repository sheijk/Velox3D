#ifndef V3D_VCOLLISIONPART_2006_04_22_H
#define V3D_VCOLLISIONPART_2006_04_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Entity.h>
#include <V3d/Physics/VGeometry.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------

/**
 * This part is used for collision only objects
 */
class VPhysicManagerPart;
class IVBoundingVolumePart;

class VCollisionPart : public entity::VPartBase
{
public:
	
	VCollisionPart();

	
	// IVPart derived
	void Activate();
	void Deactivate();
	
	static std::string GetDefaultId();

	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

private:

	void Create();
	vbool m_bActive;

	virtual void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer);

	entity::VPartConnection<physics::VPhysicManagerPart> m_pPhysicManagerPart;
	entity::VPartConnection<physics::IVBoundingVolumePart> m_pVolumePart;

	VSharedPtr<physics::VGeometry> m_pGeometry;
		
};

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
V3D_TYPEINFO_WITHPARENT(v3d::physics::VCollisionPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif //V3D_VCOLLISIONPART_2006_04_22_H
