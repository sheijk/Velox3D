/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Scene/Shapes/VFrustumVisPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Math/VVector.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/OpenGL.h>
#include <V3d/Messaging/VMessageInterpreter.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VFrustumVisPart::VFrustumVisPart()
{
	m_fFOV = 90.0f;
	m_fZNear = 1.0f;
	m_fZFar = 10.0f;
	m_fLineDist = 1.0f;
	m_fAspectRatio = 1.0f;
	m_fXYOffset = 0.0f;
}

/**
 * d'tor
 */
VFrustumVisPart::~VFrustumVisPart()
{
}

messaging::VMessageInterpreter* VFrustumVisPart::GetMessageInterpreterForClass()
{
	static messaging::VMessageInterpreter interpreter;

	return &interpreter;
}

void VFrustumVisPart::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddMemberOption("fov", this, &m_fFOV);
	interpreter.AddMemberOption("znear", this, &m_fZNear);
	interpreter.AddMemberOption("zfar", this, &m_fZFar);
	interpreter.AddMemberOption("linedist", this, &m_fLineDist);
	interpreter.AddMemberOption("aspect-ratio", this, &m_fAspectRatio);
	interpreter.AddMemberOption("xy-offset", this, &m_fXYOffset);

	VMeshPartBase::SetupProperties( interpreter );
}

//void VFrustumVisPart::OnMessage(
//	const messaging::VMessage& in_Message, 
//	messaging::VMessage* in_pAnswer)
//{
//	using namespace messaging;
//
//	static VMessageInterpreter interpreter;
//	if( ! interpreter.IsInitialized() )
//	{
//		interpreter.SetInitialized(true);
//
//		interpreter.AddMemberOption("fov", this, &m_fFOV);
//		interpreter.AddMemberOption("znear", this, &m_fZNear);
//		interpreter.AddMemberOption("zfar", this, &m_fZFar);
//		interpreter.AddMemberOption("linedist", this, &m_fLineDist);
//		interpreter.AddMemberOption("aspect-ratio", this, &m_fAspectRatio);
//		interpreter.AddMemberOption("xy-offset", this, &m_fXYOffset);
//	}
//
//	InterpreteMessage(interpreter, in_Message, in_pAnswer);
//}

namespace {
	void glVertex(const math::VVector3f& pos)
	{
		glVertex3f(pos.GetX(), pos.GetY(), pos.GetZ());
	}

	void Quad(
		const math::VVector3f& a, 
		const math::VVector3f& b,
		const math::VVector3f& c,
		const math::VVector3f& d)
	{
		glVertex(a); glVertex(b);
		glVertex(b); glVertex(c);
		glVertex(c); glVertex(d);
		glVertex(d); glVertex(a);
	}
}

vfloat32 VFrustumVisPart::CalcD() const
{
	const vfloat32 halfAngle = m_fFOV / 2.0f;
	const vfloat32 sina = sin(math::DegreeToRadian(halfAngle));
	const vfloat32 cosa = cos(math::DegreeToRadian(halfAngle));

	if( cosa > 0.0f )
		return sina / cosa;
	else
		return 0.0;
}

void VFrustumVisPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	using namespace math;

	const vfloat32 d = CalcD();
	const vfloat32 dnear = d * m_fZNear;
	const vfloat32 dfar = d * m_fZFar;

	// n - near, f - far, l - left, r - right, l - lower, u - upper
	VVector3f nll(-m_fXYOffset - dnear * m_fAspectRatio, -m_fXYOffset - dnear, - m_fZNear);
	VVector3f nlu(-m_fXYOffset - dnear * m_fAspectRatio, m_fXYOffset + dnear, - m_fZNear);
	VVector3f nru(m_fXYOffset + dnear * m_fAspectRatio,  m_fXYOffset + dnear, - m_fZNear);
	VVector3f nrl(m_fXYOffset + dnear * m_fAspectRatio,  -m_fXYOffset - dnear, - m_fZNear);

	VVector3f fll(-m_fXYOffset - dfar * m_fAspectRatio, -m_fXYOffset - dfar, - m_fZFar);
	VVector3f flu(-m_fXYOffset - dfar * m_fAspectRatio, m_fXYOffset + dfar, - m_fZFar);
	VVector3f fru(m_fXYOffset + dfar * m_fAspectRatio, m_fXYOffset + dfar, - m_fZFar);
	VVector3f frl(m_fXYOffset + dfar * m_fAspectRatio, -m_fXYOffset - dfar, - m_fZFar);

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	Quad(nll, nlu, nru, nrl);

	vfloat32 c = 0.0f;
	const vfloat32 steps = (m_fZFar - m_fZNear) / m_fLineDist;
	const vfloat32 dc = 1.0f / steps;

	if( m_fLineDist > 0.0f )
	for(float z = m_fZNear; z < m_fZFar; z += m_fLineDist)
	{
		glColor3f(1.0f - c, c, 0.0f);

		VVector3f ll(-m_fXYOffset - d * z * m_fAspectRatio, -m_fXYOffset - d * z, - z);
		VVector3f lu(-m_fXYOffset - d * z * m_fAspectRatio, m_fXYOffset + d * z, - z);
		VVector3f ru(m_fXYOffset + d * z * m_fAspectRatio, m_fXYOffset + d * z, - z);
		VVector3f rl(m_fXYOffset + d * z * m_fAspectRatio, -m_fXYOffset - d * z, - z);

		Quad(ll, lu, ru, rl);

		c += dc;
	}

	glColor3f(0.0f, 1.0f, 0.0f);
	Quad(fll, flu, fru, frl);
	glEnd();
}

V3D_REGISTER_PART_PARSER(VFrustumVisPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

