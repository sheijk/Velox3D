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
										  "Velox Console",wxPoint(50, 50),
										  wxSize(250, 700), wxCAPTION, "frame")
{
	Register();

	// some constant for easier tweaking of the layout
	// (a layout manager like in swing would be better, though :)
	const vuint cnLeft = 0;
	const vuint cnRight = 245;
	const vuint cnWidth = cnRight - cnLeft;
	const vuint cnTextControlTop = 0;
	const vuint cnInputControlTop = 625;
	const vuint cnButtonBarTop = 650;
	const vuint cnBottom = 675;
	const vuint cnQuitButtonLeft = 0;
	const vuint cnClearButtonLeft = cnWidth / 2;

	m_TextControl = NULL;
	m_InputControl = NULL;

	m_TextControl = new  wxTextCtrl(
		this, 
		-1, 
		_T(""),
		wxPoint(cnLeft, cnTextControlTop), 
		wxSize(cnWidth, cnInputControlTop - cnTextControlTop),
		wxTE_MULTILINE | wxTE_READONLY
		);

	m_InputControl = new  VTextControl(
		this, 
		-1, 
		_T(""),
		wxPoint(cnLeft, cnInputControlTop), 
		wxSize(cnWidth + 5, cnButtonBarTop - cnInputControlTop),
		wxTE_LEFT
		);

	m_QuitButton = new VQuitButton(
		this, 
		wxPoint(cnQuitButtonLeft, cnButtonBarTop), 
		wxSize(cnClearButtonLeft - cnQuitButtonLeft, cnBottom - cnButtonBarTop)
		);

	m_ClearButton = new VClearButton(
		this, 
		wxPoint(cnClearButtonLeft, cnButtonBarTop), 
		wxSize(cnWidth - cnClearButtonLeft, cnBottom - cnButtonBarTop)
		);
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
