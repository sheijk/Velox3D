#include "VTerrainTexGenPreviewFrame.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(VTerrainTexGenPreviewFrame, VRenderFrame)
EVT_SET_FOCUS(OnGotFocus)
EVT_KILL_FOCUS(OnLostFocus)
END_EVENT_TABLE()

VTerrainTexGenPreviewFrame::VTerrainTexGenPreviewFrame(
	wxWindow* in_pParent, 
	IVDocument& in_Doc,
	VTextureStageSetupFrame* in_pTexStageFrame
	) :
	VRenderFrame(in_pParent),
	m_Doc(in_Doc),
	m_pTexStageFrame(in_pTexStageFrame)
{
	SetSize(400, 300);
	CenterOnParent();
}

IVDocument::Connection VTerrainTexGenPreviewFrame::RegisterFocusListener(
	const IVDocument::FocusSlot& in_Slot)
{
	return m_FocusChangeSignal.connect(in_Slot);
}

void VTerrainTexGenPreviewFrame::OnGotFocus(wxFocusEvent& in_Event)
{
	m_FocusChangeSignal(m_Doc, IVDocument::GotFocus);
}

void VTerrainTexGenPreviewFrame::OnLostFocus(wxFocusEvent& in_Event)
{
	m_FocusChangeSignal(m_Doc, IVDocument::LostFocus);
}


//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
