#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Window/IVWxConnector.h>
#include <v3d/Window/IVWindowFrame.h>
//-----------------------------------------------------------------------------
#include "VWindowsWxApp.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace wxwindows {
//-----------------------------------------------------------------------------
using namespace v3d::window;

//-----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(VDummyFrame, wxFrame)
EVT_TIMER	(VDummyFrame::TIMER_ID, VDummyFrame::OnTimer )
END_EVENT_TABLE()
//-----------------------------------------------------------------------------

VDummyFrame::VDummyFrame() : wxFrame ((wxFrame*)NULL,-1,
	"Dummy",wxPoint(0, 0),wxSize(10, 10), wxFRAME_NO_TASKBAR , "DummyFrame")
{
		m_DisplayTimer = new wxTimer( this, TIMER_ID );
		m_DisplayTimer->Start(1, wxTIMER_CONTINUOUS);
}
//-----------------------------------------------------------------------------

void VDummyFrame::OnTimer()
{
	wxWakeUpIdle();
}
//-----------------------------------------------------------------------------
// This destructor is no good idea and will crash by call --(ins)
//VDummyFrame::~VDummyFrame()
//{
//	//delete m_DisplayTimer;
////	wxFrame::~wxFrame();
//}

//-----------------------------------------------------------------------------

VWindowsWxApp::VWindowsWxApp()
{
	IVUpdateable::Register();
	m_DummyFrame = new VDummyFrame();
}
//-----------------------------------------------------------------------------

VWindowsWxApp::~VWindowsWxApp()
{
	// @note: This delete is no good idea and will crash by call --(ins)
	//delete m_DummyFrame;
}
//-----------------------------------------------------------------------------

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
		window::IVWindowFrame* frame = WinConnect->GetCurrentFrame();
		frame->ShowFrame(true);
	} 

	return 0;
}
//-----------------------------------------------------------------------------

void VWindowsWxApp::Activate()
{
}
//-----------------------------------------------------------------------------

void VWindowsWxApp::Deactivate()
{
}
//-----------------------------------------------------------------------------

void VWindowsWxApp::Update(vfloat32 in_fSeconds)
{
	MainLoop();
}
//-----------------------------------------------------------------------------

int VWindowsWxApp::OnExit()
{
	return wxApp::OnExit();
}
//-----------------------------------------------------------------------------

bool VWindowsWxApp::OnInit()
{
	return TRUE;
}
//-----------------------------------------------------------------------------

DECLARE_APP(VWindowsWxApp)
IMPLEMENT_APP_NO_MAIN(VWindowsWxApp)
//-----------------------------------------------------------------------------
} // namespace wxwindows
} // namespace v3d
//-----------------------------------------------------------------------------
