#ifndef V3D_EDTITORFRAME_H
#define V3D_EDTITORFRAME_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Window/IVWindowFrame.h>
//-----------------------------------------------------------------------------
#include <V3d/Editor/IVEditorSuite.h>

#include <v3d/Core/SmartPtr/VGuards.h>

#pragma warning (disable : 4267)
#include <wx/wx.h>
#pragma warning (default : 4267)

#include <v3d/Editor/IVDocument.h>
#include <v3d/Editor/IVDocumentClass.h>
#include <V3dLib/BoostSignals.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace editor {
//-----------------------------------------------------------------------------

class VEditorFrame :	public wxFrame, 
						public window::IVWindowFrame, 
						IVEditorSuite
{
public:
	typedef std::vector<IVPlugin*> PluginList;

	enum MenuConstants
	{
		QuitId = 1,
		AboutId,
		RepaintId,
		ActionId,
		FirstFreeId
	};

	VEditorFrame(PluginList& in_Plugins);
	~VEditorFrame();

	/** registers a new document class */
	void RegisterDocumentClass(IVDocumentClass& in_DocumentClass);

	void RegisterTool(IVTool& in_Tool);

	virtual VMessageTreatment SendToActiveDocument(IVMessage& in_Message);

	void ShowFrame(vbool in_Param);

private:
	class FocusChangeConnector
	{
	public:
		FocusChangeConnector(VEditorFrame* in_pFrame) : m_pFrame(in_pFrame)
		{
			V3D_ASSERT(m_pFrame != 0);
		}

		void operator()(IVDocument& doc, IVDocument::FocusEventType type)
		{
			m_pFrame->OnDocumentFocusChange(doc, type);
		}

	private:
		VEditorFrame* m_pFrame;
	};

	typedef VPointer<wxMenu>::SharedPtr WxMenuPtr;
	typedef std::vector<WxMenuPtr> WxMenuList;
	typedef std::map<vint, IVAction*> MenuActionMap;

	typedef std::vector<IVDocumentClass*> DocumentClassList;
	typedef std::vector<IVDocumentClass::DocumentPtr> DocumentList;

	void OnQuit(wxCommandEvent& in_Event);
	void OnAbout(wxCommandEvent& in_Event);
	void OnAction(wxCommandEvent& in_Event);
	void OnNewDocument(wxCommandEvent& in_Event);
	void OnShowDocument(wxCommandEvent& in_Event);
	void OnRepaint(wxCommandEvent& in_Event);

	vint GetNextMessageId();

	void CreateDocument(IVDocumentClass& in_DocClass);
	void CloseDocument(IVDocument* in_pDocument);

	void OnDocumentFocusChange(
		IVDocument& in_Doc, 
		IVDocument::FocusEventType in_Type);

	// ui management
	wxMenuBar m_MenuBar;
	WxMenuList m_Menues;
	MenuActionMap m_MenuActions;
	vint m_nNextFreeMessageId;
	FocusChangeConnector m_FocusConnector;

	// document and tool management
	DocumentList m_OpenDocuments;
	DocumentClassList m_DocumentClasses;

	IVDocument* m_pActiveDocument;

	DECLARE_EVENT_TABLE()
};


//-----------------------------------------------------------------------------
} // namespace editor
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONSOLEWINDOW_H
