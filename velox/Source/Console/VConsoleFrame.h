/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCONSOLEWINDOW_H
#define V3D_VCONSOLEWINDOW_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Error/IVErrorListener.h>
#include <v3d/Error/VMessageTypeEnum.h>
#include <v3d/Utils/IVStringStream.h>
#include <v3d/Window/IVWindowFrame.h>
#include <v3d/Console/IVConsoleService.h>
//-----------------------------------------------------------------------------
#pragma warning( disable : 4267 )
#include <wx/wx.h>
#pragma warning( default : 4267 )
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
	typedef IVConsoleService::CommandConnection CommandConnection;
	typedef IVConsoleService::CommandSlot CommandSlot;

	VConsoleFrame();
	virtual ~VConsoleFrame();

	CommandConnection RegisterCommandListener(const CommandSlot& slot);

	void WriteText(VStringParam in_Text);
	void InvokeCommand(VStringParam in_strCommand);

	void ShowFrame(vbool in_Param);
	wxTextCtrl* GetTextControl();

	
private:
	IVConsoleService::CommandSignal m_CommandSignal;

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

