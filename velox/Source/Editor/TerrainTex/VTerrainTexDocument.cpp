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

#include <limits>
#include <v3d/Vfs.h>
#include <v3d/VFS/IVFileSystem.h>
#include <v3d/VFS/VIOException.h>
#include <v3d/Core/MemManager.h>
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

    EVT_MENU( ID_SELECTHM, VTerrainTexDocument::OnSelecthmClick )

    EVT_MENU( ID_TOOL_VIEWTEXSTAGE, VTerrainTexDocument::OnToolViewtexstageClick )

    EVT_MENU( ID_TOOL_VIEWTEXTURE, VTerrainTexDocument::OnToolViewtextureClick )

    EVT_MENU( ID_TOOL_VIEWHM, VTerrainTexDocument::OnToolViewhmClick )

    EVT_MENU( ID_REGENERATE, VTerrainTexDocument::  OnRegenerateClick )

    EVT_LISTBOX( ID_TEXSTAGELISTBOX, VTerrainTexDocument::OnTexstagelistboxSelected )

    EVT_TEXT_ENTER( ID_TEXTCTRL_MINHEIGHT, VTerrainTexDocument::OnTextctrlMinheightEnter )

    EVT_TEXT_ENTER( ID_TEXTCTRL_MAXHEIGHT, VTerrainTexDocument::OnTextctrlMaxheightEnter )

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
	settings.SetFullscreen(false);
	settings.SetAPI("OpenGL");
	//settings.m_bFullscreen = false;
	//settings.m_sAPIType = "OpenGL";
	//settings.m_iWinCoordX = in_Pos.x;
	//settings.m_iWinCoordY = in_Pos.y;
	settings.SetSize(GetSize().GetWidth(), GetSize().GetHeight());
	//settings.m_iWidth = GetSize().GetWidth();
	//settings.m_iHeight = GetSize().GetHeight();

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
	//	:
	//m_nWidth(in_nWidth),
	//m_nHeight(in_nHeight)
{
	m_nSelectedTexStage = -1;

	Create(in_pParent);

	m_pDrawList.Assign(new graphics::VSimpleDrawList(
		m_pPreviewPanel->GetDevice()));

	SetWindowMode(IVDocument::Show);

	//m_TextureStages.push_back(SharedPtr(new VTextureStage("/data/test2.jpg", 
	//	m_pPreviewPanel->GetDevice())));

	//TEST: load 3 textures
	m_TextureStages.push_back(SharedPtr(new VTextureStage(
		"/data/blue512.jpg", m_pDrawList->GetDevice())));
	m_TextureStages.back()->Distribution().maxHeight = 1.0f;
	m_TextureStages.back()->Distribution().minHeight = .67f;

	m_TextureStages.push_back(SharedPtr(new VTextureStage(
		"/data/green512.jpg", m_pDrawList->GetDevice())));
	m_TextureStages.back()->Distribution().maxHeight = .67f;
	m_TextureStages.back()->Distribution().minHeight = .33f;

	m_TextureStages.push_back(SharedPtr(new VTextureStage(
		"/data/red512.jpg", m_pDrawList->GetDevice())));
	m_TextureStages.back()->Distribution().maxHeight = .33f;
	m_TextureStages.back()->Distribution().minHeight = 0.0f;

	UpdateTexStageListBox();

	m_ViewMode = ViewNone;
	// create empty terrain texture
	image::VImage image(in_nWidth, in_nHeight, 24);
	m_pTerrainTexture.Assign(new VTextureStage(image, GetDevice()));

	Render();
}

VTerrainTexDocument::~VTerrainTexDocument()
{
}

graphics::IVDevice& VTerrainTexDocument::GetDevice()
{
	return m_pDrawList->GetDevice();
}

namespace {
using namespace v3d;

template<typename T>
T UnitConversion(T val) { return val; }

template<
	typename HeightValue, 
	typename FileHeightValue,// = HeightValue,
	typename Convert// = UnitConversion<HeightValue> 
>
void LoadRawHeightmapFromStream(
	vfs::IVStream& in_Stream,
	VArray2d<HeightValue, vuint>& io_Heightmap
	)
{
	const vulong size = io_Heightmap.GetWidth() * io_Heightmap.GetHeight();

	if( sizeof(HeightValue) == sizeof(FileHeightValue) )
	{
		in_Stream.Read(io_Heightmap.GetRawData(), size);
	}
	else
	{
		graphics::VBuffer<FileHeightValue> data(new FileHeightValue[size], size);
		in_Stream.Read(data.GetDataAddress(), size);

		Convert conv;

		vbool x = false;

		for(vuint i = 0; i < data.GetSize(); ++i)
		{
			io_Heightmap.GetRawData()[i] = conv(data[i]);
			//if( data[i] > 0 )
			//{
			//	io_Heightmap.GetRawData()[i] = 1.0f;
			//	x = true;
			//}
		}
	}
}

//template<typename HeightValue>
//void LoadRawHeightmapFromFile(
//	vfs::IVBufferStream& in_Stream,
//	VArray2d<HeightValue, vuint>& out_Heightmap
//	)
//{
//	// calc size and set heightmap's size
//	const vuint nSize = pStream->GetSize();
//	const vfloat32 fSizeLen = std::sqrt(vfloat32(nSize));
//	const vuint nSizeLen = fSizeLen;
//
//	if( nSizeLen * nSizeLen != nSize )
//		return;
//
//	out_Heightmap.Resize(nSizeLen, nSizeLen);
//
//	// load data
//	LoadRawHeightmapFromStream(in_Stream, out_Heightmap);
//}

struct ByteToFloat
{
	vfloat32 operator()(vbyte val)
	{
		const vbyte maxb = std::numeric_limits<vbyte>::max();
		const vbyte minb = std::numeric_limits<vbyte>::min();

		vfloat32 res = val - minb;
		res /= (maxb - minb);

		return res;
	}
};

} // namespace

//template<typename BytesPerPixel>
//void SetPixel(VImage& image, vuint x, vuint y, vuint color)
//{
//	vbyte* dest = image.GetData()[x+y*image.GetWidth()*BytesPerPixel];
//
//	vuint src = *reinterpret_cast<vuint*>(dest);
//	src &= color << 4 - BytesPerPixel;
//	*reinterpret_cast<vuint*>(dest) = src;
//}

void VTerrainTexDocument::LoadHeightmapFile(VStringParam in_strFileName)
{
	// load heightmap
	if( m_pHeightmapImage.Get() != 0 )
	{
		m_pHeightmapImage->RemovePreviewMesh(*m_pDrawList);
	}
	
	// open file
	VServicePtr<v3d::vfs::IVFileSystem> pFS;
	vfs::IVFileSystem::FileStreamPtr pFile =
		pFS->OpenFile(in_strFileName, vfs::VReadAccess);

	// calc size and precision
	const vuint nSize = pFile->GetSize();
	const vfloat32 fSizeLen = std::sqrt(vfloat32(nSize));
	const vuint nSizeLen = fSizeLen;

	if( nSizeLen * nSizeLen == nSize )
	{
		m_HeightValues.ResizeUninit(nSizeLen, nSizeLen);

		LoadRawHeightmapFromStream<vfloat32, vbyte, ByteToFloat>(
			*pFile, m_HeightValues);
	}
	else
	{
		vout << "invalid size: " << nSize << vendl;
		return;
	}

	// create image
	image::VImage image(nSizeLen, nSizeLen, 24);
	vuint index = 0;
	for(vuint y = 0; y < nSizeLen; ++y)
	for(vuint x = 0; x < nSizeLen; ++x)
	{
		//image.GetData()[index+0] = 255;
		//image.GetData()[index+1] = 255;
		//image.GetData()[index+2] = 255;
		image.GetData()[index+0] = m_HeightValues(x,y) * 255;
		image.GetData()[index+1] = m_HeightValues(x,y) * 255;
		image.GetData()[index+2] = m_HeightValues(x,y) * 255;
		index += 3;
	}

	m_pHeightmapImage.Assign(new VTextureStage(image, GetDevice()));
	m_pHeightmapImage->AddPreviewMesh(*m_pDrawList);
}

class VColor4b
{
public:
	vbyte red, green, blue, alpha;

	VColor4b() {}
	VColor4b(vbyte r, vbyte g, vbyte b, vbyte a);
};

VColor4b::VColor4b(vbyte r, vbyte g, vbyte b, vbyte a)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

void VTerrainTexDocument::HideCurrentView()
{
	switch(m_ViewMode)
	{
	case ViewTexStage:
		{
			if( ValidTexStageIndex(GetSelectedTexStage()) )
			{
				m_TextureStages[GetSelectedTexStage()]->RemovePreviewMesh(*m_pDrawList);
			}
		} break;
	case ViewHeightmap:
		{
			if( m_pHeightmapImage.Get() != 0 )
			{
				m_pHeightmapImage->RemovePreviewMesh(*m_pDrawList);
			}
		} break;
	case ViewTerrainTex:
		{
			if( m_pTerrainTexture.Get() != 0 )
			{
				m_pTerrainTexture->RemovePreviewMesh(*m_pDrawList);
			}
		} break;
	};
}

void VTerrainTexDocument::SetViewMode(ViewMode in_Mode)
{
	HideCurrentView();

	switch(in_Mode)
	{
	case ViewTexStage:
		{
			if( ValidTexStageIndex(GetSelectedTexStage()) )
			{
				m_TextureStages[GetSelectedTexStage()]->AddPreviewMesh(*m_pDrawList);
			}
		} break;
	case ViewHeightmap:
		{
			if( m_pHeightmapImage.Get() != 0 )
			{
				m_pHeightmapImage->AddPreviewMesh(*m_pDrawList);
			}
		} break;
	case ViewTerrainTex:
		{
			if( m_pTerrainTexture.Get() != 0 )
			{
				m_pTerrainTexture->AddPreviewMesh(*m_pDrawList);
			}
		} break;
	};

	m_ViewMode = in_Mode;
}

void SetPixel24(image::VImage& image, vuint x, vuint y, VColor4b color)
{
	// calculate offset
	vbyte* dest = image.GetPixelData() + (y*image.GetWidth()+x)*3;

	dest[0] = color.red;
	dest[1] = color.green;
	dest[2] = color.blue;
}

void VTerrainTexDocument::GenerateTerrainTexture()
{
	V3D_ASSERT(m_pTerrainTexture.Get() != 0);

	m_pTerrainTexture->RemovePreviewMesh(*m_pDrawList);

	const vuint nWidth = m_pTerrainTexture->Image().GetWidth();
	const vuint nHeight = m_pTerrainTexture->Image().GetHeight();

	// combine all texture stages
	VColor4b col(255, 0, 0, 255);
	image::VImage image(m_pTerrainTexture->Image());
	const vuint nTexStageCount = m_TextureStages.size();

	for(vuint y = 0; y < nHeight; ++y)
	for(vuint x = 0; x < nWidth; ++x)
	for(vuint comp = 0; comp < 3; ++comp)
	{
		vbyte val = 0;

		for(vuint ts = 0; ts < nTexStageCount; ++ts)
		{
			vfloat32 height = m_HeightValues(x,y);
			vbyte tsv = m_TextureStages[ts]->GetPixelContribution(x, y, height, comp);

			val += tsv/nTexStageCount;
		}

		image.GetPixelData()[(x+y*image.GetWidth())*3+comp] = val;
		//SetPixel24(image, x, y, col);
	}

	m_pTerrainTexture.Assign(new VTextureStage(image, GetDevice()));

	//SetViewMode(ViewTexture);
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
	m_pDrawList->Render();
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
	Render();
}

vint VTerrainTexDocument::GetSelectedTexStage() const
{
	return m_nSelectedTexStage;
	//return m_pTexStageListBox->GetSelection();
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
    wxBitmap item5Bitmap(item1->GetBitmapResource(wxT("icons\\heightmap.bmp")));
    item2->AddTool(ID_SELECTHM, _("Select a heightmap"), item5Bitmap, _("Select the heightmap to be used as a base"), wxITEM_NORMAL);
    item2->AddSeparator();
    wxBitmap item7Bitmap(item1->GetBitmapResource(wxT("icons\\t.bmp")));
    item2->AddTool(ID_TOOL_VIEWTEXSTAGE, _("Show current texture"), item7Bitmap, _T(""), wxITEM_RADIO);
    wxBitmap item8Bitmap(item1->GetBitmapResource(wxT("icons\\map.bmp")));
    item2->AddTool(ID_TOOL_VIEWTEXTURE, _("Show composed terrain texture"), item8Bitmap, _T(""), wxITEM_RADIO);
    wxBitmap item9Bitmap(item1->GetBitmapResource(wxT("icons\\mapbw.bmp")));
    item2->AddTool(ID_TOOL_VIEWHM, _("View heightmap"), item9Bitmap, _T(""), wxITEM_RADIO);
    item2->AddSeparator();
    wxBitmap item11Bitmap(item1->GetBitmapResource(wxT("icons\\G.bmp")));
    item2->AddTool(ID_REGENERATE, _("Generate"), item11Bitmap, _("Generates the terrain texture"), wxITEM_NORMAL);
    item2->Realize();
    item1->SetToolBar(item2);
    wxSplitterWindow* item12 = new wxSplitterWindow( item1, ID_SPLITTERWINDOW, wxDefaultPosition, wxSize(200, 100), wxNO_BORDER );
    wxPanel* item13 = new wxPanel( item12, ID_PANEL, wxDefaultPosition, wxSize(100, 80), wxNO_BORDER|wxTAB_TRAVERSAL );
    wxFlexGridSizer* item14 = new wxFlexGridSizer(1, 1, 0, 0);
    item14->AddGrowableRow(0);
    item14->AddGrowableCol(0);
    item13->SetSizer(item14);
    item13->SetAutoLayout(TRUE);
    wxSplitterWindow* item15 = new wxSplitterWindow( item13, ID_SPLITTERWINDOW1, wxDefaultPosition, wxSize(200, 200), wxNO_BORDER );
    wxPanel* item16 = new wxPanel( item15, ID_PANEL6, wxDefaultPosition, wxSize(100, 80), wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* item17 = new wxBoxSizer(wxHORIZONTAL);
    item16->SetSizer(item17);
    item16->SetAutoLayout(TRUE);
    wxString* item18Strings = NULL;
    wxListBox* item18 = new wxListBox( item16, ID_TEXSTAGELISTBOX, wxDefaultPosition, wxDefaultSize, 0, item18Strings, wxLB_SINGLE|wxSIMPLE_BORDER );
    m_pTexStageListBox = item18;
    item17->Add(item18, 10, wxGROW|wxALL|wxADJUST_MINSIZE, 0);
    wxPanel* item19 = new wxPanel( item15, ID_PANEL5, wxDefaultPosition, wxSize(100, 80), wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
    wxFlexGridSizer* item20 = new wxFlexGridSizer(2, 2, 0, 0);
    item20->AddGrowableCol(1);
    item19->SetSizer(item20);
    item19->SetAutoLayout(TRUE);
    wxStaticText* item21 = new wxStaticText( item19, wxID_STATIC, _("Min Height"), wxDefaultPosition, wxDefaultSize, 0 );
    item20->Add(item21, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);
    wxTextCtrl* item22 = new wxTextCtrl( item19, ID_TEXTCTRL_MINHEIGHT, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
    item20->Add(item22, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxStaticText* item23 = new wxStaticText( item19, wxID_STATIC, _("Max height"), wxDefaultPosition, wxDefaultSize, 0 );
    item20->Add(item23, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);
    wxTextCtrl* item24 = new wxTextCtrl( item19, ID_TEXTCTRL_MAXHEIGHT, _("255"), wxDefaultPosition, wxDefaultSize, 0 );
    item20->Add(item24, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    item15->SplitHorizontally(item16, item19, 150);
    item14->Add(item15, 10, wxGROW|wxGROW|wxALL, 0);
    VRenderPanel* item25 = new VRenderPanel( item12, ID_PREVIEWPANEL, wxDefaultPosition, wxSize(100, 80), wxNO_BORDER|wxTAB_TRAVERSAL );
    m_pPreviewPanel = item25;
    item12->SplitVertically(item13, item25, 200);
////@end VTerrainTexDocument content construction
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_ADDTEXTOOL
 */
void VTerrainTexDocument::OnAddtextoolClick( wxCommandEvent& event )
{
	wxString filename = wxGetTextFromUser(
		"Please enter a vfs file name",
		"Select texture",
		wxEmptyString,
		this
		);

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
	const vuint selection = m_pTexStageListBox->GetSelection();

	if( ValidTexStageIndex(selection) )
	{
		m_TextureStages[selection]->RemovePreviewMesh(*m_pDrawList);
		m_TextureStages.erase(m_TextureStages.begin()+selection);

		UpdateTexStageListBox();
	}
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_VIEWCURRTEXTOOL
 */
void VTerrainTexDocument::OnToolViewtexstageClick( wxCommandEvent& event )
{
	SetViewMode(ViewTexStage);
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_VIEWTERRAINTEXTOOL
 */
void VTerrainTexDocument::OnToolViewtextureClick( wxCommandEvent& event )
{
	SetViewMode(ViewTerrainTex);
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOL_VIEWHM
 */

void VTerrainTexDocument::OnToolViewhmClick( wxCommandEvent& event )
{
	SetViewMode(ViewHeightmap);
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
	if( m_ViewMode == ViewTexStage && ValidTexStageIndex(selection) )
	{
		vout << "hiding tex stage " << selection << "... ";

		m_TextureStages[selection]->RemovePreviewMesh(*m_pDrawList);
	}

	// show selected tex stage
	if( m_ViewMode == ViewTexStage && ValidTexStageIndex(newSelection) )
	{
		vout << "showing tex stage " << newSelection;
		m_TextureStages[newSelection]->AddPreviewMesh(*m_pDrawList);
	}

	vout << vendl;

	m_nSelectedTexStage = newSelection;
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
    else if (name == wxT("icons\\heightmap.bmp"))
    {
        wxBitmap bitmap(_T("icons\\heightmap.bmp"), wxBITMAP_TYPE_BMP);
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
    else if (name == wxT("icons\\mapbw.bmp"))
    {
        wxBitmap bitmap(_T("icons\\mapbw.bmp"), wxBITMAP_TYPE_BMP);
        return bitmap;
    }
    else if (name == wxT("icons\\G.bmp"))
    {
        wxBitmap bitmap(_T("icons\\G.bmp"), wxBITMAP_TYPE_BMP);
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

typedef vfs::IVFileSystem::FileStreamPtr FilePtr;

FilePtr OpenVfsFile(VStringParam in_strFileName, vfs::VAccessModeFlags in_Mode)
{
	VServicePtr<vfs::IVFileSystem> pFS;
	return pFS->OpenFile(in_strFileName, in_Mode);
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_SELECTHM
 */

void VTerrainTexDocument::OnSelecthmClick( wxCommandEvent& event )
{
	wxString hmFileName = wxGetTextFromUser(
		"Please enter a valid vfs filename",
		"Select heightmap",
		wxString(m_strHeightmapFileName.c_str()),
		this
		);

	if( hmFileName != wxEmptyString )
		m_strHeightmapFileName = hmFileName.c_str();

	// load heightmap
	try
	{
		LoadHeightmapFile(m_strHeightmapFileName.c_str());
	}
	catch(vfs::VIOException& e)
	{
		wxMessageBox(
			wxString(e.GetErrorString().AsCString()),
			"Failed to open file",
			wxOK | wxCENTRE,
			this
			);

		m_strHeightmapFileName = "";
	}
}

/*!
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_REGENERATE
 */

void VTerrainTexDocument::  OnRegenerateClick( wxCommandEvent& event )
{
	if( m_pTerrainTexture.Get() != 0 )
	{
		GenerateTerrainTexture();
	}
	else
	{
		wxMessageBox(
			"Please load a heightmap first",
			"Could not generate terrain texture",
			wxOK | wxCENTRE,
			this
			);
	}
}

/*!
 * wxEVT_COMMAND_TEXT_ENTER event handler for ID_TEXTCTRL_MINHEIGHT
 */

void VTerrainTexDocument::OnTextctrlMinheightEnter( wxCommandEvent& event )
{
    // Insert custom code here
    event.Skip();
}

/*!
 * wxEVT_COMMAND_TEXT_ENTER event handler for ID_TEXTCTRL_MAXHEIGHT
 */

void VTerrainTexDocument::OnTextctrlMaxheightEnter( wxCommandEvent& event )
{
    // Insert custom code here
    event.Skip();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------





