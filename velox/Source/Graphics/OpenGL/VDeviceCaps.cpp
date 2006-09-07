/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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

