/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCAMERAPART_2005_12_09_H
#define V3D_VCAMERAPART_2005_12_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Entity/VRigidBodyPart.h>
#include <V3d/Graphics/Misc/VCamera.h>
#include <V3d/Scene/VSimpleShooting.h>
#include <V3d/Entity/VUpdateablePart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VCameraPart : public entity::VPartBaseAdapter<entity::IVUpdateablePart>
{
public:
	VCameraPart();
	virtual ~VCameraPart();

	//void SetCamera(VSharedPtr<graphics::IVCamera> in_pCamera);

	virtual void Update(vfloat32 in_fSeconds);

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	virtual void OnActivate();
	virtual void OnDeactivate();

	VSharedPtr<graphics::VCamera> m_pCamera;

	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBodyPart;
	entity::VPartConnection<entity::VUpdateManagerPart> m_pUpdateManager;
	entity::VPartConnection<scene::VSimpleShooting> m_pShooting;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils

V3D_TYPEINFO_WITHPARENT(v3d::utils::VCameraPart, v3d::entity::IVUpdateablePart);
//-----------------------------------------------------------------------------
#endif // V3D_VCAMERAPART_2005_12_09_H

