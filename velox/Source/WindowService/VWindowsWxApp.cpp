#include <v3d/Window/IVWxConnector.h>
#include <v3d/Core/VObjectRegistry.h>
#include "VWindowsWxApp.h"
//-----------------------------------------------------------------------------
#include "VConsoleFrame.h"
#include <v3d/Window/IVWindowFrame.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VWindowsWxApp::VWindowsWxApp()
{
	IVUpdateable::Register();
}

/**
 * d'tor
 */
VWindowsWxApp::~VWindowsWxApp()
{
}

int VWindowsWxApp::MainLoop()
{
	while (!Pending() && ProcessIdle())
		;
	// a message came or no more idle processing to do
	DoMessage();

	//return s_currentMsg.wParam;


	window::IVWxConnector* WinConnect;
	WinConnect = QueryObject<IVWxConnector>("wx.connector");


	IVWindowFrame* frame = WinConnect->GetCurrentFrame();
	
	vuint i;
	for(i = 0; i!= WinConnect->GetNumElements(); i++)
	{
		IVWindowFrame* frame = WinConnect->GetCurrentFrame();
		frame->ShowFrame(true);
	} 

	return 0;
}

void VWindowsWxApp::Activate()
{
}

void VWindowsWxApp::Deactivate()
{
}

void VWindowsWxApp::Update(vfloat32 in_fSeconds)
{
	MainLoop();
}

int VWindowsWxApp::OnExit()
{
	return wxApp::OnExit();
}

bool VWindowsWxApp::OnInit()
{
	return TRUE;	
}

DECLARE_APP(VWindowsWxApp)
IMPLEMENT_APP_NO_MAIN(VWindowsWxApp)
//-----------------------------------------------------------------------------
} // namespace editor
} // namespace v3d
//-----------------------------------------------------------------------------
