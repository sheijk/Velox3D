/////////////////////////////////////////////////////////////////////////////
// Name:        VTerrainTexDocument.h
// Purpose:     
// Author:      Jan Rehders
// Modified by: 
// Created:     06/29/04 11:02:05
// RCS-ID:      
// Copyright:   Copy this to die
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#ifndef _VTERRAINTEXDOCUMENT_H_
#define _VTERRAINTEXDOCUMENT_H_
//-----------------------------------------------------------------------------

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "VTerrainTexDocument.cpp"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
#include "wx/toolbar.h"
#include "wx/splitter.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class VRenderPanel;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_FRAME 10000
#define SYMBOL_VTERRAINTEXDOCUMENT_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_VTERRAINTEXDOCUMENT_TITLE _("Freakin' main widow")
#define SYMBOL_VTERRAINTEXDOCUMENT_IDNAME ID_FRAME
#define SYMBOL_VTERRAINTEXDOCUMENT_SIZE wxSize(600, 400)
#define SYMBOL_VTERRAINTEXDOCUMENT_POSITION wxDefaultPosition
#define ID_TOOLBAR 10001
#define ID_ADDTEXTOOL 10002
#define ID_DELTEXTOOL 10003
#define ID_SELECTHM 10029
#define ID_TOOL_VIEWTEXSTAGE 10004
#define ID_TOOL_VIEWTEXTURE 10005
#define ID_TOOL_VIEWHM 10031
#define ID_REGENERATE 10030
#define ID_SPLITTERWINDOW 10006
#define ID_PANEL 10007
#define ID_SPLITTERWINDOW1 10032
#define ID_PANEL6 10012
#define ID_TEXSTAGELISTBOX 10012
#define ID_PANEL5 10033
#define ID_TEXTCTRL_MINHEIGHT 10034
#define ID_TEXTCTRL_MAXHEIGHT 10035
#define ID_PREVIEWPANEL 10008
////@end control identifiers
#define ID_REPAINTTIMER 9999

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor/IVDocument.h>
#include <v3d/Editor/IVMessage.h>

#include "VTextureStage.h"

#include <v3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <v3d/Window.h>
#include <V3dLib/Containers.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

class VRenderPanel : public wxPanel
{
public:
	VRenderPanel(
		wxWindow* in_pParent, 
		vint in_Id, 
		wxPoint in_Pos, wxSize in_Size, 
		vint in_Style
		);

	VRenderPanel(wxWindow* in_pParent, wxPoint in_Pos, wxSize in_Size);
	v3d::graphics::IVDevice& GetDevice();
	const v3d::graphics::IVDevice& GetDevice() const;

private:
	v3d::window::IVWindowManager::GraphicsDevicePtr m_pDevice;
};

/*!
 * VTerrainTexDocument class declaration
 */
class VTerrainTexDocument: public wxFrame, public IVDocument
{    
    // DECLARE_DYNAMIC_CLASS( VTerrainTexDocument )
    DECLARE_EVENT_TABLE()

public:
	VTerrainTexDocument(
		wxWindow* in_pParent, 
		vuint in_nWidth, 
		vuint in_nHeight);

	virtual ~VTerrainTexDocument();

	virtual Connection RegisterFocusListener(const FocusSlot& in_Slot);
	virtual void SetWindowMode(WindowMode in_Mode);
	virtual VMessageTreatment DeliverMessage(IVMessage& in_Message);

private:
	typedef std::vector<VPointer<VTextureStage>::SharedPtr> TextureStageList;

	enum ViewMode
	{
		ViewNone,
		ViewTexStage,
		ViewHeightmap,
		ViewTerrainTex
	};

	ViewMode m_ViewMode;

	void HideCurrentView();
	void SetViewMode(ViewMode in_Mode);

	void UpdateTexStageListBox();
	void Render();

	void OnRegularUpdate(wxTimerEvent& in_Event);

	graphics::IVDevice& GetDevice();

	TextureStageList m_TextureStages;

	VPointer<graphics::VSimpleDrawList>::SharedPtr m_pDrawList;
	wxTimer* m_pTimer;

	vint GetSelectedTexStage() const;
	vbool ValidTexStageIndex(vint index) const;

	vint m_nSelectedTexStage;

	// texture data
	void GenerateTerrainTexture();

	VPointer<VTextureStage>::SharedPtr m_pTerrainTexture;
	//const vuint m_nWidth;
	//const vuint m_nHeight;

	// heightmap data
	std::string m_strHeightmapFileName;

	void LoadHeightmapFile(VStringParam in_strFileName);

	VArray2d<vfloat32, vuint> m_HeightValues;
	VPointer<VTextureStage>::SharedPtr m_pHeightmapImage;
	//graphics::IVDevice::MeshHandle m_hHeightmapMesh;
	//graphics::IVDevice::BufferHandle m_hHeightmapBuffer;

	// DialogBlocks generated section
public:
	/// Constructors
    VTerrainTexDocument( );
    VTerrainTexDocument( wxWindow* parent, wxWindowID id = SYMBOL_VTERRAINTEXDOCUMENT_IDNAME, const wxString& caption = SYMBOL_VTERRAINTEXDOCUMENT_TITLE, const wxPoint& pos = SYMBOL_VTERRAINTEXDOCUMENT_POSITION, const wxSize& size = SYMBOL_VTERRAINTEXDOCUMENT_SIZE, long style = SYMBOL_VTERRAINTEXDOCUMENT_STYLE );

	bool Create( wxWindow* parent, wxWindowID id = SYMBOL_VTERRAINTEXDOCUMENT_IDNAME, const wxString& caption = SYMBOL_VTERRAINTEXDOCUMENT_TITLE, const wxPoint& pos = SYMBOL_VTERRAINTEXDOCUMENT_POSITION, const wxSize& size = SYMBOL_VTERRAINTEXDOCUMENT_SIZE, long style = SYMBOL_VTERRAINTEXDOCUMENT_STYLE );

private:
    /// Creates the controls and sizers
    void CreateControls();

////@begin VTerrainTexDocument event handler declarations

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_ADDTEXTOOL
    void OnAddtextoolClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_DELTEXTOOL
    void OnDeltextoolClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_SELECTHM
    void OnSelecthmClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOL_VIEWTEXSTAGE
    void OnToolViewtexstageClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOL_VIEWTEXTURE
    void OnToolViewtextureClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TOOL_VIEWHM
    void OnToolViewhmClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_REGENERATE
    void   OnRegenerateClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_TEXSTAGELISTBOX
    void OnTexstagelistboxSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_TEXT_ENTER event handler for ID_TEXTCTRL_MINHEIGHT
    void OnTextctrlMinheightEnter( wxCommandEvent& event );

    /// wxEVT_COMMAND_TEXT_ENTER event handler for ID_TEXTCTRL_MAXHEIGHT
    void OnTextctrlMaxheightEnter( wxCommandEvent& event );

////@end VTerrainTexDocument event handler declarations

////@begin VTerrainTexDocument member function declarations


    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end VTerrainTexDocument member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin VTerrainTexDocument member variables
    wxListBox* m_pTexStageListBox;
    VRenderPanel* m_pPreviewPanel;
////@end VTerrainTexDocument member variables
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------

#endif // _VTERRAINTEXDOCUMENT_H_
