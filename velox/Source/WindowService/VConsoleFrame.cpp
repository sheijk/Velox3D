/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VConsoleFrame.h"
#include <v3d/Window/IVWxConnector.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace win {
//-----------------------------------------------------------------------------

VConsoleFrame::VConsoleFrame() : wxFrame
							 ( (wxFrame *) NULL, -1, "Velox Console",
							 wxPoint(100, 100), wxSize(400, 700), wxCAPTION, "frame")
{


	Register();

	m_TextControl = NULL;
	m_InputControl = NULL;

	wxIcon Icon;
	Icon.LoadFile("res/console.ico",wxBITMAP_TYPE_ICO );
	SetIcon(Icon);


	m_TextControl = new  wxTextCtrl(this, -1, _T(""),
		wxPoint(0,0), wxSize(395,650),
		wxTE_MULTILINE | wxTE_READONLY );

	m_InputControl = new  wxTextCtrl(this, -1, _T(""),
		wxPoint(0,650), wxSize(400,25),
		wxTE_LEFT);

}

void VConsoleFrame::WriteText(VStringParam in_Text)
{
	wxString string(in_Text);
	m_TextControl->AppendText(string);
}

void VConsoleFrame::ShowFrame(vbool in_Param)
{
	wxFrame::Show(in_Param);
}



VConsoleFrame::~VConsoleFrame()
{

}

//-----------------------------------------------------------------------------

VConsoleFrame2::VConsoleFrame2() : wxFrame
( (wxFrame *) NULL, -1, "Velox",
 wxPoint(200, 120), wxSize(800, 700), wxCAPTION, "frame")
{


	Register();

	
	wxIcon Icon;
	Icon.LoadFile("res/console.ico",wxBITMAP_TYPE_ICO );
	SetIcon(Icon);
}

void VConsoleFrame2::ShowFrame(vbool in_Param)
{
	wxFrame::Show(in_Param);
}

VConsoleFrame2::~VConsoleFrame2()
{

}

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------

