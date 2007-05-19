/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VPHYSICMANAGERPART_2006_04_10_H
#define V3D_VPHYSICMANAGERPART_2006_04_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
//#include <V3d/Physics/VPhysics.h>
#include <V3d/Physics/VPhysicManager.h>
#include <V3d/Entity.h>
#include <V3d/Entity/VUpdateablePart.h> //move away
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
class VPhysicManagerPart : public entity::VPartBaseAdapter<entity::IVUpdateablePart>
{
public:

	VPhysicManagerPart();
	virtual ~VPhysicManagerPart();

	physics::VPhysicManagerPtr GetPhysicManager();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

	void Update(vfloat32 in_fSeconds);
private:
	virtual void OnActivate();
	virtual void OnDeactivate();

	virtual void OnMessage(
		const messaging::VMessage& in_Message,
		messaging::VMessage* in_pAnswer);

	entity::VPartConnection<entity::VUpdateManagerPart> m_pUpdateManager;

	physics::VPhysicManagerPtr m_pPhysicManager;
};



//-----------------------------------------------------------------------------
}} // namespace v3d::physics
V3D_TYPEINFO_WITHPARENT(v3d::physics::VPhysicManagerPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICMANAGER_2006_02_15_H

