#include "VConsoleWindow.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */

VConsoleWindow::VConsoleWindow()
{
}

/**
 * d'tor
 */
VConsoleWindow::~VConsoleWindow()
{
}



bool VConsoleWindow::OnInit()
{
	m_ConsoleFrame = new VConsoleFrame("Velox Console", 100, 100, 400, 700, wxCAPTION);

	m_ConsoleFrame->Show(TRUE);
	SetTopWindow(m_ConsoleFrame);
		
	return TRUE;	
}



int VConsoleWindow::MainLoop()
{
	while (!Pending() && ProcessIdle())
			;
	// a message came or no more idle processing to do
	DoMessage();
	
	//return s_currentMsg.wParam;
	return 0;
}

int VConsoleWindow::OnExit()
{
	return wxApp::OnExit();
}

void VConsoleWindow::Write(VStringParam in_Text)
{
	m_ConsoleFrame->WriteText(in_Text);
}

VConsoleFrame::VConsoleFrame(const wxChar *title, int xpos, int ypos,
							 int width, int height, long style)	 : wxFrame
							 ( (wxFrame *) NULL, -1, title,
							 wxPoint(xpos, ypos),
							 wxSize(width, height), style, "frame")
{
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

void VConsoleFrame::WriteText(VStringParam in_Text)
{
	wxString string(in_Text);
	m_TextControl->AppendText(string);
}

void VConsoleWindow::OnMessage( VStringParam in_strMessage,
							    error::VMessageType in_MessageType,
								VStringParam in_strFile,
								vuint in_nLine )
{
	switch(in_MessageType)
	{
	case v3d::error::Normal:
		{
			*this << in_strMessage << "\n";
		}
		break;
	case v3d::error::Warning:
		{
			*this << "Warning: " << "[" << in_strFile << " in line" 
				  << in_nLine << "]:" << in_strMessage << "\n";
		}
		break;
	case v3d::error::Error:
		{
            *this << "Error: "<< "[" << in_strFile << " in line" 
				  << in_nLine << "]:" << in_strMessage << "\n";
		}
		break;
	}

	
}

void VConsoleWindow::OnStateUpdate( VStringParam in_Text )
{
	*this << "State: " << in_Text;
}


VConsoleFrame::~VConsoleFrame()
{

}
DECLARE_APP(VConsoleWindow)
//DECLARE_APP_NO_MAIN(VConsoleWindow);
//VConsoleWindow ConsoleWindow;
IMPLEMENT_APP_NO_MAIN(VConsoleWindow)

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
