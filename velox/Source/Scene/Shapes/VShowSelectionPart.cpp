/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Scene/Shapes/VShowSelectionPart.h>
//-----------------------------------------------------------------------------

#include <V3d/OpenGL.h>
#include <GL/glut.h>

#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Messaging/VMessageInterpreter.h>
#include <V3d/Graphics/Geometry/Conversions.h>

//#include <V3d/Tags/VTagRegistry.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VShowSelectionPart::VShowSelectionPart()
{
	m_Color = graphics::VColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
}

/**
 * d'tor
 */
VShowSelectionPart::~VShowSelectionPart()
{
}

void VShowSelectionPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	glColor4f( m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha );
	glutWireSphere( 1.0, 10, 10 );
}

void VShowSelectionPart::OnActivate()
{
}

messaging::VMessageInterpreter* VShowSelectionPart::GetMessageInterpreterForClass()
{
	static messaging::VMessageInterpreter interpreter;
	return &interpreter;
}

void VShowSelectionPart::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddMemberOption( "color", this, &m_Color );
}

V3D_REGISTER_PART_PARSER(VShowSelectionPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

