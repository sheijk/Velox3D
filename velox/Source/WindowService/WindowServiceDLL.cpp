#define WINDOWSERVICE_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>
//-----------------------------------------------------------------------------
#include "VWindowManagerWin32.h"
//#include "VWxConnector.h"
//-----------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wx/wx.h>
#include <wx/msw/private.h>

//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::graphics;
using namespace v3d::window;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// use a smart pointer to guarante object destruction
VPointer<VWindowManagerWin32>::AutoPtr g_pWindowManagerWin;

HINSTANCE g_hInstance;

//VPointer<VWxConnector>::AutoPtr g_pWxConnector;

WINDOWSERVICE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service object and register it
	
	g_pWindowManagerWin.Assign(new VWindowManagerWin32());
	
	wxEntry(g_hInstance);
	wxSetInstance(g_hInstance);
	DisableThreadLibraryCalls (g_hInstance);
}

void WXDLLEXPORT wxEntryCleanup();

WINDOWSERVICE_API void Shutdown()
{
	// delete and unregister service object
	g_pWindowManagerWin.Release();
	//g_pWxConnector.Release();

	wxEntryCleanup();
}

/**
 * DLL Einsprungspunkt, wird beim laden der DLL aufgerufen, sollte
 * aber meist nichts tun
 */



BOOL WINAPI DllMain( HINSTANCE hInstance, 
					DWORD  ul_reason_for_call, 
					LPVOID lpReserved )

{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			g_hInstance = hInstance;
			break;
	
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	
    }
    return TRUE;
}

//-----------------------------------------------------------------------------