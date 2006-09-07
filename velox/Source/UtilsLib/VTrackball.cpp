/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Utils/VTrackball.h>
//-----------------------------------------------------------------------------
#include <V3d/Math.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::math;

VTrackball::VTrackball()
{
	m_fAltitudeAngle = 0;
	m_fDirectionAngle = 0;
	m_fDistance = 1.0f;
}

VRBTransform VTrackball::GetTransform()
{
	return m_Transform;
}

VVector3f VTrackball::GetViewPoint() const
{
	return m_Transform.GetPosition();
}

VVector3f VTrackball::GetUpVector() const
{
	return m_Transform.GetYAxis();
}

void VTrackball::RecalculateTransform()
{
	VQuatf dirRot = QuatFromAxisAngle<vfloat32>(VVector3f(0, 1, 0), m_fDirectionAngle);
	VQuatf heightRot = QuatFromAxisAngle<vfloat32>(VVector3f(1, 0, 0), m_fAltitudeAngle);
	VQuatf rotation = heightRot * dirRot;

	VVector3f viewPoint = VVector3f(0, 0, m_fDistance) * rotation;
	VVector3f up = VVector3f(0, 1, 0) * rotation;

	m_Transform.SetLookAt(viewPoint + m_Center, m_Center, up);
}

vfloat32 VTrackball::GetAltitudeAngle() const 
{
	return m_fAltitudeAngle;
}

void VTrackball::SetAltitudeAngle(vfloat32 in_AltitudeAngle) 
{ 
	m_fAltitudeAngle = Clamp(in_AltitudeAngle, -90.0f, 90.0f);
}

vfloat32 VTrackball::GetDirectionAngle() const
{
	return m_fDirectionAngle;
}

void VTrackball::SetDirectionAngle(vfloat32 in_DirectionAngle) 
{ 
	m_fDirectionAngle = fmod(in_DirectionAngle, 360.0f);
}

vfloat32 VTrackball::GetDistance() const 
{
	return m_fDistance;
}

void VTrackball::SetDistance(vfloat32 in_fDistance) 
{ 
	m_fDistance = std::max(0.01f, in_fDistance);
}

VVector3f VTrackball::GetCenter() const 
{
	return m_Center;
}

void VTrackball::SetCenter(const VVector3f& in_Center) 
{
	m_Center = in_Center;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------

