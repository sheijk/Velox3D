#include <V3d/Scene/Shapes/VArrowMeshPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Graphics/IVDevice.h>
#include <V3d/OpenGL.h>
#include <V3d/Math/Numerics.h>

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;
using namespace math;

VArrowMeshPart::VArrowMeshPart() :
	m_Color(VColor4f(1, 1, 1)),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
}

VArrowMeshPart::VArrowMeshPart(const VColor4f& in_Color) : 
	m_Color(in_Color),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
}

void VArrowMeshPart::SetColor(const VColor4f& in_Color)
{
	m_Color = in_Color;
}

void VArrowMeshPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glColor4f(m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, -1);
	sendCircleVertices(0);        
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	sendCircleVertices(0);        
	glEnd();

	glScalef(.5f, .5f, 1);

	glBegin(GL_TRIANGLE_STRIP);
	sendCircleVertices(0, 1);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 1);
	sendCircleVertices(1);
	glEnd();

	glPopMatrix();
}

void VArrowMeshPart::sendCircleVertices(vfloat32 z1)
{
	sendCircleVertices(z1, z1);
}

void VArrowMeshPart::sendCircleVertices(vfloat32 z1, vfloat32 z2)
{
	for(vfloat32 angleDeg = 0; angleDeg <= 360.0f; angleDeg += 36.0f)
	{
		glVertex3f(sin(DegreeToRadian(angleDeg)), cos(DegreeToRadian(angleDeg)), z1);

		if( z1 != z2 )
			glVertex3f(sin(DegreeToRadian(angleDeg)), cos(DegreeToRadian(angleDeg)), z2);
	}
}

namespace {
	entity::VPartParser<VArrowMeshPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
