#include "VConsoleFrame.h"
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
										  wxSize(250, 700), wxCAPTION, "frame")
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

}

void VConsoleFrame::ShowFrame(vbool in_Param)
{
	wxFrame::Show(in_Param);
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
