#include "VRenderFrame.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

VRenderFrame::VRenderFrame(wxWindow* in_pParent) :
	wxMiniFrame(
		in_pParent,
		-1, 
		"demo plugin",
        wxPoint(0, 0),
		wxSize(640, 480),
		wxTINY_CAPTION_HORIZ | wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR
		)
{
	CenterOnParent();

	VServicePtr<window::IVWindowManager> pWinManager;

	graphics::VDisplaySettings settings;
	settings.m_bFullscreen = false;
	settings.m_sAPIType = "OpenGL";
	settings.m_iWidth = GetSize().GetWidth();
	settings.m_iHeight = GetSize().GetHeight();

	m_pDevice = pWinManager->CreateGraphicsDevice(settings, (void*)GetHandle());
}

graphics::IVDevice& VRenderFrame::QueryDevice()
{
	return *m_pDevice;
}

const graphics::IVDevice& VRenderFrame::QueryDevice() const
{
	return *m_pDevice;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------