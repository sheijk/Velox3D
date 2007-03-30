/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Shapes/VOrientationGridPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Graphics/IVDevice.h>
#include <V3d/OpenGL.h>

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VOrientationGridPart::VOrientationGridPart() : 
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
}

void VOrientationGridPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	const int stripeCount = 10;
	const float stripeLength = 10.0f;
	const float stripeDistance = .1f;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glPushAttrib(GL_LINE_WIDTH);
	glLineWidth(.2f);

	glScalef(stripeLength, stripeLength, stripeLength);

	// show z = 0 plane
	glColor3f(.0f, .0f, 1.0f);
	SendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
	glRotatef(90.0f, .0f, .0f, 1.0f);
	SendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);

	// show y = 0 plane
	glColor3f(.0f, 1.0f, .0f);
	glRotatef(90, 0, 1, 0);
	SendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
	glRotatef(90.0f, .0f, .0f, 1.0f);
	SendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);

	// show x = 0 plane
	glColor3f(1.0f, .0f, .0f);
	glRotatef(90, 0, 1, 0);
	SendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
	glRotatef(90.0f, .0f, .0f, 1.0f);
	SendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);

	glPushAttrib(GL_POINT_SIZE);
	glPointSize(3.0f);

	glBegin(GL_POINTS);
	for(int i = -stripeCount; i < stripeCount; ++i) {
		glColor3f(0, 1, 1);
		glVertex3f(i * stripeDistance, 0, 0);

		glColor3f(1, 0, 1);
		glVertex3f(0, i * stripeDistance, 0);

		glColor3f(1, 1, 0);
		glVertex3f(0, 0, i * stripeDistance);
	}
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	glPopAttrib();

	glPopAttrib();
	glPopMatrix();
}

void VOrientationGridPart::SendParallelLineVertices(
	int min, int max, float distance) const
{
	glBegin(GL_LINES);
	for(int i = min; i < max; ++i) {
		glVertex2f(-1.0f, i * distance);
		glVertex2f(1.0f, i * distance);
	}
	glEnd();
}

V3D_REGISTER_PART_PARSER(VOrientationGridPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

