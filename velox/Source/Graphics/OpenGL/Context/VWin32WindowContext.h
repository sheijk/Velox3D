/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VWIN32WINDOWCONTEXT_H
#define V3D_VWIN32WINDOWCONTEXT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VException.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/Graphics/GraphicsExceptions.h>
#include <V3d/Graphics/VDisplaySettings.h>
#include <V3d/Graphics/IVRenderContext.h>
#include "VPBufferWindowContext.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A rendering context. Used internally by the graphics device to enable
 * it's associated win32 opengl context.
 *
 * @author lars
 */
class VWin32WindowContext : public IVRenderContext
{
public:

	VWin32WindowContext(HWND in_hwnd = 0, const graphics::VDisplaySettings* in_pDisplaySettings = 0);
	virtual ~VWin32WindowContext();

	/** @see v3d::graphics::IVRenderContext::MakeCurrent */
	void MakeCurrent();

	/** @see v3d::graphics::IVRenderContext::SwapBuffers */
	void SwapBuffers();

	/** @see v3d::graphics::IVRenderContext::GetDisplaySettings */
	VDisplaySettings* GetDisplaySettings();

	/** @see v3d::graphics::IVRenderContext::CreateOffscreenContext */
	IVRenderContext* CreateOffscreenContext(const graphics::VDisplaySettings* in_pDisplaySettings);

	void ShareListsWith(VWin32WindowContext* other);
private:

	graphics::VDisplaySettings m_DisplaySettings;
	HDC                        m_DeviceContext;
	HGLRC                      m_RenderContext;
	HWND                       m_Handle;
	PIXELFORMATDESCRIPTOR      m_Pixelformat;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

#endif //V3D_VWIN32WINDOWCONTEXT_H
