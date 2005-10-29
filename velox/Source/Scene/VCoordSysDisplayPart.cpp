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

VCoordSysDisplayPart::VCoordSysDisplayPart()
	: VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
}

void VCoordSysDisplayPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 0, 1);
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
