#include <v3d/System/IVSystemManager.h>
//-----------------------------------------------------------------------------
#include "VEditorFrame.h"
#include "wx/statline.h"

#include <v3d/Core/VIOStream.h>

//#include "TerrainTex/MainWindow.h"

#include <algorithm>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace editor {
//-----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(VEditorFrame, wxFrame)
EVT_MENU(QuitId, VEditorFrame::OnQuit)
EVT_MENU(AboutId, VEditorFrame::OnAbout)
EVT_MENU(RepaintId, VEditorFrame::OnRepaint)
END_EVENT_TABLE()

VEditorFrame::VEditorFrame(PluginList& in_Plugins) 
: 
	wxFrame (
		(wxFrame *) NULL, 
		-1,
		"Velox Editor", 
		wxPoint(100, 10),
		wxSize(800, 600), 
		wxCAPTION, 
		"frame"
		),
	m_FocusConnector(this),
	m_pActiveDocument(0),
	IVEditorSuite("editor.suite")
{
	m_nNextFreeMessageId = vint(FirstFreeId);

	Register();
	CreateStatusBar();
	SetStatusText("ready");

	CenterOnScreen();

	// build file menu
	vint dummyId = GetNextMessageId();
	vint newTerrainId = GetNextMessageId();

	WxMenuPtr pFileMenu(new wxMenu());
	pFileMenu->Append(newTerrainId, "New Terrain");

	Connect(
		newTerrainId,
		wxEVT_COMMAND_MENU_SELECTED,
		(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)
		VEditorFrame::OnNewDocument,
		0);

	pFileMenu->Append(AboutId, "About");
	pFileMenu->Append(dummyId, "Dummy");
	pFileMenu->Append(RepaintId, "Repaint");
	pFileMenu->AppendSeparator();
	pFileMenu->Append(QuitId, "E&xit");
	m_Menues.push_back(pFileMenu);

	m_MenuBar.Append(pFileMenu.Get(), "File");

	wxObject* p = reinterpret_cast<wxObject*>(dummyId);
	Connect(
		dummyId,
		wxEVT_COMMAND_MENU_SELECTED,
		(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)
		VEditorFrame::OnAction,
		p
		);

	// for each plugin add menu
	PluginList::iterator plugin = in_Plugins.begin();
	for( ; plugin != in_Plugins.end(); ++plugin)
	{
		WxMenuPtr pPluginMenu(new wxMenu());

		// for each action add menu item
		IVPlugin::ActionIterator action = (*plugin)->ActionsBegin();
		for( ; action != (*plugin)->ActionsEnd(); ++action)
		{
			vint id = GetNextMessageId();

			// register id - action connection
			m_MenuActions[id] = &*action;

			pPluginMenu->Append(
				m_nNextFreeMessageId, 
				action->GetName().AsCString());

			// register handler function
			Connect(
				id, 
				wxEVT_COMMAND_MENU_SELECTED,
				(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)
				VEditorFrame::OnAction
				);
		}

		m_Menues.push_back(pPluginMenu);
		m_MenuBar.Append(pPluginMenu.Get(), (*plugin)->GetName().AsCString());

		// enable plugin
		(*plugin)->Enable();
	}

	//WxMenuPtr pEditorMenu(new wxMenu());

	//// for each editor
	//EditorList::iterator editor = in_Editors.begin();
	//for( ; editor != in_Editors.end(); ++editor)
	//{
	//	// add it to editor menu selection
	//}

	//m_MenuBar.Append(pEditorMenu.Get(), "Editors");


	SetMenuBar(&m_MenuBar);

	//MainWindow* pMainWindow = new MainWindow(0);
	//pMainWindow->Show(true);
}

void VEditorFrame::RegisterDocumentClass(IVDocumentClass& in_DocClass)
{
	m_DocumentClasses.push_back(&in_DocClass);
}

void VEditorFrame::RegisterTool(IVTool& in_Tool)
{
	//TODO: add to menu etc
	in_Tool.Enable();
}

void VEditorFrame::ShowFrame(vbool in_bParam)
{
	wxFrame::Show(in_bParam);
}

VEditorFrame::~VEditorFrame()
{
}

/** signal shutdown */
void VEditorFrame::OnQuit(wxCommandEvent& event)
{
	SetStatusText("exiting...");

	VServicePtr<system::IVSystemManager> pSystemManager;
	
	pSystemManager->SetStatus(false);
}

void VEditorFrame::OnAction(wxCommandEvent& in_Event)
{
	vout << "action invoked" << in_Event.GetId() << vendl;

	MenuActionMap::iterator action = m_MenuActions.find(in_Event.GetId());
	if( action != m_MenuActions.end() )
	{
		action->second->Execute();
	}
}

void VEditorFrame::OnNewDocument(wxCommandEvent& in_Event)
{
	vout << "created new document" << vendl;

	CreateDocument(*m_DocumentClasses.front());
}

void VEditorFrame::OnShowDocument(wxCommandEvent& in_Event)
{
    // get active document
	// change it's visible mode
}

void VEditorFrame::OnRepaint(wxCommandEvent& in_Event)
{
	Refresh(false);
}

void VEditorFrame::CreateDocument(IVDocumentClass& in_DocClass)
{
	IVDocumentClass::DocumentPtr pDoc = in_DocClass.Create(this);

	if( pDoc.Get() != 0 )
	{
		pDoc->RegisterFocusListener(m_FocusConnector);

		m_OpenDocuments.push_back(pDoc);
	}
}

void VEditorFrame::OnDocumentFocusChange(
	IVDocument& in_Doc,
	IVDocument::FocusEventType in_Type
	)
{
	switch(in_Type)
	{
	case IVDocument::GotFocus:
		{
			m_pActiveDocument = &in_Doc;
			vout << "document " << &in_Doc << " got focus" << vendl;
		} break;
	case IVDocument::LostFocus:
		{
			vout << "document " << &in_Doc << " lost focus" << vendl;
		} break;
	default:
		{
			vout << "illegal focus event for window " << &in_Doc << vendl;
		} break;
	};
}

void VEditorFrame::CloseDocument(IVDocument* in_pDocument)
{
	V3D_ASSERT(in_pDocument != 0);

	// remove document from list
	for(
		DocumentList::iterator iter = m_OpenDocuments.begin();
		iter != m_OpenDocuments.end() && iter->Get() != in_pDocument;
		++iter
			)
	{
	}

	m_OpenDocuments.erase(iter);
}

VMessageTreatment VEditorFrame::SendToActiveDocument(IVMessage& in_Message)
{
	VMessageTreatment treatment;

	if( m_pActiveDocument != 0 )
	{
		treatment = m_pActiveDocument->DeliverMessage(in_Message);
	}
	else
	{
		treatment = MessageIgnored;
	}

	return treatment;
}

vint VEditorFrame::GetNextMessageId()
{
	++m_nNextFreeMessageId;
	return m_nNextFreeMessageId;
}

/** show about dialog */
void VEditorFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is the 3d editor of velox",
		"About v3d Editor", wxOK | wxICON_INFORMATION, this);
}


//-----------------------------------------------------------------------------
} // namespace editor
} // namespace v3d
//-----------------------------------------------------------------------------
