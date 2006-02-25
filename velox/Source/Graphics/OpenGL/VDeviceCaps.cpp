#include <V3d/Graphics/VDeviceCaps.h>
//-----------------------------------------------------------------------------
#include <V3d/OpenGL.h>
#include <V3d/Core.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VDeviceCaps::VDeviceCaps()
{
	maxTextures = 0;
	supportsGLSL = false;
	supportsFBO = false;
}

void VDeviceCaps::GatherInfoFromCurrentContext()
{
	GLint textureUnits = 0;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &textureUnits);
	maxTextures = textureUnits;

	supportsGLSL = GLEW_ARB_fragment_program;
	supportsFBO = GLEW_EXT_framebuffer_object;
}

void VDeviceCaps::PrintInfo() const
{
	vout << "OpenGL Device capabilities:\n";
	vout << "Texture units: " << maxTextures << "\n";
	vout << "Supports GLSL: " << supportsGLSL << "\n";
	vout << "Supports FBO:  " << supportsFBO << "\n";
	vout << vendl;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
