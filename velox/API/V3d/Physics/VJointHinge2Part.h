/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
	~VJointHinge2Part();
	
	// IVPart derived
	void Activate();
	void Deactivate();
	
	//void RegisterBody(VBody* in_pAddress);
	//void UnregisterBody(VBody* in_pAddress);
	
	VJointHinge2& GetJointHinge2();

	static std::string GetDefaultId();

	virtual const VTypeInfo& GetTypeInfo() const 
	{ return GetCompileTimeTypeInfo(this); }

private:

	//void Create();
	void RegisterLink();

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
	std::string m_sBody1Name;
	std::string m_sBody2Name;

	std::string m_sName;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
V3D_TYPEINFO_WITHPARENT(v3d::physics::VJointHinge2Part, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif //V3D_VJOINTHINGE2PART_2006_05_05_H

