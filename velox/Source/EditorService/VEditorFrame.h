#ifndef V3D_EDTITORFRAME_H
#define V3D_EDTITORFRAME_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Window/IVWindowFrame.h>
//-----------------------------------------------------------------------------
#include <wx/wx.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace editor {
//-----------------------------------------------------------------------------
//TODO: huh? wozu ist das gut? (sheijk)
class VEditorFrame;

class VEditorFrame : public wxFrame, public window::IVWindowFrame
{
public:

	enum RMenu
	{
		ID_Quit = 1,
		ID_About
	};
	VEditorFrame();
	~VEditorFrame();

	void ShowFrame(vbool in_Param);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:

	wxMenuBar m_MenuBar;
	wxMenu menuFile;

	DECLARE_EVENT_TABLE()

};


//-----------------------------------------------------------------------------
} // namespace editor
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONSOLEWINDOW_H
