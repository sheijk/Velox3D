#include "VConsoleFrame.h"
#include <v3d/System/IVSystemManager.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */




BEGIN_EVENT_TABLE(VTextControl, wxTextCtrl)
EVT_TEXT_ENTER(-1,VTextControl::OnEnter)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(VQuitButton, wxButton)
EVT_BUTTON(-1, VQuitButton::OnQuit) 
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(VClearButton, wxButton)
EVT_BUTTON(-1, VClearButton::OnClear) 
END_EVENT_TABLE()


VQuitButton::VQuitButton(wxWindow* parent, const wxPoint& pos,
						 const wxSize& size) : wxButton(parent, -1, _T("Quit"), 
									  pos, size, wxBU_EXACTFIT,
									  wxDefaultValidator, _T("Button"))
{

}

void VQuitButton::OnQuit(wxMouseEvent& event)
{
	system::IVSystemManager* SystemManager;
	SystemManager =	QueryObject<system::IVSystemManager>("system.service");

	SystemManager->SetStatus(false);
}

VClearButton::VClearButton(VConsoleFrame* parent, const wxPoint& pos,
						 const wxSize& size) : wxButton(parent, -1, _T("Clear"), 
						 pos, size, wxBU_EXACTFIT,
						 wxDefaultValidator, _T("Button"))
{
	m_pParent = parent;
}

void VClearButton::OnClear(wxMouseEvent& event)
{
	m_pParent->GetTextControl()->Clear();
	
}


VTextControl::VTextControl(VConsoleFrame *parent, wxWindowID id, const wxString
						   &value, const wxPoint &pos, const wxSize &size,
						   int style)
						   : wxTextCtrl(parent, id, value, pos, size, style)
{
	m_parent = parent;

}

// TODO: implement command processing
void VTextControl::OnEnter(wxKeyEvent& event)
{
	wxString text = this->GetValue();
	m_parent->WriteText("Command: ");
	m_parent->WriteText(text.c_str());
	m_parent->WriteText("\n");

	Clear();
}

VConsoleFrame::VConsoleFrame() : wxFrame ((wxFrame *) NULL, -1,
										  "Velox Console",wxPoint(100, 100),
										  wxSize(250, 750), wxCAPTION, "frame")
{
	Register();

	m_TextControl = NULL;
	m_InputControl = NULL;

	m_TextControl = new  wxTextCtrl(this, -1, _T(""),
		wxPoint(0,0), wxSize(245,650),
		wxTE_MULTILINE | wxTE_READONLY );

	m_InputControl = new  VTextControl(this, -1, _T(""),
		wxPoint(0,650), wxSize(250,25),
		wxTE_LEFT);

	m_QuitButton = new VQuitButton(this, wxPoint(0,675), wxSize(245,25));
	m_ClearButton = new VClearButton(this, wxPoint(0,700), wxSize(245,25));

}

void VConsoleFrame::ShowFrame(vbool in_Param)
{
	wxFrame::Show(in_Param);
}

wxTextCtrl* VConsoleFrame::GetTextControl()
{
	return m_TextControl;
}


void VConsoleFrame::WriteText(VStringParam in_Text)
{
	wxString string(in_Text);
	m_TextControl->AppendText(string);
}

VConsoleFrame::~VConsoleFrame()
{

}
//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
