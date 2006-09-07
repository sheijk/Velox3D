/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDEVICECAPS_2006_02_15_H
#define V3D_VDEVICECAPS_2006_02_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Provide information about the capabilities of a graphics device (it's
 * underlying opengl context
 *
 * @author sheijk
 */
struct VDeviceCaps
{
	/** number of texture units */
	vuint maxTextures;

	/** supports opengl shading language */
	vbool supportsGLSL;
	/** GL_EXT_FRAMEBUFFER_OBJECT support */
	vbool supportsFBO;

	//vbool isAccelerated;

	VDeviceCaps();

	/** Gathers the infos from the currently active opengl context */
	void GatherInfoFromCurrentContext();

	/** prints all infos to vout */
	void PrintInfo() const;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VDEVICECAPS_2006_02_15_H

