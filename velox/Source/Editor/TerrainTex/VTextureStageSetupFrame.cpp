#include "VTextureStageSetupFrame.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>
#include <v3d/Core/SmartPtr/VServicePtr.h>

#include <v3d/Editor/IVEditorSuite.h>

#include "Messages.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(VTextureStageSetupFrame, wxMiniFrame)
EVT_BUTTON(AddTexButton, OnAddTextureStage)
EVT_BUTTON(RemoveTexButton, OnRemoveTextureStage)
EVT_BUTTON(UpdateButton, OnUpdate)
END_EVENT_TABLE()

VTextureStageSetupFrame::VTextureStageSetupFrame(wxWindow* in_pParent) :
	VToolBase("Texture Stages"),
	wxMiniFrame(
		in_pParent,
		-1,
		"Texture Stages",
		wxPoint(0, 0),
		wxSize(150, 300),
		wxTINY_CAPTION_HORIZ | wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR
		),
	m_pListBox(0)
{
	wxPoint parentPos = in_pParent->ClientToScreen(wxPoint(0,15));
	wxSize parentSize = in_pParent->GetSize();

	SetSize(
		parentPos.x + parentSize.GetWidth() - GetSize().GetWidth(), 
		parentPos.y + 5, 
		-1, -1);

	// add selection for texture stage
	m_pListBox = new wxListBox(
		this,
		-1,
		wxPoint(0, 20),
		GetClientSize(),
		0,
		NULL
		);

	m_pAddTexButton = new wxButton(
		this,
		AddTexButton,
		"+",
		wxPoint(0, 0),
		wxSize(20, 20)
		);

	m_pRemoveTexButton = new wxButton(
		this,
		RemoveTexButton,
		"x",
		wxPoint(20, 0),
		wxSize(20, 20)
		);

	m_pUpdateButton = new wxButton(
		this,
		UpdateButton,
		"u",
		wxPoint(40, 0),
		wxSize(20, 20)
		);
}

void VTextureStageSetupFrame::Enable()
{
	Show(true);
}

VMessageTreatment VTextureStageSetupFrame::DeliverMessage(IVMessage& in_Message)
{
	return MessageIgnored;
}

void VTextureStageSetupFrame::OnAddTextureStage(wxCommandEvent& in_Event)
{
	vout << "added tex stage" << vendl;

	wxString caption("texture stage ");
	caption << m_pListBox->GetCount();

    m_pListBox->Append(caption);

	m_Stages.push_back(VTextureStage("/data/tex.tga"));
}

void VTextureStageSetupFrame::OnRemoveTextureStage(wxCommandEvent& in_Event)
{
	vout << "removed texture stage" << vendl;

	const vint selection = m_pListBox->GetSelection();

	if( selection >= 0 && selection < m_pListBox->GetCount() )
	{
		m_pListBox->Delete(selection);
		m_Stages.erase(m_Stages.begin()+selection);
	}
}

void VTextureStageSetupFrame::OnUpdate(wxCommandEvent& in_Event)
{
	const vint selection = m_pListBox->GetSelection();

	if( selection >= 0 && selection < m_pListBox->GetCount() )
	{
		vout << "send update" << vendl;

		VTextureStageUpdated msg(m_Stages[selection], selection);

		VServicePtr<IVEditorSuite> pEditor;
		if( pEditor->SendToActiveDocument(msg) == MessageProcessed )
		{
			vout << "processed" << vendl;
		}
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
