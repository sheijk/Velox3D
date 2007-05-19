/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Utils/VCameraPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace entity;

/**
 * standard c'tor
 */
VCameraPart::VCameraPart() :
	m_pRigidBodyPart(VPartDependency::Neighbour, RegisterTo()),
	m_pUpdateManager(VPartDependency::Ancestor, RegisterTo()),
	m_pShooting(VPartDependency::Ancestor, RegisterTo())
{
	m_pCamera.Assign(new graphics::VCamera());
}

/**
 * d'tor
 */
VCameraPart::~VCameraPart()
{
}

//void VCameraPart::SetCamera(VSharedPtr<graphics::IVCamera> in_pCamera)
//{
//	m_pCamera = in_pCamera;
//}

void VCameraPart::OnActivate()
{
	m_pShooting->Register(m_pCamera.Get());
	//m_pShooting->SetCamera(m_pCamera.Get());
	m_pUpdateManager->Register(this);
}

void VCameraPart::OnDeactivate()
{
	m_pShooting->Unregister(m_pCamera.Get());
	//m_pShooting->SetCamera(0);
	m_pUpdateManager->Unregister(this);
}

void VCameraPart::Update(vfloat32 in_fSeconds)
{
	if( m_pCamera.Get() != 0 && m_pRigidBodyPart.Get() != 0 )
	{
		m_pCamera->SetTransform(m_pRigidBodyPart->GetTransform());
	}
}

V3D_REGISTER_PART_PARSER(VCameraPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------

