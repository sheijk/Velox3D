#include <v3d/System/IVSystemManager.h>
//-----------------------------------------------------------------------------
#include "VEditorFrame.h"
#include "wx/statline.h"

#include <v3d/Core/VIOStream.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace editor {
//-----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(VEditorFrame, wxFrame)
EVT_MENU(QuitId, VEditorFrame::OnQuit)
EVT_MENU(AboutId, VEditorFrame::OnAbout)
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
		)
{
	m_nNextFreeMessageId = vint(FirstFreeId);

	Register();
	CreateStatusBar();
	SetStatusText("ready");

	CenterOnScreen();

	// build file menu
	vint dummyId = GetNextMessageId();

	WxMenuPtr pFileMenu(new wxMenu());
	pFileMenu->Append(AboutId, "About");
	pFileMenu->Append(dummyId, "Dummy");
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
		(*plugin)->Enable(this);
	}

	SetMenuBar(&m_MenuBar);
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
