#ifndef V3D_VPBUFFERWINDOWCONTEXT_H
#define V3D_VPBUFFERWINDOWCONTEXT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>
#include <v3d/Core/VIOStream.h>
#include <v3d/Graphics/GraphicsExceptions.h>
#include <v3d/Graphics/VDisplaySettings.h>
#include <V3d/Graphics/IVDevice.h>
#include <v3d/Graphics/IVRenderContext.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <V3d/OpenGL.h>

#include "RenderTexture.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A rendering context. Used internally by the graphics device to enable
 * it's associated pixel buffer opengl context. 
 *
 * @author lars
 */
class VPBufferWindowContext : public IVRenderContext
{
public:

	VPBufferWindowContext(const graphics::VDisplaySettings* in_pDisplaySettings = 0);
	virtual ~VPBufferWindowContext();

	/** @see v3d::graphics::IVRenderContext::MakeCurrent */
	void MakeCurrent();

	/** @see v3d::graphics::IVRenderContext::SwapBuffers */
	void SwapBuffers();

	void BindTexture();
	void UnbindTexture();
	
	/** @see v3d::graphics::IVRenderContext::GetDisplaySettings */
	VDisplaySettings* GetDisplaySettings();

	/** @see v3d::graphics::IVRenderContext::CreateOffscreenContext */
	IVRenderContext* CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings);

private:
	RenderTexture m_RenderTexture;
	VDisplaySettings m_DisplaySettings;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::graphics::VPBufferWindowContext, v3d::graphics::IVRenderContext);

#endif //V3D_VPBUFFERWINDOWCONTEXT_H