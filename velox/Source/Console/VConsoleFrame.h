#ifndef V3D_VCONSOLEWINDOW_H
#define V3D_VCONSOLEWINDOW_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Error/IVErrorListener.h>
#include <v3d/Error/VMessageTypeEnum.h>
#include <v3d/Utils/IVStringStream.h>
#include <v3d/Window/IVWindowFrame.h>
//-----------------------------------------------------------------------------
#include <wx/wx.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------

class VConsoleFrame;

class VQuitButton : public wxButton
{
public:

	VQuitButton(wxWindow* parent, const wxPoint& pos,
		const wxSize& size);

	void OnQuit(wxMouseEvent& event);

private:
	DECLARE_EVENT_TABLE()

};

class VClearButton : public wxButton
{
public:

	VClearButton(VConsoleFrame* parent, const wxPoint& pos,
		const wxSize& size);

	void OnClear(wxMouseEvent& event);

private:
	
	VConsoleFrame* m_pParent;

	DECLARE_EVENT_TABLE()

};


class VTextControl : public wxTextCtrl
{
public:

	VTextControl(VConsoleFrame *parent, wxWindowID id, const wxString &value,
		const wxPoint &pos, const wxSize &size, int style = 0);
		

	/*enum Event
	{
		ID_Enter = 1,
	};*/

	void OnEnter(wxKeyEvent& event);

private:

	VConsoleFrame* m_parent;
	
	
	DECLARE_EVENT_TABLE()


};

class VConsoleFrame : public wxFrame, public window::IVWindowFrame
{
public:

	VConsoleFrame();
	~VConsoleFrame();

	void WriteText(VStringParam in_Text);
	void ShowFrame(vbool in_Param);
	wxTextCtrl* GetTextControl();

	
private:

	wxTextCtrl* m_TextControl;
	VTextControl* m_InputControl;
	VQuitButton* m_QuitButton;
	VClearButton* m_ClearButton;



};


//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONSOLEWINDOW_H
