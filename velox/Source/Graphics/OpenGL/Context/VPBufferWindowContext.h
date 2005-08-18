#ifndef V3D_VPBUFFERWINDOWCONTEXT_H
#define V3D_VPBUFFERWINDOWCONTEXT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>
#include <v3d/Core/VIOStream.h>
#include <v3d/Graphics/GraphicsExceptions.h>
#include <v3d/Graphics/VDisplaySettings.h>
#include <v3d/Graphics/IVRenderContext.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <V3d/OpenGL.h>

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

	VPBufferWindowContext(HDC in_DeviceContext, const graphics::VDisplaySettings* in_pDisplaySettings = 0);
	virtual ~VPBufferWindowContext();

	/**
	 * Get the Pixel Buffer Object
	*/
	inline HPBUFFERARB GetPixelBuffer()
	{
		return m_PixelBuffer;
	}

	/**
	* Get the Pixel Buffer Width
	*/
	inline vuint GetWidth()
	{
		return m_DisplaySettings.GetWidth();
	}

	/**
	* Get the Pixel Buffer Height
	*/
	inline vuint GetHeight()
	{
		return m_DisplaySettings.GetHeight();
	}

	/**
	 * @see v3d::graphics::IVRenderContext::MakeCurrent
	*/
	void MakeCurrent();

	/**
	 * @see v3d::graphics::IVRenderContext::SwapBuffers
	*/
	void SwapBuffers();

	/**
	* @see v3d::graphics::IVRenderContext::CreateOffscreenContext
	*/
	IVRenderContext* CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings);

private:

	graphics::VDisplaySettings m_DisplaySettings;
	HPBUFFERARB                m_PixelBuffer;
	HDC                        m_PBufferDeviceContext;
	HDC                        m_WindowDeviceContext;
	HGLRC                      m_PBufferRenderContext;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::graphics::VPBufferWindowContext, v3d::graphics::IVRenderContext);

#endif //V3D_VPBUFFERWINDOWCONTEXT_H