#include <v3d/System/IVSystemManager.h>
//-----------------------------------------------------------------------------
#include "VEditorFrame.h"
#include "wx/statline.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace editor {
//-----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(VEditorFrame, wxFrame)
EVT_MENU(ID_Quit, VEditorFrame::OnQuit)
EVT_MENU(ID_About, VEditorFrame::OnAbout)
END_EVENT_TABLE()

VEditorFrame::VEditorFrame() : wxFrame ((wxFrame *) NULL, -1,
								"v3d Editor", wxPoint(400, 300),
								wxSize(800, 800), wxCAPTION, "frame")
{
	Register();
	CreateStatusBar();
	SetStatusText("ready");

	menuFile.Append( ID_About, "About" );
	menuFile.AppendSeparator();
	menuFile.Append( ID_Quit, "E&xit" );
	

	m_MenuBar.Append(&menuFile, "File");
	SetMenuBar(&m_MenuBar);

}

void VEditorFrame::ShowFrame(vbool in_Param)
{
	wxFrame::Show(in_Param);
}

VEditorFrame::~VEditorFrame()
{
}

void VEditorFrame::OnQuit(wxCommandEvent& event)
{
	SetStatusText("exiting...");
	system::IVSystemManager* SystemManager;
	SystemManager =	QueryObject<system::IVSystemManager>("system.service");
	
	SystemManager->SetStatus(false);

}

void VEditorFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is the 3d editor of velox",
		"About v3d Editor", wxOK | wxICON_INFORMATION, this);
}


//-----------------------------------------------------------------------------
} // namespace editor
} // namespace v3d
//-----------------------------------------------------------------------------
