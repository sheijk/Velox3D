#ifndef V3D_VCONSOLEWINDOW_H
#define V3D_VCONSOLEWINDOW_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Error/IVErrorListener.h>
#include <v3d/Error/VMessageTypeEnum.h>
#include <v3d/Utils/IVStringStream.h>
#include <wx/wx.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------

class VConsoleFrame : public wxFrame
{
public:
	VConsoleFrame( const wxChar *title, 
		int xpos, int ypos, 
		int width, int height, long style);
	~VConsoleFrame();

	void WriteText(VStringParam in_Text);

private:

	wxTextCtrl* m_TextControl;
	wxTextCtrl* m_InputControl;

};

class VConsoleWindow : public wxApp, public error::IVErrorListener,
					   public util::IVStringStream
{
public:
	VConsoleWindow();
	~VConsoleWindow();

	virtual bool OnInit();
	virtual int MainLoop();
	virtual int OnExit();

	virtual void OnMessage( VStringParam in_strMessage,
		error::VMessageType in_MessageType,
		VStringParam in_strFile,
		vuint in_nLine );


	virtual void	OnProgressbarBegin() {};
	virtual void	OnProgressbarUpdate( const vfloat32 in_fIndex) {};
	virtual void	OnProgressbarEnd() {};
	virtual void	OnStateUpdate( VStringParam in_Text );

	void Write(VStringParam in_Text);
	virtual void Flush() {};

private:

	VConsoleFrame *m_ConsoleFrame;


};



//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONSOLEWINDOW_H
