#ifndef V3D_VTERRAINTEXTGENPREVIEWFRAME_2004_06_18_H
#define V3D_VTERRAINTEXTGENPREVIEWFRAME_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor/IVDocument.h>

#include "../Controls/VRenderFrame.h"
#include "VTextureStageSetupFrame.h"

#include <wx/wx.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VTerrainTexGenPreviewFrame : public VRenderFrame
{
public:
	VTerrainTexGenPreviewFrame(
		wxWindow* in_pParent, 
		IVDocument& in_Doc,
		VTextureStageSetupFrame* in_pTexStageFrame
		);

	IVDocument::Connection RegisterFocusListener(
		const IVDocument::FocusSlot& in_Slot);

private:
	void OnGotFocus(wxFocusEvent& in_Event);
	void OnLostFocus(wxFocusEvent& in_Event);

	IVDocument& m_Doc;
	IVDocument::FocusSignal m_FocusChangeSignal;
	const VTextureStageSetupFrame* m_pTexStageFrame;

	DECLARE_EVENT_TABLE();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAINTEXTGENPREVIEWFRAME_2004_06_18_H
