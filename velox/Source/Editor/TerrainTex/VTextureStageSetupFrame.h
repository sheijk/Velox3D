#ifndef V3D_VTEXTURESTAGESETUPFRAME_2004_06_18_H
#define V3D_VTEXTURESTAGESETUPFRAME_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor/IVMessage.h>
#include "VTextureStage.h"
#include "../Utils/VToolBase.h"

#include <wx/wx.h>
#include <wx/minifram.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VTextureStageSetupFrame : public wxMiniFrame, public VToolBase
{
	enum ControlIds
	{
		AddTexButton = 1,
		RemoveTexButton,
		UpdateButton
	};

public:
	VTextureStageSetupFrame(wxWindow* in_pParent);

	virtual void Enable();
	virtual VMessageTreatment DeliverMessage(IVMessage& in_Message);

private:
	void OnAddTextureStage(wxCommandEvent& in_Event);
	void OnRemoveTextureStage(wxCommandEvent& in_Event);
	void OnUpdate(wxCommandEvent& in_Event);

	typedef std::vector<VTextureStage> TextureStageList;

	TextureStageList m_Stages;

	wxListBox* m_pListBox;
	wxButton* m_pAddTexButton;
	wxButton* m_pRemoveTexButton;
	wxButton* m_pUpdateButton;

	DECLARE_EVENT_TABLE();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTAGESETUPFRAME_2004_06_18_H
