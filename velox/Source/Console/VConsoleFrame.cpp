#include "VConsoleFrame.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */

VConsoleFrame::VConsoleFrame() : wxFrame ((wxFrame *) NULL, -1,
										  "Velox Console",wxPoint(100, 100),
										  wxSize(400, 700), wxCAPTION, "frame")
{
	Register();

	m_TextControl = NULL;
	m_InputControl = NULL;

	wxIcon Icon;
	Icon.LoadFile("res/console.ico",wxBITMAP_TYPE_ICO );
	SetIcon(Icon);


	m_TextControl = new  wxTextCtrl(this, -1, _T(""),
		wxPoint(0,0), wxSize(395,650),
		wxTE_MULTILINE | wxTE_READONLY );

	m_InputControl = new  wxTextCtrl(this, -1, _T(""),
		wxPoint(0,650), wxSize(400,25),
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
