/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Entity/VSGAnimationPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

VSGAnimationPart::VSGAnimationPart() :
	m_pParent(VPartDependency::Ancestor, RegisterTo()),
	m_pSceneGraphPart(VPartDependency::Neighbour, RegisterTo())
{
	m_Position = VVector3f(0.0f, 0.0f, 0.0f);
	m_Rotate = VVector3f(0.0f, 0.0f, 0.0f);
	m_fRotateSpeed = 0.0f;
}

VSGAnimationPart::~VSGAnimationPart()
{
}

void VSGAnimationPart::SetPosition(VVector3f in_Position)
{
	m_Position = in_Position;
}

void VSGAnimationPart::SetRotateAxis(VVector3f in_Rotate)
{
	m_Rotate = in_Rotate;
}

void VSGAnimationPart::SetRotateSpeed(vfloat32 in_Speed)
{
	m_fRotateSpeed = in_Speed;
}

math::VRBTransform VSGAnimationPart::GetRelativeTransform() const
{
	return m_Transform;
}

void VSGAnimationPart::Update(vfloat32 in_Seconds)
{
	//calculate the rotation
	m_fAngle += m_fRotateSpeed * in_Seconds;
	VQuatf Quaternion = QuatFromAxisAngle(m_Rotate, m_fAngle);

	math::Rotate(m_Transform.GetXAxis(), Quaternion);
	math::Rotate(m_Transform.GetYAxis(), Quaternion);
	math::Rotate(m_Transform.GetZAxis(), Quaternion);

	//set the translate
	m_Transform.SetPosition(m_Position);

	m_pSceneGraphPart->SetRelativeTransform(m_Transform);
}

void VSGAnimationPart::OnActivate()
{
	if(m_pParent.IsConnected())
		m_pParent->Register(this);
}

void VSGAnimationPart::OnDeactivate()
{
	if(m_pParent.IsConnected())
		m_pParent->Unregister(this);
}

std::string VSGAnimationPart::GetDefaultId()
{
	return "sgap";
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
