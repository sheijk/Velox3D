/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Shapes/VCylinderMeshPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVDevice.h>
#include <V3d/OpenGL.h>
#include <V3d/Math/Numerics.h>
#include <V3d/Graphics/Geometry/Conversions.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;
using namespace math;

VCylinderMeshPart::VCylinderMeshPart() :
	m_Color(VColor4f(1, 1, 1)),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_fButtonRadius = 1.0f;
	m_fTopRadius = 1.0f;
	m_iSlices = 10;
	m_iStacks = 10;
	m_fHeight = 1.0f;

	pGluObject = gluNewQuadric();
}

VCylinderMeshPart::VCylinderMeshPart(const VColor4f& in_Color) : 
	m_Color(in_Color),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
  m_fButtonRadius = 1.0f;
  m_fTopRadius = 1.0f;
  m_iSlices = 10;
  m_iStacks = 10;
  m_fHeight = 1.0;

  pGluObject = gluNewQuadric();
}

VCylinderMeshPart::VCylinderMeshPart(
				  vfloat32 in_fTopRadius,
				  vfloat32 in_fButtonRadius,
				  vfloat32 in_fHeight,
				  int in_iSlices,
				  int in_iStacks) : m_Color((VColor4f(1,1,1,1))),
				  VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_fTopRadius = in_fTopRadius;
	m_fButtonRadius = in_fButtonRadius;
	m_iSlices = in_iSlices;
	m_iStacks = in_iStacks;
	m_fHeight = in_fHeight;

	pGluObject = gluNewQuadric();
}

VCylinderMeshPart::~VCylinderMeshPart()
{
  gluDeleteQuadric(pGluObject);
}

void VCylinderMeshPart::SetColor(const VColor4f& in_Color)
{
	m_Color = in_Color;
}

void VCylinderMeshPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor4f(m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);
	gluCylinder(pGluObject, m_fButtonRadius, m_fTopRadius, m_fHeight, m_iSlices, m_iStacks);
	glPopMatrix();
}

void v3d::scene::VCylinderMeshPart::OnMessage(
	const messaging::VMessage& in_Message,  
	messaging::VMessage* in_pAnswer) 
{
	using namespace messaging;

	static VMessageInterpreter interpreter;

	if( !interpreter.IsInitialized() )
	{
		interpreter.SetInitialized(true);

		interpreter.AddMemberOption("color", this, &m_Color);
		interpreter.AddMemberOption("top-radius", this, &m_fTopRadius);
		interpreter.AddMemberOption("bottom-radius", this, &m_fButtonRadius);
		interpreter.AddMemberOption("slices", this, &m_iSlices);
		interpreter.AddMemberOption("stacks", this, &m_iStacks);
		interpreter.AddMemberOption("height", this, &m_fHeight);
	}

	InterpreteMessage(interpreter, in_Message, in_pAnswer);
}

V3D_REGISTER_PART_PARSER(VCylinderMeshPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene

//-----------------------------------------------------------------------------

