/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Utils/VTrackballPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Input/IVInputManager.h>
#include <V3d/Messaging/VMessageInterpreter.h>

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
VTrackballPart::VTrackballPart() :
	m_pRigidBodyPart(VPartDependency::Neighbour, RegisterTo()),
	m_pUpdateManager(VPartDependency::Ancestor, RegisterTo()),
	m_pInputPart(VPartDependency::Ancestor, RegisterTo())
{
}

/**
 * d'tor
 */
VTrackballPart::~VTrackballPart()
{
}

void VTrackballPart::Activate()
{
	m_pUpdateManager->Register(this);

	using namespace input;

	IVInputManager* pInputManager = m_pInputPart->GetInputManager();
	if( pInputManager != 0 )
	{
		IVMouseDevice* pMouse = &pInputManager->GetStandardMouse();
		m_pTrackball.Assign(new VMouseTrackball(pMouse));
	}
}

void VTrackballPart::Deactivate()
{
	m_pUpdateManager->Unregister(this);
}

void VTrackballPart::Update(vfloat32 in_fSeconds)
{
	if( m_pTrackball.Get() != 0 && m_pRigidBodyPart.Get() != 0 )
	{
		m_pTrackball->Update(in_fSeconds);
		m_pRigidBodyPart->SetTransform(m_pTrackball->GetTransform());
	}
}

void VTrackballPart::SetTrackball(const VSharedPtr<VMouseTrackball>& in_Trackball)
{
	m_pTrackball = in_Trackball;
}

vfloat32 VTrackballPart::GetAltitudeAngle() const
{
	if( m_pTrackball != 0 )
		return m_pTrackball->GetAltitudeAngle();
	else
		return .0f;
}

void VTrackballPart::SetAltitudeAngle(const vfloat32& in_AltitudeAngle)
{
	if( m_pTrackball != 0 ) {
		m_pTrackball->SetAltitudeAngle(in_AltitudeAngle);
	}
}

vfloat32 VTrackballPart::GetDirectionAngle() const
{
	if( m_pTrackball != 0 )
		return m_pTrackball->GetDirectionAngle();
	else
		return .0f;
}

void VTrackballPart::SetDirectionAngle(const vfloat32& in_DirectionAngle)
{
	if( m_pTrackball != 0 )
		m_pTrackball->SetDirectionAngle(in_DirectionAngle);
}

vfloat32 VTrackballPart::GetDistance() const
{
	if( m_pTrackball != 0 )
		return m_pTrackball->GetDistance();
	else
		return .0f;
}

void VTrackballPart::SetDistance(const vfloat32& in_Distance)
{
	if( m_pTrackball != 0 )
		m_pTrackball->SetDistance(in_Distance);
}

math::VVector3f VTrackballPart::GetCenter() const
{
	if( m_pTrackball != 0 )
		return m_pTrackball->GetCenter();
	else
		return math::VVector3f(.0f, .0f, .0f);
}

void VTrackballPart::SetCenter(const math::VVector3f& in_Center)
{
	if( m_pTrackball != 0 )
		m_pTrackball->SetCenter(in_Center);
}

void VTrackballPart::OnMessage(
	const messaging::VMessage& in_Message, 
	messaging::VMessage* in_pAnswer)
{
	static messaging::VMessageInterpreter interpreter;
	if( !interpreter.IsInitialized() )
	{
		interpreter.SetInitialized(true);

		interpreter.AddAccessorOption<VTrackballPart, vfloat32>(
			"distance",
			&VTrackballPart::GetDistance, 
			&VTrackballPart::SetDistance);
		interpreter.AddAccessorOption<VTrackballPart, vfloat32>(
			"direction-angle",
			&VTrackballPart::GetDirectionAngle,
			&VTrackballPart::SetDirectionAngle);
		interpreter.AddAccessorOption<VTrackballPart, vfloat32>(
			"altitude-angle",
			&VTrackballPart::GetAltitudeAngle,
			&VTrackballPart::SetAltitudeAngle);
		interpreter.AddAccessorOption<VTrackballPart, math::VVector3f>(
			"center",
			&VTrackballPart::GetCenter,
			&VTrackballPart::SetCenter);
	}

	interpreter.HandleMessage(this, in_Message, in_pAnswer);
}

V3D_REGISTER_PART_PARSER(VTrackballPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------

