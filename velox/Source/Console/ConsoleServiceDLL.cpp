/**
 * Example Service DLL
 *
 * Makro um Import und Export in der gleichen Datei zu realisieren
 * wird nicht gebraucht, wg. dynamischen linken
 */
//TODO: add your service's name here
#define CONSOLE_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include "VConsoleService.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wx/wx.h>
#include <wx/msw/private.h>

#include <iostream>

//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::console;
//-----------------------------------------------------------------------------

// use a smart pointer to guarante object destruction
VPointer<VConsoleService>::AutoPtr g_pConsoleService;



CONSOLE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service object and register it
	g_pConsoleService.Assign(new VConsoleService());
}

CONSOLE_API void Shutdown()
{
	// delete and unregister service object
	g_pConsoleService.Release();
}

/**
 * DLL Einsprungspunkt, wird beim laden der DLL aufgerufen, sollte
 * aber meist nichts tun
 */

void WXDLLEXPORT wxEntryCleanup();
int __cdecl wxEntry(void *,void *,char *,int,bool);
int __cdecl wxEntry(WXHINSTANCE *);

BOOL WINAPI DllMain( HINSTANCE hInstance, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			
			wxEntry(hInstance);
			wxSetInstance(hInstance);
			DisableThreadLibraryCalls (hInstance);
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			wxEntryCleanup();
			break;
			
    }
    return TRUE;
}

//-----------------------------------------------------------------------------