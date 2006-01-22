#include <V3d/Scene/Shapes/VCoordSysDisplayPart.h>
//-----------------------------------------------------------------------------

#include <V3d/OpenGL.h>
#include <V3d/Graphics/IVDevice.h>

#include <V3d/Entity/IVEntitySerializationService.h>

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VCoordSysDisplayPart::VCoordSysDisplayPart(vfloat32 in_fBrightness)
	: VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_XColor = graphics::VColor4f(in_fBrightness, 0, 0);
	m_YColor = graphics::VColor4f(0, in_fBrightness, 0);
	m_ZColor = graphics::VColor4f(0, 0, in_fBrightness);
}

namespace {
	void glColor(const graphics::VColor4f& in_Color)
	{
		glColor4f(in_Color.red, in_Color.green, in_Color.blue, in_Color.alpha);
	}
}

void VCoordSysDisplayPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	glBegin(GL_LINES);
	glColor(m_XColor);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor(m_YColor);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor(m_ZColor);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

namespace {
	entity::VPartParser<VCoordSysDisplayPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
