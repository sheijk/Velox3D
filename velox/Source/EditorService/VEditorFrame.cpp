#include <v3d/System/IVSystemManager.h>
//-----------------------------------------------------------------------------
#include "VEditorFrame.h"
#include "wx/statline.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace editor {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */

/*BEGIN_EVENT_TABLE(VEditorCanvas, wxScrolledWindow)
EVT_PAINT(  VEditorCanvas::OnPaint)
END_EVENT_TABLE()*/

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

	m_MenuBar = new wxMenuBar;
	
	wxMenu *menuFile = new wxMenu;

	menuFile->Append( ID_About, "About" );
	menuFile->AppendSeparator();
	menuFile->Append( ID_Quit, "E&xit" );
	

	m_MenuBar->Append(menuFile, "File");
	SetMenuBar(m_MenuBar);

	//m_pCanvas = new VEditorCanvas(this);

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



/*VEditorCanvas::VEditorCanvas(VEditorFrame *parent) : wxScrolledWindow(parent, -1,
												wxDefaultPosition,
												wxDefaultSize, wxHSCROLL | 
												wxVSCROLL | 
												wxNO_FULL_REPAINT_ON_RESIZE)
{

	m_Parent = parent;
}

void VEditorCanvas::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	PrepareDC( dc );
	DrawText(dc);
}


void VEditorCanvas::DrawText(wxDC& dc)
{
	dc.SetFont( wxFont(8, wxNORMAL, wxNORMAL, wxNORMAL, FALSE) );
	dc.DrawText( _T("This is text"), 10, 10 );
}*/
//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
