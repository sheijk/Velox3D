/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTRACKBALLPART_2005_12_09_H
#define V3D_VTRACKBALLPART_2005_12_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Utils/VMouseTrackball.h>
#include <V3d/Entity/VUpdateablePart.h>
#include <V3d/Entity/VRigidBodyPart.h>
#include <V3d/Utils/VInputPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VTrackballPart : public entity::IVUpdateablePart
{
public:
	VTrackballPart();
	virtual ~VTrackballPart();

	virtual void Update(vfloat32 in_fSeconds);

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

	void SetTrackball(const VSharedPtr<VMouseTrackball>& in_Trackball);


	vfloat32 GetAltitudeAngle() const;
	void SetAltitudeAngle(const vfloat32& in_AltitudeAngle);

	vfloat32 GetDirectionAngle() const;
	void SetDirectionAngle(const vfloat32& in_DirectionAngle);

	vfloat32 GetDistance() const;
	void SetDistance(const vfloat32& in_Distance);

	math::VVector3f GetCenter() const;
	void SetCenter(const math::VVector3f& in_Center);
private:
	virtual void OnActivate();
	virtual void OnDeactivate();

	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	VSharedPtr<VMouseTrackball> m_pTrackball;
	vbool m_bCenterOnParent;

	entity::VNodeConnection<entity::VRigidBodyPart> m_pRigidBodyPart;
	entity::VNodeConnection<entity::VUpdateManagerPart> m_pUpdateManager;
	entity::VNodeConnection<utils::VInputPart> m_pInputPart;
	entity::VNodeConnection<entity::VRigidBodyPart> m_pParentRigidBodyPart;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils

V3D_TYPEINFO_WITHPARENT(v3d::utils::VTrackballPart, v3d::entity::IVUpdateablePart);
//-----------------------------------------------------------------------------
#endif // V3D_VTRACKBALLPART_2005_12_09_H

