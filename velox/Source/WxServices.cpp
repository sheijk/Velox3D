#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include <v3d/Core/Modules/VModuleBase.h>

#include "Console/VConsoleService.h"

#include "WxWindowsService/VWxConnector.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wx/wx.h>
#include <wx/msw/private.h>

#include <iostream>

//-----------------------------------------------------------------------------
void WXDLLEXPORT wxEntryCleanup();
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d::console;
using namespace v3d;
using namespace v3d::wxwindows;
//-----------------------------------------------------------------------------

class VWxModule : public VModuleBase
{
	VPointer<VConsoleService>::AutoPtr m_pConsoleService;
	VPointer<wxwindows::VWxConnector>::AutoPtr m_pWxConnector;

public:
	VWxModule() : VModuleBase("wx") 
	{
	}

	virtual void Initialize();
	virtual void Shutdown();
};

void VWxModule::Initialize()
{
	m_pWxConnector.Assign(new VWxConnector("wx.connector"));

	HINSTANCE hInstance = GetModuleHandle(NULL);

	wxEntry(hInstance);
	wxSetInstance(hInstance);
	DisableThreadLibraryCalls(hInstance);

	m_pConsoleService.Assign(new VConsoleService());
}

void VWxModule::Shutdown()
{
	m_pConsoleService.Release();

	m_pWxConnector.Release();
	wxEntryCleanup();
}

//-----------------------------------------------------------------------------
namespace 
{
	VWxModule g_theWxModule;
}
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------