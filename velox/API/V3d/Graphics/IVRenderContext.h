/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVRENDERCONTEXT_H
#define V3D_IVRENDERCONTEXT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>
#include <V3d/Graphics/IVRenderContext.h>
#include <v3d/Graphics/VDisplaySettings.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A rendering context. Used internally by the graphics device to enable
 * it's associated opengl context. Abstracts platform specific ways to switch
 * the rendering context (multiple windows, pbuffers, etc.)
 *
 * @author lars
 */
class IVRenderContext
{
public:

	IVRenderContext() {};
	virtual ~IVRenderContext() {};

	/** Make the rendering Context active */
	virtual void MakeCurrent() = 0;

	/** Swap back and front buffer */
	virtual void SwapBuffers() = 0;

	/** Gets the Display Settings */
	virtual VDisplaySettings* GetDisplaySettings() = 0;

	/** Create a Offscreen Context */
	virtual IVRenderContext* CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
V3D_TYPEINFO(v3d::graphics::IVRenderContext);

#endif //V3D_IVRENDERCONTEXT_H
