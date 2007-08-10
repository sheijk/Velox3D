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

#include <V3d/Math/Numerics.h>
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
	m_fSize = 1.0f;
}

/**
 * d'tor
 */
VShowSelectionPart::~VShowSelectionPart()
{
}

//vuint counter = 0;

void VShowSelectionPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	glColor4f( m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha );

	switch( m_EditMode )
	{
	case EMMove:
		DrawMoveMode();
		break;
	case EMRotate:
		DrawRotateMode();
		break;
	case EMScale:
		DrawScaleMode();
		break;
	}

	//if( ++counter > 60 )
	//{
		//m_EditMode = EditMode( (int(m_EditMode) + 1) % 3 );
		//counter = 0;
	//}
}

namespace
{
	void SendCircleStrip(vfloat32 radius, vfloat32 bottom, vfloat32 top, vuint sectors)
	{
		const vfloat32 dangle = 2.0f * math::Pi() / vfloat32(sectors);

		for( vfloat32 angle = 0.0f; angle < 2.0f * math::Pi() + dangle; angle += dangle )
		{
			glVertex3f( radius * sin(-angle), radius * cos(angle), top );
			glVertex3f( radius * sin(-angle), radius * cos(angle), bottom );
		}
	}

	void DrawPipe(vfloat32 radius, vfloat32 length, vuint sectors, vuint slices)
	{
		glBegin( GL_TRIANGLE_STRIP );

		const vfloat32 dy = length / vfloat32(slices);
		const vfloat32 dangle = 2.0f * math::Pi() / vfloat32(sectors);

		for( vfloat32 y = 0.0f; y < length; y += dy )
		{
			SendCircleStrip(radius, y, y + dy, sectors);
		}

		glEnd();

		glBegin( GL_TRIANGLE_FAN );
		glVertex3f( 0.0f, 0.0f, length * 1.2f );
		for( vfloat32 angle = 0.0f; angle < 2.0f * math::Pi() + dangle; angle += dangle )
		{
			glVertex3f( radius * sin(-angle), radius * cos(angle), length );
		}
		glEnd();
	}
}

void VShowSelectionPart::DrawMoveMode() const
{
	const vuint detail = 6;
	const vfloat32 radius = 1.0f;
	const vfloat32 length = 5.0f;

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glColor3f( 0.f, 0.f, 1.f );
	DrawPipe( radius, length, detail, 10 );

	glRotatef( -90.0f, 1.f, 0.f, 0.f );
	glColor3f( 0.f, 1.f, 0.f );
	DrawPipe( radius, length, detail, 10 );

	glRotatef( 90.f, 0.f, 1.f, 0.f );
	glColor3f( 1.f, 0.f, 0.f );
	DrawPipe( radius, length, detail, 10 );

	glPopMatrix();
}

void VShowSelectionPart::DrawRotateMode() const
{
	const vfloat32 radius = 4.0f;
	const vfloat32 width = 0.5f;
	const vuint detail = 20;

	glPushAttrib( GL_CULL_FACE );
	glDisable( GL_CULL_FACE );

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glColor3f( .0f, .0f, 1.f );
	glBegin( GL_TRIANGLE_STRIP );
	SendCircleStrip( radius, -width, width, detail );
	glEnd();

	glColor3f( .0f, 1.f, 0.f );
	glRotatef( -90.f, 1.f, 0.f, 0.f );
	glBegin( GL_TRIANGLE_STRIP );
	SendCircleStrip( radius, -width, width, detail );
	glEnd();

	glColor3f( 1.f, 0.f, 0.f );
	glRotatef( 90.f, 0.f, 1.f, 0.f );
	glBegin( GL_TRIANGLE_STRIP );
	SendCircleStrip( radius, -width, width, detail );
	glEnd();

	glPopMatrix();

	glPopAttrib();
}

void DrawLineFromOrigin(vfloat32 x, vfloat32 y, vfloat32 z)
{
	glBegin( GL_LINES );
	glVertex3f( 0.f, 0.f, 0.f );
	glVertex3f( x, y, z );
	glEnd();
}

void VShowSelectionPart::DrawScaleMode() const
{
	const vfloat32 cubeSize = 1.0f;
	const vfloat32 lineLength = 2.0f;

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glColor3f( 1.f, 0.f, 0.f );
	DrawLineFromOrigin( lineLength, 0.f, 0.f );
	glTranslatef( lineLength, 0.f, 0.f );
	glutSolidCube( cubeSize );
	glTranslatef( -lineLength, 0.f, 0.f );

	glColor3f( 0.f, 1.f, 0.f );
	DrawLineFromOrigin( 0.f, lineLength, 0.f );
	glTranslatef( 0.f, lineLength, 0.f );
	glutSolidCube( cubeSize );
	glTranslatef( 0.f, -lineLength, 0.f );

	glColor3f( 0.f, 0.f, 1.f );
	DrawLineFromOrigin( 0.f, 0.f, lineLength );
	glTranslatef( 0.f, 0.f, lineLength );
	glutSolidCube( cubeSize );
	glTranslatef( 0.f, 0.f, -lineLength );

	glPopMatrix();
}

void VShowSelectionPart::OnActivate()
{
	VMeshPartBase::OnActivate();
}

messaging::VMessageInterpreter* VShowSelectionPart::GetMessageInterpreterForClass()
{
	static messaging::VMessageInterpreter interpreter;
	return &interpreter;
}

void VShowSelectionPart::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddMemberOption( "color", this, &m_Color );
	interpreter.AddAccessorOption<VShowSelectionPart, std::string>( "mode", 
		&VShowSelectionPart::GetEditModeName, 
		&VShowSelectionPart::SetEditMode );
}

VShowSelectionPart::EditMode VShowSelectionPart::GetEditMode() const
{
	return m_EditMode;
}

void VShowSelectionPart::SetEditMode(EditMode newMode)
{
	m_EditMode = newMode;
}

std::string VShowSelectionPart::GetEditModeName() const
{
	switch( m_EditMode )
	{
	case EMMove: return "EMMove";
	case EMRotate: return "EMRotate";
	case EMScale: return "EMScale";
	default: return "invalid";
	}
}

void VShowSelectionPart::SetEditMode(const std::string& modeName)
{
	if( modeName == "EMMove" )
		m_EditMode = EMMove;
	else if( modeName == "EMRotate" )
		m_EditMode = EMRotate;
	else
		m_EditMode = EMScale;
}

V3D_REGISTER_PART_PARSER(VShowSelectionPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

