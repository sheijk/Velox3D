#define WXWINDOWSSERVICE_API __declspec(dllexport)
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>
//-----------------------------------------------------------------------------
#include "VWxConnector.h"
//-----------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wx/wx.h>
#include <wx/msw/private.h>
//-----------------------------------------------------------------------------
void WXDLLEXPORT wxEntryCleanup();
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::wxwindows;
//-----------------------------------------------------------------------------
VPointer<wxwindows::VWxConnector>::AutoPtr g_pWxConnector;
//-----------------------------------------------------------------------------

WXWINDOWSSERVICE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service object and register it
	g_pWxConnector.Assign(new VWxConnector("wx.connector"));

	HINSTANCE hInstance = GetModuleHandle(NULL);

	
	wxEntry(hInstance);
	wxSetInstance(hInstance);
	DisableThreadLibraryCalls(hInstance);
}
//-----------------------------------------------------------------------------

WXWINDOWSSERVICE_API void Shutdown()
{
	// delete and unregister service object
	g_pWxConnector.Release();
	wxEntryCleanup();
}
//-----------------------------------------------------------------------------

BOOL WINAPI DllMain( HINSTANCE hInstance, 
					DWORD  ul_reason_for_call, 
					LPVOID lpReserved )

{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;

	}
	return TRUE;
}
//-----------------------------------------------------------------------------