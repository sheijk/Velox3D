#include "VWindowsWxApp.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VWindowsWxApp::VWindowsWxApp()
{
	//this->Register();
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
	/*m_MainFrame = new VEditorMainFrame("Editor", 100, 100, 400, 700,
											wxCAPTION);

	m_MainFrame->Show(TRUE);
	SetTopWindow(m_MainFrame);*/

	return TRUE;	
}

DECLARE_APP(VWindowsWxApp)
IMPLEMENT_APP_NO_MAIN(VWindowsWxApp)
//-----------------------------------------------------------------------------
} // namespace editor
} // namespace v3d
//-----------------------------------------------------------------------------
