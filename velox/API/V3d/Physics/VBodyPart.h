/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VBODYPART_2006_02_18_H
#define V3D_VBODYPART_2006_02_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Entity.h>
#include <V3d/Entity/VRigidBodyPart.h> //todo: sollte da verschwinden und in v3d/
#include <V3d/Physics/VBody.h>
#include <V3d/Entity/VUpdateablePart.h> //move away
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------

/**
 * a body part connecting VBody to the entity system
 */
//class VBody;
class VPhysicManagerPart;
class IVBoundingVolumePart;

class VBodyPart : public entity::VPartBaseAdapter<entity::IVUpdateablePart>
{
public:
	typedef VSharedPtr<VBody> BodyPtr;
	
	VBodyPart(BodyPtr in_pBody);
	VBodyPart();

	virtual ~VBodyPart();
	BodyPtr GetBody();

	// IVPart derived
	void Activate();
	void Deactivate();
	void Update(vfloat32 in_fSeconds);

	static std::string GetDefaultId();

	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

private:

	void Create();

	virtual void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer);

	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBodyPart;	
	entity::VPartConnection<physics::VPhysicManagerPart> m_pPhysicManagerPart;
	entity::VPartConnection<physics::IVBoundingVolumePart> m_pVolumePart;
	entity::VPartConnection<entity::VUpdateManagerPart> m_pUpdateManager;
	
	BodyPtr m_pBody;
	vfloat32 m_fMass;
	math::VVector3f m_Position;
	std::string m_sIdentifier;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
V3D_TYPEINFO_WITHPARENT(v3d::physics::VBodyPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VBODYPART_2006_02_18_H

