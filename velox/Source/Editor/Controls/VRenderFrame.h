#ifndef V3D_VRENDERFRAME_2004_06_11_H
#define V3D_VRENDERFRAME_2004_06_11_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/IVDevice.h>
#include <v3d/Window/IVWindowManager.h>
#include <wx/wx.h>
#include <wx/minifram.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

/**
 * A wxWidgets miniframe which can be rendered to using a graphics device
 */
class VRenderFrame : public wxMiniFrame
{
public:
	VRenderFrame(wxWindow* in_pParent);

	graphics::IVDevice& QueryDevice();
	const graphics::IVDevice& QueryDevice() const;
private:
	window::IVWindowManager::GraphicsDevicePtr m_pDevice;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VRENDERFRAME_2004_06_11_H
