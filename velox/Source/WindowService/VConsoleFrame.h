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
#include <v3d/Window/IVWxConnector.h>
//-----------------------------------------------------------------------------
#include <wx/wx.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace win {
//-----------------------------------------------------------------------------

class VConsoleFrame : public IVWindowFrame, public wxFrame
{
public:
	/**
	 * -----------------------------------------------------------------------------
	 */
	VConsoleFrame();
	~VConsoleFrame();

	void WriteText(VStringParam in_Text);
	void ShowFrame(vbool in_Param);
	
private:

	wxTextCtrl* m_TextControl;
	wxTextCtrl* m_InputControl;

};

class VConsoleFrame2 : public IVWindowFrame, public wxFrame
{
public:
	/**
	 * -----------------------------------------------------------------------------
	 */
	VConsoleFrame2();
	~VConsoleFrame2();

	
	void ShowFrame(vbool in_Param);
};


//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONSOLEWINDOW_H

