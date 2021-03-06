/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCIRCLEMOVERPART_2006_01_30_H
#define V3D_VCIRCLEMOVERPART_2006_01_30_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Entity/IVPart.h>
#include <V3d/Entity/VUpdateablePart.h>
#include <V3d/Entity/VRigidBodyPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VCircleMoverPart : public entity::IVUpdateablePart
{
public:
	VCircleMoverPart();

	void Update(vfloat32 in_fSeconds);

	vfloat32 GetRadius() const { return m_fRadius; }
	void SetRadius(const vfloat32& in_Value) { m_fRadius = in_Value; }
	math::VVector3f GetCenter() const { return m_Center; }
	void SetCenter(const math::VVector3f& in_Value) { m_Center = in_Value; }
	vfloat32 GetSpeed() const { return m_fSpeed; }
	void SetSpeed(const vfloat32& in_Value) { m_fSpeed = in_Value; }
	vfloat32 GetAngle() const { return m_fAngle; }
	void SetAngle(const vfloat32& in_Value) { m_fAngle = in_Value; }

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual void OnActivate();
	virtual void OnDeactivate();

private:
	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	entity::VNodeConnection<entity::VRigidBodyPart> m_pRigidBody;
	entity::VNodeConnection<entity::VUpdateManagerPart> m_pUpdateManager;

	vfloat32 m_fRadius;
	math::VVector3f m_Center;
	vfloat32 m_fSpeed;

	vfloat32 m_fAngle;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
V3D_TYPEINFO_WITHPARENT(v3d::utils::VCircleMoverPart, v3d::entity::IVUpdateablePart);
//-----------------------------------------------------------------------------
#endif // V3D_VCIRCLEMOVERPART_2006_01_30_H

