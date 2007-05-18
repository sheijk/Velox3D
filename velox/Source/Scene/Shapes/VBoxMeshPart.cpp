/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Shapes/VBoxMeshPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVDevice.h>
#include <V3d/OpenGL.h>
#include <V3d/Math/Numerics.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;
using namespace math;

VBoxMeshPart::VBoxMeshPart() :
	m_Color(VColor4f(1, 1, 1)),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
}

VBoxMeshPart::VBoxMeshPart(const VColor4f& in_Color) : 
	m_Color(in_Color),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_bWireFrame = false;
}

VBoxMeshPart::VBoxMeshPart(const math::VBoundingBox& in_BoundingBox) :
	m_Color(VColor4f(1,1,1)),
		VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_BoundingBox = in_BoundingBox;
}

VBoxMeshPart::VBoxMeshPart(
						   const math::VBoundingBox& in_BoundingBox,
						   const graphics::VColor4f& in_Color) :
	m_Color(in_Color),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_BoundingBox = in_BoundingBox;
}

void VBoxMeshPart::SetColor(const VColor4f& in_Color)
{
	m_Color = in_Color;
}

void VBoxMeshPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	GLboolean cullfaceEnable = glIsEnabled(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	if(m_bWireFrame)
	{
		
	}
	glBegin(GL_QUADS);
	glColor4f(m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);

	VVector3f length = m_BoundingBox.GetLength();
	

	glVertex3f(
		- length.GetX() / 2 ,
		- length.GetY() / 2,
		+ length.GetZ() / 2 
		);
	glNormal3i(0,0,1);
	glVertex3f(
		+ length.GetX() / 2,
		- length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(0,0,1);
	glVertex3f(
		+ length.GetX() / 2,
		+ length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(0,0,1);
	glVertex3f(
		- length.GetX() / 2,
		+ length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(0,0,1);
	//second one

	glVertex3f(
		- length.GetX()  / 2,
		- length.GetY()  /2,
		- length.GetZ() / 2);
	glNormal3i(0,0,-1);
	glVertex3f(
		+ length.GetX() / 2,
		- length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(0,0,-1);
	glVertex3f(
		+ length.GetX() / 2,
		+ length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(0,0,-1);
	glVertex3f(
		- length.GetX() / 2,
		+ length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(0,0,-1);


	//3
	glVertex3f(
		- length.GetX() / 2,
		+ length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(0,1,0);

	glVertex3f(
		+ length.GetX() / 2,
		+ length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(0,1,0);

	glVertex3f(
		+ length.GetX() / 2,
		+ length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(0,1,0);

	glVertex3f(
		- length.GetX() / 2,
		+ length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(0,1,0);

	//

	glVertex3f(
		- length.GetX() / 2,
		- length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(0,-1,0);

	glVertex3f(
		+ length.GetX() / 2,
		- length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(0,-1,0);

	glVertex3f(
		+ length.GetX() / 2,
		- length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(0,-1,0);

	glVertex3f(
		- length.GetX() / 2,
		- length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(0,-1,0);

	//
	glVertex3f(
		- length.GetX() / 2,
		- length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(-1,0,0);

	glVertex3f(
		- length.GetX() / 2,
		- length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(-1,0,0);

	glVertex3f(
		- length.GetX() / 2,
		+ length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(-1,0,0);

	glVertex3f(
		- length.GetX() / 2,
		+ length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(-1,0,0);

	//

	glVertex3f(
		+ length.GetX() / 2,
		- length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(1,0,0);

	glVertex3f(
		+ length.GetX() / 2,
		- length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(1,0,0);

	glVertex3f(
		+ length.GetX() / 2,
		+ length.GetY() / 2,
		- length.GetZ() / 2);
	glNormal3i(1,0,0);

	glVertex3f(
		+ length.GetX() / 2,
		+ length.GetY() / 2,
		+ length.GetZ() / 2);
	glNormal3i(1,0,0);

	glEnd();
	glPopAttrib();

	
	glPopMatrix();

	if( cullfaceEnable )
		glEnable(GL_CULL_FACE);
}

messaging::VMessageInterpreter* VBoxMeshPart::GetMessageInterpreterForClass()
{
	static messaging::VMessageInterpreter interpreter;

	return &interpreter;
}

math::VVector3f VBoxMeshPart::GetMinPoint() const
{
	return m_BoundingBox.GetMinPoint();
}

void VBoxMeshPart::SetMinPoint(const math::VVector3f& newPoint)
{
	m_BoundingBox.SetMinPoint( newPoint );
}

math::VVector3f VBoxMeshPart::GetMaxPoint() const
{
	return m_BoundingBox.GetMaxPoint();
}

void VBoxMeshPart::SetMaxPoint(const math::VVector3f& newPoint)
{
	m_BoundingBox.SetMaxPoint( newPoint );
}

void VBoxMeshPart::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	interpreter.AddAccessorOption<VBoxMeshPart, VVector3f>(
		"MinPoint",
		&VBoxMeshPart::GetMinPoint,
		&VBoxMeshPart::SetMinPoint);
	interpreter.AddAccessorOption<VBoxMeshPart, VVector3f>(
		"MaxPoint",
		&VBoxMeshPart::GetMaxPoint,
		&VBoxMeshPart::SetMaxPoint);

	VMeshPartBase::SetupProperties( interpreter );
}

//void VBoxMeshPart::OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
//{
//	using std::string;
//
//	if( ! in_Message.HasProperty("type") )
//		return;
//
//	const string request = in_Message.GetAs<string>("type");
//
//	if( request == "getSettings" )
//	{
//		if( in_pAnswer != 0 )
//		{
//			in_pAnswer->AddProperty("MinPoint", m_BoundingBox.GetMinPoint());
//			in_pAnswer->AddProperty("MaxPoint", m_BoundingBox.GetMaxPoint());
//			AddVariables(in_pAnswer);
//		}
//	}
//	else if( request == "update" )
//	{
//		const string name = in_Message.GetAs<string>("name");
//
//		if( name == "MinPoint" )
//		{
//			VVector3f pos = in_Message.GetAs<VVector3f>("value");
//
//			m_BoundingBox.SetMinPoint(pos);
//		}
//		if( name == "MaxPoint" )
//		{
//			VVector3f pos = in_Message.GetAs<VVector3f>("value");
//
//			m_BoundingBox.SetMaxPoint(pos);
//		}
//
//		ApplySetting(in_Message);
//	}
//}

V3D_REGISTER_PART_PARSER(VBoxMeshPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

