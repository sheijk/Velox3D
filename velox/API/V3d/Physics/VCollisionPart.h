/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCOLLISIONPART_2006_04_22_H
#define V3D_VCOLLISIONPART_2006_04_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Entity.h>
#include <V3d/Physics/VGeometry.h>
#include <V3d/Entity/VRigidBodyPart.h>
#include <V3d/Entity/VUpdateablePart.h> //move away
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------

/**
 * This part is used for collision only objects
 */
class VPhysicManagerPart;
class IVBoundingVolumePart;

class VCollisionPart : public entity::IVUpdateablePart
{
public:
	
	VCollisionPart();

	void Update(vfloat32 in_fSeconds);
	
	static std::string GetDefaultId();

	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

protected:
	virtual void OnActivate();
	virtual void OnDeactivate();

private:

	void Create();
	vbool m_bActive;

	virtual void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer);

	entity::VNodeConnection<physics::VPhysicManagerPart> m_pPhysicManagerPart;
	entity::VNodeConnection<physics::IVBoundingVolumePart> m_pVolumePart;
	entity::VNodeConnection<entity::VRigidBodyPart> m_pRigidBodyPart;
	entity::VNodeConnection<entity::VUpdateManagerPart> m_pUpdateManager;

	VSharedPtr<physics::VGeometry> m_pGeometry;
	math::VVector3f m_Position;
		
};

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
V3D_TYPEINFO_WITHPARENT(v3d::physics::VCollisionPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif //V3D_VCOLLISIONPART_2006_04_22_H

