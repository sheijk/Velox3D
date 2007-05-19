/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Physics/VCollisionPart.h>
//-----------------------------------------------------------------------------	
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/Physics/VPhysicManagerPart.h>
#include <V3d/Physics/Bounding/IVBoundingVolumePart.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;

VCollisionPart::VCollisionPart() : 
	m_pVolumePart(entity::VPartDependency::Neighbour, RegisterTo()),
	m_pRigidBodyPart(entity::VPartDependency::Neighbour, RegisterTo()),
	m_pPhysicManagerPart(entity::VPartDependency::Ancestor, RegisterTo()),
	m_pUpdateManager(VPartDependency::Ancestor, RegisterTo())
{
	m_pGeometry.Assign(0);
	m_bActive = false;
}

void VCollisionPart::OnActivate()
{
	if( m_pVolumePart.Get() == 0 )
		V3D_THROW(entity::VMissingPartException, "missing part volume part 'data'");
	if( m_pPhysicManagerPart.Get() == 0)
		V3D_THROW(entity::VMissingPartException, "missing part physic manager 'data'");

	if( !m_bActive )
	{
		Create();
		m_pUpdateManager->Register(this);
	}
}

void VCollisionPart::OnDeactivate()
{
	m_bActive = false;
	m_pGeometry->Destroy();
	m_pGeometry.Release();
	m_pUpdateManager->Unregister(this);
}

void VCollisionPart::Create()
{
	m_pGeometry = m_pPhysicManagerPart->GetPhysicManager()->CreateGeom(m_pVolumePart.Get());
	m_bActive = true;
}

void VCollisionPart::OnMessage(
							   const messaging::VMessage& in_Message,
							   messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer != 0 )
		{
			in_pAnswer->AddProperty("Active", m_bActive);
		}
	}
}

void VCollisionPart::Update(vfloat32 in_fSeconds)
{
	if(m_pRigidBodyPart.Get())
	{
		//look if the position has been modified since our last visit
		if (m_Position != m_pRigidBodyPart->GetPosition())
		{
			m_pGeometry->SetPosition(m_pRigidBodyPart->GetPosition());
			m_Position = m_pRigidBodyPart->GetPosition();

			//todo orientation
		}
	}
}

V3D_REGISTER_PART_PARSER(VCollisionPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------

