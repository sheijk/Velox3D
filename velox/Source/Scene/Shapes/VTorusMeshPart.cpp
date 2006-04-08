#include <V3d/Scene/Shapes/VTorusMeshPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVDevice.h>
#include <V3d/OpenGL.h>
#include <V3d/Math/Numerics.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <gl/glut.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;
using namespace math;

VTorusMeshPart::VTorusMeshPart() :
	m_Color(VColor4f(1, 1, 1)),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_fHeight = 5.0f;
	m_fButtonRadius = 1.0f;
	m_fTopRadius = 1.0f;
	m_iSlices = 15;
	m_iStacks = 15;
}

VTorusMeshPart::VTorusMeshPart(const VColor4f& in_Color) : 
	m_Color(in_Color),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
}

VTorusMeshPart::VTorusMeshPart(
				  vfloat32 in_fTopRadius,
				  vfloat32 in_fButtonRadius,
				  vfloat32 in_fHeight,
				  int in_iSlices,
				  int in_iStacks) : m_Color((VColor4f(1,1,1,1))),
				  VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_fTopRadius = in_fTopRadius;
	m_fButtonRadius = in_fButtonRadius;
	m_fHeight = in_fHeight;
	m_iSlices = in_iSlices;
	m_iStacks = in_iStacks;
}

void VTorusMeshPart::SetColor(const VColor4f& in_Color)
{
	m_Color = in_Color;
}

void VTorusMeshPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor4f(m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);
	glutSolidTorus(m_fButtonRadius, m_fTopRadius, m_iSlices, m_iStacks);
	glPopMatrix();
}

void VTorusMeshPart::sendCircleVertices(vfloat32 z1)
{
	sendCircleVertices(z1, z1, false);
}

void VTorusMeshPart::sendCircleVertices(vfloat32 z1, vfloat32 z2, bool normals)
{
	for(vfloat32 angleDeg = 0; angleDeg <= 360.0f; angleDeg += 36.0f)
	{
		if( normals )
		{
			glNormal3f(sin(DegreeToRadian(angleDeg)), cos(DegreeToRadian(angleDeg)), 0);
		}

		glVertex3f(sin(DegreeToRadian(angleDeg)), cos(DegreeToRadian(angleDeg)), z1);

		if( z1 != z2 )
		{
			glVertex3f(sin(DegreeToRadian(angleDeg)), cos(DegreeToRadian(angleDeg)), z2);
		}
	}
}

namespace {
	entity::VPartParser<VTorusMeshPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------