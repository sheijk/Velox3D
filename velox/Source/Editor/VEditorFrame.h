#ifndef V3D_EDTITORFRAME_H
#define V3D_EDTITORFRAME_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Window/IVWindowFrame.h>
//-----------------------------------------------------------------------------
#include <V3d/Editor/IVRegistry.h>

#pragma warning (disable : 4267)
#include <wx/wx.h>
#pragma warning (default : 4267)

//-----------------------------------------------------------------------------
namespace v3d {
namespace editor {
//-----------------------------------------------------------------------------
//TODO: huh? wozu ist das gut? (sheijk)
class VEditorFrame;

class VEditorFrame : public wxFrame, public window::IVWindowFrame
{
public:
	typedef std::vector<IVPlugin*> PluginList;

	enum MenuConstants
	{
		QuitId = 1,
		AboutId,
		ActionId,
		FirstFreeId
	};

	VEditorFrame(PluginList& in_Plugins);
	~VEditorFrame();

	void ShowFrame(vbool in_Param);

private:
	typedef VPointer<wxMenu>::SharedPtr WxMenuPtr;
	typedef std::vector<WxMenuPtr> WxMenuList;
	typedef std::map<vint, IVAction*> MenuActionMap;

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnAction(wxCommandEvent& event);

	vint GetNextMessageId();

	wxMenuBar m_MenuBar;
	WxMenuList m_Menues;
	MenuActionMap m_MenuActions;

	vint m_nNextFreeMessageId;

	DECLARE_EVENT_TABLE()
};


//-----------------------------------------------------------------------------
} // namespace editor
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONSOLEWINDOW_H
