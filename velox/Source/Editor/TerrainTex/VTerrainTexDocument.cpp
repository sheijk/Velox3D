/////////////////////////////////////////////////////////////////////////////
// Name:        VTerrainTexDocument.cpp
// Purpose:     
// Author:      Jan Rehders
// Modified by: 
// Created:     06/29/04 11:02:05
// RCS-ID:      
// Copyright:   Copy this to die
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "VTerrainTexDocument.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "VTerrainTexDocument.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

////@begin XPM images
////@end XPM images

/*!
 * VTerrainTexDocument type definition
 */

//IMPLEMENT_DYNAMIC_CLASS( VTerrainTexDocument, wxFrame )

/*!
 * VTerrainTexDocument event table definition
 */

BEGIN_EVENT_TABLE( VTerrainTexDocument, wxFrame )
	EVT_TIMER( ID_REPAINTTIMER, VTerrainTexDocument::OnRegularUpdate )

////@begin VTerrainTexDocument event table entries
    EVT_MENU( ID_ADDTEXTOOL, VTerrainTexDocument::OnAddtextoolClick )

    EVT_MENU( ID_DELTEXTOOL, VTerrainTexDocument::OnDeltextoolClick )

    EVT_MENU( ID_VIEWCURRTEXTOOL, VTerrainTexDocument::OnViewcurrtextoolClick )

    EVT_MENU( ID_VIEWTERRAINTEXTOOL, VTerrainTexDocument::OnViewterraintextoolClick )

    EVT_LISTBOX( ID_TEXSTAGELISTBOX, VTerrainTexDocument::OnTexstagelistboxSelected )

////@end VTerrainTexDocument event table entries

END_EVENT_TABLE()

//-----------------------------------------------------------------------------
VRenderPanel::VRenderPanel(
		wxWindow* in_pParent, 
		vint in_Id, 
		wxPoint in_Pos, wxSize in_Size, 
		vint in_Style
		) :
	wxPanel(
		in_pParent,
		in_Id,
		in_Pos,
		in_Size,
		in_Style
		)
{
	VServicePtr<window::IVWindowManager> pWinManager;

	graphics::VDisplaySettings settings;
	settings.m_bFullscreen = false;
	settings.m_sAPIType = "OpenGL";
	settings.m_iWinCoordX = in_Pos.x;
	settings.m_iWinCoordY = in_Pos.y;
	settings.m_iWidth = GetSize().GetWidth();
	settings.m_iHeight = GetSize().GetHeight();

	m_pDevice = pWinManager->CreateGraphicsDevice(settings, (void*)GetHandle());
}

VRenderPanel::VRenderPanel(
	wxWindow* in_pParent, 
	wxPoint in_Pos, 
	wxSize in_Size
	) :
	wxPanel(
		in_pParent,
		-1,
		in_Pos,
		in_Size
		)
{
	VServicePtr<window::IVWindowManager> pWinManager;

	graphics::VDisplaySettings settings;
	settings.m_bFullscreen = false;
	settings.m_sAPIType = "OpenGL";
	settings.m_iWinCoordX = in_Pos.x;
	settings.m_iWinCoordY = in_Pos.y;
	settings.m_iWidth = GetSize().GetWidth();
	settings.m_iHeight = GetSize().GetHeight();

	m_pDevice = pWinManager->CreateGraphicsDevice(settings, (void*)GetHandle());
}

v3d::graphics::IVDevice& VRenderPanel::GetDevice()
{
	return *m_pDevice;
}

const v3d::graphics::IVDevice& VRenderPanel::GetDevice() const
{
	return *m_pDevice;
}

//-----------------------------------------------------------------------------
VTerrainTexDocument::VTerrainTexDocument(
		wxWindow* in_pParent, 
		vuint in_nWidth, 
		vuint in_nHeight)
{
	Create(in_pParent);

	m_pDrawList.Assign(new graphics::VSimpleDrawList(
		m_pPreviewPanel->GetDevice()));

	SetWindowMode(IVDocument::Show);

	//m_TextureStages.push_back(SharedPtr(new VTextureStage("/data/test2.jpg", 
	//	m_pPreviewPanel->GetDevice())));

	Render();
}

IVDocument::Connection VTerrainTexDocument::RegisterFocusListener(const FocusSlot& in_Slot)
{
	return IVDocument::Connection();
}

void VTerrainTexDocument::SetWindowMode(WindowMode in_Mode)
{
	switch(in_Mode)
	{
	case IVDocument::Hide:
		{
			this->wxFrame::Show(false);
		} break;
	case IVDocument::Show:
		{
			this->wxFrame::Show(true);
		} break;
	}
}

VMessageTreatment VTerrainTexDocument::DeliverMessage(IVMessage& in_Message)
{
	return MessageIgnored;
}

void VTerrainTexDocument::Render()
{
	v3d::graphics::IVDevice& device(m_pPreviewPanel->GetDevice());

	device.BeginScene();
	//m_pDrawList->Render();
	device.EndScene();
}

void VTerrainTexDocument::UpdateTexStageListBox()
{
	m_pTexStageListBox->Clear();

	for(vuint stageId = 0; stageId < m_TextureStages.size(); ++stageId)
	{
		m_pTexStageListBox->Append(
			m_TextureStages[stageId]->GetTextureFileName().AsCString());
	}
}

void VTerrainTexDocument::OnRegularUpdate(wxTimerEvent& in_Event)
{
	//Render();
}

vint VTerrainTexDocument::GetSelectedTexStage() const
{
	return m_pTexStageListBox->GetSelection();
}

vbool VTerrainTexDocument::ValidTexStageIndex(vint index) const
{
	return index >= 0 && index < m_TextureStages.size();
}

//-----------------------------------------------------------------------------
/*!
 * VTerrainTexDocument constructors
 */

VTerrainTexDocument::VTerrainTexDocument( )
{
}

VTerrainTexDocument::VTerrainTexDocument( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create( parent, id, caption, pos, size, style );
}

/*!
 *  VTerrainTexDocument creator
 */

bool VTerrainTexDocument::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin VTerrainTexDocument member initialisation
    m_pTexStageListBox = NULL;
    m_pPreviewPanel = NULL;
////@end VTerrainTexDocument member initialisation

////@begin VTerrainTexDocument creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end VTerrainTexDocument creation

	m_pTimer = new wxTimer(this, ID_REPAINTTIMER);
	m_pTimer->Start(100);

    return TRUE;
}

/*!
 * Control creation for  VTerrainTexDocument
 */

void VTerrainTexDocument::CreateControls()
{    
////@begin VTerrainTexDocument content construction

    VTerrainTexDocument* item1 = this;

    wxToolBar* item2 = new wxToolBar( item1, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER|wxNO_BORDER );
    wxBitmap item3Bitmap(item1->GetBitmapResource(wxT("icons\\plus.bmp")));
    item2->AddTool(ID_ADDTEXTOOL, _("Add Texture Stage"), item3Bitmap, _T(""), wxITEM_NORMAL);
    wxBitmap item4Bitmap(item1->GetBitmapResource(wxT("icons\\redx.bmp")));
    item2->AddTool(ID_DELTEXTOOL, _("Delete texture state"), item4Bitmap, _T(""), wxITEM_NORMAL);
    item2->AddSeparator();
    wxBitmap item6Bitmap(item1->GetBitmapResource(wxT("icons\\t.bmp")));
    item2->AddTool(ID_VIEWCURRTEXTOOL, _("Show current texture"), item6Bitmap, _T(""), wxITEM_RADIO);
    wxBitmap item7Bitmap(item1->GetBitmapResource(wxT("icons\\map.bmp")));
    item2->AddTool(ID_VIEWTERRAINTEXTOOL, _("Show composed terrain texture"), item7Bitmap, _T(""), wxITEM_RADIO);
    item2->AddSeparator();
    item2->Realize();
    item1->SetToolBar(item2);
    wxSplitterWindow* item9 = new wxSplitterWindow( item1, ID_SPLITTERWINDOW, wxDefaultPosition, wxSize(100, 100), wxNO_BORDER );
    wxPanel* item10 = new wxPanel( item9, ID_PANEL, wxDefaultPosition, wxSize(100, 80), wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
    wxFlexGridSizer* item11 = new wxFlexGridSizer(1, 1, 0, 0);
    item11->AddGrowableRow(0);
    item11->AddGrowableCol(0);
    item10->SetSizer(item11);
    item10->SetAutoLayout(TRUE);
    wxString* item12Strings = NULL;
    wxListBox* item12 = new wxListBox( item10, ID_TEXSTAGELISTBOX, wxDefaultPosition, wxDefaultSize, 0, item12Strings, wxLB_SINGLE|wxNO_BORDER );
    m_pTexStageListBox = item12;
    item11->Add(item12, 10, wxGROW|wxGROW|wxALL|wxADJUST_MINSIZE, 0);
    VRenderPanel* item13 = new VRenderPanel( item9, ID_PREVIEWPANEL, wxDefaultPosition, wxSize(100, 80), wxNO_BORDER|wxTAB_TRAVERSAL );
    m_pPreviewPanel = item13;
    item9->SplitVertically(item10, item13, 100);
////@end VTerrainTexDocument content construction
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_ADDTEXTOOL
 */
void VTerrainTexDocument::OnAddtextoolClick( wxCommandEvent& event )
{
	wxString filename = wxGetTextFromUser("Please enter a vfs file name");

	try
	{
		if( filename != "" )
		{
			m_TextureStages.push_back(
				SharedPtr(new VTextureStage(filename, m_pDrawList->GetDevice())));

			UpdateTexStageListBox();
		}
	}
	catch(VException& e)
	{
		std::string message = "Could not find file: ";
		message += e.GetErrorString().AsCString();

		wxMessageBox(message.c_str(), "Error");
	}
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_DELTEXTOOL
 */

void VTerrainTexDocument::OnDeltextoolClick( wxCommandEvent& event )
{
	vuint selection = m_pTexStageListBox->GetSelection();

	if( selection >= 0 && selection < m_pTexStageListBox->GetCount() )
	{
		m_TextureStages.erase(m_TextureStages.begin()+selection);

		UpdateTexStageListBox();
	}
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_VIEWCURRTEXTOOL
 */
void VTerrainTexDocument::OnViewcurrtextoolClick( wxCommandEvent& event )
{
    // Insert custom code here
    event.Skip();
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_VIEWTERRAINTEXTOOL
 */
void VTerrainTexDocument::OnViewterraintextoolClick( wxCommandEvent& event )
{
    // Insert custom code here
    event.Skip();
}

/*!
 * wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_TEXSTAGELISTBOX
 */
void VTerrainTexDocument::OnTexstagelistboxSelected( wxCommandEvent& event )
{
	const vint selection = GetSelectedTexStage();
	const vint newSelection = event.GetSelection();

	//vout << "hid tex stage " << selection 
	//	<< " showed tex stage " << newSelection
	//	<< vendl;

	// hide current tex stage
	if( ValidTexStageIndex(selection) )
	{
		vout << "hiding tex stage " << selection << "... ";

		m_TextureStages[selection]->RemovePreviewMesh(*m_pDrawList);
	}	

	// show selected tex stage
	if( ValidTexStageIndex(newSelection) )
	{
		vout << "showing tex stage " << newSelection;
		m_TextureStages[newSelection]->AddPreviewMesh(*m_pDrawList);
	}

	vout << vendl;
}

/*!
 * Should we show tooltips?
 */

bool VTerrainTexDocument::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap VTerrainTexDocument::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin VTerrainTexDocument bitmap retrieval
    if (name == wxT("icons\\plus.bmp"))
    {
        wxBitmap bitmap(_T("icons\\plus.bmp"), wxBITMAP_TYPE_BMP);
        return bitmap;
    }
    else if (name == wxT("icons\\redx.bmp"))
    {
        wxBitmap bitmap(_T("icons\\redx.bmp"), wxBITMAP_TYPE_BMP);
        return bitmap;
    }
    else if (name == wxT("icons\\t.bmp"))
    {
        wxBitmap bitmap(_T("icons\\t.bmp"), wxBITMAP_TYPE_BMP);
        return bitmap;
    }
    else if (name == wxT("icons\\map.bmp"))
    {
        wxBitmap bitmap(_T("icons\\map.bmp"), wxBITMAP_TYPE_BMP);
        return bitmap;
    }
    return wxNullBitmap;
////@end VTerrainTexDocument bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon VTerrainTexDocument::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin VTerrainTexDocument icon retrieval
    return wxNullIcon;
////@end VTerrainTexDocument icon retrieval
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------


